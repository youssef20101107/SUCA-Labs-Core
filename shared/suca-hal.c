#include "suca-hal.h"

const char *suca_hal_result_status(const SucaHalResult *result) {
    if (!result) return "unknown";
    return suca_component_status_name(result->status);
}

int suca_hal_has_verified_component(const SucaHalResult *result) {
    return result && result->status == SUCA_COMPONENT_VERIFIED;
}
