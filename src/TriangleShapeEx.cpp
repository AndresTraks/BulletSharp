#include "StdAfx.h"

#include "Collections.h"
#include "TriangleShapeEx.h"

GimTriangleContact::GimTriangleContact()
{
	_contact = new GIM_TRIANGLE_CONTACT();
}

GimTriangleContact::GimTriangleContact(GimTriangleContact^ other)
{
	_contact = new GIM_TRIANGLE_CONTACT(*other->UnmanagedPointer);
}

void GimTriangleContact::CopyFrom(GimTriangleContact^ other)
{
	_contact->copy_from(*other->UnmanagedPointer);
}

void GimTriangleContact::MergePoints(Vector4 plane, btScalar margin, array<Vector3>^ points)
{
	btVector3* pointsTemp = Math::Vector3ArrayToUnmanaged(points);
	btVector4* planeTemp = Math::Vector4ToBtVector4(plane);

	_contact->merge_points(*planeTemp, margin, pointsTemp, points->Length);

	delete[] pointsTemp;
	delete planeTemp;
}

btScalar GimTriangleContact::PenetrationDepth::get()
{
	return _contact->m_penetration_depth;
}
void GimTriangleContact::PenetrationDepth::set(btScalar value)
{
	_contact->m_penetration_depth = value;
}

int GimTriangleContact::PointCount::get()
{
	return _contact->m_point_count;
}
void GimTriangleContact::PointCount::set(int value)
{
	_contact->m_point_count = value;
}

Vector3Array^ GimTriangleContact::Points::get()
{
	return gcnew Vector3Array(_contact->m_points, 16);
}

Vector4 GimTriangleContact::SeparatingNormal::get()
{
	return Math::BtVector4ToVector4(&_contact->m_separating_normal);
}
void GimTriangleContact::SeparatingNormal::set(Vector4 value)
{
	Math::Vector4ToBtVector4(value, &_contact->m_separating_normal);
}

GIM_TRIANGLE_CONTACT* GimTriangleContact::UnmanagedPointer::get()
{
	return _contact;
}
void GimTriangleContact::UnmanagedPointer::set(GIM_TRIANGLE_CONTACT* value)
{
	_contact = value;
}


PrimitiveTriangle::PrimitiveTriangle()
{
	_triangle = new btPrimitiveTriangle();
}

PrimitiveTriangle::PrimitiveTriangle(btPrimitiveTriangle* triangle)
{
	_triangle = triangle;
}

void PrimitiveTriangle::ApplyTransform(Matrix transform)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	_triangle->applyTransform(*transformTemp);
	delete transformTemp;
}

void PrimitiveTriangle::BuildTriPlane()
{
	_triangle->buildTriPlane();
}

int PrimitiveTriangle::ClipTriangle(PrimitiveTriangle^ other, array<Vector3>^ clippedPoints)
{
	btVector3* clippedPointsTemp = Math::Vector3ArrayToUnmanaged(clippedPoints);
	int ret = _triangle->clip_triangle(*other->UnmanagedPointer, clippedPointsTemp);
	delete[] clippedPointsTemp;
	return ret;
}

void PrimitiveTriangle::GetEdgePlane(int edge_index, [Out] Vector4% plane)
{
	btVector4* planeTemp = new btVector4;
	_triangle->get_edge_plane(edge_index, *planeTemp);
	plane = Math::BtVector4ToVector4(planeTemp);
	delete planeTemp;
}

bool PrimitiveTriangle::FindTriangleCollisionClipMethod(PrimitiveTriangle^ other, GimTriangleContact^ contacts)
{
	return _triangle->find_triangle_collision_clip_method(*other->UnmanagedPointer, *contacts->UnmanagedPointer);
}

bool PrimitiveTriangle::OverlapTestConservative(PrimitiveTriangle^ other)
{
	return _triangle->overlap_test_conservative(*other->UnmanagedPointer);
}

btScalar PrimitiveTriangle::Dummy::get()
{
	return _triangle->m_dummy;
}
void PrimitiveTriangle::Dummy::set(btScalar value)
{
	_triangle->m_dummy = value;
}

btScalar PrimitiveTriangle::Margin::get()
{
	return _triangle->m_margin;
}
void PrimitiveTriangle::Margin::set(btScalar value)
{
	_triangle->m_margin = value;
}

Vector4 PrimitiveTriangle::Plane::get()
{
	return Math::BtVector4ToVector4(&_triangle->m_plane);
}
void PrimitiveTriangle::Plane::set(Vector4 value)
{
	Math::Vector4ToBtVector4(value, &_triangle->m_plane);
}

Vector3Array^ PrimitiveTriangle::Vectors::get()
{
	return gcnew Vector3Array(_triangle->m_vertices, 3);
}

btPrimitiveTriangle* PrimitiveTriangle::UnmanagedPointer::get()
{
	return _triangle;
}
void PrimitiveTriangle::UnmanagedPointer::set(btPrimitiveTriangle* value)
{
	_triangle = value;
}


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
	btVector3* p0Temp = Math::Vector3ToBtVector3(p0);
	btVector3* p1Temp = Math::Vector3ToBtVector3(p1);
	btVector3* p2Temp = Math::Vector3ToBtVector3(p2);

	UnmanagedPointer = new btTriangleShapeEx(*p0Temp, *p1Temp, *p2Temp);

	delete p0Temp;
	delete p1Temp;
	delete p2Temp;
}

TriangleShapeEx::TriangleShapeEx(TriangleShapeEx^ other)
: TriangleShape(new btTriangleShapeEx(*other->UnmanagedPointer))
{
}

void TriangleShapeEx::ApplyTransform(Matrix transform)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	UnmanagedPointer->applyTransform(*transformTemp);
	delete transformTemp;
}

void TriangleShapeEx::BuildTriPlane(Vector4 plane)
{
	btVector4* planeTemp = Math::Vector4ToBtVector4(plane);
	UnmanagedPointer->buildTriPlane(*planeTemp);
	delete planeTemp;
}

bool TriangleShapeEx::OverlapTestConservative(TriangleShapeEx^ other)
{
	return UnmanagedPointer->overlap_test_conservative(*other->UnmanagedPointer);
}

btTriangleShapeEx* TriangleShapeEx::UnmanagedPointer::get()
{
	return (btTriangleShapeEx*)TriangleShape::UnmanagedPointer;
}
