/**
 * @file Math.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains definitions for various important constant values
 * as well as functions for many common math types.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_MATH_H
#define ELSA_MATH_H

#include <Defines.h>
#include <Math/MathTypes.h>
#include <math.h>
#include <stdlib.h>

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
#define E_DEG2RAD_MULTIPLIER E_PI / 180.0f

/** @brief A multiplier used to convert radians to degrees. */
#define E_RAD2DEG_MULTIPLIER 180.0f / E_PI

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
ELSA_INLINE f32 Sin(f32 x) {
	return sinf(x);
}

/**
 * @brief Calculates the cosine of x.
 * 
 * @param x The number to calculate the cosine of.
 * @return The cosine of x.
 */
ELSA_INLINE f32 Cos(f32 x) {
	return cosf(x);
}

/**
 * @brief Calculates the tangent of x.
 * 
 * @param x The number to calculate the tangent of.
 * @return The tangent of x.
 */
ELSA_INLINE f32 Tan(f32 x) {
	return tanf(x);
}

/**
 * @brief Calculates the arc cosine of x.
 * 
 * @param x The number to calculate the arc cosine of.
 * @return The arc cosine of x.
 */
ELSA_INLINE f32 Acos(f32 x) {
	return acosf(x);
}

/**
 * @brief Calculates the arc sine of x.
 * 
 * @param x The number to calculate the arc sine of.
 * @return The arc sine of x.
 */
ELSA_INLINE f32 Asin(f32 x) {
	return asinf(x);
}

/**
 * @brief Calculates the arc tangent of x.
 * 
 * @param x The number to calculate the arc tangent of.
 * @return The arc tangent of x.
 */
ELSA_INLINE f32 Atan(f32 x) {
	return atanf(x);
}

/**
 * @brief Calculates the square root of x.
 * 
 * @param x The number to calculate the square root of.
 * @return The square root of x.
 */
ELSA_INLINE f32 Sqrt(f32 x) {
	return sqrtf(x);
}

/**
 * @brief Calculates the absolute value of x.
 * 
 * @param x The number to get the absolute value of.
 * @return The absolute value of x.
 */
ELSA_INLINE f32 Abs(f32 x) {
	return fabsf(x);
}

/**
 * @brief Indicates if the value is a power of 2. 0 is considered _not_ a power of 2.
 * @param value The value to be interpreted.
 * @returns True if a power of 2, otherwise false.
 */
ELSA_INLINE b8 IsPowerOf2(u64 value) {
	return (value != 0) && ((value & (value - 1)) == 0);
}

// ------------------------------------------
// Vector 2
// ------------------------------------------

/**
 * @brief Creates and returns a 2-component vector with all components set to 0.0f.
 */
ELSA_INLINE v2f V2Zero() {
	return (v2f){{0.0f, 0.0f}};
}

/**
 * @brief Creates and returns a 2-component vector with all components set to 1.0f.
 */
ELSA_INLINE v2f V2One() {
	return (v2f){{1.0f, 1.0f}};
}

/**
* @brief Creates and returns a 2-component vector with all components set to the given value.
* @param scalar The value to set.
*/
ELSA_INLINE v2f V2Scalar(f32 scalar) {
	return (v2f){{scalar, scalar}};
}

/**
* @brief Creates and returns a 2-component vector with its components set to the given values.
* @param x The x value of the vector.
* @param y The y value of the vector.
*/
ELSA_INLINE v2f V2Create(f32 x, f32 y) {
	return (v2f){{x, y}};
}

/**
 * @brief Creates and returns a 2-component vector pointing up (0, 1).
 */
ELSA_INLINE v2f V2Up() {
    return (v2f){{0.0f, 1.0f}};
}

/**
 * @brief Creates and returns a 2-component vector pointing down (0, -1).
 */
ELSA_INLINE v2f V2Down() {
    return (v2f){{0.0f, -1.0f}};
}

/**
 * @brief Creates and returns a 2-component vector pointing left (-1, 0).
 */
ELSA_INLINE v2f V2Left() {
	return (v2f){{-1.0f, 0.0f}};
}

/**
 * @brief Creates and returns a 2-component vector pointing right (1, 0).
 */
ELSA_INLINE v2f V2Right() {
	return (v2f){{1.0f, 0.0f}};
}

/**
* @brief Adds left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v2f V2Add(v2f left, v2f right) {
	return (v2f){{left.x + right.x, left.y + right.y}};
}


/**
* @brief Subtracts left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v2f V2Sub(v2f left, v2f right) {
	return (v2f){{left.x - right.x, left.y - right.y}};
}

/**
* @brief Multiplies left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v2f V2Mul(v2f left, v2f right) {
	return (v2f){{left.x * right.x, left.y * right.y}};
}

/**
* @brief Divides left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v2f V2Div(v2f left, v2f right) {
	return (v2f){{left.x / right.x, left.y / right.y}};
}

/**
 * @brief Returns the squared length of the provided vector.
 * 
 * @param vector The vector to retrieve the squared length of.
 * @return The squared length.
 */
ELSA_INLINE f32 V2LengthSquared(v2f vector) {
	return vector.x * vector.x + vector.y * vector.y;
}

/**
 * @brief Returns the length of the provided vector.
 * 
 * @param vector The vector to retrieve the length of.
 * @return The length.
 */
ELSA_INLINE f32 V2Length(v2f vector) {
	return Sqrt(V2LengthSquared(vector));
}

/**
 * @brief Normalizes the provided vector in place to a unit vector.
 * 
 * @param vector A pointer to the vector to be normalized.
 */
ELSA_INLINE void V2Normalize(v2f* vector) {
	const f32 length = V2Length(*vector);
	vector->x /= length;
	vector->y /= length;
}

/**
 * @brief Returns a normalized copy of the supplied vector.
 * 
 * @param vector The vector to be normalized.
 * @return A normalized copy of the supplied vector 
 */
ELSA_INLINE v2f V2Normalized(v2f vector) {
	V2Normalize(&vector);
	return vector;
}

/**
 * @brief Returns the distance between left and right.
 * 
 * @param left The first vector.
 * @param right The second vector.
 * @return The distance between left and right.
 */
ELSA_INLINE f32 V2Distance(v2f left, v2f right) {
	v2f d = (v2f){{left.x - right.x, left.y - right.y}};
	return V2Length(d);
}

// ------------------------------------------
// Vector 3
// ------------------------------------------

/**
 * @brief Creates and returns a 3-component vector with all components set to 0.0f.
 */
ELSA_INLINE v3f V3Zero() {
	return (v3f){{0.0f, 0.0f, 0.0f}};
}

/**
 * @brief Creates and returns a 3-component vector with all components set to 1.0f.
 */
ELSA_INLINE v3f V3One() {
	return (v3f){{1.0f, 1.0f, 1.0f}};
}

/**
* @brief Creates and returns a 3-component vector with all components set to the given value.
* @param scalar The value to set.
*/
ELSA_INLINE v3f V3Scalar(f32 scalar) {
	return (v3f){{scalar, scalar, scalar}};
}

/**
* @brief Creates and returns a 3-component vector with its components set to the given values.
* @param x The x value of the vector.
* @param y The y value of the vector.
* @param z The z value of the vector.
* @returns A new vec3
*/
ELSA_INLINE v3f V3Create(f32 x, f32 y, f32 z) {
	return (v3f){{x, y, z}};
}

/**
 * @brief Returns a new vec3 containing the x, y and z components of the 
 * supplied vec4, essentially dropping the w component.
 * 
 * @param vector The 4-component vector to extract from.
 * @returns A new vec3 
 */
ELSA_INLINE v3f V3FromV4(v4f vector) {
    return (v3f){{vector.x, vector.y, vector.z}};
}

/**
 * @brief Returns a new vec4 using vector as the x, y and z components and w for w.
 * 
 * @param vector The 3-component vector.
 * @param w The w component.
 * @returns A new vec4 
 */
ELSA_INLINE v4f V3ToV4(v3f vector, f32 w) {
    return (v4f){{vector.x, vector.y, vector.z, w}};
}

/**
 * @brief Creates and returns a 3-component vector pointing up (0, 1, 0).
 */
ELSA_INLINE v3f V3Up() {
    return (v3f){{0.0f, 1.0f, 0.0f}};
}

/**
 * @brief Creates and returns a 3-component vector pointing down (0, -1, 0).
 */
ELSA_INLINE v3f V3Down() {
    return (v3f){{0.0f, -1.0f, 0.0f}};
}

/**
 * @brief Creates and returns a 3-component vector pointing left (-1, 0, 0).
 */
ELSA_INLINE v3f V3Left() {
	return (v3f){{-1.0f, 0.0f, 0.0f}};
}

/**
 * @brief Creates and returns a 3-component vector pointing right (1, 0, 0).
 */
ELSA_INLINE v3f V3Right() {
	return (v3f){{1.0f, 0.0f, 0.0f}};
}

/**
 * @brief Creates and returns a 3-component vector pointing fowards (0, 0, -1).
 */
ELSA_INLINE v3f V3Forward() {
	return (v3f){{0.0f, 0.0f, -1.0f}};
}

/**
 * @brief Creates and returns a 3-component vector pointing backards (0, 0, 1).
 */
ELSA_INLINE v3f V3Backard() {
	return (v3f){{0.0f, 0.0f, 1.0f}};
}

/**
* @brief Adds left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3Add(v3f left, v3f right) {
	return (v3f){{left.x + right.x, left.y + right.y, left.z + right.z}};
}

/**
* @brief Adds left to scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3AddScalar(v3f left, f32 scalar) {
	return (v3f){{left.x + scalar, left.y + scalar, left.z + scalar}};
}


/**
* @brief Subtracts left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3Sub(v3f left, v3f right) {
	return (v3f){{left.x - right.x, left.y - right.y, left.z - right.z}};
}

/**
* @brief Substracts left to scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3SubScalar(v3f left, f32 scalar) {
	return (v3f){{left.x - scalar, left.y - scalar, left.z - scalar}};
}

/**
* @brief Multiplies left by right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3Mul(v3f left, v3f right) {
	return (v3f){{left.x * right.x, left.y * right.y, left.z * right.z}};
}

/**
* @brief Multiplies left by scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3MulScalar(v3f left, f32 scalar) {
	return (v3f){{left.x * scalar, left.y * scalar, left.z * scalar}};
}

/**
* @brief Divides left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3Div(v3f left, v3f right) {
	return (v3f){{left.x / right.x, left.y / right.y, left.z / right.z}};
}

/**
* @brief Divides left by scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v3f V3DivScalar(v3f left, f32 scalar) {
	return (v3f){{left.x / scalar, left.y / scalar, left.z / scalar}};
}

/**
 * @brief Returns the squared length of the provided vector.
 * 
 * @param vector The vector to retrieve the squared length of.
 * @return The squared length.
 */
ELSA_INLINE f32 V3LengthSquared(v3f vector) {
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

/**
 * @brief Returns the length of the provided vector.
 * 
 * @param vector The vector to retrieve the length of.
 * @return The length.
 */
ELSA_INLINE f32 V3Length(v3f vector) {
	return Sqrt(V3LengthSquared(vector));
}

/**
 * @brief Normalizes the provided vector in place to a unit vector.
 * 
 * @param vector A pointer to the vector to be normalized.
 */
ELSA_INLINE void V3Normalize(v3f* vector) {
	const f32 length = V3Length(*vector);
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

/**
 * @brief Returns a normalized copy of the supplied vector.
 * 
 * @param vector The vector to be normalized.
 * @return A normalized copy of the supplied vector 
 */
ELSA_INLINE v3f V3Normalized(v3f vector) {
	V3Normalize(&vector);
	return vector;
}

/**
 * @brief Returns the distance between left and right.
 * 
 * @param left The first vector.
 * @param right The second vector.
 * @return The distance between left and right.
 */
ELSA_INLINE f32 V3Distance(v3f left, v3f right) {
	v3f d = (v3f){{left.x - right.x, left.y - right.y, left.z - right.z}};
	return V3Length(d);
}

/**
 * @brief Returns the dot product between the provided vectors. Typically used
 * to calculate the difference in direction.
 * 
 * @param left The first vector.
 * @param right The second vector.
 * @return The dot product. 
 */
ELSA_INLINE f32 V3Dot(v3f left, v3f right) {
	return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

/**
 * @brief Calculates and returns the cross product of the supplied vectors.
 * The cross product is a new vector which is orthoganal to both provided vectors.
 * 
 * @param left The first vector.
 * @param right The second vector.
 * @return The cross product. 
 */
ELSA_INLINE v3f V3Cross(v3f left, v3f right) {
	return (v3f) {{left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x}};
}

// ------------------------------------------
// Vector 4
// ------------------------------------------

/**
 * @brief Creates and returns a new 4-element vector using the supplied values.
 * 
 * @param x The x value.
 * @param y The y value.
 * @param z The z value.
 * @param w The w value.
 * @return A new 4-element vector.
 */
ELSA_INLINE v4f V4Create(f32 x, f32 y, f32 z, f32 w) {
	v4f out_vector;
#ifdef ELSA_USE_SSE
	out_vector.InternalElementsSSE = _mm_setr_ps(x, y, z, w);
#else
	out_vector.x = x;
	out_vector.y = y;
	out_vector.z = z;
	out_vector.w = w;
#endif
	return out_vector;
}

/**
 * @brief Returns a new vec3 containing the x, y and z components of the 
 * supplied vec4, essentially dropping the w component.
 * 
 * @param vector The 4-component vector to extract from.
 * @return A new vec3 
 */
ELSA_INLINE v3f V4ToV3(v4f vector) {
	return (v3f){{vector.x, vector.y, vector.z}};
}

/**
 * @brief Returns a new vec4 using vector as the x, y and z components and w for w.
 * 
 * @param vector The 3-component vector.
 * @param w The w component.
 * @return A new vec4 
 */
ELSA_INLINE v4f V4FromV3(v3f vector, f32 w) {
#ifdef ELSA_USE_SSE
	v4f out_vector;
	out_vector.InternalElementsSSE = _mm_setr_ps(vector.x, vector.y, vector.z, w);
	return out_vector;
#else
	return (v4f){{vector.x, vector.y, vector.z, w}};
#endif
}

/**
 * @brief Creates and returns a 4-component vector with all components set to 0.0f.
 */
ELSA_INLINE v4f V4Zero() {
#ifdef ELSA_USE_SSE
	v4f out_vector;
	out_vector.InternalElementsSSE = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
	return out_vector;
#else
	return (v4f){{0.0f, 0.0f, 0.0f, 0.0f}};
#endif
}

/**
 * @brief Creates and returns a 4-component vector with all components set to 1.0f.
 */
ELSA_INLINE v4f V4One() {
#ifdef ELSA_USE_SSE
	v4f out_vector;
	out_vector.InternalElementsSSE = _mm_setr_ps(1.0f, 1.0f, 1.0f, 1.0f);
	return out_vector;
#else
	return (v4f){{1.0f, 1.0f, 1.0f, 1.0f}};
#endif
}

/**
* @brief Adds left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4Add(v4f left, v4f right) {
#ifdef ELSA_USE_SSE
	v4f out_vector;
	out_vector.InternalElementsSSE = _mm_add_ps(left.InternalElementsSSE, right.InternalElementsSSE);
	return out_vector;
#else
	return (v4f){{left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w}};
#endif
}

/**
* @brief Adds left to scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4AddScalar(v4f left, f32 scalar) {
	return (v4f){{left.x + scalar, left.y + scalar, left.z + scalar, left.w + scalar}};
}


/**
* @brief Subtracts left to right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4Sub(v4f left, v4f right) {
#ifdef ELSA_USE_SSE
	v4f out_vector;
	out_vector.InternalElementsSSE = _mm_sub_ps(left.InternalElementsSSE, right.InternalElementsSSE);
	return out_vector;
#else
	return (v4f){{left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w}};
#endif
}

/**
* @brief Subtracts left to scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4SubScalar(v4f left, f32 scalar) {
	return (v4f){{left.x - scalar, left.y - scalar, left.z - scalar, left.w - scalar}};
}

/**
* @brief Multiplies left by right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4Mul(v4f left, v4f right) {
#ifdef ELSA_USE_SSE
	v4f out_vector;
	out_vector.InternalElementsSSE = _mm_mul_ps(left.InternalElementsSSE, right.InternalElementsSSE);
	return out_vector;
#else
	return (v4f){{left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w}};
#endif
}

/**
* @brief Multiplies left by scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4MulScalar(v4f left, f32 scalar) {
	return (v4f){{left.x * scalar, left.y * scalar, left.z * scalar, left.w * scalar}};
}

/**
* @brief Divides left by right and returns a copy of the result.
*
* @param left The first vector.
* @param right The second vector.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4Div(v4f left, v4f right) {
#ifdef ELSA_USE_SSE
	v4f out_vector;
	out_vector.InternalElementsSSE = _mm_div_ps(left.InternalElementsSSE, right.InternalElementsSSE);
	return out_vector;
#else
	return (v4f){{left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w}};
#endif
}

/**
* @brief Divides left by scalar and returns a copy of the result.
*
* @param left The first vector.
* @param scalar The scalar value.
* @returns The resulting vector.
*/
ELSA_INLINE v4f V4DivScalar(v4f left, f32 scalar) {
	return (v4f){{left.x / scalar, left.y / scalar, left.z / scalar, left.w / scalar}};
}

/**
 * @brief Returns the dot product between the provided vectors. Typically used
 * to calculate the difference in direction.
 * 
 * @param left The first vector.
 * @param right The second vector.
 * @return The dot product. 
 */
ELSA_INLINE f32 V4Dot(v4f left, v4f right) {
	f32 result = 0.0f;
#ifdef ELSA_USE_SSE
	__m128 SSEResultOne = _mm_mul_ps(left.InternalElementsSSE, right.InternalElementsSSE);
    __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    _mm_store_ss(&result, SSEResultOne);
#else
	result = (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);
#endif
	return result;
}

/**
 * @brief Returns the squared length of the provided vector.
 * 
 * @param vector The vector to retrieve the squared length of.
 * @return The squared length.
 */
ELSA_INLINE f32 V4LengthSquared(v4f vector) {
	return V4Dot(vector, vector);
}

/**
 * @brief Returns the length of the provided vector.
 * 
 * @param vector The vector to retrieve the length of.
 * @return The length.
 */
ELSA_INLINE f32 V4Length(v4f vector) {
	return Sqrt(V4LengthSquared(vector));
}

/**
 * @brief Normalizes the provided vector in place to a unit vector.
 * 
 * @param vector A pointer to the vector to be normalized.
 */
ELSA_INLINE void V4Normalize(v4f* vector) {
	const f32 length = V4Length(*vector);
	if (length != 0.0f)
	{
		f32 multiplier = 1.0f / length;
		
#ifdef ELSA_USE_SSE
		__m128 SSEMultiplier = _mm_set1_ps(multiplier);
		vector->InternalElementsSSE = _mm_mul_ps(vector->InternalElementsSSE, SSEMultiplier);
#else
		vector->x *= multiplier;
		vector->y *= multiplier;
		vector->z *= multiplier;
		vector->w *= multiplier;
#endif
	}
}

/**
 * @brief Returns a normalized copy of the supplied vector.
 * 
 * @param vector The vector to be normalized.
 * @return A normalized copy of the supplied vector 
 */
ELSA_INLINE v4f V4Normalized(v4f vector) {
	V4Normalize(&vector);
	return vector;
}

/**
 * @brief Returns the distance between left and right.
 * 
 * @param left The first vector.
 * @param right The second vector.
 * @return The distance between left and right.
 */
ELSA_INLINE f32 V4Distance(v4f left, v4f right) {
	v4f d = V4Sub(left, right);
	return V4Length(d);
}

// ------------------------------------------
// SSE Stuff
// ------------------------------------------
#ifdef ELSA_USE_SSE
ELSA_INLINE __m128 LinearCombineSSE(__m128 left, m4f right) {
	__m128 result;
    result = _mm_mul_ps(_mm_shuffle_ps(left, left, 0x00), right.Columns[0]);
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(left, left, 0x55), right.Columns[1]));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(left, left, 0xaa), right.Columns[2]));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(left, left, 0xff), right.Columns[3]));
	return result;
}
#endif

// ------------------------------------------
// 4x4 Matrix
// ------------------------------------------

/**
 * @brief Creates and returns an identity matrix
 * @return A new identity matrix 
 */
ELSA_INLINE m4f M4Identity() {
	m4f result;
	f32 Diagonal = 1.0f;
	
	result.Elements[0][0] = Diagonal;
    result.Elements[1][1] = Diagonal;
    result.Elements[2][2] = Diagonal;
    result.Elements[3][3] = Diagonal;
	
	return result;
}

/**
 * @brief Creates and returns an identity matrix with the given scalar
* @param diagonal The diagonal
*
 * @return A new identity matrix 
 */
ELSA_INLINE m4f M4Diagonal(f32 diagonal) {
	m4f result;
	
	result.Elements[0][0] = diagonal;
    result.Elements[1][1] = diagonal;
    result.Elements[2][2] = diagonal;
    result.Elements[3][3] = diagonal;
	
	return result;
}

/**
* @brief Transposes the given matrix.
* @param matrix The matrix to tranpose
*
* @returns The transposed matrix.
*/
ELSA_INLINE m4f M4Transpose(m4f matrix) {
	m4f result = matrix;
	
#ifdef ELSA_USE_SSE
	_MM_TRANSPOSE4_PS(result.Columns[0], result.Columns[1], result.Columns[2], result.Columns[3]);
#else
	for (i32 i = 0; i < 4; i++)
	{
		for (i32 j = 0; j < 4; j++)
		{
			result.Elements[j][i] = matrix.Elements[i][j];
		}
	}
#endif
	
	return result;
}

/**
* @brief Adds left and right.
* @param left The left matrix.
* @param right The right matrix.

* @returns The result matrix.
*/
ELSA_INLINE m4f M4Add(m4f left, m4f right) {
	m4f result;
	
#ifdef ELSA_USE_SSE
	result.Columns[0] = _mm_add_ps(left.Columns[0], right.Columns[0]);
    result.Columns[1] = _mm_add_ps(left.Columns[1], right.Columns[1]);
    result.Columns[2] = _mm_add_ps(left.Columns[2], right.Columns[2]);
    result.Columns[3] = _mm_add_ps(left.Columns[3], right.Columns[3]);
#else
	for (i32 i = 0; i < 4; i++)
	{
		for (i32 j = 0; j < 4; j++)
		{
			result.Elements[i][j] = left.Elements[i][j] + right.Elements[i][j];
		}
	}
#endif
	
	return result;
}

/**
* @brief Substracts left and right.
* @param left The left matrix.
* @param right The right matrix.

* @returns The result matrix.
*/
ELSA_INLINE m4f M4Sub(m4f left, m4f right) {
	m4f result;
	
#ifdef ELSA_USE_SSE
	result.Columns[0] = _mm_sub_ps(left.Columns[0], right.Columns[0]);
    result.Columns[1] = _mm_sub_ps(left.Columns[1], right.Columns[1]);
    result.Columns[2] = _mm_sub_ps(left.Columns[2], right.Columns[2]);
    result.Columns[3] = _mm_sub_ps(left.Columns[3], right.Columns[3]);
#else
	for (i32 i = 0; i < 4; i++)
	{
		for (i32 j = 0; j < 4; j++)
		{
			result.Elements[i][j] = left.Elements[i][j] - right.Elements[i][j];
		}
	}
#endif
	
	return result;
}

/**
* @brief Multiplies left and right.
* @param left The left matrix.
* @param right The right matrix.

* @returns The result matrix.
*/
ELSA_INLINE m4f M4Mul(m4f left, m4f right) {
	m4f result;
	
#ifdef ELSA_USE_SSE
	result.Columns[0] = LinearCombineSSE(right.Columns[0], left);
    result.Columns[1] = LinearCombineSSE(right.Columns[1], left);
    result.Columns[2] = LinearCombineSSE(right.Columns[2], left);
    result.Columns[3] = LinearCombineSSE(right.Columns[3], left);
#else
	for (i32 i = 0; i < 4; i++)
	{
		for (i32 j = 0; j < 4; j++)
		{
			f32 sum = 0.0f;
			for (i32 e = 0; e < 4; e++)
			{
				sum += left.Elements[e][j] * right.Elements[i][e];
			}
			
			result.Elements[i][j] = sum;
		}
	}
#endif
	
	return result;
}

/**
* @brief Multiplies left and scalar.
* @param left The left matrix.
* @param scalar The scalar value.

* @returns The result matrix.
*/
ELSA_INLINE m4f M4MulScalar(m4f left, f32 scalar) {
	m4f result;
	
#ifdef ELSA_USE_SSE
	__m128 SSEScalar = _mm_set1_ps(scalar);
    result.Columns[0] = _mm_mul_ps(left.Columns[0], SSEScalar);
    result.Columns[1] = _mm_mul_ps(left.Columns[1], SSEScalar);
    result.Columns[2] = _mm_mul_ps(left.Columns[2], SSEScalar);
    result.Columns[3] = _mm_mul_ps(left.Columns[3], SSEScalar);
#else
	for (i32 i = 0; i < 4; i++)
	{
		for (i32 j = 0; j < 4; j++)
		{
			result.Elements[i][j] = left.Elements[i][j] * scalar;
		}
	}
#endif
	
	return result;
}

/**
* @brief Multiplies left and vector.
* @param left The left matrix.
* @param vector The right vector.
*
* @returns The result vector.
*/
ELSA_INLINE v4f M4MulV4(m4f left, v4f vector) {
	v4f result;
	
#ifdef ELSA_USE_SSE
	result.InternalElementsSSE = LinearCombineSSE(vector.InternalElementsSSE, left);
#else
	i32 Columns, Rows;
    for(Rows = 0; Rows < 4; ++Rows)
    {
        f32 Sum = 0;
        for(Columns = 0; Columns < 4; ++Columns)
        {
            Sum += left.Elements[Columns][Rows] * vector.Elements[Columns];
        }
		
        result.Elements[Rows] = Sum;
    }
#endif
	
	return result;
}

/**
* @brief Divides left and scalar.
* @param left The left matrix.
* @param scalar The scalar value.

* @returns The result matrix.
*/
ELSA_INLINE m4f M4DivScalar(m4f left, f32 scalar) {
	m4f result;
	
#ifdef ELSA_USE_SSE
	__m128 SSEScalar = _mm_set1_ps(scalar);
    result.Columns[0] = _mm_div_ps(left.Columns[0], SSEScalar);
    result.Columns[1] = _mm_div_ps(left.Columns[1], SSEScalar);
    result.Columns[2] = _mm_div_ps(left.Columns[2], SSEScalar);
    result.Columns[3] = _mm_div_ps(left.Columns[3], SSEScalar);
#else
	for (i32 i = 0; i < 4; i++)
	{
		for (i32 j = 0; j < 4; j++)
		{
			result.Elements[i][j] = left.Elements[i][j] / scalar;
		}
	}
#endif
	
	return result;
}

/**
 * @brief Creates and returns an orthographic projection matrix. Typically used to
 * render flat or 2D scenes.
 * 
 * @param left The left side of the view frustum.
 * @param right The right side of the view frustum.
 * @param bottom The bottom side of the view frustum.
 * @param top The top side of the view frustum.
 * @param near The near clipping plane distance.
 * @param far The far clipping plane distance.
*
 * @returns A new orthographic projection matrix. 
 */
ELSA_INLINE m4f M4Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
	m4f result = M4Identity();
	
	result.Elements[0][0] = 2.0f / (right - left);
    result.Elements[1][1] = 2.0f / (top - bottom);
    result.Elements[2][2] = 2.0f / (near - far);
    result.Elements[3][3] = 1.0f;
	
    result.Elements[3][0] = (left + right) / (left - right);
    result.Elements[3][1] = (bottom + top) / (bottom - top);
    result.Elements[3][2] = (far + near) / (near - far);
	
	return result;
}

/**
 * @brief Creates and returns a perspective matrix. Typically used to render 3d scenes.
 * 
 * @param fov_radians The field of view in radians.
 * @param aspect_ratio The aspect ratio.
 * @param near The near clipping plane distance.
 * @param far The far clipping plane distance.
*
 * @returns A new perspective matrix. 
 */
ELSA_INLINE m4f M4Perspective(f32 fov_radians, f32 aspect_ratio, f32 near, f32 far) {
	m4f result = M4Identity();
	
	f32 Cotangent = 1.0f / Tan(fov_radians);
	
    result.Elements[0][0] = Cotangent / aspect_ratio;
    result.Elements[1][1] = Cotangent;
    result.Elements[2][3] = -1.0f;
    result.Elements[2][2] = (near + far) / (near - far);
    result.Elements[3][2] = (2.0f * near * far) / (near - far);
    result.Elements[3][3] = 0.0f;
	
	return result;
}

/**
 * @brief Creates and returns a look-at matrix, or a matrix looking 
 * at target from the perspective of position.
 * 
 * @param position The position of the matrix.
 * @param target The position to "look at".
 * @param up The up vector.
 * @return A matrix looking at target from the perspective of position. 
 */
ELSA_INLINE m4f M4LookAt(v3f eye, v3f center, v3f up) {
	m4f result = M4Identity();
	
	v3f F = V3Normalized(V3Sub(center, eye));
	v3f S = V3Normalized(V3Cross(F, up));
	v3f U = V3Cross(S, F);
	
    result.Elements[0][0] = S.x;
    result.Elements[0][1] = U.x;
    result.Elements[0][2] = -F.x;
    result.Elements[0][3] = 0.0f;
	
    result.Elements[1][0] = S.y;
    result.Elements[1][1] = U.y;
    result.Elements[1][2] = -F.y;
    result.Elements[1][3] = 0.0f;
	
    result.Elements[2][0] = S.z;
    result.Elements[2][1] = U.z;
    result.Elements[2][2] = -F.z;
    result.Elements[2][3] = 0.0f;
	
    result.Elements[3][0] = -V3Dot(S, eye);
    result.Elements[3][1] = -V3Dot(U, eye);
    result.Elements[3][2] = V3Dot(F, eye);
    result.Elements[3][3] = 1.0f;
	
	return result;
}

/**
 * @brief Creates and returns a translation matrix from the given position.
 * 
 * @param position The position to be used to create the matrix.
 * @return A newly created translation matrix.
 */
ELSA_INLINE m4f M4Translate(v3f position) {
	m4f result = M4Identity();
	result.Elements[3][0] = position.x;
    result.Elements[3][1] = position.y;
    result.Elements[3][2] = position.z;
	return result;
}

/**
 * @brief Returns a scale matrix using the provided scale.
 * 
 * @param scale The 3-component scale.
 * @return A scale matrix.
 */
ELSA_INLINE m4f M4Scale(v3f scale) {
	m4f result = M4Identity();
	result.Elements[0][0] = scale.x;
    result.Elements[1][1] = scale.y;
    result.Elements[2][2] = scale.z;
	return result;
}

/**
 * @brief Creates a rotation matrix from the provided angle and axis.
 * 
 * @param angle The rotation angle in degrees.
* @param axis The rotation axis.
 * @return A rotation matrix.
 */
ELSA_INLINE m4f M4Rotate(f32 angle, v3f axis) {
	m4f result = M4Identity();
	
	axis = V3Normalized(axis);
	
    f32 SinTheta = Sin(angle * (E_PI / 180.0f));
    f32 CosTheta = Cos(angle * (E_PI / 180.0f));
    f32 CosValue = 1.0f - CosTheta;
	
    result.Elements[0][0] = (axis.x * axis.x * CosValue) + CosTheta;
    result.Elements[0][1] = (axis.x * axis.y * CosValue) + (axis.z * SinTheta);
    result.Elements[0][2] = (axis.x * axis.z * CosValue) - (axis.y * SinTheta);
	
    result.Elements[1][0] = (axis.y * axis.x * CosValue) - (axis.z * SinTheta);
    result.Elements[1][1] = (axis.y * axis.y * CosValue) + CosTheta;
    result.Elements[1][2] = (axis.y * axis.z * CosValue) + (axis.x * SinTheta);
	
    result.Elements[2][0] = (axis.z * axis.x * CosValue) + (axis.y * SinTheta);
    result.Elements[2][1] = (axis.z * axis.y * CosValue) - (axis.x * SinTheta);
    result.Elements[2][2] = (axis.z * axis.z * CosValue) + CosTheta;
	
	return result;
}

// ------------------------------------------
// Quaternions
// ------------------------------------------

/**
 * @brief Creates an identity quaternion.
 * 
 * @returns An identity quaternion.
 */
ELSA_INLINE q4f Q4Identity() {
#ifdef ELSA_USE_SSE
	q4f result;
	result.InternalElementsSSE = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
	return result;
#else
	return (q4f){{0.0f, 0.0f, 0.0f, 1.0f}};
#endif
}

/**
* @brief Creates a quaternion.
*
* @param x The x component of the quaternion.
* @param y The y component of the quaternion.
* @param z The z component of the quaternion.
* @param w The w component of the quaternion.
* @returns The created quaternion.
*/
ELSA_INLINE q4f Q4Create(f32 x, f32 y, f32 z, f32 w) {
#ifdef ELSA_USE_SSE
	q4f result;
	result.InternalElementsSSE = _mm_setr_ps(x, y, z, w);
	return result;
#else 
	return (q4f){{x, y, z, w}};
#endif
}

/**
* @brief Adds left to right.
*
* @param left The left quaternion
* @param right The right quaternion
* @returns The result quaternion
*/
ELSA_INLINE q4f Q4Add(q4f left, q4f right) {
	q4f result;
#ifdef ELSA_USE_SSE
	result.InternalElementsSSE = _mm_add_ps(left.InternalElementsSSE, right.InternalElementsSSE);
#else
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	result.w = left.w + right.w;
#endif
	return result;
}

/**
* @brief Subtracts left to right.
*
* @param left The left quaternion
* @param right The right quaternion
* @returns The result quaternion
*/
ELSA_INLINE q4f Q4Sub(q4f left, q4f right) {
	q4f result;
#ifdef ELSA_USE_SSE
	result.InternalElementsSSE = _mm_sub_ps(left.InternalElementsSSE, right.InternalElementsSSE);
#else
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	result.w = left.w - right.w;
#endif
	return result;
}

/**
* @brief Multiplies left by right.
*
* @param left The left quaternion
* @param right The right quaternion
* @returns The result quaternion
*/
ELSA_INLINE q4f Q4Mul(q4f left, q4f right) {
	q4f result;
#ifdef ELSA_USE_SSE
	__m128 SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(left.InternalElementsSSE, left.InternalElementsSSE, _MM_SHUFFLE(0, 0, 0, 0)), _mm_setr_ps(0.f, -0.f, 0.f, -0.f));
    __m128 SSEResultTwo = _mm_shuffle_ps(right.InternalElementsSSE, right.InternalElementsSSE, _MM_SHUFFLE(0, 1, 2, 3));
    __m128 SSEResultThree = _mm_mul_ps(SSEResultTwo, SSEResultOne);
	
    SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(left.InternalElementsSSE, left.InternalElementsSSE, _MM_SHUFFLE(1, 1, 1, 1)) , _mm_setr_ps(0.f, 0.f, -0.f, -0.f));
    SSEResultTwo = _mm_shuffle_ps(right.InternalElementsSSE, right.InternalElementsSSE, _MM_SHUFFLE(1, 0, 3, 2));
    SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));
	
    SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(left.InternalElementsSSE, left.InternalElementsSSE, _MM_SHUFFLE(2, 2, 2, 2)), _mm_setr_ps(-0.f, 0.f, 0.f, -0.f));
    SSEResultTwo = _mm_shuffle_ps(right.InternalElementsSSE, right.InternalElementsSSE, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));
	
    SSEResultOne = _mm_shuffle_ps(left.InternalElementsSSE, left.InternalElementsSSE, _MM_SHUFFLE(3, 3, 3, 3));
    SSEResultTwo = _mm_shuffle_ps(right.InternalElementsSSE, right.InternalElementsSSE, _MM_SHUFFLE(3, 2, 1, 0));
    result.InternalElementsSSE = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));
#else
	result.X = (left.x * right.w) + (left.y * right.z) - (left.z * right.y) + (left.w * right.x);
    result.Y = (-left.x * right.z) + (left.y * right.w) + (left.z * right.x) + (left.w * right.y);
    result.Z = (left.x * right.y) - (left.y * right.x) + (left.z * right.w) + (left.w * right.z);
    result.W = (-left.x * right.x) - (left.y * right.y) - (left.z * right.z) + (left.w * right.w);
#endif
	return result;
}

/**
* @brief Multiplies left by scalar.
*
* @param left The left quaternion
* @param scalar The scalar value.
* @returns The result quaternion
*/
ELSA_INLINE q4f Q4MultiplyScalar(q4f left, f32 scalar) {
	q4f result;
#ifdef ELSA_USE_SSE
	__m128 scal = _mm_set1_ps(scalar);
	result.InternalElementsSSE = _mm_mul_ps(left.InternalElementsSSE, scal);
#else
	result.x = left.x * scalar;
	result.y = left.y * scalar;
	result.z = left.z * scalar;
	result.w = left.w * scalar;
#endif
	return result;
}

/**
* @brief Divides left by scalar.
*
* @param left The left quaternion
* @param scalar The scalar value.
* @returns The result quaternion
*/
ELSA_INLINE q4f Q4DivideScalar(q4f left, f32 scalar) {
	q4f result;
#ifdef ELSA_USE_SSE
	__m128 scal = _mm_set1_ps(scalar);
	result.InternalElementsSSE = _mm_div_ps(left.InternalElementsSSE, scal);
#else
	result.x = left.x / scalar;
	result.y = left.y / scalar;
	result.z = left.z / scalar;
	result.w = left.w / scalar;
#endif
	return result;
}

/**
* @brief The dot product between left and right.
*
* @param left The left quaternion.
* @param right The right quaternion.
* @returns The result quaternion
*/
ELSA_INLINE f32 Q4Dot(q4f left, q4f right) {
	f32 result;
#ifdef ELSA_USE_SSE
	__m128 SSEResultOne = _mm_mul_ps(left.InternalElementsSSE, right.InternalElementsSSE);
    __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    _mm_store_ss(&result, SSEResultOne);
#else
	result = (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);
#endif
	return result;
}

/**
 * @brief Returns the normal of the provided quaternion.
 * 
 * @param q The quaternion.
 * @returns The normal of the provided quaternion.
 */
ELSA_INLINE f32 Q4Normal(q4f q) {
	return Sqrt(Q4Dot(q, q));
}

/**
 * @brief Returns the conjugate of the provided quaternion. That is,
 * The x, y and z elements are negated, but the w element is untouched.
 * 
 * @param q The quaternion to obtain a conjugate of.
 * @return The conjugate quaternion.
 */
ELSA_INLINE q4f Q4Conjugate(q4f q) {
	return (q4f){{-q.x, -q.y, -q.z, q.w}};
}

/**
 * @brief Returns a normalized copy of the provided quaternion.
 * 
 * @param q The quaternion to normalize.
 * @return A normalized copy of the provided quaternion.
 */
ELSA_INLINE q4f Q4Normalize(q4f q) {
	q4f result;
	f32 norm = Q4Normal(q);
#ifdef ELSA_USE_SSE
	__m128 multiplier = _mm_set1_ps(norm);
	result.InternalElementsSSE = _mm_div_ps(q.InternalElementsSSE, multiplier);
#else
	result.x = q.x / norm;
	result.y = q.y / norm;
	result.z = q.z / norm;
	result.w = q.w / norm;
#endif
	return result;
}

/**
 * @brief Returns an inverse copy of the provided quaternion.
 * 
 * @param q The quaternion to invert.
 * @return An inverse copy of the provided quaternion.
 */
ELSA_INLINE q4f Q4Inverse(q4f q) {
	return Q4Normalize(Q4Conjugate(q));
}

/**
 * @brief Creates a rotation matrix from the given quaternion.
 * 
 * @param q The quaternion to be used.
 * @return A rotation matrix.
 */
ELSA_INLINE m4f Q4ToM4(q4f q) {
	m4f Result = M4Identity();
	q4f NormalizedQuaternion = Q4Normalize(q);
	
	f32 XX, YY, ZZ, XY, XZ, YZ, WX, WY, WZ;
	
    XX = NormalizedQuaternion.x * NormalizedQuaternion.x;
    YY = NormalizedQuaternion.y * NormalizedQuaternion.y;
    ZZ = NormalizedQuaternion.z * NormalizedQuaternion.z;
    XY = NormalizedQuaternion.x * NormalizedQuaternion.y;
    XZ = NormalizedQuaternion.x * NormalizedQuaternion.z;
    YZ = NormalizedQuaternion.y * NormalizedQuaternion.z;
    WX = NormalizedQuaternion.w * NormalizedQuaternion.x;
    WY = NormalizedQuaternion.w * NormalizedQuaternion.y;
    WZ = NormalizedQuaternion.w * NormalizedQuaternion.z;
	
    Result.Elements[0][0] = 1.0f - 2.0f * (YY + ZZ);
    Result.Elements[0][1] = 2.0f * (XY + WZ);
    Result.Elements[0][2] = 2.0f * (XZ - WY);
    Result.Elements[0][3] = 0.0f;
	
    Result.Elements[1][0] = 2.0f * (XY - WZ);
    Result.Elements[1][1] = 1.0f - 2.0f * (XX + ZZ);
    Result.Elements[1][2] = 2.0f * (YZ + WX);
    Result.Elements[1][3] = 0.0f;
	
    Result.Elements[2][0] = 2.0f * (XZ + WY);
    Result.Elements[2][1] = 2.0f * (YZ - WX);
    Result.Elements[2][2] = 1.0f - 2.0f * (XX + YY);
    Result.Elements[2][3] = 0.0f;
	
    Result.Elements[3][0] = 0.0f;
    Result.Elements[3][1] = 0.0f;
    Result.Elements[3][2] = 0.0f;
    Result.Elements[3][3] = 1.0f;
	
	return Result;
}

/**
 * @brief Creates a quaternion from the given axis and angle.
 * 
 * @param axis The axis of rotation.
 * @param angle The angle of rotation.
 * @param normalize Indicates if the quaternion should be normalized.
 * @return A new quaternion. 
 */
ELSA_INLINE q4f Q4FromAxis(v3f axis, f32 angle, b8 normalize) {
	const f32 half_angle = 0.5f * angle;
    f32 s = Sin(half_angle);
    f32 c = Cos(half_angle);
	
#ifdef ELSA_USE_SSE
	q4f q;
	q.InternalElementsSSE = _mm_setr_ps(s * axis.x, s * axis.y, s * axis.z, c);
#else
	q4f q = (q4f){{s * axis.x, s * axis.y, s * axis.z, c}};
#endif
    if (normalize) {
        return Q4Normalize(q);
    }
    return q;
}

/**
 * @brief Calculates spherical linear interpolation of a given percentage
 * between two quaternions.
 * 
 * @param q_0 The first quaternion.
 * @param q_1 The second quaternion.
 * @param percentage The percentage of interpolation, typically a value from 0.0f-1.0f.
 * @return An interpolated quaternion. 
 */
ELSA_INLINE q4f Q4Slerp(q4f q_0, q4f q_1, f32 percentage) {
	q4f out_quaternion;
    // Source: https://en.wikipedia.org/wiki/Slerp
    // Only unit quaternions are valid rotations.
    // Normalize to avoid undefined behavior.
    q4f v0 = Q4Normalize(q_0);
    q4f v1 = Q4Normalize(q_1);
	
    // Compute the cosine of the angle between the two vectors.
    f32 dot = Q4Dot(v0, v1);
	
    // If the dot product is negative, slerp won't take
    // the shorter path. Note that v1 and -v1 are equivalent when
    // the negation is applied to all four components. Fix by
    // reversing one quaternion.
    if (dot < 0.0f) {
        v1.x = -v1.x;
        v1.y = -v1.y;
        v1.z = -v1.z;
        v1.w = -v1.w;
        dot = -dot;
    }
	
    const f32 DOT_THRESHOLD = 0.9995f;
    if (dot > DOT_THRESHOLD) {
        // If the inputs are too close for comfort, linearly interpolate
        // and normalize the result.
        out_quaternion = Q4Create(
								  v0.x + ((v1.x - v0.x) * percentage),
								  v0.y + ((v1.y - v0.y) * percentage),
								  v0.z + ((v1.z - v0.z) * percentage),
								  v0.w + ((v1.w - v0.w) * percentage));
		
        return Q4Normalize(out_quaternion);
    }
	
    // Since dot is in range [0, DOT_THRESHOLD], acos is safe
    f32 theta_0 = Acos(dot);          // theta_0 = angle between input vectors
    f32 theta = theta_0 * percentage;  // theta = angle between v0 and result
    f32 sin_theta = Sin(theta);       // compute this value only once
    f32 sin_theta_0 = Sin(theta_0);   // compute this value only once
	
    f32 s0 = Cos(theta) - dot * sin_theta / sin_theta_0;  // == sin(theta_0 - theta) / sin(theta_0)
    f32 s1 = sin_theta / sin_theta_0;
	
    return Q4Create(
					(v0.x * s0) + (v1.x * s1),
					(v0.y * s0) + (v1.y * s1),
					(v0.z * s0) + (v1.z * s1),
					(v0.w * s0) + (v1.w * s1));
}

/**
 * @brief Converts provided degrees to radians.
 * 
 * @param degrees The degrees to be converted.
 * @return The amount in radians.
 */
ELSA_INLINE f32 DegToRad(f32 degrees) {
	return degrees * E_DEG2RAD_MULTIPLIER;
}

/**
 * @brief Converts provided radians to degrees.
 * 
 * @param radians The radians to be converted.
 * @return The amount in degrees.
 */
ELSA_INLINE f32 RadToDeg(f32 radians) {
	return radians * E_RAD2DEG_MULTIPLIER;
}

#endif