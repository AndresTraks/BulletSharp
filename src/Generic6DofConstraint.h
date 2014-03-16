#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class BoolArray;
	ref class IntArray;
	ref class RigidBody;

	public ref class RotationalLimitMotor
	{
	internal:
		btRotationalLimitMotor* _native;
		RotationalLimitMotor(btRotationalLimitMotor* native);

	public:
		RotationalLimitMotor();
		RotationalLimitMotor(RotationalLimitMotor^ limitMotor);

		btScalar SolveAngularLimits(btScalar timeStep, Vector3 axis, btScalar jacDiagABInv, RigidBody^ body0, RigidBody^ body1);
		int TestLimitValue(btScalar test_value);

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
	};

	public ref class TranslationalLimitMotor
	{
	internal:
		btTranslationalLimitMotor* _native;
		TranslationalLimitMotor(btTranslationalLimitMotor* native);

	public:
		TranslationalLimitMotor();
		TranslationalLimitMotor(TranslationalLimitMotor^ other);

		bool IsLimited(int limitIndex);
		bool NeedApplyForce(int limitIndex);
		btScalar SolveLinearAxis(btScalar timeStep, btScalar jacDiagABInv, RigidBody^ body1, Vector3 pointInA, RigidBody^ body2, Vector3 pointInB, int limit_index, Vector3 axis_normal_on_a, Vector3 anchorPos);
		int TestLimitValue(int limitIndex, btScalar test_value);

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

		property Vector3 NormalCFM
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Restitution
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
	};

	public ref class Generic6DofConstraint : TypedConstraint
	{
	internal:
		Generic6DofConstraint(btGeneric6DofConstraint* native);

	public:
		Generic6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
		Generic6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB);

		void CalcAnchorPos();
		void CalculateTransforms(Matrix transA, Matrix transB);
		void CalculateTransforms();
		//int GetLimitMotorInfo2(RotationalLimitMotor^ limot, Matrix transA, Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB, btConstraintInfo2^ info, int row, Vector3 ax1, int rotational, int rotAllowed);
		//int GetLimitMotorInfo2(RotationalLimitMotor^ limot, Matrix transA, Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB, btConstraintInfo2^ info, int row, Vector3 ax1, int rotational);
		btScalar GetAngle(int axis_index);
		Vector3 GetAxis(int axis_index);
		//void GetInfo2NonVirtual(btConstraintInfo2^ info, Matrix transA, Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB);
		btScalar GetRelativePivotPosition(int axis_index);
		RotationalLimitMotor^ GetRotationalLimitMotor(int index);
		bool IsLimited(int limitIndex);
		void SetAxis(Vector3 axis1, Vector3 axis2);
		void SetFrames(Matrix frameA, Matrix frameB);
		void SetLimit(int axis, btScalar lo, btScalar hi);
		bool TestAngularLimitMotor(int axis_index);
		void UpdateRHS(btScalar timeStep);

		property Vector3 AngularLowerLimit
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AngularUpperLimit
		{
			Vector3 get();
			void set(Vector3 value);
		}

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
			void set(Matrix value);
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
			void set(Matrix value);
		}
/*
		property void Info1NonVirtual
		{
			void get();
		}
*/
		property Vector3 LinearLowerLimit
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 LinearUpperLimit
		{
			Vector3 get();
			void set(Vector3 value);
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
	};
};
