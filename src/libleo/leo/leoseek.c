#include "n64dd.h"
#include "n64dd_functions.h"

void leoSeek(void) {
    u32 tgt_tk;
    u8 sense_code;
    u8 retry_cntr = 20;

    if (LEOcur_command->data.seek.lba > LEO_LBA_MAX) {
        do {
            LEOcur_command->header.sense = LEO_SENSE_LBA_OUT_OF_RANGE;
            LEOcur_command->header.status = LEO_STATUS_CHECK_CONDITION;
        } while (0);
    } else {
        tgt_tk = LEOcur_command->data.seek.lba + 0x18;
        leoLba_to_phys(tgt_tk);

        while (true) {
            sense_code = leoSeek_w();
            if (sense_code == LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION) {
                LEOcur_command->header.status = LEO_STATUS_GOOD;
                break;
            }

            if ((leoChk_err_retry(sense_code) == 0) && (retry_cntr--)) {
                continue;
            } else {
                do {
                    LEOcur_command->header.sense = sense_code;
                    LEOcur_command->header.status = LEO_SENSE_DIAGNOSTIC_FAILURE;
                } while (0);
                break;
            }
        }
    }
}