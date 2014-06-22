#pragma once

namespace BulletSharp
{
	public ref class PoolAllocator : ITrackingDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btPoolAllocator* _native;

		PoolAllocator(btPoolAllocator* allocator);

	public:
		!PoolAllocator();
	protected:
		~PoolAllocator();

	public:
		PoolAllocator(int elemSize, int maxElements);

		IntPtr Allocate(int size);
		bool ValidPtr(IntPtr ptr);
		void FreeMemory(IntPtr ptr);

		property int ElementSize
		{
			int get();
		}

		property int FreeCount
		{
			int get();
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property int MaxCount
		{
			int get();
		}

		property IntPtr PoolAddress
		{
			IntPtr get();
		}

		property int UsedCount
		{
			int get();
		}
	};
};
