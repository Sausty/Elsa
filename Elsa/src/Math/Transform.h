/**
 * @file Math.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains definitions for various transform functions.
 * @version 1.0
 * @date 2022-06-27
 */
#ifndef ELSA_TRANSFORM_H
#define ELSA_TRANSFORM_H

#include <Defines.h>
#include <Math/MathTypes.h>

/**
 * @brief Creates and returns a new transform, using a zero
 * vector for position, identity quaternion for rotation, and
 * a one vector for scale. Also has a null parent. Marked dirty
 * by default.
 */
ELSA_API Transform TransformCreate();

/**
 * @brief Creates a transform from the given position.
 * Uses a zero rotation and a one scale.
 *
 * @param position The position to be used.
 * @return A new transform.
 */
ELSA_API Transform TransformFromPosition(v3f pos);

/**
 * @brief Creates a transform from the given rotation.
 * Uses a zero position and a one scale.
 *
 * @param rotation The rotation to be used.
 * @return A new transform.
 */

ELSA_API Transform TransformFromRotation(q4f rotation);

/**
 * @brief Creates a transform from the given position and rotation.
 * Uses a one scale.
 *
 * @param position The position to be used.
 * @param rotation The rotation to be used.
 * @return A new transform.
 */
ELSA_API Transform TransformFromPositionRotation(v3f position, q4f rotation);

/**
 * @brief Creates a transform from the given position, rotation and scale.
 *
 * @param position The position to be used.
 * @param rotation The rotation to be used.
 * @param scale The scale to be used.
 * @return A new transform.
 */
ELSA_API Transform TransformFromPositionRotationScale(v3f position, q4f rotation, v3f scale);

/**
 * @brief Returns a pointer to the provided transform's parent.
 *
 * @param t A pointer to the transform whose parent to retrieve.
 * @return A pointer to the parent transform.
 */
ELSA_API Transform* TransformGetParent(Transform* t);

/**
 * @brief Sets the parent of the provided transform.
 *
 * @param t A pointer to the transform whose parent will be set.
 * @param parent A pointer to the parent transform.
 */
ELSA_API void TransformSetParent(Transform* t, Transform* parent);

/**
 * @brief Returns the position of the given transform.
 *
 * @param t A constant pointer whose position to get.
 * @return A copy of the position.
 */
ELSA_API v3f TransformGetPosition(const Transform* t);

/**
 * @brief Sets the position of the given transform.
 *
 * @param t A pointer to the transform to be updated.
 * @param position The position to be set.
 */
ELSA_API void TransformSetPosition(Transform* t, v3f position);

/**
 * @brief Applies a translation to the given transform. Not the
 * same as setting.
 *
 * @param t A pointer to the transform to be updated.
 * @param translation The translation to be applied.
 */
ELSA_API void TransformTranslate(Transform* t, v3f translation);

/**
 * @brief Returns the rotation of the given transform.
 *
 * @param t A constant pointer whose rotation to get.
 * @return A copy of the rotation.
 */
ELSA_API q4f TransformGetRotation(Transform* t);

/**
 * @brief Sets the rotation of the given transform.
 *
 * @param t A pointer to the transform to be updated.
 * @param rotation The rotation to be set.
 */
ELSA_API void TransformSetRotation(Transform* t, q4f rotation);

/**
 * @brief Applies a rotation to the given transform. Not the
 * same as setting.
 *
 * @param t A pointer to the transform to be updated.
 * @param rotation The rotation to be applied.
 */
ELSA_API void TransformRotate(Transform* t, q4f rotation);

/**
 * @brief Returns the scale of the given transform.
 *
 * @param t A constant pointer whose scale to get.
 * @return A copy of the scale.
 */
ELSA_API v3f TransformGetScale(Transform* t);

/**
 * @brief Sets the scale of the given transform.
 *
 * @param t A pointer to the transform to be updated.
 * @param scale The scale to be set.
 */
ELSA_API void TransformSetScale(Transform* t, v3f scale);

/**
 * @brief Applies a scale to the given transform. Not the
 * same as setting.
 *
 * @param t A pointer to the transform to be updated.
 * @param scale The scale to be applied.
 */
ELSA_API void TransformScale(Transform* t, v3f scale);

/**
 * @brief Retrieves the local transformation matrix from the provided transform.
 * Automatically recalculates the matrix if it is dirty. Otherwise, the already
 * calculated one is returned.
 *
 * @param t A pointer to the transform whose matrix to retrieve.
 * @return A copy of the local transformation matrix.
 */
ELSA_API m4f TransformGetLocal(Transform* t);

/**
 * @brief Obtains the world matrix of the given transform
 * by examining its parent (if there is one) and multiplying it
 * against the local matrix.
 *
 * @param t A pointer to the transform whose world matrix to retrieve.
 * @return A copy of the world matrix.
 */
ELSA_API m4f TransformGetWorld(Transform* t);

#endif

