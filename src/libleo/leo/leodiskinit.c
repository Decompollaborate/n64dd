#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

extern OSPiHandle* __osPiTable;

OSPiHandle __LeoDiskHandle;
OSPiHandle* __osDiskHandle;

OSPiHandle* osLeoDiskInit(void) {
    u32 saveMask;

    __LeoDiskHandle.type = 2;
    __LeoDiskHandle.baseAddress = (u32)OS_PHYSICAL_TO_K1(0x05000000);
    __LeoDiskHandle.latency = 3;
    __LeoDiskHandle.pulse = 6;
    __LeoDiskHandle.pageSize = 6;
    __LeoDiskHandle.relDuration = 2;
    __LeoDiskHandle.domain = 1;
    __LeoDiskHandle.speed = 0;

    bzero(&__LeoDiskHandle.transferInfo, sizeof(__OSTranxInfo));
    saveMask = __osDisableInt();

    __LeoDiskHandle.next = __osPiTable;
    __osPiTable = &__LeoDiskHandle;
    __osDiskHandle = &__LeoDiskHandle;

    __osRestoreInt(saveMask);

    return &__LeoDiskHandle;
}
