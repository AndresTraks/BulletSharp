#pragma once

// Fully implemented as of 02 Apr 2010

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class CapsuleShape : ConvexInternalShape
	{
	internal:
		CapsuleShape(btCapsuleShape* shape);
	
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

	internal:
		property btCapsuleShape* UnmanagedPointer
		{
			btCapsuleShape* get() new;
		}
	};

	public ref class CapsuleShapeX : CapsuleShape
	{
	public:
		CapsuleShapeX(btScalar radius, btScalar height);
	};

	public ref class CapsuleShapeZ : CapsuleShape
	{
	public:
		CapsuleShapeZ(btScalar radius, btScalar height);
	};
};