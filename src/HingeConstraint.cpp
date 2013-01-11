#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "HingeConstraint.h"
#include "RigidBody.h"

HingeConstraint::HingeConstraint(btHingeConstraint* constraint)
: TypedConstraint(constraint)
{
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA)
: TypedConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);
	VECTOR3_DEF(axisInA);
	VECTOR3_DEF(axisInB);

	UnmanagedPointer = new btHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB), VECTOR3_USE(axisInA), VECTOR3_USE(axisInB), useReferenceFrameA);

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB)
: TypedConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);
	VECTOR3_DEF(axisInA);
	VECTOR3_DEF(axisInB);

	UnmanagedPointer = new btHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB), VECTOR3_USE(axisInA), VECTOR3_USE(axisInB));

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA,
	bool useReferenceFrameA)
: TypedConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(axisInA);

	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(axisInA), useReferenceFrameA);

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(axisInA);
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA)
: TypedConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(axisInA);

	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(axisInA));

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(axisInA);
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp, useReferenceFrameA);

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp);

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp, useReferenceFrameA);
	ALIGNED_FREE(rigidBodyAFrameTemp);
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyAFrameTemp);
}

void HingeConstraint::EnableAngularMotor(bool enableMotor,
	btScalar targetVelocity, btScalar maxMotorImpulse)
{
	UnmanagedPointer->enableAngularMotor(enableMotor, targetVelocity, maxMotorImpulse);
}

btScalar HingeConstraint::GetHingeAngle(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	btScalar angle = UnmanagedPointer->getHingeAngle(*transATemp, *transBTemp);

	ALIGNED_FREE(transATemp);
	ALIGNED_FREE(transBTemp);

	return angle;
}

btScalar HingeConstraint::GetHingeAngle()
{
	return UnmanagedPointer->getHingeAngle();
}

void HingeConstraint::SetAxis(Vector3 axisInA)
{
	VECTOR3_DEF(axisInA);
	UnmanagedPointer->setAxis(VECTOR3_USE(axisInA));
	VECTOR3_DEL(axisInA);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high, btScalar _softness, btScalar _biasFactor, btScalar _relaxationFactor)
{
	UnmanagedPointer->setLimit(low, high, _softness, _biasFactor, _relaxationFactor);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high, btScalar _softness, btScalar _biasFactor)
{
	UnmanagedPointer->setLimit(low, high, _softness, _biasFactor);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high, btScalar _softness)
{
	UnmanagedPointer->setLimit(low, high, _softness);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high)
{
	UnmanagedPointer->setLimit(low, high);
}

void HingeConstraint::SetMotorTarget(btScalar targetAngle, btScalar dt)
{
	UnmanagedPointer->setMotorTarget(targetAngle, dt);
}

void HingeConstraint::SetMotorTarget(Quaternion qAinB, btScalar dt)
{
	btQuaternion* qAinBTemp = Math::QuaternionToBtQuat(qAinB);
	UnmanagedPointer->setMotorTarget(*qAinBTemp, dt);
	ALIGNED_FREE(qAinBTemp);
}

void HingeConstraint::TestLimit(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	UnmanagedPointer->testLimit(*transATemp, *transBTemp);

	ALIGNED_FREE(transATemp);
	ALIGNED_FREE(transBTemp);
}

void HingeConstraint::UpdateRHS(btScalar timeStep)
{
	UnmanagedPointer->updateRHS(timeStep);
}

Matrix HingeConstraint::AFrame::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getAFrame());
}

bool HingeConstraint::AngularOnly::get()
{
	return UnmanagedPointer->getAngularOnly();
}
void HingeConstraint::AngularOnly::set(bool value)
{
	UnmanagedPointer->setAngularOnly(value);
}

Matrix HingeConstraint::BFrame::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getAFrame());
}

bool HingeConstraint::EnableMotor::get()
{
	return UnmanagedPointer->getEnableAngularMotor();
}
void HingeConstraint::EnableMotor::set(bool value)
{
	UnmanagedPointer->enableMotor(value);
}

Matrix HingeConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetA());
}

Matrix HingeConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetB());
}

btScalar HingeConstraint::LimitSign::get()
{
	return UnmanagedPointer->getLimitSign();
}

btScalar HingeConstraint::UpperLimit::get()
{
	return UnmanagedPointer->getUpperLimit();
}

btScalar HingeConstraint::LowerLimit::get()
{
	return UnmanagedPointer->getLowerLimit();
}

btScalar HingeConstraint::MaxMotorImpulse::get()
{
	return UnmanagedPointer->getMaxMotorImpulse();
}
void HingeConstraint::MaxMotorImpulse::set(btScalar value)
{
	UnmanagedPointer->setMaxMotorImpulse(value);
}

btScalar HingeConstraint::MotorTargetVelocity::get()
{
	//return UnmanagedPointer->getMotorTargetVelocity();
	return UnmanagedPointer->getMotorTargetVelosity();
}

int HingeConstraint::SolveLimit::get()
{
	return UnmanagedPointer->getSolveLimit();
}

bool HingeConstraint::UseFrameOffset::get()
{
	return UnmanagedPointer->getUseFrameOffset();
}
void HingeConstraint::UseFrameOffset::set(bool value)
{
	UnmanagedPointer->setUseFrameOffset(value);
}

btHingeConstraint* HingeConstraint::UnmanagedPointer::get()
{
	return (btHingeConstraint*)TypedConstraint::UnmanagedPointer;
}

#endif
