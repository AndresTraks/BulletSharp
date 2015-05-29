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
	internal:
		btBroadphaseAabbCallback* _native;

		BroadphaseAabbCallback(btBroadphaseAabbCallback* native);

	protected:
		BroadphaseAabbCallback();

	public:
		virtual bool Process(BroadphaseProxy^ proxy) = 0;

	public:
		~BroadphaseAabbCallback();
	protected:
		!BroadphaseAabbCallback();
	};

	struct BroadphaseAabbCallbackWrapper : public btBroadphaseAabbCallback
	{
	protected:
		void* _aabbCallback;

	public:
		BroadphaseAabbCallbackWrapper(BroadphaseAabbCallback^ aabbCallback);
		~BroadphaseAabbCallbackWrapper();

		virtual bool process(const btBroadphaseProxy* proxy);
	};

	public ref class BroadphaseRayCallback abstract : BroadphaseAabbCallback
	{
	private:
		UIntArray^ _signs;

	internal:
		BroadphaseRayCallback(BroadphaseRayCallbackWrapper* native);

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
	protected:
		void* _rayCallback;

	public:
		BroadphaseRayCallbackWrapper(void* rayCallbackHandle);
		~BroadphaseRayCallbackWrapper();

		virtual bool process(const btBroadphaseProxy* proxy);
	};

	public ref class BroadphaseInterface : ITrackingDisposable // abstract
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btBroadphaseInterface* _native;

		BroadphaseInterface(btBroadphaseInterface* native);

	protected:
		OverlappingPairCache^ _pairCache;

	public:
		!BroadphaseInterface();
	protected:
		~BroadphaseInterface();

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
