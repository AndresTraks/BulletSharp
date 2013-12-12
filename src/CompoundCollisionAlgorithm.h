#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObject;
	ref class CollisionObjectWrapper;
	ref class CollisionShape;
	ref class PersistentManifold;

	public delegate bool CompoundChildShapePairCallback(CollisionShape^ pShape0, CollisionShape^ pShape);

	public ref class CompoundCollisionAlgorithm : ActivatingCollisionAlgorithm
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
		static CompoundChildShapePairCallback^ _compoundChildShapePairCallback;

		CompoundCollisionAlgorithm(btCompoundCollisionAlgorithm* algorithm);

	public:
		static property CompoundChildShapePairCallback^ CompoundChildShapePairCallback
		{
			::CompoundChildShapePairCallback^ get();
			void set(::CompoundChildShapePairCallback^ value);
		}

		CompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped);

		CollisionAlgorithm^ GetChildAlgorithm (int n);
	};
};
