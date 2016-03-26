#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	[Flags]
	public enum class Point2PointFlags
	{
		None = 0,
		Erp = BT_P2P_FLAGS_ERP,
		Cfm = BT_P2P_FLAGS_CFM
	};

	public ref class ConstraintSetting
	{
	internal:
		btConstraintSetting* _native;

	private:
		bool _preventDelete;

	internal:
		ConstraintSetting(btConstraintSetting* native, bool preventDelete);

		~ConstraintSetting();
		!ConstraintSetting();

	public:
		ConstraintSetting();

		property btScalar Damping
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ImpulseClamp
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Tau
		{
			btScalar get();
			void set(btScalar value);
		}
	};

	public ref class Point2PointConstraint : TypedConstraint
	{
	public:
		Point2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA,
			Vector3 pivotInB);
		Point2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA);

		void GetInfo1NonVirtual(ConstraintInfo1^ info);
		void GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix body0Trans, Matrix body1Trans);
		void UpdateRhs(btScalar timeStep);

		property Point2PointFlags Flags
		{
			Point2PointFlags get();
		}

		property Vector3 PivotInA
		{
			Vector3 get();
			void set(Vector3 pivotA);
		}

		property Vector3 PivotInB
		{
			Vector3 get();
			void set(Vector3 pivotB);
		}

		property ConstraintSetting^ Setting
		{
			ConstraintSetting^ get();
			void set(ConstraintSetting^ value);
		}
	};
};
