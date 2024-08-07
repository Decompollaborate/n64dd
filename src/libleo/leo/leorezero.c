#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

void leoRezero(void) {
    u8 sense_code;
    u8 retry_cntr = 8;

    do {
        sense_code = leoRecal_w();

        if (sense_code == LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION) {
            LEOtgt_param.cylinder = 0;
            LEOtgt_param.head = 0;
            LEOtgt_param.zone = 0;
            LEOcur_command->header.status = LEO_STATUS_GOOD;
            return;
        }

        if (leoChk_err_retry(sense_code) != 0) {
            break;
        }
    } while (retry_cntr--);

    LEOcur_command->header.sense = sense_code;
    LEOcur_command->header.status = LEO_STATUS_CHECK_CONDITION;
    return;
}
