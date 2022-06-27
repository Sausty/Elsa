#include "Transform.h"

#include <Math/Math.h>

Transform TransformCreate()
{
	Transform t = TransformFromPositionRotationScale(V3Zero(), Q4Identity(), V3One());
    t.Local = M4Identity();
    t.Parent = NULL;
    return t;
}

Transform TransformFromPosition(v3f pos)
{
	Transform t = TransformFromPositionRotationScale(pos, Q4Identity(), V3One());
    t.Local = M4Identity();
    t.Parent = NULL;
    return t;
}

Transform TransformFromRotation(q4f rotation)
{
	Transform t = TransformFromPositionRotationScale(V3Zero(), rotation, V3One());
    t.Local = M4Identity();
    t.Parent = NULL;
    return t;
}

Transform TransformFromPositionRotation(v3f position, q4f rotation)
{
	Transform t = TransformFromPositionRotationScale(position, rotation, V3One());
    t.Local = M4Identity();
    t.Parent = NULL;
    return t;
}

Transform TransformFromPositionRotationScale(v3f position, q4f rotation, v3f scale)
{
	Transform t;
    
	TransformSetPosition(&t, position);
	TransformSetRotation(&t, rotation);
	TransformSetScale(&t, scale);
	
	t.IsDirty = true;
    t.Local = M4Identity();
    t.Parent = NULL;
    return t;
}

Transform* TransformGetParent(Transform* t)
{
	if (!t) return NULL;
	return t->Parent;
}

void TransformSetParent(Transform* t, Transform* parent)
{
	if (t) {
		t->Parent = parent;
	}
}

v3f TransformGetPosition(const Transform* t)
{
	return t->Position;
}

void TransformSetPosition(Transform* t, v3f position)
{
	if (t) {
		t->Position = position;
		t->IsDirty = true;
	}
}

void TransformTranslate(Transform* t, v3f translation)
{
	if (t) {
		t->Position = V3Add(t->Position, translation);
		t->IsDirty = true;
	}
}

q4f TransformGetRotation(Transform* t)
{
	return t->Rotation;
}

void TransformSetRotation(Transform* t, q4f rotation)
{
	if (t) {
		t->Rotation = rotation;
		t->IsDirty = true;
	}
}

void TransformRotate(Transform* t, q4f rotation) {
	if (t) {
		t->Rotation = Q4Mul(t->Rotation, rotation);
		t->IsDirty = true;
	}
}

v3f TransformGetScale(Transform* t) {
	return t->Scale;
}

void TransformSetScale(Transform* t, v3f scale) {
	if (t) {
		t->Scale = scale;
		t->IsDirty = true;
	}
}

void TransformScale(Transform* t, v3f scale)
{
	if (t) {
		t->Scale = V3Mul(t->Scale, scale);
		t->IsDirty = true;
	}
}

m4f TransformGetLocal(Transform* t)
{
	if (t) {
		if (t->IsDirty) {
			m4f tr = M4Mul(Q4ToM4(t->Rotation), M4Translate(t->Position));
			tr = M4Mul(M4Scale(t->Scale), tr);
			t->Local = tr;
			t->IsDirty = false;
		}
		
		return t->Local;
	}
	
	return M4Identity();
}

m4f TransformGetWorld(Transform* t)
{
	if (t) {
		m4f l = TransformGetLocal(t);
		if (t->Parent) {
			m4f p = TransformGetWorld(t->Parent);
			return M4Mul(l, p);
		}
		return l;
	}
	return M4Identity();
}