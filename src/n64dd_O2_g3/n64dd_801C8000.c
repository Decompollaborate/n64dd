#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

extern OSThread B_801E0DB0;

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C8000.s")

extern s32 D_801D2E60;
extern s32 D_801D2E64;
void func_801C819C(UNK_PTR arg0) {
    if (arg0 != NULL) {
        D_801D2E60 = 1;
    } else {
        D_801D2E60 = 2;
    }
}

s32 func_801C81C4(void) {
    return D_801D2E60;
}

s32 func_801C81D4(void) {
    return D_801D2E64 == 1;
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C81EC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C8298.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C82E0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C832C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C83A0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C8414.s")

struct _struct_D_801D2E68_0x8 {
    /* 0x0 */ void (*unk_0)(struct_801E0D18*);      /* inferred */
    /* 0x4 */ s32 (*unk_4)(struct_801E0D18*);     /* inferred */
};                                                  /* size = 0x8 */

extern struct _struct_D_801D2E68_0x8 D_801D2E68[5];

void func_801C8424(struct_801E0D18* arg0) {
    struct _struct_D_801D2E68_0x8* temp_v0;
    s32 (*temp_s2)(struct_801E0D18*);
    void (*aux)(struct_801E0D18*);
    s32 temp_v0_2;

    arg0->unk_68 = -1;
    if ((func_801C81D4() != 0) || (arg0->unk_64 == 0)) {
        arg0->unk_66 = 1;
        temp_v0 = &D_801D2E68[arg0->unk_64];
        aux = temp_v0->unk_0;
        temp_s2 = temp_v0->unk_4;
        do {
            aux(arg0);
            temp_v0_2 = temp_s2(arg0);
        } while (temp_v0_2 == 2);
        arg0->unk_6C = temp_v0_2;
        if (arg0->unk_64 == 0) {
            func_801C819C(temp_v0_2);
        }
        arg0->unk_66 = 0;
    }
}


#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C84D4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C8554.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C8578.s")

extern OSMesgQueue* B_801E0D10;

void func_801C85F0(struct_801E0D18* arg0, s32 arg1) {
    if (arg1 == 1) {
        func_801C8424(arg0);
    } else {
        osSendMesg(B_801E0D10, arg0, 1);
    }
}

extern s32 D_801D2EB4;

//extern u8 B_801E0D7C;
//extern u8 B_801E0D7D;

#if 0
void func_801C8638(s32 arg0, s32 arg1, void (*arg2)(s32, s32, s32)) {
    func_801C9B50(arg1, arg2);
    D_801D2EB4 = arg0;
    //B_801E0D7C = 0;
    //B_801E0D7D = 0;
    B_801E0D18.unk_64 = 0;
    B_801E0D18.unk_65 = 0;
    func_801C85F0(&B_801E0D18, 0);
}
#else
void func_801C8638(s32 arg0, s32 arg1, void (*arg2)(s32, s32, s32));
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C8638.s")
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C868C.s")

s32 func_801C873C(struct_801E0D18* arg0) {
    u8 sp1F;

    arg0->unk_68 = LeoTestUnitReady(&sp1F);

    return !(sp1F & LEO_TEST_UNIT_MR);
}

s8 func_801C8770(void) {
    s32 temp = func_801C873C(&B_801E0D18);

    // == LEO_ERROR_BUSY?
    if (B_801E0D18.unk_68 == 8) {
        return 0;
    }

    if (!temp) {
        return 2;
    }

    return 1;
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C87C0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C87FC.s")

s32 func_801C8844(void) {
    return B_801E0D18.unk_66 == 1;
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C885C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C88AC.s")

#ifdef NON_MATCHING
s32 func_801C88FC(void) {
    s32 phi_v1;

    if (LeoDriveExist()) {
        phi_v1 = 8;
    } else {
        phi_v1 = 0;
    }

    B_801E0D18.unk_68 = phi_v1;

    return phi_v1 == 0;
}
#else
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C88FC.s")
#endif
