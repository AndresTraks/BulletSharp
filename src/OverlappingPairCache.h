#pragma once

#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	public ref class OverlappingPairCache abstract : BulletSharp::OverlappingPairCallback
	{
	public:
		OverlappingPairCache(btOverlappingPairCache* pairCache);

	internal:
		property btOverlappingPairCache* UnmanagedPointer
		{
			btOverlappingPairCache* get() new;
		}
	};
};
