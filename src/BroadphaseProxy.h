#pragma once

// Fully implemented as of 24 Feb 2010

#include "Enums.h"

namespace BulletSharp
{
	public ref class BroadphaseProxy
	{
	private:
		btBroadphaseProxy* _proxy;

	public:
		BroadphaseProxy();
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask,
			IntPtr multiSapParentProxy);
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask);
	internal:
		BroadphaseProxy(btBroadphaseProxy* proxy);

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

		property IntPtr ClientObject
		{
			IntPtr get();
			void set(IntPtr value);
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
}
