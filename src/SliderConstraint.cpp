#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "SliderConstraint.h"

#define Native static_cast<btSliderConstraint*>(_native)

SliderConstraint::SliderConstraint(btSliderConstraint* constraint)
: TypedConstraint(constraint)
{
}

SliderConstraint::SliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btSliderConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA);

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);
}

SliderConstraint::SliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);
	UnmanagedPointer = new btSliderConstraint(*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameA);
	ALIGNED_FREE(frameInBTemp);
}

void SliderConstraint::CalculateTransforms(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	Native->calculateTransforms(*transATemp, *transBTemp);

	ALIGNED_FREE(transATemp);
	ALIGNED_FREE(transBTemp);
}

void SliderConstraint::SetFrames(Matrix frameA, Matrix frameB)
{
	btTransform* frameATemp = Math::MatrixToBtTransform(frameA);
	btTransform* frameBTemp = Math::MatrixToBtTransform(frameB);

	Native->setFrames(*frameATemp, *frameBTemp);

	ALIGNED_FREE(frameBTemp);
	ALIGNED_FREE(frameATemp);
}

void SliderConstraint::TestAngularLimits()
{
	Native->testAngLimits();
}

void SliderConstraint::TestLinLimits()
{
	Native->testLinLimits();
}

#pragma managed(push, off)
void SliderConstraint_GetAnchorInA(btSliderConstraint* constraint, btVector3* anchorInA)
{
	//TYPO:
	//*anchorInA = constraint->getAnchorInA();
	*anchorInA = constraint->getAncorInA();
}
#pragma managed(pop)
Vector3 SliderConstraint::AnchorInA::get()
{
	btVector3* anchorInATemp = new btVector3;
	SliderConstraint_GetAnchorInA(Native, anchorInATemp);
	Vector3 anchor = Math::BtVector3ToVector3(anchorInATemp);
	delete anchorInATemp;
	return anchor;
}

#pragma managed(push, off)
void SliderConstraint_GetAnchorInB(btSliderConstraint* constraint, btVector3* anchorInB)
{
	//TYPO:
	//*anchorInB = constraint->getAnchorInB();
	*anchorInB = constraint->getAncorInB();
}
#pragma managed(pop)
Vector3 SliderConstraint::AnchorInB::get()
{
	btVector3* anchorInBTemp = new btVector3;
	SliderConstraint_GetAnchorInB(Native, anchorInBTemp);
	Vector3 anchor = Math::BtVector3ToVector3(anchorInBTemp);
	delete anchorInBTemp;
	return anchor;
}

btScalar SliderConstraint::AngularDepth::get()
{
	return Native->getAngDepth();
}

btScalar SliderConstraint::AngularPos::get()
{
	return Native->getAngularPos();
}

Matrix SliderConstraint::CalculatedTransformA::get()
{
	return Math::BtTransformToMatrix(&Native->getCalculatedTransformA());
}

Matrix SliderConstraint::CalculatedTransformB::get()
{
	return Math::BtTransformToMatrix(&Native->getCalculatedTransformB());
}

btScalar SliderConstraint::DampingDirAngular::get()
{
	return Native->getDampingDirAng();
}
void SliderConstraint::DampingDirAngular::set(btScalar value)
{
	Native->setDampingDirAng(value);
}

btScalar SliderConstraint::DampingDirLin::get()
{
	return Native->getDampingDirLin();
}
void SliderConstraint::DampingDirLin::set(btScalar value)
{
	Native->setDampingDirLin(value);
}

btScalar SliderConstraint::DampingLimAngular::get()
{
	return Native->getDampingLimAng();
}
void SliderConstraint::DampingLimAngular::set(btScalar value)
{
	Native->setDampingLimAng(value);
}

btScalar SliderConstraint::DampingLimLin::get()
{
	return Native->getDampingLimLin();
}
void SliderConstraint::DampingLimLin::set(btScalar value)
{
	Native->setDampingLimLin(value);
}

btScalar SliderConstraint::DampingOrthoAngular::get()
{
	return Native->getDampingOrthoAng();
}
void SliderConstraint::DampingOrthoAngular::set(btScalar value)
{
	Native->setDampingOrthoAng(value);
}

btScalar SliderConstraint::DampingOrthoLin::get()
{
	return Native->getDampingOrthoLin();
}
void SliderConstraint::DampingOrthoLin::set(btScalar value)
{
	Native->setDampingOrthoLin(value);
}

Matrix SliderConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetA());
}

Matrix SliderConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetB());
}

btScalar SliderConstraint::LinDepth::get()
{
	return Native->getLinDepth();
}

btScalar SliderConstraint::LinearPos::get()
{
	return Native->getLinearPos();
}

btScalar SliderConstraint::LowerAngularLimit::get()
{
	return Native->getLowerAngLimit();
}
void SliderConstraint::LowerAngularLimit::set(btScalar value)
{
	Native->setLowerAngLimit(value);
}

btScalar SliderConstraint::LowerLinLimit::get()
{
	return Native->getLowerLinLimit();
}
void SliderConstraint::LowerLinLimit::set(btScalar value)
{
	Native->setLowerLinLimit(value);
}

btScalar SliderConstraint::MaxAngularMotorForce::get()
{
	return Native->getMaxAngMotorForce();
}
void SliderConstraint::MaxAngularMotorForce::set(btScalar value)
{
	Native->setMaxAngMotorForce(value);
}

btScalar SliderConstraint::MaxLinMotorForce::get()
{
	return Native->getMaxLinMotorForce();
}
void SliderConstraint::MaxLinMotorForce::set(btScalar value)
{
	Native->setMaxLinMotorForce(value);
}

bool SliderConstraint::PoweredAngularMotor::get()
{
	return Native->getPoweredAngMotor();
}
void SliderConstraint::PoweredAngularMotor::set(bool value)
{
	Native->setPoweredAngMotor(value);
}

bool SliderConstraint::PoweredLinMotor::get()
{
	return Native->getPoweredLinMotor();
}
void SliderConstraint::PoweredLinMotor::set(bool value)
{
	Native->setPoweredLinMotor(value);
}

btScalar SliderConstraint::RestitutionDirAngular::get()
{
	return Native->getRestitutionDirAng();
}
void SliderConstraint::RestitutionDirAngular::set(btScalar value)
{
	Native->setRestitutionDirAng(value);
}

btScalar SliderConstraint::RestitutionDirLin::get()
{
	return Native->getRestitutionDirLin();
}
void SliderConstraint::RestitutionDirLin::set(btScalar value)
{
	Native->setRestitutionDirLin(value);
}

btScalar SliderConstraint::RestitutionLimAngular::get()
{
	return Native->getRestitutionLimAng();
}
void SliderConstraint::RestitutionLimAngular::set(btScalar value)
{
	Native->setRestitutionLimAng(value);
}

btScalar SliderConstraint::RestitutionLimLin::get()
{
	return Native->getRestitutionLimLin();
}
void SliderConstraint::RestitutionLimLin::set(btScalar value)
{
	Native->setRestitutionLimLin(value);
}

btScalar SliderConstraint::RestitutionOrthoAngular::get()
{
	return Native->getRestitutionOrthoAng();
}
void SliderConstraint::RestitutionOrthoAngular::set(btScalar value)
{
	Native->setRestitutionOrthoAng(value);
}

btScalar SliderConstraint::RestitutionOrthoLin::get()
{
	return Native->getRestitutionOrthoLin();
}
void SliderConstraint::RestitutionOrthoLin::set(btScalar value)
{
	Native->setRestitutionOrthoLin(value);
}

btScalar SliderConstraint::SoftnessDirAngular::get()
{
	return Native->getSoftnessDirAng();
}
void SliderConstraint::SoftnessDirAngular::set(btScalar value)
{
	Native->setSoftnessDirAng(value);
}

btScalar SliderConstraint::SoftnessDirLin::get()
{
	return Native->getSoftnessDirLin();
}
void SliderConstraint::SoftnessDirLin::set(btScalar value)
{
	Native->setSoftnessDirLin(value);
}

btScalar SliderConstraint::SoftnessLimAngular::get()
{
	return Native->getSoftnessLimAng();
}
void SliderConstraint::SoftnessLimAngular::set(btScalar value)
{
	Native->setSoftnessLimAng(value);
}

btScalar SliderConstraint::SoftnessLimLin::get()
{
	return Native->getSoftnessLimLin();
}
void SliderConstraint::SoftnessLimLin::set(btScalar value)
{
	Native->setSoftnessLimLin(value);
}

btScalar SliderConstraint::SoftnessOrthoAngular::get()
{
	return Native->getSoftnessOrthoAng();
}
void SliderConstraint::SoftnessOrthoAngular::set(btScalar value)
{
	Native->setSoftnessOrthoAng(value);
}

btScalar SliderConstraint::SoftnessOrthoLin::get()
{
	return Native->getSoftnessOrthoLin();
}
void SliderConstraint::SoftnessOrthoLin::set(btScalar value)
{
	Native->setSoftnessOrthoLin(value);
}

bool SliderConstraint::SolveAngularLimit::get()
{
	return Native->getSolveAngLimit();
}

bool SliderConstraint::SolveLinLimit::get()
{
	return Native->getSolveLinLimit();
}

btScalar SliderConstraint::TargetAngularMotorVelocity::get()
{
	return Native->getTargetAngMotorVelocity();
}
void SliderConstraint::TargetAngularMotorVelocity::set(btScalar value)
{
	Native->setTargetAngMotorVelocity(value);
}

btScalar SliderConstraint::TargetLinMotorVelocity::get()
{
	return Native->getTargetLinMotorVelocity();
}
void SliderConstraint::TargetLinMotorVelocity::set(btScalar value)
{
	Native->setTargetLinMotorVelocity(value);
}

btScalar SliderConstraint::UpperAngularLimit::get()
{
	return Native->getUpperAngLimit();
}
void SliderConstraint::UpperAngularLimit::set(btScalar value)
{
	Native->setUpperAngLimit(value);
}

btScalar SliderConstraint::UpperLinLimit::get()
{
	return Native->getUpperLinLimit();
}
void SliderConstraint::UpperLinLimit::set(btScalar value)
{
	Native->setUpperLinLimit(value);
}

bool SliderConstraint::UseFrameOffset::get()
{
	return Native->getUseFrameOffset();
}
void SliderConstraint::UseFrameOffset::set(bool value)
{
	Native->setUseFrameOffset(value);
}

bool SliderConstraint::UseLinearReferenceFrameA::get()
{
	return Native->getUseLinearReferenceFrameA();
}

#endif
