#ifndef SUCA_DEVICE_PROFILE_H
#define SUCA_DEVICE_PROFILE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SUCA_SUPPORT_BOOT_ONLY = 0,
    SUCA_SUPPORT_BASIC_UI,
    SUCA_SUPPORT_USABLE,
    SUCA_SUPPORT_HARDWARE,
    SUCA_SUPPORT_DAILY_DRIVER
} SucaSupportLevel;

typedef enum {
    SUCA_COMPONENT_UNKNOWN = 0,
    SUCA_COMPONENT_VERIFIED,
    SUCA_COMPONENT_NEEDS_VALIDATION,
    SUCA_COMPONENT_UNAVAILABLE
} SucaComponentStatus;

typedef struct {
    const char *profile_id;
    const char *model;
    const char *architecture;
    const char *soc_family;
    SucaSupportLevel support_level;
    SucaComponentStatus display;
    SucaComponentStatus touch;
    SucaComponentStatus power;
    SucaComponentStatus audio;
    SucaComponentStatus camera;
    SucaComponentStatus modem;
    SucaComponentStatus sensors;
} SucaDeviceProfile;

const char *suca_support_level_name(SucaSupportLevel level);
const char *suca_component_status_name(SucaComponentStatus status);
int suca_device_profile_is_ready_for(SucaSupportLevel requested,
                                      const SucaDeviceProfile *profile);

#ifdef __cplusplus
}
#endif

#endif
