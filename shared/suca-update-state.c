#include "suca-update-state.h"

static int valid_slot(char slot) {
    return slot == 'A' || slot == 'B';
}

const char *suca_update_state_name(SucaUpdateState state) {
    switch (state) {
    case SUCA_UPDATE_IDLE: return "idle";
    case SUCA_UPDATE_CHECKING: return "checking";
    case SUCA_UPDATE_DOWNLOADING: return "downloading";
    case SUCA_UPDATE_VERIFYING: return "verifying";
    case SUCA_UPDATE_INSTALLING_INACTIVE: return "installing-inactive-slot";
    case SUCA_UPDATE_REBOOT_PENDING: return "reboot-pending";
    case SUCA_UPDATE_HEALTH_CHECK: return "health-check";
    case SUCA_UPDATE_COMMITTED: return "committed";
    case SUCA_UPDATE_ROLLBACK: return "rollback";
    default: return "unknown";
    }
}

int suca_update_transition(SucaUpdateContext *context, SucaUpdateState next) {
    if (!context || !valid_slot(context->active_slot) || !valid_slot(context->target_slot))
        return 0;
    if (context->active_slot == context->target_slot &&
        next == SUCA_UPDATE_INSTALLING_INACTIVE)
        return 0;
    if (next == SUCA_UPDATE_ROLLBACK && context->boot_attempts >= context->boot_attempt_limit) {
        context->state = SUCA_UPDATE_ROLLBACK;
        return 1;
    }
    context->state = next;
    return 1;
}

int suca_update_mark_health(SucaUpdateContext *context, int healthy) {
    if (!context || context->state != SUCA_UPDATE_HEALTH_CHECK)
        return 0;
    if (healthy) {
        context->active_slot = context->target_slot;
        context->state = SUCA_UPDATE_COMMITTED;
        context->boot_attempts = 0;
        return 1;
    }
    context->boot_attempts++;
    context->state = SUCA_UPDATE_ROLLBACK;
    return 1;
}

int suca_update_can_install(const SucaUpdateContext *context) {
    return context && valid_slot(context->active_slot) &&
           valid_slot(context->target_slot) &&
           context->active_slot != context->target_slot;
}
