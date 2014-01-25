#pragma once

namespace BulletSharp
{
	ref class AlignedScalarArray;
	ref class AlignedVector3Array;
	ref class MultibodyLink;
	ref class MultiBodyLinkCollider;
	ref class ScalarArray;

	public ref class MultiBody
	{
	private:
		array<MultibodyLink^>^ _links;

	internal:
		btMultiBody* _native;
		MultiBody(btMultiBody* native);

	public:
		MultiBody(int nLinks, btScalar mass, Vector3 inertia, bool fixedBase, bool canSleep, bool multiDof);

		void AddBaseForce(Vector3 f);
		void AddBaseTorque(Vector3 t);
		void AddJointTorque(int i, btScalar Q);
		void AddLinkForce(int i, Vector3 f);
		void AddLinkTorque(int i, Vector3 t);
		void ApplyDeltaVee(ScalarArray^ delta_vee, btScalar multiplier);
		void ApplyDeltaVee(ScalarArray^ delta_vee);
		void CalcAccelerationDeltas(ScalarArray^ force, ScalarArray^ output, AlignedScalarArray^ scratch_r, AlignedVector3Array^ scratch_v);
		void CheckMotionAndSleepIfRequired(btScalar timestep);
		void ClearForcesAndTorques();
		void ClearVelocities();
		//void FillContactJacobian(int link, Vector3 contact_point, Vector3 normal, ScalarArray jac, AlignedScalarArray^ scratch_r, AlignedVector3Array^ scratch_v, AlignedMatrix3x3Array^ scratch_m);
		btScalar GetJointPos(int i);
		btScalar GetJointTorque(int i);
		btScalar GetJointVel(int i);
		MultibodyLink^ GetLink(int index);
		Vector3 GetLinkForce(int i);
		Vector3 GetLinkInertia(int i);
		btScalar GetLinkMass(int i);
		Vector3 GetLinkTorque(int i);
		int GetParent(int link_num);
		Quaternion GetParentToLocalRot(int i);
		Vector3 GetRVector(int i);
		void GoToSleep();
		Vector3 LocalDirToWorld(int i, Vector3 vec);
		Vector3 LocalPosToWorld(int i, Vector3 vec);
		void SetCanSleep(bool canSleep);
		void SetJointPos(int i, btScalar q);
		void SetJointVel(int i, btScalar qdot);
		void SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis, Vector3 joint_axis, Vector3 rVectorWhenQZero, bool disableParentCollision);
		void SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis, Vector3 joint_axis, Vector3 rVectorWhenQZero);
		void SetupRevolute(int i, btScalar mass, Vector3 inertia, int parent, Quaternion zero_rot_parent_to_this, Vector3 joint_axis, Vector3 parent_axis_position, Vector3 my_axis_position, bool disableParentCollision);
		void SetupRevolute(int i, btScalar mass, Vector3 inertia, int parent, Quaternion zero_rot_parent_to_this, Vector3 joint_axis, Vector3 parent_axis_position, Vector3 my_axis_position);
		void StepPositions(btScalar dt);
		//void StepVelocities(btScalar dt, AlignedScalarArray^ scratch_r, AlignedVector3Array^ scratch_v, AlignedMatrix3x3Array^ scratch_m);
		void WakeUp();
		Vector3 WorldDirToLocal(int i, Vector3 vec);
		Vector3 WorldPosToLocal(int i, Vector3 vec);

		property btScalar AngularDamping
		{
			btScalar get();
		}

		property Vector3 AngularMomentum
		{
			Vector3 get();
		}

		property MultiBodyLinkCollider^ BaseCollider
		{
			MultiBodyLinkCollider^ get();
			void set(MultiBodyLinkCollider^ value);
		}

		property Vector3 BaseForce
		{
			Vector3 get();
		}

		property Vector3 BaseInertia
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar BaseMass
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 BaseOmega
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 BasePosition
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 BaseTorque
		{
			Vector3 get();
		}

		property Vector3 BaseVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property int CompanionId
		{
			int get();
			void set(int value);
		}

		property bool HasFixedBase
		{
			bool get();
		}

		property bool HasSelfCollision
		{
			bool get();
			void set(bool value);
		}

		property bool IsAwake
		{
			bool get();
		}

		property btScalar KineticEnergy
		{
			btScalar get();
		}

		property btScalar LinearDamping
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxAppliedImpulse
		{
			btScalar get();
			void set(btScalar value);
		}

		property int NumLinks
		{
			int get();
			void set(int value);
		}

		property bool UseGyroTerm
		{
			bool get();
			void set(bool value);
		}

		property ScalarArray^ VelocityVector
		{
			ScalarArray^ get();
		}

		property Quaternion WorldToBaseRot
		{
			Quaternion get();
			void set(Quaternion value);
		}
	};
};
