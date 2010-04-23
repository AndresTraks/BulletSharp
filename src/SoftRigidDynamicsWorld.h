#pragma once

#include "DiscreteDynamicsWorld.h"
#include "Enums.h"

namespace BulletSharp
{
	ref class ConstraintSolver;
	ref class Dispatcher;
	ref class SoftBody;

	public ref class SoftRigidDynamicsWorld : DiscreteDynamicsWorld
	{
	public:
		SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
			BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
			BulletSharp::ConstraintSolver^ constraintSolver,
#endif
			CollisionConfiguration^ collisionConfiguration);

		void AddSoftBody(SoftBody^ body,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask);
		void AddSoftBody(SoftBody^ body,
			CollisionFilterGroups collisionFilterGroup);
		void AddSoftBody(SoftBody^ body);

	internal:
		property btSoftRigidDynamicsWorld* UnmanagedPointer
		{
			btSoftRigidDynamicsWorld* get() new;
		}
	};
};
