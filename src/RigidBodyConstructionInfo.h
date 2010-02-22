#pragma once

#include "CollisionShape.h"
#include "MotionState.h"

namespace BulletSharp
{
	public ref class RigidBodyConstructionInfo
	{
		private:
			btRigidBody::btRigidBodyConstructionInfo* _info;

		internal:
			CollisionShape^ _collisionShape;
			MotionState^ _motionState;

		public:
			RigidBodyConstructionInfo(btScalar mass, MotionState^ motionState, CollisionShape^ collisionShape);
			RigidBodyConstructionInfo(btScalar mass, MotionState^ motionState, CollisionShape^ collisionShape, Vector3 localInertia);

		public:
			property float Mass
			{
				float get();
				void set( float value );
			}

		internal:
			property btRigidBody::btRigidBodyConstructionInfo* UnmanagedPointer
			{
				btRigidBody::btRigidBodyConstructionInfo* get();
			}
	};
};
