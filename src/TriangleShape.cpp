#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btTriangleShape.h>
#pragma managed(pop)

#include "TriangleShape.h"

TriangleShape::TriangleShape(btTriangleShape* triangleShape)
: PolyhedralConvexShape(triangleShape)
{
}

TriangleShape::TriangleShape()
: PolyhedralConvexShape(new btTriangleShape())
{
}

TriangleShape::TriangleShape(Vector3 p0, Vector3 p1, Vector3 p2)
: PolyhedralConvexShape(0)
{
	btVector3* p0Temp = Math::Vector3ToBtVector3(p0);
	btVector3* p1Temp = Math::Vector3ToBtVector3(p1);
	btVector3* p2Temp = Math::Vector3ToBtVector3(p1);

	UnmanagedPointer = new btTriangleShape(*p0Temp, *p1Temp, *p2Temp);

	delete p0Temp;
	delete p1Temp;
	delete p2Temp;
}

void TriangleShape::CalcNormal([Out] Vector3% normal)
{
	btVector3* normalTemp = new btVector3();
	UnmanagedPointer->calcNormal(*normalTemp);
	normal = Math::BtVector3ToVector3(normalTemp);
	delete normalTemp;
}

void TriangleShape::GetPlaneEquation(int i, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport)
{
	btVector3* planeNormalTemp = new btVector3();
	btVector3* planeSupportTemp = new btVector3();

	UnmanagedPointer->getPlaneEquation(i, *planeNormalTemp, *planeSupportTemp);
	
	planeNormal = Math::BtVector3ToVector3(planeNormalTemp);
	planeSupport = Math::BtVector3ToVector3(planeSupportTemp);
	
	delete planeNormalTemp;
}

#pragma managed(push, off)
void TriangleShape_GetVertexPtr(btTriangleShape* shape, int index, btVector3* vertex)
{
	*vertex = shape->getVertexPtr(index);
}
#pragma managed(pop)
Vector3 TriangleShape::GetVertexPtr(int index)
{
	btVector3* vertexTemp = new btVector3();
	TriangleShape_GetVertexPtr(UnmanagedPointer, index, vertexTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vertexTemp);
	delete vertexTemp;
	return vertex;
}

array<Vector3>^ TriangleShape::Vertices::get()
{
	array<Vector3>^ vertices = gcnew array<Vector3>(3);
	vertices[0] = Math::BtVector3ToVector3(&UnmanagedPointer->m_vertices1[0]);
	vertices[1] = Math::BtVector3ToVector3(&UnmanagedPointer->m_vertices1[1]);
	vertices[2] = Math::BtVector3ToVector3(&UnmanagedPointer->m_vertices1[2]);
	return vertices;
}
void TriangleShape::Vertices::set(array<Vector3>^ value)
{
	Math::Vector3ToBtVector3(value[0], &UnmanagedPointer->m_vertices1[0]);
	Math::Vector3ToBtVector3(value[1], &UnmanagedPointer->m_vertices1[1]);
	Math::Vector3ToBtVector3(value[2], &UnmanagedPointer->m_vertices1[2]);
}

btTriangleShape* TriangleShape::UnmanagedPointer::get()
{
	return (btTriangleShape*)PolyhedralConvexShape::UnmanagedPointer;
}
