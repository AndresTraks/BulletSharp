#pragma once

namespace BulletSharp
{
	ref class MultiBodyJointFeedback;
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

	public ref class MultiBodyLink
	{
	internal:
		btMultibodyLink* _native;

		MultiBodyLink(btMultibodyLink* native);

	public:
		Vector3 GetAxisBottom(int dof);
		Vector3 GetAxisTop(int dof);
		void SetAxisBottom(int dof, btScalar x, btScalar y, btScalar z);
		void SetAxisBottom(int dof, Vector3 axis);
		void SetAxisTop(int dof, btScalar x, btScalar y, btScalar z);
		void SetAxisTop(int dof, Vector3 axis);
		void UpdateCacheMultiDof(array<btScalar>^ pq);
		void UpdateCacheMultiDof();
/*
		property SpatialMotionVector AbsFrameLocVelocity
		{
			SpatialMotionVector get();
			void set(SpatialMotionVector value);
		}

		property SpatialMotionVector AbsFrameTotVelocity
		{
			SpatialMotionVector get();
			void set(SpatialMotionVector value);
		}
*/
		property Vector3 AppliedConstraintForce
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedConstraintTorque
		{
			Vector3 get();
			void set(Vector3 value);
		}

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
/*
		property SpatialMotionVector^ Axes
		{
			SpatialMotionVector^ get();
		}
*/
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

		property Matrix CachedWorldTransform
		{
			Matrix get();
			void set(Matrix value);
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

		property Vector3 InertiaLocal
		{
			Vector3 get();
			void set(Vector3 value);
		}
		/*
		property MultiBodyJointFeedback^ JointFeedback
		{
			MultiBodyJointFeedback^ get();
			void set(MultiBodyJointFeedback^ value);
		}
		*/
		property String^ JointName
		{
			String^ get();
			//void set(String^ value);
		}
		/*
		property array<btScalar>^ JointPos
		{
			array<btScalar>^ get();
		}

		property array<btScalar>^ JointTorque
		{
			array<btScalar>^ get();
		}
		*/
		property FeatherstoneJointType JointType
		{
			FeatherstoneJointType get();
			void set(FeatherstoneJointType value);
		}

		property String^ LinkName
		{
			String^ get();
			//void set(String^ value);
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
