#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class ConstraintSetting : IDisposable
	{
	internal:
		btConstraintSetting* _native;
		ConstraintSetting(btConstraintSetting* native, bool preventDelete);

	private:
		bool _preventDelete;

	public:
		!ConstraintSetting();
	protected:
		~ConstraintSetting();

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
	private:
		RigidBody^ _rigidBodyA;
		RigidBody^ _rigidBodyB;

	internal:
		Point2PointConstraint(btPoint2PointConstraint* native);

	public:
		Point2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA, Vector3 pivotInB);
		Point2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA);

		void GetInfo1NonVirtual(ConstraintInfo1^ info);
		void GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix body0Trans, Matrix body1Trans);
		void UpdateRhs(btScalar timeStep);

		property Vector3 PivotInA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 PivotInB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property ConstraintSetting^ Setting
		{
			ConstraintSetting^ get();
			void set(ConstraintSetting^ value);
		}
	};
};
