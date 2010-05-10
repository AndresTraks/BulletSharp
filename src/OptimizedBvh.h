#pragma once

#include "QuantizedBvh.h"

namespace BulletSharp
{
	public ref class OptimizedBvh : QuantizedBvh
	{
	internal:
		OptimizedBvh(btOptimizedBvh* bvh);
	
	public:
		OptimizedBvh();

	internal:
		property btOptimizedBvh* UnmanagedPointer
		{
			btOptimizedBvh* get() new;
		}
	};
};
