#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactShape.h>
#pragma managed(pop)

#include "GImpactShape.h"
#include "StridingMeshInterface.h"

GImpactShapeInterface::GImpactShapeInterface(btGImpactShapeInterface* shapeInterface)
: ConcaveShape(shapeInterface)
{
}


GImpactMeshShape::GImpactMeshShape(StridingMeshInterface^ meshInterface)
: GImpactShapeInterface(new btGImpactMeshShape(meshInterface->UnmanagedPointer))
{
}
