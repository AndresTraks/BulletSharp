#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class PoolAllocator : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btPoolAllocator* _allocator;

	internal:
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

	internal:
		property btPoolAllocator* UnmanagedPointer
		{
			virtual btPoolAllocator* get();
			void set( btPoolAllocator* value );
		}
	};
};
