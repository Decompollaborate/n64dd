#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"


// From other files
void func_801C94F8(char*, u16);
void func_801C9A10(u8*, s32, char*);

// File-internal
// All 3 of these are also used in another file
u8* func_801C9EC0(void);
u8* func_801C9FFC(void);
u8* func_801CA070(void);

extern char* D_801D2ED0[];              // "Error Number    " array
extern const char* D_801D2EE0[2][8][4]; // Array of error message strings

extern u8 D_801D2FE0[2][192 * 16 / 2]; // i4 textures, 192*16. Error 41
extern u8 D_801D3BE0[2][0x2800];       // Texture array

// bss
extern u8 B_801E0F80[];
extern u8 B_801E1580[];
extern u8 B_801E3D80[];

/**
 * @brief Converts a number in decimal to a hexadecimal number with the same digits, e.g. 1234 -> 0x1234.
 *
 * Will only work on nonnegative numbers.
 *
 * @param decNumber Number in decimal to convert, e.g. 1234
 * @return s32 Hexadecimal number with the same digits as decNumber, e.g. 0x1234
 */
s32 func_801C9B70(s32 decNumber) {
    s32 currPlaceValue;
    s32 currExponent = 0;
    s32 accumulatedHexDigits = 0;
    s32 remainingDecDigits;

    // Nothing to do if only one digit.
    if (decNumber < 10) {
        return decNumber;
    }

    // Find the place value / exponent of the most significant digit in decNumber.
    for (currPlaceValue = 1; 10 * currPlaceValue <= decNumber; currPlaceValue *= 10) {
        currExponent++;
    }

    remainingDecDigits = decNumber;

    // Transfer the digits to hex one at a time.
    while (currExponent--) {
        // Place the most significant remaining digit at the end of the hex output.
        accumulatedHexDigits |= remainingDecDigits / currPlaceValue;
        accumulatedHexDigits *= 0x10; // Shift left one hex digit.

        remainingDecDigits %= currPlaceValue; // Remove most significant of the remaining digits.

        currPlaceValue /= 10;
    }

    accumulatedHexDigits += remainingDecDigits; // Only one digit left in the remainingDecDigits.
    return accumulatedHexDigits;
}

// n64ddError_GetLanguage
s32 func_801C9C48(void) {
    return (gCurrentRegion == 1) ? LANGUAGE_JP : LANGUAGE_EN;
}

// n64ddError_Memset
void func_801C9C74(u8* dest, u8 value, u32 count) {
    while (count--) {
        *dest++ = value;
    }
}

// n64ddError_GetErrorHeader
char* func_801C9CA4(void) {
    return D_801D2ED0[func_801C9C48()];
}

// n64ddError_WriteNumberJP
// Writes a 2-digit number to the char buffer provided
// Character indices for numbers in the error code (EUC-JP)
void func_801C9CD4(char* buf, s32 number) {
    s32 temp_v0 = func_801C9B70(number);
    u16 character;

    if (number >= 10) {
        character = ((temp_v0 >> 4) + '???'); // 0, 0xA380
    } else {
        character = '???'; // Space, 0xA1A1
    }

    func_801C94F8(buf, character);
    buf += 2;
    func_801C94F8(buf, ((temp_v0 & 0xF) + '???')); // 0, 0xA380
}

// n64ddError_WriteNumberEN
// Writes a 2-digit number to the char buffer provided
// Character indices for numbers in the error code (ASCII)
void func_801C9D54(char* buf, s32 number) {
    s32 temp_v0 = func_801C9B70(number);

    if (number >= 10) {
        *buf = (temp_v0 >> 4) + '0';
    } else {
        *buf = ' ';
    }
    buf++;
    *buf = (temp_v0 & 0xF) + '0';
}

void func_801C9DB8(u8* arg0, s32 errorNum) {
    char* errorHeader = func_801C9CA4();

    //! @bug: both of these functions will write to the pointer target, but errorString points to a string literal,
    //! which is meant to be const.
    if (gCurrentRegion == 1) {
        func_801C9CD4(&errorHeader[12], errorNum);
    } else {
        func_801C9D54(&errorHeader[13], errorNum);
    }
    func_801C9A10(arg0, 192, errorHeader);
}

u8* func_801C9E28(s32 errorNum) {
    func_801C9EC0();

    if (errorNum == 41) {
        return D_801D2FE0[func_801C9C48()];
    }

    // 31,32, 37,38,39,40
    if (((errorNum >= 37) && (errorNum < 41)) || (errorNum == 31) || (errorNum == 32)) {
        return B_801E0F80;
    } else {
        func_801C9DB8(B_801E0F80, errorNum);
        return B_801E0F80;
    }
}

// Clear something
u8* func_801C9EC0(void) {
    func_801C9C74(B_801E0F80, 0, 0x600);
    return B_801E0F80;
}

// Prints the error message body (?)
void func_801C9EF4(u8* arg0, s32 errorNum, s32 lineCount) {
    s32 i;

    for (i = 0; i < lineCount; i++, arg0 += 0xA00) {
        char* line = D_801D2EE0[func_801C9C48()][errorNum][i];
        if (1) {}
        func_801C9A10(arg0, 320, line);
    }
}

u8* func_801C9F90(s32 errorNum) {
    func_801C9FFC();
    if (errorNum == 3) {
        return D_801D3BE0[func_801C9C48()];
    }
    func_801C9EF4(B_801E1580, errorNum, 4);
    return B_801E1580;
}

// Clear something
u8* func_801C9FFC(void) {
    func_801C9C74(B_801E1580, 0, 0x2800);
    return B_801E1580;
}

u8* func_801CA030(s32 errorNum) {
    func_801CA070();
    func_801C9EF4(B_801E3D80, errorNum, 2);
    return B_801E3D80;
}

// Clear something
u8* func_801CA070(void) {
    func_801C9C74(B_801E3D80, 0, 0x1400);
    return B_801E3D80;
}
