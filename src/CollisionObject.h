#pragma once

#include "IDisposable.h"
#include "CollisionShape.h"
#include "Enums.h"

namespace BulletSharp
{
	public ref class CollisionObject : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btCollisionObject* _collisionObject;

	protected:
		CollisionShape^ _collisionShape;
		CollisionShape^ _rootCollisionShape;

	internal:
		CollisionObject(btCollisionObject* collisionObject);
	public:
		!CollisionObject();
	protected:
		~CollisionObject();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	public:
		void Activate();
		void Activate(bool forceActivation);
		bool CheckCollideWith(CollisionObject^ collisionObject);
		virtual bool CheckCollideWithOverride(CollisionObject^ collisionObject)
		{
			return true;
		}
		void ForceActivationState(BulletSharp::ActivationState newState);
		bool HasAnisotropicFriction();
		bool HasContactResponse();
		bool IsActive();
		bool IsKinematicObject();
		bool IsStaticObject();
		bool IsStaticOrKinematicObject();
		bool mergesSimulationIslands();

		property BulletSharp::ActivationState ActivationState
		{
			BulletSharp::ActivationState get();
			void set(BulletSharp::ActivationState value);
		}

		property Vector3 AnisotropicFriction
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar CcdMotionThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar CcdSquareMotionThreshold
		{
			btScalar get();
		}

		property btScalar CcdSweptSphereRadius
		{
			btScalar get();
			void set(btScalar value);
		}

		property int CollisionFlags
		{
			int get();
			void set(int value);
		}

		property BulletSharp::CollisionShape^ CollisionShape
		{
			BulletSharp::CollisionShape^ get();
			void set(BulletSharp::CollisionShape^ value);
		}

		property btScalar ContactProcessingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DeactivationTime
		{
			btScalar get();
			void set(btScalar value);
		}

		property int CompanionId
		{
			int get();
			void set(int value);
		}

		property btScalar Friction
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar HitFraction
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 InterpolationAngularVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 InterpolationLinearVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Matrix InterpolationWorldTransform
		{
			Matrix get();
			void set(Matrix value);
		}

		property btScalar Restitution
		{
			btScalar get();
			void set(btScalar value);
		}

		property int IslandTag
		{
			int get();
			void set(int value);
		}

		property BulletSharp::CollisionShape^ RootCollisionShape
		{
			BulletSharp::CollisionShape^ get();
		}

		property IntPtr UserPointer
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property Matrix WorldTransform
		{
			Matrix get();
			void set(Matrix value);
		}

	internal:
		property btCollisionObject* UnmanagedPointer
		{
			virtual btCollisionObject* get();
			void set(btCollisionObject* value);
		}
	};
};
