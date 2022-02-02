#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#if 0
s32 LeoCACreateLeoManager(OSPri comPri, OSPri intPri, OSMesg* cmdBuf, s32 cmdMsgCnt);
//{
//    OSPiHandle* driveRomHandle;
//    OSPiHandle* leoDiskHandle;
//    volatile LEOCmdInquiry cmdBlockInq;
//    volatile LEOCmd cmdBlockID;
//    LEODiskID thisID;
//    u32 stat;
//    u32 data;
//    {
//        volatile s32 dummy;
//    }
//    {
//        volatile u32 dummy;
//    }
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/cacreateleomanager/LeoCACreateLeoManager.s")
