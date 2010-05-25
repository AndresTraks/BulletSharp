#pragma once

// Fully implemented as of 25 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
#pragma managed(pop)

#include "ConcaveShape.h"

namespace BulletSharp
{
	ref class BvhTriangleMeshShape;

	public ref class ScaledBvhTriangleMeshShape : ConcaveShape
	{
	internal:
		ScaledBvhTriangleMeshShape(btScaledBvhTriangleMeshShape* shape);

	public:
		ScaledBvhTriangleMeshShape(BvhTriangleMeshShape^ childShape, Vector3 localScaling);

		property BvhTriangleMeshShape^ ChildShape
		{
			BvhTriangleMeshShape^ get();
		}

	internal:
		property btScaledBvhTriangleMeshShape* UnmanagedPointer
		{
			btScaledBvhTriangleMeshShape* get();
		}
	};
};
