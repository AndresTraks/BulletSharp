#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "MultiBody.h"
#include "MultiBodyJointMotor.h"

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

#endif
