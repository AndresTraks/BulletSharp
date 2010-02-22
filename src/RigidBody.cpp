#include "StdAfx.h"

#include "RigidBody.h"

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

void RigidBody::AddConstraintRef(TypedConstraint^ c)
{
	UnmanagedPointer->addConstraintRef(c->UnmanagedPointer);
}

void RigidBody::ApplyCentralForce(Vector3 force)
{
	UnmanagedPointer->applyCentralForce(*Math::Vector3ToBtVec3(force));
}

void RigidBody::ApplyCentralImpulse(Vector3 impulse)
{
	UnmanagedPointer->applyCentralImpulse(*Math::Vector3ToBtVec3(impulse));
}

void RigidBody::ApplyDamping(btScalar timeStep)
{
	UnmanagedPointer->applyDamping(timeStep);
}

void RigidBody::ApplyForce(Vector3 force, Vector3 rel_pos)
{
	UnmanagedPointer->applyForce(*Math::Vector3ToBtVec3(force), *Math::Vector3ToBtVec3(rel_pos));
}

void RigidBody::ApplyGravity()
{
	UnmanagedPointer->applyGravity();
}

void RigidBody::ApplyImpulse(Vector3 impulse, Vector3 rel_pos)
{
	UnmanagedPointer->applyImpulse(*Math::Vector3ToBtVec3(impulse), *Math::Vector3ToBtVec3(rel_pos));
}

void RigidBody::ApplyTorque(Vector3 torque)
{
	UnmanagedPointer->applyTorque(*Math::Vector3ToBtVec3(torque));
}

void RigidBody::ApplyTorqueImpulse(Vector3 torque)
{
	UnmanagedPointer->applyTorqueImpulse(*Math::Vector3ToBtVec3(torque));
}

bool RigidBody::CheckCollideWithOverride(CollisionObject^ collisionObject)
{
	return UnmanagedPointer->checkCollideWithOverride(collisionObject->UnmanagedPointer);
}

void RigidBody::ClearForces()
{
	UnmanagedPointer->clearForces();
}

btScalar RigidBody::ComputeAngularImpulseDenominator(Vector3 axis)
{
	return UnmanagedPointer->computeAngularImpulseDenominator(*Math::Vector3ToBtVec3(axis));
}

btScalar RigidBody::ComputeImpulseDenominator(Vector3 pos, Vector3 normal)
{
	return UnmanagedPointer->computeImpulseDenominator(*Math::Vector3ToBtVec3(pos), *Math::Vector3ToBtVec3(normal));
}

void RigidBody::GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	UnmanagedPointer->getAabb(*tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVec3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVec3ToVector3(tmpAabbMax);

	delete tmpAabbMin;
	delete tmpAabbMax;
}

void RigidBody::SetDamping(btScalar lin_damping, btScalar ang_damping)
{
	UnmanagedPointer->setDamping(lin_damping, ang_damping);
}

void RigidBody::SetMassProps(btScalar mass, Vector3 inertia)
{
	UnmanagedPointer->setMassProps(mass, *Math::Vector3ToBtVec3(inertia));
}

void RigidBody::SetSleepingThresholds(btScalar inertia, btScalar angular)
{
	UnmanagedPointer->setSleepingThresholds(inertia, angular);
}

void RigidBody::Translate(Vector3 v)
{
	UnmanagedPointer->translate(*Math::Vector3ToBtVec3(v));
}

void RigidBody::UpdateDeactivation(btScalar timeStep)
{
	UnmanagedPointer->updateDeactivation(timeStep);
}

void RigidBody::UpdateInertiaTensor()
{
	UnmanagedPointer->updateInertiaTensor();
}

bool RigidBody::WantsSleeping()
{
	return UnmanagedPointer->wantsSleeping();
}


RigidBody^ RigidBody::Upcast(CollisionObject^ colObj)
{
	return gcnew RigidBody(btRigidBody::upcast(colObj->UnmanagedPointer));
}


btScalar RigidBody::AngularDamping::get()
{
	return UnmanagedPointer->getAngularDamping();
}

Vector3 RigidBody::AngularFactor::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getAngularFactor());
}
void RigidBody::AngularFactor::set(Vector3 value)
{
	UnmanagedPointer->setAngularFactor(*Math::Vector3ToBtVec3(value));
}

btScalar RigidBody::AngularSleepingThreshold::get()
{
	return UnmanagedPointer->getAngularSleepingThreshold();
}

Vector3 RigidBody::AngularVelocity::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getAngularVelocity());
}
void RigidBody::AngularVelocity::set(Vector3 value)
{
	UnmanagedPointer->setAngularVelocity(*Math::Vector3ToBtVec3(value));
}

Vector3 RigidBody::CenterOfMassPosition::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getCenterOfMassPosition());
}

Matrix RigidBody::CenterOfMassTransform::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getCenterOfMassTransform());
}
void RigidBody::CenterOfMassTransform::set(Matrix value)
{
	UnmanagedPointer->setCenterOfMassTransform(*Math::MatrixToBtTransform(value));
}

Vector3 RigidBody::Gravity::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getGravity());
}
void RigidBody::Gravity::set(Vector3 value)
{
	btVector3* gravity = Math::Vector3ToBtVec3(value);
	UnmanagedPointer->setGravity(*gravity);
}

Vector3 RigidBody::InvInertiaDiagLocal::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getInvInertiaDiagLocal());
}
void RigidBody::InvInertiaDiagLocal::set(Vector3 value)
{
	btVector3* diagInvInertia = new btVector3(value.X,value.Y,value.Z);
	UnmanagedPointer->setInvInertiaDiagLocal(*diagInvInertia);
	delete diagInvInertia;
}

Vector3 RigidBody::LinearFactor::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getLinearFactor());
}
void RigidBody::LinearFactor::set(Vector3 value)
{
	UnmanagedPointer->setLinearFactor(*Math::Vector3ToBtVec3(value));
}

Vector3 RigidBody::LinearVelocity::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getLinearVelocity());
}
void RigidBody::LinearVelocity::set(Vector3 value)
{
	UnmanagedPointer->setLinearVelocity(*Math::Vector3ToBtVec3(value));
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

btRigidBody* RigidBody::UnmanagedPointer::get()
{
	return (btRigidBody*)CollisionObject::UnmanagedPointer;
}
