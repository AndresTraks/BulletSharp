#pragma once

namespace BulletSharp
{
	public ref class StackAlloc
	{
	private:
		btStackAlloc* _alloc;

	internal:
		StackAlloc(btStackAlloc* alloc);

		property btStackAlloc* UnmanagedPointer
		{
			btStackAlloc* get();
			void set(btStackAlloc* value);
		}
	};
};