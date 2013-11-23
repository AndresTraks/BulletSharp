#pragma once

namespace BulletSharp
{
	ref class AlignedScalarArray;
	ref class MultiBody;
/*
	public ref class MultiBodyJacobianData
	{
	internal:
		btMultiBodyJacobianData* _native;
		MultiBodyJacobianData(btMultiBodyJacobianData* native);

	public:
		MultiBodyJacobianData();

		AlignedScalarArray^ GetDeltaVelocities();
		AlignedScalarArray^ GetDeltaVelocitiesUnitImpulse();
		int GetFixedBodyId();
		AlignedScalarArray^ GetJacobians();
		AlignedObjectArray<btMatrix3x3> GetScratch_m();
		AlignedScalarArray^ GetScratch_r();
		AlignedObjectArray<btVector3> GetScratch_v();
		AlignedObjectArray^ GetSolverBodyPool();
		void SetDeltaVelocities(AlignedScalarArray^ value);
		void SetDeltaVelocitiesUnitImpulse(AlignedScalarArray^ value);
		void SetFixedBodyId(int value);
		void SetJacobians(AlignedScalarArray^ value);
		void SetScratch_m(AlignedObjectArray<btMatrix3x3> value);
		void SetScratch_r(AlignedScalarArray^ value);
		void SetScratch_v(AlignedObjectArray<btVector3> value);
		void SetSolverBodyPool(AlignedObjectArray^ value);

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

		property AlignedObjectArray<btMatrix3x3> Scratch_m
		{
			AlignedObjectArray<btMatrix3x3> get();
			void set(AlignedObjectArray<btMatrix3x3> value);
		}

		property AlignedScalarArray^ Scratch_r
		{
			AlignedScalarArray^ get();
			void set(AlignedScalarArray^ value);
		}

		property AlignedObjectArray<btVector3> Scratch_v
		{
			AlignedObjectArray<btVector3> get();
			void set(AlignedObjectArray<btVector3> value);
		}

		property AlignedObjectArray^ SolverBodyPool
		{
			AlignedObjectArray^ get();
			void set(AlignedObjectArray^ value);
		}
	};
*/
	public ref class MultiBodyConstraint
	{
	internal:
		btMultiBodyConstraint* _native;
		MultiBodyConstraint(btMultiBodyConstraint* native);

	public:
		//void CreateConstraintRows(MultiBodyConstraintArray^ constraintRows, MultiBodyJacobianData^ data, ContactSolverInfo^ infoGlobal);
		float GetPosition(int row);
		//FloatArray^ JacobianA(int row);
		//FloatArray^ JacobianB(int row);
		void SetMaxAppliedImpulse(float maxImp);
		void SetPosition(int row, float pos);

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

		property float MaxAppliedImpulse
		{
			float get();
			void set(float value);
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
