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
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 posX;
    /* 0x0C */ u16 posY;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ Color_RGBA8_u32 color;
    /* 0x14 */ u16 baseX;
    /* 0x16 */ u16 baseY;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26;
} struct_801CA704;

#ifdef NON_MATCHING
// TODO: size and values?
u32 D_801D8B60[1];

// arg0: some kind of char
// arg1: dramAddr
s32 func_801CA0B0(s32 arg0, s32 arg1, s32* dx, s32* dy, s32* cy) {
    s32 var_s0;
    OSPiHandle* handle;
    OSMesgQueue sp40;
    s32 sp3C;
    OSIoMesg mesg;

    handle = osDriveRomInit();
    if (arg0 >= 0x20 && arg0 < 0x7F) {  // ASCII
        var_s0 = LeoGetAAdr2(D_801D8B60[arg0], dx, dy, cy);
    } else if (arg0 >= 0x8140) {  // Shift-JIS
        var_s0 = LeoGetKAdr(arg0);
        *dx = 16;
        *dy = 16;
        *cy = 11;
    } else {
        return -1;
    }

    osCreateMesgQueue(&sp40, (OSMesg*)&sp3C, 1);

    mesg.size = 0x80;
    mesg.hdr.retQueue = &sp40;
    mesg.devAddr = var_s0 + 0xA0000;
    mesg.dramAddr = arg1;
    mesg.hdr.pri = 0;

    handle->transferInfo.cmdType = 2;
    osEPiStartDma(handle, &mesg, 0);
    osRecvMesg(&sp40, NULL, 1);

    return 0;
}
#else
s32 func_801CA0B0(s32 arg0, s32 arg1, s32* dx, s32* dy, s32* cy);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA0B0.s")
#endif

const u16 D_801D9390[0x10] = {
    1,
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

u16 func_801CA1D4(u32 arg0) {
    return D_801D9390[arg0 % ARRAY_COUNT(D_801D9390)];
}

#ifdef NON_MATCHING
void func_801CA1F0(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16* arg6, s32 arg7) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s5;
    u8* var_s1;
    s16* var_s2;

    var_s0 = 0;
    var_s1 = arg0;
    for (var_s5 = 0; var_s5 < arg4; var_s5++) {
        if (arg3 > 0) {
            var_s2 = arg6 + arg1 + (((arg2 - arg5) + var_s5 + 11) * arg7);
            do {
                if (!(var_s0 & 1)) {
                    var_a0 = *var_s1 >> 4;
                } else {
                    var_a0 = *var_s1 & 0xF;
                    var_s1 += 1;
                }
                *var_s2 = func_801CA1D4(var_a0);
                var_s0 += 1;
                var_s2++;
            } while (var_s0 != arg3);
        }
        if (arg3 & 1) {
            var_s1 += 1;
        }
    }
}
#else
void func_801CA1F0(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16* arg6, s32 arg7);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA1F0.s")
#endif

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

void func_801CA334(struct_801CA704* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->baseX = arg1;
    arg0->baseY = arg2;
    arg0->unk18 = arg3;
    arg0->unk1A = arg4;
}

void func_801CA350(struct_801CA704* arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk20 = arg1 + 0x20000000;
    arg0->unk24 = arg2;
    arg0->unk26 = arg3;
    func_801CA334(arg0, 0, 0, arg2 - 1, arg3 - 1);
}

void func_801CA3B4(struct_801CA704* arg0, s32 arg1, s32 arg2) {
    arg0->unk4 = arg1 + 0x20000000;
    arg0->unk8 = arg2;
}

#if NON_MATCHING
void func_801CA3CC(struct_801CA704* arg0, char c) {
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_v0;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    u16 temp_t1;
    u16 var_a1;
    u8 temp_v0;

    temp_v0 = arg0->unk1C;
    if (temp_v0 != 0) {
        var_a0 = (temp_v0 << 8) | c;
    } else {
        if (c >= 0x80 && c < 0x99) {
            arg0->unk1C = c;
            return;
        }
        var_a0 = c;
    }

    arg0->unk1C = 0;
    if (func_801CA0B0(var_a0, arg0->unk4, &sp48, &sp44, &sp40) == 0) {
        var_a1 = arg0->posX;
        if (arg0->unk18 < var_a1 + sp48) {
            temp_t1 = arg0->baseX;
            temp_v0_2 = arg0->posY + 0x10;
            arg0->posX = temp_t1;
            if (arg0->unk1A < temp_v0_2) {
                var_a1 = temp_t1 & 0xFFFF;
                arg0->posY = arg0->baseY;
            } else {
                arg0->posY = temp_v0_2;
                var_a1 = arg0->posX;
            }
        }
        func_801CA1F0(arg0->unk4, var_a1, arg0->posY, sp48, sp44, sp40, arg0->unk20, arg0->unk24);
        var_v0 = sp48 == 0x10 ? sp48 : sp48 + 2;
        arg0->posX += var_v0;
    }
}
#else
void func_801CA3CC(struct_801CA704* arg0, char arg1);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA3CC.s")
#endif

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
    arg0->unk18 = 0;
    arg0->unk1A = 0;
    arg0->color.rgba = 0;
    arg0->unk1C = 0;
    arg0->unk4 = 0;
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
