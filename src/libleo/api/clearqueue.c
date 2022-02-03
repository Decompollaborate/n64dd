#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

s32 LeoClearQueue(void) {
    LEOCmdClearQueue cmdBlock;

    if (!__leoActive) {
        return -1;
    }
    cmdBlock.header.command = 1;
    cmdBlock.header.reserve1 = 0;
    cmdBlock.header.control = 0;
    cmdBlock.header.reserve3 = 0;

    leoCommand(&cmdBlock);
    return 0;
}
