#pragma once

namespace BulletSharp
{
	struct BroadphaseAabbCallbackWrapper;
	struct BroadphaseRayCallbackWrapper;

	ref class BroadphaseProxy;
	ref class Dispatcher;
	ref class OverlappingPairCache;
	ref class UIntArray;

	public ref class BroadphaseAabbCallback abstract
	{
	private:
		[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
        delegate bool ProcessUnmanagedDelegate(IntPtr proxy);

		bool ProcessUnmanaged(IntPtr proxy);

	internal:
		btBroadphaseAabbCallback* _native;
		ProcessUnmanagedDelegate^ _process;

		BroadphaseAabbCallback(btBroadphaseAabbCallback* native);

		~BroadphaseAabbCallback();
		!BroadphaseAabbCallback();

	protected:
		BroadphaseAabbCallback();

	public:
		virtual bool Process(BroadphaseProxy^ proxy) = 0;
	};

	typedef bool (*pBroadphaseAabbCallback_Process)(const btBroadphaseProxy* proxy);

	struct BroadphaseAabbCallbackWrapper : public btBroadphaseAabbCallback
	{
	private:
		pBroadphaseAabbCallback_Process _processCallback;

	public:
		BroadphaseAabbCallbackWrapper(pBroadphaseAabbCallback_Process processCallback);

		virtual bool process(const btBroadphaseProxy* proxy);
	};

	public ref class BroadphaseRayCallback abstract : BroadphaseAabbCallback
	{
	private:
		UIntArray^ _signs;

	protected:
		BroadphaseRayCallback();

	public:
		property btScalar LambdaMax
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 RayDirectionInverse
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property UIntArray^ Signs
		{
			UIntArray^ get();
		}
	};

	struct BroadphaseRayCallbackWrapper : public btBroadphaseRayCallback
	{
	private:
		pBroadphaseAabbCallback_Process _processCallback;

	public:
		BroadphaseRayCallbackWrapper(pBroadphaseAabbCallback_Process processCallback);

		virtual bool process(const btBroadphaseProxy* proxy);
	};

	public ref class BroadphaseInterface abstract
	{
	internal:
		btBroadphaseInterface* _native;

	protected:
		OverlappingPairCache^ _overlappingPairCache;

	internal:
		BroadphaseInterface(btBroadphaseInterface* native);

		~BroadphaseInterface();
		!BroadphaseInterface();

	public:
		void AabbTestRef(Vector3% aabbMin, Vector3% aabbMax, BroadphaseAabbCallback^ callback);
		void AabbTest(Vector3 aabbMin, Vector3 aabbMax, BroadphaseAabbCallback^ callback);
		void CalculateOverlappingPairs(Dispatcher^ dispatcher);
		virtual BroadphaseProxy^ CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
			BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
			short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy) = 0;
		void DestroyProxy(BroadphaseProxy^ proxy, Dispatcher^ dispatcher);
		void GetAabb(BroadphaseProxy^ proxy, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		void GetBroadphaseAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		void PrintStats();
		void RayTestRef(Vector3% rayFrom, Vector3% rayTo, BroadphaseRayCallback^ rayCallback,
			Vector3% aabbMin, Vector3% aabbMax);
		void RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback,
			Vector3 aabbMin, Vector3 aabbMax);
		void RayTestRef(Vector3% rayFrom, Vector3% rayTo, BroadphaseRayCallback^ rayCallback);
		void RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback);
		void ResetPool(Dispatcher^ dispatcher);
		void SetAabbRef(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax, Dispatcher^ dispatcher);
		void SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property BulletSharp::OverlappingPairCache^ OverlappingPairCache
		{
			BulletSharp::OverlappingPairCache^ get();
		}
	};
};
