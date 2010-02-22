#pragma once

namespace BulletSharp
{
	public ref class BroadphaseProxy
	{
	private:
		btBroadphaseProxy* _proxy;

	public:
		BroadphaseProxy();
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax,
			IntPtr userPtr, short int collisionFilterGroup,
			short int collisionFilterMask,
			IntPtr multiSapParentProxy);
		BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax,
			IntPtr userPtr, short int collisionFilterGroup,
			short int collisionFilterMask);
	internal:
		BroadphaseProxy(btBroadphaseProxy* proxy);

	public:
		property int Uid
		{
			int get();
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
