#ifndef LIBULTRA_FUNCTIONS_H
#define LIBULTRA_FUNCTIONS_H

#include "ultra64.h"

typedef struct StackEntry {
    /* 0x00 */ struct StackEntry* next;
    /* 0x04 */ struct StackEntry* prev;
    /* 0x08 */ u32 head;
    /* 0x0C */ u32 tail;
    /* 0x10 */ u32 initValue;
    /* 0x14 */ s32 minSpace;
    /* 0x18 */ const char* name;
} StackEntry; // size = 0x1C

typedef enum {
    STACK_STATUS_OK = 0,
    STACK_STATUS_WARNING = 1,
    STACK_STATUS_OVERFLOW = 2
} StackStatus;


// void bootproc(void);
// void osSyncPrintf(const char* fmt, ...);
// void osSyncPrintfFReg(s32 idx, f32* value);
// void osSyncPrintfFPCR(u32 value);
// void osSyncPrintfThreadContext(OSThread* t);
// void osSyncPrintfStackTrace(OSThread* t, u32 flags);
void StackCheck_Init(StackEntry* entry, void* stackTop, void* stackBottom, u32 initValue, s32 minSpace, const char* name);
// void Sleep_Cycles(OSTime time);
// void Sleep_Nsec(u32 nsec);
void Sleep_Usec(u32 usec);
// void Sleep_Msec(u32 ms);
// void Sleep_Sec(u32 sec);
// void __osPiCreateAccessQueue(void);
void __osPiGetAccess(void);
void __osPiRelAccess(void);
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags);
void osStopThread(OSThread* t);
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags);
// long long __ull_rshift(unsigned long long left, unsigned long long right);
// unsigned long long __ull_rem(unsigned long long left, unsigned long long right);
// unsigned long long __ull_div(unsigned long long left, unsigned long long right);
// void __ull_divremi(unsigned long long* quotient, unsigned long long* remainder, unsigned long long dividend, unsigned short divisor);
// long long __ll_lshift(long long left, long long right);
// long long __ll_rem(long long left, unsigned long long right);
long long __ll_div(long long left, long long right);
long long __ll_mul(long long left, long long right);
// void __ull_divremi(unsigned long long* quotient, unsigned long long* remainder, unsigned long long dividend, unsigned short divisor);
// long long __ll_mod(long long left, long long right);
// long long __ll_rshift(long long left, long long right);
// void __osExceptionPreamble(void);
// void __osExceptionPreamble(void);
// void __osException(void);
void __osEnqueueThread(OSThread** arg0, OSThread* arg1);
OSThread* __osPopThread(OSThread** arg0);
void osDestroyThread(OSThread* arg0);
void bzero(void* begin, s32 length);
void osCreateThread(OSThread* t, OSId id, void* entry, void* arg, void* sp, OSPri p);
void osWritebackDCache(void* vaddr, s32 nbytes);
// void osWritebackDCacheAll(void);
void* osViGetNextFramebuffer(void);
// uintptr_t osVirtualToPhysical(void* vaddr);
void osViBlack(u8 active);
OSIntMask osSetIntMask(OSIntMask im);
// void osViSetMode(OSViMode* modep);
void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m);
s32 osEPiStartDma(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction);
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msq, s32 count);
void osInvalDCache(void* vaddr, size_t nbytes);
void osSetThreadPri(OSThread* t, OSPri pri);
OSPri osGetThreadPri(OSThread* t);
s32 __osEPiRawStartDma(OSPiHandle* handle, s32 direction, u32 cartAddr, void* dramAddr, size_t size);
OSTime osGetTime(void);
// void __osSetCompare(u32 value);
void bcopy(void* __src, void* __dest, size_t __n);
OSIntMask __osDisableInt(void);
void __osRestoreInt(OSIntMask im);
// void __osViSwapContext(void);
s32 osEPiReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data);
s32 osEPiWriteIo(OSPiHandle* pihandle, u32 devAddr, u32 data);
void osStartThread(OSThread* arg0);
void __osSetHWIntrRoutine(s32 idx, OSMesgQueue* queue, OSMesg msg);

OSPiHandle* osDriveRomInit(void)

#endif
