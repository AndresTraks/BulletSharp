#include "StdAfx.h"

#include "OptimizedBvh.h"

OptimizedBvh::OptimizedBvh(btOptimizedBvh* bvh)
: QuantizedBvh(bvh)
{
}

OptimizedBvh::OptimizedBvh()
: QuantizedBvh(new btOptimizedBvh())
{
}

btOptimizedBvh* OptimizedBvh::UnmanagedPointer::get()
{
	return (btOptimizedBvh*)QuantizedBvh::UnmanagedPointer;
}
