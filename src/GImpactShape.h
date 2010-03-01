#pragma once

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
	public:
		GImpactMeshShape(StridingMeshInterface^ meshInterface);
	};
};
