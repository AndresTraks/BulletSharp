#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionShape.h"
#include "Enums.h"
#include "MotionState.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

RigidBody::RigidBody(RigidBodyConstructionInfo^ info)
: CollisionObject(new btRigidBody(*info->UnmanagedPointer))
{
	_collisionShape = info->_collisionShape;
	_rootCollisionShape = info->_collisionShape;
	_motionState = info->_motionState;
}

RigidBody::RigidBody(btRigidBody* body)
: CollisionObject(body)
{
}

#ifndef DISABLE_CONSTRAINTS
void RigidBody::AddConstraintRef(TypedConstraint^ c)
{
	UnmanagedPointer->addConstraintRef(c->UnmanagedPointer);
}

TypedConstraint^ RigidBody::GetConstraintRef(int index)
{
	return gcnew TypedConstraint(UnmanagedPointer->getConstraintRef(index));
}

void RigidBody::RemoveConstraintRef(TypedConstraint^ c)
{
	UnmanagedPointer->removeConstraintRef(c->UnmanagedPointer);
}

int RigidBody::NumConstraintRefs::get()
{
	return UnmanagedPointer->getNumConstraintRefs();
}
#endif

void RigidBody::ApplyCentralForce(Vector3 force)
{
	UnmanagedPointer->applyCentralForce(*Math::Vector3ToBtVector3(force));
}

void RigidBody::ApplyCentralImpulse(Vector3 impulse)
{
	UnmanagedPointer->applyCentralImpulse(*Math::Vector3ToBtVector3(impulse));
}

void RigidBody::ApplyDamping(btScalar timeStep)
{
	UnmanagedPointer->applyDamping(timeStep);
}

void RigidBody::ApplyForce(Vector3 force, Vector3 rel_pos)
{
	UnmanagedPointer->applyForce(*Math::Vector3ToBtVector3(force), *Math::Vector3ToBtVector3(rel_pos));
}

void RigidBody::ApplyGravity()
{
	UnmanagedPointer->applyGravity();
}

void RigidBody::ApplyImpulse(Vector3 impulse, Vector3 rel_pos)
{
	UnmanagedPointer->applyImpulse(*Math::Vector3ToBtVector3(impulse), *Math::Vector3ToBtVector3(rel_pos));
}

void RigidBody::ApplyTorque(Vector3 torque)
{
	UnmanagedPointer->applyTorque(*Math::Vector3ToBtVector3(torque));
}

void RigidBody::ApplyTorqueImpulse(Vector3 torque)
{
	UnmanagedPointer->applyTorqueImpulse(*Math::Vector3ToBtVector3(torque));
}

bool RigidBody::CheckCollideWithOverride(CollisionObject^ co)
{
	return UnmanagedPointer->checkCollideWithOverride(co->UnmanagedPointer);
}

void RigidBody::ClearForces()
{
	UnmanagedPointer->clearForces();
}

btScalar RigidBody::ComputeAngularImpulseDenominator(Vector3 axis)
{
	return UnmanagedPointer->computeAngularImpulseDenominator(*Math::Vector3ToBtVector3(axis));
}

btScalar RigidBody::ComputeImpulseDenominator(Vector3 pos, Vector3 normal)
{
	return UnmanagedPointer->computeImpulseDenominator(*Math::Vector3ToBtVector3(pos), *Math::Vector3ToBtVector3(normal));
}

void RigidBody::GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	UnmanagedPointer->getAabb(*aabbMinTemp, *aabbMaxTemp);

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

#pragma managed(push, off)
void RigidBody_GetVelocityInLocalPoint(btRigidBody* body, btVector3* velocity, btVector3* rel_pos)
{
	*velocity = body->getVelocityInLocalPoint(*rel_pos);
}
#pragma managed(pop)
Vector3 RigidBody::GetVelocityInLocalPoint(Vector3 rel_pos)
{
	btVector3* rel_posTemp = Math::Vector3ToBtVector3(rel_pos);
	btVector3* velocityTemp = new btVector3;
	
	RigidBody_GetVelocityInLocalPoint(UnmanagedPointer, velocityTemp, rel_posTemp);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	
	delete rel_posTemp;
	delete velocityTemp;
	
	return velocity;
}

void RigidBody::IntegrateVelocities(btScalar step)
{
	UnmanagedPointer->integrateVelocities(step);
}

bool RigidBody::IsInWorld()
{
	return UnmanagedPointer->isInWorld();
}

void RigidBody::PredictIntegratedTransform(btScalar step, Matrix predictedTransform)
{
	btTransform* predictedTransformTemp = Math::MatrixToBtTransform(predictedTransform);
	UnmanagedPointer->predictIntegratedTransform(step, *predictedTransformTemp);
	delete predictedTransformTemp;
}

void RigidBody::ProceedToTransform(Matrix newTransform)
{
	btTransform* newTransformTemp = Math::MatrixToBtTransform(newTransform);
	UnmanagedPointer->proceedToTransform(*newTransformTemp);
	delete newTransformTemp;
}

void RigidBody::SaveKinematicState(btScalar step)
{
	UnmanagedPointer->saveKinematicState(step);
}

void RigidBody::SetDamping(btScalar lin_damping, btScalar ang_damping)
{
	UnmanagedPointer->setDamping(lin_damping, ang_damping);
}

void RigidBody::SetMassProps(btScalar mass, Vector3 inertia)
{
	UnmanagedPointer->setMassProps(mass, *Math::Vector3ToBtVector3(inertia));
}

void RigidBody::SetSleepingThresholds(btScalar inertia, btScalar angular)
{
	UnmanagedPointer->setSleepingThresholds(inertia, angular);
}

void RigidBody::Translate(Vector3 v)
{
	UnmanagedPointer->translate(*Math::Vector3ToBtVector3(v));
}

void RigidBody::UpdateDeactivation(btScalar timeStep)
{
	UnmanagedPointer->updateDeactivation(timeStep);
}

void RigidBody::UpdateInertiaTensor()
{
	UnmanagedPointer->updateInertiaTensor();
}

RigidBody^ RigidBody::Upcast(CollisionObject^ colObj)
{
	btRigidBody* body = btRigidBody::upcast(colObj->UnmanagedPointer);
	if (body == nullptr)
		return nullptr;
	return gcnew RigidBody(body);
}

#ifndef DISABLE_INTERNAL
void RigidBody::InternalApplyImpulse(Vector3 linearComponent, Vector3 angularComponent, btScalar impulseMagnitude)
{
	btVector3* linearComponentTemp = Math::Vector3ToBtVector3(linearComponent);
	btVector3* angularComponentTemp = Math::Vector3ToBtVector3(angularComponent);

	UnmanagedPointer->internalApplyImpulse(*linearComponentTemp, *angularComponentTemp, impulseMagnitude);

	delete linearComponentTemp;
	delete angularComponentTemp;
}

void RigidBody::InternalApplyPushImpulse(Vector3 linearComponent, Vector3 angularComponent, btScalar impulseMagnitude)
{
	btVector3* linearComponentTemp = Math::Vector3ToBtVector3(linearComponent);
	btVector3* angularComponentTemp = Math::Vector3ToBtVector3(angularComponent);

	UnmanagedPointer->internalApplyPushImpulse(*linearComponentTemp, *angularComponentTemp, impulseMagnitude);

	delete linearComponentTemp;
	delete angularComponentTemp;
}

void RigidBody::InternalWritebackVelocity(btScalar timeStep)
{
	UnmanagedPointer->internalWritebackVelocity(timeStep);
}

void RigidBody::InternalWritebackVelocity()
{
	UnmanagedPointer->internalWritebackVelocity();
}

Vector3 RigidBody::InternalAngularFactor::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->internalGetAngularFactor());
}

Vector3 RigidBody::InternalDeltaAngularVelocity::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->internalGetDeltaAngularVelocity());
}

Vector3 RigidBody::InternalDeltaLinearVelocity::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->internalGetDeltaLinearVelocity());
}

Vector3 RigidBody::InternalInvMass::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->internalGetInvMass());
}

Vector3 RigidBody::InternalPushVelocity::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->internalGetPushVelocity());
}

Vector3 RigidBody::InternalTurnVelocity::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->internalGetTurnVelocity());
}
#endif


btScalar RigidBody::AngularDamping::get()
{
	return UnmanagedPointer->getAngularDamping();
}

Vector3 RigidBody::AngularFactor::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAngularFactor());
}
void RigidBody::AngularFactor::set(Vector3 value)
{
	UnmanagedPointer->setAngularFactor(*Math::Vector3ToBtVector3(value));
}

btScalar RigidBody::AngularSleepingThreshold::get()
{
	return UnmanagedPointer->getAngularSleepingThreshold();
}

Vector3 RigidBody::AngularVelocity::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAngularVelocity());
}
void RigidBody::AngularVelocity::set(Vector3 value)
{
	UnmanagedPointer->setAngularVelocity(*Math::Vector3ToBtVector3(value));
}

BroadphaseProxy^ RigidBody::BroadphaseProxy::get()
{
	return gcnew BulletSharp::BroadphaseProxy(UnmanagedPointer->getBroadphaseProxy());
}
void RigidBody::BroadphaseProxy::set(BulletSharp::BroadphaseProxy^ value)
{
	UnmanagedPointer->setNewBroadphaseProxy(value->UnmanagedPointer);
}

Vector3 RigidBody::CenterOfMassPosition::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getCenterOfMassPosition());
}

Matrix RigidBody::CenterOfMassTransform::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getCenterOfMassTransform());
}
void RigidBody::CenterOfMassTransform::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	UnmanagedPointer->setCenterOfMassTransform(*valueTemp);
	delete valueTemp;
}

CollisionShape^ RigidBody::CollisionShape::get()
{
	return gcnew BulletSharp::CollisionShape(UnmanagedPointer->getCollisionShape());
}

RigidBodyFlags RigidBody::Flags::get()
{
	return (RigidBodyFlags)UnmanagedPointer->getFlags();
}
void RigidBody::Flags::set(RigidBodyFlags value)
{
	UnmanagedPointer->setFlags((btRigidBodyFlags) value);
}

Vector3 RigidBody::Gravity::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getGravity());
}
void RigidBody::Gravity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setGravity(*valueTemp);
	delete valueTemp;
}

Vector3 RigidBody::InvInertiaDiagLocal::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getInvInertiaDiagLocal());
}
void RigidBody::InvInertiaDiagLocal::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setInvInertiaDiagLocal(*valueTemp);
	delete valueTemp;
}

Matrix RigidBody::InvInertiaTensorWorld::get()
{
	return Math::BtMatrix3x3ToMatrix(&UnmanagedPointer->getInvInertiaTensorWorld());
}

btScalar RigidBody::InvMass::get()
{
	return UnmanagedPointer->getInvMass();
}

btScalar RigidBody::LinearDamping::get()
{
	return UnmanagedPointer->getLinearDamping();
}

Vector3 RigidBody::LinearFactor::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getLinearFactor());
}
void RigidBody::LinearFactor::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setLinearFactor(*valueTemp);
	delete valueTemp;
}

btScalar RigidBody::LinearSleepingThreshold::get()
{
	return UnmanagedPointer->getLinearSleepingThreshold();
}

Vector3 RigidBody::LinearVelocity::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getLinearVelocity());
}
void RigidBody::LinearVelocity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setLinearVelocity(*valueTemp);
	delete valueTemp;
}

BulletSharp::MotionState^ RigidBody::MotionState::get()
{
	if (_motionState == nullptr)
	{
		btMotionState* state = UnmanagedPointer->getMotionState();
		if (state != nullptr)
			_motionState = gcnew BulletSharp::MotionState(state);
	}
	return _motionState;
}
void RigidBody::MotionState::set(BulletSharp::MotionState^ value)
{
	UnmanagedPointer->setMotionState(value->UnmanagedPointer);
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
	btQuaternion* orientationTemp = new btQuaternion();
	RigidBody_GetOrientation(UnmanagedPointer, orientationTemp);
	Quaternion orientation = Math::BtQuatToQuaternion(orientationTemp);
	delete orientationTemp;
	return orientation;
}

Vector3 RigidBody::TotalForce::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getTotalForce());
}

Vector3 RigidBody::TotalTorque::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getTotalTorque());
}

bool RigidBody::WantsSleeping::get()
{
	return UnmanagedPointer->wantsSleeping();
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

RigidBody::RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape)
{
	btCollisionShape* btColShape = (collisionShape != nullptr) ?
		collisionShape->UnmanagedPointer : nullptr;
	btMotionState* btMotState = (motionState != nullptr) ?
		motionState->UnmanagedPointer : nullptr;

	_info = RigidBody_GetUnmanagedConstructionInfo(mass, btMotState, btColShape);
	_collisionShape = collisionShape;
	_motionState = motionState;
}

RigidBody::RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape, Vector3 localInertia)
{
	btCollisionShape* btColShape = (collisionShape != nullptr) ?
		collisionShape->UnmanagedPointer : nullptr;
	btMotionState* btMotState = (motionState != nullptr) ?
		motionState->UnmanagedPointer : nullptr;

	_info = RigidBody_GetUnmanagedConstructionInfo(mass, btMotState, btColShape, Math::Vector3ToBtVector3(localInertia));
	_collisionShape = collisionShape;
	_motionState = motionState;
}

btScalar RigidBody::RigidBodyConstructionInfo::AdditionalAngularDampingFactor::get()
{
	return _info->m_additionalAngularDampingFactor;
}
void RigidBody::RigidBodyConstructionInfo::AdditionalAngularDampingFactor::set(btScalar value)
{
	_info->m_additionalAngularDampingFactor = value;
}

btScalar RigidBody::RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::get()
{
	return _info->m_additionalAngularDampingThresholdSqr;
}
void RigidBody::RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::set(btScalar value)
{
	_info->m_additionalAngularDampingThresholdSqr = value;
}

bool RigidBody::RigidBodyConstructionInfo::AdditionalDamping::get()
{
	return _info->m_additionalDamping;
}
void RigidBody::RigidBodyConstructionInfo::AdditionalDamping::set(bool value)
{
	_info->m_additionalDamping = value;
}

btScalar RigidBody::RigidBodyConstructionInfo::AdditionalDampingFactor::get()
{
	return _info->m_additionalDampingFactor;
}
void RigidBody::RigidBodyConstructionInfo::AdditionalDampingFactor::set(btScalar value)
{
	_info->m_additionalDampingFactor = value;
}

btScalar RigidBody::RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::get()
{
	return _info->m_additionalLinearDampingThresholdSqr;
}
void RigidBody::RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::set(btScalar value)
{
	_info->m_additionalLinearDampingThresholdSqr = value;
}

btScalar RigidBody::RigidBodyConstructionInfo::AngularDamping::get()
{
	return _info->m_angularDamping;
}
void RigidBody::RigidBodyConstructionInfo::AngularDamping::set(btScalar value)
{
	_info->m_angularDamping = value;
}

btScalar RigidBody::RigidBodyConstructionInfo::AngularSleepingThreshold::get()
{
	return _info->m_angularSleepingThreshold;
}
void RigidBody::RigidBodyConstructionInfo::AngularSleepingThreshold::set(btScalar value)
{
	_info->m_angularSleepingThreshold = value;
}

CollisionShape^ RigidBody::RigidBodyConstructionInfo::CollisionShape::get()
{
	return gcnew BulletSharp::CollisionShape(_info->m_collisionShape);
}
void RigidBody::RigidBodyConstructionInfo::CollisionShape::set(BulletSharp::CollisionShape^ value)
{
	_info->m_collisionShape = value->UnmanagedPointer;
}

btScalar RigidBody::RigidBodyConstructionInfo::Friction::get()
{
	return _info->m_friction;
}
void RigidBody::RigidBodyConstructionInfo::Friction::set(btScalar value)
{
	_info->m_friction = value;
}

btScalar RigidBody::RigidBodyConstructionInfo::LinearDamping::get()
{
	return _info->m_linearDamping;
}
void RigidBody::RigidBodyConstructionInfo::LinearDamping::set(btScalar value)
{
	_info->m_linearDamping = value;
}

btScalar RigidBody::RigidBodyConstructionInfo::LinearSleepingThreshold::get()
{
	return _info->m_linearSleepingThreshold;
}
void RigidBody::RigidBodyConstructionInfo::LinearSleepingThreshold::set(btScalar value)
{
	_info->m_linearSleepingThreshold = value;
}

Vector3 RigidBody::RigidBodyConstructionInfo::LocalInertia::get()
{
	return Math::BtVector3ToVector3(&_info->m_localInertia);
}
void RigidBody::RigidBodyConstructionInfo::LocalInertia::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_localInertia);
}

btScalar RigidBody::RigidBodyConstructionInfo::Mass::get()
{
	return _info->m_mass;
}
void RigidBody::RigidBodyConstructionInfo::Mass::set(btScalar value)
{
	_info->m_mass = value;
}

BulletSharp::MotionState^ RigidBody::RigidBodyConstructionInfo::MotionState::get()
{
	btMotionState* state = _info->m_motionState;
	if (state != nullptr)
		_motionState = gcnew BulletSharp::MotionState(state);

	return _motionState;
}
void RigidBody::RigidBodyConstructionInfo::MotionState::set(BulletSharp::MotionState^ value)
{
	_info->m_motionState = value->UnmanagedPointer;
}

btScalar RigidBody::RigidBodyConstructionInfo::Restitution::get()
{
	return _info->m_restitution;
}
void RigidBody::RigidBodyConstructionInfo::Restitution::set(btScalar value)
{
	_info->m_restitution = value;
}

Matrix RigidBody::RigidBodyConstructionInfo::StartWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_info->m_startWorldTransform);
}
void RigidBody::RigidBodyConstructionInfo::StartWorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_info->m_startWorldTransform);
}

btRigidBody::btRigidBodyConstructionInfo* RigidBody::RigidBodyConstructionInfo::UnmanagedPointer::get()
{
	return _info;
}
