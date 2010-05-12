#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "SliderConstraint.h"

SliderConstraint::SliderConstraint(btSliderConstraint* constraint)
: TypedConstraint(constraint)
{
}

SliderConstraint::SliderConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btSliderConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA);

	delete frameInATemp;
	delete frameInBTemp;
}

SliderConstraint::SliderConstraint(RigidBody^ rbB, Matrix frameInB, bool useLinearReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btSliderConstraint(*rbB->UnmanagedPointer, *frameInBTemp, useLinearReferenceFrameA);

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

void SliderConstraint::TestAngLimits()
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
	btVector3* anchorInATemp = new btVector3();
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
	btVector3* anchorInBTemp = new btVector3();
	SliderConstraint_GetAnchorInB(UnmanagedPointer, anchorInBTemp);
	Vector3 anchor = Math::BtVector3ToVector3(anchorInBTemp);
	delete anchorInBTemp;
	return anchor;
}

btScalar SliderConstraint::AngDepth::get()
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

btScalar SliderConstraint::DampingDirAng::get()
{
	return UnmanagedPointer->getDampingDirAng();
}
void SliderConstraint::DampingDirAng::set(btScalar value)
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

btScalar SliderConstraint::DampingLimAng::get()
{
	return UnmanagedPointer->getDampingLimAng();
}
void SliderConstraint::DampingLimAng::set(btScalar value)
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

btScalar SliderConstraint::DampingOrthoAng::get()
{
	return UnmanagedPointer->getDampingOrthoAng();
}
void SliderConstraint::DampingOrthoAng::set(btScalar value)
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

btScalar SliderConstraint::LowerAngLimit::get()
{
	return UnmanagedPointer->getLowerAngLimit();
}
void SliderConstraint::LowerAngLimit::set(btScalar value)
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

btScalar SliderConstraint::MaxAngMotorForce::get()
{
	return UnmanagedPointer->getMaxAngMotorForce();
}
void SliderConstraint::MaxAngMotorForce::set(btScalar value)
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

bool SliderConstraint::PoweredAngMotor::get()
{
	return UnmanagedPointer->getPoweredAngMotor();
}
void SliderConstraint::PoweredAngMotor::set(bool value)
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

btScalar SliderConstraint::RestitutionDirAng::get()
{
	return UnmanagedPointer->getRestitutionDirAng();
}
void SliderConstraint::RestitutionDirAng::set(btScalar value)
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

btScalar SliderConstraint::RestitutionLimAng::get()
{
	return UnmanagedPointer->getRestitutionLimAng();
}
void SliderConstraint::RestitutionLimAng::set(btScalar value)
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

btScalar SliderConstraint::RestitutionOrthoAng::get()
{
	return UnmanagedPointer->getRestitutionOrthoAng();
}
void SliderConstraint::RestitutionOrthoAng::set(btScalar value)
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

btScalar SliderConstraint::SoftnessDirAng::get()
{
	return UnmanagedPointer->getSoftnessDirAng();
}
void SliderConstraint::SoftnessDirAng::set(btScalar value)
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

btScalar SliderConstraint::SoftnessLimAng::get()
{
	return UnmanagedPointer->getSoftnessLimAng();
}
void SliderConstraint::SoftnessLimAng::set(btScalar value)
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

btScalar SliderConstraint::SoftnessOrthoAng::get()
{
	return UnmanagedPointer->getSoftnessOrthoAng();
}
void SliderConstraint::SoftnessOrthoAng::set(btScalar value)
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

bool SliderConstraint::SolveAngLimit::get()
{
	return UnmanagedPointer->getSolveAngLimit();
}

bool SliderConstraint::SolveLinLimit::get()
{
	return UnmanagedPointer->getSolveLinLimit();
}

btScalar SliderConstraint::TargetAngMotorVelocity::get()
{
	return UnmanagedPointer->getTargetAngMotorVelocity();
}
void SliderConstraint::TargetAngMotorVelocity::set(btScalar value)
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

btScalar SliderConstraint::UpperAngLimit::get()
{
	return UnmanagedPointer->getUpperAngLimit();
}
void SliderConstraint::UpperAngLimit::set(btScalar value)
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
