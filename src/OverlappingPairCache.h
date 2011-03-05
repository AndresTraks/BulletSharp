#pragma once

// Fully implemented as of 22 Mar 2010

#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	ref class AlignedBroadphasePairArray;

	public ref class OverlapCallback : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btOverlapCallback* _callback;

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

	internal:
		property btOverlapCallback* UnmanagedPointer
		{
			virtual btOverlapCallback* get();
			void set(btOverlapCallback* value);
		}
	};

	public ref class OverlapFilterCallback abstract : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btOverlapFilterCallback* _callback;

	internal:
		OverlapFilterCallback(btOverlapFilterCallback* callback);
		static OverlapFilterCallback^ GetObject(btOverlapFilterCallback* callback);

	public:
		!OverlapFilterCallback();
	protected:
		~OverlapFilterCallback();

	public:
		OverlapFilterCallback();

		virtual bool NeedBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) = 0;

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btOverlapFilterCallback* UnmanagedPointer
		{
			virtual btOverlapFilterCallback* get();
			void set(btOverlapFilterCallback* value);
		}
	};

	public ref class OverlappingPairCache : OverlappingPairCallback
	{
	internal:
		OverlappingPairCache(btOverlappingPairCache* pairCache);

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

	internal:
		property btOverlappingPairCache* UnmanagedPointer
		{
			btOverlappingPairCache* get() new;
		}
	};

	public ref class HashedOverlappingPairCache : OverlappingPairCache
	{
	internal:
		HashedOverlappingPairCache(btHashedOverlappingPairCache* pairCache);

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

	internal:
		property btHashedOverlappingPairCache* UnmanagedPointer
		{
			btHashedOverlappingPairCache* get() new;
		}
	};

	public ref class SortedOverlappingPairCache : OverlappingPairCache
	{
	internal:
		SortedOverlappingPairCache(btSortedOverlappingPairCache* sortedPairCache);

	public:
		SortedOverlappingPairCache();

		bool NeedsBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);

		property BulletSharp::OverlapFilterCallback^ OverlapFilterCallback
		{
			BulletSharp::OverlapFilterCallback^ get();
			void set(BulletSharp::OverlapFilterCallback^ value);
		}

	internal:
		property btSortedOverlappingPairCache* UnmanagedPointer
		{
			btSortedOverlappingPairCache* get() new;
		}
	};

	public ref class NullPairCache : OverlappingPairCache
	{
	internal:
		NullPairCache(btNullPairCache* nullPairCache);

	public:
		NullPairCache();

	internal:
		property btNullPairCache* UnmanagedPointer
		{
			btNullPairCache* get() new;
		}
	};

	class OverlapFilterCallbackWrapper : public btOverlapFilterCallback
	{
	private:
		auto_gcroot<OverlapFilterCallback^> _callback;

	public:
		OverlapFilterCallbackWrapper(OverlapFilterCallback^ callback);

		virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const;
	};
};
