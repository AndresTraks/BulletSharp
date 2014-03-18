#pragma once

#include "CharacterControllerInterface.h"

namespace BulletSharp
{
	ref class ConvexShape;
	ref class PairCachingGhostObject;

	public ref class KinematicCharacterController : CharacterControllerInterface
	{
	internal:
		KinematicCharacterController(btKinematicCharacterController* native);

	public:
		KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape,
			btScalar stepHeight, int upAxis);
		KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape,
			btScalar stepHeight);

		void SetFallSpeed(btScalar fallSpeed);
		void SetJumpSpeed(btScalar jumpSpeed);
		void SetMaxJumpHeight(btScalar maxJumpHeight);
		void SetUpAxis(int axis);
		void SetUseGhostSweepTest(bool useGhostObjectSweepTest);

		property PairCachingGhostObject^ GhostObject
		{
			PairCachingGhostObject^ get();
		}

		property btScalar Gravity
		{
			btScalar get();
			void set(btScalar gravity);
		}

		property btScalar MaxSlope
		{
			btScalar get();
			void set(btScalar slopeRadians);
		}
	};
};
