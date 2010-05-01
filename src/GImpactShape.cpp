#include "StdAfx.h"

#include "GImpactShape.h"
#include "StridingMeshInterface.h"

GImpactShapeInterface::GImpactShapeInterface(btGImpactShapeInterface* shapeInterface)
: ConcaveShape(shapeInterface)
{
}

void GImpactShapeInterface::UpdateBound()
{
	UnmanagedPointer->updateBound();
}

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
