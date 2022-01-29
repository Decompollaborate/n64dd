#include "n64dd.h"
#include "n64dd_functions.h"

extern OSPiHandle* LEOPiInfo;

void leoInquiry(void) {
    u32 sp1C;

    osEPiReadIo(LEOPiInfo, 0x05000540, &sp1C);
    if (func_801CC820(0x1B0000, 0) == 0) {
        u32 sp18;

        osEPiReadIo(LEOPiInfo, 0x05000500, &sp18);
        if (sp18 & 0x10000) {
            sp1C |= 0x100000;
        }
    }

    ((LEOCmdInquiry*)LEOcur_command)->devType = 0;
    ((LEOCmdInquiry*)LEOcur_command)->version = sp1C >> 0x10;
    ((LEOCmdInquiry*)LEOcur_command)->devNum = 1;
    ((LEOCmdInquiry*)LEOcur_command)->leoBiosVer = 0;
    LEOcur_command->header.status = LEO_STATUS_GOOD;
}
