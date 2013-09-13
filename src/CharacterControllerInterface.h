#pragma once

#include "IActionInterface.h"
#include "IDisposable.h"

namespace BulletSharp
{
	public ref class CharacterControllerInterface : IActionInterface,  BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btCharacterControllerInterface* _native;
		CharacterControllerInterface(btCharacterControllerInterface* controllerInterface);

	public:
		!CharacterControllerInterface();
	protected:
		~CharacterControllerInterface();

	public:
#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ debugDrawer);
#endif
		virtual void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);

		void Jump();
		void PlayerStep(CollisionWorld^ collisionWorld, btScalar dt);
		void Reset(CollisionWorld^ collisionWorld);
		void SetUpInterpolate(bool value);
		void SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval);
		void SetWalkDirection(Vector3 walkDirection);
		void Warp(Vector3 origin);

		property bool CanJump
		{
			bool get();
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool OnGround
		{
			bool get();
		}
	};
};