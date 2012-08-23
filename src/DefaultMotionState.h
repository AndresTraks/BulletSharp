#pragma once

#include "MotionState.h"

namespace BulletSharp
{
	public ref class DefaultMotionState : BulletSharp::MotionState
	{
	public:
		DefaultMotionState(Matrix startTrans);
		DefaultMotionState();

		virtual property Matrix WorldTransform
		{
			Matrix get() override;
			void set(Matrix value) override;
		}

		void GetWorldTransform([Out] Matrix% transform);
	};
};
