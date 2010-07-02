#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "BoxCollision.h"
#include "GImpactShape.h"
#include "StridingMeshInterface.h"
#include "TriangleShapeEx.h"
#ifndef DISABLE_BVH
#include "GImpactBvh.h"
#endif

GImpactShapeInterface::GImpactShapeInterface(btGImpactShapeInterface* shapeInterface)
: ConcaveShape(shapeInterface)
{
}

void GImpactShapeInterface::GetBulletTriangle(int prim_index, [Out] TriangleShapeEx^% triangle)
{
	btTriangleShapeEx* triangleTemp = new btTriangleShapeEx;
	UnmanagedPointer->getBulletTriangle(prim_index, *triangleTemp);
	triangle = gcnew TriangleShapeEx(triangleTemp);
}

CollisionShape^ GImpactShapeInterface::GetChildShape(int index)
{
	return gcnew CollisionShape(UnmanagedPointer->getChildShape(index));
}

#pragma managed(push, off)
btTransform* GImpactShapeInterface_GetChildTransform(btGImpactShapeInterface* shape, int index)
{
	btTransform* transform = new btTransform;
	*transform = shape->getChildTransform(index);
	return transform;
}
#pragma managed(pop)
Matrix GImpactShapeInterface::GetChildTransform(int index)
{
	btTransform* transformTemp = GImpactShapeInterface_GetChildTransform(UnmanagedPointer, index);
	Matrix transform = Math::BtTransformToMatrix(transformTemp);
	return transform;
}

void GImpactShapeInterface::GetPrimitiveTriangle(int prim_index, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle;
	UnmanagedPointer->getPrimitiveTriangle(prim_index, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

void GImpactShapeInterface::LockChildShapes()
{
	UnmanagedPointer->lockChildShapes();
}

void GImpactShapeInterface::PostUpdate()
{
	UnmanagedPointer->postUpdate();
}

void GImpactShapeInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, CollisionWorld::RayResultCallback^ resultCallback)
{
	btVector3* rayFromTemp = Math::Vector3ToBtVector3(rayFrom);
	btVector3* rayToTemp = Math::Vector3ToBtVector3(rayTo);

	UnmanagedPointer->rayTest(*rayFromTemp, *rayToTemp, *resultCallback->UnmanagedPointer);

	delete rayFromTemp;
	delete rayToTemp;
}

void GImpactShapeInterface::SetChildTransform(int index, Matrix transform)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	UnmanagedPointer->setChildTransform(index, *transformTemp);
	delete transformTemp;
}

void GImpactShapeInterface::UnlockChildShapes()
{
	UnmanagedPointer->unlockChildShapes();
}

void GImpactShapeInterface::UpdateBound()
{
	UnmanagedPointer->updateBound();
}

//GImpactBoxSet^ GImpactShapeInterface::BoxSet::get()
//{
//	return gcnew GImpactBoxSet(UnmanagedPointer->getBoxSet());
//}

bool GImpactShapeInterface::ChildrenHasTransform::get()
{
	return UnmanagedPointer->childrenHasTransform();
}

BulletSharp::GImpactShapeType GImpactShapeInterface::GImpactShapeType::get()
{
	return (BulletSharp::GImpactShapeType)UnmanagedPointer->getGImpactShapeType();
}

bool GImpactShapeInterface::HasBoxSet::get()
{
	return UnmanagedPointer->hasBoxSet();
}

#pragma managed(push, off)
void GImpactShapeInterface_GetLocalBox(btGImpactShapeInterface* shape, btAABB* aabb)
{
	*aabb = shape->getLocalBox();
}
#pragma managed(pop)
Aabb^ GImpactShapeInterface::LocalBox::get()
{
	btAABB* boxTemp = new btAABB();
	GImpactShapeInterface_GetLocalBox(UnmanagedPointer, boxTemp);
	return gcnew Aabb(boxTemp);
}

bool GImpactShapeInterface::NeedsRetrieveTetrahedrons::get()
{
	return UnmanagedPointer->needsRetrieveTetrahedrons();
}

bool GImpactShapeInterface::NeedsRetrieveTriangles::get()
{
	return UnmanagedPointer->needsRetrieveTriangles();
}

int GImpactShapeInterface::NumChildShapes::get()
{
	return UnmanagedPointer->getNumChildShapes();
}

#ifndef DISABLE_BVH
PrimitiveManagerBase^ GImpactShapeInterface::PrimitiveManager::get()
{
	return gcnew PrimitiveManagerBase((btPrimitiveManagerBase*)UnmanagedPointer->getPrimitiveManager());
}
#endif

btGImpactShapeInterface* GImpactShapeInterface::UnmanagedPointer::get()
{
	return (btGImpactShapeInterface*)ConcaveShape::UnmanagedPointer;
}


GImpactMeshShape::GImpactMeshShape(btGImpactMeshShape* shape)
: GImpactShapeInterface(shape)
{
}

GImpactMeshShape::GImpactMeshShape(StridingMeshInterface^ meshInterface)
: GImpactShapeInterface(new btGImpactMeshShape(meshInterface->UnmanagedPointer))
{
}

StridingMeshInterface^ GImpactMeshShape::MeshInterface::get()
{
	return gcnew StridingMeshInterface(UnmanagedPointer->getMeshInterface());
}

int GImpactMeshShape::MeshPartCount::get()
{
	return UnmanagedPointer->getMeshPartCount();
}

btGImpactMeshShape* GImpactMeshShape::UnmanagedPointer::get()
{
	return (btGImpactMeshShape*)GImpactShapeInterface::UnmanagedPointer;
}

#endif
