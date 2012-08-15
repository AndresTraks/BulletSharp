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
: CollisionObject(new btRigidBody(*info->_unmanaged))
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
	VECTOR3_DEF(force);
	Unmanaged->applyCentralForce(VECTOR3_USE(force));
	VECTOR3_DEL(force);
}

void RigidBody::ApplyCentralImpulse(Vector3 impulse)
{
	VECTOR3_DEF(impulse);
	Unmanaged->applyCentralImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void RigidBody::ApplyDamping(btScalar timeStep)
{
	Unmanaged->applyDamping(timeStep);
}

void RigidBody::ApplyForce(Vector3 force, Vector3 relativePosition)
{
	VECTOR3_DEF(force);
	VECTOR3_DEF(relativePosition);
	
	Unmanaged->applyForce(VECTOR3_USE(force), VECTOR3_USE(relativePosition));
	
	VECTOR3_DEL(force);
	VECTOR3_DEL(relativePosition);
}

void RigidBody::ApplyGravity()
{
	Unmanaged->applyGravity();
}

void RigidBody::ApplyImpulse(Vector3 impulse, Vector3 relativePosition)
{
	VECTOR3_DEF(impulse);
	VECTOR3_DEF(relativePosition);

	Unmanaged->applyImpulse(VECTOR3_USE(impulse), VECTOR3_USE(relativePosition));
	
	VECTOR3_DEL(impulse);
	VECTOR3_DEL(relativePosition);
}

void RigidBody::ApplyTorque(Vector3 torque)
{
	VECTOR3_DEF(torque);
	Unmanaged->applyTorque(VECTOR3_USE(torque));
	VECTOR3_DEL(torque);
}

void RigidBody::ApplyTorqueImpulse(Vector3 torque)
{
	VECTOR3_DEF(torque);
	Unmanaged->applyTorqueImpulse(VECTOR3_USE(torque));
	VECTOR3_DEL(torque);
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
	VECTOR3_DEF(axis);
	btScalar ret = Unmanaged->computeAngularImpulseDenominator(VECTOR3_USE(axis));
	VECTOR3_DEL(axis);
	return ret;
}

btScalar RigidBody::ComputeImpulseDenominator(Vector3 pos, Vector3 normal)
{
	VECTOR3_DEF(pos);
	VECTOR3_DEF(normal);

	btScalar ret = Unmanaged->computeImpulseDenominator(VECTOR3_USE(pos), VECTOR3_USE(normal));

	VECTOR3_DEL(pos);
	VECTOR3_DEL(normal);
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
	VECTOR3_DEF(relativePosition);
	btVector3* velocityTemp = new btVector3;

	RigidBody_GetVelocityInLocalPoint((btRigidBody*)_unmanaged, velocityTemp, VECTOR3_PTR(relativePosition));
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);

	VECTOR3_DEL(relativePosition);
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
	VECTOR3_DEF(inertia);
	Unmanaged->setMassProps(mass, VECTOR3_USE(inertia));
	VECTOR3_DEL(inertia);
}

void RigidBody::SetSleepingThresholds(btScalar inertia, btScalar angular)
{
	Unmanaged->setSleepingThresholds(inertia, angular);
}

void RigidBody::Translate(Vector3 vector)
{
	VECTOR3_DEF(vector);
	Unmanaged->translate(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
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
	VECTOR3_DEF(linearComponent);
	VECTOR3_DEF(angularComponent);

	Unmanaged->internalApplyImpulse(VECTOR3_USE(linearComponent), VECTOR3_USE(angularComponent), impulseMagnitude);

	VECTOR3_DEL(linearComponent);
	VECTOR3_DEL(angularComponent);
}

void RigidBody::InternalApplyPushImpulse(Vector3 linearComponent, Vector3 angularComponent, btScalar impulseMagnitude)
{
	VECTOR3_DEF(linearComponent);
	VECTOR3_DEF(angularComponent);

	Unmanaged->internalApplyPushImpulse(VECTOR3_USE(linearComponent), VECTOR3_USE(angularComponent), impulseMagnitude);

	VECTOR3_DEL(linearComponent);
	VECTOR3_DEL(angularComponent);
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
	VECTOR3_DEF(value);
	Unmanaged->setAngularFactor(VECTOR3_USE(value));
	VECTOR3_DEL(value);
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
	VECTOR3_DEF(value);
	Unmanaged->setAngularVelocity(VECTOR3_USE(value));
	VECTOR3_DEL(value);
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
	VECTOR3_DEF(value);
	Unmanaged->setGravity(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

Vector3 RigidBody::InvInertiaDiagLocal::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getInvInertiaDiagLocal());
}
void RigidBody::InvInertiaDiagLocal::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Unmanaged->setInvInertiaDiagLocal(VECTOR3_USE(value));
	VECTOR3_DEL(value);
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
	VECTOR3_DEF(value);
	Unmanaged->setLinearFactor(VECTOR3_USE(value));
	VECTOR3_DEL(value);
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
	VECTOR3_DEF(value);
	Unmanaged->setLinearVelocity(VECTOR3_USE(value));
	VECTOR3_DEL(value);
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
	btScalar mass, btMotionState* motionState, btCollisionShape* collisionShape)
{
	return new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape);
}

btRigidBody::btRigidBodyConstructionInfo* RigidBody_GetUnmanagedConstructionInfoLocalInertia(
	btScalar mass, btMotionState* motionState, btCollisionShape* collisionShape, btVector3* localInertia)
{
	return new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape, *localInertia);
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape)
{
	_unmanaged = RigidBody_GetUnmanagedConstructionInfo(mass,
		GetUnmanagedNullable(motionState), GetUnmanagedNullable(collisionShape));
	_motionState = motionState;
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape, Vector3 localInertia)
{
	VECTOR3_DEF(localInertia);
	_unmanaged = RigidBody_GetUnmanagedConstructionInfoLocalInertia(mass,
		GetUnmanagedNullable(motionState), GetUnmanagedNullable(collisionShape),
		VECTOR3_PTR(localInertia));
	VECTOR3_DEL(localInertia);
	_motionState = motionState;
}

btScalar RigidBodyConstructionInfo::AdditionalAngularDampingFactor::get()
{
	return _unmanaged->m_additionalAngularDampingFactor;
}
void RigidBodyConstructionInfo::AdditionalAngularDampingFactor::set(btScalar value)
{
	_unmanaged->m_additionalAngularDampingFactor = value;
}

btScalar RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::get()
{
	return _unmanaged->m_additionalAngularDampingThresholdSqr;
}
void RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::set(btScalar value)
{
	_unmanaged->m_additionalAngularDampingThresholdSqr = value;
}

bool RigidBodyConstructionInfo::AdditionalDamping::get()
{
	return _unmanaged->m_additionalDamping;
}
void RigidBodyConstructionInfo::AdditionalDamping::set(bool value)
{
	_unmanaged->m_additionalDamping = value;
}

btScalar RigidBodyConstructionInfo::AdditionalDampingFactor::get()
{
	return _unmanaged->m_additionalDampingFactor;
}
void RigidBodyConstructionInfo::AdditionalDampingFactor::set(btScalar value)
{
	_unmanaged->m_additionalDampingFactor = value;
}

btScalar RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::get()
{
	return _unmanaged->m_additionalLinearDampingThresholdSqr;
}
void RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::set(btScalar value)
{
	_unmanaged->m_additionalLinearDampingThresholdSqr = value;
}

btScalar RigidBodyConstructionInfo::AngularDamping::get()
{
	return _unmanaged->m_angularDamping;
}
void RigidBodyConstructionInfo::AngularDamping::set(btScalar value)
{
	_unmanaged->m_angularDamping = value;
}

btScalar RigidBodyConstructionInfo::AngularSleepingThreshold::get()
{
	return _unmanaged->m_angularSleepingThreshold;
}
void RigidBodyConstructionInfo::AngularSleepingThreshold::set(btScalar value)
{
	_unmanaged->m_angularSleepingThreshold = value;
}

CollisionShape^ RigidBodyConstructionInfo::CollisionShape::get()
{
	return BulletSharp::CollisionShape::GetManaged(_unmanaged->m_collisionShape);
}
void RigidBodyConstructionInfo::CollisionShape::set(BulletSharp::CollisionShape^ value)
{
	_unmanaged->m_collisionShape = GetUnmanagedNullable(value);
}

btScalar RigidBodyConstructionInfo::Friction::get()
{
	return _unmanaged->m_friction;
}
void RigidBodyConstructionInfo::Friction::set(btScalar value)
{
	_unmanaged->m_friction = value;
}

btScalar RigidBodyConstructionInfo::LinearDamping::get()
{
	return _unmanaged->m_linearDamping;
}
void RigidBodyConstructionInfo::LinearDamping::set(btScalar value)
{
	_unmanaged->m_linearDamping = value;
}

btScalar RigidBodyConstructionInfo::LinearSleepingThreshold::get()
{
	return _unmanaged->m_linearSleepingThreshold;
}
void RigidBodyConstructionInfo::LinearSleepingThreshold::set(btScalar value)
{
	_unmanaged->m_linearSleepingThreshold = value;
}

Vector3 RigidBodyConstructionInfo::LocalInertia::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_localInertia);
}
void RigidBodyConstructionInfo::LocalInertia::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_localInertia);
}

btScalar RigidBodyConstructionInfo::Mass::get()
{
	return _unmanaged->m_mass;
}
void RigidBodyConstructionInfo::Mass::set(btScalar value)
{
	_unmanaged->m_mass = value;
}

BulletSharp::MotionState^ RigidBodyConstructionInfo::MotionState::get()
{
	btMotionState* state = _unmanaged->m_motionState;
	if (state != nullptr)
		_motionState = gcnew BulletSharp::MotionState(state);

	return _motionState;
}
void RigidBodyConstructionInfo::MotionState::set(BulletSharp::MotionState^ value)
{
	_unmanaged->m_motionState = value->_unmanaged;
}

btScalar RigidBodyConstructionInfo::Restitution::get()
{
	return _unmanaged->m_restitution;
}
void RigidBodyConstructionInfo::Restitution::set(btScalar value)
{
	_unmanaged->m_restitution = value;
}

Matrix RigidBodyConstructionInfo::StartWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_unmanaged->m_startWorldTransform);
}
void RigidBodyConstructionInfo::StartWorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_unmanaged->m_startWorldTransform);
}
