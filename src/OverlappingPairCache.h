#pragma once

#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	ref class AlignedBroadphasePairArray;

	public ref class OverlapCallback abstract : IDisposable
	{
	internal:
		btOverlapCallback* _native;

	public:
		!OverlapCallback();
	protected:
		~OverlapCallback();

	public:
		bool ProcessOverlap(BroadphasePair^ pair);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	public ref class OverlapFilterCallback abstract : IDisposable
	{
	internal:
		btOverlapFilterCallback* _native;
		OverlapFilterCallback(btOverlapFilterCallback* native);
		static OverlapFilterCallback^ GetManaged(btOverlapFilterCallback* callback);

	public:
		!OverlapFilterCallback();
	protected:
		~OverlapFilterCallback();

	public:
		OverlapFilterCallback();

		virtual bool NeedBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) abstract;

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	public ref class OverlappingPairCache abstract : OverlappingPairCallback
	{
	internal:
		OverlappingPairCache(btOverlappingPairCache* native);

	private:
		AlignedBroadphasePairArray^ _overlappingPairArray;

	public:
		void CleanOverlappingPair(BroadphasePair^ pair, Dispatcher^ dispatcher);
		void CleanProxyFromPairs(BroadphaseProxy^ proxy, Dispatcher^ dispatcher);
		BroadphasePair^ FindPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
		void ProcessAllOverlappingPairs(array<OverlapCallback^>^ callback, Dispatcher^ dispatcher);
#ifndef DISABLE_INTERNAL
		void SetInternalGhostPairCallback(OverlappingPairCallback^ ghostPairCallback);
#endif
		void SetOverlapFilterCallback(OverlapFilterCallback^ callback);
		void SortOverlappingPairs(Dispatcher^ dispatcher);

		property bool HasDeferredRemoval
		{
			bool get();
		}

		property int NumOverlappingPairs
		{
			int get();
		}

		property AlignedBroadphasePairArray^ OverlappingPairArray
		{
			AlignedBroadphasePairArray^ get();
		}
		/*
		property BroadphasePair^ OverlappingPairArrayPtr
		{
			BroadphasePair^ get();
		}
		*/
	};

	public ref class HashedOverlappingPairCache : OverlappingPairCache
	{
	internal:
		HashedOverlappingPairCache(btHashedOverlappingPairCache* native);

	public:
		HashedOverlappingPairCache();

		bool NeedsBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);

		property int Count
		{
			int get();
		}

		property BulletSharp::OverlapFilterCallback^ OverlapFilterCallback
		{
			BulletSharp::OverlapFilterCallback^ get();
			void set(BulletSharp::OverlapFilterCallback^ value);
		}
	};

	public ref class SortedOverlappingPairCache : OverlappingPairCache
	{
	internal:
		SortedOverlappingPairCache(btSortedOverlappingPairCache* native);

	public:
		SortedOverlappingPairCache();

		bool NeedsBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);

		property BulletSharp::OverlapFilterCallback^ OverlapFilterCallback
		{
			BulletSharp::OverlapFilterCallback^ get();
			void set(BulletSharp::OverlapFilterCallback^ value);
		}
	};

	public ref class NullPairCache : OverlappingPairCache
	{
	internal:
		NullPairCache(btNullPairCache* native);

	public:
		NullPairCache();
	};

	class OverlapFilterCallbackWrapper : public btOverlapFilterCallback
	{
	private:
		gcroot<OverlapFilterCallback^> _callback;

	public:
		OverlapFilterCallbackWrapper(OverlapFilterCallback^ callback);

		virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const;
	};
};
