#pragma once

#include "MultiBodyConstraint.h"

namespace BulletSharp
{
	public ref class MultiBodyJointMotor : MultiBodyConstraint
	{
	internal:
		MultiBodyJointMotor(btMultiBodyJointMotor* native);

	public:
		MultiBodyJointMotor(MultiBody^ body, int link, float desiredVelocity, float maxMotorImpulse);
	};
};
