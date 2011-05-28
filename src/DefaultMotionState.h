#pragma once

#include "MotionState.h"

namespace BulletSharp
{
	public ref class DefaultMotionState : BulletSharp::MotionState
	{
	public:
		DefaultMotionState(Matrix startTrans);
		DefaultMotionState();

		void GetWorldTransform([Out] Matrix% transform);
	};
};
