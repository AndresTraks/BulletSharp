#pragma once

namespace BulletSharp
{
	ref class CollisionAlgorithm;

	public ref class BroadphaseProxy
	{
	internal:
		btBroadphaseProxy* _native;
		int _uid;
		BroadphaseProxy(btBroadphaseProxy* native);

	private:
		bool _doesNotOwnObject;

	protected:
		Object^ _clientObject;

	internal:
		static BroadphaseProxy^ GetManaged(btBroadphaseProxy* broadphaseProxy);

	public:
		BroadphaseProxy();
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject, CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask, IntPtr multiSapParentProxy);
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject, CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask);

		static bool IsCompound(int proxyType);
		static bool IsConcave(int proxyType);
		static bool IsConvex(int proxyType);
		static bool IsConvex2d(int proxyType);
		static bool IsInfinite(int proxyType);
		static bool IsNonMoving(int proxyType);
		static bool IsPolyhedral(int proxyType);
		static bool IsSoftBody(int proxyType);

		property Vector3 AabbMax
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AabbMin
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Object^ ClientObject
		{
			Object^ get();
			void set(Object^ value);
		}

		property CollisionFilterGroups CollisionFilterGroup
		{
			CollisionFilterGroups get();
			void set(CollisionFilterGroups value);
		}

		property CollisionFilterGroups CollisionFilterMask
		{
			CollisionFilterGroups get();
			void set(CollisionFilterGroups value);
		}

		property IntPtr MultiSapParentProxy
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property int UniqueID
		{
			int get();
			void set(int value);
		}

	internal:
		property btBroadphaseProxy* UnmanagedPointer
		{
			virtual btBroadphaseProxy* get();
			void set(btBroadphaseProxy* value);
		}
	};

	public ref struct BroadphasePair
	{
	internal:
		btBroadphasePair* _native;

		BroadphasePair(btBroadphasePair* pair);

	public:
		//BroadphasePair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy);
		//BroadphasePair(BroadphasePair^ pair);
		//BroadphasePair();

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
	};
}
