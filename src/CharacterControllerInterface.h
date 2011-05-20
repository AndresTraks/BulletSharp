#pragma once

#include "ActionInterface.h"

namespace BulletSharp
{
	public ref class CharacterControllerInterface : ActionInterface
	{
	internal:
		CharacterControllerInterface(btCharacterControllerInterface* controllerInterface);

	public:
		void Jump();
		void PlayerStep(CollisionWorld^ collisionWorld, btScalar dt);
		void Reset();
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

	internal:
		property btCharacterControllerInterface* UnmanagedPointer
		{
			btCharacterControllerInterface* get() new;
		}
	};
};