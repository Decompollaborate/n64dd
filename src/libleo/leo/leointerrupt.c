#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#if 0
s32 __osLeoInterrupt();
//{
//    u32 stat;
//    volatile u32 pi_stat;
//    u32 bm_stat;
//    __OSTranxInfo* info;
//    __OSBlockInfo* blockInfo;
//    {
//        int errNum;
//    }
//    {
//        __OSBlockInfo* bptr;
//    }
//}

// static
void __osLeoAbnormalResume();
//{
//    __OSTranxInfo* info;
//    u32 pi_stat;
//}

// static
void __osLeoResume();
//{
//    __OSEventState* es;
//    OSMesgQueue* mq;
//    s32 last;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leointerrupt/__osLeoInterrupt.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leointerrupt/__osLeoAbnormalResume.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leointerrupt/__osLeoResume.s")
