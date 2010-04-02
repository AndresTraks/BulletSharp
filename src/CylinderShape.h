#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class CylinderShape : ConvexInternalShape
	{
	public:
		CylinderShape(Vector3 halfExtents);
		CylinderShape(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ);
		CylinderShape(btScalar halfExtents);
	};

	public ref class CylinderShapeX : ConvexInternalShape
	{
	public:
		CylinderShapeX(Vector3 halfExtents);
		CylinderShapeX(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ);
		CylinderShapeX(btScalar halfExtents);
	};

	public ref class CylinderShapeZ : ConvexInternalShape
	{
	public:
		CylinderShapeZ(Vector3 halfExtents);
		CylinderShapeZ(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ);
		CylinderShapeZ(btScalar halfExtents);
	};
};
