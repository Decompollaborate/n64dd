#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

s32 LeoTestUnitReady(u8* status) {
    volatile LEOCmdTestUnitReady cmdBlock;

    if (!__leoActive) {
        return -1;
    }

    if ((HW_REG(PI_STATUS_REG, u32) & 1) != 0) {
        return 8;
    }

    cmdBlock.header.command = 3;
    cmdBlock.header.reserve1 = 0;
    cmdBlock.header.control = 0;
    cmdBlock.header.reserve3 = 0;

    leoCommand(&cmdBlock);

    while (cmdBlock.header.status == 8) {
    }

    *status = cmdBlock.test;
    return cmdBlock.header.sense;
}
