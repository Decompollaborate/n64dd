#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

s32 LeoSeek(LEOCmd* cmdBlock, u32 lba, OSMesgQueue* mq) {
    if (!__leoActive) {
        return -1;
    }

    cmdBlock->header.command = LEO_COMMAND_READ_DISK_ID;
    cmdBlock->header.reserve1 = 0;
    cmdBlock->header.control = 0;
    cmdBlock->header.reserve3 = 0;
    cmdBlock->data.readWrite.lba = lba;

    if (mq != NULL) {
        cmdBlock->header.control |= LEO_CONTROL_POST;
        cmdBlock->header.post = mq;
    }

    leoCommand(cmdBlock);
    return 0;
}
