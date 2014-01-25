#pragma once

namespace BulletSharp
{
	ref class MultiBodyLinkCollider;

	public ref class MultibodyLink
	{
	internal:
		btMultibodyLink* _native;
		MultibodyLink(btMultibodyLink* native);

	public:
		MultibodyLink();

		void UpdateCache();

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
		property Vector3 AxesBottom
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AxesTop
		{
			Vector3 get();
			void set(Vector3 value);
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

		property MultiBodyLinkCollider^ Collider
		{
			MultiBodyLinkCollider^ get();
			void set(MultiBodyLinkCollider^ value);
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
		property float JointPos
		{
			float get();
			void set(float value);
		}
		
		property float JointTorque
		{
			float get();
			void set(float value);
		}
		*/
		property float Mass
		{
			float get();
			void set(float value);
		}

		property int Parent
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
