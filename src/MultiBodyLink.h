#pragma once

namespace BulletSharp
{
	ref class ScalarArray;
	ref class MultiBodyLinkCollider;

	public enum FeatherstoneJointType
	{
		Revolute = btMultibodyLink::eRevolute,
		Prismatic = btMultibodyLink::ePrismatic,
		Spherical = btMultibodyLink::eSpherical,
#ifdef BT_MULTIBODYLINK_INCLUDE_PLANAR_JOINTS
		Planar = btMultibodyLink::ePlanar,
#endif
		Invalid = btMultibodyLink::eInvalid
	};

	public ref class MultibodyLink
	{
	internal:
		btMultibodyLink* _native;
		MultibodyLink(btMultibodyLink* native);

	public:
		MultibodyLink();

		Vector3 GetAxisBottom(int dof);
		Vector3 GetAxisTop(int dof);
		void SetAxisBottom(int dof, Vector3 axis);
		void SetAxisBottom(int dof, btScalar x, btScalar y, btScalar z);
		void SetAxisTop(int dof, Vector3 axis);
		void SetAxisTop(int dof, btScalar x, btScalar y, btScalar z);
		void UpdateCache();
		void UpdateCacheMultiDof(ScalarArray^ pq);
		void UpdateCacheMultiDof();

		property Vector3 AppliedForce
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedTorque
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Quaternion CachedRotParentToThis
		{
			Quaternion get();
			void set(Quaternion value);
		}

		property Vector3 CachedRVector
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property int CfgOffset
		{
			int get();
			void set(int value);
		}

		property MultiBodyLinkCollider^ Collider
		{
			MultiBodyLinkCollider^ get();
			void set(MultiBodyLinkCollider^ value);
		}

		property int DofCount
		{
			int get();
			void set(int value);
		}

		property int DofOffset
		{
			int get();
			void set(int value);
		}

		property Vector3 DVector
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 EVector
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property int Flags
		{
			int get();
			void set(int value);
		}

		property Vector3 Inertia
		{
			Vector3 get();
			void set(Vector3 value);
		}
		/*
		property float^ JointPos
		{
			float^ get();
			void set(float^ value);
		}

		property float^ JointTorque
		{
			float^ get();
			void set(float^ value);
		}
		*/
		property FeatherstoneJointType JointType
		{
			FeatherstoneJointType get();
			void set(FeatherstoneJointType value);
		}

		property btScalar Mass
		{
			btScalar get();
			void set(btScalar value);
		}

		property int Parent
		{
			int get();
			void set(int value);
		}

		property int PosVarCount
		{
			int get();
			void set(int value);
		}

		property Quaternion ZeroRotParentToThis
		{
			Quaternion get();
			void set(Quaternion value);
		}
	};
};
