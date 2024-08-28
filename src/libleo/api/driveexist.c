#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

u32 LeoDriveExist(void) {
    u32 data;
    u32 saveMask;
    u32 stat;
    u32 latency;
    u32 pulse;
    u32 pageSize;
    u32 relDuration;

    __osPiGetAccess();

    while ((stat = HW_REG(PI_STATUS_REG, u32)) & (PI_STATUS_BUSY | PI_STATUS_IOBUSY)) {}

    latency = HW_REG(PI_BSD_DOM1_LAT_REG, u32);
    pageSize = HW_REG(PI_BSD_DOM1_PGS_REG, u32);
    relDuration = HW_REG(PI_BSD_DOM1_RLS_REG, u32);
    pulse = HW_REG(PI_BSD_DOM1_PWD_REG, u32);

    HW_REG(PI_BSD_DOM1_LAT_REG, u32) = 0xFF;
    HW_REG(PI_BSD_DOM1_PGS_REG, u32) = 0;
    HW_REG(PI_BSD_DOM1_RLS_REG, u32) = 3;
    HW_REG(PI_BSD_DOM1_PWD_REG, u32) = 0xFF;

    data = HW_REG(0x06001010, u32); // Something in the n64dd address space?

    HW_REG(PI_BSD_DOM1_LAT_REG, u32) = latency;
    HW_REG(PI_BSD_DOM1_PGS_REG, u32) = pageSize;
    HW_REG(PI_BSD_DOM1_RLS_REG, u32) = relDuration;
    HW_REG(PI_BSD_DOM1_PWD_REG, u32) = pulse;

    __osPiRelAccess();
    if (data == 0x2129FFF8) {
        return true;
    }
    return false;
}
