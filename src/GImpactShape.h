#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactShape.h>
#pragma managed(pop)

#include "ConcaveShape.h"
#include "StridingMeshInterface.h"

namespace BulletSharp
{
	public ref class GImpactShapeInterface abstract : BulletSharp::ConcaveShape
	{
		internal:
			GImpactShapeInterface(btGImpactShapeInterface* shapeInterface);
	};

	public ref class GImpactMeshShape : BulletSharp::GImpactShapeInterface
	{
		public:
			GImpactMeshShape(StridingMeshInterface^ meshInterface);
	};
};
