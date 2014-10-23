#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class ConeShape : ConvexInternalShape
	{
	internal:
		ConeShape(btConeShape* native);

	public:
		ConeShape(btScalar radius, btScalar height);

		property int ConeUpIndex
		{
			int get();
			void set(int upIndex);
		}

		property btScalar Height
		{
			btScalar get();
		}

		property btScalar Radius
		{
			btScalar get();
		}
	};

	public ref class ConeShapeX : ConeShape
	{
	public:
		ConeShapeX(btScalar radius, btScalar height);
	};

	public ref class ConeShapeZ : ConeShape
	{
	public:
		ConeShapeZ(btScalar radius, btScalar height);
	};
};
