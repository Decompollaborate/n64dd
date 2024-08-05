#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

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
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA1F0.s")
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA2F8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA314.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA334.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA350.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA3B4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA3CC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA4F4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA5BC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA618.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA670.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA6A0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA6D8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA6E4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA704.s")
