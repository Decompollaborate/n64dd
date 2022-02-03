#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

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

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/leointerrupt.s")

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
void leosetup_BM();
//

extern u32 LEOasic_bm_ctl_shadow;
extern u16 LEOrw_flags;

#ifdef NON_MATCHING
// weird access to LEOrw_flags
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
#else
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/leosetup_BM.s")
#endif

// static
u32 leochk_err_reg();
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/leochk_err_reg.s")
