#pragma once

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "CollisionObject.h"
#include "DebugDraw.h"
#include "IDispatcher.h"
#include "IDisposable.h"

using namespace System::Drawing;

namespace BulletSharp
{
	public ref class CollisionWorld : BulletSharp::IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btCollisionWorld* _world;
		protected:
			IDispatcher^ _dispatcher;
			BroadphaseInterface^ _broadphase;
			DebugDraw^ _debugDraw;
			OverlappingPairCache^ _pairCache;
			CollisionObjectArray^ _collisionObjects;

		protected:
			CollisionWorld(btCollisionWorld* world);
		public:
			CollisionWorld(BulletSharp::IDispatcher^ dispatcher, BroadphaseInterface^ pairCache, CollisionConfiguration^ collisionConfiguration);
		public:
			!CollisionWorld();
		protected:
			~CollisionWorld();
		public:
			property bool IsDisposed
			{
				virtual bool get();
			}

			void AddCollisionObject(CollisionObject^ collisionObject, short int collisionFilterGroup, short int collisionFilterMask);
			//void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration);
			//void ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback);
			void PerformDiscreteCollisionDetection();
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

			property BulletSharp::IDispatcher^ IDispatcher
			{
				BulletSharp::IDispatcher^ get();
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
