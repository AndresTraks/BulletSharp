#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactShape.h>
#pragma managed(pop)

#include "ConcaveShape.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class GImpactShapeInterface abstract : ConcaveShape
	{
	internal:
		GImpactShapeInterface(btGImpactShapeInterface* shapeInterface);
	};

	public ref class GImpactMeshShape : GImpactShapeInterface
	{
	internal:
		GImpactMeshShape(btGImpactMeshShape* shape);
	public:
		GImpactMeshShape(StridingMeshInterface^ meshInterface);
	};
};
