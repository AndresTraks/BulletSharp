#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObjectWrapper;
	ref class CollisionShape;

	public delegate bool CompoundChildShapePairCallback(CollisionShape^ pShape0, CollisionShape^ pShape);

	public ref class CompoundCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btCompoundCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		ref class SwappedCreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			SwappedCreateFunc(btCompoundCollisionAlgorithm::SwappedCreateFunc* native);

		public:
			SwappedCreateFunc();
		};

	internal:
		static CompoundChildShapePairCallback^ _compoundChildShapePairCallback;

		CompoundCollisionAlgorithm(btCompoundCollisionAlgorithm* native);

	public:
		CompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ body0Wrap,
			CollisionObjectWrapper^ body1Wrap, bool isSwapped);

		CollisionAlgorithm^ GetChildAlgorithm(int n);

		static property CompoundChildShapePairCallback^ CompoundChildShapePairCallback
		{
			::CompoundChildShapePairCallback^ get();
			void set(::CompoundChildShapePairCallback^ value);
		}
	};
};
