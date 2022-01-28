#include "n64dd.h"
#include "n64dd_functions.h"

// s8 leoChk_cur_drvmode();                                 /* extern */
s8 func_801CCBC0();                                 /* extern */

// leoTest_unit_rdy
void leoTest_unit_rdy(void) {
    ((LEOCmdTestUnitReady*)LEOcur_command)->test = func_801CCBC0();
    LEOcur_command->header.sense = LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION;
    LEOcur_command->header.status = LEO_STATUS_GOOD;
}
