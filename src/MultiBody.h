#pragma once

namespace BulletSharp
{
	ref class AlignedScalarArray;
	ref class AlignedVector3Array;
	ref class MultiBodyLink;
	ref class MultiBodyLinkCollider;
	ref class ScalarArray;
	ref class Serializer;

	public ref class MultiBody
	{
	internal:
		btMultiBody* _native;

	private:
		array<MultiBodyLink^>^ _links;

	internal:
		MultiBody(btMultiBody* native);

		~MultiBody();
		!MultiBody();

	public:
		MultiBody(int nLinks, btScalar mass, Vector3 inertia, bool fixedBase, bool canSleep);

		void AddBaseConstraintForce(Vector3 f);
		void AddBaseConstraintTorque(Vector3 t);
		void AddBaseForce(Vector3 f);
		void AddBaseTorque(Vector3 t);
		void AddJointTorque(int i, btScalar q);
		void AddJointTorqueMultiDof(int i, array<btScalar>^ q);
		void AddJointTorqueMultiDof(int i, int dof, btScalar q);
		void AddLinkConstraintForce(int i, Vector3 f);
		void AddLinkConstraintTorque(int i, Vector3 t);
		void AddLinkForce(int i, Vector3 f);
		void AddLinkTorque(int i, Vector3 t);
		void ApplyDeltaVeeMultiDof(array<btScalar>^ deltaVee, btScalar multiplier);
		void ApplyDeltaVeeMultiDof2(array<btScalar>^ deltaVee, btScalar multiplier);
		void CalcAccelerationDeltasMultiDof(array<btScalar>^ force, array<btScalar>^ output,
			AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV);
		int CalculateSerializeBufferSize();
		void CheckMotionAndSleepIfRequired(btScalar timestep);
		void ClearConstraintForces();
		void ClearForcesAndTorques();
		void ClearVelocities();
		/*void ComputeAccelerationsArticulatedBodyAlgorithmMultiDof(btScalar deltaTime,
			AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV, AlignedMatrix3x3Array^ scratchM,
			bool isConstraintPass);
		void ComputeAccelerationsArticulatedBodyAlgorithmMultiDof(btScalar deltaTime,
			AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV, AlignedMatrix3x3Array^ scratchM);
		void FillConstraintJacobianMultiDof(int link, Vector3 contactPoint, Vector3 normalAng,
			Vector3 normalLin, array<btScalar>^ jac, AlignedScalarArray^ scratchR,
			AlignedVector3Array^ scratchV, AlignedMatrix3x3Array^ scratchM);
		void FillContactJacobianMultiDof(int link, Vector3 contactPoint, Vector3 normal,
			array<btScalar>^ jac, AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV,
			AlignedMatrix3x3Array^ scratchM);*/
		void FinalizeMultiDof();
		//void ForwardKinematics(AlignedQuaternionArray^ scratchQ, AlignedVector3Array^ scratchM);
		btScalar GetJointPos(int i);
		//array<btScalar>^ GetJointPosMultiDof(int i);
		btScalar GetJointTorque(int i);
		//array<btScalar>^ GetJointTorqueMultiDof(int i);
		btScalar GetJointVel(int i);
		//array<btScalar>^ GetJointVelMultiDof(int i);
		MultiBodyLink^ GetLink(int index);
		Vector3 GetLinkForce(int i);
		Vector3 GetLinkInertia(int i);
		btScalar GetLinkMass(int i);
		Vector3 GetLinkTorque(int i);
		int GetParent(int linkNum);
		Quaternion GetParentToLocalRot(int i);
		Vector3 GetRVector(int i);
		void GoToSleep();
		bool InternalNeedsJointFeedback();
		Vector3 LocalDirToWorld(int i, Vector3 vec);
		Vector3 LocalPosToWorld(int i, Vector3 vec);
		void ProcessDeltaVeeMultiDof2();
#ifndef DISABLE_SERIALIZE
		String^ Serialize(IntPtr dataBuffer, Serializer^ serializer);
#endif
		void SetJointPos(int i, btScalar q);
		void SetJointPosMultiDof(int i, array<btScalar>^ q);
		void SetJointVel(int i, btScalar qdot);
		void SetJointVelMultiDof(int i, array<btScalar>^ qdot);
		void SetPosUpdated(bool updated);
		void SetupFixed(int linkIndex, btScalar mass, Vector3 inertia, int parent,
			Quaternion rotParentToThis, Vector3 parentComToThisPivotOffset, Vector3 thisPivotToThisComOffset);
		void SetupPlanar(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis,
			Vector3 rotationAxis, Vector3 parentComToThisComOffset, bool disableParentCollision);
		void SetupPlanar(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis,
			Vector3 rotationAxis, Vector3 parentComToThisComOffset);
		void SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis,
			Vector3 jointAxis, Vector3 parentComToThisPivotOffset, Vector3 thisPivotToThisComOffset,
			bool disableParentCollision);
		void SetupRevolute(int linkIndex, btScalar mass, Vector3 inertia, int parentIndex,
			Quaternion rotParentToThis, Vector3 jointAxis, Vector3 parentComToThisPivotOffset,
			Vector3 thisPivotToThisComOffset, bool disableParentCollision);
		void SetupRevolute(int linkIndex, btScalar mass, Vector3 inertia, int parentIndex,
			Quaternion rotParentToThis, Vector3 jointAxis, Vector3 parentComToThisPivotOffset,
			Vector3 thisPivotToThisComOffset);
		void SetupSpherical(int linkIndex, btScalar mass, Vector3 inertia, int parent,
			Quaternion rotParentToThis, Vector3 parentComToThisPivotOffset, Vector3 thisPivotToThisComOffset,
			bool disableParentCollision);
		void SetupSpherical(int linkIndex, btScalar mass, Vector3 inertia, int parent,
			Quaternion rotParentToThis, Vector3 parentComToThisPivotOffset, Vector3 thisPivotToThisComOffset);
		void StepPositionsMultiDof(btScalar deltaTime, array<btScalar>^ pq, array<btScalar>^ pqd);
		void StepPositionsMultiDof(btScalar deltaTime, array<btScalar>^ pq);
		void StepPositionsMultiDof(btScalar deltaTime);
		//void UpdateCollisionObjectWorldTransforms(AlignedQuaternionArray^ scratchQ, AlignedVector3Array^ scratchM);
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

		property String^ BaseName
		{
			String^ get();
			//void set(String^ name);
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
		/*
		property Matrix BaseWorldTransform
		{
			Matrix get();
			void set(Matrix tr);
		}
		*/
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
