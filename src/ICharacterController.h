#pragma once

#include "IAction.h"

namespace BulletSharp
{
	public interface class ICharacterController : IAction
	{
		void Jump();
		void PlayerStep(CollisionWorld^ collisionWorld, btScalar dt);
		void PreStep(CollisionWorld^ collisionWorld);
		void Reset(CollisionWorld^ collisionWorld);
		void SetUpInterpolate(bool value);
		void SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval);
		void SetWalkDirection(Vector3 walkDirection);
		void Warp(Vector3 origin);

		property bool CanJump
		{
			bool get();
		}

		property bool OnGround
		{
			bool get();
		}
	};
};
