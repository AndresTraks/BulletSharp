#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class HingeConstraint : TypedConstraint
	{
	private:
		RigidBody^ _rigidBodyA;
		RigidBody^ _rigidBodyB;

	internal:
		HingeConstraint(btHingeConstraint* native);

	public:
		HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA, Vector3 pivotInB,
			Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA, Vector3 pivotInB,
			Vector3 axisInA, Vector3 axisInB);
		HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA);
		HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame,
			bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame);
		HingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame);

		void EnableAngularMotor(bool enableMotor, btScalar targetVelocity, btScalar maxMotorImpulse);
		btScalar GetHingeAngle(Matrix transA, Matrix transB);
		void GetInfo1NonVirtual(ConstraintInfo1^ info);
		void GetInfo2Internal(ConstraintInfo2^ info, Matrix transA, Matrix transB,
			Vector3 angVelA, Vector3 angVelB);
		void GetInfo2InternalUsingFrameOffset(ConstraintInfo2^ info, Matrix transA,
			Matrix transB, Vector3 angVelA, Vector3 angVelB);
		void GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA, Matrix transB,
			Vector3 angVelA, Vector3 angVelB);
		void SetAxis(Vector3 axisInA);
		void SetFrames(Matrix frameA, Matrix frameB);
		void SetLimit(btScalar low, btScalar high, btScalar softness, btScalar biasFactor,
			btScalar relaxationFactor);
		void SetLimit(btScalar low, btScalar high, btScalar softness, btScalar biasFactor);
		void SetLimit(btScalar low, btScalar high, btScalar softness);
		void SetLimit(btScalar low, btScalar high);
		void SetMotorTarget(btScalar targetAngle, btScalar dt);
		void SetMotorTarget(Quaternion qAinB, btScalar dt);
		void TestLimit(Matrix transA, Matrix transB);
		void UpdateRHS(btScalar timeStep);

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

		property bool EnableMotor
		{
			bool get();
			void set(bool value);
		}

		property Matrix FrameOffsetA
		{
			Matrix get();
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
		}

		property btScalar HingeAngle
		{
			btScalar get();
		}

		property btScalar LimitSign
		{
			btScalar get();
		}

		property btScalar LowerLimit
		{
			btScalar get();
		}

		property btScalar MaxMotorImpulse
		{
			btScalar get();
			void set(btScalar maxMotorImpulse);
		}

		property btScalar MotorTargetVelocity
		{
			btScalar get();
		}

		property int SolveLimit
		{
			int get();
		}

		property btScalar UpperLimit
		{
			btScalar get();
		}

		property bool UseFrameOffset
		{
			bool get();
			void set(bool frameOffsetOnOff);
		}
	};

	public ref class HingeAccumulatedAngleConstraint : HingeConstraint
	{
	internal:
		HingeAccumulatedAngleConstraint(btHingeAccumulatedAngleConstraint* native);

	public:
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, RigidBody^ rbB, Vector3 pivotInA,
			Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA);
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, RigidBody^ rbB, Vector3 pivotInA,
			Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB);
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA,
			bool useReferenceFrameA);
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA);
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame,
			Matrix rbBFrame, bool useReferenceFrameA);
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame,
			Matrix rbBFrame);
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, Matrix rbAFrame, bool useReferenceFrameA);
		HingeAccumulatedAngleConstraint(RigidBody^ rbA, Matrix rbAFrame);

		property btScalar AccumulatedHingeAngle
		{
			btScalar get();
			void set(btScalar accAngle);
		}
	};
};
