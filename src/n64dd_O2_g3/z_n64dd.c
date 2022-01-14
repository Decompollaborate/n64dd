#include "n64dd.h"

// data
/*
struct_801DC000* D_801D2E50 = &D_801DC000;

s32 (*D_801D2E54)(s32) = func_801C7A1C;
*/

extern struct_801DC000* D_801D2E50;

s32 func_801CE120(void);

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6E80.s")
// Might be u8, will need to examine code function
s32 func_801C6E80(void) {
    return func_801CE120();
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6EA0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6EAC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6EF0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6F08.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6F30.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6F78.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6FAC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C6FD8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7018.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7064.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7098.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C70E4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C70FC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C711C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7268.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7438.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C746C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C75BC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C761C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7658.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7818.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C78B8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C78F0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7920.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C79CC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7A10.s")

s32 func_801C7A1C(s32);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7A1C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7B48.s")


s32 func_801CBEF0(UNK_TYPE arg0, UNK_TYPE arg1, s32* arg2);

s32 func_801C7BEC(s32 arg0) {
    s32 sp1C;

    if (func_801CBEF0(arg0, 1, &sp1C) == 0) {
        return sp1C;
    }
    return 0;
}


#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7C1C.s")

extern u8 D_801D9DB8;
extern u64 D_801D9DC0;
#if 0
void func_801C7C1C(UNK_PTR arg0, s32 arg1, u32 arg2) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    struct_801DC000* sp4C;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;
    u32 temp_t7;
    u32 temp_v1;
    u32 temp_v1_2;
    u64 temp_ret;
    u64 temp_ret_2;
    s32 phi_s0;
    s32 phi_s1;
    s32 phi_s1_2;
    s32 phi_s1_3;

    func_801C6FD8();
    func_801C6F30();
    D_801D9DB8 = 1;

    //D_801D9DC0.unk_0 = 0;
    //D_801D9DC0.unk_4 = 0U;
    D_801D9DC0 = 0;
    
    func_801C7B48(arg1, &sp5C, &sp54);
    func_801C7B48(arg1 + arg2, &sp58, &sp50);
    sp4C = D_801D2E50;
    if (sp5C == sp58) {
        func_801C7920(sp5C, sp4C, func_801C7BEC(sp5C));
        bcopy(sp4C + sp54, arg0, arg2);
    } else {
        func_801C7920(sp5C, sp4C, func_801C7BEC(sp5C));
        bcopy(sp4C + sp54, arg0, func_801C7BEC(sp5C) - sp54);
        temp_v0 = sp5C + 1;
        phi_s1 = 0;
        phi_s1_2 = 0;
        phi_s1_3 = 0;
        if (temp_v0 < sp58) {
            phi_s0 = temp_v0;
            if (temp_v0 < sp58) {
                do {
                    temp_s0 = phi_s0 + 1;
                    temp_s1 = phi_s1_3 + func_801C7BEC(phi_s0);
                    phi_s0 = temp_s0;
                    phi_s1 = temp_s1;
                    phi_s1_3 = temp_s1;
                } while (temp_s0 < sp58);
            }
            func_801C7920(sp5C + 1, (func_801C7BEC(sp5C) + arg0) - sp54, phi_s1, sp54);
            phi_s1_2 = phi_s1;
        }
        if (sp50 > 0) {
            func_801C7920(sp58, sp4C, func_801C7BEC(sp58));
            bcopy(sp4C, ((func_801C7BEC(sp5C) + arg0) - sp54) + phi_s1_2, (u32) sp50);
        }
    }
    //if ((D_801D9DC0.unk_0 != 0) || (D_801D9DC0.unk_4 != 0)) {
    if ((D_801D9DC0 != 0)) {
        temp_ret = osGetTime();
        temp_v1 = (u32) temp_ret;
        //temp_t7 = D_801D9DC0.unk_4;
        //temp_ret_2 = __ll_mul((temp_ret - D_801D9DC0.unk_0) - (temp_v1 < temp_t7), temp_v1 - temp_t7, 0, 0x40);
        temp_v1_2 = (u32) __ull_div(temp_ret_2, (u32) temp_ret_2, 0, 0xBB8);
        if ((0xF4240 - temp_v1_2) > 0) {
            Sleep_Usec(0xF4240 - temp_v1_2);
        }
    }
    func_801C7018();
    func_801C6F78();
}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7E78.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7E80.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C7F24.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/n64dd_SetDiskVersion.s")