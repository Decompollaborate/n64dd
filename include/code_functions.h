#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

#include "ultra64.h"
#include "libc/stdint.h"

typedef union Color_RGBA8_u32 {
    struct {
        u8 r, g, b, a;
    };
    u32 rgba;
} Color_RGBA8_u32;

typedef struct {
    /* 0x00 */ s16 type;
    /* 0x02 */ char misc[0x1E];
} OSScMsg; // size = 0x20

typedef struct IrqMgrClient {
    /* 0x00 */ struct IrqMgrClient* prev;
    /* 0x04 */ OSMesgQueue* queue;
} IrqMgrClient;

typedef struct {
    /* 0x000 */ OSScMsg retraceMsg;
    /* 0x020 */ OSScMsg prenmiMsg;
    /* 0x040 */ OSScMsg nmiMsg;
    /* 0x060 */ OSMesgQueue queue;
    /* 0x078 */ OSMesg msgBuf[8];
    /* 0x098 */ OSThread thread;
    /* 0x248 */ IrqMgrClient* clients;
    /* 0x24C */ u8 resetStatus;
    /* 0x250 */ OSTime resetTime;
    /* 0x258 */ OSTimer timer;
    /* 0x278 */ OSTime retraceTime;
} IrqMgr; // size = 0x280

void DmaMgr_DmaFromDriveRom(void* ram, uintptr_t rom, size_t size);

void Fault_AddHungupAndCrash(const char* filename, u32 line);

void IrqMgr_AddClient(IrqMgr* irqMgr, IrqMgrClient* client, OSMesgQueue* msgQueue);
void IrqMgr_RemoveClient(IrqMgr* irqMgr, IrqMgrClient* client);

s32 PrintUtils_VPrintf(PrintCallback* pfn, const char* fmt, va_list args);

void func_800D31A0(void);

void func_800F6B3C(void);
void func_800F6BDC(void);

// N64 only
UNK_PTR func_800AD4C0(UNK_PTR);
void func_800AD51C(void);

#endif
