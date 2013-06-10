#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "Solve2LinearConstraint.h"

Solve2LinearConstraint::Solve2LinearConstraint(btSolve2LinearConstraint* constraint)
{
	_native = constraint;
}

Solve2LinearConstraint::Solve2LinearConstraint(btScalar tau, btScalar damping)
{
	_native = new btSolve2LinearConstraint(tau, damping);
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
	VECTOR3_DEF(invInertiaADiag);
	VECTOR3_DEF(linvelA);
	VECTOR3_DEF(angvelA);
	VECTOR3_DEF(rel_posA1);
	VECTOR3_DEF(invInertiaBDiag);
	VECTOR3_DEF(linvelB);
	VECTOR3_DEF(angvelB);
	VECTOR3_DEF(rel_posA2);
	VECTOR3_DEF(normalA);
	VECTOR3_DEF(rel_posB1);
	VECTOR3_DEF(rel_posB2);
	VECTOR3_DEF(normalB);

	_native->resolveBilateralPairConstraint(
		(btRigidBody*)body0->_native, (btRigidBody*)body1->_native, *world2ATemp, *world2BTemp,
		VECTOR3_USE(invInertiaADiag), invMassA, VECTOR3_USE(linvelA), VECTOR3_USE(angvelA), VECTOR3_USE(rel_posA1),
		VECTOR3_USE(invInertiaBDiag), invMassB, VECTOR3_USE(linvelB), VECTOR3_USE(angvelB), VECTOR3_USE(rel_posA2),
		depthA, VECTOR3_USE(normalA), VECTOR3_USE(rel_posB1), VECTOR3_USE(rel_posB2), depthB, VECTOR3_USE(normalB), imp0, imp1
	);

	VECTOR3_DEL(invInertiaADiag);
	VECTOR3_DEL(linvelA);
	VECTOR3_DEL(angvelA);
	VECTOR3_DEL(rel_posA1);
	VECTOR3_DEL(invInertiaBDiag);
	VECTOR3_DEL(linvelB);
	VECTOR3_DEL(angvelB);
	VECTOR3_DEL(rel_posA2);
	VECTOR3_DEL(normalA);
	VECTOR3_DEL(rel_posB1);
	VECTOR3_DEL(rel_posB2);
	VECTOR3_DEL(normalB);
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
	VECTOR3_DEF(invInertiaADiag);
	VECTOR3_DEF(linvelA);
	VECTOR3_DEF(angvelA);
	VECTOR3_DEF(rel_posA1);
	VECTOR3_DEF(invInertiaBDiag);
	VECTOR3_DEF(linvelB);
	VECTOR3_DEF(angvelB);
	VECTOR3_DEF(rel_posA2);
	VECTOR3_DEF(normalA);
	VECTOR3_DEF(rel_posB1);
	VECTOR3_DEF(rel_posB2);
	VECTOR3_DEF(normalB);

	_native->resolveUnilateralPairConstraint(
		(btRigidBody*)body0->_native, (btRigidBody*)body1->_native, *world2ATemp, *world2BTemp,
		VECTOR3_USE(invInertiaADiag), invMassA, VECTOR3_USE(linvelA), VECTOR3_USE(angvelA), VECTOR3_USE(rel_posA1),
		VECTOR3_USE(invInertiaBDiag), invMassB, VECTOR3_USE(linvelB), VECTOR3_USE(angvelB), VECTOR3_USE(rel_posA2),
		depthA, VECTOR3_USE(normalA), VECTOR3_USE(rel_posB1), VECTOR3_USE(rel_posB2), depthB, VECTOR3_USE(normalB), imp0, imp1
	);

	VECTOR3_DEL(invInertiaADiag);
	VECTOR3_DEL(linvelA);
	VECTOR3_DEL(angvelA);
	VECTOR3_DEL(rel_posA1);
	VECTOR3_DEL(invInertiaBDiag);
	VECTOR3_DEL(linvelB);
	VECTOR3_DEL(angvelB);
	VECTOR3_DEL(rel_posA2);
	VECTOR3_DEL(normalA);
	VECTOR3_DEL(rel_posB1);
	VECTOR3_DEL(rel_posB2);
	VECTOR3_DEL(normalB);
}

#endif
