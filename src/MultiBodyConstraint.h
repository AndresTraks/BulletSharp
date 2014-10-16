#pragma once

namespace BulletSharp
{
	ref class AlignedScalarArray;
	ref class MultiBody;
/*
	public ref class MultiBodyJacobianData : IDisposable
	{
	internal:
		btMultiBodyJacobianData* _native;
		MultiBodyJacobianData(btMultiBodyJacobianData* native);

	public:
		!MultiBodyJacobianData();
	protected:
		~MultiBodyJacobianData();

	public:
		MultiBodyJacobianData();

		property AlignedScalarArray^ DeltaVelocities
		{
			AlignedScalarArray^ get();
			void set(AlignedScalarArray^ value);
		}

		property AlignedScalarArray^ DeltaVelocitiesUnitImpulse
		{
			AlignedScalarArray^ get();
			void set(AlignedScalarArray^ value);
		}

		property int FixedBodyId
		{
			int get();
			void set(int value);
		}

		property AlignedScalarArray^ Jacobians
		{
			AlignedScalarArray^ get();
			void set(AlignedScalarArray^ value);
		}

		property AlignedMatrix3x3Array^ ScratchM
		{
			AlignedMatrix3x3Array^ get();
			void set(AlignedMatrix3x3Array^ value);
		}

		property AlignedScalarArray^ ScratchR
		{
			AlignedScalarArray^ get();
			void set(AlignedScalarArray^ value);
		}

		property AlignedVector3Array^ ScratchV
		{
			AlignedVector3Array^ get();
			void set(AlignedVector3Array^ value);
		}

		property AlignedObjectArray^ SolverBodyPool
		{
			AlignedObjectArray^ get();
			void set(AlignedObjectArray^ value);
		}
	};
*/
	public ref class MultiBodyConstraint abstract : IDisposable
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
		//void CreateConstraintRows(MultiBodyConstraintArray^ constraintRows, MultiBodyJacobianData^ data,
		//	ContactSolverInfo^ infoGlobal);
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
