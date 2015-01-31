#pragma once

namespace BulletSharp
{
	ref class AlignedScalarArray;
	ref class MultiBody;
	interface class IDebugDraw;

	public ref class MultiBodyConstraint abstract
	{
	internal:
		btMultiBodyConstraint* _native;

		MultiBodyConstraint(btMultiBodyConstraint* native);

	public:
		!MultiBodyConstraint();
	protected:
		~MultiBodyConstraint();

	protected:
		MultiBody^ _multiBodyA;
		MultiBody^ _multiBodyB;

	public:
#ifndef DISABLE_CONSTRAINTS
		//void CreateConstraintRows(MultiBodyConstraintArray^ constraintRows, MultiBodyJacobianData^ data,
		//	ContactSolverInfo^ infoGlobal);
#endif
#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ drawer) = 0;
#endif
		btScalar GetPosition(int row);
		//FloatArray^ JacobianA(int row);
		//FloatArray^ JacobianB(int row);
		void SetPosition(int row, btScalar pos);

		property int IslandIdA
		{
			int get();
		}

		property int IslandIdB
		{
			int get();
		}

		property bool IsUnilateral
		{
			bool get();
		}

		property btScalar MaxAppliedImpulse
		{
			btScalar get();
			void set(btScalar maxImp);
		}

		property MultiBody^ MultiBodyA
		{
			MultiBody^ get();
		}

		property MultiBody^ MultiBodyB
		{
			MultiBody^ get();
		}

		property int NumRows
		{
			int get();
		}
	};
};
