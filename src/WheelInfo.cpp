#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "RigidBody.h"
#include "WheelInfo.h"

WheelInfoConstructionInfo::WheelInfoConstructionInfo(btWheelInfoConstructionInfo* native)
{
	_native = native;
}

WheelInfoConstructionInfo::!WheelInfoConstructionInfo()
{
	ALIGNED_FREE(_native);
	_native = 0;
}

WheelInfoConstructionInfo::~WheelInfoConstructionInfo()
{
	this->!WheelInfoConstructionInfo();
}

WheelInfoConstructionInfo::WheelInfoConstructionInfo()
{
	_native = ALIGNED_NEW(btWheelInfoConstructionInfo) ();
}

Vector3 WheelInfoConstructionInfo::ChassisConnectionCS::get()
{
	return Math::BtVector3ToVector3(&_native->m_chassisConnectionCS);
}
void WheelInfoConstructionInfo::ChassisConnectionCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_chassisConnectionCS);
}

btScalar WheelInfoConstructionInfo::FrictionSlip::get()
{
	return _native->m_frictionSlip;
}
void WheelInfoConstructionInfo::FrictionSlip::set(btScalar value)
{
	_native->m_frictionSlip = value;
}

bool WheelInfoConstructionInfo::IsFrontWheel::get()
{
	return _native->m_bIsFrontWheel;
}
void WheelInfoConstructionInfo::IsFrontWheel::set(bool value)
{
	_native->m_bIsFrontWheel = value;
}

btScalar WheelInfoConstructionInfo::MaxSuspensionForce::get()
{
	return _native->m_maxSuspensionForce;
}
void WheelInfoConstructionInfo::MaxSuspensionForce::set(btScalar value)
{
	_native->m_maxSuspensionForce = value;
}

btScalar WheelInfoConstructionInfo::MaxSuspensionTravelCm::get()
{
	return _native->m_maxSuspensionTravelCm;
}
void WheelInfoConstructionInfo::MaxSuspensionTravelCm::set(btScalar value)
{
	_native->m_maxSuspensionTravelCm = value;
}

btScalar WheelInfoConstructionInfo::SuspensionRestLength::get()
{
	return _native->m_suspensionRestLength;
}
void WheelInfoConstructionInfo::SuspensionRestLength::set(btScalar value)
{
	_native->m_suspensionRestLength = value;
}

btScalar WheelInfoConstructionInfo::SuspensionStiffness::get()
{
	return _native->m_suspensionStiffness;
}
void WheelInfoConstructionInfo::SuspensionStiffness::set(btScalar value)
{
	_native->m_suspensionStiffness = value;
}

Vector3 WheelInfoConstructionInfo::WheelAxleCS::get()
{
	return Math::BtVector3ToVector3(&_native->m_wheelAxleCS);
}
void WheelInfoConstructionInfo::WheelAxleCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_wheelAxleCS);
}

btScalar WheelInfoConstructionInfo::WheelsDampingCompression::get()
{
	return _native->m_wheelsDampingCompression;
}
void WheelInfoConstructionInfo::WheelsDampingCompression::set(btScalar value)
{
	_native->m_wheelsDampingCompression = value;
}

btScalar WheelInfoConstructionInfo::WheelsDampingRelaxation::get()
{
	return _native->m_wheelsDampingRelaxation;
}
void WheelInfoConstructionInfo::WheelsDampingRelaxation::set(btScalar value)
{
	_native->m_wheelsDampingRelaxation = value;
}

Vector3 WheelInfoConstructionInfo::WheelDirectionCS::get()
{
	return  Math::BtVector3ToVector3(&_native->m_wheelDirectionCS);
}
void WheelInfoConstructionInfo::WheelDirectionCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_wheelDirectionCS);
}

btScalar WheelInfoConstructionInfo::WheelRadius::get()
{
	return _native->m_wheelRadius;
}
void WheelInfoConstructionInfo::WheelRadius::set(btScalar value)
{
	_native->m_wheelRadius = value;
}


RaycastInfo::RaycastInfo(btWheelInfo::RaycastInfo* native)
{
	_native = native;
}

RaycastInfo::RaycastInfo()
{
	_native = new btWheelInfo::RaycastInfo();
}

Vector3 RaycastInfo::ContactNormalWS::get()
{
	return Math::BtVector3ToVector3(&_native->m_contactNormalWS);
}
void RaycastInfo::ContactNormalWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_contactNormalWS);
}

Vector3 RaycastInfo::ContactPointWS::get()
{
	return Math::BtVector3ToVector3(&_native->m_contactPointWS);
}
void RaycastInfo::ContactPointWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_contactPointWS);
}

Object^ RaycastInfo::GroundObject::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)_native->m_groundObject);
}
void RaycastInfo::GroundObject::set(Object^ value)
{
	_native->m_groundObject = GetUnmanagedNullable(static_cast<RigidBody^>(value));
}

Vector3 RaycastInfo::HardPointWS::get()
{
	return Math::BtVector3ToVector3(&_native->m_hardPointWS);
}
void RaycastInfo::HardPointWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hardPointWS);
}

bool RaycastInfo::IsInContact::get()
{
	return _native->m_isInContact;
}
void RaycastInfo::IsInContact::set(bool value)
{
	_native->m_isInContact = value;
}

btScalar RaycastInfo::SuspensionLength::get()
{
	return _native->m_suspensionLength;
}
void RaycastInfo::SuspensionLength::set(btScalar value)
{
	_native->m_suspensionLength = value;
}

Vector3 RaycastInfo::WheelAxleWS::get()
{
	return Math::BtVector3ToVector3(&_native->m_wheelAxleWS);
}
void RaycastInfo::WheelAxleWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_wheelAxleWS);
}

Vector3 RaycastInfo::WheelDirectionWS::get()
{
	return Math::BtVector3ToVector3(&_native->m_wheelDirectionWS);
}
void RaycastInfo::WheelDirectionWS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_wheelDirectionWS);
}


WheelInfo::WheelInfo(btWheelInfo* native)
{
	_native = native;
}

WheelInfo::WheelInfo(WheelInfoConstructionInfo^ ci)
{
	_native = ALIGNED_NEW(btWheelInfo) (*ci->_native);
}

void WheelInfo::UpdateWheel(RigidBody^ chassis, ::RaycastInfo^ raycastInfo)
{
	_native->updateWheel(*(btRigidBody*)chassis->_native, *raycastInfo->_native);
}

btScalar WheelInfo::Brake::get()
{
	return _native->m_brake;
}
void WheelInfo::Brake::set(btScalar value)
{
	_native->m_brake = value;
}

Vector3 WheelInfo::ChassisConnectionPointCS::get()
{
	return Math::BtVector3ToVector3(&_native->m_chassisConnectionPointCS);
}
void WheelInfo::ChassisConnectionPointCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_chassisConnectionPointCS);
}

Object^ WheelInfo::ClientInfo::get()
{
	void* obj = _native->m_clientInfo;
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}
void WheelInfo::ClientInfo::set(Object^ value)
{
	void* obj = _native->m_clientInfo;
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_native->m_clientInfo = GCHandleToVoidPtr(handle);
}

btScalar WheelInfo::ClippedInvContactDotSuspension::get()
{
	return _native->m_clippedInvContactDotSuspension;
}
void WheelInfo::ClippedInvContactDotSuspension::set(btScalar value)
{
	_native->m_clippedInvContactDotSuspension = value;
}

btScalar WheelInfo::DeltaRotation::get()
{
	return _native->m_deltaRotation;
}
void WheelInfo::DeltaRotation::set(btScalar value)
{
	_native->m_deltaRotation = value;
}

btScalar WheelInfo::EngineForce::get()
{
	return _native->m_engineForce;
}
void WheelInfo::EngineForce::set(btScalar value)
{
	_native->m_engineForce = value;
}

btScalar WheelInfo::FrictionSlip::get()
{
	return _native->m_frictionSlip;
}
void WheelInfo::FrictionSlip::set(btScalar value)
{
	_native->m_frictionSlip = value;
}

bool WheelInfo::IsFrontWheel::get()
{
	return _native->m_bIsFrontWheel;
}
void WheelInfo::IsFrontWheel::set(bool value)
{
	_native->m_bIsFrontWheel = value;
}

btScalar WheelInfo::MaxSuspensionForce::get()
{
	return _native->m_maxSuspensionForce;
}
void WheelInfo::MaxSuspensionForce::set(btScalar value)
{
	_native->m_maxSuspensionForce = value;
}

btScalar WheelInfo::MaxSuspensionTravelCm::get()
{
	return _native->m_maxSuspensionTravelCm;
}
void WheelInfo::MaxSuspensionTravelCm::set(btScalar value)
{
	_native->m_maxSuspensionTravelCm = value;
}

#pragma managed(push, off)
void WheelInfo_SetRaycastInfo(btWheelInfo* wheelInfo, btWheelInfo::RaycastInfo* info)
{
	wheelInfo->m_raycastInfo = *info;
}
#pragma managed(pop)
RaycastInfo^ WheelInfo::RaycastInfo::get()
{
	if (!_raycastInfo) {
		_raycastInfo = gcnew ::RaycastInfo(&_native->m_raycastInfo);
	}
	return _raycastInfo;
}
void WheelInfo::RaycastInfo::set(::RaycastInfo^ value)
{
	WheelInfo_SetRaycastInfo(_native, value->_native);
}

btScalar WheelInfo::RollInfluence::get()
{
	return _native->m_rollInfluence;
}
void WheelInfo::RollInfluence::set(btScalar value)
{
	_native->m_rollInfluence = value;
}

btScalar WheelInfo::Rotation::get()
{
	return _native->m_rotation;
}
void WheelInfo::Rotation::set(btScalar value)
{
	_native->m_rotation = value;
}

btScalar WheelInfo::SkidInfo::get()
{
	return _native->m_skidInfo;
}
void WheelInfo::SkidInfo::set(btScalar value)
{
	_native->m_skidInfo = value;
}

btScalar WheelInfo::Steering::get()
{
	return _native->m_steering;
}
void WheelInfo::Steering::set(btScalar value)
{
	_native->m_steering = value;
}

btScalar WheelInfo::SuspensionRelativeVelocity::get()
{
	return _native->m_suspensionRelativeVelocity;
}
void WheelInfo::SuspensionRelativeVelocity::set(btScalar value)
{
	_native->m_suspensionRelativeVelocity = value;
}

btScalar WheelInfo::SuspensionRestLength::get()
{
	return _native->getSuspensionRestLength();
}

btScalar WheelInfo::SuspensionRestLength1::get()
{
	return _native->m_suspensionRestLength1;
}
void WheelInfo::SuspensionRestLength1::set(btScalar value)
{
	_native->m_suspensionRestLength1 = value;
}

btScalar WheelInfo::SuspensionStiffness::get()
{
	return _native->m_suspensionStiffness;
}
void WheelInfo::SuspensionStiffness::set(btScalar value)
{
	_native->m_suspensionStiffness = value;
}

Vector3 WheelInfo::WheelAxleCS::get()
{
	return Math::BtVector3ToVector3(&_native->m_wheelAxleCS);
}
void WheelInfo::WheelAxleCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_wheelAxleCS);
}

btScalar WheelInfo::WheelsDampingCompression::get()
{
	return _native->m_wheelsDampingCompression;
}
void WheelInfo::WheelsDampingCompression::set(btScalar value)
{
	_native->m_wheelsDampingCompression = value;
}

btScalar WheelInfo::WheelsDampingRelaxation::get()
{
	return _native->m_wheelsDampingRelaxation;
}
void WheelInfo::WheelsDampingRelaxation::set(btScalar value)
{
	_native->m_wheelsDampingRelaxation = value;
}

Vector3 WheelInfo::WheelDirectionCS::get()
{
	return  Math::BtVector3ToVector3(&_native->m_wheelDirectionCS);
}
void WheelInfo::WheelDirectionCS::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_wheelDirectionCS);
}

btScalar WheelInfo::WheelsRadius::get()
{
	return _native->m_wheelsRadius;
}
void WheelInfo::WheelsRadius::set(btScalar value)
{
	_native->m_wheelsRadius = value;
}

btScalar WheelInfo::WheelsSuspensionForce::get()
{
	return _native->m_wheelsSuspensionForce;
}
void WheelInfo::WheelsSuspensionForce::set(btScalar value)
{
	_native->m_wheelsSuspensionForce = value;
}

Matrix WheelInfo::WorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->m_worldTransform);
}
void WheelInfo::WorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_worldTransform);
}

#endif