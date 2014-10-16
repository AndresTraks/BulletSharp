#include "StdAfx.h"

#ifndef DISABLE_GEOMETRY_UTIL

#include "AlignedObjectArray.h"
#include "GeometryUtil.h"

bool GeometryUtil::AreVerticesBehindPlane(Vector3 planeNormal, AlignedVector3Array^ vertices,
	btScalar margin)
{
	VECTOR3_CONV(planeNormal);
	bool ret = btGeometryUtil::areVerticesBehindPlane(VECTOR3_USE(planeNormal), *(btAlignedObjectArray<btVector3>*)vertices->_native,
		margin);
	VECTOR3_DEL(planeNormal);
	return ret;
}

void GeometryUtil::GetPlaneEquationsFromVertices(AlignedVector3Array^ vertices, AlignedVector3Array^ planeEquationsOut)
{
	btGeometryUtil::getPlaneEquationsFromVertices(*(btAlignedObjectArray<btVector3>*)vertices->_native, *(btAlignedObjectArray<btVector3>*)planeEquationsOut->_native);
}

void GeometryUtil::GetVerticesFromPlaneEquations(AlignedVector3Array^ planeEquations,
	AlignedVector3Array^ verticesOut)
{
	btGeometryUtil::getVerticesFromPlaneEquations(*(btAlignedObjectArray<btVector3>*)planeEquations->_native, *(btAlignedObjectArray<btVector3>*)verticesOut->_native);
}
/*
bool GeometryUtil::IsInside(AlignedVector3Array^ vertices, Vector3 planeNormal, btScalar margin)
{
	VECTOR3_CONV(planeNormal);
	bool ret = btGeometryUtil::isInside(*(btAlignedObjectArray<btVector3>*)vertices->_native, VECTOR3_USE(planeNormal),
		margin);
	VECTOR3_DEL(planeNormal);
	return ret;
}
*/
bool GeometryUtil::IsPointInsidePlanes(AlignedVector3Array^ planeEquations, Vector3 point,
	btScalar margin)
{
	VECTOR3_CONV(point);
	bool ret = btGeometryUtil::isPointInsidePlanes(*(btAlignedObjectArray<btVector3>*)planeEquations->_native, VECTOR3_USE(point),
		margin);
	VECTOR3_DEL(point);
	return ret;
}

#endif
