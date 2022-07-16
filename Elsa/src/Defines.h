/**
 * @file Defines.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains global type definitions which are used 
 * throughout the entire engine and applications referencing it. 
 * @version 1.0
 * @date 2022-06-17
 */

#ifndef ELSA_DEFINES_H
#define ELSA_DEFINES_H

/** @brief Just used to mark code blocks */
#define CODE_BLOCK(name)

/** @brief Signed 8-bit numeric type */
typedef char i8;

/** @brief Unsigned 8-bit numeric type */
typedef unsigned char u8;

/** @brief Signed 16-bit numeric type */
typedef short i16;

/** @brief Unsigned 16-bit numeric type */
typedef unsigned short u16;

/** @brief Signed 32-bit numeric type */
typedef int i32;

/** @brief Unsigned 32-bit numeric type */
typedef unsigned int u32;

/** @brief Signed 64-bit numeric type */
typedef long long i64;

/** @brief Unsigned 64-bit numeric type */
typedef unsigned long long u64;

/** @brief 32-bit floating point type */
typedef float f32;

/** @brief 64-bit floating point type */
typedef double f64;

/** @brief 8-bit boolean value */
typedef i8 b8;

/** @brief True. */
#define true 1

/** @brief False. */
#define false 0

// Export directives
#ifdef ELSA_EXPORT
#ifdef _MSC_VER
/** @brief Import/export qualifier */
#define ELSA_API __declspec(dllexport)
#else
/** @brief Import/export qualifier */
#define ELSA_API __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
/** @brief Import/export qualifier */
#define ELSA_API __declspec(dllimport)
#else
/** @brief Import/export qualifier */
#define ELSA_API
#endif
#endif

// Platform detection
#if defined(_WIN64) || defined(_WIN32)
#define ELSA_PLATFORM_WINDOWS
#define ELSA_VULKAN
#elif __APPLE__
#define ELSA_METAL
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE && TARGET_OS_SIMULATOR
#define ELSA_PLATFORM_IOS_SIMULATOR
#elif TARGET_OS_IPHONE && TARGET_OS_MACCATALYST
#define ELSA_PLATFORM_MAC_CATALYST
#elif TARGET_OS_IPHONE
#define ELSA_PLATFORM_IPHONE
#else
#define TARGET_OS_OSX 1
#define ELSA_PLATFORM_MACOS
#endif
#elif __linux
#define ELSA_PLATFORM_LINUX
#define ELSA_VULKAN
#elif __unix
#define ELSA_PLATFORM_UNIX
#define ELSA_VULKAN
#elif __posix
#define ELSA_PLATFORM_POSIX
#define ELSA_VULKAN
#else
#error "Unknown platform!"
#endif

// Inline
#if defined(__clang__) || defined(__gcc__)
#define ELSA_INLINE __attribute__((always_inline)) inline
#define ELSA_NO_INLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define ELSA_INLINE __forceinline
#define ELSA_NO_INLINE __declspec(noinline)
#else
#define ELSA_INLINE static inline
#define ELSA_NO_INLINE 
#endif

/**
 * @brief Clamps value to a range of min and max (inclusive).
 * @param value The value to be clamped.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @returns The clamped value.
 */
#define ELSA_CLAMP(value, min, max) ((value <= min) ? min : (value >= max) ? max \
: value)

#endif