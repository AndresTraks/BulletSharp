#pragma once

namespace BulletSharp
{
	ref class RigidBody;

	public ref class Solve2LinearConstraint
	{
	internal:
		btSolve2LinearConstraint* _native;

	private:
		bool _preventDelete;

	internal:
		Solve2LinearConstraint(btSolve2LinearConstraint* native, bool preventDelete);

		~Solve2LinearConstraint();
		!Solve2LinearConstraint();

	public:
		Solve2LinearConstraint(btScalar tau, btScalar damping);

		void ResolveBilateralPairConstraint(RigidBody^ body0, RigidBody^ body1, Matrix world2A,
			Matrix world2B, Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA,
			Vector3 angvelA, Vector3 relPosA1, Vector3 invInertiaBDiag, btScalar invMassB,
			Vector3 linvelB, Vector3 angvelB, Vector3 relPosA2, btScalar depthA, Vector3 normalA,
			Vector3 relPosB1, Vector3 relPosB2, btScalar depthB, Vector3 normalB, [Out] btScalar% imp0,
			[Out] btScalar% imp1);
		void ResolveUnilateralPairConstraint(RigidBody^ body0, RigidBody^ body1,
			Matrix world2A, Matrix world2B, Vector3 invInertiaADiag, btScalar invMassA,
			Vector3 linvelA, Vector3 angvelA, Vector3 relPosA1, Vector3 invInertiaBDiag,
			btScalar invMassB, Vector3 linvelB, Vector3 angvelB, Vector3 relPosA2,
			btScalar depthA, Vector3 normalA, Vector3 relPosB1, Vector3 relPosB2, btScalar depthB,
			Vector3 normalB, [Out] btScalar% imp0, [Out] btScalar% imp1);
	};
};
