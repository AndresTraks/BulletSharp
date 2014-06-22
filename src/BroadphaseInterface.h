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

	public:
		BroadphaseAabbCallback();
		virtual bool Process(BroadphaseProxy^ proxy) = 0;

	public:
		~BroadphaseAabbCallback();
	protected:
		!BroadphaseAabbCallback();
	};

	struct BroadphaseAabbCallbackWrapper : public btBroadphaseAabbCallback
	{
	protected:
		gcroot<BroadphaseAabbCallback^> _aabbCallback;

	public:
		BroadphaseAabbCallbackWrapper(BroadphaseAabbCallback^ aabbCallback);

		virtual bool process(const btBroadphaseProxy* proxy);
	};

	public ref class BroadphaseRayCallback abstract : BroadphaseAabbCallback
	{
	internal:
		BroadphaseRayCallback(BroadphaseRayCallbackWrapper* callback);

	public:
		BroadphaseRayCallback();

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
		gcroot<BroadphaseRayCallback^> _rayCallback;

	public:
		BroadphaseRayCallbackWrapper(gcroot<BroadphaseRayCallback^> rayCallback);

		virtual bool process(const btBroadphaseProxy* proxy);
	};

	public ref class BroadphaseInterface : ITrackingDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btBroadphaseInterface* _native;
		BroadphaseInterface(btBroadphaseInterface* native);
		static BroadphaseInterface^ GetManaged(btBroadphaseInterface* broadphase);

	protected:
		OverlappingPairCache^ _pairCache;

	public:
		!BroadphaseInterface();
	protected:
		~BroadphaseInterface();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	public:
		void AabbTest(Vector3 aabbMin, Vector3 aabbMax, BroadphaseAabbCallback^ callback);
		void CalculateOverlappingPairs(Dispatcher^ dispatcher);
		BroadphaseProxy^ CreateProxy(Vector3 aabbMin, Vector3 aabbMax,
			int shapeType, IntPtr userPtr, CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy);
		void DestroyProxy(BroadphaseProxy^ proxy, Dispatcher^ dispatcher);
		void GetAabb(BroadphaseProxy^ proxy, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		void GetBroadphaseAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		void PrintStats();
		void RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback,
			Vector3 aabbMin, Vector3 aabbMax);
		void RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback);
		void ResetPool(Dispatcher^ dispatcher);
		void SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher);

		property BulletSharp::OverlappingPairCache^ OverlappingPairCache
		{
			BulletSharp::OverlappingPairCache^ get();
		}
	};
};
