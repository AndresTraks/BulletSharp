#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "Solve2LinearConstraint.h"

Solve2LinearConstraint::Solve2LinearConstraint(btSolve2LinearConstraint* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

Solve2LinearConstraint::~Solve2LinearConstraint()
{
	this->!Solve2LinearConstraint();
}

Solve2LinearConstraint::!Solve2LinearConstraint()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

Solve2LinearConstraint::Solve2LinearConstraint(btScalar tau, btScalar damping)
{
	_native = new btSolve2LinearConstraint(tau, damping);
}

void Solve2LinearConstraint::ResolveBilateralPairConstraint(RigidBody^ body0, RigidBody^ body1,
	Matrix world2A, Matrix world2B, Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA,
	Vector3 angvelA, Vector3 relPosA1, Vector3 invInertiaBDiag, btScalar invMassB,
	Vector3 linvelB, Vector3 angvelB, Vector3 relPosA2, btScalar depthA, Vector3 normalA,
	Vector3 relPosB1, Vector3 relPosB2, btScalar depthB, Vector3 normalB, [Out] btScalar% imp0,
	[Out] btScalar% imp1)
{
	MATRIX3X3_CONV(world2A);
	MATRIX3X3_CONV(world2B);
	VECTOR3_CONV(invInertiaADiag);
	VECTOR3_CONV(linvelA);
	VECTOR3_CONV(angvelA);
	VECTOR3_CONV(relPosA1);
	VECTOR3_CONV(invInertiaBDiag);
	VECTOR3_CONV(linvelB);
	VECTOR3_CONV(angvelB);
	VECTOR3_CONV(relPosA2);
	VECTOR3_CONV(normalA);
	VECTOR3_CONV(relPosB1);
	VECTOR3_CONV(relPosB2);
	VECTOR3_CONV(normalB);
	btScalar imp0Temp;
	btScalar imp1Temp;
	_native->resolveBilateralPairConstraint((btRigidBody*)body0->_native, (btRigidBody*)body1->_native,
		MATRIX3X3_USE(world2A), MATRIX3X3_USE(world2B), VECTOR3_USE(invInertiaADiag),
		invMassA, VECTOR3_USE(linvelA), VECTOR3_USE(angvelA), VECTOR3_USE(relPosA1),
		VECTOR3_USE(invInertiaBDiag), invMassB, VECTOR3_USE(linvelB), VECTOR3_USE(angvelB),
		VECTOR3_USE(relPosA2), depthA, VECTOR3_USE(normalA), VECTOR3_USE(relPosB1),
		VECTOR3_USE(relPosB2), depthB, VECTOR3_USE(normalB), imp0Temp, imp1Temp);
	MATRIX3X3_DEL(world2A);
	MATRIX3X3_DEL(world2B);
	VECTOR3_DEL(invInertiaADiag);
	VECTOR3_DEL(linvelA);
	VECTOR3_DEL(angvelA);
	VECTOR3_DEL(relPosA1);
	VECTOR3_DEL(invInertiaBDiag);
	VECTOR3_DEL(linvelB);
	VECTOR3_DEL(angvelB);
	VECTOR3_DEL(relPosA2);
	VECTOR3_DEL(normalA);
	VECTOR3_DEL(relPosB1);
	VECTOR3_DEL(relPosB2);
	VECTOR3_DEL(normalB);
	imp0 = imp0Temp;
	imp1 = imp1Temp;
}

void Solve2LinearConstraint::ResolveUnilateralPairConstraint(RigidBody^ body0, RigidBody^ body1,
	Matrix world2A, Matrix world2B, Vector3 invInertiaADiag, btScalar invMassA, Vector3 linvelA,
	Vector3 angvelA, Vector3 relPosA1, Vector3 invInertiaBDiag, btScalar invMassB,
	Vector3 linvelB, Vector3 angvelB, Vector3 relPosA2, btScalar depthA, Vector3 normalA,
	Vector3 relPosB1, Vector3 relPosB2, btScalar depthB, Vector3 normalB, [Out] btScalar% imp0,
	[Out] btScalar% imp1)
{
	MATRIX3X3_CONV(world2A);
	MATRIX3X3_CONV(world2B);
	VECTOR3_CONV(invInertiaADiag);
	VECTOR3_CONV(linvelA);
	VECTOR3_CONV(angvelA);
	VECTOR3_CONV(relPosA1);
	VECTOR3_CONV(invInertiaBDiag);
	VECTOR3_CONV(linvelB);
	VECTOR3_CONV(angvelB);
	VECTOR3_CONV(relPosA2);
	VECTOR3_CONV(normalA);
	VECTOR3_CONV(relPosB1);
	VECTOR3_CONV(relPosB2);
	VECTOR3_CONV(normalB);
	btScalar imp0Temp;
	btScalar imp1Temp;
	_native->resolveUnilateralPairConstraint((btRigidBody*)body0->_native, (btRigidBody*)body1->_native,
		MATRIX3X3_USE(world2A), MATRIX3X3_USE(world2B), VECTOR3_USE(invInertiaADiag),
		invMassA, VECTOR3_USE(linvelA), VECTOR3_USE(angvelA), VECTOR3_USE(relPosA1),
		VECTOR3_USE(invInertiaBDiag), invMassB, VECTOR3_USE(linvelB), VECTOR3_USE(angvelB),
		VECTOR3_USE(relPosA2), depthA, VECTOR3_USE(normalA), VECTOR3_USE(relPosB1),
		VECTOR3_USE(relPosB2), depthB, VECTOR3_USE(normalB), imp0Temp, imp1Temp);
	MATRIX3X3_DEL(world2A);
	MATRIX3X3_DEL(world2B);
	VECTOR3_DEL(invInertiaADiag);
	VECTOR3_DEL(linvelA);
	VECTOR3_DEL(angvelA);
	VECTOR3_DEL(relPosA1);
	VECTOR3_DEL(invInertiaBDiag);
	VECTOR3_DEL(linvelB);
	VECTOR3_DEL(angvelB);
	VECTOR3_DEL(relPosA2);
	VECTOR3_DEL(normalA);
	VECTOR3_DEL(relPosB1);
	VECTOR3_DEL(relPosB2);
	VECTOR3_DEL(normalB);
	imp0 = imp0Temp;
	imp1 = imp1Temp;
}

#endif
