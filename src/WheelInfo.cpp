#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "RigidBody.h"
#include "WheelInfo.h"

Vector3 WheelInfoConstructionInfo::ChassisConnectionCS::get()
{
	return _chassisConnectionCS;
}
void WheelInfoConstructionInfo::ChassisConnectionCS::set(Vector3 value)
{
	_chassisConnectionCS = value;
}

btScalar WheelInfoConstructionInfo::FrictionSlip::get()
{
	return _frictionSlip;
}
void WheelInfoConstructionInfo::FrictionSlip::set(btScalar value)
{
	_frictionSlip = value;
}

bool WheelInfoConstructionInfo::IsFrontWheel::get()
{
	return _isFrontWheel;
}
void WheelInfoConstructionInfo::IsFrontWheel::set(bool value)
{
	_isFrontWheel = value;
}

btScalar WheelInfoConstructionInfo::MaxSuspensionForce::get()
{
	return _maxSuspensionForce;
}
void WheelInfoConstructionInfo::MaxSuspensionForce::set(btScalar value)
{
	_maxSuspensionForce = value;
}

btScalar WheelInfoConstructionInfo::MaxSuspensionTravelCm::get()
{
	return _maxSuspensionTravelCm;
}
void WheelInfoConstructionInfo::MaxSuspensionTravelCm::set(btScalar value)
{
	_maxSuspensionTravelCm = value;
}

btScalar WheelInfoConstructionInfo::SuspensionRestLength::get()
{
	return _suspensionRestLength;
}
void WheelInfoConstructionInfo::SuspensionRestLength::set(btScalar value)
{
	_suspensionRestLength = value;
}

btScalar WheelInfoConstructionInfo::SuspensionStiffness::get()
{
	return _suspensionStiffness;
}
void WheelInfoConstructionInfo::SuspensionStiffness::set(btScalar value)
{
	_suspensionStiffness = value;
}

Vector3 WheelInfoConstructionInfo::WheelAxleCS::get()
{
	return _wheelAxleCS;
}
void WheelInfoConstructionInfo::WheelAxleCS::set(Vector3 value)
{
	_wheelAxleCS = value;
}

Vector3 WheelInfoConstructionInfo::WheelDirectionCS::get()
{
	return _wheelDirectionCS;
}
void WheelInfoConstructionInfo::WheelDirectionCS::set(Vector3 value)
{
	_wheelDirectionCS = value;
}

btScalar WheelInfoConstructionInfo::WheelRadius::get()
{
	return _wheelRadius;
}
void WheelInfoConstructionInfo::WheelRadius::set(btScalar value)
{
	_wheelRadius = value;
}

btScalar WheelInfoConstructionInfo::WheelsDampingCompression::get()
{
	return _wheelsDampingCompression;
}
void WheelInfoConstructionInfo::WheelsDampingCompression::set(btScalar value)
{
	_wheelsDampingCompression = value;
}

btScalar WheelInfoConstructionInfo::WheelsDampingRelaxation::get()
{
	return _wheelsDampingRelaxation;
}
void WheelInfoConstructionInfo::WheelsDampingRelaxation::set(btScalar value)
{
	_wheelsDampingRelaxation = value;
}


WheelInfo::WheelInfo(WheelInfoConstructionInfo^ ci)
{
	_suspensionRestLength1 = ci->SuspensionRestLength;
	_maxSuspensionTravelCm = ci->MaxSuspensionTravelCm;

	_wheelsRadius = ci->WheelRadius;
	_suspensionStiffness = ci->SuspensionStiffness;
	_wheelsDampingCompression = ci->WheelsDampingCompression;
	_wheelsDampingRelaxation = ci->WheelsDampingRelaxation;
	_chassisConnectionPointCS = ci->ChassisConnectionCS;
	_wheelDirectionCS = ci->WheelDirectionCS;
	_wheelAxleCS = ci->WheelAxleCS;
	_frictionSlip = ci->FrictionSlip;
	_steering = btScalar(0.);
	_engineForce = btScalar(0.);
	_rotation = btScalar(0.);
	_deltaRotation = btScalar(0.);
	_brake = btScalar(0.);
	_rollInfluence = btScalar(0.1);
	_isFrontWheel = ci->IsFrontWheel;
	_maxSuspensionForce = ci->MaxSuspensionForce;
}

void WheelInfo::UpdateWheel(RigidBody^ chassis, ::RaycastInfo^ raycastInfo)
{
	if (RaycastInfo.IsInContact)
	{
		btScalar project = Vector3_Dot(RaycastInfo.ContactNormalWS, RaycastInfo.WheelDirectionWS);
		Vector3 relpos = RaycastInfo.ContactPointWS - chassis->CenterOfMassPosition;
		Vector3 chassis_velocity_at_contactPoint = chassis->GetVelocityInLocalPoint(relpos);
		btScalar projVel = Vector3_Dot(RaycastInfo.ContactNormalWS, chassis_velocity_at_contactPoint);
		if ( project >= btScalar(-0.1))
		{
			_suspensionRelativeVelocity = btScalar(0.0);
			_clippedInvContactDotSuspension = btScalar(1.0) / btScalar(0.1);
		}
		else
		{
			btScalar inv = btScalar(-1.) / project;
			_suspensionRelativeVelocity = projVel * inv;
			_clippedInvContactDotSuspension = inv;
		}
		
	}

	else	// Not in contact : position wheel in a nice (rest length) position
	{
		RaycastInfo.SuspensionLength = SuspensionRestLength;
		_suspensionRelativeVelocity = btScalar(0.0);
		RaycastInfo.ContactNormalWS = -RaycastInfo.WheelDirectionWS;
		_clippedInvContactDotSuspension = btScalar(1.0);
	}
}

btScalar WheelInfo::Brake::get()
{
	return _brake;
}
void WheelInfo::Brake::set(btScalar value)
{
	_brake = value;
}

Vector3 WheelInfo::ChassisConnectionPointCS::get()
{
	return _chassisConnectionPointCS;
}
void WheelInfo::ChassisConnectionPointCS::set(Vector3 value)
{
	_chassisConnectionPointCS = value;
}

Object^ WheelInfo::ClientInfo::get()
{
	return _clientInfo;
}
void WheelInfo::ClientInfo::set(Object^ value)
{
	_clientInfo = value;
}

btScalar WheelInfo::ClippedInvContactDotSuspension::get()
{
	return _clippedInvContactDotSuspension;
}
void WheelInfo::ClippedInvContactDotSuspension::set(btScalar value)
{
	_clippedInvContactDotSuspension = value;
}

btScalar WheelInfo::DeltaRotation::get()
{
	return _deltaRotation;
}
void WheelInfo::DeltaRotation::set(btScalar value)
{
	_deltaRotation = value;
}

btScalar WheelInfo::EngineForce::get()
{
	return _engineForce;
}
void WheelInfo::EngineForce::set(btScalar value)
{
	_engineForce = value;
}

btScalar WheelInfo::FrictionSlip::get()
{
	return _frictionSlip;
}
void WheelInfo::FrictionSlip::set(btScalar value)
{
	_frictionSlip = value;
}

bool WheelInfo::IsFrontWheel::get()
{
	return _isFrontWheel;
}
void WheelInfo::IsFrontWheel::set(bool value)
{
	_isFrontWheel = value;
}

btScalar WheelInfo::MaxSuspensionForce::get()
{
	return _maxSuspensionForce;
}
void WheelInfo::MaxSuspensionForce::set(btScalar value)
{
	_maxSuspensionForce = value;
}

btScalar WheelInfo::MaxSuspensionTravelCm::get()
{
	return _maxSuspensionTravelCm;
}
void WheelInfo::MaxSuspensionTravelCm::set(btScalar value)
{
	_maxSuspensionTravelCm = value;
}

btScalar WheelInfo::RollInfluence::get()
{
	return _rollInfluence;
}
void WheelInfo::RollInfluence::set(btScalar value)
{
	_rollInfluence = value;
}

btScalar WheelInfo::Rotation::get()
{
	return _rotation;
}
void WheelInfo::Rotation::set(btScalar value)
{
	_rotation = value;
}

btScalar WheelInfo::SkidInfo::get()
{
	return _skidInfo;
}
void WheelInfo::SkidInfo::set(btScalar value)
{
	_skidInfo = value;
}

btScalar WheelInfo::Steering::get()
{
	return _steering;
}
void WheelInfo::Steering::set(btScalar value)
{
	_steering = value;
}

btScalar WheelInfo::SuspensionRelativeVelocity::get()
{
	return _suspensionRelativeVelocity;
}
void WheelInfo::SuspensionRelativeVelocity::set(btScalar value)
{
	_suspensionRelativeVelocity = value;
}

btScalar WheelInfo::SuspensionRestLength::get()
{
	return _suspensionRestLength1;
}

btScalar WheelInfo::SuspensionRestLength1::get()
{
	return _suspensionRestLength1;
}
void WheelInfo::SuspensionRestLength1::set(btScalar value)
{
	_suspensionRestLength1 = value;
}

btScalar WheelInfo::SuspensionStiffness::get()
{
	return _suspensionStiffness;
}
void WheelInfo::SuspensionStiffness::set(btScalar value)
{
	_suspensionStiffness = value;
}

Vector3 WheelInfo::WheelAxleCS::get()
{
	return _wheelAxleCS;
}
void WheelInfo::WheelAxleCS::set(Vector3 value)
{
	_wheelAxleCS = value;
}

Vector3 WheelInfo::WheelDirectionCS::get()
{
	return _wheelDirectionCS;
}
void WheelInfo::WheelDirectionCS::set(Vector3 value)
{
	_wheelDirectionCS = value;
}

btScalar WheelInfo::WheelsDampingCompression::get()
{
	return _wheelsDampingCompression;
}
void WheelInfo::WheelsDampingCompression::set(btScalar value)
{
	_wheelsDampingCompression = value;
}

btScalar WheelInfo::WheelsDampingRelaxation::get()
{
	return _wheelsDampingRelaxation;
}
void WheelInfo::WheelsDampingRelaxation::set(btScalar value)
{
	_wheelsDampingRelaxation = value;
}

btScalar WheelInfo::WheelsRadius::get()
{
	return _wheelsRadius;
}
void WheelInfo::WheelsRadius::set(btScalar value)
{
	_wheelsRadius = value;
}

btScalar WheelInfo::WheelsSuspensionForce::get()
{
	return _wheelsSuspensionForce;
}
void WheelInfo::WheelsSuspensionForce::set(btScalar value)
{
	_wheelsSuspensionForce = value;
}

Matrix WheelInfo::WorldTransform::get()
{
	return _worldTransform;
}
void WheelInfo::WorldTransform::set(Matrix value)
{
	_worldTransform = value;
}

#endif
