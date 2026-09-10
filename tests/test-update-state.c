#include <assert.h>
#include <string.h>
#include "../shared/suca-update-state.h"

int main(void) {
    SucaUpdateContext context = {
        .active_slot = 'A',
        .target_slot = 'B',
        .boot_attempts = 0,
        .boot_attempt_limit = 2,
        .state = SUCA_UPDATE_IDLE,
    };

    assert(suca_update_can_install(&context));
    assert(suca_update_transition(&context, SUCA_UPDATE_VERIFYING));
    assert(suca_update_transition(&context, SUCA_UPDATE_INSTALLING_INACTIVE));
    assert(suca_update_transition(&context, SUCA_UPDATE_REBOOT_PENDING));
    assert(suca_update_transition(&context, SUCA_UPDATE_HEALTH_CHECK));
    assert(suca_update_mark_health(&context, 1));
    assert(context.active_slot == 'B');
    assert(context.state == SUCA_UPDATE_COMMITTED);

    context.active_slot = 'A';
    context.target_slot = 'B';
    context.state = SUCA_UPDATE_HEALTH_CHECK;
    assert(suca_update_mark_health(&context, 0));
    assert(context.state == SUCA_UPDATE_ROLLBACK);

    context.active_slot = 'A';
    context.target_slot = 'A';
    assert(!suca_update_can_install(&context));
    assert(strcmp(suca_update_state_name(SUCA_UPDATE_ROLLBACK), "rollback") == 0);
    return 0;
}
