#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

u32 LeoDriveExist(void) {
    register u32 sp1C;
    register s32 status;
    register u32 lastLatency;
    register u32 lastPageSize;
    register u32 lastRelDuration;
    register u32 lastPulse;

    __osPiGetAccess();

    while ((status = HW_REG(PI_STATUS_REG, u32)) & (PI_STATUS_BUSY | PI_STATUS_IOBUSY)) {}

    lastLatency = HW_REG(PI_BSD_DOM1_LAT_REG, u32);
    lastPageSize = HW_REG(PI_BSD_DOM1_PGS_REG, u32);
    lastRelDuration = HW_REG(PI_BSD_DOM1_RLS_REG, u32);
    lastPulse = HW_REG(PI_BSD_DOM1_PWD_REG, u32);

    HW_REG(PI_BSD_DOM1_LAT_REG, u32) = 0xFF;
    HW_REG(PI_BSD_DOM1_PGS_REG, u32) = 0;
    HW_REG(PI_BSD_DOM1_RLS_REG, u32) = 3;
    HW_REG(PI_BSD_DOM1_PWD_REG, u32) = 0xFF;

    sp1C = HW_REG(0x06001010, u32); // Something in the n64dd address space?

    HW_REG(PI_BSD_DOM1_LAT_REG, u32) = lastLatency;
    HW_REG(PI_BSD_DOM1_PGS_REG, u32) = lastPageSize;
    HW_REG(PI_BSD_DOM1_RLS_REG, u32) = lastRelDuration;
    HW_REG(PI_BSD_DOM1_PWD_REG, u32) = lastPulse;

    __osPiRelAccess();
    if (sp1C == 0x2129FFF8) {
        return 1;
    }
    return 0;
}
