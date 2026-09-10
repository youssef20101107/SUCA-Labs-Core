#ifndef SUCA_UPDATE_STATE_H
#define SUCA_UPDATE_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SUCA_UPDATE_IDLE = 0,
    SUCA_UPDATE_CHECKING,
    SUCA_UPDATE_DOWNLOADING,
    SUCA_UPDATE_VERIFYING,
    SUCA_UPDATE_INSTALLING_INACTIVE,
    SUCA_UPDATE_REBOOT_PENDING,
    SUCA_UPDATE_HEALTH_CHECK,
    SUCA_UPDATE_COMMITTED,
    SUCA_UPDATE_ROLLBACK
} SucaUpdateState;

typedef struct {
    char active_slot;
    char target_slot;
    unsigned int boot_attempts;
    unsigned int boot_attempt_limit;
    SucaUpdateState state;
} SucaUpdateContext;

const char *suca_update_state_name(SucaUpdateState state);
int suca_update_transition(SucaUpdateContext *context, SucaUpdateState next);
int suca_update_mark_health(SucaUpdateContext *context, int healthy);
int suca_update_can_install(const SucaUpdateContext *context);

#ifdef __cplusplus
}

#endif

#endif
