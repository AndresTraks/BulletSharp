#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#pragma managed(push, off)
#include <BulletSoftBody/btSoftBodyHelpers.h>
#pragma managed(pop)

#include <stdio.h>

#include "SoftBody.h"
#include "SoftBodyHelpers.h"
#include "StringConv.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

using namespace BulletSharp::SoftBody;

float SoftBodyHelpers::CalculateUV(int resx, int resy, int ix, int iy, int id)
{
	return btSoftBodyHelpers::CalculateUV(resx, resy, ix, iy, id);
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateEllipsoid(SoftBodyWorldInfo^ worldInfo,
	Vector3 center, Vector3 radius, int res)
{
	btVector3* centerTemp = Math::Vector3ToBtVector3(center);
	btVector3* radiusTemp = Math::Vector3ToBtVector3(radius);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateEllipsoid(*worldInfo->UnmanagedPointer,
		*centerTemp, *radiusTemp, res));

	delete centerTemp;
	delete radiusTemp;

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromConvexHull(SoftBodyWorldInfo ^worldInfo,
	array<Vector3>^ vertices, bool randomizeConstraints)
{
	btVector3* btVertices = Math::Vector3ArrayToUnmanaged(vertices);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromConvexHull(*worldInfo->UnmanagedPointer,
		btVertices, vertices->Length, randomizeConstraints));

	delete[] btVertices;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromConvexHull(SoftBodyWorldInfo ^worldInfo,
	array<Vector3>^ vertices)
{
	btVector3* btVertices = Math::Vector3ArrayToUnmanaged(vertices);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromConvexHull(*worldInfo->UnmanagedPointer,
		btVertices, vertices->Length));

	delete[] btVertices;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTetGenData(SoftBodyWorldInfo^ worldInfo, String^ ele,
	String^ face, String^ node, bool faceLinks, bool tetraLinks, bool facesfromtetras)
{
	const char* eleTemp = StringConv::ManagedToUnmanaged(ele);
	const char* faceTemp = StringConv::ManagedToUnmanaged(face);
	const char* nodeTemp = StringConv::ManagedToUnmanaged(node);

	return gcnew SoftBody(btSoftBodyHelpers::CreateFromTetGenData(*worldInfo->UnmanagedPointer,
		eleTemp, faceTemp, nodeTemp, faceLinks, tetraLinks, facesfromtetras)
		);

	StringConv::FreeUnmanagedString(eleTemp);
	StringConv::FreeUnmanagedString(faceTemp);
	StringConv::FreeUnmanagedString(nodeTemp);
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTetGenFile(SoftBodyWorldInfo^ worldInfo, String^ elementFilename,
	String^ faceFilename, String^ nodeFilename, bool faceLinks, bool tetraLinks, bool facesfromtetras)
{
	FILE* f_read;
	long fileSize;
	char* elementStr;
	char* faceStr;
	char* nodeStr;

	// Read elements file
	if (elementFilename != nullptr)
	{
		const char* elementFileStr = StringConv::ManagedToUnmanaged(elementFilename);
		errno_t ret = fopen_s(&f_read, elementFileStr, "rb");
		StringConv::FreeUnmanagedString(elementFileStr);
		if (ret != 0)
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
		ret = fread(elementStr, 1, fileSize, f_read);
		fclose(f_read);
		if (ret != fileSize)
			return nullptr;

		elementStr[fileSize] = 0;
	}
	else
	{
		elementStr = 0;
	}

	if (faceFilename != nullptr)
	{
		// Read faces file
		const char* faceFileStr = StringConv::ManagedToUnmanaged(faceFilename);
		errno_t ret = fopen_s(&f_read, faceFileStr, "rb");
		StringConv::FreeUnmanagedString(faceFileStr);
		if (ret != 0)
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
		ret = fread(faceStr, 1, fileSize, f_read);
		fclose(f_read);
		if (ret != fileSize)
		{
			if (elementStr)
				free(elementStr);
			return nullptr;
		}

		faceStr[fileSize] = 0;
	}
	else
	{
		faceStr = 0;
	}

	// Read nodes file
	const char* nodeFileStr = StringConv::ManagedToUnmanaged(nodeFilename);
	errno_t ret = fopen_s(&f_read, nodeFileStr, "rb");
	StringConv::FreeUnmanagedString(nodeFileStr);
	if (ret != 0)
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
	ret = fread(nodeStr, 1, fileSize, f_read);
	fclose(f_read);
	if (ret != fileSize)
	{
		if (elementStr)
			free(elementStr);
		if (faceStr)
			free(faceStr);
		free(nodeStr);
		return nullptr;
	}

	nodeStr[fileSize] = 0;

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTetGenData(
		*worldInfo->UnmanagedPointer, elementStr, faceStr, nodeStr,
		faceLinks, tetraLinks, facesfromtetras)
		);

	free(elementStr);
	free(faceStr);
	free(nodeStr);

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
	array<btScalar>^ vertices, array<int>^ triangles, bool randomizeConstraints)
{
	pin_ptr<btScalar> verticesPtr = &vertices[0];
	pin_ptr<int> trianglesPtr = &triangles[0];

	return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
		verticesPtr, trianglesPtr, triangles->Length / 3, randomizeConstraints));
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
	array<btScalar>^ vertices, array<int>^ triangles)
{
	pin_ptr<btScalar> verticesPtr = &vertices[0];
	pin_ptr<int> trianglesPtr = &triangles[0];

	return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
		verticesPtr, trianglesPtr, triangles->Length / 3));
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
	array<Vector3>^ vertices, array<int>^ triangles, bool randomizeConstraints)
{
	pin_ptr<int> trianglesPtr = &triangles[0];
	btVector3* btVertices = Math::Vector3ArrayToUnmanaged(vertices);

	return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
		(btScalar*)btVertices, trianglesPtr, triangles->Length / 3, randomizeConstraints));

	delete[] btVertices;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
	array<Vector3>^ vertices, array<int>^ triangles)
{
	pin_ptr<int> trianglesPtr = &triangles[0];
	btVector3* btVertices = Math::Vector3ArrayToUnmanaged(vertices);

	return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
		(btScalar*)btVertices, trianglesPtr, triangles->Length / 3));

	delete[] btVertices;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatch(SoftBodyWorldInfo^ worldInfo,
	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
	int resx, int resy, int fixeds, bool gendiags)
{
	btVector3* corner00Temp = Math::Vector3ToBtVector3(corner00);
	btVector3* corner10Temp = Math::Vector3ToBtVector3(corner10);
	btVector3* corner01Temp = Math::Vector3ToBtVector3(corner01);
	btVector3* corner11Temp = Math::Vector3ToBtVector3(corner11);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatch(*worldInfo->UnmanagedPointer,
		*corner00Temp, *corner10Temp, *corner01Temp, *corner11Temp, resx, resy, fixeds, gendiags));

	delete corner00Temp;
	delete corner10Temp;
	delete corner01Temp;
	delete corner11Temp;

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatchUV(SoftBodyWorldInfo^ worldInfo,
	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
	int resx, int resy, int fixeds, bool gendiags, array<float>^ texCoords)
{
	btVector3* corner00Temp = Math::Vector3ToBtVector3(corner00);
	btVector3* corner10Temp = Math::Vector3ToBtVector3(corner10);
	btVector3* corner01Temp = Math::Vector3ToBtVector3(corner01);
	btVector3* corner11Temp = Math::Vector3ToBtVector3(corner11);

	pin_ptr<float> texCoordsPtr = &texCoords[0];

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatchUV(*worldInfo->UnmanagedPointer,
		*corner00Temp, *corner10Temp, *corner01Temp, *corner11Temp, resx, resy, fixeds, gendiags, texCoordsPtr));

	delete corner00Temp;
	delete corner10Temp;
	delete corner01Temp;
	delete corner11Temp;

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatchUV(SoftBodyWorldInfo^ worldInfo,
	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
	int resx, int resy, int fixeds, bool gendiags)
{
		btVector3* corner00Temp = Math::Vector3ToBtVector3(corner00);
	btVector3* corner10Temp = Math::Vector3ToBtVector3(corner10);
	btVector3* corner01Temp = Math::Vector3ToBtVector3(corner01);
	btVector3* corner11Temp = Math::Vector3ToBtVector3(corner11);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatchUV(*worldInfo->UnmanagedPointer,
		*corner00Temp, *corner10Temp, *corner01Temp, *corner11Temp, resx, resy, fixeds, gendiags));

	delete corner00Temp;
	delete corner10Temp;
	delete corner01Temp;
	delete corner11Temp;

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateRope(SoftBodyWorldInfo^ worldInfo,
	Vector3 from, Vector3 to, int res, int fixeds)
{
	btVector3* fromTemp = Math::Vector3ToBtVector3(from);
	btVector3* toTemp = Math::Vector3ToBtVector3(to);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateRope(
		*worldInfo->UnmanagedPointer, *fromTemp, *toTemp, res, fixeds));

	delete fromTemp;
	delete toTemp;

	return body;
}

#ifndef DISABLE_DEBUGDRAW
void SoftBodyHelpers::Draw(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, DrawFlags drawFlags)
{
	btSoftBodyHelpers::Draw(psb->UnmanagedPointer, iDraw->UnmanagedPointer, (int)drawFlags);
}

void SoftBodyHelpers::Draw(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw)
{
	btSoftBodyHelpers::Draw(psb->UnmanagedPointer, iDraw->UnmanagedPointer);
}

void SoftBodyHelpers::DrawInfos(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, bool masses, bool areas, bool stress)
{
	btSoftBodyHelpers::DrawInfos(psb->UnmanagedPointer, iDraw->UnmanagedPointer, masses, areas, stress);
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, int minDepth, int maxDepth)
{
	btSoftBodyHelpers::DrawNodeTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer, minDepth, maxDepth);
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, int minDepth)
{
	btSoftBodyHelpers::DrawNodeTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer, minDepth);
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawNodeTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer);
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, int minDepth, int maxDepth)
{
	btSoftBodyHelpers::DrawFaceTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer, minDepth, maxDepth);
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, int minDepth)
{
	btSoftBodyHelpers::DrawFaceTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer, minDepth);
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawFaceTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer);
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, int minDepth, int maxDepth)
{
	btSoftBodyHelpers::DrawClusterTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer, minDepth, maxDepth);
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw, int minDepth)
{
	btSoftBodyHelpers::DrawClusterTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer, minDepth);
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawClusterTree(psb->UnmanagedPointer, iDraw->UnmanagedPointer);
}

void SoftBodyHelpers::DrawFrame(BulletSharp::SoftBody::SoftBody^ psb, DebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawFrame(psb->UnmanagedPointer, iDraw->UnmanagedPointer);
}
#endif

#endif
