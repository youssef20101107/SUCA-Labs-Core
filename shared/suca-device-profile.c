#include "suca-device-profile.h"

static int status_is_verified(SucaComponentStatus status) {
    return status == SUCA_COMPONENT_VERIFIED;
}

const char *suca_support_level_name(SucaSupportLevel level) {
    switch (level) {
    case SUCA_SUPPORT_BOOT_ONLY: return "boot-only";
    case SUCA_SUPPORT_BASIC_UI: return "basic-ui";
    case SUCA_SUPPORT_USABLE: return "usable";
    case SUCA_SUPPORT_HARDWARE: return "hardware";
    case SUCA_SUPPORT_DAILY_DRIVER: return "daily-driver";
    default: return "unknown";
    }
}

const char *suca_component_status_name(SucaComponentStatus status) {
    switch (status) {
    case SUCA_COMPONENT_VERIFIED: return "verified";
    case SUCA_COMPONENT_NEEDS_VALIDATION: return "needs-device-validation";
    case SUCA_COMPONENT_UNAVAILABLE: return "unavailable";
    default: return "unknown";
    }
}

int suca_device_profile_is_ready_for(SucaSupportLevel requested,
                                      const SucaDeviceProfile *profile) {
    if (!profile) return 0;
    if (requested <= SUCA_SUPPORT_BOOT_ONLY)
        return 1;
    if (requested == SUCA_SUPPORT_BASIC_UI)
        return status_is_verified(profile->display) &&
               status_is_verified(profile->touch);
    if (requested == SUCA_SUPPORT_USABLE)
        return suca_device_profile_is_ready_for(SUCA_SUPPORT_BASIC_UI, profile) &&
               status_is_verified(profile->power) &&
               status_is_verified(profile->audio);
    if (requested == SUCA_SUPPORT_HARDWARE)
        return suca_device_profile_is_ready_for(SUCA_SUPPORT_USABLE, profile) &&
               status_is_verified(profile->camera) &&
               status_is_verified(profile->modem) &&
               status_is_verified(profile->sensors);
    if (requested == SUCA_SUPPORT_DAILY_DRIVER)
        return suca_device_profile_is_ready_for(SUCA_SUPPORT_HARDWARE, profile);
    return 0;
}
