#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	[Flags]
	public enum class ConeTwistFlags
	{
		None = 0,
		LinearCfm = BT_CONETWIST_FLAGS_LIN_CFM,
		LinearErp = BT_CONETWIST_FLAGS_LIN_ERP,
		AngularCfm = BT_CONETWIST_FLAGS_ANG_CFM
	};

	public ref class ConeTwistConstraint : TypedConstraint
	{
	public:
		ConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame,
			Matrix rigidBodyBFrame);
		ConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame);

		void CalcAngleInfo();
		void CalcAngleInfo2(Matrix transA, Matrix transB, Matrix invInertiaWorldA,
			Matrix invInertiaWorldB);
		void EnableMotor(bool b);
		void GetInfo1NonVirtual(ConstraintInfo1^ info);
		void GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA, Matrix transB,
			Matrix invInertiaWorldA, Matrix invInertiaWorldB);
		btScalar GetLimit(int limitIndex);
		Vector3 GetPointForAngle(btScalar fAngleInRadians, btScalar fLength);
		void SetFrames(Matrix frameA, Matrix frameB);
		void SetLimit(int limitIndex, btScalar limitValue);
		void SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan,
			btScalar softness, btScalar biasFactor, btScalar relaxationFactor);
		void SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan,
			btScalar softness, btScalar biasFactor);
		void SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan,
			btScalar softness);
		void SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan);
		void SetMaxMotorImpulseNormalized(btScalar maxMotorImpulse);
		void SetMotorTargetInConstraintSpace(Quaternion q);
		void UpdateRhs(btScalar timeStep);

		property Matrix AFrame
		{
			Matrix get();
		}

		property bool AngularOnly
		{
			bool get();
			void set(bool angularOnly);
		}

		property Matrix BFrame
		{
			Matrix get();
		}

		property btScalar BiasFactor
		{
			btScalar get();
		}

		property btScalar Damping
		{
			btScalar get();
			void set(btScalar damping);
		}

		property btScalar FixThresh
		{
			btScalar get();
			void set(btScalar fixThresh);
		}

		property ConeTwistFlags Flags
		{
			ConeTwistFlags get();
		}

		property Matrix FrameOffsetA
		{
			Matrix get();
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
		}

		property bool IsMaxMotorImpulseNormalized
		{
			bool get();
		}

		property bool IsMotorEnabled
		{
			bool get();
		}

		property bool IsPastSwingLimit
		{
			bool get();
		}

		property btScalar LimitSoftness
		{
			btScalar get();
		}

		property btScalar MaxMotorImpulse
		{
			btScalar get();
			void set(btScalar maxMotorImpulse);
		}

		property Quaternion MotorTarget
		{
			Quaternion get();
			void set(Quaternion q);
		}

		property btScalar RelaxationFactor
		{
			btScalar get();
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
