/**
 * @file Math.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief Hosts creation and destruction methods for the renderer backend.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_MATH_H
#define ELSA_MATH_H

#include <Defines.h>

/** @brief An approximate representation of PI. */
#define E_PI 3.14159265358979323846f

/** @brief An approximate representation of PI multiplied by 2. */
#define E_PI_2 2.0f * E_PI

/** @brief An approximate representation of PI divided by 2. */
#define E_HALF_PI 0.5f * E_PI

/** @brief An approximate representation of PI divided by 4. */
#define E_QUARTER_PI 0.25f * E_PI

/** @brief One divided by an approximate representation of PI. */
#define E_ONE_OVER_PI 1.0f / E_PI

/** @brief One divided by half of an approximate representation of PI. */
#define E_ONE_OVER_2_PI 1.0f / E_PI_2

/** @brief An approximation of the square root of 2. */
#define E_SQRT_TWO 1.41421356237309504880f

/** @brief An approximation of the square root of 3. */
#define E_SQRT_THREE 1.73205080756887729352f

/** @brief One divided by an approximation of the square root of 2. */
#define E_SQRT_ONE_OVER_TWO 0.70710678118654752440f

/** @brief One divided by an approximation of the square root of 3. */
#define E_SQRT_ONE_OVER_THREE 0.57735026918962576450f

/** @brief A multiplier used to convert degrees to radians. */
#define E_DEG2RAD_MULTIPLIER K_PI / 180.0f

/** @brief A multiplier used to convert radians to degrees. */
#define E_RAD2DEG_MULTIPLIER 180.0f / K_PI

/** @brief The multiplier to convert seconds to milliseconds. */
#define E_SEC_TO_MS_MULTIPLIER 1000.0f

/** @brief The multiplier to convert milliseconds to seconds. */
#define E_MS_TO_SEC_MULTIPLIER 0.001f

/** @brief A huge number that should be larger than any valid number used. */
#define E_INFINITY 1e30f

/** @brief Smallest positive number where 1.0 + FLOAT_EPSILON != 0 */
#define E_FLOAT_EPSILON 1.192092896e-07f

// ------------------------------------------
// General math functions
// ------------------------------------------

/**
 * @brief Calculates the sine of x.
 * 
 * @param x The number to calculate the sine of.
 * @return The sine of x.
 */
ELSA_API f32 Sin(f32 x);

/**
 * @brief Calculates the cosine of x.
 * 
 * @param x The number to calculate the cosine of.
 * @return The cosine of x.
 */
ELSA_API f32 Cos(f32 x);

/**
 * @brief Calculates the tangent of x.
 * 
 * @param x The number to calculate the tangent of.
 * @return The tangent of x.
 */
ELSA_API f32 Tan(f32 x);

/**
 * @brief Calculates the arc cosine of x.
 * 
 * @param x The number to calculate the arc cosine of.
 * @return The arc cosine of x.
 */
ELSA_API f32 Acos(f32 x);

/**
 * @brief Calculates the arc sine of x.
 * 
 * @param x The number to calculate the arc sine of.
 * @return The arc sine of x.
 */
ELSA_API f32 Asin(f32 x);

/**
 * @brief Calculates the arc tangent of x.
 * 
 * @param x The number to calculate the arc tangent of.
 * @return The arc tangent of x.
 */
ELSA_API f32 Asin(f32 x);

/**
 * @brief Calculates the square root of x.
 * 
 * @param x The number to calculate the square root of.
 * @return The square root of x.
 */
ELSA_API f32 Sqrt(f32 x);

/**
 * @brief Calculates the absolute value of x.
 * 
 * @param x The number to get the absolute value of.
 * @return The absolute value of x.
 */
ELSA_API f32 Abs(f32 x);

/**
 * @brief Indicates if the value is a power of 2. 0 is considered _not_ a power of 2.
 * @param value The value to be interpreted.
 * @returns True if a power of 2, otherwise false.
 */
ELSA_API b8 IsPowerOf2(u64 value);

/**
 * @brief Returns a random integer.
 * 
 * @return A random integer.
 */
ELSA_API i32 Random();

/**
 * @brief Returns a random integer that is within the given range (inclusive).
 * 
 * @param min The minimum of the range.
 * @param max The maximum of the range.
 * @return A random integer.
 */
ELSA_API i32 RandomInRange(i32 min, i32 max);

/**
 * @brief Returns a random floating-point number.
 * 
 * @return A random floating-point number.
 */
ELSA_API f32 FRandom();

/**
 * @brief Returns a random floating-point number that is within the given range (inclusive).
 * 
 * @param min The minimum of the range.
 * @param max The maximum of the range.
 * @return A random floating-point number.
 */
ELSA_API f32 FRandomInRange(f32 min, f32 max);

#endif