#pragma once

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "CollisionObject.h"
#include "DebugDraw.h"
#include "Enums.h"
#include "Dispatcher.h"
#include "IDisposable.h"

using namespace System::Drawing;

namespace BulletSharp
{
	public ref class CollisionWorld : BulletSharp::IDisposable
	{
	public:
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
		DebugDraw^ _debugDraw;
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
		//void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration);
		//void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback);
		void PerformDiscreteCollisionDetection();
		void RayTest(Vector3 rayFromWorld, Vector3 rayToWorld,
			RayResultCallback^ resultCallback);
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

		property DebugDraw^ DebugDrawer
		{
			DebugDraw^ get();
			void set(DebugDraw^ value);
		}

		property BulletSharp::Dispatcher^ Dispatcher
		{
			BulletSharp::Dispatcher^ get();
		}

		//property BulletSharp::DispatcherInfo^ DispatchInfo
		//{
		//	BulletSharp::DispatcherInfo^ get();
		//	void set(BulletSharp::DispatcherInfo^ value);
		//}

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
