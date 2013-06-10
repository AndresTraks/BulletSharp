#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "Collections.h"
#include "TriangleShapeEx.h"

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


PrimitiveTriangle::PrimitiveTriangle()
{
	_native = new btPrimitiveTriangle();
}

PrimitiveTriangle::PrimitiveTriangle(btPrimitiveTriangle* triangle)
{
	_native = triangle;
}

void PrimitiveTriangle::ApplyTransform(Matrix transform)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	_native->applyTransform(*transformTemp);
	ALIGNED_FREE(transformTemp);
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

void PrimitiveTriangle::GetEdgePlane(int edge_index, [Out] Vector4% plane)
{
	btVector4* planeTemp = new btVector4;
	_native->get_edge_plane(edge_index, *planeTemp);
	plane = Math::BtVector4ToVector4(planeTemp);
	delete planeTemp;
}

bool PrimitiveTriangle::FindTriangleCollisionClipMethod(PrimitiveTriangle^ other, GimTriangleContact^ contacts)
{
	return _native->find_triangle_collision_clip_method(*other->_native, *contacts->_native);
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

Vector3Array^ PrimitiveTriangle::Vectors::get()
{
	return gcnew Vector3Array(_native->m_vertices, 3);
}


#define Native static_cast<btTriangleShapeEx*>(_native)

TriangleShapeEx::TriangleShapeEx()
: TriangleShape(new btTriangleShapeEx())
{
}

TriangleShapeEx::TriangleShapeEx(btTriangleShapeEx* triangle)
: TriangleShape(triangle)
{
}

TriangleShapeEx::TriangleShapeEx(Vector3 p0, Vector3 p1, Vector3 p2)
: TriangleShape()
{
	VECTOR3_DEF(p0);
	VECTOR3_DEF(p1);
	VECTOR3_DEF(p2);

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
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	Native->applyTransform(*transformTemp);
	ALIGNED_FREE(transformTemp);
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
