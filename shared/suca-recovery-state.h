#ifndef SUCA_RECOVERY_STATE_H
#define SUCA_RECOVERY_STATE_H

typedef enum {
    SUCA_RECOVERY_IDLE = 0,
    SUCA_RECOVERY_INSPECTING,
    SUCA_RECOVERY_VERIFYING_BACKUP,
    SUCA_RECOVERY_RESTORING,
    SUCA_RECOVERY_ROLLBACK_PENDING,
    SUCA_RECOVERY_COMPLETED,
    SUCA_RECOVERY_FAILED,
    SUCA_RECOVERY_REQUIRES_USER_ACTION
} SucaRecoveryState;

typedef struct {
    SucaRecoveryState state;
    int original_preserved;
    int backup_verified;
} SucaRecoveryContext;

const char *suca_recovery_state_name(SucaRecoveryState state);
int suca_recovery_transition(SucaRecoveryContext *context, SucaRecoveryState next);
int suca_recovery_can_restore(const SucaRecoveryContext *context);

#endif
