#pragma once

#include "DiscreteDynamicsWorld.h"

namespace BulletSharp
{
	namespace SoftBody
	{
		ref class AlignedSoftBodyArray;
		ref class ConstraintSolver;
		ref class Dispatcher;
		ref class SoftBody;
		ref class SoftBodySolver;
		ref class SoftBodyWorldInfo;

		public ref class SoftRigidDynamicsWorld : DiscreteDynamicsWorld
		{
		public:
			SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
				BulletSharp::ConstraintSolver^ constraintSolver,
#endif
				CollisionConfiguration^ collisionConfiguration);

			SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
				BulletSharp::ConstraintSolver^ constraintSolver,
#endif
				CollisionConfiguration^ collisionConfiguration, SoftBodySolver^ softBodySolver);

			void AddSoftBody(SoftBody^ body,
				CollisionFilterGroups collisionFilterGroup,
				CollisionFilterGroups collisionFilterMask);
			void AddSoftBody(SoftBody^ body,
				CollisionFilterGroups collisionFilterGroup);
			void AddSoftBody(SoftBody^ body);
			void RemoveSoftBody(SoftBody^ body);

			property AlignedSoftBodyArray^ SoftBodyArray
			{
				AlignedSoftBodyArray^ get();
			}

			property SoftBodyWorldInfo^ WorldInfo
			{
				SoftBodyWorldInfo^ get();
			}

		internal:
			property btSoftRigidDynamicsWorld* UnmanagedPointer
			{
				btSoftRigidDynamicsWorld* get() new;
			}
		};
	};
};
