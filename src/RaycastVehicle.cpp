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

RaycastVehicle::RaycastVehicle(RaycastVehicle::VehicleTuning^ tuning, BulletSharp::RigidBody^ chassis, VehicleRaycaster^ raycaster)
: ActionInterface(new btRaycastVehicle(*tuning->UnmanagedPointer, chassis->UnmanagedPointer, raycaster->UnmanagedPointer))
{
	_chassisBody = chassis;
}

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

WheelInfo^ RaycastVehicle::AddWheel(Vector3 connectionPointCS0, Vector3 wheelDirectionCS0,
	Vector3 wheelAxleCS, btScalar suspensionRestLength,	btScalar wheelRadius,
	VehicleTuning^ tuning, bool isFrontWheel)
{
	btVector3* connectionPointCS0Temp = Math::Vector3ToBtVector3(connectionPointCS0);
	btVector3* wheelDirectionCS0Temp = Math::Vector3ToBtVector3(wheelDirectionCS0);
	btVector3* wheelAxleCSTemp = Math::Vector3ToBtVector3(wheelAxleCS);

	btWheelInfo* wheelInfo = &UnmanagedPointer->addWheel(*connectionPointCS0Temp,
		*wheelDirectionCS0Temp,	*wheelAxleCSTemp, suspensionRestLength, wheelRadius,
		*tuning->UnmanagedPointer, isFrontWheel);
	
	delete connectionPointCS0Temp;
	delete wheelDirectionCS0Temp;
	delete wheelAxleCSTemp;

	return gcnew BulletSharp::WheelInfo(wheelInfo);
}

void RaycastVehicle::ApplyEngineForce(btScalar force, int wheel)
{
	UnmanagedPointer->applyEngineForce(force, wheel);
}

WheelInfo^ RaycastVehicle::GetWheelInfo(int index)
{
	return gcnew BulletSharp::WheelInfo(&UnmanagedPointer->getWheelInfo(index));
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

btScalar RaycastVehicle::RayCast(BulletSharp::WheelInfo^ wheel)
{
	return UnmanagedPointer->rayCast(*wheel->UnmanagedPointer);
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

void RaycastVehicle::SetPitchControl(btScalar pitch)
{
	UnmanagedPointer->setPitchControl(pitch);
}

/*
void RaycastVehicle::SetRaycastWheelInfo(int wheelIndex, bool isInContact, Vector3 hitPoint, Vector3 hitNormal, btScalar depth)
{
	btVector3* hitPointTemp = Math::Vector3ToBtVector3(hitPoint);
	btVector3* hitNormalTemp = Math::Vector3ToBtVector3(hitNormal);

	UnmanagedPointer->setRaycastWheelInfo(wheelIndex, isInContact, *hitPointTemp, *hitNormalTemp, depth);

	delete hitPointTemp;
	delete hitNormalTemp;
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

void RaycastVehicle::UpdateWheelTransform(int wheelIndex, bool interpolatedTransform)
{
	UnmanagedPointer->updateWheelTransform(wheelIndex, interpolatedTransform);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex)
{
	UnmanagedPointer->updateWheelTransform(wheelIndex);
}

void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheelIndex, bool interpolatedTransform)
{
	UnmanagedPointer->updateWheelTransformsWS(*wheelIndex->UnmanagedPointer, interpolatedTransform);
}

void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheelIndex)
{
	UnmanagedPointer->updateWheelTransformsWS(*wheelIndex->UnmanagedPointer);
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
	btVector3* vectorTemp = new btVector3;
	RaycastVehicle_GetForwardVector(UnmanagedPointer, vectorTemp);
	Vector3 vector = Math::BtVector3ToVector3(vectorTemp);
	delete vectorTemp;
	return vector;
}

int RaycastVehicle::NumWheels::get()
{
	return UnmanagedPointer->getNumWheels();
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

AlignedWheelInfoArray^ RaycastVehicle::WheelInfo::get()
{
	return gcnew AlignedWheelInfoArray(&UnmanagedPointer->m_wheelInfo);
}

btRaycastVehicle* RaycastVehicle::UnmanagedPointer::get()
{
	return (btRaycastVehicle*)ActionInterface::UnmanagedPointer;
}


DefaultVehicleRaycaster::DefaultVehicleRaycaster(DynamicsWorld^ world)
: VehicleRaycaster(new btDefaultVehicleRaycaster(world->UnmanagedPointer))
{
}

#endif
