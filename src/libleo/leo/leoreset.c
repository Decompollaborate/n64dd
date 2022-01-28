#include "n64dd.h"
#include "n64dd_functions.h"

extern OSMesgQueue B_801E5DE8;
// OSMesgQueue LEOcommand_que;

u8 func_801CC380(void);

void leoClr_queue(void);
//{
//    OSMesg clr_cmd;
//}

void func_801CE7E0(void) {
    OSMesg clr_cmd;

    while (osRecvMesg(&B_801E5DE8, &clr_cmd, OS_MESG_NOBLOCK) == 0) {
        ((LEOCmd*)clr_cmd)->header.sense = LEO_SENSE_COMMAND_TERMINATED;
        ((LEOCmd*)clr_cmd)->header.status = LEO_STATUS_CHECK_CONDITION;
        if (((LEOCmd*)clr_cmd)->header.control & LEO_CONTROL_POST) {
            osSendMesg(((LEOCmd*)clr_cmd)->header.post, (OSMesg)LEO_SENSE_COMMAND_TERMINATED, OS_MESG_BLOCK);
        }
    }
}


void func_801CE888(void) {
    u32 sense_code;

    sense_code = func_801CC380();
    if ((sense_code == LEO_SENSE_COMMAND_PHASE_ERROR) || (sense_code == LEO_SENSE_DEVICE_COMMUNICATION_FAILURE) ||
        (sense_code == LEO_SENSE_POWERONRESET_DEVICERESET_OCCURED)) {
        LEOcur_command->header.sense = sense_code;
        LEOcur_command->header.status = LEO_STATUS_CHECK_CONDITION;
    } else {
        LEOcur_command->header.sense = LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION;
        LEOcur_command->header.status = LEO_STATUS_GOOD;
    }
}
