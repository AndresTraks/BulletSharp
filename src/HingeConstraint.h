#pragma once

// Fully implemented as of 12 May 2010

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class HingeConstraint : TypedConstraint
	{
	internal:
		HingeConstraint(btHingeConstraint* constraint);

	public:
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Vector3 pivotInA, Vector3 pivotInB,
			Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Vector3 pivotInA, Vector3 pivotInB,
			Vector3 axisInA, Vector3 axisInB);
		HingeConstraint(RigidBody^ rbA,	Vector3 pivotInA, Vector3 axisInA, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA,	Vector3 pivotInA, Vector3 axisInA);
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,	Matrix rbAFrame, Matrix rbBFrame);
		HingeConstraint(RigidBody^ rbA,	Matrix rbAFrame, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA, Matrix rbAFrame);

		void EnableAngularMotor(bool enableMotor, btScalar targetVelocity, btScalar maxMotorImpulse);
		btScalar GetHingeAngle(Matrix transA, Matrix transB);
		btScalar GetHingeAngle();
		void SetAxis(Vector3 axisInA);
		void SetLimit(btScalar low, btScalar high, btScalar _softness, btScalar _biasFactor, btScalar _relaxationFactor);
		void SetLimit(btScalar low, btScalar high, btScalar _softness, btScalar _biasFactor);
		void SetLimit(btScalar low, btScalar high, btScalar _softness);
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
			void set(bool value);
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

		property btScalar LimitSign
		{
			btScalar get();
		}

		property btScalar LowerLimit
		{
			btScalar get();
		}

		property btScalar UpperLimit
		{
			btScalar get();
		}

		property btScalar MaxMotorImpulse
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MotorTargetVelocity
		{
			btScalar get();
		}

		property int SolveLimit
		{
			int get();
		}

		property bool UseFrameOffset
		{
			bool get();
			void set(bool value);
		}

	internal:
		property btHingeConstraint* UnmanagedPointer
		{
			btHingeConstraint* get() new;
		}
	};
};
