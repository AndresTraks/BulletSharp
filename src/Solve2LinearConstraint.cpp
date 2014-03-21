#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "Solve2LinearConstraint.h"

Solve2LinearConstraint::Solve2LinearConstraint(btSolve2LinearConstraint* native)
{
	_native = native;
}

Solve2LinearConstraint::Solve2LinearConstraint(btScalar tau, btScalar damping)
{
	_native = new btSolve2LinearConstraint(tau, damping);
}

void Solve2LinearConstraint::ResolveBilateralPairConstraint(RigidBody^ body0, RigidBody^ body1,
	Matrix world2A, Matrix world2B, Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA,
	Vector3 angvelA, Vector3 rel_posA1, Vector3 invInertiaBDiag, btScalar invMassB,
	Vector3 linvelB, Vector3 angvelB, Vector3 rel_posA2, btScalar depthA, Vector3 normalA,
	Vector3 rel_posB1, Vector3 rel_posB2, btScalar depthB, Vector3 normalB, [Out] btScalar% imp0,
	[Out] btScalar% imp1)
{
	MATRIX3X3_CONV(world2A);
	MATRIX3X3_CONV(world2B);
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
	btScalar imp0Temp;
	btScalar imp1Temp;
	_native->resolveBilateralPairConstraint((btRigidBody*)body0->_native, (btRigidBody*)body1->_native,
		MATRIX3X3_USE(world2A), MATRIX3X3_USE(world2B), VECTOR3_USE(invInertiaADiag),
		invMassA, VECTOR3_USE(linvelA), VECTOR3_USE(angvelA), VECTOR3_USE(rel_posA1),
		VECTOR3_USE(invInertiaBDiag), invMassB, VECTOR3_USE(linvelB), VECTOR3_USE(angvelB),
		VECTOR3_USE(rel_posA2), depthA, VECTOR3_USE(normalA), VECTOR3_USE(rel_posB1),
		VECTOR3_USE(rel_posB2), depthB, VECTOR3_USE(normalB), imp0Temp, imp1Temp);
	imp0 = imp0Temp;
	imp1 = imp1Temp;
	MATRIX3X3_DEL(world2A);
	MATRIX3X3_DEL(world2B);
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

void Solve2LinearConstraint::ResolveUnilateralPairConstraint(RigidBody^ body0, RigidBody^ body1,
	Matrix world2A, Matrix world2B, Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA,
	Vector3 angvelA, Vector3 rel_posA1, Vector3 invInertiaBDiag, btScalar invMassB,
	Vector3 linvelB, Vector3 angvelB, Vector3 rel_posA2, btScalar depthA, Vector3 normalA,
	Vector3 rel_posB1, Vector3 rel_posB2, btScalar depthB, Vector3 normalB, [Out] btScalar% imp0,
	[Out] btScalar% imp1)
{
	MATRIX3X3_CONV(world2A);
	MATRIX3X3_CONV(world2B);
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
	btScalar imp0Temp;
	btScalar imp1Temp;
	_native->resolveUnilateralPairConstraint((btRigidBody*)body0->_native, (btRigidBody*)body1->_native,
		MATRIX3X3_USE(world2A), MATRIX3X3_USE(world2B), VECTOR3_USE(invInertiaADiag),
		invMassA, VECTOR3_USE(linvelA), VECTOR3_USE(angvelA), VECTOR3_USE(rel_posA1),
		VECTOR3_USE(invInertiaBDiag), invMassB, VECTOR3_USE(linvelB), VECTOR3_USE(angvelB),
		VECTOR3_USE(rel_posA2), depthA, VECTOR3_USE(normalA), VECTOR3_USE(rel_posB1),
		VECTOR3_USE(rel_posB2), depthB, VECTOR3_USE(normalB), imp0Temp, imp1Temp);
	imp0 = imp0Temp;
	imp1 = imp1Temp;
	MATRIX3X3_DEL(world2A);
	MATRIX3X3_DEL(world2B);
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
