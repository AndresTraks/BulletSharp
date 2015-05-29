#pragma once

namespace BulletSharp
{
	ref class CollisionAlgorithm;

	public ref class BroadphaseProxy
	{
	internal:
		btBroadphaseProxy* _native;
		int _uid;

	private:
		Object^ _clientObject;

	internal:
		BroadphaseProxy(btBroadphaseProxy* native);
		static BroadphaseProxy^ GetManaged(btBroadphaseProxy* broadphaseProxy);

	public:
		static bool IsCompound(BroadphaseNativeType proxyType);
		static bool IsConcave(BroadphaseNativeType proxyType);
		static bool IsConvex(BroadphaseNativeType proxyType);
		static bool IsConvex2D(BroadphaseNativeType proxyType);
		static bool IsInfinite(BroadphaseNativeType proxyType);
		static bool IsNonMoving(BroadphaseNativeType proxyType);
		static bool IsPolyhedral(BroadphaseNativeType proxyType);
		static bool IsSoftBody(BroadphaseNativeType proxyType);

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
	};

	public ref struct BroadphasePair
	{
	internal:
		btBroadphasePair* _native;

		BroadphasePair(btBroadphasePair* native);

	public:
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
};
