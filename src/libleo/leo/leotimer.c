#include "n64dd.h"
#include "n64dd_functions.h"

#if 0
void leoReadTimer();
//{
//    u8* rdparam;
//    u8 data[4];
//    u8 sense_code;
//    Label: rd_timer_err1 @ 340;
//    Label: rd_timer_err2 @ 376;
//}

static const u8 ymdupper[6];

static const u8 dayupper[13];

void leoSetTimer();
//{
//    LEOCmdReadTimer rd_timer;
//    u8* p_tmp;
//    u32 year;
//    u32 month;
//    u32 temp;
//    u32 ymd;
//    u8 result;
//    Label: cmd_invalid_param @ 1028;
//    Label: cmd_err_end @ 1036;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/ymdupper.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/dayupper.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/func_801CEBA0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/func_801CEC5C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/func_801CEE94.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/func_801CF004.s")
