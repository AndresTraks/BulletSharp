#pragma once

// Fully implemented as of 12 Apr 2010

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

	internal:
		property btStaticPlaneShape* UnmanagedPointer
		{
			btStaticPlaneShape* get();
		}
	};
};
