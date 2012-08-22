#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexInternalShape abstract : ConvexShape
	{
	internal:
		ConvexInternalShape(btConvexInternalShape* convexInternalShape);

	public:
		void SetSafeMargin(btScalar minDimension, btScalar defaultMarginMultiplier);
		void SetSafeMargin(btScalar minDimension);
		void SetSafeMargin(Vector3 halfExtents, btScalar defaultMarginMultiplier);
		void SetSafeMargin(Vector3 halfExtents);

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
	};

	public ref class ConvexInternalAabbCachingShape abstract : ConvexInternalShape
	{
	internal:
		ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape);
	};
};
