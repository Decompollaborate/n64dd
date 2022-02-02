#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

void leoTest_unit_rdy(void) {
    ((LEOCmdTestUnitReady*)LEOcur_command)->test = leoChk_cur_drvmode();
    LEOcur_command->header.sense = LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION;
    LEOcur_command->header.status = LEO_STATUS_GOOD;
}
