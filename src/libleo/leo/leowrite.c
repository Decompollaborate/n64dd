#include "n64dd.h"
#include "n64dd_functions.h"

extern OSMesgQueue LEOcontrol_que;
extern OSThread LEOinterruptThread;
extern u16 LEOrw_flags; // N.B. NOT volatile in this file!
extern LEOCmd *LEOcur_command;
extern u8 LEOdisk_type;


// Different from libleo.a:
// void leoWrite();
// //{
// //    u32 message;
// //    u32 start_lba;
// //    u32 xfer_blk;
// //    u32 write_bytes;
// //    u8 retry_count;
// //    Label: invalid_lba @ 132;
// //}
void leoWrite(void) {
    u32 message;
    u32 start_lba;
    u32 xfer_blk;
    u32 write_bytes;
    // u8 retry_count;

    start_lba = LEOcur_command->data.readWrite.lba;
    xfer_blk = LEOcur_command->data.readWrite.transferBlks;
    if (((start_lba | xfer_blk) >> 0x10) != 0) {
        goto invalid_lba;
    }
    start_lba += 0x18;
    // temp = start_lba + xfer_blk; // ?
    if ((start_lba >= 0x10DC) || (start_lba + xfer_blk > 0x10DC)) {
        invalid_lba:
        LEOcur_command->header.sense = LEO_SENSE_LBA_OUT_OF_RANGE;
        LEOcur_command->header.status = LEO_STATUS_CHECK_CONDITION;
        return;
    }

    if (start_lba < LEORAM_START_LBA[LEOdisk_type]) {
        LEOcur_command->header.sense = LEO_SENSE_WRITE_PROTECT_ERROR;
        LEOcur_command->header.status = LEO_STATUS_CHECK_CONDITION;
        return;
    }

    if (xfer_blk == 0) {
        LEOcur_command->header.sense = LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION;
        LEOcur_command->header.status = LEO_STATUS_GOOD;
        return;
    }

    LEOrw_flags = 0x8000;
    LEOtgt_param.lba = start_lba;
    osStartThread(&LEOinterruptThread);
    osRecvMesg(&LEOcontrol_que, (OSMesg*)&message, OS_MESG_BLOCK);

    if (message != 0x90000) {
        LEOcur_command->header.sense = message;
        LEOcur_command->header.status = LEO_STATUS_CHECK_CONDITION;
        return;
    }

    LEOcur_command->header.sense = LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION;
    LEOcur_command->header.status = LEO_STATUS_GOOD;
}