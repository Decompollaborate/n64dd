#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#if 0
typedef struct {
    /* 0x0 */ u8 year;
    /* 0x1 */ u8 month;
    /* 0x2 */ u8 day;
    /* 0x3 */ u8 hour;
    /* 0x4 */ u8 minute;
    /* 0x5 */ u8 second;
} __LOCTime;

void leoReadTimer();
//{
//    u8* rdparam;
//    u8 data[4];
//    u8 sense_code;
//    __LOCTime time;
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
//    __LOCTime time;
//}

// static
u8 __locReadTimer(__LOCTime* time);
//{
//    u32 data;
//    u8 sense_code;
//}

// static
u8 __locSetTimer(__LOCTime* time);
//{
//    u32 YearMonthX10000h;
//    u32 DayHourX10000h;
//    u32 MinuteSecondX10000h;
//    u8 result;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/ymdupper.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/dayupper.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/leoReadTimer.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/leoSetTimer.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/func_801CEE94.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leotimer/func_801CF004.s")
