#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "RigidBody.h"
#include "WheelInfo.h"

#define __GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
#define __VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))

WheelInfoConstructionInfo::WheelInfoConstructionInfo()
{
	_info = new btWheelInfoConstructionInfo();
}

Vector3 WheelInfoConstructionInfo::ChassisConnectionCS::get()
{
	return  Math::BtVector3ToVector3(&_info->m_chassisConnectionCS);
}
void WheelInfoConstructionInfo::ChassisConnectionCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_chassisConnectionCS);
}

btScalar WheelInfoConstructionInfo::FrictionSlip::get()
{
	return _info->m_frictionSlip;
}
void WheelInfoConstructionInfo::FrictionSlip::set(btScalar value)
{
	_info->m_frictionSlip = value;
}

bool WheelInfoConstructionInfo::IsFrontWheel::get()
{
	return _info->m_bIsFrontWheel;
}
void WheelInfoConstructionInfo::IsFrontWheel::set(bool value)
{
	_info->m_bIsFrontWheel = value;
}

btScalar WheelInfoConstructionInfo::MaxSuspensionForce::get()
{
	return _info->m_maxSuspensionForce;
}
void WheelInfoConstructionInfo::MaxSuspensionForce::set(btScalar value)
{
	_info->m_maxSuspensionForce = value;
}

btScalar WheelInfoConstructionInfo::MaxSuspensionTravelCm::get()
{
	return _info->m_maxSuspensionTravelCm;
}
void WheelInfoConstructionInfo::MaxSuspensionTravelCm::set(btScalar value)
{
	_info->m_maxSuspensionTravelCm = value;
}

btScalar WheelInfoConstructionInfo::SuspensionRestLength::get()
{
	return _info->m_suspensionRestLength;
}
void WheelInfoConstructionInfo::SuspensionRestLength::set(btScalar value)
{
	_info->m_suspensionRestLength = value;
}

btScalar WheelInfoConstructionInfo::SuspensionStiffness::get()
{
	return _info->m_suspensionStiffness;
}
void WheelInfoConstructionInfo::SuspensionStiffness::set(btScalar value)
{
	_info->m_suspensionStiffness = value;
}

Vector3 WheelInfoConstructionInfo::WheelAxleCS::get()
{
	return  Math::BtVector3ToVector3(&_info->m_wheelAxleCS);
}
void WheelInfoConstructionInfo::WheelAxleCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_wheelAxleCS);
}

btScalar WheelInfoConstructionInfo::WheelDampingCompression::get()
{
	return _info->m_wheelsDampingCompression;
}
void WheelInfoConstructionInfo::WheelDampingCompression::set(btScalar value)
{
	_info->m_wheelsDampingCompression = value;
}

btScalar WheelInfoConstructionInfo::WheelDampingRelaxation::get()
{
	return _info->m_wheelsDampingRelaxation;
}
void WheelInfoConstructionInfo::WheelDampingRelaxation::set(btScalar value)
{
	_info->m_wheelsDampingRelaxation = value;
}

Vector3 WheelInfoConstructionInfo::WheelDirectionCS::get()
{
	return  Math::BtVector3ToVector3(&_info->m_wheelDirectionCS);
}
void WheelInfoConstructionInfo::WheelDirectionCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_wheelDirectionCS);
}

btScalar WheelInfoConstructionInfo::WheelRadius::get()
{
	return _info->m_wheelRadius;
}
void WheelInfoConstructionInfo::WheelRadius::set(btScalar value)
{
	_info->m_wheelRadius = value;
}

btWheelInfoConstructionInfo* WheelInfoConstructionInfo::UnmanagedPointer::get()
{
	return _info;
}
void WheelInfoConstructionInfo::UnmanagedPointer::set(btWheelInfoConstructionInfo* value)
{
	_info = value;
}


WheelInfo::RaycastInfo::RaycastInfo(btWheelInfo::RaycastInfo* info)
{
	_info = info;
}

WheelInfo::RaycastInfo::RaycastInfo()
{
	_info = new btWheelInfo::RaycastInfo();
}

Vector3 WheelInfo::RaycastInfo::ContactNormalWS::get()
{
	return Math::BtVector3ToVector3(&_info->m_contactNormalWS);
}
void WheelInfo::RaycastInfo::ContactNormalWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_contactNormalWS);
}

Vector3 WheelInfo::RaycastInfo::ContactPointWS::get()
{
	return Math::BtVector3ToVector3(&_info->m_contactPointWS);
}
void WheelInfo::RaycastInfo::ContactPointWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_contactPointWS);
}

Object^ WheelInfo::RaycastInfo::GroundObject::get()
{
	if (_info->m_groundObject = 0)
		return nullptr;

	return gcnew RigidBody((btRigidBody*)_info->m_groundObject);
}
void WheelInfo::RaycastInfo::GroundObject::set(Object^ value)
{
	RigidBody^ body = static_cast<RigidBody^>(value);
	if (body == nullptr)
		_info->m_groundObject = 0;
	
	_info->m_groundObject = body->UnmanagedPointer;
}

Vector3 WheelInfo::RaycastInfo::HardPointWS::get()
{
	return Math::BtVector3ToVector3(&_info->m_hardPointWS);
}
void WheelInfo::RaycastInfo::HardPointWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_hardPointWS);
}

bool WheelInfo::RaycastInfo::IsInContact::get()
{
	return _info->m_isInContact;
}
void WheelInfo::RaycastInfo::IsInContact::set(bool value)
{
	_info->m_isInContact = value;
}

btScalar WheelInfo::RaycastInfo::SuspensionLength::get()
{
	return _info->m_suspensionLength;
}
void WheelInfo::RaycastInfo::SuspensionLength::set(btScalar value)
{
	_info->m_suspensionLength = value;
}

Vector3 WheelInfo::RaycastInfo::WheelAxleWS::get()
{
	return Math::BtVector3ToVector3(&_info->m_wheelAxleWS);
}
void WheelInfo::RaycastInfo::WheelAxleWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_wheelAxleWS);
}

Vector3 WheelInfo::RaycastInfo::WheelDirectionWS::get()
{
	return Math::BtVector3ToVector3(&_info->m_wheelDirectionWS);
}
void WheelInfo::RaycastInfo::WheelDirectionWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_wheelDirectionWS);
}

btWheelInfo::RaycastInfo* WheelInfo::RaycastInfo::UnmanagedPointer::get()
{
	return _info;
}
void WheelInfo::RaycastInfo::UnmanagedPointer::set(btWheelInfo::RaycastInfo* value)
{
	_info = value;
}


WheelInfo::WheelInfo(btWheelInfo* wheelInfo)
{
	_wheelInfo = wheelInfo;
}

WheelInfo::WheelInfo(WheelInfoConstructionInfo^ ci)
{
	_wheelInfo = new btWheelInfo(*ci->UnmanagedPointer);
}

void WheelInfo::UpdateWheel(RigidBody^ chassis, RaycastInfo^ raycastInfo)
{
	_wheelInfo->updateWheel(*chassis->UnmanagedPointer, *raycastInfo->UnmanagedPointer);
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

Object^ WheelInfo::ClientInfo::get()
{
	void* obj = _wheelInfo->m_clientInfo;
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(__VOIDPTR_TO_GCHANDLE(obj).Target);
}
void WheelInfo::ClientInfo::set(Object^ value)
{
	void* obj = _wheelInfo->m_clientInfo;
	if (obj != nullptr)
		__VOIDPTR_TO_GCHANDLE(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_wheelInfo->m_clientInfo = __GCHANDLE_TO_VOIDPTR(handle);
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

btScalar WheelInfo::MaxSuspensionForce::get()
{
	return _wheelInfo->m_maxSuspensionForce;
}
void WheelInfo::MaxSuspensionForce::set(btScalar value)
{
	_wheelInfo->m_maxSuspensionForce = value;
}

btScalar WheelInfo::MaxSuspensionTravelCm::get()
{
	return _wheelInfo->m_maxSuspensionTravelCm;
}
void WheelInfo::MaxSuspensionTravelCm::set(btScalar value)
{
	_wheelInfo->m_maxSuspensionTravelCm = value;
}

#pragma managed(push, off)
void WheelInfo_SetRaycastInfo(btWheelInfo* wheelInfo, btWheelInfo::RaycastInfo* info)
{
	wheelInfo->m_raycastInfo = *info;
}
#pragma managed(pop)
WheelInfo::RaycastInfo^ WheelInfo::RaycastInfo_::get()
{
	return gcnew RaycastInfo(&_wheelInfo->m_raycastInfo);
}
void WheelInfo::RaycastInfo_::set(WheelInfo::RaycastInfo^ value)
{
	WheelInfo_SetRaycastInfo(_wheelInfo, value->UnmanagedPointer);
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
	return _wheelInfo->getSuspensionRestLength();
}

btScalar WheelInfo::SuspensionRestLength1::get()
{
	return _wheelInfo->m_suspensionRestLength1;
}
void WheelInfo::SuspensionRestLength1::set(btScalar value)
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

Vector3 WheelInfo::WheelAxleCS::get()
{
	return  Math::BtVector3ToVector3(&_wheelInfo->m_wheelAxleCS);
}
void WheelInfo::WheelAxleCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_wheelInfo->m_wheelAxleCS);
}

btScalar WheelInfo::WheelDampingCompression::get()
{
	return _wheelInfo->m_wheelsDampingCompression;
}
void WheelInfo::WheelDampingCompression::set(btScalar value)
{
	_wheelInfo->m_wheelsDampingCompression = value;
}

btScalar WheelInfo::WheelDampingRelaxation::get()
{
	return _wheelInfo->m_wheelsDampingRelaxation;
}
void WheelInfo::WheelDampingRelaxation::set(btScalar value)
{
	_wheelInfo->m_wheelsDampingRelaxation = value;
}

Vector3 WheelInfo::WheelDirectionCS::get()
{
	return  Math::BtVector3ToVector3(&_wheelInfo->m_wheelDirectionCS);
}
void WheelInfo::WheelDirectionCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_wheelInfo->m_wheelDirectionCS);
}

btScalar WheelInfo::WheelRadius::get()
{
	return _wheelInfo->m_wheelsRadius;
}
void WheelInfo::WheelRadius::set(btScalar value)
{
	_wheelInfo->m_wheelsRadius = value;
}

btScalar WheelInfo::WheelSuspensionForce::get()
{
	return _wheelInfo->m_wheelsSuspensionForce;
}
void WheelInfo::WheelSuspensionForce::set(btScalar value)
{
	_wheelInfo->m_wheelsSuspensionForce = value;
}

Matrix WheelInfo::WorldTransform::get()
{
	return Math::BtTransformToMatrix(&_wheelInfo->m_worldTransform);
}
void WheelInfo::WorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_wheelInfo->m_worldTransform);
}

btWheelInfo* WheelInfo::UnmanagedPointer::get()
{
	return _wheelInfo;
}
void WheelInfo::UnmanagedPointer::set(btWheelInfo* value)
{
	_wheelInfo = value;
}

#endif