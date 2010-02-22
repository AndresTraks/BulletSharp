#pragma once

#include "ConvexInternalAabbCachingShape.h"

namespace BulletSharp
{
	public ref class CylinderShape : BulletSharp::ConvexInternalShape
	{
		public:
			CylinderShape(Vector3 halfExtents);
			CylinderShape(float halfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ);
	};

	public ref class CylinderShapeX : BulletSharp::ConvexInternalShape
	{
		public:
			CylinderShapeX(Vector3 halfExtents);
			CylinderShapeX(float halfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ);
	};

	public ref class CylinderShapeZ : BulletSharp::ConvexInternalShape
	{
		public:
			CylinderShapeZ(Vector3 halfExtents);
			CylinderShapeZ(float halfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ);
	};
};
