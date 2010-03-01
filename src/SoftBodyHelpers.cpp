#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletSoftBody/btSoftBodyHelpers.h>
#pragma managed(pop)

#include "SoftBody.h"
#include "SoftBodyHelpers.h"
#include "StringConv.h"

float SoftBodyHelpers::CalculateUV(int resx, int resy, int ix, int iy, int id)
{
	return btSoftBodyHelpers::CalculateUV(resx, resy, ix, iy, id);
}

SoftBody^ SoftBodyHelpers::CreateEllipsoid(SoftBodyWorldInfo^ worldInfo,
	Vector3 center, Vector3 radius, int res)
{
	return gcnew SoftBody(btSoftBodyHelpers::CreateEllipsoid(*worldInfo->UnmanagedPointer,
		*Math::Vector3ToBtVec3(center), *Math::Vector3ToBtVec3(radius), res));
}

SoftBody^ SoftBodyHelpers::CreateFromConvexHull(BulletSharp::SoftBodyWorldInfo ^worldInfo,
	array<Vector3>^ vertices, bool randomizeConstraints)
{
	btVector3* btVertices = new btVector3[vertices->Length];
	for(int i=0; i<vertices->Length; i++)
		Math::Vector3ToBtVec3(vertices[i], &btVertices[i]);
	return gcnew SoftBody(btSoftBodyHelpers::CreateFromConvexHull(*worldInfo->UnmanagedPointer,
		btVertices, vertices->Length, randomizeConstraints));
}

SoftBody^ SoftBodyHelpers::CreateFromConvexHull(BulletSharp::SoftBodyWorldInfo ^worldInfo,
	array<Vector3>^ vertices)
{
	btVector3* btVertices = new btVector3[vertices->Length];
	for(int i=0; i<vertices->Length; i++)
		Math::Vector3ToBtVec3(vertices[i], &btVertices[i]);
	return gcnew SoftBody(btSoftBodyHelpers::CreateFromConvexHull(*worldInfo->UnmanagedPointer,
		btVertices, vertices->Length));
}

SoftBody^ SoftBodyHelpers::CreateFromTetGenData(SoftBodyWorldInfo^ worldInfo, String^ ele,
	String^ face, String^ node, bool bfacelinks, bool btetralinks, bool bfacesfromtetras)
{
	return gcnew SoftBody(btSoftBodyHelpers::CreateFromTetGenData(*worldInfo->UnmanagedPointer,
		StringConv::ManagedToUnmanaged(ele), StringConv::ManagedToUnmanaged(face),
		StringConv::ManagedToUnmanaged(node), bfacelinks, btetralinks, bfacesfromtetras)
	);
}

/*
SoftBody^ SoftBodyHelpers::CreateFromTetGenFile(SoftBodyWorldInfo^ worldInfo, String^ ele,
	String^ face, String^ node, bool bfacelinks, bool btetralinks, bool bfacesfromtetras)
{
	return gcnew SoftBody(btSoftBodyHelpers::CreateFromTetGenFile(*worldInfo->UnmanagedPointer,
		StringConv::ManagedToUnmanaged(ele), StringConv::ManagedToUnmanaged(face),
		StringConv::ManagedToUnmanaged(node), bfacelinks, btetralinks, bfacesfromtetras)
	);
}
*/