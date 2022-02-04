#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

extern vu16 LEOrw_flags;

// extern ? LEOC2_Syndrome;
extern OSIoMesg LEOPiDmaParam;
// extern ? LEOc2_param;
extern OSMesgQueue LEOc2ctrl_que;
extern u8* LEOc2ctrl_que_buf;

u32 read_write_track();

#if 0
void leointerrupt(void* arg);
//{
//    u32 result;
//    u32 tg_blocks;
//    Label: complete @ 364;
//}

// static
u32 read_write_track();
//{
//    u32 message;
//    u32 block;
//    u32 retry_cntr;
//    block_param_form block_param;
//    {
//        u16 bnum;
//    }
//    {
//        u8* temp;
//        u32 c2datasize;
//    }
//    Label: track_end @ 2248;
//    Label: do_retry @ 2276;
//}

// static
u32 leoChk_mecha_int();
//{
//    u32 stat;
//    u32 index_stat;
//}

// static
void leosetup_BM();
//{
//}

// static
u32 leochk_err_reg();
//{
//    u32 sense;
//    u32 index_status;
//}
#endif

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/leointerrupt.s")

void leointerrupt(void* arg) {
    u32 result;
    u32 tg_blocks;

    osCreateMesgQueue(&LEOc2ctrl_que, (OSMesg)&LEOc2ctrl_que_buf, 1);

    while (true) {
        osStopThread(&LEOinterruptThread);
        tg_blocks = LEOcur_command->data.readWrite.transferBlks;
        LEOwrite_pointer = LEOcur_command->data.readWrite.buffPtr;

        do {
            leoLba_to_phys(LEOtgt_param.lba);
            if (LEOrw_flags & 0x8000) {
                result = leoSeek_i(1);
            } else {
                result = leoSeek_i(0);
            }

            if (result != 0) {
                goto complete;
            }

            if (LEOrw_flags & 0x2000) {
                LEOtgt_param.rdwr_blocks = 1;
            } else if (LEOtgt_param.rdwr_blocks > tg_blocks) {
                LEOtgt_param.rdwr_blocks = tg_blocks;
            }
            LEOtgt_param.lba += LEOtgt_param.rdwr_blocks;
            tg_blocks -= LEOtgt_param.rdwr_blocks;
            result = read_write_track();
            if (result != 0) {
                goto complete;
            }

            LEOcur_command->data.readWrite.rwBytes = LEOwrite_pointer - (u8*)LEOcur_command->data.readWrite.buffPtr;
        } while (tg_blocks != 0);
        result = 0x90000; // Inaccessible?

    complete:;

        osSendMesg(&LEOcontrol_que, result, 1);
    }
}

// static
u32 read_write_track();
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/read_write_track.s")

// static
u32 leoChk_mecha_int(void) {
    u32 stat = leoWait_mecha_cmd_done(0x10001);
    u32 index_stat;

    if (stat == 0) {
        osEPiReadIo(LEOPiInfo, 0x0500050C, &index_stat);
        if ((index_stat & 0x60000000) != 0x60000000) {
            stat = 0x18;
        }
    }
    return stat;
}

// static
void leosetup_BM(void) {
    osEPiWriteIo(LEOPiInfo, 0x05000510, LEOasic_bm_ctl_shadow | 0x10000000);
    osEPiWriteIo(LEOPiInfo, 0x05000510, LEOasic_bm_ctl_shadow);

    if (LEOtgt_param.start_block != 0) {
        LEOasic_bm_ctl_shadow = 0x5A0000;
    } else {
        LEOasic_bm_ctl_shadow = 0;
    }

    if (!(LEOrw_flags & 0x8000)) {
        LEOasic_bm_ctl_shadow |= 0x40000000;
    }

    if (LEOtgt_param.rdwr_blocks == 2) {
        LEOasic_bm_ctl_shadow |= 0x02000000;
    }

    osEPiWriteIo(LEOPiInfo, 0x05000510, LEOasic_bm_ctl_shadow);
}

// static
u32 leochk_err_reg(void) {
    u32 sense;
    u32 index_status;

    osEPiReadIo(LEOPiInfo, 0x05000514, &sense);
    osEPiWriteIo(LEOPiInfo, 0x05000510, LEOasic_bm_ctl_shadow | 0x10000000);
    osEPiWriteIo(LEOPiInfo, 0x05000510, LEOasic_bm_ctl_shadow);

    if (sense & 0x04000000) {
        return 0x31;
    }

    if (sense & 0x10000000) {
        return 4;
    }

    if (sense & (0x40000000 | 0x2000000)) {
        if (LEOrw_flags & 0x8000) {
            return 0x16;
        }
        return 0x17;
    }

    if (sense & 0x80000000) {
        return 0x18;
    }

    osEPiReadIo(LEOPiInfo, 0x0500050C, &index_status);
    if ((index_status & 0x60000000) == 0x60000000) {
        return 0x19;
    }

    return 0x18;
}
