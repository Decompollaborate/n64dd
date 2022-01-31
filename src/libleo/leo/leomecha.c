#include "n64dd.h"
#include "n64dd_functions.h"

#if 0
static u32 asic_cur_status;

u8 leoAnalize_asic_status();
//{
//    u32 curr_stat;
//}

u8 leoChk_asic_ready(u32 asic_cmd);
//{
//    u32 sense_code;
//}

u8 leoChk_done_status(u32 asic_cmd);
//{
//    u32 asic_data;
//    u32 code;
//}

u8 leoSend_asic_cmd_i(u32 asic_cmd, u32 asic_data);
//{
//    u8 status;
//}

u8 leoWait_mecha_cmd_done(u32 asic_cmd);
//{
//    u32 done_stat;
//}

u8 leoSend_asic_cmd_w(u32 asic_cmd, u32 asic_data);
//{
//    u32 wstatus;
//}

u8 leoDetect_index_w();
//{
//}

u8 leoRecal_i();
//{
//}

u8 leoRecal_w();
//{
//}

u8 leoSeek_i(u16 rwmode);
//{
//    u32 tgt_tk;
//}

u8 leoSeek_w();
//{
//    u8 sksense;
//}

u8 leoRecv_event_mesg(s32 control);
//{
//    u32 message;
//}

u32 leoChk_err_retry(u32 sense);
//{
//}

u8 leoChk_cur_drvmode();
//{
//    u8 devstat;
//}

void leoDrive_reset();
//{
//}
#endif

// leoAnalize_asic_status
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC380.s")

// leoChk_asic_ready
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC48C.s")

// leoChk_done_status
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC574.s")

// leoSend_asic_cmd_i
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC728.s")

// leoWait_mecha_cmd_done
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC7D0.s")

// Looks more like leoSend_asic_cmd_w ?
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC820.s")

// ?
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSend_asic_cmd_w.s")

// leoDetect_index_w
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC944.s")

// leoRecal_i
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC96C.s")

// leoRecal_w
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoRecal_w.s")

// leoSeek_i
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CC9BC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSeek_w.s")

// leoRecv_event_mesg
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CCA5C.s")

// Quite different
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoChk_err_retry.s")

// leoChk_cur_drvmode
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CCBC0.s")

// leoDrive_reset
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/func_801CCC00.s")
