#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionDispatcher;
	ref class CollisionObjectWrapper;
	ref class CollisionShape;
	ref class CompoundShape;
	ref class ConcaveShape;
	ref class GImpactShapeInterface;
	ref class ManifoldResult;

	public ref class GImpactCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btGImpactCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

	internal:
		GImpactCollisionAlgorithm(btGImpactCollisionAlgorithm* native);

	public:
		GImpactCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ body0Wrap,
			CollisionObjectWrapper^ body1Wrap);

		void GImpactVsCompoundShape(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			GImpactShapeInterface^ shape0, CompoundShape^ shape1, bool swapped);
		void GImpactVsConcave(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			GImpactShapeInterface^ shape0, ConcaveShape^ shape1, bool swapped);
		void GImpactVsGImpact(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			GImpactShapeInterface^ shape0, GImpactShapeInterface^ shape1);
		void GImpactVsShape(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			GImpactShapeInterface^ shape0, CollisionShape^ shape1, bool swapped);
		//ManifoldResult^ InternalGetResultOut();
		static void RegisterAlgorithm(CollisionDispatcher^ dispatcher);

		property int Face0
		{
			int get();
			void set(int value);
		}

		property int Face1
		{
			int get();
			void set(int value);
		}

		property int Part0
		{
			int get();
			void set(int value);
		}

		property int Part1
		{
			int get();
			void set(int value);
		}
	};
};
