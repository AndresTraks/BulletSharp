#pragma once

namespace BulletSharp
{
	public ref class ContactSolverInfoData
	{
	internal:
		btContactSolverInfoData* _native;

	private:
		bool _preventDelete;

	internal:
		ContactSolverInfoData(btContactSolverInfoData* native, bool preventDelete);

		~ContactSolverInfoData();
		!ContactSolverInfoData();

	public:
		ContactSolverInfoData();

		property btScalar Damping
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Erp
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Erp2
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Friction
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar GlobalCfm
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar LinearSlop
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxErrorReduction
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxGyroscopicForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property int MinimumSolverBatchSize
		{
			int get();
			void set(int value);
		}

		property int NumIterations
		{
			int get();
			void set(int value);
		}

		property int RestingContactRestitutionThreshold
		{
			int get();
			void set(int value);
		}

		property btScalar Restitution
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SingleAxisRollingFrictionThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property SolverModes SolverMode
		{
			SolverModes get();
			void set(SolverModes value);
		}

		property btScalar Sor
		{
			btScalar get();
			void set(btScalar value);
		}

		property int SplitImpulse
		{
			int get();
			void set(int value);
		}

		property btScalar SplitImpulsePenetrationThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SplitImpulseTurnErp
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Tau
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar TimeStep
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar WarmstartingFactor
		{
			btScalar get();
			void set(btScalar value);
		}
	};

	public ref class ContactSolverInfo : ContactSolverInfoData
	{
	internal:
		ContactSolverInfo(btContactSolverInfo* native, bool preventDelete);

	public:
		ContactSolverInfo();
	};
};
