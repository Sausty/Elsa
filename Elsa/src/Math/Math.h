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
#include <Math/MathTypes.h>

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
ELSA_API f32 V4Dot(v4f left, v4f right) {
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

#endif