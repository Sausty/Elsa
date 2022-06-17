#ifndef ELSA_DEFINES_H
#define ELSA_DEFINES_H

// Signed 8-bit numeric type
typedef char i8;

// Unsigned 8-bit numeric type
typedef unsigned char u8;

// Signed 16-bit numeric type
typedef short i16;

// Unsigned 16-bit numeric type
typedef unsigned short u16;

// Signed 32-bit numeric type
typedef int i32;

// Unsigned 32-bit numeric type
typedef unsigned int u32;

// Signed 64-bit numeric type
typedef long long i64;

// Unsigned 64-bit numeric type
typedef unsigned long long u64;

// 32-bit floating point type
typedef float f32;

// 64-bit floating point type
typedef double f64;

// 8-bit boolean type
typedef i8 b8;

// Boolean values
#define true 1
#define false 0

// Export directives
#ifdef ELSA_EXPORT
    #ifdef _MSC_VER
        #define ELSA_API __declspec(dllexport)
    #else
        #define ELSA_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define ELSA_API __declspec(dllimport)
    #else
        #define ELSA_API
    #endif
#endif

// Platform detection
#if defined(_WIN64) || defined(_WIN32)
    #define ELSA_PLATFORM_WINDOWS
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE && TARGET_OS_SIMULATOR
        #define ELSA_PLATFORM_IOS_SIMULATOR
    #elif TARGET_OS_IPHONE && TARGET_OS_MACCATALYST
        #define ELSA_PLATFORM_MAC_CATALYST
    #elif TARGET_OS_IPHONE
        #define ELSA_PLATFORM_IPHONE
    #else
        #define TARGET_OS_OSX 1
        #define ELSA_PLATFORM_OSX
    #endif
#elif __linux
    #define ELSA_PLATFORM_LINUX
#elif __unix
    #define ELSA_PLATFORM_UNIX
#elif __posix
    #define ELSA_PLATFORM_POSIX
#else
    #error "Unknown platform!"
#endif

#endif