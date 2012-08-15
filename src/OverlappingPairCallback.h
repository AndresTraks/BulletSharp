#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref struct BroadphasePair;
	ref class BroadphaseProxy;
	ref class Dispatcher;

	public ref class OverlappingPairCallback : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btOverlappingPairCallback* _unmanaged;
		OverlappingPairCallback(btOverlappingPairCallback* pairCallback);
		static OverlappingPairCallback^ GetManaged(btOverlappingPairCallback* callback);

	public:
		!OverlappingPairCallback();
	protected:
		~OverlappingPairCallback();

	public:
		BroadphasePair^ AddOverlappingPair(BroadphaseProxy^ proxy0,
			BroadphaseProxy^ proxy1);
		IntPtr RemoveOverlappingPair(BroadphaseProxy^ proxy0,
			BroadphaseProxy^ proxy1, Dispatcher^ dispatcher);
		void RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0,
			Dispatcher^ dispatcher);

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btOverlappingPairCallback* UnmanagedPointer
		{
			virtual btOverlappingPairCallback* get();
			void set(btOverlappingPairCallback* value);
		}
	};
};