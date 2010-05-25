#pragma once

// Fully implemented as of 25 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btMultiSphereShape.h>
#pragma managed(pop)

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class MultiSphereShape : ConvexInternalAabbCachingShape
	{
	internal:
		MultiSphereShape(btMultiSphereShape* shape);

	public:
		MultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi);

		Vector3 GetSpherePosition(int index);
		btScalar GetSphereRadius(int index);

		property int SphereCount
		{
			int get();
		}

	internal:
		property btMultiSphereShape* UnmanagedPointer
		{
			btMultiSphereShape* get() new;
		}
	};
};
