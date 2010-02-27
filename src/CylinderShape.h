#pragma once

#include "ConvexInternalAabbCachingShape.h"

namespace BulletSharp
{
	public ref class CylinderShape : ConvexInternalShape
	{
	public:
		CylinderShape(Vector3 halfExtents);
		CylinderShape(float halfExtentsX, float halfExtentsY, float halfExtentsZ);
		CylinderShape(float halfExtents);
	};

	public ref class CylinderShapeX : ConvexInternalShape
	{
	public:
		CylinderShapeX(Vector3 halfExtents);
		CylinderShapeX(float halfExtentsX, float halfExtentsY, float halfExtentsZ);
		CylinderShapeX(float halfExtents);
	};

	public ref class CylinderShapeZ : ConvexInternalShape
	{
	public:
		CylinderShapeZ(Vector3 halfExtents);
		CylinderShapeZ(float halfExtentsX, float halfExtentsY, float halfExtentsZ);
		CylinderShapeZ(float halfExtents);
	};
};
