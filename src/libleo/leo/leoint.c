#include "n64dd.h"
#include "n64dd_functions.h"

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

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/read_write_track.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/leoChk_mecha_int.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/leosetup_BM.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoint/leochk_err_reg.s")
