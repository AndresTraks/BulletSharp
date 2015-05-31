#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexInternalShape abstract : ConvexShape
	{
	internal:
		ConvexInternalShape(btConvexInternalShape* native);

	public:
		void SetSafeMargin(btScalar minDimension, btScalar defaultMarginMultiplier);
		void SetSafeMargin(btScalar minDimension);
		void SetSafeMarginRef(Vector3% halfExtents, btScalar defaultMarginMultiplier);
		void SetSafeMargin(Vector3 halfExtents, btScalar defaultMarginMultiplier);
		void SetSafeMarginRef(Vector3% halfExtents);
		void SetSafeMargin(Vector3 halfExtents);

		property Vector3 ImplicitShapeDimensions
		{
			Vector3 get();
			void set(Vector3 dimensions);
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
		ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* native);

	public:
		void RecalcLocalAabb();
	};
};
