#pragma once

#include "MultiBodyConstraint.h"

namespace BulletSharp
{
	interface class IDebugDraw;

	public ref class MultiBodyJointMotor : MultiBodyConstraint
	{
	internal:
		MultiBodyJointMotor(btMultiBodyJointMotor* native);

	public:
		MultiBodyJointMotor(MultiBody^ body, int link, btScalar desiredVelocity,
			btScalar maxMotorImpulse);
		MultiBodyJointMotor(MultiBody^ body, int link, int linkDoF, btScalar desiredVelocity,
			btScalar maxMotorImpulse);

#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ drawer) override;
#endif

		void SetPositionTarget(btScalar posTarget, btScalar kp);
		void SetPositionTarget(btScalar posTarget);
		void SetVelocityTarget(btScalar velTarget, btScalar kd);
		void SetVelocityTarget(btScalar velTarget);
	};
};
