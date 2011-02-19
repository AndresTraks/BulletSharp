#pragma once

// Fully implemented as of 24 Feb 2010

namespace BulletSharp
{
	ref class CollisionAlgorithm;

	public ref class BroadphaseProxy
	{
	private:
		btBroadphaseProxy* _proxy;
		bool _doesNotOwnObject;

	protected:
		Object^ _clientObject;

	internal:
		BroadphaseProxy(btBroadphaseProxy* proxy);

	public:
		BroadphaseProxy();
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask,
			IntPtr multiSapParentProxy);
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask);

	internal:
		static BroadphaseProxy^ GetObject(btBroadphaseProxy* broadphaseProxy);

	public:
		property Vector3 AabbMin
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AabbMax
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Object^ ClientObject
		{
			Object^ get();
			void set(Object^ value);
		}

		property BulletSharp::CollisionFilterGroups CollisionFilterGroup
		{
			BulletSharp::CollisionFilterGroups get();
			void set(BulletSharp::CollisionFilterGroups value);
		}

		property BulletSharp::CollisionFilterGroups CollisionFilterMask
		{
			BulletSharp::CollisionFilterGroups get();
			void set(BulletSharp::CollisionFilterGroups value);
		}

		property IntPtr MultiSapParentProxy
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property int Uid
		{
			int get();
			void set(int value);
		}

		bool IsCompound(int proxyType);
		bool IsConcave(int proxyType);
		bool IsConvex(int proxyType);
		bool IsConvex2d(int proxyType);
		bool IsInfinite(int proxyType);
		bool IsPolyhedral(int proxyType);
		bool IsSoftBody(int proxyType);

	internal:
		property btBroadphaseProxy* UnmanagedPointer
		{
			virtual btBroadphaseProxy* get();
			void set(btBroadphaseProxy* value);
		}
	};

	public ref class BroadphasePair
	{
	private:
		btBroadphasePair* _pair;

	internal:
		BroadphasePair(btBroadphasePair* pair);

	public:
		BroadphasePair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy);
		BroadphasePair(BroadphasePair^ pair);
		BroadphasePair();

		property CollisionAlgorithm^ Algorithm
		{
			CollisionAlgorithm^ get();
			void set(CollisionAlgorithm^ value);
		}

		property BroadphaseProxy^ Proxy0
		{
			BroadphaseProxy^ get();
			void set(BroadphaseProxy^ value);
		}

		property BroadphaseProxy^ Proxy1
		{
			BroadphaseProxy^ get();
			void set(BroadphaseProxy^ value);
		}

	internal:
		property btBroadphasePair* UnmanagedPointer
		{
			virtual btBroadphasePair* get();
			void set(btBroadphasePair* value);
		}
	};
}
