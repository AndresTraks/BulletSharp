#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class MultiSphereShape : ConvexInternalAabbCachingShape
	{
	public:
		MultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi);

		Vector3 GetSpherePosition(int index);
		btScalar GetSphereRadius(int index);

		property int SphereCount
		{
			int get();
		}
	};
};
