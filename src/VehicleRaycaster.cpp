#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "RigidBody.h"
#include "VehicleRaycaster.h"

VehicleRaycaster::VehicleRaycasterResult::VehicleRaycasterResult()
{
	_result = new btVehicleRaycaster::btVehicleRaycasterResult();
}

btScalar VehicleRaycaster::VehicleRaycasterResult::DistFraction::get()
{
	return _result->m_distFraction;
}
void VehicleRaycaster::VehicleRaycasterResult::DistFraction::set(btScalar value)
{
	_result->m_distFraction = value;
}

Vector3 VehicleRaycaster::VehicleRaycasterResult::HitNormalInWorld::get()
{
	return Math::BtVector3ToVector3(&_result->m_hitNormalInWorld);
}
void VehicleRaycaster::VehicleRaycasterResult::HitNormalInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_result->m_hitNormalInWorld);
}

Vector3 VehicleRaycaster::VehicleRaycasterResult::HitPointInWorld::get()
{
	return Math::BtVector3ToVector3(&_result->m_hitPointInWorld);
}
void VehicleRaycaster::VehicleRaycasterResult::HitPointInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_result->m_hitPointInWorld);
}

btVehicleRaycaster::btVehicleRaycasterResult* VehicleRaycaster::VehicleRaycasterResult::UnmanagedPointer::get()
{
	return _result;
}
void VehicleRaycaster::VehicleRaycasterResult::UnmanagedPointer::set(btVehicleRaycaster::btVehicleRaycasterResult* value)
{
	_result = value;
}


VehicleRaycaster::VehicleRaycaster(btVehicleRaycaster* vehicleRaycaster)
{
	_vehicleRaycaster = vehicleRaycaster;
}

Object^ VehicleRaycaster::CastRay(Vector3 from, Vector3 to, VehicleRaycasterResult^ result)
{
	void* ret = _vehicleRaycaster->castRay(*Math::Vector3ToBtVector3(to), *Math::Vector3ToBtVector3(to),
		*result->UnmanagedPointer);

	if (ret = 0)
		return nullptr;

	return gcnew RigidBody((btRigidBody*)ret);
}

btVehicleRaycaster* VehicleRaycaster::UnmanagedPointer::get()
{
	return _vehicleRaycaster;
}
void VehicleRaycaster::UnmanagedPointer::set(btVehicleRaycaster* value)
{
	_vehicleRaycaster = value;
}

#endif
