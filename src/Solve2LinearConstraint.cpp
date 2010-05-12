#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "Solve2LinearConstraint.h"

Solve2LinearConstraint::Solve2LinearConstraint(btSolve2LinearConstraint* constraint)
{
	_constraint = constraint;
}

Solve2LinearConstraint::Solve2LinearConstraint(btScalar tau, btScalar damping)
{
	_constraint = new btSolve2LinearConstraint(tau, damping);
}

void Solve2LinearConstraint::ResolveBilateralPairConstraint(
	RigidBody^ body0, RigidBody^ body1, Matrix world2A, Matrix world2B,
	Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA, Vector3 angvelA, Vector3 rel_posA1,
	Vector3 invInertiaBDiag, btScalar invMassB, Vector3 linvelB, Vector3 angvelB, Vector3 rel_posA2,
	btScalar depthA, Vector3 normalA, Vector3 rel_posB1, Vector3 rel_posB2,
	btScalar depthB, Vector3 normalB, btScalar imp0, btScalar imp1)
{
	btMatrix3x3* world2ATemp = Math::MatrixToBtMatrix3x3(world2A);
	btMatrix3x3* world2BTemp = Math::MatrixToBtMatrix3x3(world2B);
	btVector3* invInertiaADiagTemp = Math::Vector3ToBtVector3(invInertiaADiag);
	btVector3* linvelATemp = Math::Vector3ToBtVector3(linvelA);
	btVector3* angvelATemp = Math::Vector3ToBtVector3(angvelA);
	btVector3* rel_posA1Temp = Math::Vector3ToBtVector3(rel_posA1);
	btVector3* invInertiaBDiagTemp = Math::Vector3ToBtVector3(invInertiaBDiag);
	btVector3* linvelBTemp = Math::Vector3ToBtVector3(linvelB);
	btVector3* angvelBTemp = Math::Vector3ToBtVector3(angvelB);
	btVector3* rel_posA2Temp = Math::Vector3ToBtVector3(rel_posA2);
	btVector3* normalATemp = Math::Vector3ToBtVector3(normalA);
	btVector3* rel_posB1Temp = Math::Vector3ToBtVector3(rel_posB1);
	btVector3* rel_posB2Temp = Math::Vector3ToBtVector3(rel_posB2);
	btVector3* normalBTemp = Math::Vector3ToBtVector3(normalB);

	_constraint->resolveBilateralPairConstraint(
		body0->UnmanagedPointer, body1->UnmanagedPointer, *world2ATemp, *world2BTemp,
		*invInertiaADiagTemp, invMassA, *linvelATemp, *angvelATemp, *rel_posA1Temp,
		*invInertiaBDiagTemp, invMassB, *linvelBTemp, *angvelBTemp, *rel_posA2Temp,
		depthA, *normalATemp, *rel_posB1Temp, *rel_posB2Temp, depthB, *normalBTemp, imp0, imp1
	);

	delete world2ATemp;
	delete world2BTemp;
	delete invInertiaADiagTemp;
	delete linvelATemp;
	delete angvelATemp;
	delete rel_posA1Temp;
	delete invInertiaBDiagTemp;
	delete linvelBTemp;
	delete angvelBTemp;
	delete rel_posA2Temp;
	delete normalATemp;
	delete rel_posB1Temp;
	delete rel_posB2Temp;
	delete normalBTemp;
}

void Solve2LinearConstraint::ResolveUnilateralPairConstraint(
	RigidBody^ body0, RigidBody^ body1, Matrix world2A, Matrix world2B,
	Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA, Vector3 angvelA, Vector3 rel_posA1,
	Vector3 invInertiaBDiag, btScalar invMassB, Vector3 linvelB, Vector3 angvelB, Vector3 rel_posA2,
	btScalar depthA, Vector3 normalA, Vector3 rel_posB1, Vector3 rel_posB2,
	btScalar depthB, Vector3 normalB, btScalar imp0, btScalar imp1)
{
	btMatrix3x3* world2ATemp = Math::MatrixToBtMatrix3x3(world2A);
	btMatrix3x3* world2BTemp = Math::MatrixToBtMatrix3x3(world2B);
	btVector3* invInertiaADiagTemp = Math::Vector3ToBtVector3(invInertiaADiag);
	btVector3* linvelATemp = Math::Vector3ToBtVector3(linvelA);
	btVector3* angvelATemp = Math::Vector3ToBtVector3(angvelA);
	btVector3* rel_posA1Temp = Math::Vector3ToBtVector3(rel_posA1);
	btVector3* invInertiaBDiagTemp = Math::Vector3ToBtVector3(invInertiaBDiag);
	btVector3* linvelBTemp = Math::Vector3ToBtVector3(linvelB);
	btVector3* angvelBTemp = Math::Vector3ToBtVector3(angvelB);
	btVector3* rel_posA2Temp = Math::Vector3ToBtVector3(rel_posA2);
	btVector3* normalATemp = Math::Vector3ToBtVector3(normalA);
	btVector3* rel_posB1Temp = Math::Vector3ToBtVector3(rel_posB1);
	btVector3* rel_posB2Temp = Math::Vector3ToBtVector3(rel_posB2);
	btVector3* normalBTemp = Math::Vector3ToBtVector3(normalB);

	_constraint->resolveUnilateralPairConstraint(
		body0->UnmanagedPointer, body1->UnmanagedPointer, *world2ATemp, *world2BTemp,
		*invInertiaADiagTemp, invMassA, *linvelATemp, *angvelATemp, *rel_posA1Temp,
		*invInertiaBDiagTemp, invMassB, *linvelBTemp, *angvelBTemp, *rel_posA2Temp,
		depthA, *normalATemp, *rel_posB1Temp, *rel_posB2Temp, depthB, *normalBTemp, imp0, imp1
	);

	delete world2ATemp;
	delete world2BTemp;
	delete invInertiaADiagTemp;
	delete linvelATemp;
	delete angvelATemp;
	delete rel_posA1Temp;
	delete invInertiaBDiagTemp;
	delete linvelBTemp;
	delete angvelBTemp;
	delete rel_posA2Temp;
	delete normalATemp;
	delete rel_posB1Temp;
	delete rel_posB2Temp;
	delete normalBTemp;
}

btSolve2LinearConstraint* Solve2LinearConstraint::UnmanagedPointer::get()
{
	return _constraint;
}

#endif
