#pragma once

namespace BulletSharp
{
	ref class MultiBody;

	public ref class MultiBodySolverConstraint
	{
	internal:
		btMultiBodySolverConstraint* _native;
		MultiBodySolverConstraint(btMultiBodySolverConstraint* native);

	public:
		MultiBodySolverConstraint();

		property Vector3 AngularComponentA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AngularComponentB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar AppliedImpulse
		{
			btScalar get();
			//void set(btScalar value);
		}

		property btScalar AppliedPushImpulse
		{
			btScalar get();
			//void set(btScalar value);
		}

		property btScalar Cfm
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 ContactNormal1
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 ContactNormal2
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property int DeltaVelAindex
		{
			int get();
			void set(int value);
		}

		property int DeltaVelBindex
		{
			int get();
			void set(int value);
		}

		property btScalar Friction
		{
			btScalar get();
			void set(btScalar value);
		}

		property int FrictionIndex
		{
			int get();
			void set(int value);
		}

		property int JacAindex
		{
			int get();
			void set(int value);
		}

		property int JacBindex
		{
			int get();
			void set(int value);
		}

		property btScalar JacDiagABInv
		{
			btScalar get();
			void set(btScalar value);
		}

		property int LinkA
		{
			int get();
			void set(int value);
		}

		property int LinkB
		{
			int get();
			void set(int value);
		}

		property btScalar LowerLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property BulletSharp::MultiBody^ MultiBodyA
		{
			BulletSharp::MultiBody^ get();
			void set(BulletSharp::MultiBody^ value);
		}

		property BulletSharp::MultiBody^ MultiBodyB
		{
			BulletSharp::MultiBody^ get();
			void set(BulletSharp::MultiBody^ value);
		}

		property int OverrideNumSolverIterations
		{
			int get();
			void set(int value);
		}

		property Vector3 Relpos1CrossNormal
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 Relpos2CrossNormal
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Rhs
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RhsPenetration
		{
			btScalar get();
			void set(btScalar value);
		}

		property int SolverBodyIdA
		{
			int get();
			void set(int value);
		}

		property int SolverBodyIdB
		{
			int get();
			void set(int value);
		}

		property btScalar UpperLimit
		{
			btScalar get();
			void set(btScalar value);
		}
	};
};
