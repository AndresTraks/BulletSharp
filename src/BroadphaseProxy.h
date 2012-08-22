#pragma once

namespace BulletSharp
{
	ref class CollisionAlgorithm;

	public ref class BroadphaseProxy
	{
	internal:
		btBroadphaseProxy* _unmanaged;

	private:
		bool _doesNotOwnObject;

	protected:
		Object^ _clientObject;

	internal:
		BroadphaseProxy(btBroadphaseProxy* proxy);
		int _uid;

		static BroadphaseProxy^ GetManaged(btBroadphaseProxy* broadphaseProxy);

	public:
		BroadphaseProxy();
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask,
			IntPtr multiSapParentProxy);
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask);

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

		static bool IsCompound(int proxyType);
		static bool IsConcave(int proxyType);
		static bool IsConvex(int proxyType);
		static bool IsConvex2d(int proxyType);
		static bool IsInfinite(int proxyType);
		static bool IsPolyhedral(int proxyType);
		static bool IsSoftBody(int proxyType);

	internal:
		property btBroadphaseProxy* UnmanagedPointer
		{
			virtual btBroadphaseProxy* get();
			void set(btBroadphaseProxy* value);
		}
	};

	public ref struct BroadphasePair
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
