#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "GeometryUtil.h"

void GeometryUtil::GetPlaneEquationsFromVertices(AlignedVector3Array^ vertices, [Out] AlignedVector3Array^% planeEquationsOut)
{
	btAlignedObjectArray<btVector3>* planeEquationsOutTemp = new btAlignedObjectArray<btVector3>;
	btGeometryUtil::getPlaneEquationsFromVertices(*vertices->UnmanagedPointer, *planeEquationsOutTemp);
	planeEquationsOut = gcnew AlignedVector3Array(planeEquationsOutTemp);
}

void GeometryUtil::GetVerticesFromPlaneEquations(AlignedVector3Array^ planeEquations, [Out] AlignedVector3Array^% verticesOut)
{
	btAlignedObjectArray<btVector3>* verticesOutTemp = new btAlignedObjectArray<btVector3>;
	btGeometryUtil::getPlaneEquationsFromVertices(*planeEquations->UnmanagedPointer, *verticesOutTemp);
	verticesOut = gcnew AlignedVector3Array(verticesOutTemp);
}
/*
bool GeometryUtil::IsInside(AlignedVector3Array^ vertices, Vector3 planeNormal, btScalar margin)
{
	btVector3* planeNormalTemp = Math::Vector3ToBtVector3(planeNormal);
	bool ret = btGeometryUtil::isInside(*vertices->UnmanagedPointer, *planeNormalTemp, margin);
	delete planeNormalTemp;
	return ret;
}
*/
bool GeometryUtil::IsPointInsidePlanes(AlignedVector3Array^ planeEquations, Vector3 point, btScalar margin)
{
	btVector3* pointTemp = Math::Vector3ToBtVector3(point);
	bool ret = btGeometryUtil::isPointInsidePlanes(*planeEquations->UnmanagedPointer, *pointTemp, margin);
	delete pointTemp;
	return ret;
}

bool GeometryUtil::AreVerticesBehindPlane(Vector3 planeNormal, AlignedVector3Array^ vertices, btScalar margin)
{
	btVector3* planeNormalTemp = Math::Vector3ToBtVector3(planeNormal);
	bool ret = btGeometryUtil::areVerticesBehindPlane(*planeNormalTemp, *vertices->UnmanagedPointer, margin);
	delete planeNormalTemp;
	return ret;
}
