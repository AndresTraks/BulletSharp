#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#pragma managed(push, off)
#include <BulletSoftBody/btSoftBodyHelpers.h>
#pragma managed(pop)

#include <stdio.h>

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
		*Math::Vector3ToBtVector3(center), *Math::Vector3ToBtVector3(radius), res));
}

SoftBody^ SoftBodyHelpers::CreateFromConvexHull(BulletSharp::SoftBodyWorldInfo ^worldInfo,
	array<Vector3>^ vertices, bool randomizeConstraints)
{
	btVector3* btVertices = new btVector3[vertices->Length];
	for(int i=0; i<vertices->Length; i++)
		Math::Vector3ToBtVector3(vertices[i], &btVertices[i]);

	return gcnew SoftBody(btSoftBodyHelpers::CreateFromConvexHull(*worldInfo->UnmanagedPointer,
		btVertices, vertices->Length, randomizeConstraints));
}

SoftBody^ SoftBodyHelpers::CreateFromConvexHull(BulletSharp::SoftBodyWorldInfo ^worldInfo,
	array<Vector3>^ vertices)
{
	btVector3* btVertices = new btVector3[vertices->Length];
	for(int i=0; i<vertices->Length; i++)
		Math::Vector3ToBtVector3(vertices[i], &btVertices[i]);

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

SoftBody^ SoftBodyHelpers::CreateFromTetGenFile(SoftBodyWorldInfo^ worldInfo, String^ ele,
	String^ face, String^ node, bool bfacelinks, bool btetralinks, bool bfacesfromtetras)
{
	FILE* f_read;
	long fileSize;
	char* elementStr;
	char* faceStr;
	char* nodeStr;

	// Read elements file
	if (ele != nullptr)
	{
		if (fopen_s(&f_read, StringConv::ManagedToUnmanaged(ele), "rb"))
			return nullptr;
		fseek(f_read, 0, SEEK_END);
		fileSize = ftell(f_read);
		elementStr = (char*) malloc(fileSize+1);
		if (!elementStr)
		{
			fclose(f_read);
			return nullptr;
		}
		fseek(f_read, 0, SEEK_SET);
		fread(elementStr, 1, fileSize, f_read);
		elementStr[fileSize] = 0;
		fclose(f_read);
	}
	else
	{
		elementStr = 0;
	}

	if (face != nullptr)
	{
		// Read faces file
		if (fopen_s(&f_read, StringConv::ManagedToUnmanaged(face), "rb"))
		{
			if (elementStr)
				free(elementStr);
			return nullptr;
		}
		fseek(f_read, 0, SEEK_END);
		fileSize = ftell(f_read);
		faceStr = (char*) malloc(fileSize+1);
		if (!faceStr)
		{
			fclose(f_read);
			if (elementStr)
				free(elementStr);
			return nullptr;
		}
		fseek(f_read, 0, SEEK_SET);
		fread(faceStr, 1, fileSize, f_read);
		faceStr[fileSize] = 0;
		fclose(f_read);
	}
	else
	{
		faceStr = 0;
	}

	// Read nodes file
	if (fopen_s(&f_read, StringConv::ManagedToUnmanaged(node), "rb"))
	{
		if (elementStr)
			free(elementStr);
		if (faceStr)
			free(faceStr);
		return nullptr;
	}
	fseek(f_read, 0, SEEK_END);
	fileSize = ftell(f_read);
	nodeStr = (char*) malloc(fileSize+1);
	if (!nodeStr)
	{
		fclose(f_read);
		if (elementStr)
			free(elementStr);
		if (faceStr)
			free(faceStr);
		return nullptr;
	}
	fseek(f_read, 0, SEEK_SET);
	fread(nodeStr, 1, fileSize, f_read);
	nodeStr[fileSize] = 0;
	fclose(f_read);

	SoftBody^ softBody = gcnew SoftBody(btSoftBodyHelpers::CreateFromTetGenData(
		*worldInfo->UnmanagedPointer, elementStr, faceStr, nodeStr,
		bfacelinks, btetralinks, bfacesfromtetras)
	);

	free(elementStr);
	free(faceStr);
	free(nodeStr);

	return softBody;
}

SoftBody^ SoftBodyHelpers::CreatePatch(SoftBodyWorldInfo^ worldInfo,
	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
	int resx, int resy, int fixeds, bool gendiags)
{
	return gcnew SoftBody(btSoftBodyHelpers::CreatePatch(*worldInfo->UnmanagedPointer,
		*Math::Vector3ToBtVector3(corner00), *Math::Vector3ToBtVector3(corner10),
		*Math::Vector3ToBtVector3(corner01), *Math::Vector3ToBtVector3(corner11),
		resx, resy, fixeds, gendiags));
}

#endif
