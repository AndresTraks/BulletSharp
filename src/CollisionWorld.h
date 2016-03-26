#pragma once

namespace BulletSharp
{
	ref class AlignedCollisionObjectArray;
	ref class AlignedScalarArray;
	ref class AlignedVector3Array;
	ref class BroadphaseInterface;
	ref class BroadphaseProxy;
	ref class CollisionConfiguration;
	ref class CollisionObject;
	ref class CollisionObjectWrapper;
	ref class CollisionShape;
	ref class ConvexShape;
	ref class Dispatcher;
	ref class DispatcherInfo;
	ref class ManifoldPoint;
	ref class OverlappingPairCache;
	ref class Serializer;
	interface class IDebugDraw;

	class ContactResultCallbackWrapper;
	class DebugDrawWrapper;

	public ref class LocalShapeInfo
	{
	internal:
		btCollisionWorld::LocalShapeInfo* _native;
		LocalShapeInfo(btCollisionWorld::LocalShapeInfo* native, bool preventDelete);

	private:
		bool _preventDelete;

		~LocalShapeInfo();
		!LocalShapeInfo();

	public:
		LocalShapeInfo();

		property int ShapePart
		{
			int get();
			void set(int value);
		}

		property int TriangleIndex
		{
			int get();
			void set(int value);
		}
	};

	public ref class LocalRayResult
	{
	internal:
		btCollisionWorld::LocalRayResult* _native;

	private:
		bool _preventDelete;
		LocalShapeInfo^ _localShapeInfo;

	internal:
		LocalRayResult(btCollisionWorld::LocalRayResult* native, bool preventDelete);

		~LocalRayResult();
		!LocalRayResult();

	public:
		LocalRayResult(CollisionObject^ collisionObject, LocalShapeInfo^ localShapeInfo,
			Vector3 hitNormalLocal, btScalar hitFraction);

		property CollisionObject^ CollisionObject
		{
			BulletSharp::CollisionObject^ get();
			void set(BulletSharp::CollisionObject^ value);
		}

		property btScalar HitFraction
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 HitNormalLocal
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property LocalShapeInfo^ LocalShapeInfo
		{
			BulletSharp::LocalShapeInfo^ get();
			void set(BulletSharp::LocalShapeInfo^ value);
		}
	};

	public ref class RayResultCallback abstract
	{
	private:
		[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
		delegate float AddSingleResultUnmanagedDelegate(IntPtr rayResult, bool normalInWorldSpace);
		[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
		delegate bool NeedsCollisionUnmanagedDelegate(IntPtr proxy0);

		AddSingleResultUnmanagedDelegate^ _addSingleResult;
		NeedsCollisionUnmanagedDelegate^ _needsCollision;

		float AddSingleResultUnmanaged(IntPtr rayResult, bool normalInWorldSpace);
		bool NeedsCollisionUnmanaged(IntPtr proxy0);

	internal:
		btCollisionWorld::RayResultCallback* _native;

		~RayResultCallback();
		!RayResultCallback();

	protected:
		RayResultCallback();

	public:
		virtual btScalar AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace) = 0;
		virtual bool NeedsCollision(BroadphaseProxy^ proxy0);

		property btScalar ClosestHitFraction
		{
			btScalar get();
			void set(btScalar value);
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

		property CollisionObject^ CollisionObject
		{
			BulletSharp::CollisionObject^ get();
			void set(BulletSharp::CollisionObject^ value);
		}

		property unsigned int Flags
		{
			unsigned int get();
			void set(unsigned int value);
		}

		property bool HasHit
		{
			bool get();
		}

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	typedef btScalar (*pRayResultCallback_AddSingleResult)(btCollisionWorld::LocalRayResult& rayResult,
		bool normalInWorldSpace);
	typedef bool (*pRayResultCallback_NeedsCollision)(btBroadphaseProxy* proxy0);

	class RayResultCallbackWrapper : public btCollisionWorld::RayResultCallback
	{
	private:
		pRayResultCallback_AddSingleResult _addSingleResultCallback;
		pRayResultCallback_NeedsCollision _needsCollisionCallback;

	public:
		RayResultCallbackWrapper(pRayResultCallback_AddSingleResult addSingleResultCallback,
			pRayResultCallback_NeedsCollision needsCollisionCallback);

		virtual bool needsCollision(btBroadphaseProxy* proxy0) const;
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace);
	};

	public ref class AllHitsRayResultCallback : RayResultCallback
	{
		List<BulletSharp::CollisionObject^>^ _collisionObjects;
		List<btScalar>^ _hitFractions;
		List<Vector3>^ _hitNormalWorld;
		List<Vector3>^ _hitPointWorld;
		Vector3 _rayFromWorld;
		Vector3 _rayToWorld;

	public:
		AllHitsRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld);

		virtual btScalar AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace) override;

		property IList<BulletSharp::CollisionObject^>^ CollisionObjects
		{
			IList<BulletSharp::CollisionObject^>^ get();
		}

		property IList<btScalar>^ HitFractions
		{
			IList<btScalar>^ get();
		}

		property IList<Vector3>^ HitNormalWorld
		{
			IList<Vector3>^ get();
		}

		property IList<Vector3>^ HitPointWorld
		{
			IList<Vector3>^ get();
		}

		property Vector3 RayFromWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 RayToWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};

	public ref class LocalConvexResult
	{
	internal:
		btCollisionWorld::LocalConvexResult* _native;

	private:
		bool _preventDelete;
		BulletSharp::LocalShapeInfo^ _localShapeInfo;

	internal:
		LocalConvexResult(btCollisionWorld::LocalConvexResult* native, bool preventDelete);

		~LocalConvexResult();
		!LocalConvexResult();

	public:
		LocalConvexResult(CollisionObject^ hitCollisionObject, LocalShapeInfo^ localShapeInfo,
			Vector3 hitNormalLocal, Vector3 hitPointLocal, btScalar hitFraction);

		property CollisionObject^ HitCollisionObject
		{
			CollisionObject^ get();
			void set(CollisionObject^ value);
		}

		property btScalar HitFraction
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 HitNormalLocal
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 HitPointLocal
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property LocalShapeInfo^ LocalShapeInfo
		{
			BulletSharp::LocalShapeInfo^ get();
			void set(BulletSharp::LocalShapeInfo^ value);
		}
	};

	public ref class ConvexResultCallback abstract
	{
	internal:
		btCollisionWorld::ConvexResultCallback* _native;

	private:
		btScalar _closestHitFraction;
		CollisionFilterGroups _collisionFilterGroup, _collisionFilterMask;

	protected:
		ConvexResultCallback();

	public:
		virtual btScalar AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace) = 0;
		virtual bool NeedsCollision(BroadphaseProxy^ proxy0);

		property btScalar ClosestHitFraction
		{
			btScalar get();
			void set(btScalar value);
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

		property bool HasHit
		{
			bool get();
		}
	};

	class ConvexResultCallbackWrapper : public btCollisionWorld::ConvexResultCallback
	{
	private:
		GCHandle _callback;
		void* _callbackPtr;

	public:
		ConvexResultCallbackWrapper(BulletSharp::ConvexResultCallback^ callback);
		~ConvexResultCallbackWrapper();

		virtual bool needsCollision(btBroadphaseProxy* proxy0) const;
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& rayResult, bool normalInWorldSpace);
	};

	public ref class ClosestConvexResultCallback : ConvexResultCallback
	{
		Vector3 _convexFromWorld;
		Vector3 _convexToWorld;
		CollisionObject^ _hitCollisionObject;
		Vector3 _hitNormalWorld;
		Vector3 _hitPointWorld;

	public:
		ClosestConvexResultCallback(Vector3% convexFromWorld, Vector3% convexToWorld);
		ClosestConvexResultCallback();

		virtual btScalar AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace) override;

		property Vector3 ConvexFromWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 ConvexToWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property CollisionObject^ HitCollisionObject
		{
			CollisionObject^ get();
			void set(CollisionObject^ value);
		}

		property Vector3 HitNormalWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 HitPointWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};

	public ref class ClosestRayResultCallback : RayResultCallback
	{
		Vector3 _hitNormalWorld;
		Vector3 _hitPointWorld;
		Vector3 _rayFromWorld;
		Vector3 _rayToWorld;

	public:
		ClosestRayResultCallback();
		//ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld);
		ClosestRayResultCallback(Vector3% rayFromWorld, Vector3% rayToWorld);

		virtual btScalar AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace) override;

		property Vector3 HitNormalWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 HitPointWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 RayFromWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 RayToWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};

	public ref class ContactResultCallback abstract
	{
	private:
		CollisionFilterGroups _collisionFilterGroup, _collisionFilterMask;

	protected:
		ContactResultCallback();

	public:
		virtual btScalar AddSingleResult(ManifoldPoint^ cp, CollisionObjectWrapper^ colObj0Wrap, int partId0, int index0,
			CollisionObjectWrapper^ colObj1Wrap, int partId1, int index1) = 0;
		virtual bool NeedsCollision(BroadphaseProxy^ proxy0);

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
	};

	class ContactResultCallbackWrapper : public btCollisionWorld::ContactResultCallback
	{
	private:
		void* _callback;

	public:
		ContactResultCallbackWrapper(BulletSharp::ContactResultCallback^ callback);
		~ContactResultCallbackWrapper();

		virtual bool needsCollision(btBroadphaseProxy* proxy0) const;
		virtual btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0, int partId0, int index0,
			const btCollisionObjectWrapper* colObj1, int partId1, int index1);
	};

	public ref class CollisionWorld
	{
	internal:
		btCollisionWorld* _native;

	private:
		DispatcherInfo^ _dispatchInfo;
		Dispatcher^ _dispatcher;

	protected:
		BroadphaseInterface^ _broadphase;
		AlignedCollisionObjectArray^ _collisionObjectArray;

#ifndef DISABLE_DEBUGDRAW
	internal:
		IDebugDraw^ _debugDrawer;
#endif

	internal:
		CollisionWorld(btCollisionWorld* native);

		~CollisionWorld();
		!CollisionWorld();

	public:
		CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ broadphasePairCache,
			BulletSharp::CollisionConfiguration^ collisionConfiguration);

		void AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask);
		void AddCollisionObject(CollisionObject^ collisionObject, short collisionFilterGroup, short collisionFilterMask);
		void AddCollisionObject(CollisionObject^ collisionObject);
		void ComputeOverlappingPairs();
		void ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB, ContactResultCallback^ resultCallback);
		void ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback);
		void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback,
			btScalar allowedCcdPenetration);
		void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback);
#ifndef DISABLE_DEBUGDRAW
		void DebugDrawObject(Matrix worldTransform, CollisionShape^ shape, BtColor color);
		void DebugDrawWorld();
#endif
		static void ObjectQuerySingle(ConvexShape^ castShape, Matrix rayFromTrans,
			Matrix rayToTrans, CollisionObject^ collisionObject, CollisionShape^ collisionShape,
			Matrix colObjWorldTransform, ConvexResultCallback^ resultCallback, btScalar allowedPenetration);
		void PerformDiscreteCollisionDetection();
		void RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, RayResultCallback^ resultCallback);
		void RayTest(Vector3% rayFromWorld, Vector3% rayToWorld, RayResultCallback^ resultCallback);
		static void RayTestSingle(Matrix rayFromTrans, Matrix rayToTrans, CollisionObject^ collisionObject,
			CollisionShape^ collisionShape, Matrix colObjWorldTransform, RayResultCallback^ resultCallback);
		void RemoveCollisionObject(CollisionObject^ collisionObject);
#ifndef DISABLE_SERIALIZE
		void Serialize(Serializer^ serializer);
#endif
		void UpdateAabbs();
		void UpdateSingleAabb(CollisionObject^ colObj);

		property BroadphaseInterface^ Broadphase
		{
			BroadphaseInterface^ get();
			void set(BroadphaseInterface^ pairCache);
		}

		property AlignedCollisionObjectArray^ CollisionObjectArray
		{
			AlignedCollisionObjectArray^ get();
		}
#ifndef DISABLE_DEBUGDRAW
		property IDebugDraw^ DebugDrawer
		{
			IDebugDraw^ get();
			void set(IDebugDraw^ debugDrawer);
		}
#endif

		property Dispatcher^ Dispatcher
		{
			BulletSharp::Dispatcher^ get();
		internal:
			void set(BulletSharp::Dispatcher^ value);
		}

		property DispatcherInfo^ DispatchInfo
		{
			DispatcherInfo^ get();
		}

		property bool ForceUpdateAllAabbs
		{
			bool get();
			void set(bool forceUpdateAllAabbs);
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property int NumCollisionObjects
		{
			int get();
		}

		property OverlappingPairCache^ PairCache
		{
			OverlappingPairCache^ get();
		}
	};
};
