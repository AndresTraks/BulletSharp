#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class CylinderShape : ConvexInternalShape
	{
	internal:
		CylinderShape(btCylinderShape* native);

	public:
		CylinderShape(Vector3 halfExtents);
		CylinderShape(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ);
		CylinderShape(btScalar halfExtents);

		property Vector3 HalfExtentsWithMargin
		{
			Vector3 get();
		}

		property Vector3 HalfExtentsWithoutMargin
		{
			Vector3 get();
		}

		property btScalar Radius
		{
			btScalar get();
		}

		property int UpAxis
		{
			int get();
		}
	};

	public ref class CylinderShapeX : CylinderShape
	{
	public:
		CylinderShapeX(Vector3 halfExtents);
		CylinderShapeX(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ);
		CylinderShapeX(btScalar halfExtents);
	};

	public ref class CylinderShapeZ : CylinderShape
	{
	public:
		CylinderShapeZ(Vector3 halfExtents);
		CylinderShapeZ(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ);
		CylinderShapeZ(btScalar halfExtents);
	};
};
