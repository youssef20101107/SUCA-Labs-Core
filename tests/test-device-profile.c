#include <assert.h>
#include <string.h>
#include "../shared/suca-device-profile.h"

int main(void) {
    SucaDeviceProfile profile = {
        .profile_id = "test",
        .model = "test-device",
        .architecture = "aarch64",
        .soc_family = "generic",
        .support_level = SUCA_SUPPORT_BASIC_UI,
        .display = SUCA_COMPONENT_VERIFIED,
        .touch = SUCA_COMPONENT_VERIFIED,
        .power = SUCA_COMPONENT_NEEDS_VALIDATION,
        .audio = SUCA_COMPONENT_NEEDS_VALIDATION,
        .camera = SUCA_COMPONENT_NEEDS_VALIDATION,
        .modem = SUCA_COMPONENT_NEEDS_VALIDATION,
        .sensors = SUCA_COMPONENT_NEEDS_VALIDATION,
    };

    assert(strcmp(suca_support_level_name(SUCA_SUPPORT_BASIC_UI), "basic-ui") == 0);
    assert(suca_device_profile_is_ready_for(SUCA_SUPPORT_BASIC_UI, &profile));
    assert(!suca_device_profile_is_ready_for(SUCA_SUPPORT_USABLE, &profile));
    assert(!suca_device_profile_is_ready_for(SUCA_SUPPORT_HARDWARE, &profile));
    assert(!suca_device_profile_is_ready_for(SUCA_SUPPORT_DAILY_DRIVER, &profile));
    return 0;
}
