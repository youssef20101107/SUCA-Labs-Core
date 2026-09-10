#include "suca-recovery-state.h"

const char *suca_recovery_state_name(SucaRecoveryState state) {
    switch (state) {
    case SUCA_RECOVERY_IDLE: return "idle";
    case SUCA_RECOVERY_INSPECTING: return "inspecting";
    case SUCA_RECOVERY_VERIFYING_BACKUP: return "verifying-backup";
    case SUCA_RECOVERY_RESTORING: return "restoring";
    case SUCA_RECOVERY_ROLLBACK_PENDING: return "rollback-pending";
    case SUCA_RECOVERY_COMPLETED: return "completed";
    case SUCA_RECOVERY_FAILED: return "failed";
    case SUCA_RECOVERY_REQUIRES_USER_ACTION: return "requires-user-action";
    default: return "unknown";
    }
}

int suca_recovery_transition(SucaRecoveryContext *context, SucaRecoveryState next) {
    if (!context) return 0;
    if (next == SUCA_RECOVERY_RESTORING &&
        (!context->original_preserved || !context->backup_verified))
        return 0;
    context->state = next;
    return 1;
}

int suca_recovery_can_restore(const SucaRecoveryContext *context) {
    return context && context->original_preserved && context->backup_verified;
}
