#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	ref class BvhTriangleMeshShape;

	public ref class ScaledBvhTriangleMeshShape : ConcaveShape
	{
		BvhTriangleMeshShape^ _childShape;

	public:
		ScaledBvhTriangleMeshShape(BvhTriangleMeshShape^ childShape, Vector3 localScaling);

		property BvhTriangleMeshShape^ ChildShape
		{
			BvhTriangleMeshShape^ get();
		}
	};
};
