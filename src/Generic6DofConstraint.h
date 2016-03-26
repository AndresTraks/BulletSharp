#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class BoolArray;
	ref class IntArray;
	ref class RigidBody;

	[Flags]
	public enum class SixDofFlags
	{
		None = 0,
		CfmNormal = BT_6DOF_FLAGS_CFM_NORM,
		CfmStop = BT_6DOF_FLAGS_CFM_STOP,
		ErpStop = BT_6DOF_FLAGS_ERP_STOP
	};

	public ref class RotationalLimitMotor
	{
	internal:
		btRotationalLimitMotor* _native;

	private:
		bool _preventDelete;

	internal:
		RotationalLimitMotor(btRotationalLimitMotor* native, bool preventDelete);

		~RotationalLimitMotor();
		!RotationalLimitMotor();

	public:
		RotationalLimitMotor();
		RotationalLimitMotor(RotationalLimitMotor^ limitMotor);

		btScalar SolveAngularLimits(btScalar timeStep, Vector3 axis, btScalar jacDiagABInv,
			RigidBody^ body0, RigidBody^ body1);
		int TestLimitValue(btScalar testValue);

		property btScalar AccumulatedImpulse
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Bounce
		{
			btScalar get();
			void set(btScalar value);
		}

		property int CurrentLimit
		{
			int get();
			void set(int value);
		}

		property btScalar CurrentLimitError
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar CurrentPosition
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Damping
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool EnableMotor
		{
			bool get();
			void set(bool value);
		}

		property btScalar HiLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool IsLimited
		{
			bool get();
		}

		property btScalar LimitSoftness
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar LoLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxLimitForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxMotorForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool NeedApplyTorques
		{
			bool get();
		}

		property btScalar NormalCfm
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar StopCfm
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar StopErp
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar TargetVelocity
		{
			btScalar get();
			void set(btScalar value);
		}
	};

	public ref class TranslationalLimitMotor
	{
	internal:
		btTranslationalLimitMotor* _native;

	private:
		bool _preventDelete;

	internal:
		TranslationalLimitMotor(btTranslationalLimitMotor* native, bool preventDelete);

		~TranslationalLimitMotor();
		!TranslationalLimitMotor();

	public:
		TranslationalLimitMotor();
		TranslationalLimitMotor(TranslationalLimitMotor^ other);

		bool IsLimited(int limitIndex);
		bool NeedApplyForce(int limitIndex);
		btScalar SolveLinearAxis(btScalar timeStep, btScalar jacDiagABInv, RigidBody^ body1,
			Vector3 pointInA, RigidBody^ body2, Vector3 pointInB, int limitIndex, Vector3 axisNormalOnA,
			Vector3 anchorPos);
		int TestLimitValue(int limitIndex, btScalar testValue);

		property Vector3 AccumulatedImpulse
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property IntArray^ CurrentLimit
		{
			IntArray^ get();
		}

		property Vector3 CurrentLimitError
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 CurrentLinearDiff
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Damping
		{
			btScalar get();
			void set(btScalar value);
		}

		property BoolArray^ EnableMotor
		{
			BoolArray^ get();
		}

		property btScalar LimitSoftness
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 LowerLimit
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 MaxMotorForce
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 NormalCfm
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Restitution
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 StopCfm
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 StopErp
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 TargetVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 UpperLimit
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};

	public ref class Generic6DofConstraint : TypedConstraint
	{
	private:
		array<RotationalLimitMotor^>^ _angularLimits;
		TranslationalLimitMotor^ _linearLimits;

	internal:
		Generic6DofConstraint(btGeneric6DofConstraint* native);

	public:
		Generic6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA,
			Matrix frameInB, bool useLinearReferenceFrameA);
		Generic6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB);

		void CalcAnchorPos();
		void CalculateTransforms(Matrix transA, Matrix transB);
		void CalculateTransforms();
		int GetLimitMotorInfo2(RotationalLimitMotor^ limitMotor, Matrix transA, Matrix transB,
			Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB, ConstraintInfo2^ info,
			int row, Vector3 ax1, int rotational, int rotAllowed);
		int GetLimitMotorInfo2(RotationalLimitMotor^ limitMotor, Matrix transA, Matrix transB,
			Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB, ConstraintInfo2^ info,
			int row, Vector3 ax1, int rotational);
		btScalar GetAngle(int axisIndex);
		Vector3 GetAxis(int axisIndex);
		void GetInfo1NonVirtual(ConstraintInfo1^ info);
		void GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA, Matrix transB,
			Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB);
		btScalar GetRelativePivotPosition(int axisIndex);
		RotationalLimitMotor^ GetRotationalLimitMotor(int index);
		bool IsLimited(int limitIndex);
		void SetAxis(Vector3 axis1, Vector3 axis2);
		void SetFrames(Matrix frameA, Matrix frameB);
		void SetLimit(int axis, btScalar lo, btScalar hi);
		bool TestAngularLimitMotor(int axisIndex);
		void UpdateRhs(btScalar timeStep);

		property Vector3 AngularLowerLimit
		{
			Vector3 get();
			void set(Vector3 angularLower);
		}

		property Vector3 AngularUpperLimit
		{
			Vector3 get();
			void set(Vector3 angularUpper);
		}

		property Matrix CalculatedTransformA
		{
			Matrix get();
		}

		property Matrix CalculatedTransformB
		{
			Matrix get();
		}

		property SixDofFlags Flags
		{
			SixDofFlags get();
		}

		property Matrix FrameOffsetA
		{
			Matrix get();
			void set(Matrix value);
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
			void set(Matrix value);
		}

		property Vector3 LinearLowerLimit
		{
			Vector3 get();
			void set(Vector3 linearLower);
		}

		property Vector3 LinearUpperLimit
		{
			Vector3 get();
			void set(Vector3 linearUpper);
		}

		property TranslationalLimitMotor^ TranslationalLimitMotor
		{
			BulletSharp::TranslationalLimitMotor^ get();
		}

		property bool UseFrameOffset
		{
			bool get();
			void set(bool frameOffsetOnOff);
		}

		property bool UseLinearReferenceFrameA
		{
			bool get();
			void set(bool linearReferenceFrameA);
		}
	};
};
