#pragma once

#include "ICharacterController.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class ConvexShape;
	ref class PairCachingGhostObject;

	public ref class KinematicCharacterController : ICharacterController
	{
	protected:
		btScalar _addedMargin; // TODO: remove this and fix the code
		bool _bounceFix;
		ConvexShape^ _convexShape; // is also in _ghostObject, but it needs to be convex, so we store it here to avoid upcast
		Vector3 _currentPosition;
		btScalar _currentStepOffset;
		btScalar _fallSpeed;
		bool _fullDrop;
		PairCachingGhostObject^ _ghostObject;
		btScalar _gravity;
		btScalar _jumpSpeed;
		bool _interpolateUp;
		btScalar _maxJumpHeight;
		btScalar _maxSlopeRadians; // Slope angle that is set (used for returning the exact value)
		btScalar _maxSlopeCosine;  // Cosine equivalent of m_maxSlopeRadians (calculated once when set, for optimization)
		Vector3 _normalizedDirection;
		btScalar _stepHeight;
		Vector3 _targetPosition;
		bool _touchingContact;
		Vector3 _touchingNormal;
		int _upAxis;
		bool _useGhostObjectSweepTest;
		bool _useWalkDirection;
		btScalar _velocityTimeInterval;
		btScalar _verticalVelocity;
		btScalar _verticalOffset;
		Vector3 _walkDirection;
		bool _wasJumping;
		bool _wasOnGround;

	public:
		KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape,
			btScalar stepHeight, int upAxis);
		KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape,
			btScalar stepHeight);

	protected:
		Vector3 ComputeReflectionDirection(Vector3% direction, Vector3% normal);
		static Vector3 GetUpAxisDirection(int upAxis);
		Vector3 ParallelComponent(Vector3% direction, Vector3% normal);
		Vector3 PerpindicularComponent(Vector3% direction, Vector3% normal);
		bool RecoverFromPenetration(CollisionWorld^ collisionWorld);
		void StepDown(CollisionWorld^ collisionWorld, btScalar dt);
		void StepForwardAndStrafe(CollisionWorld^ collisionWorld, Vector3% walkMove);
		void StepUp(CollisionWorld^ world);
		void UpdateTargetPositionBasedOnCollision(Vector3 hitNormal);

	public:
#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ debugDrawer);
#endif
		virtual void Jump();
		virtual void PlayerStep(CollisionWorld^ collisionWorld, btScalar dt);
		virtual void PreStep(CollisionWorld^ collisionWorld);
		virtual void Reset(CollisionWorld^ collisionWorld);
		void SetFallSpeed(btScalar fallSpeed);
		void SetJumpSpeed(btScalar jumpSpeed);
		void SetMaxJumpHeight(btScalar maxJumpHeight);
		void SetUpAxis(int axis);
		virtual void SetUpInterpolate(bool value);
		void SetUseGhostSweepTest(bool useGhostObjectSweepTest);
		virtual void SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval);
		virtual void SetWalkDirection(Vector3 walkDirection);
		virtual void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);
		virtual void Warp(Vector3 origin);

		property PairCachingGhostObject^ GhostObject
		{
			PairCachingGhostObject^ get();
		}

		property btScalar Gravity
		{
			btScalar get();
			void set(btScalar gravity);
		}

		property bool CanJump
		{
			virtual bool get();
		}

		property btScalar MaxSlope
		{
			btScalar get();
			void set(btScalar slopeRadians);
		}

		property bool OnGround
		{
			virtual bool get();
		}
	};

	ref class KinematicClosestNotMeConvexResultCallback : ClosestConvexResultCallback
	{
	protected:
		CollisionObject^ _me;
        Vector3 _up;
        float _minSlopeDot;

	public:
		KinematicClosestNotMeConvexResultCallback(CollisionObject^ me, Vector3 up, btScalar minSlopeDot);

		virtual btScalar AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace) override;
	};
};
