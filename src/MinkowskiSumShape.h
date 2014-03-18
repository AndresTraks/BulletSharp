#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	ref class ConvexShape;

	public ref class MinkowskiSumShape : ConvexInternalShape
	{
	internal:
		MinkowskiSumShape(btMinkowskiSumShape* native);

	public:
		MinkowskiSumShape(ConvexShape^ shapeA, ConvexShape^ shapeB);

		property ConvexShape^ ShapeA
		{
			ConvexShape^ get();
		}

		property ConvexShape^ ShapeB
		{
			ConvexShape^ get();
		}

		property Matrix TransformA
		{
			Matrix get();
			void set(Matrix transA);
		}

		property Matrix TransformB
		{
			Matrix get();
			void set(Matrix transB);
		}
	};
};
