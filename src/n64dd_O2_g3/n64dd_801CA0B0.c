#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

// from color.h
typedef union Color_RGBA8_u32 {
    struct {
        u8 r, g, b, a;
    };
    u32 rgba;
} Color_RGBA8_u32;

// Similar to GfxPrint
typedef struct struct_801CA704 {
    /* 0x00 */ PrintCallback callback;
    /* 0x04 */ void* charTexBuf;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 posX;
    /* 0x0C */ u16 posY;
    /* 0x10 */ Color_RGBA8_u32 color;
    /* 0x14 */ u16 baseX;
    /* 0x16 */ u16 baseY;
    /* 0x18 */ u16 endX;
    /* 0x1A */ u16 endY;
    /* 0x1C */ u8 sjisPrevByte;
    /* 0x20 */ void* frameBuf;
    /* 0x24 */ u16 screenWidth;
    /* 0x26 */ u16 screenHeight;
} struct_801CA704;

#ifdef NON_MATCHING
// TODO: size and values?
u32 D_801D8B60[1];

// Loads character texture to buffer
s32 func_801CA0B0(s32 charCode, void* charTexBuf, s32* dx, s32* dy, s32* cy) {
    s32 offset;
    OSPiHandle* handle;
    OSMesgQueue queue;
    OSMesg msgBuf[1];
    OSIoMesg mesg;

    handle = osDriveRomInit();
    if (charCode >= 0x20 && charCode < 0x7F) {  // ASCII
        offset = LeoGetAAdr2(D_801D8B60[charCode], dx, dy, cy);
    } else if (charCode >= 0x8140) {  // Shift-JIS
        offset = LeoGetKAdr(charCode);
        *dx = 16;
        *dy = 16;
        *cy = 11;
    } else {
        return -1;
    }

    osCreateMesgQueue(&queue, msgBuf, ARRAY_COUNT(msgBuf));

    mesg.size = 0x80;
    mesg.hdr.retQueue = &queue;
    mesg.devAddr = offset + DDROM_FONT_START;
    mesg.dramAddr = charTexBuf;
    mesg.hdr.pri = 0;

    handle->transferInfo.cmdType = 2;
    osEPiStartDma(handle, &mesg, 0);
    osRecvMesg(&queue, NULL, 1);

    return 0;
}
#else
s32 func_801CA0B0(s32 charCode, void* charTexBuf, s32* dx, s32* dy, s32* cy);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA0B0.s")
#endif

const u16 D_801D9390[16] = {
    0x0001,
    0x1085,
    0x2109,
    0x318D,
    0x4211,
    0x5295,
    0x6319,
    0x739D,
    0x8C63,
    0x9CE7,
    0xAD6B,
    0xBDEF,
    0xCE73,
    0xDEF7,
    0xEF7B,
    0xFFFF,
};

// Maps 4-bit intensity to a 16-bit color
u16 func_801CA1D4(u32 arg0) {
    return D_801D9390[arg0 % ARRAY_COUNT(D_801D9390)];
}

void func_801CA1F0(void* charTexBuf, s32 posX, s32 posY, s32 dx, s32 dy, s32 cy, void* frameBuf, s32 screenWidth) {
    s32 intensity;
    s32 x;
    s32 y;
    u8* src = charTexBuf;
    u16* dst = frameBuf;

    for (y = 0; y < dy; y++) {
        for (x = 0; x < dx; x++) {
            if (!(x & 1)) {
                intensity = *src >> 4;
            } else {
                intensity = *src & 0xF;
                src++;
            }
            dst[posX + x + ((posY + (11 - cy) + y) * screenWidth)] = func_801CA1D4(intensity);
        }
        if (dx & 1) {
            src++;
        }
    }
}

void func_801CA2F8(struct_801CA704* arg0, u32 r, u32 g, u32 b, u32 a) {
    arg0->color.r = r;
    arg0->color.g = g;
    arg0->color.b = b;
    arg0->color.a = a;
}

void func_801CA314(struct_801CA704* arg0, s32 arg1, s32 arg2) {
    arg0->posX = arg0->baseX + arg1;
    arg0->posY = arg0->baseY + arg2;
}

void func_801CA334(struct_801CA704* arg0, s32 baseX, s32 baseY, s32 endX, s32 endY) {
    arg0->baseX = baseX;
    arg0->baseY = baseY;
    arg0->endX = endX;
    arg0->endY = endY;
}

void func_801CA350(struct_801CA704* arg0, void* frameBuf, s32 screenWidth, s32 screenHeight) {
    arg0->frameBuf = (u8*)frameBuf + 0x20000000;
    arg0->screenWidth = screenWidth;
    arg0->screenHeight = screenHeight;
    func_801CA334(arg0, 0, 0, screenWidth - 1, screenHeight - 1);
}

void func_801CA3B4(struct_801CA704* arg0, void* charTexBuf, s32 arg2) {
    arg0->charTexBuf = (u8*)charTexBuf + 0x20000000;
    arg0->unk8 = arg2;
}

void func_801CA3CC(struct_801CA704* arg0, char c) {
    s32 charCode;
    s32 dx;
    s32 dy;
    s32 cy;

    if (arg0->sjisPrevByte != 0) {
        charCode = (arg0->sjisPrevByte << 8) | c;
    } else {
        if (c >= 0x80 && c < 0x99) {
            arg0->sjisPrevByte = c;
            return;
        }
        charCode = c;
    }

    arg0->sjisPrevByte = 0;
    if (func_801CA0B0(charCode, arg0->charTexBuf, &dx, &dy, &cy) == 0) {
        if (arg0->posX + dx > arg0->endX) {
            arg0->posX = arg0->baseX;
            if (arg0->posY + 16 > arg0->endY) {
                arg0->posY = arg0->baseY;
            } else {
                arg0->posY += 16;
            }
        }
        func_801CA1F0(arg0->charTexBuf, arg0->posX, arg0->posY, dx, dy, cy, arg0->frameBuf, arg0->screenWidth);
        arg0->posX += (dx == 16 ? dx : dx + 2);
    }
}

void func_801CA4F4(struct_801CA704* arg0, char c) {
    if (c >= 0x20 && c <= 0xFF) {
        func_801CA3CC(arg0, c);
        return;
    } else {
        switch (c) {
        case '\n':
            arg0->posY += 32;
            /* fallthrough */
        case '\r':
            arg0->posX = arg0->baseX;
            break;
        case '\t':
            do {
                func_801CA3CC(arg0, ' ');
            } while ((arg0->posX - arg0->baseX) % 256);
            break;
        case '\0':
            break;
        }
    }
}

void func_801CA5BC(struct_801CA704* arg0, const char* str, s32 arg2, size_t count) {
    const char* s = str;
    s32 n = arg2 * count;

    while (n != 0) {
        func_801CA4F4(arg0, *s++);
        n--;
    }
}

void func_801CA618(struct_801CA704* arg0, const char* str) {
    while (*str != 0) {
        func_801CA4F4(arg0, *str++);
    }
}

void* func_801CA670(void* arg, const char* str, size_t count) {
    func_801CA5BC(arg, str, 1, count);
    return arg;
}

void func_801CA6A0(struct_801CA704* arg0) {
    arg0->callback = &func_801CA670;
    arg0->posX = 0;
    arg0->posY = 0;
    arg0->baseX = 0;
    arg0->baseY = 0;
    arg0->endX = 0;
    arg0->endY = 0;
    arg0->color.rgba = 0;
    arg0->sjisPrevByte = 0;
    arg0->charTexBuf = NULL;
}

void func_801CA6D8(struct_801CA704* arg0) {}

s32 func_801CA6E4(struct_801CA704* arg0, const char* fmt, va_list args) {
    return PrintUtils_VPrintf(&arg0->callback, fmt, args);
}

s32 func_801CA704(struct_801CA704* arg0, const char* fmt, ...) {
    s32 ret;
    va_list args;

    va_start(args, fmt);
    ret = func_801CA6E4(arg0, fmt, args);
    va_end(args);

    return ret;
}
