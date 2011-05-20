#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class ConvexConcaveCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		ref class SwappedCreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			SwappedCreateFunc();
		};

		ConvexConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1, bool isSwapped);

		void ClearCache();

	internal:
		property btConvexConcaveCollisionAlgorithm* UnmanagedPointer
		{
			btConvexConcaveCollisionAlgorithm* get() new;
		}
	};
};
