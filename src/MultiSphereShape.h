#pragma once

// Fully implemented as of 23 Nov 2010

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
