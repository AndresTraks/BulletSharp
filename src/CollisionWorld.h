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

	public ref class CollisionWorld : ITrackingDisposable
	{
	public:
		ref class LocalShapeInfo : IDisposable
		{
		internal:
			btCollisionWorld::LocalShapeInfo* _native;

		public:
			!LocalShapeInfo();
		protected:
			~LocalShapeInfo();

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

		ref class LocalRayResult : IDisposable
		{
		internal:
			btCollisionWorld::LocalRayResult* _native;

		private:
			LocalShapeInfo^ _localShapeInfo;

		public:
			!LocalRayResult();
		protected:
			~LocalRayResult();

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
				CollisionWorld::LocalShapeInfo^ get();
				void set(CollisionWorld::LocalShapeInfo^ value);
			}
		};

		ref class RayResultCallback abstract : IDisposable
		{
		internal:
			btCollisionWorld::RayResultCallback* _native;

			RayResultCallback(btCollisionWorld::RayResultCallback* native);

		public:
			!RayResultCallback();
		protected:
			~RayResultCallback();

		public:
			btScalar AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace);
			bool NeedsCollision(BroadphaseProxy^ proxy0);

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

		ref class AllHitsRayResultCallback : RayResultCallback
		{
		private:
			AlignedCollisionObjectArray^ _collisionObjects;
			AlignedScalarArray^ _hitFractions;
			AlignedVector3Array^ _hitNormalWorld;
			AlignedVector3Array^ _hitPointWorld;

		public:
			AllHitsRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld);

			property AlignedCollisionObjectArray^ CollisionObjects
			{
				AlignedCollisionObjectArray^ get();
			}

			property AlignedScalarArray^ HitFractions
			{
				AlignedScalarArray^ get();
			}

			property AlignedVector3Array^ HitNormalWorld
			{
				AlignedVector3Array^ get();
			}

			property AlignedVector3Array^ HitPointWorld
			{
				AlignedVector3Array^ get();
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

		ref class LocalConvexResult : IDisposable
		{
		internal:
			btCollisionWorld::LocalConvexResult* _native;

		private:
			LocalShapeInfo^ _localShapeInfo;

		public:
			!LocalConvexResult();
		protected:
			~LocalConvexResult();

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
				CollisionWorld::LocalShapeInfo^ get();
				void set(CollisionWorld::LocalShapeInfo^ value);
			}
		};

		ref class ConvexResultCallback abstract : IDisposable
		{
		internal:
			btCollisionWorld::ConvexResultCallback* _native;

			ConvexResultCallback(btCollisionWorld::ConvexResultCallback* native);

		public:
			!ConvexResultCallback();
		protected:
			~ConvexResultCallback();

		public:
			btScalar AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace);
			bool NeedsCollision(BroadphaseProxy^ proxy0);

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

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		ref class ClosestConvexResultCallback : ConvexResultCallback
		{
		public:
			ClosestConvexResultCallback(Vector3 convexFromWorld, Vector3 convexToWorld);
			ClosestConvexResultCallback(Vector3% convexFromWorld, Vector3% convexToWorld);

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

		ref class ClosestRayResultCallback : RayResultCallback
		{
		public:
			ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld);
			ClosestRayResultCallback(Vector3% rayFromWorld, Vector3% rayToWorld);

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

		ref class ContactResultCallback abstract : IDisposable
		{
		internal:
			ContactResultCallbackWrapper* _native;

			ContactResultCallback(ContactResultCallbackWrapper* callback);

		public:
			!ContactResultCallback();
		protected:
			~ContactResultCallback();

		public:
			ContactResultCallback();

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

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btCollisionWorld* _native;
		CollisionWorld(btCollisionWorld* native);

	protected:
		AlignedCollisionObjectArray^ _collisionObjectArray;
		Dispatcher^ _dispatcher;
		BroadphaseInterface^ _broadphase;

	public:
		!CollisionWorld();
	protected:
		~CollisionWorld();

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

	class ContactResultCallbackWrapper : public btCollisionWorld::ContactResultCallback
	{
	private:
		gcroot<CollisionWorld::ContactResultCallback^> _callback;

	public:
		ContactResultCallbackWrapper(CollisionWorld::ContactResultCallback^ callback);

		virtual bool needsCollision(btBroadphaseProxy* proxy0) const;
		virtual btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0, int partId0, int index0,
			const btCollisionObjectWrapper* colObj1, int partId1, int index1);

		virtual bool baseNeedsCollision(btBroadphaseProxy* proxy0) const;
	};
};
