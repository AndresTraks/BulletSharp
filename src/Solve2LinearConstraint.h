#pragma once

// Fully implemented as of 23 Nov 2010

namespace BulletSharp
{
	ref class RigidBody;

	public ref class Solve2LinearConstraint
	{
	private:
		btSolve2LinearConstraint* _constraint;

	internal:
		Solve2LinearConstraint(btSolve2LinearConstraint* constraint);

	public:
		Solve2LinearConstraint(btScalar tau, btScalar damping);

		void ResolveBilateralPairConstraint(RigidBody^ body0, RigidBody^ body1, Matrix world2A, Matrix world2B,
			Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA, Vector3 angvelA, Vector3 rel_posA1,
			Vector3 invInertiaBDiag, btScalar invMassB, Vector3 linvelB, Vector3 angvelB, Vector3 rel_posA2,
			btScalar depthA, Vector3 normalA, Vector3 rel_posB1, Vector3 rel_posB2,
			btScalar depthB, Vector3 normalB, btScalar imp0, btScalar imp1);

		void ResolveUnilateralPairConstraint(RigidBody^ body0, RigidBody^ body1, Matrix world2A, Matrix world2B,
			Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA, Vector3 angvelA, Vector3 rel_posA1,
			Vector3 invInertiaBDiag, btScalar invMassB, Vector3 linvelB, Vector3 angvelB, Vector3 rel_posA2,
			btScalar depthA, Vector3 normalA, Vector3 rel_posB1, Vector3 rel_posB2,
			btScalar depthB, Vector3 normalB, btScalar imp0, btScalar imp1);

	internal:
		property btSolve2LinearConstraint* UnmanagedPointer
		{
			virtual btSolve2LinearConstraint* get();
		}
	};
};
