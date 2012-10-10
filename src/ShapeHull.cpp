#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Collections.h"
#include "ConvexShape.h"
#include "ShapeHull.h"

ShapeHull::ShapeHull(ConvexShape^ shape)
{
	_shapeHull = new btShapeHull((btConvexShape*)shape->_native);
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

UIntArray^ ShapeHull::Indices::get()
{
	return gcnew UIntArray(_shapeHull->getIndexPointer(), NumIndices);
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

Vector3Array^ ShapeHull::Vertices::get()
{
	return gcnew Vector3Array(_shapeHull->getVertexPointer(), NumVertices);
}

#endif
