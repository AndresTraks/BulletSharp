#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "HingeConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btHingeConstraint*>(_native)

HingeConstraint::HingeConstraint(btHingeConstraint* native)
	: TypedConstraint(native)
{
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA,
	Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA)
	: TypedConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(pivotInB);
	VECTOR3_CONV(axisInA);
	VECTOR3_CONV(axisInB);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB), VECTOR3_USE(axisInA), VECTOR3_USE(axisInB),
		useReferenceFrameA);
	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);

	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA,
	Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB)
	: TypedConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(pivotInB);
	VECTOR3_CONV(axisInA);
	VECTOR3_CONV(axisInB);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB), VECTOR3_USE(axisInA), VECTOR3_USE(axisInB));
	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);

	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA,
	bool useReferenceFrameA)
	: TypedConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(axisInA);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA),
		VECTOR3_USE(axisInA), useReferenceFrameA);
	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(axisInA);

	_rigidBodyA = rigidBodyA;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA)
	: TypedConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(axisInA);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA),
		VECTOR3_USE(axisInA));
	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(axisInA);

	_rigidBodyA = rigidBodyA;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rbAFrame,
	Matrix rbBFrame, bool useReferenceFrameA)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(rbAFrame);
	TRANSFORM_CONV(rbBFrame);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(rbAFrame), TRANSFORM_USE(rbBFrame), useReferenceFrameA);
	TRANSFORM_DEL(rbAFrame);
	TRANSFORM_DEL(rbBFrame);

	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rbAFrame,
	Matrix rbBFrame)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(rbAFrame);
	TRANSFORM_CONV(rbBFrame);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(rbAFrame), TRANSFORM_USE(rbBFrame));
	TRANSFORM_DEL(rbAFrame);
	TRANSFORM_DEL(rbBFrame);

	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Matrix rbAFrame, bool useReferenceFrameA)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(rbAFrame);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, TRANSFORM_USE(rbAFrame),
		useReferenceFrameA);
	TRANSFORM_DEL(rbAFrame);

	_rigidBodyA = rigidBodyA;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Matrix rbAFrame)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(rbAFrame);
	UnmanagedPointer = new btHingeConstraint(*(btRigidBody*)rigidBodyA->_native, TRANSFORM_USE(rbAFrame));
	TRANSFORM_DEL(rbAFrame);

	_rigidBodyA = rigidBodyA;
}

void HingeConstraint::EnableAngularMotor(bool enableMotor, btScalar targetVelocity,
	btScalar maxMotorImpulse)
{
	Native->enableAngularMotor(enableMotor, targetVelocity, maxMotorImpulse);
}

btScalar HingeConstraint::GetHingeAngle(Matrix transA, Matrix transB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	btScalar ret = Native->getHingeAngle(TRANSFORM_USE(transA), TRANSFORM_USE(transB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	return ret;
}

void HingeConstraint::GetInfo1NonVirtual(ConstraintInfo1^ info)
{
	Native->getInfo1NonVirtual(info->_native);
}

#ifndef DISABLE_INTERNAL
void HingeConstraint::GetInfo2Internal(ConstraintInfo2^ info, Matrix transA, Matrix transB,
	Vector3 angVelA, Vector3 angVelB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	VECTOR3_CONV(angVelA);
	VECTOR3_CONV(angVelB);
	Native->getInfo2Internal(info->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
		VECTOR3_USE(angVelA), VECTOR3_USE(angVelB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	VECTOR3_DEL(angVelA);
	VECTOR3_DEL(angVelB);
}

void HingeConstraint::GetInfo2InternalUsingFrameOffset(ConstraintInfo2^ info, Matrix transA,
	Matrix transB, Vector3 angVelA, Vector3 angVelB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	VECTOR3_CONV(angVelA);
	VECTOR3_CONV(angVelB);
	Native->getInfo2InternalUsingFrameOffset(info->_native, TRANSFORM_USE(transA),
		TRANSFORM_USE(transB), VECTOR3_USE(angVelA), VECTOR3_USE(angVelB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	VECTOR3_DEL(angVelA);
	VECTOR3_DEL(angVelB);
}

void HingeConstraint::GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA, Matrix transB,
	Vector3 angVelA, Vector3 angVelB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	VECTOR3_CONV(angVelA);
	VECTOR3_CONV(angVelB);
	Native->getInfo2NonVirtual(info->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
		VECTOR3_USE(angVelA), VECTOR3_USE(angVelB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	VECTOR3_DEL(angVelA);
	VECTOR3_DEL(angVelB);
}
#endif

void HingeConstraint::SetAxis(Vector3 axisInA)
{
	VECTOR3_CONV(axisInA);
	Native->setAxis(VECTOR3_USE(axisInA));
	VECTOR3_DEL(axisInA);
}

void HingeConstraint::SetFrames(Matrix frameA, Matrix frameB)
{
	TRANSFORM_CONV(frameA);
	TRANSFORM_CONV(frameB);
	Native->setFrames(TRANSFORM_USE(frameA), TRANSFORM_USE(frameB));
	TRANSFORM_DEL(frameA);
	TRANSFORM_DEL(frameB);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high, btScalar softness, btScalar biasFactor,
	btScalar relaxationFactor)
{
	Native->setLimit(low, high, softness, biasFactor, relaxationFactor);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high, btScalar softness, btScalar biasFactor)
{
	Native->setLimit(low, high, softness, biasFactor);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high, btScalar softness)
{
	Native->setLimit(low, high, softness);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high)
{
	Native->setLimit(low, high);
}

void HingeConstraint::SetMotorTarget(btScalar targetAngle, btScalar dt)
{
	Native->setMotorTarget(targetAngle, dt);
}

void HingeConstraint::SetMotorTarget(Quaternion qAinB, btScalar dt)
{
	QUATERNION_CONV(qAinB);
	Native->setMotorTarget(QUATERNION_USE(qAinB), dt);
	QUATERNION_DEL(qAinB);
}

void HingeConstraint::TestLimit(Matrix transA, Matrix transB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	Native->testLimit(TRANSFORM_USE(transA), TRANSFORM_USE(transB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
}

void HingeConstraint::UpdateRHS(btScalar timeStep)
{
	Native->updateRHS(timeStep);
}

Matrix HingeConstraint::AFrame::get()
{
	return Math::BtTransformToMatrix(&Native->getAFrame());
}

bool HingeConstraint::AngularOnly::get()
{
	return Native->getAngularOnly();
}
void HingeConstraint::AngularOnly::set(bool angularOnly)
{
	Native->setAngularOnly(angularOnly);
}

Matrix HingeConstraint::BFrame::get()
{
	return Math::BtTransformToMatrix(&Native->getBFrame());
}

bool HingeConstraint::EnableMotor::get()
{
	return Native->getEnableAngularMotor();
}
void HingeConstraint::EnableMotor::set(bool enableMotor)
{
	Native->enableMotor(enableMotor);
}

Matrix HingeConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetA());
}

Matrix HingeConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetB());
}

btScalar HingeConstraint::HingeAngle::get()
{
	return Native->getHingeAngle();
}

btScalar HingeConstraint::LimitSign::get()
{
	return Native->getLimitSign();
}

btScalar HingeConstraint::LowerLimit::get()
{
	return Native->getLowerLimit();
}

btScalar HingeConstraint::MaxMotorImpulse::get()
{
	return Native->getMaxMotorImpulse();
}
void HingeConstraint::MaxMotorImpulse::set(btScalar maxMotorImpulse)
{
	Native->setMaxMotorImpulse(maxMotorImpulse);
}

btScalar HingeConstraint::MotorTargetVelocity::get()
{
	return Native->getMotorTargetVelosity();
}

int HingeConstraint::SolveLimit::get()
{
	return Native->getSolveLimit();
}

btScalar HingeConstraint::UpperLimit::get()
{
	return Native->getUpperLimit();
}

bool HingeConstraint::UseFrameOffset::get()
{
	return Native->getUseFrameOffset();
}
void HingeConstraint::UseFrameOffset::set(bool frameOffsetOnOff)
{
	Native->setUseFrameOffset(frameOffsetOnOff);
}

#endif
