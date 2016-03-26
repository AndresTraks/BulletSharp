#pragma once

namespace BulletSharp
{
	ref class Serializer;

	public ref class CollisionShape abstract : ITrackingDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btCollisionShape* _native;
		bool _preventDelete;

	private:
		Object^ _userObject;
		BroadphaseNativeType _shapeType;
		bool _isDisposed;

	internal:
		CollisionShape(btCollisionShape* native);
		static CollisionShape^ GetManaged(btCollisionShape* collisionShape);

		~CollisionShape();
		!CollisionShape();

	public:
		void CalculateLocalInertia(btScalar mass, [Out] Vector3% inertia);
		Vector3 CalculateLocalInertia(btScalar mass);
#ifndef DISABLE_SERIALIZE
		int CalculateSerializeBufferSize();
#endif
		void CalculateTemporalAabb(Matrix% curTrans, Vector3% linvel, Vector3% angvel,
			btScalar timeStep, [Out] Vector3% temporalAabbMin, [Out] Vector3% temporalAabbMax);
		void CalculateTemporalAabb(Matrix curTrans, Vector3 linvel, Vector3 angvel,
			btScalar timeStep, [Out] Vector3% temporalAabbMin, [Out] Vector3% temporalAabbMax);
		virtual bool Equals(Object^ obj) override;
		virtual void GetAabbRef(Matrix% t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		virtual void GetAabb(Matrix t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		void GetBoundingSphere([Out] Vector3% center, [Out] btScalar% radius);
		btScalar GetContactBreakingThreshold(btScalar defaultContactThresholdFactor);
		virtual int GetHashCode() override;
#ifndef DISABLE_SERIALIZE
		String^ Serialize(IntPtr dataBuffer, Serializer^ serializer);
		void SerializeSingleShape(Serializer^ serializer);
#endif

		property btScalar AngularMotionDisc
		{
			btScalar get();
		}

		property Vector3 AnisotropicRollingFrictionDirection
		{
			Vector3 get();
		}

		property bool IsCompound
		{
			bool get();
		}

		property bool IsConcave
		{
			bool get();
		}

		property bool IsConvex
		{
			bool get();
		}

		property bool IsConvex2D
		{
			bool get();
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool IsInfinite
		{
			bool get();
		}

		property bool IsNonMoving
		{
			bool get();
		}

		property bool IsPolyhedral
		{
			bool get();
		}

		property bool IsSoftBody
		{
			bool get();
		}

		property Vector3 LocalScaling
		{
			Vector3 get();
			void set(Vector3 scaling);
		}

		property btScalar Margin
		{
			btScalar get();
			void set(btScalar margin);
		}

		property String^ Name
		{
			String^ get();
		}

		property BroadphaseNativeType ShapeType
		{
			BroadphaseNativeType get();
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

	internal:
		property btCollisionShape* UnmanagedPointer
		{
			btCollisionShape* get();
			void set(btCollisionShape* value);
		}
	};
};
