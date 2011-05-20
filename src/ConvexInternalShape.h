#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexInternalShape abstract : ConvexShape
	{
	internal:
		ConvexInternalShape(btConvexInternalShape* convexInternalShape);

	public:
		property Vector3 ImplicitShapeDimensions
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 LocalScalingNV
		{
			Vector3 get();
		}

		property btScalar MarginNV
		{
			btScalar get();
		}

	internal:
		property btConvexInternalShape* UnmanagedPointer
		{
			btConvexInternalShape* get() new;
		}
	};

	public ref class ConvexInternalAabbCachingShape abstract : ConvexInternalShape
	{
	internal:
		ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape);
	};
};
