#pragma once

// Fully implemented as of 23 apr 2010

#include "IDisposable.h"

using namespace msclr;
using namespace System::Drawing;

namespace BulletSharp
{
	ref class BroadphaseInterface;
	ref class BroadphaseProxy;
	ref class CollisionConfiguration;
	ref class CollisionObject;
	ref class AlignedCollisionObjectArray;
	ref class CollisionShape;
	ref class ConvexShape;
	ref class DebugDraw;
	ref class Dispatcher;
	ref class DispatcherInfo;
	ref class ManifoldPoint;
	ref class OverlappingPairCache;
	ref class Serializer;

	class ContactResultCallbackWrapper;

	public ref class CollisionWorld : BulletSharp::IDisposable
	{
	public:
		ref class LocalShapeInfo
		{
		private:
			btCollisionWorld::LocalShapeInfo* _info;

		internal:
			LocalShapeInfo(btCollisionWorld::LocalShapeInfo* info);

		public:
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

		internal:
			property btCollisionWorld::LocalShapeInfo* UnmanagedPointer
			{
				virtual btCollisionWorld::LocalShapeInfo* get();
				void set(btCollisionWorld::LocalShapeInfo* value);
			}
		};

		ref class LocalConvexResult
		{
		private:
			btCollisionWorld::LocalConvexResult* _result;

		public:
			LocalConvexResult(CollisionObject^ collisionObject, LocalShapeInfo^ localShapeInfo,
				Vector3 hitNormalLocal, Vector3 hitPointLocal, btScalar hitFraction);

			property BulletSharp::CollisionObject^ CollisionObject
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

		internal:
			property btCollisionWorld::LocalConvexResult* UnmanagedPointer
			{
				virtual btCollisionWorld::LocalConvexResult* get();
				void set(btCollisionWorld::LocalConvexResult* value);
			}
		};

		ref class ConvexResultCallback : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btCollisionWorld::ConvexResultCallback* _callback;

		protected:
			ConvexResultCallback(btCollisionWorld::ConvexResultCallback* callback);

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

		internal:
			property btCollisionWorld::ConvexResultCallback* UnmanagedPointer
			{
				virtual btCollisionWorld::ConvexResultCallback* get();
				void set(btCollisionWorld::ConvexResultCallback* value);
			}
		};

		ref class ClosestConvexResultCallback : ConvexResultCallback
		{
		internal:
			ClosestConvexResultCallback(btCollisionWorld::ClosestConvexResultCallback* callback);

		public:
			ClosestConvexResultCallback(Vector3 convexFromWorld, Vector3 convexToWorld);

			property BulletSharp::CollisionObject^ CollisionObject
			{
				BulletSharp::CollisionObject^ get();
				void set(BulletSharp::CollisionObject^ value);
			}

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

			property btCollisionWorld::ClosestConvexResultCallback* UnmanagedPointer
			{
				btCollisionWorld::ClosestConvexResultCallback* get() new;
			}
		};

		ref class ContactResultCallback abstract : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			ContactResultCallbackWrapper* _callback;

		internal:
			ContactResultCallback(ContactResultCallbackWrapper* callback);

		public:
			!ContactResultCallback();
		protected:
			~ContactResultCallback();

		public:
			ContactResultCallback();

			virtual btScalar AddSingleResult(ManifoldPoint^ cp, CollisionObject^ colObj0, int partId0, int index0,
				CollisionObject^ colObj1, int partId1, int index1) = 0;
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

		internal:
			property ContactResultCallbackWrapper* UnmanagedPointer
			{
				virtual ContactResultCallbackWrapper* get();
				void set(ContactResultCallbackWrapper* value);
			}
		};

		ref class LocalRayResult
		{
		private:
			btCollisionWorld::LocalRayResult* _result;

		public:
			LocalRayResult(CollisionObject^ collisionObject, LocalShapeInfo^ localShapeInfo,
				Vector3 hitNormalLocal, btScalar hitFraction);

			property BulletSharp::CollisionObject^ CollisionObject
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

		internal:
			property btCollisionWorld::LocalRayResult* UnmanagedPointer
			{
				virtual btCollisionWorld::LocalRayResult* get();
				void set(btCollisionWorld::LocalRayResult* value);
			}
		};

		ref class RayResultCallback : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btCollisionWorld::RayResultCallback* _callback;

		protected:
			RayResultCallback(btCollisionWorld::RayResultCallback* callback);

		public:
			!RayResultCallback();
		protected:
			~RayResultCallback();

		public:
			btScalar AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace);
			bool NeedsCollision(BroadphaseProxy^ proxy0);

			property BulletSharp::CollisionObject^ CollisionObject
			{
				BulletSharp::CollisionObject^ get();
				void set(BulletSharp::CollisionObject^ value);
			}

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

		internal:
			property btCollisionWorld::RayResultCallback* UnmanagedPointer
			{
				virtual btCollisionWorld::RayResultCallback* get();
				void set(btCollisionWorld::RayResultCallback* value);
			}
		};

		ref class ClosestRayResultCallback : RayResultCallback
		{
		public:
			ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld);

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

		internal:
			property btCollisionWorld::ClosestRayResultCallback* UnmanagedPointer
			{
				btCollisionWorld::ClosestRayResultCallback* get() new;
			}
		};

	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btCollisionWorld* _world;
		AlignedCollisionObjectArray^ _collisionObjectArray;

	protected:
		CollisionConfiguration^ _collisionConfiguration;
		Dispatcher^ _dispatcher;
		BroadphaseInterface^ _broadphase;
#ifndef DISABLE_DEBUGDRAW
		DebugDraw^ _debugDraw;
#endif

	internal:
		CollisionWorld(btCollisionWorld* world);

	public:
		!CollisionWorld();
	protected:
		~CollisionWorld();

	public:
		CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache, CollisionConfiguration^ collisionConfiguration);

		static void ObjectQuerySingle(ConvexShape^ castShape, Matrix rayFromTrans, Matrix rayToTrans,
			CollisionObject^ collisionObject, CollisionShape^ collisionShape,
			Matrix colObjWorldTransform, ConvexResultCallback^ resultCallback,
			btScalar allowedPenetration);
		static void RayTestSingle(Matrix rayFromTrans, Matrix rayToTrans,
			CollisionObject^ collisionObject, CollisionShape^ collisionShape,
			Matrix colObjWorldTransform, RayResultCallback^ resultCallback);

		void AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask);
		void AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup);
		void AddCollisionObject(CollisionObject^ collisionObject);
		void ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB, ContactResultCallback^ resultCallback);
		void ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback);
		void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration);
		void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback);
#ifndef DISABLE_DEBUGDRAW
		void DebugDrawObject(Matrix worldTransform, CollisionShape^ shape, BtColor color);
		void DebugDrawWorld();
#endif
		void PerformDiscreteCollisionDetection();
		void RayTest(Vector3 rayFromWorld, Vector3 rayToWorld,
			RayResultCallback^ resultCallback);
		void RemoveCollisionObject(CollisionObject^ collisionObject);
		void UpdateAabbs();
		void UpdateSingleAabb(CollisionObject^ colObj);

#ifndef DISABLE_SERIALIZE
		void Serialize(Serializer^ serializer);
#endif

		property bool IsDisposed
		{
			virtual bool get();
		}

		property BroadphaseInterface^ Broadphase
		{
			BroadphaseInterface^ get();
			void set(BroadphaseInterface^ value);
		}

		property AlignedCollisionObjectArray^ CollisionObjectArray
		{
			AlignedCollisionObjectArray^ get();
		}
#ifndef DISABLE_DEBUGDRAW
		property DebugDraw^ DebugDrawer
		{
			DebugDraw^ get();
			void set(DebugDraw^ value);
		}
#endif
		property BulletSharp::Dispatcher^ Dispatcher
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
			void set(bool value);
		}

		property int NumCollisionObjects
		{
			int get();
		}

		property OverlappingPairCache^ PairCache
		{
			OverlappingPairCache^ get();
		}

	internal:
		property btCollisionWorld* UnmanagedPointer
		{
			virtual btCollisionWorld* get();
			void set(btCollisionWorld* value);
		}
	};

	class ContactResultCallbackWrapper : public btCollisionWorld::ContactResultCallback
	{
	private:
		auto_gcroot<CollisionWorld::ContactResultCallback^> _callback;

	public:
		ContactResultCallbackWrapper(CollisionWorld::ContactResultCallback^ callback);

		virtual bool needsCollision(btBroadphaseProxy* proxy0) const;
		virtual btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObject* colObj0, int partId0, int index0,
			const btCollisionObject* colObj1, int partId1, int index1);

		virtual bool baseNeedsCollision(btBroadphaseProxy* proxy0) const;
	};
};
