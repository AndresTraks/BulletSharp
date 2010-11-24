#pragma once

// Fully implemented as of 24 Nov 2010

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	ref class ConvexShape;

	public ref class MinkowskiSumShape : ConvexInternalShape
	{
	internal:
		MinkowskiSumShape(btMinkowskiSumShape* shape);

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
			void set(Matrix value);
		}

		property Matrix TransformB
		{
			Matrix get();
			void set(Matrix value);
		}

	internal:
		property btMinkowskiSumShape* UnmanagedPointer
		{
			btMinkowskiSumShape* get() new;
		}
	};
};
