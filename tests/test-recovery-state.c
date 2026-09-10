#include <assert.h>
#include <string.h>
#include "../shared/suca-recovery-state.h"

int main(void) {
    SucaRecoveryContext context = {
        .state = SUCA_RECOVERY_IDLE,
        .original_preserved = 0,
        .backup_verified = 0,
    };

    assert(!suca_recovery_can_restore(&context));
    assert(!suca_recovery_transition(&context, SUCA_RECOVERY_RESTORING));
    context.original_preserved = 1;
    context.backup_verified = 1;
    assert(suca_recovery_can_restore(&context));
    assert(suca_recovery_transition(&context, SUCA_RECOVERY_RESTORING));
    assert(strcmp(suca_recovery_state_name(context.state), "restoring") == 0);
    return 0;
}
