#include "StdAfx.h"

#ifndef DISABLE_GEOMETRY_UTIL

#include "AlignedObjectArray.h"
#include "GeometryUtil.h"

void GeometryUtil::GetPlaneEquationsFromVertices(AlignedVector3Array^ vertices, [Out] AlignedVector3Array^% planeEquationsOut)
{
	btAlignedObjectArray<btVector3>* planeEquationsOutTemp = new btAlignedObjectArray<btVector3>;
	btGeometryUtil::getPlaneEquationsFromVertices(*(btAlignedObjectArray<btVector3>*)vertices->_unmanaged, *planeEquationsOutTemp);
	planeEquationsOut = gcnew AlignedVector3Array(planeEquationsOutTemp);
}

void GeometryUtil::GetVerticesFromPlaneEquations(AlignedVector3Array^ planeEquations, [Out] AlignedVector3Array^% verticesOut)
{
	btAlignedObjectArray<btVector3>* verticesOutTemp = new btAlignedObjectArray<btVector3>;
	btGeometryUtil::getVerticesFromPlaneEquations(*(btAlignedObjectArray<btVector3>*)planeEquations->_unmanaged, *verticesOutTemp);
	verticesOut = gcnew AlignedVector3Array(verticesOutTemp);
}
/*
bool GeometryUtil::IsInside(AlignedVector3Array^ vertices, Vector3 planeNormal, btScalar margin)
{
	VECTOR3_DEF(planeNormal);
	bool ret = btGeometryUtil::isInside(*vertices->UnmanagedPointer, VECTOR3_USE(planeNormal), margin);
	VECTOR3_DEL(planeNormal);
	return ret;
}
*/
bool GeometryUtil::IsPointInsidePlanes(AlignedVector3Array^ planeEquations, Vector3 point, btScalar margin)
{
	VECTOR3_DEF(point);
	bool ret = btGeometryUtil::isPointInsidePlanes(*(btAlignedObjectArray<btVector3>*)planeEquations->_unmanaged, VECTOR3_USE(point), margin);
	VECTOR3_DEL(point);
	return ret;
}

bool GeometryUtil::AreVerticesBehindPlane(Vector3 planeNormal, AlignedVector3Array^ vertices, btScalar margin)
{
	VECTOR3_DEF(planeNormal);
	bool ret = btGeometryUtil::areVerticesBehindPlane(VECTOR3_USE(planeNormal), *(btAlignedObjectArray<btVector3>*)vertices->_unmanaged, margin);
	VECTOR3_DEL(planeNormal);
	return ret;
}

#endif
