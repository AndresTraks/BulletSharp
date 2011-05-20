#pragma once

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObject;

	public ref class SoftBodyConcaveCollisionAlgorithm abstract : CollisionAlgorithm
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

	internal:
		SoftBodyConcaveCollisionAlgorithm(btSoftBodyConcaveCollisionAlgorithm* algorithm);

	public:
		SoftBodyConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1, bool isSwapped);

		void ClearCache();

	internal:
		property btSoftBodyConcaveCollisionAlgorithm* UnmanagedPointer
		{
			btSoftBodyConcaveCollisionAlgorithm* get() new;
		}
	};
};
