#include "n64dd.h"
#include "n64dd_functions.h"

extern LEOCmd* LEOcur_command;

void leoSeek(void) {
    u32 tgt_tk;
    u8 sense_code;
    u8 retry_cntr = 20;

    if (LEOcur_command->data.seek.lba >= 0x10C4) {
        do {
            LEOcur_command->header.sense = 0x20;
            LEOcur_command->header.status = 2;
        } while (0);
    } else {
        tgt_tk = LEOcur_command->data.seek.lba + 0x18;
        leoLba_to_phys(tgt_tk);

        while (true) {
            sense_code = leoSeek_w();
            if (sense_code == 0) {
                LEOcur_command->header.status = 0;
                break;
            }

            if ((leoChk_err_retry(sense_code) == 0) && (retry_cntr--)) {
                continue;
            } else {
                do {
                    LEOcur_command->header.sense = sense_code;
                    LEOcur_command->header.status = 2;
                } while (0);
                break;
            }
        }
    }
}