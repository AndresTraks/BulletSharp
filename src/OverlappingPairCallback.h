#pragma once

namespace BulletSharp
{
	ref struct BroadphasePair;
	ref class BroadphaseProxy;
	ref class Dispatcher;

	public ref class OverlappingPairCallback abstract : IDisposable
	{
	internal:
		btOverlappingPairCallback* _native;

	private:
		bool _preventDelete;

	internal:
		OverlappingPairCallback(btOverlappingPairCallback* native, bool preventDelete);
		static OverlappingPairCallback^ GetManaged(btOverlappingPairCallback* callback);

	public:
		!OverlappingPairCallback();
	protected:
		~OverlappingPairCallback();

	public:
		BroadphasePair^ AddOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
		IntPtr RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
			Dispatcher^ dispatcher);
		void RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0, Dispatcher^ dispatcher);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
};
