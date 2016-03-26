#pragma once

namespace BulletSharp
{
	ref class BroadphaseProxy;
	ref class CollisionShape;
	ref class Serializer;

	public ref class CollisionObject : ITrackingDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btCollisionObject* _native;
		bool _preventDelete;

	private:
		bool _isDisposed;
		BroadphaseProxy^ _broadphaseHandle;
		Object^ _userObject;

	protected:
		CollisionShape^ _collisionShape;

	internal:
		CollisionObject(btCollisionObject* native);

		~CollisionObject();
		!CollisionObject();

	public:
		CollisionObject();

		void Activate(bool forceActivation);
		void Activate();
#ifndef DISABLE_SERIALIZE
		int CalculateSerializeBufferSize();
#endif
		bool CheckCollideWith(CollisionObject^ collisionObject);
		bool CheckCollideWithOverride(CollisionObject^ collisionObject);
		void ForceActivationState(BulletSharp::ActivationState newState);
		virtual int GetHashCode() override;
		void GetWorldTransform([Out] Matrix% transform);
		bool HasAnisotropicFriction(AnisotropicFrictionFlags frictionMode);
		bool HasAnisotropicFriction();
#ifndef DISABLE_SERIALIZE
		String^ Serialize(IntPtr dataBuffer, Serializer^ serializer);
		void SerializeSingleObject(Serializer^ serializer);
#endif
		void SetAnisotropicFriction(Vector3 anisotropicFriction, AnisotropicFrictionFlags frictionMode);
		void SetAnisotropicFriction(Vector3 anisotropicFriction);
		void SetIgnoreCollisionCheck(CollisionObject^ collisionObject, bool ignoreCollisionCheck);

	internal:
		static CollisionObject^ GetManaged(btCollisionObject* collisionObject);

	public:
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

		property BroadphaseProxy^ BroadphaseHandle
		{
			BroadphaseProxy^ get();
			void set(BroadphaseProxy^ handle);
		}

		property btScalar CcdMotionThreshold
		{
			btScalar get();
			void set(btScalar ccdMotionThreshold);
		}

		property btScalar CcdSquareMotionThreshold
		{
			btScalar get();
		}

		property btScalar CcdSweptSphereRadius
		{
			btScalar get();
			void set(btScalar radius);
		}

		property CollisionFlags CollisionFlags
		{
			BulletSharp::CollisionFlags get();
			void set(BulletSharp::CollisionFlags flags);
		}

		property BulletSharp::CollisionShape^ CollisionShape
		{
			BulletSharp::CollisionShape^ get();
			void set(BulletSharp::CollisionShape^ collisionShape);
		}

		property int CompanionId
		{
			int get();
			void set(int id);
		}

		property btScalar ContactProcessingThreshold
		{
			btScalar get();
			void set(btScalar contactProcessingThreshold);
		}

		property btScalar DeactivationTime
		{
			btScalar get();
			void set(btScalar time);
		}

		property btScalar Friction
		{
			btScalar get();
			void set(btScalar frict);
		}

		property bool HasContactResponse
		{
			bool get();
		}

		property btScalar HitFraction
		{
			btScalar get();
			void set(btScalar hitFraction);
		}

		property Vector3 InterpolationAngularVelocity
		{
			Vector3 get();
			void set(Vector3 angvel);
		}

		property Vector3 InterpolationLinearVelocity
		{
			Vector3 get();
			void set(Vector3 linvel);
		}

		property Matrix InterpolationWorldTransform
		{
			Matrix get();
			void set(Matrix trans);
		}

		property bool IsActive
		{
			bool get();
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool IsKinematicObject
		{
			bool get();
		}

		property int IslandTag
		{
			int get();
			void set(int tag);
		}

		property bool IsStaticObject
		{
			bool get();
		}

		property bool IsStaticOrKinematicObject
		{
			bool get();
		}

		property bool MergesSimulationIslands
		{
			bool get();
		}

		property btScalar Restitution
		{
			btScalar get();
			void set(btScalar rest);
		}

		property btScalar RollingFriction
		{
			btScalar get();
			void set(btScalar frict);
		}

		property int UpdateRevisionInternal
		{
			int get();
		}

		property int UserIndex
		{
			int get();
			void set(int index);
		}

		// UserPointer implemented as UserObject
		property Object^ UserObject
		{
			Object^ get();
			void set(Object^ value);
		}

		property Matrix WorldTransform
		{
			Matrix get();
			void set(Matrix worldTrans);
		}

	internal:
		property btCollisionObject* UnmanagedPointer
		{
			virtual btCollisionObject* get();
			void set(btCollisionObject* value);
		}
	};
};
