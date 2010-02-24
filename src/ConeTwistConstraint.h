#pragma once

#include "RigidBody.h"
#include "TypedConstraint.h"

namespace BulletSharp
{
	public ref class ConeTwistConstraint : TypedConstraint
	{
	public:
		ConeTwistConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Matrix rbAFrame, Matrix rbBFrame);
		ConeTwistConstraint(RigidBody^ rbA, Matrix rbAFrame);

		void CalcAngleInfo();
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
			btScalar _twistSpan, btScalar _softness,
			btScalar _biasFactor, btScalar _relaxationFactor);
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
			btScalar _twistSpan, btScalar _softness, btScalar _biasFactor);
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
			btScalar _twistSpan, btScalar _softness);
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2, btScalar _twistSpan);
		void SetLimit(int limitIndex, btScalar limitValue);

		property btConeTwistConstraint* UnmanagedPointer
		{
			btConeTwistConstraint* get() new;
		}
	};
};
