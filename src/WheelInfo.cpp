#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "WheelInfo.h"

WheelInfo::WheelInfo(btWheelInfo* wheelInfo)
{
	_wheelInfo = wheelInfo;
}

Vector3 WheelInfo::AxleCS::get()
{
	return  Math::BtVector3ToVector3(&_wheelInfo->m_wheelAxleCS);
}
void WheelInfo::AxleCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_wheelInfo->m_wheelAxleCS);
}

btScalar WheelInfo::Brake::get()
{
	return _wheelInfo->m_brake;
}
void WheelInfo::Brake::set(btScalar value)
{
	_wheelInfo->m_brake = value;
}

Vector3 WheelInfo::ChassisConnectionPointCS::get()
{
	return  Math::BtVector3ToVector3(&_wheelInfo->m_chassisConnectionPointCS);
}
void WheelInfo::ChassisConnectionPointCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_wheelInfo->m_chassisConnectionPointCS);
}

IntPtr WheelInfo::ClientInfo::get()
{
	return IntPtr(_wheelInfo->m_clientInfo);
}
void WheelInfo::ClientInfo::set(IntPtr value)
{
	_wheelInfo->m_clientInfo = value.ToPointer();
}

btScalar WheelInfo::ClippedInvContactDotSuspension::get()
{
	return _wheelInfo->m_clippedInvContactDotSuspension;
}
void WheelInfo::ClippedInvContactDotSuspension::set(btScalar value)
{
	_wheelInfo->m_clippedInvContactDotSuspension = value;
}

btScalar WheelInfo::DeltaRotation::get()
{
	return _wheelInfo->m_deltaRotation;
}
void WheelInfo::DeltaRotation::set(btScalar value)
{
	_wheelInfo->m_deltaRotation = value;
}

btScalar WheelInfo::DampingCompression::get()
{
	return _wheelInfo->m_wheelsDampingCompression;
}
void WheelInfo::DampingCompression::set(btScalar value)
{
	_wheelInfo->m_wheelsDampingCompression = value;
}

btScalar WheelInfo::DampingRelaxation::get()
{
	return _wheelInfo->m_wheelsDampingRelaxation;
}
void WheelInfo::DampingRelaxation::set(btScalar value)
{
	_wheelInfo->m_wheelsDampingRelaxation = value;
}

Vector3 WheelInfo::DirectionCS::get()
{
	return  Math::BtVector3ToVector3(&_wheelInfo->m_wheelDirectionCS);
}
void WheelInfo::DirectionCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_wheelInfo->m_wheelDirectionCS);
}

btScalar WheelInfo::EngineForce::get()
{
	return _wheelInfo->m_engineForce;
}
void WheelInfo::EngineForce::set(btScalar value)
{
	_wheelInfo->m_engineForce = value;
}

btScalar WheelInfo::FrictionSlip::get()
{
	return _wheelInfo->m_frictionSlip;
}
void WheelInfo::FrictionSlip::set(btScalar value)
{
	_wheelInfo->m_frictionSlip = value;
}

bool WheelInfo::IsFrontWheel::get()
{
	return _wheelInfo->m_bIsFrontWheel;
}
void WheelInfo::IsFrontWheel::set(bool value)
{
	_wheelInfo->m_bIsFrontWheel = value;
}

btScalar WheelInfo::MaxSuspensionTravelCm::get()
{
	return _wheelInfo->m_maxSuspensionTravelCm;
}
void WheelInfo::MaxSuspensionTravelCm::set(btScalar value)
{
	_wheelInfo->m_maxSuspensionTravelCm = value;
}

btScalar WheelInfo::Radius::get()
{
	return _wheelInfo->m_wheelsRadius;
}
void WheelInfo::Radius::set(btScalar value)
{
	_wheelInfo->m_wheelsRadius = value;
}

btScalar WheelInfo::RollInfluence::get()
{
	return _wheelInfo->m_rollInfluence;
}
void WheelInfo::RollInfluence::set(btScalar value)
{
	_wheelInfo->m_rollInfluence = value;
}

btScalar WheelInfo::Rotation::get()
{
	return _wheelInfo->m_rotation;
}
void WheelInfo::Rotation::set(btScalar value)
{
	_wheelInfo->m_rotation = value;
}

btScalar WheelInfo::SkidInfo::get()
{
	return _wheelInfo->m_skidInfo;
}
void WheelInfo::SkidInfo::set(btScalar value)
{
	_wheelInfo->m_skidInfo = value;
}

btScalar WheelInfo::Steering::get()
{
	return _wheelInfo->m_steering;
}
void WheelInfo::Steering::set(btScalar value)
{
	_wheelInfo->m_steering = value;
}

btScalar WheelInfo::SuspensionForce::get()
{
	return _wheelInfo->m_wheelsSuspensionForce;
}
void WheelInfo::SuspensionForce::set(btScalar value)
{
	_wheelInfo->m_wheelsSuspensionForce = value;
}

btScalar WheelInfo::SuspensionRelativeVelocity::get()
{
	return _wheelInfo->m_suspensionRelativeVelocity;
}
void WheelInfo::SuspensionRelativeVelocity::set(btScalar value)
{
	_wheelInfo->m_suspensionRelativeVelocity = value;
}

btScalar WheelInfo::SuspensionRestLength::get()
{
	return _wheelInfo->m_suspensionRestLength1;
}
void WheelInfo::SuspensionRestLength::set(btScalar value)
{
	_wheelInfo->m_suspensionRestLength1 = value;
}

btScalar WheelInfo::SuspensionStiffness::get()
{
	return _wheelInfo->m_suspensionStiffness;
}
void WheelInfo::SuspensionStiffness::set(btScalar value)
{
	_wheelInfo->m_suspensionStiffness = value;
}

Matrix WheelInfo::WorldTransform::get()
{
	return Math::BtTransformToMatrix(&_wheelInfo->m_worldTransform);
}
void WheelInfo::WorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_wheelInfo->m_worldTransform);
}

#endif