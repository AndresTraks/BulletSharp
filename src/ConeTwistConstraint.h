#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class ConeTwistConstraint : TypedConstraint
	{
	internal:
		ConeTwistConstraint(btConeTwistConstraint* native);

	public:
		ConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame);
		ConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame);

		void CalcAngleInfo();
		void CalcAngleInfo2(Matrix transA, Matrix transB, Matrix invInertiaWorldA, Matrix invInertiaWorldB);
		void EnableMotor(bool b);
		Vector3 GetPointForAngle(btScalar fAngleInRadians, btScalar fLength);
		void SetAngularOnly(bool angularOnly);
		void SetDamping(btScalar damping);
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2, btScalar _twistSpan, btScalar _softness,
			btScalar _biasFactor, btScalar _relaxationFactor);
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2, btScalar _twistSpan, btScalar _softness,
			btScalar _biasFactor);
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2, btScalar _twistSpan, btScalar _softness);
		void SetLimit(btScalar _swingSpan1, btScalar _swingSpan2, btScalar _twistSpan);
		void SetLimit(int limitIndex, btScalar limitValue);
		void SetMaxMotorImpulse(btScalar maxMotorImpulse);
		void SetMaxMotorImpulseNormalized(btScalar maxMotorImpulse);
		void SetMotorTarget(Quaternion q);
		void SetMotorTargetInConstraintSpace(Quaternion q);
		void UpdateRHS(btScalar timeStep);

		property Matrix AFrame
		{
			Matrix get();
		}

		property Matrix BFrame
		{
			Matrix get();
		}

		property btScalar FixThresh
		{
			btScalar get();
			void set(btScalar value);
		}

		property Matrix FrameOffsetA
		{
			Matrix get();
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
		}

		property bool IsPastSwingLimit
		{
			bool get();
		}

		property int SolveSwingLimit
		{
			int get();
		}

		property int SolveTwistLimit
		{
			int get();
		}

		property btScalar SwingSpan1
		{
			btScalar get();
		}

		property btScalar SwingSpan2
		{
			btScalar get();
		}

		property btScalar TwistAngle
		{
			btScalar get();
		}

		property btScalar TwistLimitSign
		{
			btScalar get();
		}

		property btScalar TwistSpan
		{
			btScalar get();
		}
	};
};
