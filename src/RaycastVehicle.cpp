#include "StdAfx.h"

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

RaycastVehicle::RaycastVehicle(RaycastVehicle::VehicleTuning^ tuning, BulletSharp::RigidBody^ chassis, VehicleRaycaster^ raycaster)
: ActionInterface(new btRaycastVehicle(*tuning->UnmanagedPointer, chassis->UnmanagedPointer, raycaster->UnmanagedPointer))
{
	_chassisBody = chassis;
}

RaycastVehicle::VehicleTuning::VehicleTuning()
{
	_vehicleTuning = new btRaycastVehicle::btVehicleTuning();
}

btRaycastVehicle::btVehicleTuning* RaycastVehicle::VehicleTuning::UnmanagedPointer::get()
{
	return _vehicleTuning;
}
void RaycastVehicle::VehicleTuning::UnmanagedPointer::set(btRaycastVehicle::btVehicleTuning* value)
{
	_vehicleTuning = value;
}

WheelInfo^ RaycastVehicle::AddWheel(Vector3 connectionPointCS0, Vector3 wheelDirectionCS0,
	Vector3 wheelAxleCS, btScalar suspensionRestLength,	btScalar wheelRadius,
	VehicleTuning^ tuning, bool isFrontWheel)
{
	btWheelInfo* wheelInfo = &UnmanagedPointer->addWheel(
		*Math::Vector3ToBtVec3(connectionPointCS0),
		*Math::Vector3ToBtVec3(wheelDirectionCS0),
		*Math::Vector3ToBtVec3(wheelAxleCS),
		suspensionRestLength, wheelRadius, *tuning->UnmanagedPointer, isFrontWheel);
	return gcnew WheelInfo(wheelInfo);
}

void RaycastVehicle::ApplyEngineForce(btScalar force, int wheel)
{
	UnmanagedPointer->applyEngineForce(force, wheel);
}

WheelInfo^ RaycastVehicle::GetWheelInfo(int index)
{
	return gcnew WheelInfo(&UnmanagedPointer->getWheelInfo(index));
}

btScalar RaycastVehicle::GetSteeringValue(int wheel)
{
	return UnmanagedPointer->getSteeringValue(wheel);
}
void RaycastVehicle::SetSteeringValue(btScalar steering, int wheel)
{
	UnmanagedPointer->setSteeringValue(steering, wheel);
}

Matrix RaycastVehicle::GetWheelTransformWS(int wheelIndex)
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getWheelTransformWS(wheelIndex));
}

void RaycastVehicle::ResetSuspension()
{
	UnmanagedPointer->resetSuspension();
}

void RaycastVehicle::SetBrake(btScalar brake, int wheelIndex)
{
	UnmanagedPointer->setBrake(brake, wheelIndex);
}

void RaycastVehicle::SetCoordinateSystem(int rightIndex, int upIndex, int forwardIndex)
{
	UnmanagedPointer->setCoordinateSystem(rightIndex, upIndex, forwardIndex);
}
/*
void RaycastVehicle::SetRaycastWheelInfo(int wheelIndex, bool isInContact, Vector3 hitPoint, Vector3 hitNormal, btScalar depth)
{
	UnmanagedPointer->setRaycastWheelInfo(wheelIndex, isInContact, *Math::Vector3ToBtVec3(hitPoint), *Math::Vector3ToBtVec3(hitNormal), depth);
}
*/
void RaycastVehicle::UpdateFriction(btScalar timeStep)
{
	UnmanagedPointer->updateFriction(timeStep);
}

void RaycastVehicle::UpdateSuspension(btScalar deltaTime)
{
	UnmanagedPointer->updateSuspension(deltaTime);
}

void RaycastVehicle::UpdateVehicle(btScalar step)
{
	UnmanagedPointer->updateVehicle(step);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex)
{
	UnmanagedPointer->updateWheelTransform(wheelIndex);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex, bool interpolatedTransform)
{
	UnmanagedPointer->updateWheelTransform(wheelIndex, interpolatedTransform);
}

Matrix RaycastVehicle::ChassisWorldTransform::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getChassisWorldTransform());
}

btScalar RaycastVehicle::CurrentSpeedKmHour::get()
{
	return UnmanagedPointer->getCurrentSpeedKmHour();
}

int RaycastVehicle::ForwardAxis::get()
{
	return UnmanagedPointer->getForwardAxis();
}

Vector3 RaycastVehicle::ForwardVector::get()
{
	btVector3* forward = new btVector3;
	RaycastVehicle_GetForwardVector(UnmanagedPointer, forward);
	Vector3 v = Math::BtVec3ToVector3(forward);
	delete forward;
	return v;
}

int RaycastVehicle::NumWheels::get()
{
	return UnmanagedPointer->getNumWheels();
}

void RaycastVehicle::PitchControl::set(btScalar value)
{
	UnmanagedPointer->setPitchControl(value);
}

int RaycastVehicle::RightAxis::get()
{
	return UnmanagedPointer->getRightAxis();
}

RigidBody^ RaycastVehicle::RigidBody::get()
{
	return _chassisBody;
}

int RaycastVehicle::UpAxis::get()
{
	return UnmanagedPointer->getUpAxis();
}

btRaycastVehicle* RaycastVehicle::UnmanagedPointer::get()
{
	return (btRaycastVehicle*)ActionInterface::UnmanagedPointer;
}
