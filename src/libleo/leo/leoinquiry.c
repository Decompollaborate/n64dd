#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

void leoInquiry(void) {
    u32 asic_id;
    u32 asic_data;

    osEPiReadIo(LEOPiInfo, 0x05000540, &asic_id);
    if (leoSend_asic_cmd_w(0x1B0000, 0) == 0) {
        osEPiReadIo(LEOPiInfo, 0x05000500, &asic_data);
        if (asic_data & 0x10000) {
            asic_id |= 0x100000;
        }
    }

    ((LEOCmdInquiry*)LEOcur_command)->devType = 0;
    ((LEOCmdInquiry*)LEOcur_command)->version = asic_id >> 0x10;
    ((LEOCmdInquiry*)LEOcur_command)->devNum = 1;
    ((LEOCmdInquiry*)LEOcur_command)->leoBiosVer = 0;
    LEOcur_command->header.status = LEO_STATUS_GOOD;
}
