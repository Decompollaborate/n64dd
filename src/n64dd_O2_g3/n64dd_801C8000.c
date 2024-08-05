#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

// bss
extern OSMesgQueue* B_801E0D10[2];
extern struct_801E0D18 B_801E0D18;
extern OSMesg B_801E0D88[1];
extern OSMesg B_801E0D90[8];
extern OSThread B_801E0DB0;

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8000/func_801C8000.s")

extern s32 D_801D2E60;
extern s32 D_801D2E64;
void func_801C819C(UNK_TYPE arg0) {
    if (arg0 != 0) {
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

void func_801C81EC(struct_801E0D18* arg0) {
    osCreateMesgQueue(&arg0->unk_1C, B_801E0D88, ARRAY_COUNT(B_801E0D88));

    if (gCurrentRegion == 1) {
        arg0->unk_68 = LeoCJCreateLeoManager(LEO_PRIORITY_WRK, LEO_PRIORITY_INT, B_801E0D90, ARRAY_COUNT(B_801E0D90));
    } else {
        arg0->unk_68 = LeoCACreateLeoManager(LEO_PRIORITY_WRK, LEO_PRIORITY_INT, B_801E0D90, ARRAY_COUNT(B_801E0D90));
    }

    if ((arg0->unk_68 == LEO_ERROR_DEVICE_COMMUNICATION_FAILURE) || (arg0->unk_68 == LEO_ERROR_GOOD)) {
        D_801D2E64 = 1;
    }
}

void func_801C8298(struct_801E0D18* arg0) {
    LEOCmd sp1C;

    LeoSeek(&sp1C, &arg0->unk_38, &arg0->unk_1C);
    osRecvMesg(&arg0->unk_1C, (void** ) &arg0->unk_68, 1);
}

void func_801C82E0(struct_801E0D18* arg0) {
    LEOCmd sp1C;

    LeoSpdlMotor(&sp1C, 4, &arg0->unk_1C);
    osRecvMesg(&arg0->unk_1C, (void** ) &arg0->unk_68, 1);
}

void func_801C832C(struct_801E0D18* arg0) {
    s32 sp34;
    s32 startLBA = arg0->unk_5C;

    if (LeoByteToLBA(startLBA, arg0->unk_60, &sp34) == 0) {
        OSMesgQueue* sp28 = &arg0->unk_1C;

        LeoReadWrite(&arg0->unk_00, OS_READ, startLBA, arg0->unk_58, sp34, sp28);
        osRecvMesg(sp28, (void** ) &arg0->unk_68, 1);
    }
}

void func_801C83A0(struct_801E0D18* arg0) {
    s32 sp34;
    s32 startLBA = arg0->unk_58;

    if (LeoByteToLBA(startLBA, arg0->unk_60, &sp34) == 0) {
        OSMesgQueue* sp28 = &arg0->unk_1C;

        LeoReadWrite(&arg0->unk_00, OS_WRITE, startLBA, arg0->unk_5C, sp34, sp28);
        osRecvMesg(sp28, (void** ) &arg0->unk_68, 1);
    }
}

void func_801C8414(struct_801E0D18* arg0) {
    arg0->unk_68 = 9;
}

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

void func_801C84D4(void* arg) {
    while (true) {
        struct_801E0D18* sp24;

        osRecvMesg(B_801E0D10[0], (void*)&sp24, 1);
        func_801C8424(sp24);
        osSendMesg(B_801E0D10[1], NULL, 1);
    }
}

void func_801C8554(void) {
    osDestroyThread(&B_801E0DB0);
}

void func_801C8578(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    B_801E0D10[0] = arg0;
    B_801E0D10[1] = arg1;
    osCreateThread(&B_801E0DB0, arg2, &func_801C84D4, NULL, arg3, arg4);
    osStartThread(&B_801E0DB0);
}

void func_801C85F0(struct_801E0D18* arg0, s32 arg1) {
    if (arg1 == 1) {
        func_801C8424(arg0);
    } else {
        osSendMesg(B_801E0D10[0], arg0, 1);
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

    if (B_801E0D18.unk_68 == LEO_ERROR_BUSY) {
        return 0;
    }

    if (!temp) {
        return 2;
    }

    return 1;
}

s32 func_801C87C0(void) {
    if (func_801C8844() == 0) {
        if (B_801E0D18.unk_68 != 0) {
            return B_801E0D18.unk_68;
        }
    }

    return -1;
}

s32 func_801C87FC(void) {
    s32* new_var = &B_801E0D18.unk_68;
    s32 temp_v0;

    if (func_801C8844() == 0) {
        temp_v0 = B_801E0D18.unk_6C;

        if ((temp_v0 == 3) || (temp_v0 == 4)) {
            return *new_var;
        }
    }

    return 0;
}

s32 func_801C8844(void) {
    return B_801E0D18.unk_66 == 1;
}

s32 func_801C885C(void) {
    B_801E0D18.unk_64 = 3;
    func_801C85F0(&B_801E0D18, 1);

    if ((B_801E0D18.unk_6C == 3) || (B_801E0D18.unk_6C == 4)) {
        return -1;
    }
    return B_801E0D18.unk_6C == 0;
}

s32 func_801C88AC(void) {
    s32 phi_v0;

    B_801E0D18.unk_64 = 4;
    func_801C85F0(&B_801E0D18, 1);
    if ((B_801E0D18.unk_6C == 3) || (B_801E0D18.unk_6C == 4)) {
        return -1;
    }
    return B_801E0D18.unk_6C == 0;
}

s32 func_801C88FC(void) {
    s32 temp = 0;
    s32 phi_v1;

    if (LeoDriveExist()) {
        phi_v1 = 8;
    } else {
        phi_v1 = 0;
    }

    temp = phi_v1 == temp;

    B_801E0D18.unk_68 = phi_v1;

    return temp;
}
