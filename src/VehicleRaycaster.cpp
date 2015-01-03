#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "RigidBody.h"
#include "VehicleRaycaster.h"

VehicleRaycasterResult::~VehicleRaycasterResult()
{
	this->!VehicleRaycasterResult();
}

VehicleRaycasterResult::!VehicleRaycasterResult()
{
	ALIGNED_FREE(_native);
	_native = NULL;
}

VehicleRaycasterResult::VehicleRaycasterResult()
{
	_native = ALIGNED_NEW(btVehicleRaycaster::btVehicleRaycasterResult) ();
}

btScalar VehicleRaycasterResult::DistFraction::get()
{
	return _native->m_distFraction;
}
void VehicleRaycasterResult::DistFraction::set(btScalar value)
{
	_native->m_distFraction = value;
}

Vector3 VehicleRaycasterResult::HitNormalInWorld::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitNormalInWorld);
}
void VehicleRaycasterResult::HitNormalInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitNormalInWorld);
}

Vector3 VehicleRaycasterResult::HitPointInWorld::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitPointInWorld);
}
void VehicleRaycasterResult::HitPointInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitPointInWorld);
}

#endif
