#pragma once

#include "DiscreteDynamicsWorld.h"
#include "SoftBodyHelpers.h"

namespace BulletSharp
{
	ref class Serializer;
	ref class CollisionShape;
	ref class ConstraintSolver;
	ref class Dispatcher;

	namespace SoftBody
	{
		ref class AlignedSoftBodyArray;
		ref class SoftBody;
		ref class SoftBodySolver;
		ref class SoftBodyWorldInfo;

		public ref class SoftRigidDynamicsWorld : DiscreteDynamicsWorld
		{
		private:
			AlignedSoftBodyArray^ _softBodyArray;
			SoftBodySolver^ _softBodySolver; // private ref passed to bodies during AddSoftBody
			bool _ownsSolver;
			SoftBodyWorldInfo^ _worldInfo;

			!SoftRigidDynamicsWorld();
			~SoftRigidDynamicsWorld();

		public:
			SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
				BulletSharp::ConstraintSolver^ constraintSolver,
#endif
				CollisionConfiguration^ collisionConfiguration, SoftBodySolver^ softBodySolver);
			SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
				BulletSharp::ConstraintSolver^ constraintSolver,
#endif
				CollisionConfiguration^ collisionConfiguration);

			void AddSoftBody(SoftBody^ body,
				CollisionFilterGroups collisionFilterGroup,
				CollisionFilterGroups collisionFilterMask);
			void AddSoftBody(SoftBody^ body,
				short collisionFilterGroup,
				short collisionFilterMask);
			void AddSoftBody(SoftBody^ body);
			void RemoveSoftBody(SoftBody^ body);

			property BulletSharp::SoftBody::DrawFlags DrawFlags
			{
				BulletSharp::SoftBody::DrawFlags get();
				void set(BulletSharp::SoftBody::DrawFlags f);
			}

			property AlignedSoftBodyArray^ SoftBodyArray
			{
				AlignedSoftBodyArray^ get();
			}

			property SoftBodyWorldInfo^ WorldInfo
			{
				SoftBodyWorldInfo^ get();
			}
		};
	};
};
