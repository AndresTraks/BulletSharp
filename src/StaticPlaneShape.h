#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	public ref class StaticPlaneShape : BulletSharp::ConcaveShape
	{
		public:
			StaticPlaneShape(Vector3 planeNormal, btScalar planeConstant);

		internal:
			property btStaticPlaneShape* UnmanagedPointer
			{
				btStaticPlaneShape* get();
			}
	};
};
