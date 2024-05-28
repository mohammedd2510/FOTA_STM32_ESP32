// Header Guard File
#ifndef STD_TYPES_H
#define STD_TYPES_H

// typedef new_datatype old_datatype
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef signed char s8;
typedef signed short int s16;
typedef signed int s32;

typedef float f32;
typedef double f64;

typedef void (*pCallBackNotification)(void);

typedef void (*PtrFunction)(void);
#define NULL 0

#define ZERO_INIT 0

#define INTERRUPT_ENABLED 1
#define INTERRUPT_DISABLED 0

#define INTERRUPT_ACTIVE 1
#define INTERRUPT_INACTIVE 0

#define STD_OK 0
#define STD_NOK 1
#define STD_TIMEOUT 2

typedef u8 Std_ReturnType;

#endif
