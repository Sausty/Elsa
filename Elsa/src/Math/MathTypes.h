/**
 * @file MathTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief Contains various math types required for the engine.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_MATH_TYPES_H
#define ELSA_MATH_TYPES_H

#include <Defines.h>

#ifdef _MSC_VER
#ifdef __SSE__
#define ELSA_USE_SSE 1
#endif
#endif

#ifdef ELSA_USE_SSE
#include <xmmintrin.h>
#endif

/**
 * @brief A 2-element floating point vector.
 */
typedef union vec2f {
	f32 Elements[2];
	struct {
		union {
			/** @brief The first element. */
            f32 x,
			/** @brief The first element. */
			r,
			/** @brief The first element. */
			s,
			/** @brief The first element. */
			u;
		};
		union {
			/** @brief The second element. */
            f32 y,
			/** @brief The second element. */
			g,
			/** @brief The second element. */
			t,
			/** @brief The second element. */
			v;
		};
	};
} v2f;

/**
 * @brief A 3-element floating point vector.
 */
typedef union vec3f {
	f32 Elements[3];
	struct {
		union {
			/** @brief The first element. */
            f32 x,
			/** @brief The first element. */
			r,
			/** @brief The first element. */
			s,
			/** @brief The first element. */
			u;
		};
		union {
			/** @brief The second element. */
            f32 y,
			/** @brief The second element. */
			g,
			/** @brief The second element. */
			t,
			/** @brief The second element. */
			v;
		};
		union {
            /** @brief The third element. */
            f32 z,
			/** @brief The third element. */
			b,
			/** @brief The third element. */
			p,
			/** @brief The third element. */
			w;
        };
	};
} v3f;

/**
 * @brief A 4-element floating point vector.
 */
typedef union vec4f {
	f32 Elements[4];
	struct {
		union {
			/** @brief The first element. */
            f32 x,
			/** @brief The first element. */
			r,
			/** @brief The first element. */
			s,
			/** @brief The first element. */
			u;
		};
		union {
			/** @brief The second element. */
            f32 y,
			/** @brief The second element. */
			g,
			/** @brief The second element. */
			t,
			/** @brief The second element. */
			v;
		};
		union {
            /** @brief The third element. */
            f32 z,
			/** @brief The third element. */
			b,
			/** @brief The third element. */
			p;
        };
		union {
			/** @brief The fourth element. */
			f32 w,
			/** @brief The fourth element. */
			a,
			/** @brief The fourth element. */
			q;
		};
	};
	
#ifdef ELSA_USE_SSE
	__m128 InternalElementsSSE;
#endif
} v4f;

/** @brief A quaternion, used to represent rotational orientation. */
typedef v4f q4f;

/** @brief a floating point 4x4 matrix, typically used to represent object transformations. Column-major. */
typedef union m4f {
	/** @brief The matrix elements */
	f32 Data[4][4];
	
#ifdef ELSA_USE_SSE
	__m128 Columns[4];
#endif
} m4f;

/**
 * @brief Represents the transform of an object in the world.
 * Transforms can have a parent whose own transform is then
 * taken into account.
 */
typedef struct Transform {
	/** @brief The position in the world. */
	v3f Position;
	
	/** @brief The rotation in the world. */
	q4f Rotation;
	
	/** @brief The scale in the world. */
	v3f Scale;
	
	/**
     * @brief Indicates if the position, rotation or scale have changed,
     * indicating that the local matrix needs to be recalculated.
     */
	b8 IsDirty;
	
	/**
     * @brief The local transformation matrix, updated whenever
     * the position, rotation or scale have changed.
     */
	m4f Local;
	
	/** @brief A pointer to a parent transform if one is assigned. Can also be null. */
	struct Transform* Parent;
} Transform;

#endif