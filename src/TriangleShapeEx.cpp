#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "Collections.h"
#include "TriangleShapeEx.h"

GimTriangleContact::GimTriangleContact(GIM_TRIANGLE_CONTACT* native)
{
	_native = native;
}

GimTriangleContact::~GimTriangleContact()
{
	this->!GimTriangleContact();
}

GimTriangleContact::!GimTriangleContact()
{
	delete _native;
	_native = NULL;
}

GimTriangleContact::GimTriangleContact()
{
	_native = new GIM_TRIANGLE_CONTACT();
}

GimTriangleContact::GimTriangleContact(GimTriangleContact^ other)
{
	_native = new GIM_TRIANGLE_CONTACT(*other->_native);
}

void GimTriangleContact::CopyFrom(GimTriangleContact^ other)
{
	_native->copy_from(*other->_native);
}

void GimTriangleContact::MergePoints(Vector4 plane, btScalar margin, array<Vector3>^ points)
{
	btVector3* pointsTemp = Math::Vector3ArrayToUnmanaged(points);
	btVector4* planeTemp = Math::Vector4ToBtVector4(plane);
	_native->merge_points(*planeTemp, margin, pointsTemp, points->Length);
	delete[] pointsTemp;
	delete planeTemp;
}

btScalar GimTriangleContact::PenetrationDepth::get()
{
	return _native->m_penetration_depth;
}
void GimTriangleContact::PenetrationDepth::set(btScalar value)
{
	_native->m_penetration_depth = value;
}

int GimTriangleContact::PointCount::get()
{
	return _native->m_point_count;
}
void GimTriangleContact::PointCount::set(int value)
{
	_native->m_point_count = value;
}

Vector3Array^ GimTriangleContact::Points::get()
{
	return gcnew Vector3Array(_native->m_points, 16);
}

Vector4 GimTriangleContact::SeparatingNormal::get()
{
	return Math::BtVector4ToVector4(&_native->m_separating_normal);
}
void GimTriangleContact::SeparatingNormal::set(Vector4 value)
{
	Math::Vector4ToBtVector4(value, &_native->m_separating_normal);
}


PrimitiveTriangle::PrimitiveTriangle(btPrimitiveTriangle* native)
{
	_native = native;
}

PrimitiveTriangle::~PrimitiveTriangle()
{
	this->!PrimitiveTriangle();
}

PrimitiveTriangle::!PrimitiveTriangle()
{
	delete _native;
	_native = NULL;
}

PrimitiveTriangle::PrimitiveTriangle()
{
	_native = new btPrimitiveTriangle();
}

void PrimitiveTriangle::ApplyTransform(Matrix transform)
{
	TRANSFORM_CONV(transform);
	_native->applyTransform(TRANSFORM_USE(transform));
	TRANSFORM_DEL(transform);
}

void PrimitiveTriangle::BuildTriPlane()
{
	_native->buildTriPlane();
}

int PrimitiveTriangle::ClipTriangle(PrimitiveTriangle^ other, array<Vector3>^ clippedPoints)
{
	btVector3* clippedPointsTemp = Math::Vector3ArrayToUnmanaged(clippedPoints);
	int ret = _native->clip_triangle(*other->_native, clippedPointsTemp);
	delete[] clippedPointsTemp;
	return ret;
}

bool PrimitiveTriangle::FindTriangleCollisionClipMethod(PrimitiveTriangle^ other,
	GimTriangleContact^ contacts)
{
	return _native->find_triangle_collision_clip_method(*other->_native, *contacts->_native);
}

void PrimitiveTriangle::GetEdgePlane(int edgeIndex, [Out] Vector4% plane)
{
	btVector4* planeTemp = ALIGNED_NEW(btVector4);
	_native->get_edge_plane(edgeIndex, *planeTemp);
	plane = Math::BtVector4ToVector4(planeTemp);
	ALIGNED_FREE(planeTemp);
}

bool PrimitiveTriangle::OverlapTestConservative(PrimitiveTriangle^ other)
{
	return _native->overlap_test_conservative(*other->_native);
}

btScalar PrimitiveTriangle::Dummy::get()
{
	return _native->m_dummy;
}
void PrimitiveTriangle::Dummy::set(btScalar value)
{
	_native->m_dummy = value;
}

btScalar PrimitiveTriangle::Margin::get()
{
	return _native->m_margin;
}
void PrimitiveTriangle::Margin::set(btScalar value)
{
	_native->m_margin = value;
}

Vector4 PrimitiveTriangle::Plane::get()
{
	return Math::BtVector4ToVector4(&_native->m_plane);
}
void PrimitiveTriangle::Plane::set(Vector4 value)
{
	Math::Vector4ToBtVector4(value, &_native->m_plane);
}

Vector3Array^ PrimitiveTriangle::Vertices::get()
{
	if (_vertices == nullptr)
	{
		_vertices = gcnew Vector3Array(_native->m_vertices, 3);
	}
	return _vertices;
}


#define Native static_cast<btTriangleShapeEx*>(_native)

TriangleShapeEx::TriangleShapeEx(btTriangleShapeEx* native)
	: TriangleShape(native)
{
}

TriangleShapeEx::TriangleShapeEx()
	: TriangleShape(new btTriangleShapeEx())
{
}

TriangleShapeEx::TriangleShapeEx(Vector3 p0, Vector3 p1, Vector3 p2)
	: TriangleShape(0)
{
	VECTOR3_CONV(p0);
	VECTOR3_CONV(p1);
	VECTOR3_CONV(p2);
	UnmanagedPointer = new btTriangleShapeEx(VECTOR3_USE(p0), VECTOR3_USE(p1), VECTOR3_USE(p2));
	VECTOR3_DEL(p0);
	VECTOR3_DEL(p1);
	VECTOR3_DEL(p2);
}

TriangleShapeEx::TriangleShapeEx(TriangleShapeEx^ other)
	: TriangleShape(new btTriangleShapeEx(*(btTriangleShapeEx*)other->_native))
{
}

void TriangleShapeEx::ApplyTransform(Matrix transform)
{
	TRANSFORM_CONV(transform);
	Native->applyTransform(TRANSFORM_USE(transform));
	TRANSFORM_DEL(transform);
}

void TriangleShapeEx::BuildTriPlane(Vector4 plane)
{
	btVector4* planeTemp = Math::Vector4ToBtVector4(plane);
	Native->buildTriPlane(*planeTemp);
	delete planeTemp;
}

bool TriangleShapeEx::OverlapTestConservative(TriangleShapeEx^ other)
{
	return Native->overlap_test_conservative(*(btTriangleShapeEx*)other->_native);
}

#endif
