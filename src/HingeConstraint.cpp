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
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* pivotInBTemp = Math::Vector3ToBtVector3(pivotInB);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);
	btVector3* axisInBTemp = Math::Vector3ToBtVector3(axisInB);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer,
		*pivotInATemp, *pivotInBTemp, *axisInATemp, *axisInBTemp, useReferenceFrameA);

	delete pivotInATemp;
	delete pivotInBTemp;
	delete axisInATemp;
	delete axisInBTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB)
: TypedConstraint(0)
{
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* pivotInBTemp = Math::Vector3ToBtVector3(pivotInB);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);
	btVector3* axisInBTemp = Math::Vector3ToBtVector3(axisInB);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer,
		*pivotInATemp, *pivotInBTemp, *axisInATemp, *axisInBTemp);

	delete pivotInATemp;
	delete pivotInBTemp;
	delete axisInATemp;
	delete axisInBTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA,
	bool useReferenceFrameA)
: TypedConstraint(0)
{
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *pivotInATemp, *axisInATemp, useReferenceFrameA);

	delete pivotInATemp;
	delete axisInATemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA, Vector3 axisInA)
: TypedConstraint(0)
{
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *pivotInATemp, *axisInATemp);

	delete pivotInATemp;
	delete axisInATemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp, useReferenceFrameA);

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp);

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *rigidBodyAFrameTemp, useReferenceFrameA);

	delete rigidBodyAFrameTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	UnmanagedPointer = new btHingeConstraint(*rigidBodyA->UnmanagedPointer, *rigidBodyAFrameTemp);

	delete rigidBodyAFrameTemp;
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

	delete transATemp;
	delete transBTemp;

	return angle;
}

btScalar HingeConstraint::GetHingeAngle()
{
	return UnmanagedPointer->getHingeAngle();
}

void HingeConstraint::SetAxis(Vector3 axisInA)
{
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);
	UnmanagedPointer->setAxis(*axisInATemp);
	delete axisInATemp;
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
	delete qAinBTemp;
}

void HingeConstraint::TestLimit(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	UnmanagedPointer->testLimit(*transATemp, *transBTemp);

	delete transATemp;
	delete transBTemp;
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
