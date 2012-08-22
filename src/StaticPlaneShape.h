#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	public ref class StaticPlaneShape : ConcaveShape
	{
	internal:
		StaticPlaneShape(btStaticPlaneShape* shape);

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
