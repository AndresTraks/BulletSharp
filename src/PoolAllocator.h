#pragma once

namespace BulletSharp
{
	public ref class PoolAllocator
	{
	internal:
		btPoolAllocator* _native;

	private:
		bool _preventDelete;

	internal:
		PoolAllocator(btPoolAllocator* native, bool preventDelete);

		~PoolAllocator();
		!PoolAllocator();

	public:
		PoolAllocator(int elemSize, int maxElements);

		IntPtr Allocate(int size);
		void FreeMemory(IntPtr ptr);
		bool ValidPtr(IntPtr ptr);

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
