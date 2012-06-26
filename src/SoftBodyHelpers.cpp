#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

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
	VECTOR3_DEF(center);
	VECTOR3_DEF(radius);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateEllipsoid(*worldInfo->UnmanagedPointer,
		VECTOR3_USE(center), VECTOR3_USE(radius), res));

	VECTOR3_DEL(center);
	VECTOR3_DEL(radius);

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

	if (sizeof(Vector3) == 3 * sizeof(btScalar)) {
		pin_ptr<Vector3> vPtr = &vertices[0];
		return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
			(btScalar*)vPtr, trianglesPtr, triangles->Length / 3, randomizeConstraints));
	}

	int len = vertices->Length;
	btScalar* btVertices = new btScalar[len*3];
	for(int i=0; i<len; i++) {
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
		btVertices[i*3] = vertices[i].x;
		btVertices[i*3+1] = vertices[i].y;
		btVertices[i*3+2] = vertices[i].z;
#else
		btVertices[i*3] = vertices[i].X;
		btVertices[i*3+1] = vertices[i].Y;
		btVertices[i*3+2] = vertices[i].Z;
#endif
	}
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
		btVertices, trianglesPtr, triangles->Length / 3, randomizeConstraints));
	delete[] btVertices;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
	array<Vector3>^ vertices, array<int>^ triangles)
{
	pin_ptr<int> trianglesPtr = &triangles[0];

	if (sizeof(Vector3) == 3 * sizeof(btScalar)) {
		pin_ptr<Vector3> vPtr = &vertices[0];
		return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
			(btScalar*)vPtr, trianglesPtr, triangles->Length / 3));
	}

	int len = vertices->Length;
	btScalar* btVertices = new btScalar[len*3];
	for(int i=0; i<len; i++) {
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
		btVertices[i*3] = vertices[i].x;
		btVertices[i*3+1] = vertices[i].y;
		btVertices[i*3+2] = vertices[i].z;
#else
		btVertices[i*3] = vertices[i].X;
		btVertices[i*3+1] = vertices[i].Y;
		btVertices[i*3+2] = vertices[i].Z;
#endif
	}
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->UnmanagedPointer,
		btVertices, trianglesPtr, triangles->Length / 3));
	delete[] btVertices;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatch(SoftBodyWorldInfo^ worldInfo,
	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
	int resx, int resy, int fixeds, bool gendiags)
{
	VECTOR3_DEF(corner00);
	VECTOR3_DEF(corner10);
	VECTOR3_DEF(corner01);
	VECTOR3_DEF(corner11);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatch(*worldInfo->UnmanagedPointer,
		VECTOR3_USE(corner00), VECTOR3_USE(corner10), VECTOR3_USE(corner01), VECTOR3_USE(corner11),
		resx, resy, fixeds, gendiags));

	VECTOR3_DEL(corner00);
	VECTOR3_DEL(corner10);
	VECTOR3_DEL(corner01);
	VECTOR3_DEL(corner11);

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatchUV(SoftBodyWorldInfo^ worldInfo,
	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
	int resx, int resy, int fixeds, bool gendiags, array<float>^ texCoords)
{
	VECTOR3_DEF(corner00);
	VECTOR3_DEF(corner10);
	VECTOR3_DEF(corner01);
	VECTOR3_DEF(corner11);

	pin_ptr<float> texCoordsPtr = &texCoords[0];

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatchUV(*worldInfo->UnmanagedPointer,
		VECTOR3_USE(corner00), VECTOR3_USE(corner10), VECTOR3_USE(corner01), VECTOR3_USE(corner11),
		resx, resy, fixeds, gendiags, texCoordsPtr));

	VECTOR3_DEL(corner00);
	VECTOR3_DEL(corner10);
	VECTOR3_DEL(corner01);
	VECTOR3_DEL(corner11);

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatchUV(SoftBodyWorldInfo^ worldInfo,
	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
	int resx, int resy, int fixeds, bool gendiags)
{
	VECTOR3_DEF(corner00);
	VECTOR3_DEF(corner10);
	VECTOR3_DEF(corner01);
	VECTOR3_DEF(corner11);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatchUV(*worldInfo->UnmanagedPointer,
		VECTOR3_USE(corner00), VECTOR3_USE(corner10), VECTOR3_USE(corner01), VECTOR3_USE(corner11),
		resx, resy, fixeds, gendiags));

	VECTOR3_DEL(corner00);
	VECTOR3_DEL(corner10);
	VECTOR3_DEL(corner01);
	VECTOR3_DEL(corner11);

	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateRope(SoftBodyWorldInfo^ worldInfo,
	Vector3 from, Vector3 to, int res, int fixeds)
{
	VECTOR3_DEF(from);
	VECTOR3_DEF(to);

	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateRope(
		*worldInfo->UnmanagedPointer, VECTOR3_USE(from), VECTOR3_USE(to), res, fixeds));

	VECTOR3_DEL(from);
	VECTOR3_DEL(to);

	return body;
}

#ifndef DISABLE_DEBUGDRAW
void SoftBodyHelpers::Draw(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, DrawFlags drawFlags)
{
	btSoftBodyHelpers::Draw(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), (int)drawFlags);
}

void SoftBodyHelpers::Draw(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	btSoftBodyHelpers::Draw(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw));
}

void SoftBodyHelpers::DrawInfos(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, bool masses, bool areas, bool stress)
{
	btSoftBodyHelpers::DrawInfos(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), masses, areas, stress);
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth, int maxDepth)
{
	btSoftBodyHelpers::DrawNodeTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), minDepth, maxDepth);
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth)
{
	btSoftBodyHelpers::DrawNodeTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), minDepth);
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawNodeTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw));
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth, int maxDepth)
{
	btSoftBodyHelpers::DrawFaceTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), minDepth, maxDepth);
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth)
{
	btSoftBodyHelpers::DrawFaceTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), minDepth);
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawFaceTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw));
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth, int maxDepth)
{
	btSoftBodyHelpers::DrawClusterTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), minDepth, maxDepth);
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth)
{
	btSoftBodyHelpers::DrawClusterTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw), minDepth);
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawClusterTree(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw));
}

void SoftBodyHelpers::DrawFrame(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	btSoftBodyHelpers::DrawFrame(psb->UnmanagedPointer, DebugDraw::GetUnmanaged(iDraw));
}
#endif

#endif
