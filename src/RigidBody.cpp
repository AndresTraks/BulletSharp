#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionShape.h"
#include "DefaultMotionState.h"
#include "MotionState.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

RigidBodyConstructionInfo::~RigidBodyConstructionInfo()
{
	this->!RigidBodyConstructionInfo();
}

RigidBodyConstructionInfo::!RigidBodyConstructionInfo()
{
	ALIGNED_FREE(_native);
	_native = NULL;
}

#ifndef BT_USE_SSE_IN_API
#pragma managed(push, off)
btRigidBody::btRigidBodyConstructionInfo* RigidBody_GetUnmanagedConstructionInfo(
	btScalar mass, btMotionState* motionState, btCollisionShape* collisionShape)
{
	return ALIGNED_NEW(btRigidBody::btRigidBodyConstructionInfo) (mass, motionState, collisionShape);
}
#pragma managed(pop)
#endif

btRigidBody::btRigidBodyConstructionInfo* RigidBody_GetUnmanagedConstructionInfoLocalInertia(
	btScalar mass, btMotionState* motionState, btCollisionShape* collisionShape, btVector3* localInertia)
{
	return ALIGNED_NEW(btRigidBody::btRigidBodyConstructionInfo) (mass, motionState, collisionShape, *localInertia);
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape)
{
#ifdef BT_USE_SSE_IN_API
	btVector3* localInertia = ALIGNED_NEW(btVector3) (0,0,0); // default localInertia parameter is not aligned
	_native = RigidBody_GetUnmanagedConstructionInfoLocalInertia(mass,
		GetUnmanagedNullable(motionState), GetUnmanagedNullable(collisionShape), localInertia);
	ALIGNED_FREE(localInertia);
#else
	_native = RigidBody_GetUnmanagedConstructionInfo(mass,
		GetUnmanagedNullable(motionState), GetUnmanagedNullable(collisionShape));
#endif
	_collisionShape = collisionShape;
	_motionState = motionState;
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, BulletSharp::CollisionShape^ collisionShape, Vector3 localInertia)
{
	VECTOR3_CONV(localInertia);
	_native = RigidBody_GetUnmanagedConstructionInfoLocalInertia(mass,
		GetUnmanagedNullable(motionState), GetUnmanagedNullable(collisionShape),
		VECTOR3_PTR(localInertia));
	VECTOR3_DEL(localInertia);
	_collisionShape = collisionShape;
	_motionState = motionState;
}

btScalar RigidBodyConstructionInfo::AdditionalAngularDampingFactor::get()
{
	return _native->m_additionalAngularDampingFactor;
}
void RigidBodyConstructionInfo::AdditionalAngularDampingFactor::set(btScalar value)
{
	_native->m_additionalAngularDampingFactor = value;
}

btScalar RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::get()
{
	return _native->m_additionalAngularDampingThresholdSqr;
}
void RigidBodyConstructionInfo::AdditionalAngularDampingThresholdSqr::set(btScalar value)
{
	_native->m_additionalAngularDampingThresholdSqr = value;
}

bool RigidBodyConstructionInfo::AdditionalDamping::get()
{
	return _native->m_additionalDamping;
}
void RigidBodyConstructionInfo::AdditionalDamping::set(bool value)
{
	_native->m_additionalDamping = value;
}

btScalar RigidBodyConstructionInfo::AdditionalDampingFactor::get()
{
	return _native->m_additionalDampingFactor;
}
void RigidBodyConstructionInfo::AdditionalDampingFactor::set(btScalar value)
{
	_native->m_additionalDampingFactor = value;
}

btScalar RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::get()
{
	return _native->m_additionalLinearDampingThresholdSqr;
}
void RigidBodyConstructionInfo::AdditionalLinearDampingThresholdSqr::set(btScalar value)
{
	_native->m_additionalLinearDampingThresholdSqr = value;
}

btScalar RigidBodyConstructionInfo::AngularDamping::get()
{
	return _native->m_angularDamping;
}
void RigidBodyConstructionInfo::AngularDamping::set(btScalar value)
{
	_native->m_angularDamping = value;
}

btScalar RigidBodyConstructionInfo::AngularSleepingThreshold::get()
{
	return _native->m_angularSleepingThreshold;
}
void RigidBodyConstructionInfo::AngularSleepingThreshold::set(btScalar value)
{
	_native->m_angularSleepingThreshold = value;
}

CollisionShape^ RigidBodyConstructionInfo::CollisionShape::get()
{
	return _collisionShape;
}
void RigidBodyConstructionInfo::CollisionShape::set(BulletSharp::CollisionShape^ value)
{
	_collisionShape = value;
	_native->m_collisionShape = GetUnmanagedNullable(value);
}

btScalar RigidBodyConstructionInfo::Friction::get()
{
	return _native->m_friction;
}
void RigidBodyConstructionInfo::Friction::set(btScalar value)
{
	_native->m_friction = value;
}

btScalar RigidBodyConstructionInfo::LinearDamping::get()
{
	return _native->m_linearDamping;
}
void RigidBodyConstructionInfo::LinearDamping::set(btScalar value)
{
	_native->m_linearDamping = value;
}

btScalar RigidBodyConstructionInfo::LinearSleepingThreshold::get()
{
	return _native->m_linearSleepingThreshold;
}
void RigidBodyConstructionInfo::LinearSleepingThreshold::set(btScalar value)
{
	_native->m_linearSleepingThreshold = value;
}

Vector3 RigidBodyConstructionInfo::LocalInertia::get()
{
	return Math::BtVector3ToVector3(&_native->m_localInertia);
}
void RigidBodyConstructionInfo::LocalInertia::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_localInertia);
}

btScalar RigidBodyConstructionInfo::Mass::get()
{
	return _native->m_mass;
}
void RigidBodyConstructionInfo::Mass::set(btScalar value)
{
	_native->m_mass = value;
}

BulletSharp::MotionState^ RigidBodyConstructionInfo::MotionState::get()
{
	return _motionState;
}
void RigidBodyConstructionInfo::MotionState::set(BulletSharp::MotionState^ value)
{
	_native->m_motionState = GetUnmanagedNullable(value);
	_motionState = value;
}

btScalar RigidBodyConstructionInfo::Restitution::get()
{
	return _native->m_restitution;
}
void RigidBodyConstructionInfo::Restitution::set(btScalar value)
{
	_native->m_restitution = value;
}

btScalar RigidBodyConstructionInfo::RollingFriction::get()
{
	return _native->m_rollingFriction;
}
void RigidBodyConstructionInfo::RollingFriction::set(btScalar value)
{
	_native->m_rollingFriction = value;
}

Matrix RigidBodyConstructionInfo::StartWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->m_startWorldTransform);
}
void RigidBodyConstructionInfo::StartWorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_startWorldTransform);
}


#define Native static_cast<btRigidBody*>(_native)

RigidBody::RigidBody(RigidBodyConstructionInfo^ constructionInfo)
	: CollisionObject(ALIGNED_NEW(btRigidBody) (*constructionInfo->_native))
{
	_collisionShape = constructionInfo->CollisionShape;
	_motionState = constructionInfo->_motionState;
}

#ifndef DISABLE_CONSTRAINTS
void RigidBody::AddConstraintRef(TypedConstraint^ c)
{
	Native->addConstraintRef(c->_native);
}
#endif

void RigidBody::ApplyCentralForce(Vector3 force)
{
	VECTOR3_CONV(force);
	Native->applyCentralForce(VECTOR3_USE(force));
	VECTOR3_DEL(force);
}

void RigidBody::ApplyCentralImpulse(Vector3 impulse)
{
	VECTOR3_CONV(impulse);
	Native->applyCentralImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void RigidBody::ApplyDamping(btScalar timeStep)
{
	Native->applyDamping(timeStep);
}

void RigidBody::ApplyForce(Vector3 force, Vector3 relativePosition)
{
	VECTOR3_CONV(force);
	VECTOR3_CONV(relativePosition);
	Native->applyForce(VECTOR3_USE(force), VECTOR3_USE(relativePosition));
	VECTOR3_DEL(force);
	VECTOR3_DEL(relativePosition);
}

void RigidBody::ApplyGravity()
{
	Native->applyGravity();
}

void RigidBody::ApplyImpulse(Vector3 impulse, Vector3 relativePosition)
{
	VECTOR3_CONV(impulse);
	VECTOR3_CONV(relativePosition);
	Native->applyImpulse(VECTOR3_USE(impulse), VECTOR3_USE(relativePosition));
	VECTOR3_DEL(impulse);
	VECTOR3_DEL(relativePosition);
}

void RigidBody::ApplyTorque(Vector3 torque)
{
	VECTOR3_CONV(torque);
	Native->applyTorque(VECTOR3_USE(torque));
	VECTOR3_DEL(torque);
}

void RigidBody::ApplyTorqueImpulse(Vector3 torque)
{
	VECTOR3_CONV(torque);
	Native->applyTorqueImpulse(VECTOR3_USE(torque));
	VECTOR3_DEL(torque);
}

void RigidBody::ClearForces()
{
	Native->clearForces();
}

btScalar RigidBody::ComputeAngularImpulseDenominator(Vector3 axis)
{
	VECTOR3_CONV(axis);
	btScalar ret = Native->computeAngularImpulseDenominator(VECTOR3_USE(axis));
	VECTOR3_DEL(axis);
	return ret;
}

#pragma managed(push, off)
void RigidBody_ComputeGyroscopicForceExplicit(btRigidBody* body, btVector3* ret, btScalar maxGyroscopicForce)
{
	*ret = body->computeGyroscopicForceExplicit(maxGyroscopicForce);
}
#pragma managed(pop)
Vector3 RigidBody::ComputeGyroscopicForceExplicit(btScalar maxGyroscopicForce)
{
	btVector3* retTemp = ALIGNED_NEW(btVector3);
	RigidBody_ComputeGyroscopicForceExplicit(Native, retTemp, maxGyroscopicForce);
	Vector3 ret = Math::BtVector3ToVector3(retTemp);
	ALIGNED_FREE(retTemp);
	return ret;
}

#pragma managed(push, off)
void RigidBody_ComputeGyroscopicImpulseImplicit_Body(btRigidBody* body, btVector3* ret, btScalar step)
{
	*ret = body->computeGyroscopicImpulseImplicit_Body(step);
}
#pragma managed(pop)
Vector3 RigidBody::ComputeGyroscopicImpulseImplicitBody(btScalar step)
{
	btVector3* retTemp = ALIGNED_NEW(btVector3);
	RigidBody_ComputeGyroscopicImpulseImplicit_Body(Native, retTemp, step);
	Vector3 ret = Math::BtVector3ToVector3(retTemp);
	ALIGNED_FREE(retTemp);
	return ret;
}

#pragma managed(push, off)
void RigidBody_ComputeGyroscopicImpulseImplicit_World(btRigidBody* body, btVector3* ret, btScalar dt)
{
	*ret = body->computeGyroscopicImpulseImplicit_World(dt);
}
#pragma managed(pop)
Vector3 RigidBody::ComputeGyroscopicImpulseImplicitWorld(btScalar deltaTime)
{
	btVector3* retTemp = ALIGNED_NEW(btVector3);
	RigidBody_ComputeGyroscopicImpulseImplicit_World(Native, retTemp, deltaTime);
	Vector3 ret = Math::BtVector3ToVector3(retTemp);
	ALIGNED_FREE(retTemp);
	return ret;
}

btScalar RigidBody::ComputeImpulseDenominator(Vector3 pos, Vector3 normal)
{
	VECTOR3_CONV(pos);
	VECTOR3_CONV(normal);
	btScalar ret = Native->computeImpulseDenominator(VECTOR3_USE(pos), VECTOR3_USE(normal));
	VECTOR3_DEL(pos);
	VECTOR3_DEL(normal);
	return ret;
}

void RigidBody::GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);

	Native->getAabb(*aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ RigidBody::GetConstraintRef(int index)
{
	return TypedConstraint::GetManaged(Native->getConstraintRef(index));
}
#endif

#pragma managed(push, off)
void RigidBody_GetVelocityInLocalPoint(btRigidBody* body, btVector3* velocity, btVector3* rel_pos)
{
	*velocity = body->getVelocityInLocalPoint(*rel_pos);
}
#pragma managed(pop)
Vector3 RigidBody::GetVelocityInLocalPoint(Vector3 relativePosition)
{
	VECTOR3_CONV(relativePosition);
	btVector3* velocityTemp = ALIGNED_NEW(btVector3);

	RigidBody_GetVelocityInLocalPoint(Native, velocityTemp, VECTOR3_PTR(relativePosition));
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);

	VECTOR3_DEL(relativePosition);
	ALIGNED_FREE(velocityTemp);

	return velocity;
}

void RigidBody::IntegrateVelocities(btScalar step)
{
	Native->integrateVelocities(step);
}

void RigidBody::PredictIntegratedTransform(btScalar step, [Out] Matrix% predictedTransform)
{
	btTransform* predictedTransformTemp = ALIGNED_NEW(btTransform);
	Native->predictIntegratedTransform(step, *predictedTransformTemp);
	Math::BtTransformToMatrix(predictedTransformTemp, predictedTransform);
	ALIGNED_FREE(predictedTransformTemp);
}

void RigidBody::ProceedToTransform(Matrix newTrans)
{
	TRANSFORM_CONV(newTrans);
	Native->proceedToTransform(TRANSFORM_USE(newTrans));
	TRANSFORM_DEL(newTrans);
}

#ifndef DISABLE_CONSTRAINTS
void RigidBody::RemoveConstraintRef(TypedConstraint^ c)
{
	Native->removeConstraintRef(c->_native);
}
#endif

void RigidBody::SaveKinematicState(btScalar step)
{
	Native->saveKinematicState(step);
}

void RigidBody::SetDamping(btScalar linearDamping, btScalar angularDamping)
{
	Native->setDamping(linearDamping, angularDamping);
}

void RigidBody::SetMassProps(btScalar mass, Vector3 inertia)
{
	VECTOR3_CONV(inertia);
	Native->setMassProps(mass, VECTOR3_USE(inertia));
	VECTOR3_DEL(inertia);
}

void RigidBody::SetSleepingThresholds(btScalar linear, btScalar angular)
{
	Native->setSleepingThresholds(linear, angular);
}

void RigidBody::Translate(Vector3 vector)
{
	VECTOR3_CONV(vector);
	Native->translate(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
}

RigidBody^ RigidBody::Upcast(CollisionObject^ colObj)
{
	btRigidBody* body = btRigidBody::upcast(colObj->_native);
	return (RigidBody^)CollisionObject::GetManaged(body);
}

void RigidBody::UpdateDeactivation(btScalar timeStep)
{
	Native->updateDeactivation(timeStep);
}

void RigidBody::UpdateInertiaTensor()
{
	Native->updateInertiaTensor();
}

btScalar RigidBody::AngularDamping::get()
{
	return Native->getAngularDamping();
}

Vector3 RigidBody::AngularFactor::get()
{
	return Math::BtVector3ToVector3(&Native->getAngularFactor());
}
void RigidBody::AngularFactor::set(Vector3 value)
{
	VECTOR3_CONV(value);
	Native->setAngularFactor(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

btScalar RigidBody::AngularSleepingThreshold::get()
{
	return Native->getAngularSleepingThreshold();
}

Vector3 RigidBody::AngularVelocity::get()
{
	return Math::BtVector3ToVector3(&Native->getAngularVelocity());
}
void RigidBody::AngularVelocity::set(Vector3 angVel)
{
	VECTOR3_CONV(angVel);
	Native->setAngularVelocity(VECTOR3_USE(angVel));
	VECTOR3_DEL(angVel);
}

BroadphaseProxy^ RigidBody::BroadphaseProxy::get()
{
	return BulletSharp::BroadphaseProxy::GetManaged(Native->getBroadphaseProxy());
}
void RigidBody::BroadphaseProxy::set(BulletSharp::BroadphaseProxy^ value)
{
	Native->setNewBroadphaseProxy(value->_native);
}

Vector3 RigidBody::CenterOfMassPosition::get()
{
	return Math::BtVector3ToVector3(&Native->getCenterOfMassPosition());
}

Matrix RigidBody::CenterOfMassTransform::get()
{
	return Math::BtTransformToMatrix(&Native->getCenterOfMassTransform());
}
void RigidBody::CenterOfMassTransform::set(Matrix xform)
{
	TRANSFORM_CONV(xform);
	Native->setCenterOfMassTransform(TRANSFORM_USE(xform));
	TRANSFORM_DEL(xform);
}

int RigidBody::ContactSolverType::get()
{
	return Native->m_contactSolverType;
}
void RigidBody::ContactSolverType::set(int value)
{
	Native->m_contactSolverType = value;
}

RigidBodyFlags RigidBody::Flags::get()
{
	return (RigidBodyFlags)Native->getFlags();
}
void RigidBody::Flags::set(RigidBodyFlags flags)
{
	Native->setFlags((btRigidBodyFlags) flags);
}

int RigidBody::FrictionSolverType::get()
{
	return Native->m_frictionSolverType;
}
void RigidBody::FrictionSolverType::set(int value)
{
	Native->m_frictionSolverType = value;
}

Vector3 RigidBody::Gravity::get()
{
	return Math::BtVector3ToVector3(&Native->getGravity());
}
void RigidBody::Gravity::set(Vector3 acceleration)
{
	VECTOR3_CONV(acceleration);
	Native->setGravity(VECTOR3_USE(acceleration));
	VECTOR3_DEL(acceleration);
}

Vector3 RigidBody::InvInertiaDiagLocal::get()
{
	return Math::BtVector3ToVector3(&Native->getInvInertiaDiagLocal());
}
void RigidBody::InvInertiaDiagLocal::set(Vector3 diagInvInertia)
{
	VECTOR3_CONV(diagInvInertia);
	Native->setInvInertiaDiagLocal(VECTOR3_USE(diagInvInertia));
	VECTOR3_DEL(diagInvInertia);
}

Matrix RigidBody::InvInertiaTensorWorld::get()
{
	return Math::BtMatrix3x3ToMatrix(&Native->getInvInertiaTensorWorld());
}

btScalar RigidBody::InvMass::get()
{
	return Native->getInvMass();
}

bool RigidBody::IsInWorld::get()
{
	return Native->isInWorld();
}

btScalar RigidBody::LinearDamping::get()
{
	return Native->getLinearDamping();
}

Vector3 RigidBody::LinearFactor::get()
{
	return Math::BtVector3ToVector3(&Native->getLinearFactor());
}
void RigidBody::LinearFactor::set(Vector3 linearFactor)
{
	VECTOR3_CONV(linearFactor);
	Native->setLinearFactor(VECTOR3_USE(linearFactor));
	VECTOR3_DEL(linearFactor);
}

btScalar RigidBody::LinearSleepingThreshold::get()
{
	return Native->getLinearSleepingThreshold();
}

Vector3 RigidBody::LinearVelocity::get()
{
	return Math::BtVector3ToVector3(&Native->getLinearVelocity());
}
void RigidBody::LinearVelocity::set(Vector3 linVel)
{
	VECTOR3_CONV(linVel);
	Native->setLinearVelocity(VECTOR3_USE(linVel));
	VECTOR3_DEL(linVel);
}

#pragma managed(push, off)
void RigidBody_GetLocalInertia(btRigidBody* body, btVector3* ret)
{
	*ret = body->getLocalInertia();
}
#pragma managed(pop)
Vector3 RigidBody::LocalInertia::get()
{
	btVector3* retTemp = ALIGNED_NEW(btVector3);
	RigidBody_GetLocalInertia(Native, retTemp);
	Vector3 ret = Math::BtVector3ToVector3(retTemp);
	ALIGNED_FREE(retTemp);
	return ret;
}

BulletSharp::MotionState^ RigidBody::MotionState::get()
{
	return _motionState;
}
void RigidBody::MotionState::set(BulletSharp::MotionState^ motionState)
{
	Native->setMotionState(GetUnmanagedNullable(motionState));
	_motionState = motionState;
}
#ifndef DISABLE_CONSTRAINTS
int RigidBody::NumConstraintRefs::get()
{
	return Native->getNumConstraintRefs();
}
#endif
#pragma managed(push, off)
void RigidBody_GetOrientation(btRigidBody* body, btQuaternion* orientation)
{
	//FIXME: *orientation = body->getOrientation();
	body->getWorldTransform().getBasis().getRotation(*orientation);
}
#pragma managed(pop)
Quaternion RigidBody::Orientation::get()
{
	btQuaternion* orientationTemp = ALIGNED_NEW(btQuaternion);
	RigidBody_GetOrientation(Native, orientationTemp);
	Quaternion orientation = Math::BtQuatToQuaternion(orientationTemp);
	ALIGNED_FREE(orientationTemp);
	return orientation;
}

Vector3 RigidBody::TotalForce::get()
{
	return Math::BtVector3ToVector3(&Native->getTotalForce());
}

Vector3 RigidBody::TotalTorque::get()
{
	return Math::BtVector3ToVector3(&Native->getTotalTorque());
}

bool RigidBody::WantsSleeping::get()
{
	return Native->wantsSleeping();
}
