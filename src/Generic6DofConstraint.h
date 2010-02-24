#pragma once

#include "RigidBody.h"
#include "TypedConstraint.h"

namespace BulletSharp
{
	public ref class RotationalLimitMotor
	{
	private:
		btRotationalLimitMotor* motor;
	internal:
		RotationalLimitMotor(btRotationalLimitMotor* motor);
	public:
		RotationalLimitMotor();
		RotationalLimitMotor(RotationalLimitMotor^ motor);

		btScalar SolveAngularLimits(btScalar timeStep, Vector3 axis,
			btScalar jacDiagABInv, RigidBody^ body0, RigidBody^ body1);
		int TestLimitValue(btScalar test_value);

		property bool IsLimited
		{
			bool get();
		}

		property bool NeedApplyTorques
		{
			bool get();
		}

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

		property btScalar NormalCFM
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar StopCFM
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar StopERP
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar TargetVelocity
		{
			btScalar get();
			void set(btScalar value);
		}

	internal:
		property btRotationalLimitMotor* UnmanagedPointer
		{
			btRotationalLimitMotor* get();
		}
	};

	public ref class TranslationalLimitMotor
	{
	private:
		btTranslationalLimitMotor* motor;
	internal:
		TranslationalLimitMotor(btTranslationalLimitMotor* motor);
	public:
		TranslationalLimitMotor();
		TranslationalLimitMotor(TranslationalLimitMotor^ motor);


		bool IsLimited(int limitIndex);
		bool NeedApplyForce(int limitIndex);
		btScalar SolveLinearAxis(btScalar timeStep, btScalar jacDiagABInv,
			RigidBody^ body1, Vector3 pointInA, RigidBody^ body2, Vector3 pointInB,
			int limit_index, Vector3 axis_normal_on_a, Vector3 anchorPos);
		int TestLimitValue(int limitIndex, btScalar test_value);

		property Vector3 AccumulatedImpulse
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property int CurrentLimit[int]
		{
			int get(int index);
			void set(int index, int value);
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

		property bool EnableMotor[int]
		{
			bool get(int index);
			void set(int index, bool value);
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

		property Vector3 NormalCFM
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Resitution
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 StopCFM
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 StopERP
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

	internal:
		property btTranslationalLimitMotor* UnmanagedPointer
		{
			btTranslationalLimitMotor* get();
		}
	};

	public ref class Generic6DofConstraint : TypedConstraint
	{
	public:
		Generic6DofConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Matrix frameInA, Matrix frameInB, bool useReferenceFrameA);
		Generic6DofConstraint(RigidBody^ rbB, Matrix frameInB,
			bool useReferenceFrameA);

		void CalcAnchorPos();
		void CalculateTransforms();
		void CalculateTransforms(Matrix transA, Matrix transB);
		btScalar GetAngle(int axis_index);
		Vector3 GetAxis(int axis_index);
		btScalar GetRelativePivotPosition(int axis_index);
		RotationalLimitMotor^ GetRotationalLimitMotor(int index);
		bool IsLimited(int limitIndex);
		void SetAngularLowerLimit(Vector3 value);
		void SetAngularUpperLimit(Vector3 value);
		void SetLimit(int axis, btScalar lo, btScalar hi);
		void SetLinearLowerLimit(Vector3 linearLower);
		void SetLinearUpperLimit(Vector3 linearUpper);
		bool TestAngularLimitMotor(int axis_index);
		void UpdateRHS(btScalar timeStep);

		property Matrix CalculatedTransformA
		{
			Matrix get();
		}

		property Matrix CalculatedTransformB
		{
			Matrix get();
		}

		property Matrix FrameOffsetA
		{
			Matrix get();
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
		}

		property TranslationalLimitMotor^ TranslationalLimitMotor
		{
			BulletSharp::TranslationalLimitMotor^ get();
		}

		property bool UseFrameOffset
		{
			bool get();
			void set(bool value);
		}

		property btGeneric6DofConstraint* UnmanagedPointer
		{
			btGeneric6DofConstraint* get() new;
		}
	};
};
