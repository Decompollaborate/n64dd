#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"
#include "ultra64/internal.h"

extern OSThread* __osRunQueue;
extern OSHWIntr __OSGlobalIntMask;
void __osLeoAbnormalResume(void);
void __osLeoResume(void);

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


// static
void __osLeoAbnormalResume(void) {
    __OSTranxInfo* info;
    u32 pi_stat;

    info = &__osDiskHandle->transferInfo;
    pi_stat = HW_REG(PI_STATUS_REG, u32);
    while (pi_stat & 3) {
        pi_stat = HW_REG(PI_STATUS_REG, u32);
    }

    HW_REG(0x5000510, u32) = info->bmCtlShadow | 0x10000000;
    pi_stat = HW_REG(PI_STATUS_REG, u32);
    while (pi_stat & 3) {
        pi_stat = HW_REG(PI_STATUS_REG, u32);
    }

    HW_REG(0x5000510, u32) = info->bmCtlShadow;
    __osLeoResume();
    HW_REG(PI_STATUS_REG, u32) = 2;
    __OSGlobalIntMask |= 0x100401;
}

// static
void __osLeoResume(void) {
    __OSEventState* es;
    OSMesgQueue* mq;
    s32 last;

    es = &__osEventStateTab[8];
    mq = es->queue;
    if ((mq == 0) || (mq->validCount >= mq->msgCount)) {
        return;
    }
    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = es->msg;
    mq->validCount++;
    if (mq->mtqueue->next != NULL) {
        __osEnqueueThread(&__osRunQueue, __osPopThread(&mq->mtqueue));
    }
}