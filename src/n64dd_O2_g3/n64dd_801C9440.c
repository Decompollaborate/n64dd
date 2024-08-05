#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

// data
void (*D_801D2EC0)(s32, s32, s32) = NULL;

// bss
extern s32 B_801E0F70;

/**
 * Seems to work out if a pair of bytes is a valid EUC-JP character, although there may be additions to the font that
 * make the strange first check make more sense.
 *
 * @param bytes Array 2 bytes to test
 * @return boolean
 */
s32 func_801C9440(u8* bytes) {
    // This is every possible first byte. May make more sense what was intended with the font files?
    if (((*bytes >= 0x8E) && (*bytes <= 0xFE)) || ((*bytes != 0x8F) && (*bytes != 0xA0))) {
        bytes++;
        return (*bytes >= 0xA0) && (*bytes <= 0xFE);
    }
    return false;
}

/**
 * A crude check for a valid 2-byte Shift-JIS character
 *
 * @param bytes Array containing a pair of bytes to test
 * @return boolean
 */
s32 func_801C9494(u8* bytes) {
    // Allowable first bytes.
    if (((*bytes >= 0x81) && (*bytes <= 0x9F)) || ((*bytes >= 0xE0) && (*bytes <= 0xFC))) {
        bytes++;
        // Allowable second bytes.
        return (*bytes >= 0x40) && (*bytes <= 0xFC) && *bytes != 0x7F;
    }
    return false;
}

// Extracts 2 bytes from a bytepacked big-endian short.
void func_801C94F8(char* arg0, u16 arg1) {
    arg0[0] = arg1 >> 8;
    arg0[1] = arg1 & 0xFF;
}

// Convert EUC-JP to JIS X 0208
u16 func_801C9514(u16 eucjpCh) {
    return eucjpCh - 0x8080;
}

/**
 * @brief Converts a JIS X 0208 codepoint to a Shift-JIS one.
 *
 * @param jisCodepoint Two bytes, each between 0x21 and 0x7E, packed big-endian into a short.
 * @return u16 Shift-JIS character representation (expected to be big-endian)
 */
u16 func_801C9534(u16 jisCodepoint) {
    u8 hiByte = (jisCodepoint >> 8) & 0xFF;
    u8 loByte = jisCodepoint & 0xFF;

    if (hiByte & 1) {
        loByte += 0x1F;
        if (loByte >= 0x7F) {
            loByte++;
        }
    } else {
        loByte += 0x7E;
    }

    hiByte = (hiByte - 0x21) / 2 + 0x81;
    if (hiByte >= 0xA0) {
        hiByte += 0x40;
    }

    return (hiByte << 8) + loByte;
}

void func_801C95C0(s32 arg0, s32 arg1, UNK_TYPE arg2) {
    if (D_801D2EC0 != NULL) {
        D_801D2EC0(arg0, arg1, arg2);
    }
}

s32 func_801C95F0(char* arg0) {
    return LeoGetKAdr(func_801C9534(func_801C9514((arg0[0] << 8) | arg0[1]))) + DDROM_FONT_START;
}

s32 func_801C963C(s32* arg0, s32* arg1, s32* arg2, s32* arg3, u8 arg4) {
    s32 temp_v0;
    s32 temp_v1;

    u16 temp = (arg4 - 0x20);
    temp += ((0xC0 * B_801E0F70));

    temp_v0 = LeoGetAAdr(temp, arg1, arg2, arg3);
    temp_v1 = temp_v0 & 0xF;
    *arg0 = (temp_v0 - temp_v1) + DDROM_FONT_START;
    return temp_v1;
}

s32 func_801C969C(UNK_TYPE arg0, s32* arg1, s32* arg2, s32* arg3, u8* arg4) {
    s32 sp24;
    s32 phi_v1;

    if (func_801C9440(arg4)) {
        sp24 = func_801C95F0(arg4);
        *arg1 = 0x10;
        *arg2 = 0x10;
        *arg3 = 0xB;
        phi_v1 = 0;
    } else {
        phi_v1 = func_801C963C(&sp24, arg1, arg2, arg3, *arg4);
    }
    // sp20 = phi_v1;
    func_801C95C0(arg0, sp24, 0x80);
    return phi_v1;
}

// return boolean
s32 func_801C9740(u8* arg0, UNK_TYPE4 arg1, u8 arg2) {
    if (arg1 == 1) {
        *arg0 = arg2 * 0x10;
        return false;
    } else {
        *arg0 |= arg2;
        return true;
    }
}

s32 func_801C9778(s32 arg0, s32* arg1, s32 arg2) {
    arg0 += (arg2 >> 1);

    if (((*arg1 == 1) && !(arg2 & 1)) || ((*arg1 == 0) && (arg2 & 1))) {
        arg0 += arg2 & 1;
        *arg1 = 1;
    } else {
        *arg1 = 0;
    }
    return arg0;
}

#ifdef NON_MATCHING
s32 func_801C97C4(s32* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8* arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 var_fp;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    s32 sp4C;
    s32 var_s4;
    s32 sp44;

    sp4C = arg2;
    sp44 = arg6 + arg3 + arg4;
    var_s4 = 1;
    var_fp = func_801C9778(*arg0, &sp4C, arg3);
    arg1 >>= 1;
    var_fp += ((11 - arg8) * arg1);
    if (arg6 & 1) {
        arg6++;
    }
    if (arg7 != 0) {
        arg7--;
        do {
            var_s0 = var_fp;
            var_s1 = sp4C;
            for (var_s3 = 0; var_s3 < arg6; var_s3++) {
                if (var_s4 == 1) {
                    if (func_801C9740(var_s0, var_s1, *arg5 >> 4) != 0) {
                        var_s0 += 1;
                    }
                } else {
                    if (func_801C9740(var_s0, var_s1, *arg5 & 0xF) != 0) {
                        var_s0 += 1;
                    }
                    arg5 += 1;
                }
                var_s4 ^= 1;
                var_s1 ^= 1;
            }
            var_fp += arg1;
            arg7--;
        } while (arg7 != 0);
    }
    *arg0 = func_801C9778(*arg0, &arg2, sp44);
    return arg2;
}
#else
s32 func_801C97C4(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 arg7, s32 arg8);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9440/func_801C97C4.s")
#endif

void func_801C9954(u8* bytes, s32* arg1, s32* arg2) {
    u8 prevCh;
    u8 nextCh;

    if (func_801C9440(bytes)) {
        *arg2 = 0;
        *arg1 = 0;
    } else {
        *arg2 = 0;
        *arg1 = 0;

        prevCh = bytes[-1];
        nextCh = bytes[1];

        switch (bytes[0]) {
            case ' ':
                *arg2 = 0;
                *arg1 = 0;
                break;

            case 'I':
            case 'i':
                *arg2 = 2;
                *arg1 = 2;
                if (1) {}
                *arg2 = 2;
                if (prevCh == 0x20) {
                    *arg1 = 0;
                }
                if (nextCh == 0x20) {
                    *arg2 = 0;
                }
                break;

            default:
                *arg2 = 1;
                *arg1 = 1;
                if (1) {}
                *arg2 = 1;
                break;
        }
    }
}

void func_801C9A10(s32 arg0, s32 arg1, u8* arg2) {
    u8 sp80[0xA0];
    s32 temp_s1;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 var_s2;
    s32 sp68;
    s32 sp64;
    s32 temp_v1;

    temp_s1 = (((u32)&sp80 + 0xF) / 0x10) * 0x10;
    var_s2 = 1;
    if (arg2 != NULL) {
        while (*arg2 != 0) {
            func_801C9954(arg2, &sp68, &sp64);
            temp_v1 = func_801C969C(temp_s1, &sp78, &sp74, &sp70, arg2);
            if (sp78 & 1) {
                sp78++;
            }
            var_s2 = func_801C97C4(&arg0, arg1, var_s2, sp68, sp64, temp_s1 + temp_v1, sp78, sp74, sp70);
            if (func_801C9440(arg2) != 0) {
                arg2++;
            }
            arg2++;
        }
    }
}

void func_801C9B50(s32 arg0, void (*arg1)(s32, s32, s32)) {
    B_801E0F70 = arg0;
    D_801D2EC0 = arg1;
}
