#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

UNK_PTR func_800AD4C0(UNK_PTR);

extern IrqMgr D_8011D968;
extern u8 D_80121212;
extern vu8 D_80121213;
extern vu8 D_80121214;

// data
extern void* D_801D2E50;
extern s32 (*D_801D2E54)(s32);
// struct_801DC000* D_801D2E50 = &B_801DC000;
// s32 (*D_801D2E54)(s32) = func_801C7A1C;

// bss
extern struct_801D9B90 B_801D9B90; // probably a struct

extern struct_801D9C30 B_801D9C30;
extern struct_801D9C30* B_801D9D48;

extern struct_801D9D50 B_801D9D50;

extern OSMesgQueue B_801D9D80;
extern OSMesgQueue B_801D9D98;
extern OSMesg B_801D9DB0[1];
extern OSMesg B_801D9DB4[1];

extern vu8 B_801D9DB8;

extern volatile OSTime B_801D9DC0;
extern s32 B_801D9DC8; // 1 if disk gameName is correct, 2 otherwise
extern UNK_TYPE B_801D9DCC;
extern UNK_TYPE B_801D9DD0;
extern UNK_TYPE B_801D9DD4;
extern OSThread B_801D9DD8;

extern STACK(B_801D9F88, 0x1000);
extern StackEntry B_801DAF88;
extern STACK(B_801DAFA8, 0x1000);
extern StackEntry B_801DBFA8;

// in-function static
extern void* B_801DBFC8;
extern LEODiskID B_801DBFD0;
extern s32 B_801DBFF0; // bool

// Might be u8, will need to examine code function

u32 func_801C6E80(void) {
    return LeoDriveExist();
}

void func_801C6EA0(UNK_TYPE arg0) {
}

void func_801C6EAC(void) {
    if (D_80121214 == 0) {
        func_800C78FC();
        D_80121214 = 1;
    }
}

s32 func_801C6EF0(void) {
    return D_80121214 != 0;
}

s32 func_801C6F08(void) {
    if (D_80121214 != 0) {
        return 1;
    }
    return 1;
}

void func_801C6F30(void) {
    func_801C6EAC();
    while (func_801C6F08() == 0) {
        Sleep_Usec(16666); // 100000 / 6
    }
}


void func_801C6F78(void) {
    if (D_80121214 != 0) {
        D_80121214 = 0;
        func_800C785C();
    }
}

// boolean
s32 func_801C6FAC(void) {
    if (D_80121213 == 0) {
        return false;
    } else {
        D_80121213 = 0;
        return true;
    }
}

void func_801C6FD8(void) {
    while (!func_801C6FAC()) {
        Sleep_Usec(16666); // 100000 / 6
    }
}

// Adds a HungupAndCrash
void func_801C7018(void) {
    if (D_80121213 != 0) {
        Fault_AddHungupAndCrash("../z_n64dd.c", 503);
    }
    D_80121213 = 1;
}

s32 func_801C7064(void) {
    B_801D9D50.unk0 = 5;
    return (&func_801C8000)(&B_801D9D50);
}

s32 func_801C7098(void) {
    s32 phi_v1;

    if (0) { }

    B_801D9D50.unk0 = 10;
    phi_v1 = (&func_801C8000)(&B_801D9D50);
    if (phi_v1 < 0) {
        func_800D31A0_Freeze();
    }
    return phi_v1;
}

s32 func_801C70E4(void) {
    return B_801D9DC8 == 1;
}

// Used by EnMag and FileChoose
s32 func_801C70FC(void) {
    return func_801C70E4();
}

#ifdef NON_MATCHING
// Matches but needs in-function static
void func_801C711C(void* arg) {
    static void* B_801DBFC8;
    struct_801D9B90* arg0 = (struct_801D9B90*) arg;
    s16* sp58;
    s32 var_s0;
    void* temp_v0;

    sp58 = NULL;
    arg0->unk98 = &D_8011D968;
    osCreateMesgQueue(&arg0->unk78, (void*)arg0, 30);
    IrqMgr_AddClient(arg0->unk98, &arg0->unk90, &arg0->unk78);
    var_s0 = 0;
    do {
        osRecvMesg(&arg0->unk78, (OSMesg*)&sp58, 1);
        switch (*sp58) {
        case 1:
            temp_v0 = osViGetNextFramebuffer();
            if (B_801DBFC8 != temp_v0) {
                B_801DBFC8 = temp_v0;
                B_801D9DB8 = 1;
            }
            func_801C8AA8();
            break;
        case 4:
            LeoReset();
            break;
        case 3:
            var_s0 = 1;
            break;
        }
    } while (var_s0 == 0);
    IrqMgr_RemoveClient(arg0->unk98, &arg0->unk90);
}
#else
void func_801C711C(void* arg);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/z_n64dd/func_801C711C.s")
#endif

void func_801C7268(void) {
    s32 pad;
    s32 sp20;
    s32 sp1C;

    sp20 = func_801C6EF0();
    if (sp20 == 0) {
        func_801C6F30();
    }
    B_801D9DB8 = 1;
    B_801D9DC0 = 0;
    if (func_801C7064() == 1) {
        func_801C7098();
    } else if (B_801D9DC8 != 0) {
        B_801D9DC8 = 0;
    }
    if (B_801D9DC0 != 0) {
        sp1C = (osGetTime() - B_801D9DC0) * 64 / 3000;

        // Remnants from debug statements?
        osGetTime() - B_801D9DC0;
        (osGetTime() - B_801D9DC0) * 64 / 3000;
        (osGetTime() - B_801D9DC0) * 64 / 3000;

        if (1000000 - sp1C > 0) {
            Sleep_Usec(1000000 - sp1C);
        }
    }
    if (sp20 == 0) {
        func_801C6F78();
    }
}

void func_801C7438(void* arg0) {
    u16* var_v0;

    for (var_v0 = (u16*)arg0; var_v0 < (u16*)((u8*)arg0 + 0x25800); var_v0++) {
        *var_v0 = 1;
    }
}

void func_801C746C(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp2C;

    if (arg0 != 0 || arg1 != 0 || arg2 != 0) {
        sp2C = (u8*)osViGetNextFramebuffer() + 0x20000000;
        if ((u32)sp2C & 0xFFFFFF) {
            if (B_801D9DB8 != 0) {
                B_801D9DB8 = 0;
                func_801C7438(sp2C);
                B_801D9DC0 = osGetTime();
            }
            if (arg0 != 0) {
                func_801CA1F0(arg0, 0x60, 0x20, 0xC0, 0x10, 0xB, sp2C, 0x140);
            }
            if (arg1 != 0) {
                func_801CA1F0(arg1, 0, 0x50, 0x140, 0x40, 0xB, sp2C, 0x140);
            }
            if (arg2 != 0) {
                func_801CA1F0(arg2, 0, 0xB0, 0x140, 0x20, 0xB, sp2C, 0x140);
            }
            osViBlack(0);
        }
    }
}

void func_801C75BC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp;

    if (arg0 == 0 && arg1 == 0 && arg2 == 0) {
        return;
    }

    if (B_801D9DB8) {}

    if (arg0 != 0) {
        B_801D9DCC = arg0;
    }
    if (arg1 != 0) {
        B_801D9DD0 = arg1;
    }
    if (arg2 != 0) {
        B_801D9DD4 = arg2;
    }
    func_801C746C(arg0, arg1, arg2);
}

void func_801C761C(void) {
    Sleep_Msec(100);
    func_801C746C(B_801D9DCC, B_801D9DD0, B_801D9DD4);
}

s32 func_801C7658(void) {
    if (D_80121212 != 0) {
        return 0;
    }

    StackCheck_Init(&B_801DAF88, B_801D9F88, STACK_TOP(B_801D9F88), 0, 0x100, "ddmsg");
    osCreateThread(&B_801D9DD8, 9, &func_801C711C, &B_801D9B90, STACK_TOP(B_801D9F88), 13);
    osStartThread(&B_801D9DD8);

    osCreateMesgQueue(&B_801D9D80, B_801D9DB0, ARRAY_COUNT(B_801D9DB0));
    osCreateMesgQueue(&B_801D9D98, B_801D9DB4, ARRAY_COUNT(B_801D9DB4));

    StackCheck_Init(&B_801DBFA8, B_801DAFA8, STACK_TOP(B_801DAFA8), 0, 0x100, "n64dd");

    B_801D9D50.unk1C = &B_801D9D80;
    B_801D9D50.unk20 = &B_801D9D98;
    B_801D9D50.unk24 = 8;
    B_801D9D50.unk28 = &B_801DBFA8;
    B_801D9D50.unk2C = 13;
    B_801D9D50.unk0 = 1;

    (&func_801C8000)(&B_801D9D50);

    D_80121213 = 1;
    func_801C6FD8();

    B_801D9D50.unk0 = 2;
    B_801D9D50.unk10 = 6;
    B_801D9D50.unk14 = &D_80000A54;
    B_801D9D50.unkC = &func_801C75BC;
    (&func_801C8000)(&B_801D9D50);

    B_801D9D50.unk0 = 13;
    (&func_801C8000)(&B_801D9D50);
    return 0;
}

s32 func_801C7818(void) {
    B_801D9D50.unk0 = 12;
    (&func_801C8000)(&B_801D9D50);

    while (func_801C81C4() == 0) {
        // the number 16666 sounds like it could be 1 frame (at 60 frames per second)
        Sleep_Usec(1000000*1/60);
    }

    if (func_801C81C4() != 2) {
        func_801C761C();
        func_800D31A0_Freeze();
        return -3;
    }

    func_801C7018();
    D_80121212 = 1;
    return 0;
}

s32 func_801C78B8(void) {
    s32 phi_v1 = func_801C7658();

    if (phi_v1 == 0) {
        phi_v1 = func_801C7818();
    }
    return phi_v1;
}

s32 func_801C78F0(void) {
    B_801D9D50.unk0 = 0;
    return (&func_801C8000)(&B_801D9D50);
}

void func_801C7920(s32 arg0, s32 arg1, s32 arg2) {
    B_801D9D50.unk18 = arg1;
    B_801D9D50.unk1C = arg0;
    B_801D9D50.unk20 = arg2;
    B_801D9D50.unk0 = 3;
    (&func_801C8000)(&B_801D9D50);
    osGetTime();
    B_801D9D50.unk0 = 6;
    while ((&func_801C8000)(&B_801D9D50) != 0) {
        Sleep_Usec(16666); // 100000 / 6
    }
    B_801D9D50.unk0 = 7;
    if ((&func_801C8000)(&B_801D9D50) != 0) {
        func_800D31A0_Freeze();
    }
}

void func_801C79CC(s32 arg0, s32 arg1, s32 arg2) {
    B_801D9D50.unk18 = arg0;
    B_801D9D50.unk1C = arg1;
    B_801D9D50.unk20 = arg2;
    B_801D9D50.unk0 = 4;
    (&func_801C8000)(&B_801D9D50);
}

void func_801C7A10(LEODiskID* arg0) {
}

// Checks diskId, sets B_801D9DC8 and returns true if diskId is correct
s32 func_801C7A1C(struct_801C7A1C* arg0) {
    LEODiskID *diskId;

    diskId = &arg0->diskId;
    func_801C7A10(diskId);
    if (!B_801DBFF0) {
        if ((bcmp(&diskId->gameName, "EZLJ", 4) == 0) || (bcmp(&diskId->gameName, "EZLE", 4) == 0)) {
            B_801DBFD0 = *diskId;
            B_801DBFF0 = true;
            B_801D9DC8 = 1;
        } else {
            B_801D9DC8 = 2;
        }
    } else if (bcmp(&B_801DBFD0, diskId, 0x20) == 0) {
        B_801D9DC8 = 1;
    } else {
        B_801D9DC8 = 2;
    }
    return B_801D9DC8 == 1;
}

s32 func_801C7B48(s32 arg0, s32* arg1, s32* arg2) {
    s32 sp2C;
    s32 temp_v0;
    s32 sp24;
    s32 sp20;
    s32 temp_v0_2;

    temp_v0_2 = LeoByteToLBA(1, arg0 + 1, &sp2C);
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    sp24 = sp2C - 1;
    if (sp2C == 1) {
        sp20 = 0;
    } else {
        temp_v0 = LeoLBAToByte(1, sp24, &sp20);
        if (temp_v0 != 0) {
            return temp_v0;
        }
    }
    *arg1 = sp24 + 1;
    *arg2 = arg0 - sp20;
    return 0;
}

s32 func_801C7BEC(s32 startLBA) {
    s32 bytes;

    if (LeoLBAToByte(startLBA, 1, &bytes) == 0) {
        return bytes;
    }
    return 0;
}

void func_801C7C1C(void* arg0, s32 arg1, s32 arg2) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    void* sp4C;
    s32 var_s0;
    s32 var_s1;
    s32 temp_v1_2;

    func_801C6FD8();
    func_801C6F30();
    B_801D9DB8 = 1;
    B_801D9DC0 = 0;
    func_801C7B48(arg1, &sp5C, &sp54);
    func_801C7B48(arg1 + arg2, &sp58, &sp50);
    sp4C = D_801D2E50;
    if (sp5C == sp58) {
        func_801C7920(sp5C, sp4C, func_801C7BEC(sp5C));
        bcopy((u8*)sp4C + sp54, arg0, arg2);
    } else {
        var_s1 = 0;
        func_801C7920(sp5C, sp4C, func_801C7BEC(sp5C));
        bcopy((u8*)sp4C + sp54, arg0, func_801C7BEC(sp5C) - sp54);
        if (sp5C + 1 < sp58) {
            for (var_s0 = sp5C + 1; var_s0 < sp58; var_s0++) {
                var_s1 += func_801C7BEC(var_s0);
            }
            func_801C7920(sp5C + 1, (u8*)arg0 + func_801C7BEC(sp5C) - sp54, var_s1);
        }
        if (sp50 > 0) {
            func_801C7920(sp58, sp4C, func_801C7BEC(sp58));
            bcopy((u8*)sp4C, (u8*)arg0 + func_801C7BEC(sp5C) - sp54 + var_s1, sp50);
        }
    }
    if (B_801D9DC0 != 0) {
        temp_v1_2 = (osGetTime() - B_801D9DC0) * 64 / 3000;
        if (1000000 - temp_v1_2 > 0) {
            Sleep_Usec(1000000 - temp_v1_2);
        }
    }
    func_801C7018();
    func_801C6F78();
}

void func_801C7E78(void) {
}

s32 func_801C7E80(void) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    if (B_801D9D48 != NULL) {
        return -1;
    }
    B_801D9D48 = &B_801D9C30;
    func_801C7C1C(B_801D9D48, 0x1060, 0x118);
    sp24 = B_801D9D48->unk_004 - B_801D9D48->unk_000;
    sp20 = B_801D9D48->unk_00C - B_801D9D48->unk_008;
    sp18 = B_801D9D48->unk_008 + sp24;
    func_801C7C1C(B_801D9D48->unk_008, B_801D9D48->unk_000, sp24);
    bzero(sp18, sp20 - sp24);
    func_800AD4C0(B_801D9D48->unk_010);
    return 0;
}

s32 func_801C7F24(void) {
    u32 temp_a0;
    struct_801D9C30* temp_v0;

    if (B_801D9D48 == 0) {
        return -1;
    }

    // Function from code
    func_800AD51C();

    temp_v0 = B_801D9D48;
    temp_a0 = temp_v0->unk_008;
    bzero(temp_a0, temp_v0->unk_00C - temp_a0);
    bzero(B_801D9D48, sizeof(struct_801D9C30));
    B_801D9D48 = 0;
    return 0;
}

void n64dd_SetDiskVersion(s32 arg0) {
    if (arg0 != 0) {
        if (B_801D9D48 == 0) {
            func_801C7E80();
        }
    } else if (B_801D9D48 != 0) {
        func_801C7F24();
    }
}
