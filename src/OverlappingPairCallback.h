#pragma once

namespace BulletSharp
{
	ref struct BroadphasePair;
	ref class BroadphaseProxy;
	ref class Dispatcher;

	public ref class OverlappingPairCallback abstract
	{
	private:
		bool _preventDelete;

	internal:
		btOverlappingPairCallback* _native;

		OverlappingPairCallback(btOverlappingPairCallback* native, bool preventDelete);

		~OverlappingPairCallback();
		!OverlappingPairCallback();

	protected:
		OverlappingPairCallback();

	public:
		virtual BroadphasePair^ AddOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1) = 0;
		virtual IntPtr RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
			Dispatcher^ dispatcher) = 0;
		virtual void RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0, Dispatcher^ dispatcher) = 0;

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	struct OverlappingPairCallbackWrapper : public btOverlappingPairCallback
	{
	protected:
		void* _overlappingPairCallback;

	public:
		OverlappingPairCallbackWrapper(OverlappingPairCallback^ overlappingPairCallback);
		~OverlappingPairCallbackWrapper();

		virtual btBroadphasePair* addOverlappingPair(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1);
		virtual void* removeOverlappingPair(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1, btDispatcher* dispatcher);
		virtual void removeOverlappingPairsContainingProxy(btBroadphaseProxy* proxy0, btDispatcher* dispatcher);
	};
};
