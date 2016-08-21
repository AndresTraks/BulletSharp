#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "MultiBody.h"
#include "MultiBodyJointMotor.h"

#define Native static_cast<btMultiBodyJointMotor*>(_native)

MultiBodyJointMotor::MultiBodyJointMotor(btMultiBodyJointMotor* native)
	: MultiBodyConstraint(native)
{
}

MultiBodyJointMotor::MultiBodyJointMotor(MultiBody^ body, int link, btScalar desiredVelocity,
	btScalar maxMotorImpulse)
	: MultiBodyConstraint(new btMultiBodyJointMotor(body->_native, link, desiredVelocity,
		maxMotorImpulse))
{
	_multiBodyA = body;
	_multiBodyB = body;
}

MultiBodyJointMotor::MultiBodyJointMotor(MultiBody^ body, int link, int linkDoF,
	btScalar desiredVelocity, btScalar maxMotorImpulse)
	: MultiBodyConstraint(new btMultiBodyJointMotor(body->_native, link, linkDoF,
		desiredVelocity, maxMotorImpulse))
{
	_multiBodyA = body;
	_multiBodyB = body;
}

#ifndef DISABLE_DEBUGDRAW
void MultiBodyJointMotor::DebugDraw(IDebugDraw^ drawer)
{
	// TODO
}
#endif

void MultiBodyJointMotor::SetPositionTarget(btScalar posTarget, btScalar kp)
{
	Native->setPositionTarget(posTarget, kp);
}

void MultiBodyJointMotor::SetPositionTarget(btScalar posTarget)
{
	Native->setPositionTarget(posTarget);
}

void MultiBodyJointMotor::SetVelocityTarget(btScalar velTarget, btScalar kd)
{
	Native->setVelocityTarget(velTarget, kd);
}

void MultiBodyJointMotor::SetVelocityTarget(btScalar velTarget)
{
	Native->setVelocityTarget(velTarget);
}

#endif
