#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

u8* func_801C9E28(s32 errorNum);
u8* func_801C9EC0(void);
u8* func_801C9F90(s32 errorNum);
u8* func_801C9FFC(void);
u8* func_801CA030(s32 errorNum);
u8* func_801CA070(void);

extern u8* D_801D2EA4;
extern s32 D_801D2EA8;
extern u8* D_801D2EAC;
extern u8* D_801D2EB0;

extern s32 B_801E0F60;
extern s32 B_801E0F64;

// Set error message title texture?
void func_801C8940(s32 errorNum) {
    D_801D2EA4 = func_801C9E28(errorNum);
    D_801D2EA8 = 1;
}

// Clear error message title texture?
void func_801C8974(void) {
    if (D_801D2EA8 == 1) {
        D_801D2EA4 = func_801C9EC0();
        D_801D2EA8 = 0;
    }
}

// Set error message something
void func_801C89B8(s32 errorNum) {
    D_801D2EAC = func_801C9F90(errorNum);
    B_801E0F60 = 1;
}

// Clear error message something
void func_801C89EC(void) {
    if (B_801E0F60 == 1) {
        D_801D2EAC = func_801C9FFC();
        B_801E0F60 = 0;
    }
}

// Set error message something
void func_801C8A30(s32 errorNum) {
    D_801D2EB0 = func_801CA030(errorNum);
    B_801E0F64 = 1;
}

// Clear error message something
void func_801C8A64(void) {
    if (B_801E0F64 == 1) {
        D_801D2EB0 = func_801CA070();
        B_801E0F64 = 0;
    }
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8AA8.s")

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8B58.s")
void func_801C8B58(s32 arg0, s32 arg1, s32 arg2) {
    func_801C8940(arg0);
    func_801C89B8(arg1);
    func_801C8A30(arg2);
}

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8B90.s")
void func_801C8B90(void) {
    func_801C8974();
    func_801C89EC();
    func_801C8A64();
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8BC0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8C1C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8CEC.s")

s32 func_801C8DC0(struct_801E0D18* arg0);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8DC0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8E70.s")

extern s32 (*D_801D2E54)(s32);

s32 func_801C8F1C(struct_801E0D18* arg0) {
    if (D_801D2E54 != 0) {
        return D_801D2E54(arg0);
    }
    return 1;
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8F58.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C9000.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C90C4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C90FC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C912C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C91E0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C9260.s")

s32 func_801C9334(struct_801E0D18* arg0) {
    while (true) {
        u32 temp_v0 = func_801C8DC0(arg0);

        if ((temp_v0 == 3) || (temp_v0 == 4) || (temp_v0 == 5)) {
            return temp_v0;
        }
        // Fake match
        if ((temp_v0  & 0xFFFFFFFFu) == 0) {
            if (func_801C8F1C(arg0) != 0) {
                return 0;
            }
            return 7;
        }
        if (1) {}
    }
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C93C4.s")
