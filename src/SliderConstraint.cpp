#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "SliderConstraint.h"

#define Native static_cast<btSliderConstraint*>(_native)

SliderConstraint::SliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btSliderConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB), useLinearReferenceFrameA);
	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

SliderConstraint::SliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btSliderConstraint(*(btRigidBody*)rigidBodyB->_native, TRANSFORM_USE(frameInB),
		useLinearReferenceFrameA);
	TRANSFORM_DEL(frameInB);
	_rigidBodyA = GetFixedBody();
	_rigidBodyB = rigidBodyB;
}

void SliderConstraint::CalculateTransforms(Matrix transA, Matrix transB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	Native->calculateTransforms(TRANSFORM_USE(transA), TRANSFORM_USE(transB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
}

void SliderConstraint::GetInfo1NonVirtual(ConstraintInfo1^ info)
{
	Native->getInfo1NonVirtual(info->_native);
}

void SliderConstraint::GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA, Matrix transB,
	Vector3 linVelA, Vector3 linVelB, btScalar rbAinvMass, btScalar rbBinvMass)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	VECTOR3_CONV(linVelA);
	VECTOR3_CONV(linVelB);
	Native->getInfo2NonVirtual(info->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
		VECTOR3_USE(linVelA), VECTOR3_USE(linVelB), rbAinvMass, rbBinvMass);
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	VECTOR3_DEL(linVelA);
	VECTOR3_DEL(linVelB);
}

void SliderConstraint::SetFrames(Matrix frameA, Matrix frameB)
{
	TRANSFORM_CONV(frameA);
	TRANSFORM_CONV(frameB);
	Native->setFrames(TRANSFORM_USE(frameA), TRANSFORM_USE(frameB));
	TRANSFORM_DEL(frameA);
	TRANSFORM_DEL(frameB);
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
	btVector3* anchorInATemp = ALIGNED_NEW(btVector3);
	SliderConstraint_GetAnchorInA(Native, anchorInATemp);
	Vector3 anchor = Math::BtVector3ToVector3(anchorInATemp);
	ALIGNED_FREE(anchorInATemp);
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
	btVector3* anchorInBTemp = ALIGNED_NEW(btVector3);
	SliderConstraint_GetAnchorInB(Native, anchorInBTemp);
	Vector3 anchor = Math::BtVector3ToVector3(anchorInBTemp);
	ALIGNED_FREE(anchorInBTemp);
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
void SliderConstraint::DampingDirAngular::set(btScalar dampingDirAng)
{
	Native->setDampingDirAng(dampingDirAng);
}

btScalar SliderConstraint::DampingDirLin::get()
{
	return Native->getDampingDirLin();
}
void SliderConstraint::DampingDirLin::set(btScalar dampingDirLin)
{
	Native->setDampingDirLin(dampingDirLin);
}

btScalar SliderConstraint::DampingLimAngular::get()
{
	return Native->getDampingLimAng();
}
void SliderConstraint::DampingLimAngular::set(btScalar dampingLimAng)
{
	Native->setDampingLimAng(dampingLimAng);
}

btScalar SliderConstraint::DampingLimLin::get()
{
	return Native->getDampingLimLin();
}
void SliderConstraint::DampingLimLin::set(btScalar dampingLimLin)
{
	Native->setDampingLimLin(dampingLimLin);
}

btScalar SliderConstraint::DampingOrthoAngular::get()
{
	return Native->getDampingOrthoAng();
}
void SliderConstraint::DampingOrthoAngular::set(btScalar dampingOrthoAng)
{
	Native->setDampingOrthoAng(dampingOrthoAng);
}

btScalar SliderConstraint::DampingOrthoLin::get()
{
	return Native->getDampingOrthoLin();
}
void SliderConstraint::DampingOrthoLin::set(btScalar dampingOrthoLin)
{
	Native->setDampingOrthoLin(dampingOrthoLin);
}

SliderFlags SliderConstraint::Flags::get()
{
	return (SliderFlags) Native->getFlags();
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
void SliderConstraint::LowerAngularLimit::set(btScalar lowerLimit)
{
	Native->setLowerAngLimit(lowerLimit);
}

btScalar SliderConstraint::LowerLinLimit::get()
{
	return Native->getLowerLinLimit();
}
void SliderConstraint::LowerLinLimit::set(btScalar lowerLimit)
{
	Native->setLowerLinLimit(lowerLimit);
}

btScalar SliderConstraint::MaxAngularMotorForce::get()
{
	return Native->getMaxAngMotorForce();
}
void SliderConstraint::MaxAngularMotorForce::set(btScalar maxAngMotorForce)
{
	Native->setMaxAngMotorForce(maxAngMotorForce);
}

btScalar SliderConstraint::MaxLinMotorForce::get()
{
	return Native->getMaxLinMotorForce();
}
void SliderConstraint::MaxLinMotorForce::set(btScalar maxLinMotorForce)
{
	Native->setMaxLinMotorForce(maxLinMotorForce);
}

bool SliderConstraint::PoweredAngularMotor::get()
{
	return Native->getPoweredAngMotor();
}
void SliderConstraint::PoweredAngularMotor::set(bool onOff)
{
	Native->setPoweredAngMotor(onOff);
}

bool SliderConstraint::PoweredLinMotor::get()
{
	return Native->getPoweredLinMotor();
}
void SliderConstraint::PoweredLinMotor::set(bool onOff)
{
	Native->setPoweredLinMotor(onOff);
}

btScalar SliderConstraint::RestitutionDirAngular::get()
{
	return Native->getRestitutionDirAng();
}
void SliderConstraint::RestitutionDirAngular::set(btScalar restitutionDirAng)
{
	Native->setRestitutionDirAng(restitutionDirAng);
}

btScalar SliderConstraint::RestitutionDirLin::get()
{
	return Native->getRestitutionDirLin();
}
void SliderConstraint::RestitutionDirLin::set(btScalar restitutionDirLin)
{
	Native->setRestitutionDirLin(restitutionDirLin);
}

btScalar SliderConstraint::RestitutionLimAngular::get()
{
	return Native->getRestitutionLimAng();
}
void SliderConstraint::RestitutionLimAngular::set(btScalar restitutionLimAng)
{
	Native->setRestitutionLimAng(restitutionLimAng);
}

btScalar SliderConstraint::RestitutionLimLin::get()
{
	return Native->getRestitutionLimLin();
}
void SliderConstraint::RestitutionLimLin::set(btScalar restitutionLimLin)
{
	Native->setRestitutionLimLin(restitutionLimLin);
}

btScalar SliderConstraint::RestitutionOrthoAngular::get()
{
	return Native->getRestitutionOrthoAng();
}
void SliderConstraint::RestitutionOrthoAngular::set(btScalar restitutionOrthoAng)
{
	Native->setRestitutionOrthoAng(restitutionOrthoAng);
}

btScalar SliderConstraint::RestitutionOrthoLin::get()
{
	return Native->getRestitutionOrthoLin();
}
void SliderConstraint::RestitutionOrthoLin::set(btScalar restitutionOrthoLin)
{
	Native->setRestitutionOrthoLin(restitutionOrthoLin);
}

btScalar SliderConstraint::SoftnessDirAngular::get()
{
	return Native->getSoftnessDirAng();
}
void SliderConstraint::SoftnessDirAngular::set(btScalar softnessDirAng)
{
	Native->setSoftnessDirAng(softnessDirAng);
}

btScalar SliderConstraint::SoftnessDirLin::get()
{
	return Native->getSoftnessDirLin();
}
void SliderConstraint::SoftnessDirLin::set(btScalar softnessDirLin)
{
	Native->setSoftnessDirLin(softnessDirLin);
}

btScalar SliderConstraint::SoftnessLimAngular::get()
{
	return Native->getSoftnessLimAng();
}
void SliderConstraint::SoftnessLimAngular::set(btScalar softnessLimAng)
{
	Native->setSoftnessLimAng(softnessLimAng);
}

btScalar SliderConstraint::SoftnessLimLin::get()
{
	return Native->getSoftnessLimLin();
}
void SliderConstraint::SoftnessLimLin::set(btScalar softnessLimLin)
{
	Native->setSoftnessLimLin(softnessLimLin);
}

btScalar SliderConstraint::SoftnessOrthoAngular::get()
{
	return Native->getSoftnessOrthoAng();
}
void SliderConstraint::SoftnessOrthoAngular::set(btScalar softnessOrthoAng)
{
	Native->setSoftnessOrthoAng(softnessOrthoAng);
}

btScalar SliderConstraint::SoftnessOrthoLin::get()
{
	return Native->getSoftnessOrthoLin();
}
void SliderConstraint::SoftnessOrthoLin::set(btScalar softnessOrthoLin)
{
	Native->setSoftnessOrthoLin(softnessOrthoLin);
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
void SliderConstraint::TargetAngularMotorVelocity::set(btScalar targetAngMotorVelocity)
{
	Native->setTargetAngMotorVelocity(targetAngMotorVelocity);
}

btScalar SliderConstraint::TargetLinMotorVelocity::get()
{
	return Native->getTargetLinMotorVelocity();
}
void SliderConstraint::TargetLinMotorVelocity::set(btScalar targetLinMotorVelocity)
{
	Native->setTargetLinMotorVelocity(targetLinMotorVelocity);
}

btScalar SliderConstraint::UpperAngularLimit::get()
{
	return Native->getUpperAngLimit();
}
void SliderConstraint::UpperAngularLimit::set(btScalar upperLimit)
{
	Native->setUpperAngLimit(upperLimit);
}

btScalar SliderConstraint::UpperLinLimit::get()
{
	return Native->getUpperLinLimit();
}
void SliderConstraint::UpperLinLimit::set(btScalar upperLimit)
{
	Native->setUpperLinLimit(upperLimit);
}

bool SliderConstraint::UseFrameOffset::get()
{
	return Native->getUseFrameOffset();
}
void SliderConstraint::UseFrameOffset::set(bool frameOffsetOnOff)
{
	Native->setUseFrameOffset(frameOffsetOnOff);
}

bool SliderConstraint::UseLinearReferenceFrameA::get()
{
	return Native->getUseLinearReferenceFrameA();
}

#endif
