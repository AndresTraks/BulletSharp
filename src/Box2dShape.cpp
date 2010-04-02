#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#pragma managed(pop)

#include "Box2dShape.h"

Box2dShape::Box2dShape(btBox2dShape* shape)
: PolyhedralConvexShape(shape)
{
}

Box2dShape::Box2dShape(Vector3 boxHalfExtents)
: PolyhedralConvexShape(new btBox2dShape(*Math::Vector3ToBtVector3(boxHalfExtents)))
{
}

Box2dShape::Box2dShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ)
: PolyhedralConvexShape(new btBox2dShape(*(new btVector3(boxHalfExtentsX,boxHalfExtentsY,boxHalfExtentsZ))))
{
}

Box2dShape::Box2dShape(btScalar boxHalfExtents)
: PolyhedralConvexShape(new btBox2dShape(*(new btVector3(boxHalfExtents,boxHalfExtents,boxHalfExtents))))
{
}

Vector3 Box2dShape::Centroid::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getCentroid());
}

#pragma managed(push, off)
btVector3* Box2dShape_GetHalfExtentsWithMargin(btBox2dShape* shape)
{
	btVector3* extents = new btVector3;
	*extents = shape->getHalfExtentsWithMargin();
	return extents;
}
#pragma managed(pop)

Vector3 Box2dShape::HalfExtentsWithMargin::get()
{
	return Math::BtVector3ToVector3(Box2dShape_GetHalfExtentsWithMargin(UnmanagedPointer));
}

Vector3 Box2dShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getHalfExtentsWithoutMargin());
}

array<Vector3>^ Box2dShape::Normals::get()
{
	const btVector3* btNormals = UnmanagedPointer->getNormals();
	array<Vector3>^ normals = gcnew array<Vector3>(4);
	normals[0] = Math::BtVector3ToVector3(&btNormals[0]);
	normals[1] = Math::BtVector3ToVector3(&btNormals[1]);
	normals[2] = Math::BtVector3ToVector3(&btNormals[2]);
	normals[3] = Math::BtVector3ToVector3(&btNormals[3]);
	return normals;
}

int Box2dShape::VertexCount::get()
{
	return UnmanagedPointer->getVertexCount();
}

array<Vector3>^ Box2dShape::Vertices::get()
{
	const btVector3* btVertices = UnmanagedPointer->getVertices();
	array<Vector3>^ vertices = gcnew array<Vector3>(4);
	vertices[0] = Math::BtVector3ToVector3(&btVertices[0]);
	vertices[1] = Math::BtVector3ToVector3(&btVertices[1]);
	vertices[2] = Math::BtVector3ToVector3(&btVertices[2]);
	vertices[3] = Math::BtVector3ToVector3(&btVertices[3]);
	return vertices;
}

Vector3 Box2dShape::GetVertex(int i)
{
	btVector3* vertex = new btVector3;
	UnmanagedPointer->getVertex(i, *vertex);
	return Math::BtVector3ToVector3(vertex);
}

Box2dShape^ Box2dShape::Upcast(CollisionShape^ shape)
{
	return gcnew Box2dShape((btBox2dShape*)shape->UnmanagedPointer);
}

btBox2dShape* Box2dShape::UnmanagedPointer::get()
{
	return (btBox2dShape*)PolyhedralConvexShape::UnmanagedPointer;
}
