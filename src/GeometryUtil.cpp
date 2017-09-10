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

List<Vector3>^ GeometryUtil::GetVerticesFromPlaneEquations(ICollection<Vector4>^ planeEquations)
{
	int numPlanes = planeEquations->Count;
	array<Vector3>^ planeNormals = gcnew array<Vector3>(numPlanes);
	array<btScalar>^ planeConstants = gcnew array<btScalar>(numPlanes);
	int i = 0;
	for each (Vector4 plane in planeEquations)
	{
		planeNormals[i] = Vector3(Vector_X(plane), Vector_Y(plane), Vector_Z(plane));
		planeConstants[i] = Vector_W(plane);
		i++;
	}

	List<Vector3>^ vertices = gcnew List<Vector3>();
	for (int i = 0; i < numPlanes; i++)
	{
		for (int j = i + 1; j < numPlanes; j++)
		{
			for (int k = j + 1; k < numPlanes; k++)
			{
				Vector3 n2n3;
				Vector3 n3n1;
				Vector3 n1n2;

				Vector3_Cross(planeNormals[j], planeNormals[k], n2n3);
				Vector3_Cross(planeNormals[k], planeNormals[i], n3n1);
				Vector3_Cross(planeNormals[i], planeNormals[j], n1n2);

				if ((Vector3_LengthSquared(n2n3) > 0.0001f) &&
					(Vector3_LengthSquared(n3n1) > 0.0001f) &&
					(Vector3_LengthSquared(n1n2) > 0.0001f))
				{
					//point P out of 3 plane equations:

					//	  d1 ( N2 * N3 ) + d2 ( N3 * N1 ) + d3 ( N1 * N2 )  
					//P = ------------------------------------------------
					//	N1 . ( N2 * N3 )  

					float quotient = Vector3_Dot(planeNormals[i], n2n3);
					if (btFabs(quotient) > 0.000001)
					{
						quotient = -1.0f / quotient;
						n2n3 *= planeConstants[i];
						n3n1 *= planeConstants[j];
						n1n2 *= planeConstants[k];
						Vector3 potentialPoint = quotient * (n2n3 + n3n1 + n1n2);

						//check if inside, and replace supportingVertexOut if needed
						if (IsPointInsidePlanes(planeEquations, potentialPoint, 0.01f))
						{
							vertices->Add(potentialPoint);
						}
					}
				}
			}
		}
	}
	return vertices;
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
bool GeometryUtil::IsPointInsidePlanes(ICollection<Vector4>^ planeEquations, Vector3 point,
	btScalar margin)
{
	for each (Vector4 plane in planeEquations)
	{
		Vector3 normal = Vector3(Vector_X(plane), Vector_Y(plane), Vector_Z(plane));
		btScalar dist = Vector3_Dot(normal, point) + Vector_W(plane);
		if (dist > margin)
		{
			return false;
		}
	}
	return true;
}

#endif
