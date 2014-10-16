#pragma once

#include "DiscreteCollisionDetectorInterface.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;
	ref class ConvexShape;
	ref class DebugDraw;

	public ref class GjkPairDetector : DiscreteCollisionDetectorInterface
	{
	internal:
		GjkPairDetector(btGjkPairDetector* native);

	public:
		GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB, SimplexSolverInterface^ simplexSolver,
			ConvexPenetrationDepthSolver^ penetrationDepthSolver);
		GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB, BroadphaseNativeType shapeTypeA,
			BroadphaseNativeType shapeTypeB, btScalar marginA, btScalar marginB, SimplexSolverInterface^ simplexSolver,
			ConvexPenetrationDepthSolver^ penetrationDepthSolver);

#ifndef DISABLE_DEBUGDRAW
		void GetClosestPointsNonVirtual(ClosestPointInput^ input, Result^ output,
			IDebugDraw^ debugDraw);
#else
		void GetClosestPointsNonVirtual(ClosestPointInput^ input, Result^ output);
#endif
#ifndef DISABLE_INTERNAL
		void SetIgnoreMargin(bool ignoreMargin);
#endif
		void SetMinkowskiA(ConvexShape^ minkA);
		void SetMinkowskiB(ConvexShape^ minkB);
		void SetPenetrationDepthSolver(ConvexPenetrationDepthSolver^ penetrationDepthSolver);

		property Vector3 CachedSeparatingAxis
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar CachedSeparatingDistance
		{
			btScalar get();
		}

		property int CatchDegeneracies
		{
			int get();
			void set(int value);
		}

		property int CurIter
		{
			int get();
			void set(int value);
		}

		property int DegenerateSimplex
		{
			int get();
			void set(int value);
		}

		property int FixContactNormalDirection
		{
			int get();
			void set(int value);
		}

		property int LastUsedMethod
		{
			int get();
			void set(int value);
		}
	};
};
