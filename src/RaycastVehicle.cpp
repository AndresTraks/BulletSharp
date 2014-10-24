#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "AlignedObjectArray.h"
#include "DynamicsWorld.h"
#include "RaycastVehicle.h"
#include "RigidBody.h"
#include "WheelInfo.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

RaycastVehicle::VehicleTuning::~VehicleTuning()
{
	this->!VehicleTuning();
}

RaycastVehicle::VehicleTuning::!VehicleTuning()
{
	delete _native;
	_native = NULL;
}

RaycastVehicle::VehicleTuning::VehicleTuning()
{
	_native = new btRaycastVehicle::btVehicleTuning();
}

btScalar RaycastVehicle::VehicleTuning::FrictionSlip::get()
{
	return _native->m_frictionSlip;
}
void RaycastVehicle::VehicleTuning::FrictionSlip::set(btScalar value)
{
	_native->m_frictionSlip = value;
}

btScalar RaycastVehicle::VehicleTuning::MaxSuspensionForce::get()
{
	return _native->m_maxSuspensionForce;
}
void RaycastVehicle::VehicleTuning::MaxSuspensionForce::set(btScalar value)
{
	_native->m_maxSuspensionForce = value;
}

btScalar RaycastVehicle::VehicleTuning::MaxSuspensionTravelCm::get()
{
	return _native->m_maxSuspensionTravelCm;
}
void RaycastVehicle::VehicleTuning::MaxSuspensionTravelCm::set(btScalar value)
{
	_native->m_maxSuspensionTravelCm = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionCompression::get()
{
	return _native->m_suspensionCompression;
}
void RaycastVehicle::VehicleTuning::SuspensionCompression::set(btScalar value)
{
	_native->m_suspensionCompression = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionDamping::get()
{
	return _native->m_suspensionDamping;
}
void RaycastVehicle::VehicleTuning::SuspensionDamping::set(btScalar value)
{
	_native->m_suspensionDamping = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionStiffness::get()
{
	return _native->m_suspensionStiffness;
}
void RaycastVehicle::VehicleTuning::SuspensionStiffness::set(btScalar value)
{
	_native->m_suspensionStiffness = value;
}


RaycastVehicle::RaycastVehicle(RaycastVehicle::VehicleTuning^ tuning, BulletSharp::RigidBody^ chassis, VehicleRaycaster^ raycaster)
{
	_native = new btRaycastVehicle(*tuning->_native, (btRigidBody*)chassis->_native, raycaster->_native);
	_chassisBody = chassis;
	_tuning = tuning;
	_raycaster = raycaster;
}

RaycastVehicle::~RaycastVehicle()
{
	this->!RaycastVehicle();
}

RaycastVehicle::!RaycastVehicle()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

WheelInfo^ RaycastVehicle::AddWheel(Vector3 connectionPointCS0, Vector3 wheelDirectionCS0,
	Vector3 wheelAxleCS, btScalar suspensionRestLength, btScalar wheelRadius, VehicleTuning^ tuning,
	bool isFrontWheel)
{
	VECTOR3_CONV(connectionPointCS0);
	VECTOR3_CONV(wheelDirectionCS0);
	VECTOR3_CONV(wheelAxleCS);
	btWheelInfo* ret = &_native->addWheel(VECTOR3_USE(connectionPointCS0), VECTOR3_USE(wheelDirectionCS0),
		VECTOR3_USE(wheelAxleCS), suspensionRestLength, wheelRadius, *tuning->_native,
		isFrontWheel);
	VECTOR3_DEL(connectionPointCS0);
	VECTOR3_DEL(wheelDirectionCS0);
	VECTOR3_DEL(wheelAxleCS);
	return gcnew BulletSharp::WheelInfo(ret, true);
}

void RaycastVehicle::ApplyEngineForce(btScalar force, int wheel)
{
	_native->applyEngineForce(force, wheel);
}

#ifndef DISABLE_DEBUGDRAW
void RaycastVehicle::DebugDraw(IDebugDraw^ debugDrawer)
{
	_native->debugDraw(DebugDraw::GetUnmanaged(debugDrawer));
}
#endif

btScalar RaycastVehicle::GetSteeringValue(int wheel)
{
	return _native->getSteeringValue(wheel);
}

WheelInfo^ RaycastVehicle::GetWheelInfo(int index)
{
	return gcnew BulletSharp::WheelInfo(&_native->getWheelInfo(index), true);
}

Matrix RaycastVehicle::GetWheelTransformWS(int wheelIndex)
{
	return Math::BtTransformToMatrix(&_native->getWheelTransformWS(wheelIndex));
}

btScalar RaycastVehicle::RayCast(BulletSharp::WheelInfo^ wheel)
{
	return _native->rayCast(*wheel->_native);
}

void RaycastVehicle::ResetSuspension()
{
	_native->resetSuspension();
}

void RaycastVehicle::SetBrake(btScalar brake, int wheelIndex)
{
	_native->setBrake(brake, wheelIndex);
}

void RaycastVehicle::SetCoordinateSystem(int rightIndex, int upIndex, int forwardIndex)
{
	_native->setCoordinateSystem(rightIndex, upIndex, forwardIndex);
}

void RaycastVehicle::SetPitchControl(btScalar pitch)
{
	_native->setPitchControl(pitch);
}

void RaycastVehicle::SetSteeringValue(btScalar steering, int wheel)
{
	_native->setSteeringValue(steering, wheel);
}

void RaycastVehicle::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep)
{
	_native->updateAction(collisionWorld->_native, deltaTimeStep);
}

void RaycastVehicle::UpdateFriction(btScalar timeStep)
{
	_native->updateFriction(timeStep);
}

void RaycastVehicle::UpdateSuspension(btScalar deltaTime)
{
	_native->updateSuspension(deltaTime);
}

void RaycastVehicle::UpdateVehicle(btScalar step)
{
	_native->updateVehicle(step);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex, bool interpolatedTransform)
{
	_native->updateWheelTransform(wheelIndex, interpolatedTransform);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex)
{
	_native->updateWheelTransform(wheelIndex);
}

void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheel, bool interpolatedTransform)
{
	_native->updateWheelTransformsWS(*wheel->_native, interpolatedTransform);
}

void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheel)
{
	_native->updateWheelTransformsWS(*wheel->_native);
}

Matrix RaycastVehicle::ChassisWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->getChassisWorldTransform());
}

btScalar RaycastVehicle::CurrentSpeedKmHour::get()
{
	return _native->getCurrentSpeedKmHour();
}

int RaycastVehicle::ForwardAxis::get()
{
	return _native->getForwardAxis();
}

#pragma managed(push, off)
void RaycastVehicle_GetForwardVector(btRaycastVehicle* vehicle, btVector3* forward)
{
	*forward = vehicle->getForwardVector();
}
#pragma managed(pop)

Vector3 RaycastVehicle::ForwardVector::get()
{
	btVector3* vectorTemp = ALIGNED_NEW(btVector3);
	RaycastVehicle_GetForwardVector(_native, vectorTemp);
	Vector3 vector = Math::BtVector3ToVector3(vectorTemp);
	ALIGNED_FREE(vectorTemp);
	return vector;
}

bool RaycastVehicle::IsDisposed::get()
{
	return ( _native == NULL );
}

int RaycastVehicle::NumWheels::get()
{
	return _native->getNumWheels();
}

int RaycastVehicle::RightAxis::get()
{
	return _native->getRightAxis();
}

RigidBody^ RaycastVehicle::RigidBody::get()
{
	return _chassisBody;
}

RaycastVehicle::VehicleTuning^ RaycastVehicle::Tuning::get()
{
	return _tuning;
}

VehicleRaycaster^ RaycastVehicle::Raycaster::get()
{
	return _raycaster;
}

int RaycastVehicle::UpAxis::get()
{
	return _native->getUpAxis();
}

AlignedWheelInfoArray^ RaycastVehicle::WheelInfo::get()
{
	return gcnew AlignedWheelInfoArray(&_native->m_wheelInfo);
}


DefaultVehicleRaycaster::DefaultVehicleRaycaster(DynamicsWorld^ world)
	: VehicleRaycaster(new btDefaultVehicleRaycaster((btDynamicsWorld*)world->_native))
{
}

#endif
