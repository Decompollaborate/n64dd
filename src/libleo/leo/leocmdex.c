#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

extern vu16 LEOrw_flags;

static void (*cmd_tbl[16])(void) = {
    NULL,
    leoClr_queue,
    leoInquiry,
    leoTest_unit_rdy,
    leoRezero,
    leoRead,
    leoWrite,
    leoSeek,
    leoStart_stop,
    leoRd_capacity,
    leoTranslate,
    leoMode_sel,
    leoReadDiskId,
    leoReadTimer,
    leoSetTimer,
    leoClr_reset,
};

static LEOCmdRead system_read_cmd = {
    {LEO_COMMAND_READ, 0, 0, 0, 0, 0, 0, 0, 0},
    12, 1, 0, 0,
};

static const u8 system_lba[8] = { 0, 1, 8, 9, 0, 0, 0, 0 };

OSPiHandle* LEOPiInfo;
OSIoMesg LEOPiDmaParam;
s32 currentCommand;

#if 0
void leomain(void* arg);
//{
//    u32 cur_status;
//    u32 sense_code;
//    u8 disktype_bak;
//    Label: invalid_disktype @ 1252;
//    Label: post_exe @ 1340;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leocmdex/leomain.s")

u8 leoRead_system_area(void) {
    LEOCmdRead dummy_cmd;
    void* backup_pointer;
    u32 retry_cntr;
    s32 read_mode;

    backup_pointer = LEOcur_command;
    LEOcur_command = (LEOCmd*)&dummy_cmd;
    read_mode = 0;
    retry_cntr = 0;

    while (1) {
        LEOdisk_type = 0;
        // For lba_to_phys to avoid dealing with alternative tracks on the disk
        LEO_sys_data.param.defect_num[0] = 0;
        LEOrw_flags = 0x3000;
        dummy_cmd = system_read_cmd;
        dummy_cmd.buffPtr = &LEO_sys_data;

        if (read_mode == 0) {
            // read System LBA 12 (+0, this is an offset value for leoRead_common)
            // see system_read_cmd premade struct
            leoRead_common(0);
            switch (dummy_cmd.header.sense) {
                case LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION:
                    do {
                        // if expecting a retail disk, LBA 12 is expected to do a read error, if not then freeze
                    } while (LEO_country_code != 0);
                    retry_cntr = 0;
                    read_mode--;
                    continue;
                case LEO_SENSE_UNRECOVERED_READ_ERROR:
                    do {
                        // if expecting a development disk, LBA 12 is expected to read correctly, if not then freeze
                    } while (LEO_country_code == 0);
                    retry_cntr = 0;
                    read_mode--;
                    continue;
            }
        } else {
            // read System LBA 0,1,8,9 (or 2,3,10,11 for dev)
            dummy_cmd.lba = system_lba[retry_cntr & 3];
            if (LEO_country_code == 0) {
                dummy_cmd.lba += 2;
            }
            leoRead_common(0);
            if (dummy_cmd.header.status == LEO_STATUS_GOOD) {
                do {
                    // if disk country and set country code in libleo mismatch, then freeze
                } while (LEO_sys_data.param.country != LEO_country_code);
                goto sys_read_end;
            }
        }

system_retry:
        if (leoChk_err_retry(dummy_cmd.header.sense) != LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION) {
            break;
        }
        if (retry_cntr++ >= 0x40U) {
            break;
        }
        if ((retry_cntr & 7) == 0) {
            // Recalibrate drive every 8th tries
            if ((dummy_cmd.header.sense = leoSend_asic_cmd_w(0x30001, 0)) ==
                LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION) {
                continue;
            }
            goto system_retry;
        }
    }

sys_read_end:
    LEOcur_command = backup_pointer;
    LEOcur_command->header.sense = dummy_cmd.header.sense;
    return LEOcur_command->header.sense;
}
