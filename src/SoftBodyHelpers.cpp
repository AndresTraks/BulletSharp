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

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateEllipsoid(SoftBodyWorldInfo^ worldInfo, Vector3 center,
	Vector3 radius, int res)
{
	VECTOR3_CONV(center);
	VECTOR3_CONV(radius);
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateEllipsoid(*worldInfo->_native, VECTOR3_USE(center),
		VECTOR3_USE(radius), res));
	VECTOR3_DEL(center);
	VECTOR3_DEL(radius);
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromConvexHull(SoftBodyWorldInfo^ worldInfo, array<Vector3>^ vertices,
	bool randomizeConstraints)
{
	btVector3* btVertices = Math::Vector3ArrayToUnmanaged(vertices);
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromConvexHull(*worldInfo->_native, btVertices,
		randomizeConstraints));
	delete[] btVertices;
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromConvexHull(SoftBodyWorldInfo^ worldInfo, array<Vector3>^ vertices)
{
	btVector3* btVertices = Math::Vector3ArrayToUnmanaged(vertices);
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromConvexHull(*worldInfo->_native, btVertices,
		vertices->Length));
	delete[] btVertices;
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTetGenData(SoftBodyWorldInfo^ worldInfo, String^ ele,
	String^ face, String^ node, bool faceLinks, bool tetraLinks, bool facesFromTetras)
{
	const char* eleTemp = StringConv::ManagedToUnmanaged(ele);
	const char* faceTemp = StringConv::ManagedToUnmanaged(face);
	const char* nodeTemp = StringConv::ManagedToUnmanaged(node);
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTetGenData(*worldInfo->_native, eleTemp,
		faceTemp, nodeTemp, faceLinks, tetraLinks, facesFromTetras));
	StringConv::FreeUnmanagedString(eleTemp);
	StringConv::FreeUnmanagedString(faceTemp);
	StringConv::FreeUnmanagedString(nodeTemp);
	body->WorldInfo = worldInfo;
	return body;
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
		*worldInfo->_native, elementStr, faceStr, nodeStr, faceLinks, tetraLinks, facesfromtetras)
	);

	free(elementStr);
	free(faceStr);
	free(nodeStr);
	
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo, array<btScalar>^ vertices,
	array<int>^ triangles, bool randomizeConstraints)
{
	pin_ptr<btScalar> verticesPtr = &vertices[0];
	pin_ptr<int> trianglesPtr = &triangles[0];
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->_native, verticesPtr,
		trianglesPtr, triangles->Length / 3, randomizeConstraints));
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo, array<btScalar>^ vertices,
	array<int>^ triangles)
{
	pin_ptr<btScalar> verticesPtr = &vertices[0];
	pin_ptr<int> trianglesPtr = &triangles[0];
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->_native, verticesPtr,
		trianglesPtr, triangles->Length / 3));
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
	array<Vector3>^ vertices, array<int>^ triangles, bool randomizeConstraints)
{
	pin_ptr<int> trianglesPtr = &triangles[0];

	if (sizeof(Vector3) == 3 * sizeof(btScalar)) {
		pin_ptr<Vector3> vPtr = &vertices[0];
		return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->_native,
			(btScalar*)vPtr, trianglesPtr, triangles->Length / 3, randomizeConstraints));
	}

	int len = vertices->Length;
	btScalar* btVertices = new btScalar[len*3];
	for(int i=0; i<len; i++) {
		btVertices[i*3] = Vector_X(vertices[i]);
		btVertices[i*3+1] = Vector_Y(vertices[i]);
		btVertices[i*3+2] = Vector_Z(vertices[i]);
	}
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->_native,
		btVertices, trianglesPtr, triangles->Length / 3, randomizeConstraints));
	delete[] btVertices;
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
	array<Vector3>^ vertices, array<int>^ triangles)
{
	pin_ptr<int> trianglesPtr = &triangles[0];

	if (sizeof(Vector3) == 3 * sizeof(btScalar)) {
		pin_ptr<Vector3> vPtr = &vertices[0];
		return gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->_native,
			(btScalar*)vPtr, trianglesPtr, triangles->Length / 3));
	}

	int len = vertices->Length;
	btScalar* btVertices = new btScalar[len*3];
	for(int i=0; i<len; i++) {
		btVertices[i*3] = Vector_X(vertices[i]);
		btVertices[i*3+1] = Vector_Y(vertices[i]);
		btVertices[i*3+2] = Vector_Z(vertices[i]);
	}
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateFromTriMesh(*worldInfo->_native,
		btVertices, trianglesPtr, triangles->Length / 3));
	delete[] btVertices;
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatch(SoftBodyWorldInfo^ worldInfo, Vector3 corner00,
	Vector3 corner10, Vector3 corner01, Vector3 corner11, int resx, int resy, int fixeds,
	bool gendiags)
{
	VECTOR3_CONV(corner00);
	VECTOR3_CONV(corner10);
	VECTOR3_CONV(corner01);
	VECTOR3_CONV(corner11);
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatch(*worldInfo->_native, VECTOR3_USE(corner00),
		VECTOR3_USE(corner10), VECTOR3_USE(corner01), VECTOR3_USE(corner11), resx,
		resy, fixeds, gendiags));
	VECTOR3_DEL(corner00);
	VECTOR3_DEL(corner10);
	VECTOR3_DEL(corner01);
	VECTOR3_DEL(corner11);
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatchUV(SoftBodyWorldInfo^ worldInfo, Vector3 corner00,
	Vector3 corner10, Vector3 corner01, Vector3 corner11, int resx, int resy, int fixeds,
	bool gendiags, array<float>^ texCoords)
{
	VECTOR3_CONV(corner00);
	VECTOR3_CONV(corner10);
	VECTOR3_CONV(corner01);
	VECTOR3_CONV(corner11);
	pin_ptr<float> texCoordsPtr = &texCoords[0];
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatchUV(*worldInfo->_native, VECTOR3_USE(corner00),
		VECTOR3_USE(corner10), VECTOR3_USE(corner01), VECTOR3_USE(corner11), resx,
		resy, fixeds, gendiags, texCoordsPtr));
	VECTOR3_DEL(corner00);
	VECTOR3_DEL(corner10);
	VECTOR3_DEL(corner01);
	VECTOR3_DEL(corner11);
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreatePatchUV(SoftBodyWorldInfo^ worldInfo, Vector3 corner00,
	Vector3 corner10, Vector3 corner01, Vector3 corner11, int resx, int resy, int fixeds,
	bool gendiags)
{
	VECTOR3_CONV(corner00);
	VECTOR3_CONV(corner10);
	VECTOR3_CONV(corner01);
	VECTOR3_CONV(corner11);
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreatePatchUV(*worldInfo->_native, VECTOR3_USE(corner00),
		VECTOR3_USE(corner10), VECTOR3_USE(corner01), VECTOR3_USE(corner11), resx,
		resy, fixeds, gendiags));
	VECTOR3_DEL(corner00);
	VECTOR3_DEL(corner10);
	VECTOR3_DEL(corner01);
	VECTOR3_DEL(corner11);
	body->WorldInfo = worldInfo;
	return body;
}

BulletSharp::SoftBody::SoftBody^ SoftBodyHelpers::CreateRope(SoftBodyWorldInfo^ worldInfo, Vector3 from,
	Vector3 to, int res, int fixeds)
{
	VECTOR3_CONV(from);
	VECTOR3_CONV(to);
	SoftBody^ body = gcnew SoftBody(btSoftBodyHelpers::CreateRope(*worldInfo->_native, VECTOR3_USE(from), VECTOR3_USE(to),
		res, fixeds));
	VECTOR3_DEL(from);
	VECTOR3_DEL(to);
	body->WorldInfo = worldInfo;
	return body;
}

#ifndef DISABLE_DEBUGDRAW
void SoftBodyHelpers::Draw(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, DrawFlags drawFlags)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::Draw((btSoftBody*)psb->_native, debugDrawer->_native, (int)drawFlags);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::Draw((btSoftBody*)psb->_native, wrapper, (int)drawFlags);
		delete wrapper;
	}
}

void SoftBodyHelpers::Draw(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::Draw((btSoftBody*)psb->_native, debugDrawer->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::Draw((btSoftBody*)psb->_native, wrapper);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth,
	int maxDepth)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawClusterTree((btSoftBody*)psb->_native, debugDrawer->_native, minDepth, maxDepth);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawClusterTree((btSoftBody*)psb->_native, wrapper, minDepth, maxDepth);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawClusterTree((btSoftBody*)psb->_native, debugDrawer->_native, minDepth);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawClusterTree((btSoftBody*)psb->_native, wrapper, minDepth);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawClusterTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawClusterTree((btSoftBody*)psb->_native, debugDrawer->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawClusterTree((btSoftBody*)psb->_native, wrapper);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth,
	int maxDepth)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawFaceTree((btSoftBody*)psb->_native, debugDrawer->_native, minDepth, maxDepth);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawFaceTree((btSoftBody*)psb->_native, wrapper, minDepth, maxDepth);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawFaceTree((btSoftBody*)psb->_native, debugDrawer->_native, minDepth);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawFaceTree((btSoftBody*)psb->_native, wrapper, minDepth);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawFaceTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawFaceTree((btSoftBody*)psb->_native, debugDrawer->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawFaceTree((btSoftBody*)psb->_native, wrapper);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawFrame(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawFrame((btSoftBody*)psb->_native, debugDrawer->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawFrame((btSoftBody*)psb->_native, wrapper);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawInfos(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, bool masses, bool areas,
	bool stress)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawInfos((btSoftBody*)psb->_native, debugDrawer->_native,
			masses, areas, stress);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawInfos((btSoftBody*)psb->_native, wrapper,
			masses, areas, stress);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth,
	int maxDepth)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawNodeTree((btSoftBody*)psb->_native, debugDrawer->_native, minDepth, maxDepth);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawNodeTree((btSoftBody*)psb->_native, wrapper, minDepth, maxDepth);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw, int minDepth)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawNodeTree((btSoftBody*)psb->_native, debugDrawer->_native, minDepth);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawNodeTree((btSoftBody*)psb->_native, wrapper, minDepth);
		delete wrapper;
	}
}

void SoftBodyHelpers::DrawNodeTree(BulletSharp::SoftBody::SoftBody^ psb, IDebugDraw^ iDraw)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(iDraw);
	if (debugDrawer) {
		btSoftBodyHelpers::DrawNodeTree((btSoftBody*)psb->_native, debugDrawer->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		btSoftBodyHelpers::DrawNodeTree((btSoftBody*)psb->_native, wrapper);
		delete wrapper;
	}
}
#endif

void SoftBodyHelpers::ReoptimizeLinkOrder(BulletSharp::SoftBody::SoftBody^ psb)
{
	btSoftBodyHelpers::ReoptimizeLinkOrder((btSoftBody*)psb->_native);
}

#endif
