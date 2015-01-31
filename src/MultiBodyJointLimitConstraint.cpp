#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "MultiBody.h"
#include "MultiBodyJointLimitConstraint.h"

MultiBodyJointLimitConstraint::MultiBodyJointLimitConstraint(btMultiBodyJointLimitConstraint* native)
	: MultiBodyConstraint(native)
{
}

MultiBodyJointLimitConstraint::MultiBodyJointLimitConstraint(MultiBody^ body, int link,
	btScalar lower, btScalar upper)
	: MultiBodyConstraint(new btMultiBodyJointLimitConstraint(body->_native, link,
		lower, upper))
{
	_multiBodyA = body;
	_multiBodyB = body;
}

#ifndef DISABLE_DEBUGDRAW
void MultiBodyJointLimitConstraint::DebugDraw(IDebugDraw^ drawer)
{
	// TODO
}
#endif

#endif
