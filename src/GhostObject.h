#pragma once

#include "CollisionObject.h"
#include "CollisionWorld.h"
#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	ref class AlignedCollisionObjectArray;
	ref class BroadphaseProxy;
	ref class ConvexShape;
	ref class Dispatcher;
	ref class HashedOverlappingPairCache;

	public ref class GhostObject : CollisionObject
	{
		AlignedCollisionObjectArray^ _overlappingPairs;

	internal:
		GhostObject(btGhostObject* native);

	public:
		GhostObject();

#ifndef DISABLE_INTERNAL
		void AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy, BroadphaseProxy^ thisProxy);
		void AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy);
#endif
		void ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld, Matrix convexToWorld,
			ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration);
		void ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld, Matrix convexToWorld,
			ConvexResultCallback^ resultCallback);
		CollisionObject^ GetOverlappingObject(int index);
		void RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, RayResultCallback^ resultCallback);
#ifndef DISABLE_INTERNAL
		void RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher,
			BroadphaseProxy^ thisProxy);
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
		HashedOverlappingPairCache^ _hashPairCache;

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

		virtual BroadphasePair^ AddOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) override;
		virtual IntPtr RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
			Dispatcher^ dispatcher) override;
		virtual void RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0, Dispatcher^ dispatcher) override;
	};
};
