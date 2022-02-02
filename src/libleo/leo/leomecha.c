#include "n64dd.h"
#include "n64dd_functions.h"

#if 0
static u32 asic_cur_status;

static u32 unit_atten;

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

u8 leoSend_asic_cmd_w_nochkDiskChange(u32 asic_cmd, u32 asic_data);
//{
//    u8 status;
//    u32 done_stat;
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
//    u32 done_mesg;
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

u32 leoChkUnit_atten();
//{
//}

u32 leoRetUnit_atten();
//{
//}

void leoClrUA_RESET();
//{
//}

void leoClrUA_MEDIUM_CHANGED();
//{
//}

void leoSetUA_MEDIUM_CHANGED();
//{
//}

void leoInitUnit_atten();
//{
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoAnalize_asic_status.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoChk_asic_ready.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoChk_done_status.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSend_asic_cmd_i.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoWait_mecha_cmd_done.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSend_asic_cmd_w.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSend_asic_cmd_w_nochkDiskChange.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoDetect_index_w.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoRecal_i.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoRecal_w.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSeek_i.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSeek_w.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoRecv_event_mesg.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoChk_err_retry.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoChk_cur_drvmode.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoDrive_reset.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoChkUnit_atten.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoRetUnit_atten.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoClrUA_RESET.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoClrUA_MEDIUM_CHANGED.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoSetUA_MEDIUM_CHANGED.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leomecha/leoInitUnit_atten.s")
