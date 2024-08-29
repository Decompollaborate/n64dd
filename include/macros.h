#ifndef MACROS_H
#define MACROS_H

#define NTSC_1_0 0
#define NTSC_1_1 1
#define PAL_1_0  2
#define NTSC_1_2 3
#define PAL_1_1  4

#if OOT_VERSION == NTSC_1_0 || OOT_VERSION == NTSC_1_1 || OOT_VERSION == NTSC_1_2
#define OOT_NTSC 1
#define OOT_PAL 0
#else
#define OOT_NTSC 0
#define OOT_PAL 1
#endif

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define ALIGN8(val) (((val) + 7) & ~7)

#define STACK(stack, size) u64 stack[ALIGN8(size) / sizeof(u64)]

#define STACK_TOP(stack) ((u8*)(stack) + sizeof(stack))

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(x)
#endif

#define FALLTHROUGH  __attribute__((fallthrough))

#endif
