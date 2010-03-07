#pragma once

#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	ref class BroadphasePairArray;

	public ref class OverlapCallback
	{
	};

	public ref class OverlappingPairCache : OverlappingPairCallback
	{
	internal:
		OverlappingPairCache(btOverlappingPairCache* pairCache);

	public:
		void CleanOverlappingPair(BroadphasePair^ pair, Dispatcher^ dispatcher);
		void CleanProxyFromPairs(BroadphaseProxy^ proxy, Dispatcher^ dispatcher);
		BroadphasePair^ FindPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
		//virtual void ProcessAllOverlappingPairs(array<OverlapCallback^>^ callback, Dispatcher^ dispatcher);
		void SetInternalGhostPairCallback(OverlappingPairCallback^ ghostPairCallback);
		//void SetOverlapFilterCallback(OverlapFilterCallback^ callback);
		void SortOverlappingPairs(Dispatcher^ dispatcher);

		property bool HasDeferredRemoval
		{
			bool get();
		}

		property int NumOverlappingPairs
		{
			int get();
		}

		property BroadphasePairArray^ OverlappingPairArray
		{
			BroadphasePairArray^ get();
		}

	internal:
		property btOverlappingPairCache* UnmanagedPointer
		{
			btOverlappingPairCache* get() new;
		}
	};
};
