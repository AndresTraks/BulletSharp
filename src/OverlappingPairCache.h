#pragma once

#include "OverlappingPairCallback.h"

namespace BulletSharp
{
	public ref class OverlappingPairCache : BulletSharp::OverlappingPairCallback
	{
	internal:
		OverlappingPairCache(btOverlappingPairCache* pairCache);

		property btOverlappingPairCache* UnmanagedPointer
		{
			btOverlappingPairCache* get() new;
		}
	};
};
