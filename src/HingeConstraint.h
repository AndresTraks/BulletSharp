#pragma once

#include "RigidBody.h"
#include "TypedConstraint.h"

namespace BulletSharp
{
	public ref class HingeConstraint : TypedConstraint
	{
	public:
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Vector3 pivotInA, Vector3 pivotInB,
			Vector3 axisInA, Vector3 axisInB,
			bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Vector3 pivotInA, Vector3 pivotInB,
			Vector3 axisInA, Vector3 axisInB);
		HingeConstraint(RigidBody^ rbA,	Vector3 pivotInA, Vector3 axisInA,
			bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA,	Vector3 pivotInA, Vector3 axisInA);
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Matrix rbAFrame, Matrix rbBFrame, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Matrix rbAFrame, Matrix rbBFrame);
		HingeConstraint(RigidBody^ rbA,	Matrix rbAFrame, bool useReferenceFrameA);
		HingeConstraint(RigidBody^ rbA, Matrix rbAFrame);

		void EnableAngularMotor(bool enableMotor,
			btScalar targetVelocity, btScalar maxMotorImpulse);

		void SetLimit(btScalar low, btScalar high,
			btScalar _softness, btScalar _biasFactor, btScalar _relaxationFactor);
		void SetLimit(btScalar low, btScalar high,
			btScalar _softness, btScalar _biasFactor);
		void SetLimit(btScalar low, btScalar high,
			btScalar _softness);
		void SetLimit(btScalar low, btScalar high);

		property btHingeConstraint* UnmanagedPointer
		{
			btHingeConstraint* get() new;
		}
	};
};
