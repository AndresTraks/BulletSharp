#pragma once

// Fully implemented as of 10 Apr 2010

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class CylinderShape : ConvexInternalShape
	{
	internal:
		CylinderShape(btCylinderShape* shape);

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

	internal:
		property btCylinderShape* UnmanagedPointer
		{
			btCylinderShape* get() new;
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
