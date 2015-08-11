#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Collections.h"
#include "ConvexShape.h"
#include "ShapeHull.h"

ShapeHull::~ShapeHull()
{
	this->!ShapeHull();
}

ShapeHull::!ShapeHull()
{
	delete _native;
	_native = NULL;
}

ShapeHull::ShapeHull(ConvexShape^ shape)
{
	_native = new btShapeHull((btConvexShape*)shape->_native);
	_shape = shape;
}

bool ShapeHull::BuildHull(btScalar margin)
{
	return _native->buildHull(margin);
}

BulletSharp::DataStream^ ShapeHull::GetIndexStream()
{
	return gcnew BulletSharp::DataStream((void*)_native->getIndexPointer(), NumIndices * sizeof(unsigned int), true, false, false);
}

BulletSharp::DataStream^ ShapeHull::GetVertexStream()
{
	return gcnew BulletSharp::DataStream((void*)_native->getVertexPointer(), NumVertices * sizeof(btVector3), true, false, false);
}

UIntArray^ ShapeHull::Indices::get()
{
	return gcnew UIntArray(_native->getIndexPointer(), NumIndices);
}

int ShapeHull::NumIndices::get()
{
	return _native->numIndices();
}

int ShapeHull::NumTriangles::get()
{
	return _native->numTriangles();
}

int ShapeHull::NumVertices::get()
{
	return _native->numVertices();
}

Vector3Array^ ShapeHull::Vertices::get()
{
	return gcnew Vector3Array(_native->getVertexPointer(), NumVertices);
}

#endif
