#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "AlignedObjectArray.h"
#include "DynamicsWorld.h"
#include "RaycastVehicle.h"
#include "RigidBody.h"
#include "VehicleRaycaster.h"
#include "WheelInfo.h"

#pragma managed(push, off)
void RaycastVehicle_GetForwardVector(btRaycastVehicle* vehicle, btVector3* forward)
{
	*forward = vehicle->getForwardVector();
}
#pragma managed(pop)

RaycastVehicle::VehicleTuning::VehicleTuning()
{
	_vehicleTuning = new btRaycastVehicle::btVehicleTuning();
}

btScalar RaycastVehicle::VehicleTuning::FrictionSlip::get()
{
	return UnmanagedPointer->m_frictionSlip;
}
void RaycastVehicle::VehicleTuning::FrictionSlip::set(btScalar value)
{
	UnmanagedPointer->m_frictionSlip = value;
}

btScalar RaycastVehicle::VehicleTuning::MaxSuspensionForce::get()
{
	return UnmanagedPointer->m_maxSuspensionForce;
}
void RaycastVehicle::VehicleTuning::MaxSuspensionForce::set(btScalar value)
{
	UnmanagedPointer->m_maxSuspensionForce = value;
}

btScalar RaycastVehicle::VehicleTuning::MaxSuspensionTravelCm::get()
{
	return UnmanagedPointer->m_maxSuspensionTravelCm;
}
void RaycastVehicle::VehicleTuning::MaxSuspensionTravelCm::set(btScalar value)
{
	UnmanagedPointer->m_maxSuspensionTravelCm = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionCompression::get()
{
	return UnmanagedPointer->m_suspensionCompression;
}
void RaycastVehicle::VehicleTuning::SuspensionCompression::set(btScalar value)
{
	UnmanagedPointer->m_suspensionCompression = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionDamping::get()
{
	return UnmanagedPointer->m_suspensionDamping;
}
void RaycastVehicle::VehicleTuning::SuspensionDamping::set(btScalar value)
{
	UnmanagedPointer->m_suspensionDamping = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionStiffness::get()
{
	return UnmanagedPointer->m_suspensionStiffness;
}
void RaycastVehicle::VehicleTuning::SuspensionStiffness::set(btScalar value)
{
	UnmanagedPointer->m_suspensionStiffness = value;
}

btRaycastVehicle::btVehicleTuning* RaycastVehicle::VehicleTuning::UnmanagedPointer::get()
{
	return _vehicleTuning;
}
void RaycastVehicle::VehicleTuning::UnmanagedPointer::set(btRaycastVehicle::btVehicleTuning* value)
{
	_vehicleTuning = value;
}


#define Native (static_cast<btRaycastVehicle*>(_native))

RaycastVehicle::RaycastVehicle(RaycastVehicle::VehicleTuning^ tuning, BulletSharp::RigidBody^ chassis, VehicleRaycaster^ raycaster)
: ActionInterface(new btRaycastVehicle(*tuning->UnmanagedPointer, (btRigidBody*)chassis->_native, raycaster->UnmanagedPointer))
{
	_chassisBody = chassis;
}

WheelInfo^ RaycastVehicle::AddWheel(Vector3 connectionPointCS0, Vector3 wheelDirectionCS0,
	Vector3 wheelAxleCS, btScalar suspensionRestLength,	btScalar wheelRadius,
	VehicleTuning^ tuning, bool isFrontWheel)
{
	VECTOR3_DEF(connectionPointCS0);
	VECTOR3_DEF(wheelDirectionCS0);
	VECTOR3_DEF(wheelAxleCS);

	btWheelInfo* wheelInfo = &Native->addWheel(VECTOR3_USE(connectionPointCS0),
		VECTOR3_USE(wheelDirectionCS0), VECTOR3_USE(wheelAxleCS), suspensionRestLength, wheelRadius,
		*tuning->UnmanagedPointer, isFrontWheel);
	
	VECTOR3_DEL(connectionPointCS0);
	VECTOR3_DEL(wheelDirectionCS0);
	VECTOR3_DEL(wheelAxleCS);

	return gcnew BulletSharp::WheelInfo(wheelInfo);
}

void RaycastVehicle::ApplyEngineForce(btScalar force, int wheel)
{
	Native->applyEngineForce(force, wheel);
}

WheelInfo^ RaycastVehicle::GetWheelInfo(int index)
{
	return gcnew BulletSharp::WheelInfo(&Native->getWheelInfo(index));
}

btScalar RaycastVehicle::GetSteeringValue(int wheel)
{
	return Native->getSteeringValue(wheel);
}
void RaycastVehicle::SetSteeringValue(btScalar steering, int wheel)
{
	Native->setSteeringValue(steering, wheel);
}

Matrix RaycastVehicle::GetWheelTransformWS(int wheelIndex)
{
	return Math::BtTransformToMatrix(&Native->getWheelTransformWS(wheelIndex));
}

btScalar RaycastVehicle::RayCast(BulletSharp::WheelInfo^ wheel)
{
	return Native->rayCast(*wheel->_native);
}

void RaycastVehicle::ResetSuspension()
{
	Native->resetSuspension();
}

void RaycastVehicle::SetBrake(btScalar brake, int wheelIndex)
{
	Native->setBrake(brake, wheelIndex);
}

void RaycastVehicle::SetCoordinateSystem(int rightIndex, int upIndex, int forwardIndex)
{
	Native->setCoordinateSystem(rightIndex, upIndex, forwardIndex);
}

void RaycastVehicle::SetPitchControl(btScalar pitch)
{
	Native->setPitchControl(pitch);
}

/*
void RaycastVehicle::SetRaycastWheelInfo(int wheelIndex, bool isInContact, Vector3 hitPoint, Vector3 hitNormal, btScalar depth)
{
	VECTOR3_DEF(hitPoint);
	VECTOR3_DEF(hitNormal);

	Native->setRaycastWheelInfo(wheelIndex, isInContact, VECTOR3_USE(hitPoint), VECTOR3_USE(hitNormal), depth);

	VECTOR3_DEL(hitPoint);
	VECTOR3_DEL(hitNormal);
}
*/
void RaycastVehicle::UpdateFriction(btScalar timeStep)
{
	Native->updateFriction(timeStep);
}

void RaycastVehicle::UpdateSuspension(btScalar deltaTime)
{
	Native->updateSuspension(deltaTime);
}

void RaycastVehicle::UpdateVehicle(btScalar step)
{
	Native->updateVehicle(step);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex, bool interpolatedTransform)
{
	Native->updateWheelTransform(wheelIndex, interpolatedTransform);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex)
{
	Native->updateWheelTransform(wheelIndex);
}

void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheelIndex, bool interpolatedTransform)
{
	Native->updateWheelTransformsWS(*wheelIndex->_native, interpolatedTransform);
}

void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheelIndex)
{
	Native->updateWheelTransformsWS(*wheelIndex->_native);
}

Matrix RaycastVehicle::ChassisWorldTransform::get()
{
	return Math::BtTransformToMatrix(&Native->getChassisWorldTransform());
}

btScalar RaycastVehicle::CurrentSpeedKmHour::get()
{
	return Native->getCurrentSpeedKmHour();
}

int RaycastVehicle::ForwardAxis::get()
{
	return Native->getForwardAxis();
}

Vector3 RaycastVehicle::ForwardVector::get()
{
	btVector3* vectorTemp = new btVector3;
	RaycastVehicle_GetForwardVector(Native, vectorTemp);
	Vector3 vector = Math::BtVector3ToVector3(vectorTemp);
	delete vectorTemp;
	return vector;
}

int RaycastVehicle::NumWheels::get()
{
	return Native->getNumWheels();
}

int RaycastVehicle::RightAxis::get()
{
	return Native->getRightAxis();
}

RigidBody^ RaycastVehicle::RigidBody::get()
{
	return _chassisBody;
}

int RaycastVehicle::UpAxis::get()
{
	return Native->getUpAxis();
}

AlignedWheelInfoArray^ RaycastVehicle::WheelInfo::get()
{
	return gcnew AlignedWheelInfoArray(&Native->m_wheelInfo);
}


DefaultVehicleRaycaster::DefaultVehicleRaycaster(DynamicsWorld^ world)
: VehicleRaycaster(new btDefaultVehicleRaycaster(world->UnmanagedPointer))
{
}

#endif
