#include "n64dd.h"
#include "n64dd_functions.h"

#if 0
static u32 mseq_tbl[16];

static const u32 rd_mseq_code[16];

static const u32 wt_mseq_code[16];

void leoSet_mseq(u16 rwmode);
//{
//    u32* tbl;
//    u32 sct_byte_x;
//    u32 sct_byte_u;
//    u8 i;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomseq_tbl/rd_mseq_code.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomseq_tbl/wt_mseq_code.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomseq_tbl/leoSet_mseq.s")
