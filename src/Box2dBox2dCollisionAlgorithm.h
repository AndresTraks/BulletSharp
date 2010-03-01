#pragma once

#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class Box2dBox2dCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};
	};
};
