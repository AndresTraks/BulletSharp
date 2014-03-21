#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	public ref class StaticPlaneShape : ConcaveShape
	{
	internal:
		StaticPlaneShape(btStaticPlaneShape* native);

	public:
		StaticPlaneShape(Vector3 planeNormal, btScalar planeConstant);

		property btScalar PlaneConstant
		{
			btScalar get();
		}

		property Vector3 PlaneNormal
		{
			Vector3 get();
		}
	};
};
