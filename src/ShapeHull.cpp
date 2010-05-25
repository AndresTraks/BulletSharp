#include "StdAfx.h"

#include "ConvexShape.h"
#include "ShapeHull.h"

ShapeHull::ShapeHull(ConvexShape^ shape)
{
	_shapeHull = new btShapeHull(shape->UnmanagedPointer);
}

bool ShapeHull::BuildHull(btScalar margin)
{
	return _shapeHull->buildHull(margin);
}

BulletSharp::DataStream^ ShapeHull::GetIndexStream()
{
	return gcnew BulletSharp::DataStream((void*)_shapeHull->getIndexPointer(), NumIndices * sizeof(unsigned int), true, false, false);
}

BulletSharp::DataStream^ ShapeHull::GetVertexStream()
{
	return gcnew BulletSharp::DataStream((void*)_shapeHull->getVertexPointer(), NumVertices * sizeof(btVector3), true, false, false);
}

int ShapeHull::NumIndices::get()
{
	return _shapeHull->numIndices();
}

int ShapeHull::NumTriangles::get()
{
	return _shapeHull->numTriangles();
}

int ShapeHull::NumVertices::get()
{
	return _shapeHull->numVertices();
}
