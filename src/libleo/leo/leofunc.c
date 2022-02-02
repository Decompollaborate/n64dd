#include "n64dd.h"
#include "n64dd_functions.h"

#if 0
static OSMesgQueue LEOpost_que;

static OSMesg LEOpost_que_buf;

void leoInitialize(OSPri compri, OSPri intpri, OSMesg* command_que_buf, u32 cmd_buff_size);
//{
//    u32 savedMask;
//    OSPri oldPri;
//    OSPri myPri;
//    OSPri pri;
//}

void leoCommand(void* cmd_blk_addr);
//{
//    Label: cmd_queing @ 864;
//}

static const u8 zero[1];

void LeoReset();
//{
//}

s32 __leoSetReset();
//{
//}

s32 LeoResetClear();
//{
//    LEOCmdHeader resetclear;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leofunc/R_801D93B0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leofunc/leoInitialize.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leofunc/leoCommand.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leofunc/LeoReset.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leofunc/__leoSetReset.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leofunc/LeoResetClear.s")
