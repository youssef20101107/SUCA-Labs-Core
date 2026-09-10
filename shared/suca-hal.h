#ifndef SUCA_HAL_H
#define SUCA_HAL_H

#include "suca-device-profile.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    SucaComponentStatus status;
    int value;
    const char *detail;
} SucaHalResult;

typedef struct {
    SucaHalResult (*display_status)(void);
    SucaHalResult (*touch_status)(void);
    SucaHalResult (*power_status)(void);
    SucaHalResult (*audio_status)(void);
    SucaHalResult (*camera_status)(void);
    SucaHalResult (*modem_status)(void);
    SucaHalResult (*sensors_status)(void);
} SucaHalOps;

const char *suca_hal_result_status(const SucaHalResult *result);
int suca_hal_has_verified_component(const SucaHalResult *result);

#ifdef __cplusplus
}

#endif

#endif
