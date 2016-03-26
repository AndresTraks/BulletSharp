#pragma once

#include "MultiBodyConstraint.h"

namespace BulletSharp
{
	public ref class MultiBodyJointLimitConstraint : MultiBodyConstraint
	{
	internal:
		MultiBodyJointLimitConstraint(btMultiBodyJointLimitConstraint* native);

	public:
		MultiBodyJointLimitConstraint(MultiBody^ body, int link, btScalar lower,
			btScalar upper);

#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ drawer) override;
#endif
	};
};
