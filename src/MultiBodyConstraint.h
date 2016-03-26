#pragma once

namespace BulletSharp
{
	ref class ContactSolverInfo;
	ref class MultiBody;
	ref class MultiBodyConstraintArray;
	interface class IDebugDraw;

	public ref class MultiBodyConstraint abstract
	{
	internal:
		btMultiBodyConstraint* _native;

		MultiBodyConstraint(btMultiBodyConstraint* native);

		~MultiBodyConstraint();
		!MultiBodyConstraint();

	protected:
		MultiBody^ _multiBodyA;
		MultiBody^ _multiBodyB;

	public:
		void AllocateJacobiansMultiDof();
#ifndef DISABLE_CONSTRAINTS
		//void CreateConstraintRows(MultiBodyConstraintArray^ constraintRows, MultiBodyJacobianData^ data,
		//	ContactSolverInfo^ infoGlobal);
#endif
#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ drawer) = 0;
#endif
		void FinalizeMultiDof();
		btScalar GetAppliedImpulse(int dof);
		btScalar GetPosition(int row);
		void InternalSetAppliedImpulse(int dof, btScalar appliedImpulse);
		//ScalarArray^ JacobianA(int row);
		//ScalarArray^ JacobianB(int row);
		void SetPosition(int row, btScalar pos);
		void UpdateJacobianSizes();

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
