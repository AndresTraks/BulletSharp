#pragma once

#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	ref class AlignedBroadphasePairArray;

	public ref class OverlapCallback abstract
	{
	internal:
		btOverlapCallback* _native;

		~OverlapCallback();
		!OverlapCallback();

	public:
		bool ProcessOverlap(BroadphasePair^ pair);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	public ref class OverlapFilterCallback abstract
	{
	internal:
		btOverlapFilterCallback* _native;

		OverlapFilterCallback(btOverlapFilterCallback* native);

		~OverlapFilterCallback();
		!OverlapFilterCallback();

	protected:
		OverlapFilterCallback();
	
	public:
		virtual bool NeedBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) abstract;

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	public ref class OverlappingPairCache abstract : OverlappingPairCallback
	{
	internal:
		OverlappingPairCache(btOverlappingPairCache* native, bool preventDelete);

	private:
		AlignedBroadphasePairArray^ _overlappingPairArray;
#ifndef DISABLE_INTERNAL
		OverlappingPairCallback^ _ghostPairCallback;
#endif

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
	private:
		OverlapFilterCallback^ _overlapFilterCallback;

	internal:
		HashedOverlappingPairCache(btHashedOverlappingPairCache* native, bool preventDelete);

	public:
		HashedOverlappingPairCache();

		virtual BroadphasePair^ AddOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) override;
		bool NeedsBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
		virtual IntPtr RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
			Dispatcher^ dispatcher) override;
		virtual void RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0, Dispatcher^ dispatcher) override;

		property int Count
		{
			int get();
		}

		property OverlapFilterCallback^ OverlapFilterCallback
		{
			BulletSharp::OverlapFilterCallback^ get();
			void set(BulletSharp::OverlapFilterCallback^ value);
		}
	};

	public ref class SortedOverlappingPairCache : OverlappingPairCache
	{
	private:
		OverlapFilterCallback^ _overlapFilterCallback;

	public:
		SortedOverlappingPairCache();

		virtual BroadphasePair^ AddOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) override;
		bool NeedsBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
		virtual IntPtr RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
			Dispatcher^ dispatcher) override;
		virtual void RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0, Dispatcher^ dispatcher) override;

		property OverlapFilterCallback^ OverlapFilterCallback
		{
			BulletSharp::OverlapFilterCallback^ get();
			void set(BulletSharp::OverlapFilterCallback^ value);
		}
	};

	public ref class NullPairCache : OverlappingPairCache
	{
	public:
		NullPairCache();

		virtual BroadphasePair^ AddOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) override;
		virtual IntPtr RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
			Dispatcher^ dispatcher) override;
		virtual void RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0, Dispatcher^ dispatcher) override;
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
