#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#define ROLLING_INFLUENCE_FIX

#include <BulletDynamics/ConstraintSolver/btContactConstraint.h> // resolveSingleBilateral
#include "AlignedObjectArray.h"
#include "DynamicsWorld.h"
#include "MotionState.h"
#include "RaycastVehicle.h"
#include "RigidBody.h"
#include "WheelInfo.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

RaycastVehicle::VehicleTuning::VehicleTuning()
{
	_suspensionStiffness = btScalar(5.88);
	_suspensionCompression = btScalar(0.83);
	_suspensionDamping = btScalar(0.88);
	_maxSuspensionTravelCm = btScalar(500.0);
	_frictionSlip = btScalar(10.5);
	_maxSuspensionForce = btScalar(6000.0);
}

btScalar RaycastVehicle::VehicleTuning::FrictionSlip::get()
{
	return _frictionSlip;
}
void RaycastVehicle::VehicleTuning::FrictionSlip::set(btScalar value)
{
	_frictionSlip = value;
}

btScalar RaycastVehicle::VehicleTuning::MaxSuspensionForce::get()
{
	return _maxSuspensionForce;
}
void RaycastVehicle::VehicleTuning::MaxSuspensionForce::set(btScalar value)
{
	_maxSuspensionForce = value;
}

btScalar RaycastVehicle::VehicleTuning::MaxSuspensionTravelCm::get()
{
	return _maxSuspensionTravelCm;
}
void RaycastVehicle::VehicleTuning::MaxSuspensionTravelCm::set(btScalar value)
{
	_maxSuspensionTravelCm = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionCompression::get()
{
	return _suspensionCompression;
}
void RaycastVehicle::VehicleTuning::SuspensionCompression::set(btScalar value)
{
	_suspensionCompression = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionDamping::get()
{
	return _suspensionDamping;
}
void RaycastVehicle::VehicleTuning::SuspensionDamping::set(btScalar value)
{
	_suspensionDamping = value;
}

btScalar RaycastVehicle::VehicleTuning::SuspensionStiffness::get()
{
	return _suspensionStiffness;
}
void RaycastVehicle::VehicleTuning::SuspensionStiffness::set(btScalar value)
{
	_suspensionStiffness = value;
}


static RaycastVehicle::RaycastVehicle()
{
	RigidBodyConstructionInfo^ info = gcnew RigidBodyConstructionInfo(0, nullptr, nullptr);
	_fixedBody = gcnew BulletSharp::RigidBody(info);
	_fixedBody->SetMassProps(0, Vector3_Zero);
}

RaycastVehicle::RaycastVehicle(RaycastVehicle::VehicleTuning^ tuning, BulletSharp::RigidBody^ chassis, IVehicleRaycaster^ raycaster)
{
	_wheelInfo = gcnew List<BulletSharp::WheelInfo^>();
	_chassisBody = chassis;
	_vehicleRaycaster = raycaster;
	_indexRightAxis = 0;
	_indexUpAxis = 2;
	_indexForwardAxis = 1;
	_currentVehicleSpeedKmHour = 0;
	_steeringValue = 0;
}

WheelInfo^ RaycastVehicle::AddWheel(Vector3 connectionPointCS, Vector3 wheelDirectionCS0,
	Vector3 wheelAxleCS, btScalar suspensionRestLength, btScalar wheelRadius, VehicleTuning^ tuning,
	bool isFrontWheel)
{
	WheelInfoConstructionInfo^ ci = gcnew WheelInfoConstructionInfo();

	ci->ChassisConnectionCS = connectionPointCS;
	ci->WheelDirectionCS = wheelDirectionCS0;
	ci->WheelAxleCS = wheelAxleCS;
	ci->SuspensionRestLength = suspensionRestLength;
	ci->WheelRadius = wheelRadius;
	ci->SuspensionStiffness = tuning->SuspensionStiffness;
	ci->WheelsDampingCompression = tuning->SuspensionCompression;
	ci->WheelsDampingRelaxation = tuning->SuspensionDamping;
	ci->FrictionSlip = tuning->FrictionSlip;
	ci->IsFrontWheel = isFrontWheel;
	ci->MaxSuspensionTravelCm = tuning->MaxSuspensionTravelCm;
	ci->MaxSuspensionForce = tuning->MaxSuspensionForce;

	BulletSharp::WheelInfo^ wheel = gcnew BulletSharp::WheelInfo(ci);
	_wheelInfo->Add(wheel);

	UpdateWheelTransformsWS(wheel, false);
	UpdateWheelTransform(NumWheels - 1, false);
	return wheel;
}

void RaycastVehicle::ApplyEngineForce(btScalar force, int wheel)
{
	System::Diagnostics::Debug::Assert(wheel >= 0 && wheel < NumWheels);
	BulletSharp::WheelInfo^ wheelInfo = GetWheelInfo(wheel);
	wheelInfo->EngineForce = force;
}

#pragma managed(push, off)
void RaycastVehicle_GetBasisAxle(const btTransform* transform, int axis, btVector3* axle)
{
	axle->setX(transform->getBasis()[0][axis]);
	axle->setY(transform->getBasis()[1][axis]);
	axle->setZ(transform->getBasis()[2][axis]);
}
#pragma managed(pop)

#ifndef DISABLE_DEBUGDRAW
void RaycastVehicle::DebugDraw(IDebugDraw^ debugDrawer)
{
	btVector3& wheelColor = *ALIGNED_NEW(btVector3);
	btTransform* worldTransformTemp = ALIGNED_NEW(btTransform);
	btVector3* axleTemp = ALIGNED_NEW(btVector3);

	for (int v = 0; v < NumWheels; v++)
	{
		BulletSharp::WheelInfo^ wheel = GetWheelInfo(v);

		if (wheel->RaycastInfo.IsInContact)
		{
			wheelColor.setValue(0, 0, 1);
		}
		else
		{
			wheelColor.setValue(1, 0, 1);
		}

		Math::MatrixToBtTransform(wheel->WorldTransform, worldTransformTemp);
		Vector3 wheelPosWS = Math::BtVector3ToVector3(&worldTransformTemp->getOrigin());
		RaycastVehicle_GetBasisAxle(worldTransformTemp, RightAxis, axleTemp);
		Vector3 axle = Math::BtVector3ToVector3(axleTemp);

		//debug wheels (cylinders)
		debugDrawer->DrawLine(wheelPosWS, wheelPosWS + axle, BtVectorToBtColor(wheelColor));
		debugDrawer->DrawLine(wheelPosWS, wheel->RaycastInfo.ContactPointWS, BtVectorToBtColor(wheelColor));
	}
	ALIGNED_FREE(wheelColor);
	ALIGNED_FREE(worldTransformTemp);
	ALIGNED_FREE(axleTemp);
}
#endif

btScalar RaycastVehicle::GetSteeringValue(int wheel)
{
	return GetWheelInfo(wheel)->Steering;
}

WheelInfo^ RaycastVehicle::GetWheelInfo(int index)
{
	System::Diagnostics::Debug::Assert(index >= 0 && index < NumWheels);
	return _wheelInfo[index];
}

Matrix RaycastVehicle::GetWheelTransformWS(int wheelIndex)
{
	System::Diagnostics::Debug::Assert(wheelIndex < NumWheels);
	return _wheelInfo[wheelIndex]->WorldTransform;
}

btScalar RaycastVehicle::RayCast(BulletSharp::WheelInfo^ wheel)
{
	UpdateWheelTransformsWS(wheel, false);

	btScalar depth = -1;

	btScalar raylen = wheel->SuspensionRestLength + wheel->WheelsRadius;

	Vector3 rayvector = wheel->RaycastInfo.WheelDirectionWS * raylen;
	Vector3 source = wheel->RaycastInfo.HardPointWS;
	wheel->RaycastInfo.ContactPointWS = source + rayvector;
	Vector3 target = wheel->RaycastInfo.ContactPointWS;

	btScalar param = btScalar(0.);
	VehicleRaycasterResult^ rayResults = gcnew VehicleRaycasterResult();

	System::Diagnostics::Debug::Assert(_vehicleRaycaster != nullptr);

	Object^ obj = _vehicleRaycaster->CastRay(source, target, rayResults);

	wheel->RaycastInfo.GroundObject = nullptr;

	if (obj)
	{
		param = rayResults->DistFraction;
		depth = raylen * rayResults->DistFraction;
		wheel->RaycastInfo.ContactNormalWS = rayResults->HitNormalInWorld;
		wheel->RaycastInfo.IsInContact = true;

		wheel->RaycastInfo.GroundObject = _fixedBody;///@todo for driving on dynamic/movable objects!;
		//wheel->RaycastInfo.GroundObject = object;

		btScalar hitDistance = param * raylen;
		wheel->RaycastInfo.SuspensionLength = hitDistance - wheel->WheelsRadius;

		//clamp on max suspension travel
		btScalar minSuspensionLength = wheel->SuspensionRestLength - wheel->MaxSuspensionTravelCm * btScalar(0.01);
		btScalar maxSuspensionLength = wheel->SuspensionRestLength + wheel->MaxSuspensionTravelCm * btScalar(0.01);
		if (wheel->RaycastInfo.SuspensionLength < minSuspensionLength)
		{
			wheel->RaycastInfo.SuspensionLength = minSuspensionLength;
		}
		if (wheel->RaycastInfo.SuspensionLength > maxSuspensionLength)
		{
			wheel->RaycastInfo.SuspensionLength = maxSuspensionLength;
		}

		wheel->RaycastInfo.ContactPointWS = rayResults->HitPointInWorld;

		btScalar denominator = Vector3_Dot(wheel->RaycastInfo.ContactNormalWS, wheel->RaycastInfo.WheelDirectionWS);

		Vector3 relpos = wheel->RaycastInfo.ContactPointWS - RigidBody->CenterOfMassPosition;
		Vector3 chassis_velocity_at_contactPoint = RigidBody->GetVelocityInLocalPoint(relpos);
		btScalar projVel = Vector3_Dot(wheel->RaycastInfo.ContactNormalWS, chassis_velocity_at_contactPoint);

		if (denominator >= btScalar(-0.1))
		{
			wheel->SuspensionRelativeVelocity = btScalar(0.0);
			wheel->ClippedInvContactDotSuspension = btScalar(1.0) / btScalar(0.1);
		}
		else
		{
			btScalar inv = btScalar(-1.) / denominator;
			wheel->SuspensionRelativeVelocity = projVel * inv;
			wheel->ClippedInvContactDotSuspension = inv;
		}
	}
	else
	{
		//put wheel info as in rest position
		wheel->RaycastInfo.SuspensionLength = wheel->SuspensionRestLength;
		wheel->SuspensionRelativeVelocity = btScalar(0.0);
		wheel->RaycastInfo.ContactNormalWS = -wheel->RaycastInfo.WheelDirectionWS;
		wheel->ClippedInvContactDotSuspension = btScalar(1.0);
	}

	delete rayResults;

	return depth;
}

void RaycastVehicle::ResetSuspension()
{
	for (int i = 0; i < NumWheels; i++)
	{
		BulletSharp::WheelInfo^ wheel = GetWheelInfo(i);
		wheel->RaycastInfo.SuspensionLength = wheel->SuspensionRestLength;
		wheel->SuspensionRelativeVelocity = btScalar(0.0);

		wheel->RaycastInfo.ContactNormalWS = -wheel->RaycastInfo.WheelDirectionWS;
		//wheel->ContactFriction = btScalar(0.0);
		wheel->ClippedInvContactDotSuspension = btScalar(1.0);
	}
}

void RaycastVehicle::SetBrake(btScalar brake, int wheelIndex)
{
	System::Diagnostics::Debug::Assert(wheelIndex >= 0 && wheelIndex < NumWheels);
	GetWheelInfo(wheelIndex)->Brake = brake;
}

void RaycastVehicle::SetCoordinateSystem(int rightIndex, int upIndex, int forwardIndex)
{
	_indexRightAxis = rightIndex;
	_indexUpAxis = upIndex;
	_indexForwardAxis = forwardIndex;
}

void RaycastVehicle::SetPitchControl(btScalar pitch)
{
	_pitchControl = pitch;
}

void RaycastVehicle::SetSteeringValue(btScalar steering, int wheel)
{
	System::Diagnostics::Debug::Assert(wheel >= 0 && wheel < NumWheels);
	BulletSharp::WheelInfo^ wheelInfo = GetWheelInfo(wheel);
	wheelInfo->Steering = steering;
}

void RaycastVehicle::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep)
{
	UpdateVehicle(deltaTimeStep);
}

btScalar CalcRollingFriction(RigidBody^ body0, RigidBody^ body1, Vector3 contactPosWorld, Vector3 frictionDirectionWorld, btScalar maxImpulse)
{
    btScalar denom0 = body0->ComputeImpulseDenominator(contactPosWorld, frictionDirectionWorld);
    btScalar denom1 = body1->ComputeImpulseDenominator(contactPosWorld, frictionDirectionWorld);
    const btScalar relaxation = 1.0f;
    btScalar jacDiagABInv = relaxation / (denom0 + denom1);

    Vector3 rel_pos1 = contactPosWorld - body0->CenterOfMassPosition;
    Vector3 rel_pos2 = contactPosWorld - body1->CenterOfMassPosition;

    Vector3 vel1 = body0->GetVelocityInLocalPoint(rel_pos1);
    Vector3 vel2 = body1->GetVelocityInLocalPoint(rel_pos2);
    Vector3 vel = vel1 - vel2;

    btScalar vrel = Vector3_Dot(frictionDirectionWorld, vel);

    // calculate j that moves us to zero relative velocity
    btScalar j1 = -vrel * jacDiagABInv;
	btSetMin(j1, maxImpulse);
	btSetMax(j1, -maxImpulse);

    return j1;
}

void RaycastVehicle::UpdateFriction(btScalar timeStep)
{
	int numWheel = NumWheels;
	if (numWheel == 0)
	{
		return;
	}

	Array::Resize<Vector3>(_forwardWS, numWheel);
	Array::Resize<Vector3>(_axle, numWheel);
	Array::Resize<btScalar>(_forwardImpulse, numWheel);
	Array::Resize<btScalar>(_sideImpulse, numWheel);

	int numWheelsOnGround = 0;

	int i;
	for (i = 0; i < numWheel; i++)
	{
		BulletSharp::WheelInfo^ wheelInfo = _wheelInfo[i];
		BulletSharp::RigidBody^ groundObject = static_cast<BulletSharp::RigidBody^>(wheelInfo->RaycastInfo.GroundObject);
		if (groundObject)
			numWheelsOnGround++;
		_sideImpulse[i] = btScalar(0.);
		_forwardImpulse[i] = btScalar(0.);
	}

	btTransform* wheelTransTemp = ALIGNED_NEW(btTransform);
	btVector3* contactPointWSTemp = ALIGNED_NEW(btVector3);
	btVector3* axleTemp = ALIGNED_NEW(btVector3);
	for (i = 0; i < numWheel; i++)
	{
		BulletSharp::WheelInfo^ wheelInfo = _wheelInfo[i];
		BulletSharp::RigidBody^ groundObject = static_cast<BulletSharp::RigidBody^>(wheelInfo->RaycastInfo.GroundObject);
		if (groundObject)
		{
			Math::MatrixToBtTransform(GetWheelTransformWS(i), wheelTransTemp);
			RaycastVehicle_GetBasisAxle(wheelTransTemp, _indexRightAxis, axleTemp);
			_axle[i] = Math::BtVector3ToVector3(axleTemp);

			Vector3 surfNormalWS = wheelInfo->RaycastInfo.ContactNormalWS;
			btScalar proj = Vector3_Dot(_axle[i], surfNormalWS);
			_axle[i] -= surfNormalWS * proj;
			Vector3_Normalize(_axle[i]);

			Vector3_Cross(surfNormalWS, _axle[i], _forwardWS[i]);
			Vector3_Normalize(_forwardWS[i]);

			Math::Vector3ToBtVector3(wheelInfo->RaycastInfo.ContactPointWS, contactPointWSTemp);
			Math::Vector3ToBtVector3(_axle[i], axleTemp);
			btScalar sideImpulseTemp;
			resolveSingleBilateral(
				*(btRigidBody*)_chassisBody->_native, *contactPointWSTemp,
				*(btRigidBody*)groundObject->_native, *contactPointWSTemp,
				0, *axleTemp, sideImpulseTemp, timeStep);
			_sideImpulse[i] = sideImpulseTemp;

			btScalar sideFrictionStiffness2 = btScalar(1.0);
			_sideImpulse[i] *= sideFrictionStiffness2;
		}
	}
	ALIGNED_FREE(wheelTransTemp);
	ALIGNED_FREE(contactPointWSTemp);
	ALIGNED_FREE(axleTemp);

	btScalar sideFactor = btScalar(1.);
	btScalar fwdFactor = 0.5;

	bool sliding = false;
	for (i = 0; i < numWheel; i++)
	{
		BulletSharp::WheelInfo^ wheelInfo = _wheelInfo[i];
		BulletSharp::RigidBody^ groundObject = static_cast<BulletSharp::RigidBody^>(wheelInfo->RaycastInfo.GroundObject);
		btScalar rollingFriction = 0.f;
		if (groundObject)  
		{
			if (wheelInfo->EngineForce != 0.f)
			{
				rollingFriction = wheelInfo->EngineForce * timeStep;
			}
			else
			{
				btScalar defaultRollingFrictionImpulse = 0.f;
 				btScalar maxImpulse = wheelInfo->Brake ? wheelInfo->Brake : defaultRollingFrictionImpulse;
				rollingFriction = CalcRollingFriction(_chassisBody, groundObject, wheelInfo->RaycastInfo.ContactPointWS, _forwardWS[i], maxImpulse);
			}
		}

		//switch between active rolling (throttle), braking and non-active rolling friction (no throttle/break)

		_forwardImpulse[i] = btScalar(0.);
		wheelInfo->SkidInfo= btScalar(1.);

		if (groundObject)
		{
			_wheelInfo[i]->SkidInfo = btScalar(1.);
				
			btScalar maximp = wheelInfo->WheelsSuspensionForce * timeStep * wheelInfo->FrictionSlip;
			btScalar maximpSide = maximp;

			btScalar maximpSquared = maximp * maximpSide;
			

			_forwardImpulse[i] = rollingFriction;//wheelInfo->EngineForce* timeStep;

			btScalar x = (_forwardImpulse[i] ) * fwdFactor;
			btScalar y = (_sideImpulse[i] ) * sideFactor;
				
			btScalar impulseSquared = (x*x + y*y);

			if (impulseSquared > maximpSquared)
			{
				sliding = true;
					
				btScalar factor = maximp / btSqrt(impulseSquared);
					
				_wheelInfo[i]->SkidInfo *= factor;
			}
		}
	}

	if (sliding)
	{
		for (i = 0; i < numWheel; i++)
		{
			if (_sideImpulse[i] != btScalar(0.))
			{
				BulletSharp::WheelInfo^ wheelInfo = _wheelInfo[i];
				if (wheelInfo->SkidInfo < btScalar(1.))
				{
					_forwardImpulse[i] *= wheelInfo->SkidInfo;
					_sideImpulse[i] *= wheelInfo->SkidInfo;
				}
			}
		}
	}

	// apply the impulses
	for (i = 0; i < numWheel; i++)
	{
		BulletSharp::WheelInfo^ wheelInfo = _wheelInfo[i];
		Vector3 rel_pos = wheelInfo->RaycastInfo.ContactPointWS -
			_chassisBody->CenterOfMassPosition;

		if (_forwardImpulse[i] != btScalar(0.))
		{
			_chassisBody->ApplyImpulse(_forwardWS[i] * _forwardImpulse[i], rel_pos);
		}
		if (_sideImpulse[i] != btScalar(0.))
		{
			BulletSharp::RigidBody^ groundObject = static_cast<BulletSharp::RigidBody^>(wheelInfo->RaycastInfo.GroundObject);

			Vector3 rel_pos2 = wheelInfo->RaycastInfo.ContactPointWS -
				groundObject->CenterOfMassPosition;

					
			Vector3 sideImp = _axle[i] * _sideImpulse[i];

#if defined ROLLING_INFLUENCE_FIX // fix. It only worked if car's up was along Y - VT.
			btVector3* chassisWorldUpTemp = ALIGNED_NEW(btVector3);
			RaycastVehicle_GetBasisAxle(&static_cast<btRigidBody*>(RigidBody->_native)->getCenterOfMassTransform(), _indexUpAxis, chassisWorldUpTemp);
			Vector3 chassisWorldUp = Math::BtVector3ToVector3(chassisWorldUpTemp);
			ALIGNED_FREE(chassisWorldUpTemp);
			rel_pos -= chassisWorldUp * (Vector3_Dot(chassisWorldUp, rel_pos) * (1.f-wheelInfo->RollInfluence));
#else
#if defined(GRAPHICS_MONOGAME)
			switch (_indexUpAxis)
			{
			case 0:
				Vector_SetX(rel_pos, Vector_X(rel_pos) * wheelInfo->RollInfluence);
				break;
			case 1:
				Vector_SetY(rel_pos, Vector_Y(rel_pos) * wheelInfo->RollInfluence);
				break;
			case 2:
				Vector_SetZ(rel_pos, Vector_Z(rel_pos) * wheelInfo->RollInfluence);
				break;
			}
#else
			rel_pos[_indexUpAxis] = (btScalar)rel_pos[_indexUpAxis] * (btScalar)wheelInfo->RollInfluence;
#endif
#endif
			_chassisBody->ApplyImpulse(sideImp, rel_pos);

			//apply friction impulse on the ground
			groundObject->ApplyImpulse(-sideImp, rel_pos2);
		}
	}
}

void RaycastVehicle::UpdateSuspension(btScalar deltaTime)
{
	btScalar chassisMass = btScalar(1.) / _chassisBody->InvMass;

	int i;
	for (i = 0; i < NumWheels; i++)
	{
		BulletSharp::WheelInfo^ wheelInfo = _wheelInfo[i];
		if (wheelInfo->RaycastInfo.IsInContact)
		{
			btScalar force;
			//	Spring
			btScalar susp_length = wheelInfo->SuspensionRestLength;
			btScalar current_length = wheelInfo->RaycastInfo.SuspensionLength;

			btScalar length_diff = (susp_length - current_length);

			force = wheelInfo->SuspensionStiffness
				* length_diff * wheelInfo->ClippedInvContactDotSuspension;


			// Damper
			btScalar projected_rel_vel = wheelInfo->SuspensionRelativeVelocity;
			{
				btScalar susp_damping;
				if ( projected_rel_vel < btScalar(0.0) )
				{
					susp_damping = wheelInfo->WheelsDampingCompression;
				}
				else
				{
					susp_damping = wheelInfo->WheelsDampingRelaxation;
				}
				force -= susp_damping * projected_rel_vel;
			}


			// RESULT
			wheelInfo->WheelsSuspensionForce = force * chassisMass;
			if (wheelInfo->WheelsSuspensionForce < btScalar(0.))
			{
				wheelInfo->WheelsSuspensionForce = btScalar(0.);
			}
		}
		else
		{
			wheelInfo->WheelsSuspensionForce = btScalar(0.0);
		}
	}
}

#pragma managed(push, off)
btScalar RaycastVehicle_UpdateVehicle_GetSpeed(btVector3* linearVelocity, btVector3* forwardW)
{
	if (forwardW->dot(*linearVelocity) < btScalar(0.))
	{
		return -linearVelocity->length();
	}
	return linearVelocity->length();
}
#pragma managed(pop)
void RaycastVehicle::UpdateVehicle(btScalar step)
{
	int numWheels = NumWheels;

	int i;
	for (i = 0; i < numWheels; i++)
	{
		UpdateWheelTransform(i, false);
	}

	btVector3* linearVelocityTemp = Math::Vector3ToBtVector3(RigidBody->LinearVelocity);
	btTransform* chassisTransTemp = Math::MatrixToBtTransform(ChassisWorldTransform);
	btVector3* forwardWTemp = ALIGNED_NEW(btVector3);
	RaycastVehicle_GetBasisAxle(chassisTransTemp, _indexForwardAxis, forwardWTemp);
	_currentVehicleSpeedKmHour = btScalar(3.6) * RaycastVehicle_UpdateVehicle_GetSpeed(linearVelocityTemp, forwardWTemp);
	ALIGNED_FREE(linearVelocityTemp);
	ALIGNED_FREE(chassisTransTemp);
	ALIGNED_FREE(forwardWTemp);

	for (i = 0; i < numWheels; i++)
	{
		RayCast(_wheelInfo[i]);
	}

	UpdateSuspension(step);
	for (i = 0; i < numWheels; i++)
	{
		BulletSharp::WheelInfo^ wheel = _wheelInfo[i];

		btScalar suspensionForce = wheel->WheelsSuspensionForce;
		if (suspensionForce > wheel->MaxSuspensionForce)
		{
			suspensionForce = wheel->MaxSuspensionForce;
		}
		Vector3 impulse = wheel->RaycastInfo.ContactNormalWS * (suspensionForce * step);
		Vector3 relpos = wheel->RaycastInfo.ContactPointWS - RigidBody->CenterOfMassPosition;
		RigidBody->ApplyImpulse(impulse, relpos);
	}

	UpdateFriction(step);

	btVector3* fwdTemp = ALIGNED_NEW(btVector3);
	for (i = 0; i < numWheels; i++)
	{
		BulletSharp::WheelInfo^ wheel = _wheelInfo[i];
		Vector3 relpos = wheel->RaycastInfo.HardPointWS - RigidBody->CenterOfMassPosition;
		Vector3 vel = RigidBody->GetVelocityInLocalPoint(relpos);

		if (wheel->RaycastInfo.IsInContact)
		{
			RaycastVehicle_GetBasisAxle(&static_cast<btRigidBody*>(RigidBody->_native)->getCenterOfMassTransform(), ForwardAxis, fwdTemp);
			Vector3 fwd = Math::BtVector3ToVector3(fwdTemp);
			
			btScalar proj = Vector3_Dot(fwd, wheel->RaycastInfo.ContactNormalWS);
			fwd -= wheel->RaycastInfo.ContactNormalWS * proj;

			btScalar proj2 = Vector3_Dot(fwd, vel);
			wheel->DeltaRotation = (proj2 * step) / (wheel->WheelsRadius);
			wheel->Rotation += wheel->DeltaRotation;
		}
		else
		{
			wheel->Rotation += wheel->DeltaRotation;
		}

		wheel->DeltaRotation *= btScalar(0.99);//damping of rotation when not in contact
	}
	ALIGNED_FREE(fwdTemp);
}

#pragma managed(push, off)
void RaycastVehicle_UpdateWheelTransform(const btVector3* wheelDirectionWS, const btVector3* right,
	btScalar steering, btScalar rotation, const btVector3* hardPointWS, btScalar suspensionLength,
	btTransform* worldTransform)
{
	btVector3 up = -*wheelDirectionWS;
	btVector3 fwd = up.cross(*right);
	fwd = fwd.normalize();
	// up = right.cross(fwd);
	// up.normalize();

	btQuaternion steeringOrn(up, steering);
	btMatrix3x3 steeringMat(steeringOrn);

	btQuaternion rotatingOrn(*right, -rotation);
	btMatrix3x3 rotatingMat(rotatingOrn);

	btMatrix3x3 basis2(
		right->getX(),fwd[0],up[0],
		right->getY(),fwd[1],up[1],
		right->getZ(),fwd[2],up[2]
	);
	
	worldTransform->setBasis(steeringMat * rotatingMat * basis2);
	worldTransform->setOrigin(*hardPointWS + *wheelDirectionWS * suspensionLength);
}
#pragma managed(pop)
void RaycastVehicle::UpdateWheelTransform(int wheelIndex, bool interpolatedTransform)
{
	BulletSharp::WheelInfo^ wheel = _wheelInfo[wheelIndex];
	UpdateWheelTransformsWS(wheel, interpolatedTransform);

	btVector3* wheelDirectionWSTemp = Math::Vector3ToBtVector3(wheel->RaycastInfo.WheelDirectionWS);
	btVector3* wheelAxleWSTemp = Math::Vector3ToBtVector3(wheel->RaycastInfo.WheelAxleWS);
	btVector3* hardPointWSTemp = Math::Vector3ToBtVector3(wheel->RaycastInfo.HardPointWS);
	btTransform* worldTransformTemp = ALIGNED_NEW(btTransform);
	RaycastVehicle_UpdateWheelTransform(wheelDirectionWSTemp, wheelAxleWSTemp,
		wheel->Steering, wheel->Rotation, hardPointWSTemp, wheel->RaycastInfo.SuspensionLength, worldTransformTemp);
	wheel->WorldTransform = Math::BtTransformToMatrix(worldTransformTemp);
	ALIGNED_FREE(wheelDirectionWSTemp);
	ALIGNED_FREE(wheelAxleWSTemp);
	ALIGNED_FREE(hardPointWSTemp);
	ALIGNED_FREE(worldTransformTemp);
}

void RaycastVehicle::UpdateWheelTransform(int wheelIndex)
{
	UpdateWheelTransform(wheelIndex, true);
}

#pragma managed(push, off)
void RaycastVehicle_UpdateWheelTransformsWS(const btTransform* chassisTrans,
	const btVector3* chassisConnectionPointCS, btVector3* hardPointWS,
	const btVector3* wheelDirectionCS, btVector3* wheelDirectionWS,
	const btVector3* wheelAxleCS, btVector3* wheelAxleWS)
{
	*hardPointWS = *chassisTrans * *chassisConnectionPointCS;
	*wheelDirectionWS = chassisTrans->getBasis() * *wheelDirectionCS;
	*wheelAxleWS = chassisTrans->getBasis() * *wheelAxleCS;
}
#pragma managed(pop)
void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheel, bool interpolatedTransform)
{
	wheel->RaycastInfo.IsInContact = false;

	Matrix chassisTrans = ChassisWorldTransform;
	if (interpolatedTransform && RigidBody->MotionState != nullptr)
	{
		chassisTrans = RigidBody->MotionState->WorldTransform;
	}

	TRANSFORM_CONV(chassisTrans);
	btVector3* chassisConnectionPointCSTemp = Math::Vector3ToBtVector3(wheel->ChassisConnectionPointCS);
	btVector3* wheelDirectionCSTemp = Math::Vector3ToBtVector3(wheel->WheelDirectionCS);
	btVector3* wheelAxleCSTemp = Math::Vector3ToBtVector3(wheel->WheelAxleCS);
	btVector3* hardPointWS = ALIGNED_NEW(btVector3);
	btVector3* wheelDirectionWS = ALIGNED_NEW(btVector3);
	btVector3* wheelAxleWS = ALIGNED_NEW(btVector3);
	RaycastVehicle_UpdateWheelTransformsWS(TRANSFORM_PTR(chassisTrans),
		chassisConnectionPointCSTemp, hardPointWS,
		wheelDirectionCSTemp, wheelDirectionWS,
		wheelAxleCSTemp, wheelAxleWS);
	Math::BtVector3ToVector3(hardPointWS, wheel->RaycastInfo.HardPointWS);
	Math::BtVector3ToVector3(wheelDirectionWS, wheel->RaycastInfo.WheelDirectionWS);
	Math::BtVector3ToVector3(wheelAxleWS, wheel->RaycastInfo.WheelAxleWS);
	TRANSFORM_DEL(chassisTrans);
	ALIGNED_FREE(chassisConnectionPointCSTemp);
	ALIGNED_FREE(wheelDirectionCSTemp);
	ALIGNED_FREE(wheelAxleCSTemp);
	ALIGNED_FREE(hardPointWS);
	ALIGNED_FREE(wheelDirectionWS);
	ALIGNED_FREE(wheelAxleWS);
}

void RaycastVehicle::UpdateWheelTransformsWS(BulletSharp::WheelInfo^ wheel)
{
	UpdateWheelTransformsWS(wheel, true);
}

Matrix RaycastVehicle::ChassisWorldTransform::get()
{
	return RigidBody->CenterOfMassTransform;
}

btScalar RaycastVehicle::CurrentSpeedKmHour::get()
{
	return _currentVehicleSpeedKmHour;
}

int RaycastVehicle::ForwardAxis::get()
{
	return _indexForwardAxis;
}

Vector3 RaycastVehicle::ForwardVector::get()
{
	btTransform* chassisTransTemp = Math::MatrixToBtTransform(ChassisWorldTransform);
	btVector3* forwardVectorTemp = ALIGNED_NEW(btVector3);
	RaycastVehicle_GetBasisAxle(chassisTransTemp, _indexForwardAxis, forwardVectorTemp);
	Vector3 forwardVector = Math::BtVector3ToVector3(forwardVectorTemp);
	ALIGNED_FREE(chassisTransTemp);
	ALIGNED_FREE(forwardVectorTemp);
	return forwardVector;
}

int RaycastVehicle::NumWheels::get()
{
	return _wheelInfo->Count;
}

int RaycastVehicle::RightAxis::get()
{
	return _indexRightAxis;
}

RigidBody^ RaycastVehicle::RigidBody::get()
{
	return _chassisBody;
}

int RaycastVehicle::UpAxis::get()
{
	return _indexUpAxis;
}

IList<WheelInfo^>^ RaycastVehicle::WheelInfo::get()
{
	return _wheelInfo;
}


DefaultVehicleRaycaster::~DefaultVehicleRaycaster()
{
	this->!DefaultVehicleRaycaster();
}

DefaultVehicleRaycaster::!DefaultVehicleRaycaster()
{
	delete _native;
	_native = NULL;
}

DefaultVehicleRaycaster::DefaultVehicleRaycaster(DynamicsWorld^ world)
{
	_native = new btDefaultVehicleRaycaster((btDynamicsWorld*)world->_native);
}

Object^ DefaultVehicleRaycaster::CastRay(Vector3 from, Vector3 to, VehicleRaycasterResult^ result)
{
	VECTOR3_CONV(from);
	VECTOR3_CONV(to);
	void* ret = _native->castRay(VECTOR3_USE(from), VECTOR3_USE(to), *result->_native);
	VECTOR3_DEL(from);
	VECTOR3_DEL(to);
	return CollisionObject::GetManaged((btRigidBody*)ret);
}

#endif
