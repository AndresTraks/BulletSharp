#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System::Drawing;

namespace BulletSharp
{
	ref class BroadphaseInterface;
	ref class CollisionConfiguration;
	ref class CollisionObject;
	ref class CollisionObjectArray;
	ref class CollisionShape;
	ref class DebugDraw;
	ref class Dispatcher;
	ref class DispatcherInfo;
	ref class OverlappingPairCache;

	public ref class CollisionWorld : BulletSharp::IDisposable
	{
	public:
		ref class ContactResultCallback : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btCollisionWorld::ContactResultCallback* _callback;
		
		protected:
			ContactResultCallback(btCollisionWorld::ContactResultCallback* callback);
		public:
			!ContactResultCallback();
		protected:
			~ContactResultCallback();
		public:
			property bool IsDisposed
			{
				virtual bool get();
			}

		internal:
			property btCollisionWorld::ContactResultCallback* UnmanagedPointer
			{
				virtual btCollisionWorld::ContactResultCallback* get();
				void set(btCollisionWorld::ContactResultCallback* value);
			}
		};

		ref class RayResultCallback abstract : BulletSharp::IDisposable
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
			property BulletSharp::CollisionObject^ CollisionObject
			{
				BulletSharp::CollisionObject^ get();
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

			property Vector3 HitPointWorld
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
	protected:
		Dispatcher^ _dispatcher;
		BroadphaseInterface^ _broadphase;
#ifndef DISABLE_DEBUGDRAW
		DebugDraw^ _debugDraw;
#endif
		OverlappingPairCache^ _pairCache;
		CollisionObjectArray^ _collisionObjects;

	protected:
		CollisionWorld(btCollisionWorld* world);
	public:
		CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache, CollisionConfiguration^ collisionConfiguration);
	public:
		!CollisionWorld();
	protected:
		~CollisionWorld();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

		void AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask);
		void AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup);
		void AddCollisionObject(CollisionObject^ collisionObject);
		void ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB, ContactResultCallback^ resultCallback);
		void ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback);
		//void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration);
		//void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback);
#ifndef DISABLE_DEBUGDRAW
		void DebugDrawWorld();
#endif
		void PerformDiscreteCollisionDetection();
		void RayTest(Vector3 rayFromWorld, Vector3 rayToWorld,
			RayResultCallback^ resultCallback);
		void RayTestSingle(Matrix rayFromTrans, Matrix rayToTrans,
			CollisionObject^ collisionObject, CollisionShape^ collisionShape,
			Matrix colObjWorldTransform, RayResultCallback^ resultCallback);
		void RemoveCollisionObject(CollisionObject^ collisionObject);
		void UpdateAabbs();
		void UpdateSingleAabb(CollisionObject^ colObj);

		property BroadphaseInterface^ Broadphase
		{
			BroadphaseInterface^ get();
			void set(BroadphaseInterface^ value);
		}

		property BulletSharp::CollisionObjectArray^ CollisionObjectArray
		{
			BulletSharp::CollisionObjectArray^ get();
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
};
