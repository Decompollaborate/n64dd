#include "n64dd.h"
#include "n64dd_functions.h"

extern LEOCmd* B_801E5E78;

// u16 leoLba_to_phys(u32 lba);
u16 func_801CE340(u32 lba);
// u8 leoSeek_w();
u8 func_801CCA20();
// u32 leoChk_err_retry(u32 sense);
u32 func_801CCAB0(u32 sense);

// void leoSeek(void);
void func_801D2D90(void) {
    u32 tgt_tk;
    u8 sense_code;
    u8 retry_cntr = 20;

    if (B_801E5E78->data.seek.lba >= 0x10C4) {
        do {
            B_801E5E78->header.sense = 0x20;
            B_801E5E78->header.status = 2;
        } while (0);
    } else {
        tgt_tk = B_801E5E78->data.seek.lba + 0x18;
        func_801CE340(tgt_tk);

        while (true) {
            sense_code = func_801CCA20();
            if (sense_code == 0) {
                B_801E5E78->header.status = 0;
                break;
            }

            if ((func_801CCAB0(sense_code) == 0) && (retry_cntr--)) {
                continue;
            } else {
                do {
                    B_801E5E78->header.sense = sense_code;
                    B_801E5E78->header.status = 2;
                } while (0);
                break;
            }
        }
    }
}