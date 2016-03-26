#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class BoolArray;
	ref class IntArray;
	ref class RigidBody;

	public ref class RotationalLimitMotor2
	{
	internal:
		btRotationalLimitMotor2* _native;

	private:
		bool _preventDelete;

	internal:
		RotationalLimitMotor2(btRotationalLimitMotor2* native, bool preventDelete);

		~RotationalLimitMotor2();
		!RotationalLimitMotor2();

	public:
		RotationalLimitMotor2();
		RotationalLimitMotor2(RotationalLimitMotor2^ limitMotor);

		void TestLimitValue(btScalar testValue);

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

		property btScalar CurrentLimitErrorHi
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar CurrentPosition
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool EnableMotor
		{
			bool get();
			void set(bool value);
		}

		property bool EnableSpring
		{
			bool get();
			void set(bool value);
		}

		property btScalar EquilibriumPoint
		{
			btScalar get();
			void set(btScalar value);
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

		property btScalar LoLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxMotorForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MotorCfm
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MotorErp
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool ServoMotor
		{
			bool get();
			void set(bool value);
		}

		property btScalar ServoTarget
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SpringDamping
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool SpringDampingLimited
		{
			bool get();
			void set(bool value);
		}

		property btScalar SpringStiffness
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool SpringStiffnessLimited
		{
			bool get();
			void set(bool value);
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

	public ref class TranslationalLimitMotor2
	{
	internal:
		btTranslationalLimitMotor2* _native;

	private:
		bool _preventDelete;

	internal:
		TranslationalLimitMotor2(btTranslationalLimitMotor2* native, bool preventDelete);

		~TranslationalLimitMotor2();
		!TranslationalLimitMotor2();

	public:
		TranslationalLimitMotor2();
		TranslationalLimitMotor2(TranslationalLimitMotor2^ other);

		bool IsLimited(int limitIndex);
		void TestLimitValue(int limitIndex, btScalar testValue);

		property Vector3 Bounce
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

		property Vector3 CurrentLimitErrorHi
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 CurrentLinearDiff
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property BoolArray^ EnableMotor
		{
			BoolArray^ get();
		}

		property BoolArray^ EnableSpring
		{
			BoolArray^ get();
		}

		property Vector3 EquilibriumPoint
		{
			Vector3 get();
			void set(Vector3 value);
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

		property Vector3 MotorCfm
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 MotorErp
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property BoolArray^ ServoMotor
		{
			BoolArray^ get();
		}

		property Vector3 ServoTarget
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 SpringDamping
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property BoolArray^ SpringDampingLimited
		{
			BoolArray^ get();
		}

		property Vector3 SpringStiffness
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property BoolArray^ SpringStiffnessLimited
		{
			BoolArray^ get();
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

	public ref class Generic6DofSpring2Constraint : TypedConstraint
	{
	private:
		array<RotationalLimitMotor2^>^ _angularLimits;
		TranslationalLimitMotor2^ _linearLimits;

	internal:
		Generic6DofSpring2Constraint(btGeneric6DofSpring2Constraint* native);

	public:
		Generic6DofSpring2Constraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
			Matrix frameInA, Matrix frameInB, RotateOrder rotOrder);
		Generic6DofSpring2Constraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
			Matrix frameInA, Matrix frameInB);
		Generic6DofSpring2Constraint(RigidBody^ rigidBodyB, Matrix frameInB, RotateOrder rotOrder);
		Generic6DofSpring2Constraint(RigidBody^ rigidBodyB, Matrix frameInB);

		void CalculateTransforms(Matrix transA, Matrix transB);
		void CalculateTransforms();
		void EnableMotor(int index, bool onOff);
		void EnableSpring(int index, bool onOff);
		btScalar GetAngle(int axisIndex);
		Vector3 GetAxis(int axisIndex);
		btScalar GetRelativePivotPosition(int axisIndex);
		RotationalLimitMotor2^ GetRotationalLimitMotor(int index);
		bool IsLimited(int limitIndex);
		void SetAxis(Vector3 axis1, Vector3 axis2);
		void SetBounce(int index, btScalar bounce);
		void SetDamping(int index, btScalar damping, bool limitIfNeeded);
		void SetDamping(int index, btScalar damping);
		void SetEquilibriumPoint();
		void SetEquilibriumPoint(int index, btScalar val);
		void SetEquilibriumPoint(int index);
		void SetFrames(Matrix frameA, Matrix frameB);
		void SetLimit(int axis, btScalar lo, btScalar hi);
		void SetLimitReversed(int axis, btScalar lo, btScalar hi);
		void SetMaxMotorForce(int index, btScalar force);
		void SetServo(int index, bool onOff);
		void SetServoTarget(int index, btScalar target);
		void SetStiffness(int index, btScalar stiffness, bool limitIfNeeded);
		void SetStiffness(int index, btScalar stiffness);
		void SetTargetVelocity(int index, btScalar velocity);

		property Vector3 AngularLowerLimit
		{
			Vector3 get();
			void set(Vector3 angularLower);
		}

		property Vector3 AngularLowerLimitReversed
		{
			Vector3 get();
			void set(Vector3 angularLower);
		}

		property Vector3 AngularUpperLimit
		{
			Vector3 get();
			void set(Vector3 angularUpper);
		}

		property Vector3 AngularUpperLimitReversed
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

		property Matrix FrameOffsetA
		{
			Matrix get();
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
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

		property RotateOrder RotationOrder
		{
			RotateOrder get();
			void set(RotateOrder order);
		}

		property TranslationalLimitMotor2^ TranslationalLimitMotor
		{
			TranslationalLimitMotor2^ get();
		}
	};
};
