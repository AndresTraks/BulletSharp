#pragma once

// Fully implemented as of 07 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#pragma managed(pop)

#include "CollisionObject.h"
#include "CollisionWorld.h"

namespace BulletSharp
{
	ref class BroadphaseProxy;
	ref class CollisionObjectArray;
	ref class HashedOverlappingPairCache;

	public ref class GhostObject : CollisionObject
	{
	internal:
		GhostObject(btGhostObject* ghostObject);

	public:
		GhostObject();

		void AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy, BroadphaseProxy^ thisProxy);
		void AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy);
		//void ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld, Matrix convexToWorld,
		//	CollisionWorld::ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration);
		//void ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld, Matrix convexToWorld,
		//	CollisionWorld::ConvexResultCallback^ resultCallback);
		CollisionObject^ GetOverlappingObject(int index);
		void RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, CollisionWorld::RayResultCallback^ resultCallback);
		void RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher, BroadphaseProxy^ thisProxy);
		void RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher);

		static GhostObject^ Upcast(CollisionObject^ colObj);

		property int NumOverlappingObjects
		{
			int get();
		}

		property CollisionObjectArray^ OverlappingPairs
		{
			CollisionObjectArray^ get();
		}

	internal:
		virtual property btGhostObject* UnmanagedPointer
		{
			btGhostObject* get() new;
		}
	};

	public ref class PairCachingGhostObject : GhostObject
	{
	internal:
		PairCachingGhostObject(btPairCachingGhostObject* ghost);
	
	property HashedOverlappingPairCache^ OverlappingPairCache
	{
		HashedOverlappingPairCache^ get();
	}

	public:
		PairCachingGhostObject();

	internal:
		virtual property btPairCachingGhostObject* UnmanagedPointer
		{
			btPairCachingGhostObject* get() new;
		}
	};
}
