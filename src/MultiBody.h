#pragma once

namespace BulletSharp
{
	ref class AlignedScalarArray;
	ref class AlignedVector3Array;
	ref class MultiBodyLink;
	ref class MultiBodyLinkCollider;
	ref class ScalarArray;

	public ref class MultiBody
	{
	private:
		array<MultiBodyLink^>^ _links;

	internal:
		btMultiBody* _native;

		MultiBody(btMultiBody* native);

	public:
		!MultiBody();
	protected:
		~MultiBody();

	public:
		MultiBody(int nLinks, btScalar mass, Vector3 inertia, bool fixedBase, bool canSleep,
			bool multiDof);
		MultiBody(int nLinks, btScalar mass, Vector3 inertia, bool fixedBase, bool canSleep);

		void AddBaseForce(Vector3 f);
		void AddBaseTorque(Vector3 t);
		void AddJointTorque(int i, btScalar Q);
		void AddLinkForce(int i, Vector3 f);
		void AddLinkTorque(int i, Vector3 t);
		void ApplyDeltaVee(ScalarArray^ deltaVee, btScalar multiplier);
		void ApplyDeltaVee(ScalarArray^ deltaVee);
		void CalcAccelerationDeltas(ScalarArray^ force, ScalarArray^ output, AlignedScalarArray^ scratchR,
			AlignedVector3Array^ scratchV);
		void CheckMotionAndSleepIfRequired(btScalar timestep);
		void ClearForcesAndTorques();
		void ClearVelocities();
		//void FillContactJacobian(int link, Vector3 contactPoint, Vector3 normal, ScalarArray^ jac,
		//	AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV, AlignedMatrix3x3Array^ scratchM);
		btScalar GetJointPos(int i);
		btScalar GetJointTorque(int i);
		btScalar GetJointVel(int i);
		MultiBodyLink^ GetLink(int index);
		Vector3 GetLinkForce(int i);
		Vector3 GetLinkInertia(int i);
		btScalar GetLinkMass(int i);
		Vector3 GetLinkTorque(int i);
		int GetParent(int linkNum);
		Quaternion GetParentToLocalRot(int i);
		Vector3 GetRVector(int i);
		void GoToSleep();
		Vector3 LocalDirToWorld(int i, Vector3 vec);
		Vector3 LocalPosToWorld(int i, Vector3 vec);
		void SetCanSleep(bool canSleep);
		void SetJointPos(int i, btScalar q);
		void SetJointVel(int i, btScalar qdot);
		void SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis,
			Vector3 jointAxis, Vector3 rVectorWhenQZero, bool disableParentCollision);
		void SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis,
			Vector3 jointAxis, Vector3 rVectorWhenQZero);
		void SetupRevolute(int i, btScalar mass, Vector3 inertia, int parent, Quaternion zeroRotParentToThis,
			Vector3 jointAxis, Vector3 parentAxisPosition, Vector3 myAxisPosition,
			bool disableParentCollision);
		void SetupRevolute(int i, btScalar mass, Vector3 inertia, int parent, Quaternion zeroRotParentToThis,
			Vector3 jointAxis, Vector3 parentAxisPosition, Vector3 myAxisPosition);
		void StepPositions(btScalar dt);
		//void StepVelocities(btScalar dt, AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV,
		//	AlignedMatrix3x3Array^ scratchM);
		void WakeUp();
		Vector3 WorldDirToLocal(int i, Vector3 vec);
		Vector3 WorldPosToLocal(int i, Vector3 vec);

		property btScalar AngularDamping
		{
			btScalar get();
			void set(btScalar damp);
		}

		property Vector3 AngularMomentum
		{
			Vector3 get();
		}

		property MultiBodyLinkCollider^ BaseCollider
		{
			MultiBodyLinkCollider^ get();
			void set(MultiBodyLinkCollider^ collider);
		}

		property Vector3 BaseForce
		{
			Vector3 get();
		}

		property Vector3 BaseInertia
		{
			Vector3 get();
			void set(Vector3 inertia);
		}

		property btScalar BaseMass
		{
			btScalar get();
			void set(btScalar mass);
		}

		property Vector3 BaseOmega
		{
			Vector3 get();
			void set(Vector3 omega);
		}

		property Vector3 BasePosition
		{
			Vector3 get();
			void set(Vector3 pos);
		}

		property Vector3 BaseTorque
		{
			Vector3 get();
		}

		property Vector3 BaseVelocity
		{
			Vector3 get();
			void set(Vector3 vel);
		}

		property bool CanSleep
		{
			bool get();
			void set(bool canSleep);
		}

		property int CompanionId
		{
			int get();
			void set(int id);
		}

		property bool HasFixedBase
		{
			bool get();
		}

		property bool HasSelfCollision
		{
			bool get();
			void set(bool hasSelfCollision);
		}

		property bool IsAwake
		{
			bool get();
		}

		property bool IsMultiDof
		{
			bool get();
		}

		property bool IsPosUpdated
		{
			bool get();
		}

		property bool IsUsingGlobalVelocities
		{
			bool get();
			void set(bool use);
		}

		property bool IsUsingRK4Integration
		{
			bool get();
			void set(bool use);
		}

		property btScalar KineticEnergy
		{
			btScalar get();
		}

		property btScalar LinearDamping
		{
			btScalar get();
			void set(btScalar damp);
		}

		property btScalar MaxAppliedImpulse
		{
			btScalar get();
			void set(btScalar maxImp);
		}

		property btScalar MaxCoordinateVelocity
		{
			btScalar get();
			void set(btScalar maxVel);
		}

		property int NumDofs
		{
			int get();
		}

		property int NumLinks
		{
			int get();
			void set(int numLinks);
		}

		property int NumPosVars
		{
			int get();
		}

		property bool UseGyroTerm
		{
			bool get();
			void set(bool useGyro);
		}

		property ScalarArray^ VelocityVector
		{
			ScalarArray^ get();
		}

		property Quaternion WorldToBaseRot
		{
			Quaternion get();
			void set(Quaternion rot);
		}
	};
};
