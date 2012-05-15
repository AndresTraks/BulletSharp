#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionShape.h"
#include "MotionState.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

#define Unmanaged static_cast<btRigidBody*>(_unmanaged)

RigidBody::RigidBody(RigidBodyConstructionInfo^ info)
: CollisionObject(new btRigidBody(*info->UnmanagedPointer))
{
	_motionState = info->_motionState;
}

RigidBody::RigidBody(btRigidBody* body)
: CollisionObject(body)
{
}

#ifndef DISABLE_CONSTRAINTS
void RigidBody::AddConstraintRef(TypedConstraint^ constraint)
{
	Unmanaged->addConstraintRef(constraint->UnmanagedPointer);
}

TypedConstraint^ RigidBody::GetConstraintRef(int index)
{
	return TypedConstraint::Upcast(Unmanaged->getConstraintRef(index));
}

void RigidBody::RemoveConstraintRef(TypedConstraint^ constraint)
{
	Unmanaged->removeConstraintRef(constraint->UnmanagedPointer);
}

int RigidBody::ConstraintRefCount::get()
{
	return Unmanaged->getNumConstraintRefs();
}
#endif

void RigidBody::ApplyCentralForce(Vector3 force)
{
	btVector3* forceTemp = Math::Vector3ToBtVector3(force);
	Unmanaged->applyCentralForce(*forceTemp);
	delete forceTemp;
}

void RigidBody::ApplyCentralImpulse(Vector3 impulse)
{
	btVector3* impulseTemp = Math::Vector3ToBtVector3(impulse);
	Unmanaged->applyCentralImpulse(*impulseTemp);
	delete impulseTemp;
}

void RigidBody::ApplyDamping(btScalar timeStep)
{
	Unmanaged->applyDamping(timeStep);
}

void RigidBody::ApplyForce(Vector3 force, Vector3 relativePosition)
{
	btVector3* forceTemp = Math::Vector3ToBtVector3(force);
	btVector3* relativePositionTemp = Math::Vector3ToBtVector3(relativePosition);
	
	Unmanaged->applyForce(*forceTemp, *relativePositionTemp);
	
	delete relativePosition;
	delete forceTemp;
}

void RigidBody::ApplyGravity()
{
	Unmanaged->applyGravity();
}

void RigidBody::ApplyImpulse(Vector3 impulse, Vector3 relativePosition)
{
	btVector3* impulseTemp = Math::Vector3ToBtVector3(impulse);
	btVector3* relativePositionTemp = Math::Vector3ToBtVector3(relativePosition);

	Unmanaged->applyImpulse(*impulseTemp, *relativePositionTemp);
	
	delete relativePositionTemp;
	delete impulseTemp;
}

void RigidBody::ApplyTorque(Vector3 torque)
{
	btVector3* torqueTemp = Math::Vector3ToBtVector3(torque);
	Unmanaged->applyTorque(*torqueTemp);
	delete torqueTemp;
}

void RigidBody::ApplyTorqueImpulse(Vector3 torque)
{
	btVector3* torqueTemp = Math::Vector3ToBtVector3(torque);
	Unmanaged->applyTorqueImpulse(*torqueTemp);
	delete torqueTemp;
}

bool RigidBody::CheckCollideWithOverride(CollisionObject^ co)
{
	return Unmanaged->checkCollideWithOverride(co->UnmanagedPointer);
}

void RigidBody::ClearForces()
{
	Unmanaged->clearForces();
}

btScalar RigidBody::ComputeAngularImpulseDenominator(Vector3 axis)
{
	btVector3* axisTemp = Math::Vector3ToBtVector3(axis);
	btScalar ret = Unmanaged->computeAngularImpulseDenominator(*axisTemp);
	delete axisTemp;
	return ret;
}

btScalar RigidBody::ComputeImpulseDenominator(Vector3 pos, Vector3 normal)
{
	btVector3* posTemp = Math::Vector3ToBtVector3(pos);
	btVector3* normalTemp = Math::Vector3ToBtVector3(normal);

	btScalar ret = Unmanaged->computeImpulseDenominator(*posTemp, *normalTemp);

	delete normalTemp;
	delete posTemp;
	return ret;
}

void RigidBody::GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	Unmanaged->getAabb(*aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

#pragma managed(push, off)
void RigidBody_GetVelocityInLocalPoint(btRigidBody* body, btVector3* velocity, btVector3* rel_pos)
{
	*velocity = body->getVelocityInLocalPoint(*rel_pos);
}
#pragma managed(pop)
Vector3 RigidBody::GetVelocityInLocalPoint(Vector3 relativePosition)
{
	btVector3* relativePositionTemp = Math::Vector3ToBtVector3(relativePosition);
	btVector3* velocityTemp = new btVector3;

	RigidBody_GetVelocityInLocalPoint((btRigidBody*)_unmanaged, velocityTemp, relativePositionTemp);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);

	delete relativePositionTemp;
	delete velocityTemp;

	return velocity;
}

void RigidBody::IntegrateVelocities(btScalar step)
{
	Unmanaged->integrateVelocities(step);
}

bool RigidBody::IsInWorld()
{
	return Unmanaged->isInWorld();
}

void RigidBody::PredictIntegratedTransform(btScalar step, Matrix predictedTransform)
{
	btTransform* predictedTransformTemp = Math::MatrixToBtTransform(predictedTransform);
	Unmanaged->predictIntegratedTransform(step, *predictedTransformTemp);
	delete predictedTransformTemp;
}

void RigidBody::ProceedToTransform(Matrix newTransform)
{
	btTransform* newTransformTemp = Math::MatrixToBtTransform(newTransform);
	Unmanaged->proceedToTransform(*newTransformTemp);
	delete newTransformTemp;
}

void RigidBody::SaveKinematicState(btScalar step)
{
	Unmanaged->saveKinematicState(step);
}

void RigidBody::SetDamping(btScalar linearDamping, btScalar angularDamping)
{
	Unmanaged->setDamping(linearDamping, angularDamping);
}

void RigidBody::SetMassProps(btScalar mass, Vector3 inertia)
{
	btVector3* inertiaTemp = Math::Vector3ToBtVector3(inertia);
	Unmanaged->setMassProps(mass, *inertiaTemp);
	delete inertiaTemp;
}

void RigidBody::SetSleepingThresholds(btScalar inertia, btScalar angular)
{
	Unmanaged->setSleepingThresholds(inertia, angular);
}

void RigidBody::Translate(Vector3 vector)
{
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	Unmanaged->translate(*vectorTemp);
	delete vectorTemp;
}

void RigidBody::UpdateDeactivation(btScalar timeStep)
{
	Unmanaged->updateDeactivation(timeStep);
}

void RigidBody::UpdateInertiaTensor()
{
	Unmanaged->updateInertiaTensor();
}

RigidBody^ RigidBody::Upcast(CollisionObject^ colObj)
{
	btRigidBody* body = btRigidBody::upcast(colObj->UnmanagedPointer);
	return (RigidBody^)CollisionObject::GetManaged(body);
}

#ifndef DISABLE_INTERNAL
void RigidBody::InternalApplyImpulse(Vector3 linearComponent, Vector3 angularComponent, btScalar impulseMagnitude)
{
	btVector3* linearComponentTemp = Math::Vector3ToBtVector3(linearComponent);
	btVector3* angularComponentTemp = Math::Vector3ToBtVector3(angularComponent);

	Unmanaged->internalApplyImpulse(*linearComponentTemp, *angularComponentTemp, impulseMagnitude);

	delete linearComponentTemp;
	delete angularComponentTemp;
}

void RigidBody::InternalApplyPushImpulse(Vector3 linearComponent, Vector3 angularComponent, btScalar impulseMagnitude)
{
	btVector3* linearComponentTemp = Math::Vector3ToBtVector3(linearComponent);
	btVector3* angularComponentTemp = Math::Vector3ToBtVector3(angularComponent);

	Unmanaged->internalApplyPushImpulse(*linearComponentTemp, *angularComponentTemp, impulseMagnitude);

	delete linearComponentTemp;
	delete angularComponentTemp;
}

void RigidBody::InternalWritebackVelocity(btScalar timeStep)
{
	Unmanaged->internalWritebackVelocity(timeStep);
}

void RigidBody::InternalWritebackVelocity()
{
	Unmanaged->internalWritebackVelocity();
}

Vector3 RigidBody::InternalAngularFactor::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->internalGetAngularFactor());
}

Vector3 RigidBody::InternalDeltaAngularVelocity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->internalGetDeltaAngularVelocity());
}

Vector3 RigidBody::InternalDeltaLinearVelocity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->internalGetDeltaLinearVelocity());
}

Vector3 RigidBody::InternalInvMass::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->internalGetInvMass());
}

Vector3 RigidBody::InternalPushVelocity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->internalGetPushVelocity());
}

Vector3 RigidBody::InternalTurnVelocity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->internalGetTurnVelocity());
}
#endif


btScalar RigidBody::AngularDamping::get()
{
	return Unmanaged->getAngularDamping();
}

Vector3 RigidBody::AngularFactor::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getAngularFactor());
}
void RigidBody::AngularFactor::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	Unmanaged->setAngularFactor(*valueTemp);
	delete valueTemp;
}

btScalar RigidBody::AngularSleepingThreshold::get()
{
	return Unmanaged->getAngularSleepingThreshold();
}

Vector3 RigidBody::AngularVelocity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getAngularVelocity());
}
void RigidBody::AngularVelocity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	Unmanaged->setAngularVelocity(*valueTemp);
	delete valueTemp;
}

BroadphaseProxy^ RigidBody::BroadphaseProxy::get()
{
	return BulletSharp::BroadphaseProxy::GetManaged(Unmanaged->getBroadphaseProxy());
}
void RigidBody::BroadphaseProxy::set(BulletSharp::BroadphaseProxy^ value)
{
	Unmanaged->setNewBroadphaseProxy(value->UnmanagedPointer);
}

Vector3 RigidBody::CenterOfMassPosition::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getCenterOfMassPosition());
}

Matrix RigidBody::CenterOfMassTransform::get()
{
	return Math::BtTransformToMatrix(&Unmanaged->getCenterOfMassTransform());
}
void RigidBody::CenterOfMassTransform::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	Unmanaged->setCenterOfMassTransform(*valueTemp);
	delete valueTemp;
}

RigidBodyFlags RigidBody::Flags::get()
{
	return (RigidBodyFlags)Unmanaged->getFlags();
}
void RigidBody::Flags::set(RigidBodyFlags value)
{
	Unmanaged->setFlags((btRigidBodyFlags) value);
}

Vector3 RigidBody::Gravity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getGravity());
}
void RigidBody::Gravity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	Unmanaged->setGravity(*valueTemp);
	delete valueTemp;
}

Vector3 RigidBody::InvInertiaDiagLocal::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getInvInertiaDiagLocal());
}
void RigidBody::InvInertiaDiagLocal::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	Unmanaged->setInvInertiaDiagLocal(*valueTemp);
	delete valueTemp;
}

Matrix RigidBody::InvInertiaTensorWorld::get()
{
	return Math::BtMatrix3x3ToMatrix(&Unmanaged->getInvInertiaTensorWorld());
}

btScalar RigidBody::InvMass::get()
{
	return Unmanaged->getInvMass();
}

btScalar RigidBody::LinearDamping::get()
{
	return Unmanaged->getLinearDamping();
}

Vector3 RigidBody::LinearFactor::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getLinearFactor());
}
void RigidBody::LinearFactor::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	Unmanaged->setLinearFactor(*valueTemp);
	delete valueTemp;
}

btScalar RigidBody::LinearSleepingThreshold::get()
{
	return Unmanaged->getLinearSleepingThreshold();
}

Vector3 RigidBody::LinearVelocity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getLinearVelocity());
}
void RigidBody::LinearVelocity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	Unmanaged->setLinearVelocity(*valueTemp);
	delete valueTemp;
}

BulletSharp::MotionState^ RigidBody::MotionState::get()
{
	/*
	btMotionState* state = Unmanaged->getMotionState();
	if (_motionState != nullptr && _motionState->UnmanagedPointer == state)
		return _motionState;

	_motionState = gcnew BulletSharp::MotionState(state);
	return _motionState;
	*/

	if (_motionState == nullptr)
	{
		btMotionState* state = Unmanaged->getMotionState();
		if (state != nullptr)
			_motionState = gcnew BulletSharp::MotionState(state);
	}
	return _motionState;
}
void RigidBody::MotionState::set(BulletSharp::MotionState^ value)
{
	Unmanaged->setMotionState(value->_unmanaged);
	_motionState = value;
}

#pragma managed(push, off)
void RigidBody_GetOrientation(btRigidBody* body, btQuaternion* orientation)
{
	*orientation = body->getOrientation();
}
#pragma managed(pop)
Quaternion RigidBody::Orientation::get()
{
	btQuaternion* orientationTemp = new btQuaternion;
	RigidBody_GetOrientation((btRigidBody*)_unmanaged, orientationTemp);
	Quaternion orientation = Math::BtQuatToQuaternion(orientationTemp);
	delete orientationTemp;
	return orientation;
}

Vector3 RigidBody::TotalForce::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getTotalForce());
}

Vector3 RigidBody::TotalTorque::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getTotalTorque());
}

bool RigidBody::WantsSleeping::get()
{
	return Unmanaged->wantsSleeping();
}

btRigidBody* RigidBody::UnmanagedPointer::get()
{
	return (btRigidBody*)CollisionObject::UnmanagedPointer;
}


btRigidBody::btRigidBodyConstructionInfo* RigidBody_GetUnmanagedConstructionInfo(
	btScalar mass, btMotionState* motionState, btCollisionShape* collisionShape, btVector3* localInertia = new btVector3())
{
	btRigidBody::btRigidBodyConstructionInfo* ret =
		new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape, *localInertia);
	delete localInertia;
	return ret;
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape)
{
	_info = RigidBody_GetUnmanagedConstructionInfo(mass,
		GetUnmanagedNullableNew(motionState), GetUnmanagedNullable(collisionShape));
	_motionState = motionState;
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape, Vector3 localInertia)
{
	_info = RigidBody_GetUnmanagedConstructionInfo(mass,
		GetUnmanagedNullableNew(motionState), GetUnmanagedNullable(collisionShape),
		Math::Vector3ToBtVector3(localInertia));
	_motionState = motionState;
}

btScalar RigidBodyConstructionInfo::AdditionalAngularDampingFactor::get()
{
	return _info->m_additionalAngularDampingFactor;
}
void RigidBodyConstructionInfo::AdditionalAngularDampingFactor::set(btScalar value)
{
	_info->m_additionalAngularDampingFactor = value;
}

btScalar RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::get()
{
	return _info->m_additionalAngularDampingThresholdSqr;
}
void RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::set(btScalar value)
{
	_info->m_additionalAngularDampingThresholdSqr = value;
}

bool RigidBodyConstructionInfo::AdditionalDamping::get()
{
	return _info->m_additionalDamping;
}
void RigidBodyConstructionInfo::AdditionalDamping::set(bool value)
{
	_info->m_additionalDamping = value;
}

btScalar RigidBodyConstructionInfo::AdditionalDampingFactor::get()
{
	return _info->m_additionalDampingFactor;
}
void RigidBodyConstructionInfo::AdditionalDampingFactor::set(btScalar value)
{
	_info->m_additionalDampingFactor = value;
}

btScalar RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::get()
{
	return _info->m_additionalLinearDampingThresholdSqr;
}
void RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::set(btScalar value)
{
	_info->m_additionalLinearDampingThresholdSqr = value;
}

btScalar RigidBodyConstructionInfo::AngularDamping::get()
{
	return _info->m_angularDamping;
}
void RigidBodyConstructionInfo::AngularDamping::set(btScalar value)
{
	_info->m_angularDamping = value;
}

btScalar RigidBodyConstructionInfo::AngularSleepingThreshold::get()
{
	return _info->m_angularSleepingThreshold;
}
void RigidBodyConstructionInfo::AngularSleepingThreshold::set(btScalar value)
{
	_info->m_angularSleepingThreshold = value;
}

CollisionShape^ RigidBodyConstructionInfo::CollisionShape::get()
{
	return BulletSharp::CollisionShape::GetManaged(_info->m_collisionShape);
}
void RigidBodyConstructionInfo::CollisionShape::set(BulletSharp::CollisionShape^ value)
{
	_info->m_collisionShape = value->UnmanagedPointer;
}

btScalar RigidBodyConstructionInfo::Friction::get()
{
	return _info->m_friction;
}
void RigidBodyConstructionInfo::Friction::set(btScalar value)
{
	_info->m_friction = value;
}

btScalar RigidBodyConstructionInfo::LinearDamping::get()
{
	return _info->m_linearDamping;
}
void RigidBodyConstructionInfo::LinearDamping::set(btScalar value)
{
	_info->m_linearDamping = value;
}

btScalar RigidBodyConstructionInfo::LinearSleepingThreshold::get()
{
	return _info->m_linearSleepingThreshold;
}
void RigidBodyConstructionInfo::LinearSleepingThreshold::set(btScalar value)
{
	_info->m_linearSleepingThreshold = value;
}

Vector3 RigidBodyConstructionInfo::LocalInertia::get()
{
	return Math::BtVector3ToVector3(&_info->m_localInertia);
}
void RigidBodyConstructionInfo::LocalInertia::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_localInertia);
}

btScalar RigidBodyConstructionInfo::Mass::get()
{
	return _info->m_mass;
}
void RigidBodyConstructionInfo::Mass::set(btScalar value)
{
	_info->m_mass = value;
}

BulletSharp::MotionState^ RigidBodyConstructionInfo::MotionState::get()
{
	btMotionState* state = _info->m_motionState;
	if (state != nullptr)
		_motionState = gcnew BulletSharp::MotionState(state);

	return _motionState;
}
void RigidBodyConstructionInfo::MotionState::set(BulletSharp::MotionState^ value)
{
	_info->m_motionState = value->_unmanaged;
}

btScalar RigidBodyConstructionInfo::Restitution::get()
{
	return _info->m_restitution;
}
void RigidBodyConstructionInfo::Restitution::set(btScalar value)
{
	_info->m_restitution = value;
}

Matrix RigidBodyConstructionInfo::StartWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_info->m_startWorldTransform);
}
void RigidBodyConstructionInfo::StartWorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_info->m_startWorldTransform);
}

btRigidBody::btRigidBodyConstructionInfo* RigidBodyConstructionInfo::UnmanagedPointer::get()
{
	return _info;
}
