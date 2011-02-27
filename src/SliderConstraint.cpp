#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "SliderConstraint.h"

SliderConstraint::SliderConstraint(btSliderConstraint* constraint)
: TypedConstraint(constraint)
{
}

SliderConstraint::SliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btSliderConstraint(*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA);

	delete frameInATemp;
	delete frameInBTemp;
}

SliderConstraint::SliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btSliderConstraint(*rigidBodyB->UnmanagedPointer, *frameInBTemp, useLinearReferenceFrameA);

	delete frameInBTemp;
}

void SliderConstraint::CalculateTransforms(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	UnmanagedPointer->calculateTransforms(*transATemp, *transBTemp);

	delete transATemp;
	delete transBTemp;
}

void SliderConstraint::SetFrames(Matrix frameA, Matrix frameB)
{
	btTransform* frameATemp = Math::MatrixToBtTransform(frameA);
	btTransform* frameBTemp = Math::MatrixToBtTransform(frameB);

	UnmanagedPointer->setFrames(*frameATemp, *frameBTemp);

	delete frameBTemp;
	delete frameATemp;
}

void SliderConstraint::TestAngularLimits()
{
	UnmanagedPointer->testAngLimits();
}

void SliderConstraint::TestLinLimits()
{
	UnmanagedPointer->testLinLimits();
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
	SliderConstraint_GetAnchorInA(UnmanagedPointer, anchorInATemp);
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
	SliderConstraint_GetAnchorInB(UnmanagedPointer, anchorInBTemp);
	Vector3 anchor = Math::BtVector3ToVector3(anchorInBTemp);
	delete anchorInBTemp;
	return anchor;
}

btScalar SliderConstraint::AngularDepth::get()
{
	return UnmanagedPointer->getAngDepth();
}

Matrix SliderConstraint::CalculatedTransformA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getCalculatedTransformA());
}

Matrix SliderConstraint::CalculatedTransformB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getCalculatedTransformB());
}

btScalar SliderConstraint::DampingDirAngular::get()
{
	return UnmanagedPointer->getDampingDirAng();
}
void SliderConstraint::DampingDirAngular::set(btScalar value)
{
	UnmanagedPointer->setDampingDirAng(value);
}

btScalar SliderConstraint::DampingDirLin::get()
{
	return UnmanagedPointer->getDampingDirLin();
}
void SliderConstraint::DampingDirLin::set(btScalar value)
{
	UnmanagedPointer->setDampingDirLin(value);
}

btScalar SliderConstraint::DampingLimAngular::get()
{
	return UnmanagedPointer->getDampingLimAng();
}
void SliderConstraint::DampingLimAngular::set(btScalar value)
{
	UnmanagedPointer->setDampingLimAng(value);
}

btScalar SliderConstraint::DampingLimLin::get()
{
	return UnmanagedPointer->getDampingLimLin();
}
void SliderConstraint::DampingLimLin::set(btScalar value)
{
	UnmanagedPointer->setDampingLimLin(value);
}

btScalar SliderConstraint::DampingOrthoAngular::get()
{
	return UnmanagedPointer->getDampingOrthoAng();
}
void SliderConstraint::DampingOrthoAngular::set(btScalar value)
{
	UnmanagedPointer->setDampingOrthoAng(value);
}

btScalar SliderConstraint::DampingOrthoLin::get()
{
	return UnmanagedPointer->getDampingOrthoLin();
}
void SliderConstraint::DampingOrthoLin::set(btScalar value)
{
	UnmanagedPointer->setDampingOrthoLin(value);
}

Matrix SliderConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetA());
}

Matrix SliderConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetB());
}

btScalar SliderConstraint::LinDepth::get()
{
	return UnmanagedPointer->getLinDepth();
}

btScalar SliderConstraint::LinearPos::get()
{
	return UnmanagedPointer->getLinearPos();
}

btScalar SliderConstraint::LowerAngularLimit::get()
{
	return UnmanagedPointer->getLowerAngLimit();
}
void SliderConstraint::LowerAngularLimit::set(btScalar value)
{
	UnmanagedPointer->setLowerAngLimit(value);
}

btScalar SliderConstraint::LowerLinLimit::get()
{
	return UnmanagedPointer->getLowerLinLimit();
}
void SliderConstraint::LowerLinLimit::set(btScalar value)
{
	UnmanagedPointer->setLowerLinLimit(value);
}

btScalar SliderConstraint::MaxAngularMotorForce::get()
{
	return UnmanagedPointer->getMaxAngMotorForce();
}
void SliderConstraint::MaxAngularMotorForce::set(btScalar value)
{
	UnmanagedPointer->setMaxAngMotorForce(value);
}

btScalar SliderConstraint::MaxLinMotorForce::get()
{
	return UnmanagedPointer->getMaxLinMotorForce();
}
void SliderConstraint::MaxLinMotorForce::set(btScalar value)
{
	UnmanagedPointer->setMaxLinMotorForce(value);
}

bool SliderConstraint::PoweredAngularMotor::get()
{
	return UnmanagedPointer->getPoweredAngMotor();
}
void SliderConstraint::PoweredAngularMotor::set(bool value)
{
	UnmanagedPointer->setPoweredAngMotor(value);
}

bool SliderConstraint::PoweredLinMotor::get()
{
	return UnmanagedPointer->getPoweredLinMotor();
}
void SliderConstraint::PoweredLinMotor::set(bool value)
{
	UnmanagedPointer->setPoweredLinMotor(value);
}

btScalar SliderConstraint::RestitutionDirAngular::get()
{
	return UnmanagedPointer->getRestitutionDirAng();
}
void SliderConstraint::RestitutionDirAngular::set(btScalar value)
{
	UnmanagedPointer->setRestitutionDirAng(value);
}

btScalar SliderConstraint::RestitutionDirLin::get()
{
	return UnmanagedPointer->getRestitutionDirLin();
}
void SliderConstraint::RestitutionDirLin::set(btScalar value)
{
	UnmanagedPointer->setRestitutionDirLin(value);
}

btScalar SliderConstraint::RestitutionLimAngular::get()
{
	return UnmanagedPointer->getRestitutionLimAng();
}
void SliderConstraint::RestitutionLimAngular::set(btScalar value)
{
	UnmanagedPointer->setRestitutionLimAng(value);
}

btScalar SliderConstraint::RestitutionLimLin::get()
{
	return UnmanagedPointer->getRestitutionLimLin();
}
void SliderConstraint::RestitutionLimLin::set(btScalar value)
{
	UnmanagedPointer->setRestitutionLimLin(value);
}

btScalar SliderConstraint::RestitutionOrthoAngular::get()
{
	return UnmanagedPointer->getRestitutionOrthoAng();
}
void SliderConstraint::RestitutionOrthoAngular::set(btScalar value)
{
	UnmanagedPointer->setRestitutionOrthoAng(value);
}

btScalar SliderConstraint::RestitutionOrthoLin::get()
{
	return UnmanagedPointer->getRestitutionOrthoLin();
}
void SliderConstraint::RestitutionOrthoLin::set(btScalar value)
{
	UnmanagedPointer->setRestitutionOrthoLin(value);
}

btScalar SliderConstraint::SoftnessDirAngular::get()
{
	return UnmanagedPointer->getSoftnessDirAng();
}
void SliderConstraint::SoftnessDirAngular::set(btScalar value)
{
	UnmanagedPointer->setSoftnessDirAng(value);
}

btScalar SliderConstraint::SoftnessDirLin::get()
{
	return UnmanagedPointer->getSoftnessDirLin();
}
void SliderConstraint::SoftnessDirLin::set(btScalar value)
{
	UnmanagedPointer->setSoftnessDirLin(value);
}

btScalar SliderConstraint::SoftnessLimAngular::get()
{
	return UnmanagedPointer->getSoftnessLimAng();
}
void SliderConstraint::SoftnessLimAngular::set(btScalar value)
{
	UnmanagedPointer->setSoftnessLimAng(value);
}

btScalar SliderConstraint::SoftnessLimLin::get()
{
	return UnmanagedPointer->getSoftnessLimLin();
}
void SliderConstraint::SoftnessLimLin::set(btScalar value)
{
	UnmanagedPointer->setSoftnessLimLin(value);
}

btScalar SliderConstraint::SoftnessOrthoAngular::get()
{
	return UnmanagedPointer->getSoftnessOrthoAng();
}
void SliderConstraint::SoftnessOrthoAngular::set(btScalar value)
{
	UnmanagedPointer->setSoftnessOrthoAng(value);
}

btScalar SliderConstraint::SoftnessOrthoLin::get()
{
	return UnmanagedPointer->getSoftnessOrthoLin();
}
void SliderConstraint::SoftnessOrthoLin::set(btScalar value)
{
	UnmanagedPointer->setSoftnessOrthoLin(value);
}

bool SliderConstraint::SolveAngularLimit::get()
{
	return UnmanagedPointer->getSolveAngLimit();
}

bool SliderConstraint::SolveLinLimit::get()
{
	return UnmanagedPointer->getSolveLinLimit();
}

btScalar SliderConstraint::TargetAngularMotorVelocity::get()
{
	return UnmanagedPointer->getTargetAngMotorVelocity();
}
void SliderConstraint::TargetAngularMotorVelocity::set(btScalar value)
{
	UnmanagedPointer->setTargetAngMotorVelocity(value);
}

btScalar SliderConstraint::TargetLinMotorVelocity::get()
{
	return UnmanagedPointer->getTargetLinMotorVelocity();
}
void SliderConstraint::TargetLinMotorVelocity::set(btScalar value)
{
	UnmanagedPointer->setTargetLinMotorVelocity(value);
}

btScalar SliderConstraint::UpperAngularLimit::get()
{
	return UnmanagedPointer->getUpperAngLimit();
}
void SliderConstraint::UpperAngularLimit::set(btScalar value)
{
	UnmanagedPointer->setUpperAngLimit(value);
}

btScalar SliderConstraint::UpperLinLimit::get()
{
	return UnmanagedPointer->getUpperLinLimit();
}
void SliderConstraint::UpperLinLimit::set(btScalar value)
{
	UnmanagedPointer->setUpperLinLimit(value);
}

bool SliderConstraint::UseFrameOffset::get()
{
	return UnmanagedPointer->getUseFrameOffset();
}
void SliderConstraint::UseFrameOffset::set(bool value)
{
	UnmanagedPointer->setUseFrameOffset(value);
}

bool SliderConstraint::UseLinearReferenceFrameA::get()
{
	return UnmanagedPointer->getUseLinearReferenceFrameA();
}

btSliderConstraint* SliderConstraint::UnmanagedPointer::get()
{
	return (btSliderConstraint*)TypedConstraint::UnmanagedPointer;
}

#endif
