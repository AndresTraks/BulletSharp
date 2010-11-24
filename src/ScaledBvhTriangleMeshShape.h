#pragma once

// Fully implemented as of 23 Nov 2010

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
