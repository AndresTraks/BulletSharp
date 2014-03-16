#pragma once

#include "CollisionObject.h"
#include "CollisionWorld.h"
#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	ref class BroadphaseProxy;
	ref class AlignedCollisionObjectArray;
	ref class ConvexShape;
	ref class HashedOverlappingPairCache;

	public ref class GhostObject : CollisionObject
	{
	internal:
		GhostObject(btGhostObject* native);

	private:
		AlignedCollisionObjectArray^ _overlappingPairs;

	public:
		GhostObject();

#ifndef DISABLE_INTERNAL
		void AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy, BroadphaseProxy^ thisProxy);
		void AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy);
#endif
		void ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld, Matrix convexToWorld, CollisionWorld::ConvexResultCallback^ resultCallback, float allowedCcdPenetration);
		void ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld, Matrix convexToWorld, CollisionWorld::ConvexResultCallback^ resultCallback);
		CollisionObject^ GetOverlappingObject(int index);
		void RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, CollisionWorld::RayResultCallback^ resultCallback);

#ifndef DISABLE_INTERNAL
		void RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher, BroadphaseProxy^ thisProxy);
		void RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher);
#endif

		static GhostObject^ Upcast(CollisionObject^ colObj);

		property int NumOverlappingObjects
		{
			int get();
		}

		property AlignedCollisionObjectArray^ OverlappingPairs
		{
			AlignedCollisionObjectArray^ get();
		}
	};

	public ref class PairCachingGhostObject : GhostObject
	{
	internal:
		PairCachingGhostObject(btPairCachingGhostObject* native);

	private:
		HashedOverlappingPairCache^ _overlappingPairCache;

	public:
		PairCachingGhostObject();

		property HashedOverlappingPairCache^ OverlappingPairCache
		{
			HashedOverlappingPairCache^ get();
		}
	};

	public ref class GhostPairCallback : OverlappingPairCallback
	{
	internal:
		GhostPairCallback(btGhostPairCallback* native);

	public:
		GhostPairCallback();
	};
};
