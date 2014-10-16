#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class CapsuleShape : ConvexInternalShape
	{
	internal:
		CapsuleShape(btCapsuleShape* native);

	public:
		CapsuleShape(btScalar radius, btScalar height);

		property btScalar HalfHeight
		{
			btScalar get();
		}

		property btScalar Radius
		{
			btScalar get();
		}

		property int UpAxis
		{
			int get();
		}
	};

	public ref class CapsuleShapeX : CapsuleShape
	{
	internal:
		CapsuleShapeX(btCapsuleShapeX* native);

	public:
		CapsuleShapeX(btScalar radius, btScalar height);
	};

	public ref class CapsuleShapeZ : CapsuleShape
	{
	internal:
		CapsuleShapeZ(btCapsuleShapeZ* native);

	public:
		CapsuleShapeZ(btScalar radius, btScalar height);
	};
};
