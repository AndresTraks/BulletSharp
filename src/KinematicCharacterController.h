#pragma once

#include "CharacterControllerInterface.h"

namespace BulletSharp
{
	ref class PairCachingGhostObject;
	ref class ConvexShape;

	public ref class KinematicCharacterController : CharacterControllerInterface
	{
	internal:
		KinematicCharacterController(btKinematicCharacterController* characterController);

	public:
		KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight, int upAxis);
		KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight);

		void SetFallSpeed(btScalar fallSpeed);
		void SetJumpSpeed(btScalar jumpSpeed);
		void SetMaxJumpHeight(btScalar maxJumpHeight);
		void SetUpAxis(int axis);
		void SetUseGhostSweepTest(bool useGhostObjectSweepTest);

		property BulletSharp::GhostObject^ GhostObject
		{
			BulletSharp::GhostObject^ get();
		}
	};
};
