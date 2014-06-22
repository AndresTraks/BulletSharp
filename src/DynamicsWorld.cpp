#include "StdAfx.h"

#include "IActionInterface.h"
#include "ConstraintSOlver.h"
#include "ContactSolverInfo.h"
#include "DynamicsWorld.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif
#ifndef DISABLE_VEHICLE
#include "RaycastVehicle.h"
#endif
#ifndef DISABLE_UNCOMMON
#include "CharacterControllerInterface.h"
#endif

#define Native static_cast<btDynamicsWorld*>(_native)

DynamicsWorld::DynamicsWorld(btDynamicsWorld* native)
	: CollisionWorld(native)
{
}

void DynamicsWorld::AddAction(IActionInterface^ action)
{
	if (!_actions) {
		_actions = gcnew System::Collections::Generic::List<IActionInterface^>();
	}
	_actions->Add(action);
#ifndef DISABLE_VEHICLE
	RaycastVehicle^ vehicle = dynamic_cast<RaycastVehicle^>(action);
	if (vehicle) {
		Native->addAction(vehicle->_native);
		return;
	}
#endif
#ifndef DISABLE_UNCOMMON
	CharacterControllerInterface^ character = dynamic_cast<CharacterControllerInterface^>(action);
	if (character) {
		Native->addAction(character->_native);
		return;
	}
#endif
	ActionInterfaceWrapper* wrapper = new ActionInterfaceWrapper(action, this);
	ObjectTable::Add(action, wrapper);
	Native->addAction(wrapper);
	return;
}

#ifndef DISABLE_CONSTRAINTS
void DynamicsWorld::AddConstraint(TypedConstraint^ constraint, bool disableCollisionsBetweenLinkedBodies)
{
	Native->addConstraint(constraint->_native, disableCollisionsBetweenLinkedBodies);
}

void DynamicsWorld::AddConstraint(TypedConstraint^ constraint)
{
	Native->addConstraint(constraint->_native);
}
#endif

void DynamicsWorld::AddRigidBody(RigidBody^ body)
{
	Native->addRigidBody((btRigidBody*)body->_native);
}

void DynamicsWorld::AddRigidBody(RigidBody^ body, CollisionFilterGroups group, CollisionFilterGroups mask)
{
	Native->addRigidBody((btRigidBody*)body->_native, (short)group, (short)mask);
}

void DynamicsWorld::ClearForces()
{
	Native->clearForces();
}
#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ DynamicsWorld::GetConstraint(int index)
{
	return TypedConstraint::GetManaged(Native->getConstraint(index));
}
#endif
void DynamicsWorld::RemoveAction(IActionInterface^ action)
{
	if (!_actions) {
		// No shapes have been added
		return;
	}

	_actions->Remove(action);

#ifndef DISABLE_VEHICLE
	RaycastVehicle^ vehicle = dynamic_cast<RaycastVehicle^>(action);
	if (vehicle) {
		Native->removeAction(vehicle->_native);
		return;
	}
#endif
#ifndef DISABLE_UNCOMMON
	CharacterControllerInterface^ character = dynamic_cast<CharacterControllerInterface^>(action);
	if (character) {
		Native->removeAction(character->_native);
		return;
	}
#endif
	ActionInterfaceWrapper* wrapper = (ActionInterfaceWrapper*)ObjectTable::GetUnmanagedObject(action);
	Native->removeAction(wrapper);
	ObjectTable::Remove(wrapper);
	delete wrapper;
}
#ifndef DISABLE_CONSTRAINTS
void DynamicsWorld::RemoveConstraint(TypedConstraint^ constraint)
{
	Native->removeConstraint(constraint->_native);
}
#endif
void DynamicsWorld::RemoveRigidBody(RigidBody^ body)
{
	Native->removeRigidBody((btRigidBody*)body->_native);
}

void callback(btDynamicsWorld* world, btScalar timeStep)
{
	void* userInfo = world->getWorldUserInfo();
	DynamicsWorld^ dynamicsWorld = static_cast<DynamicsWorld^>(VoidPtrToGCHandle(userInfo).Target);
	dynamicsWorld->_callback(dynamicsWorld, timeStep);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo,
	bool isPreTick)
{
	_callback = cb;
	_userObject = worldUserInfo;

	void* nativeUserInfo = Native->getWorldUserInfo();
	if (cb != nullptr) {
		if (!nativeUserInfo) {
			GCHandle handle = GCHandle::Alloc(this, GCHandleType::Weak);
			nativeUserInfo = GCHandleToVoidPtr(handle);
		}
		Native->setInternalTickCallback(callback, nativeUserInfo, isPreTick);
	} else {
		if (nativeUserInfo) {
			VoidPtrToGCHandle(nativeUserInfo).Free();
		}
		Native->setInternalTickCallback(0, 0, isPreTick);
	}
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo)
{
	SetInternalTickCallback(cb, worldUserInfo, false);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb)
{
	SetInternalTickCallback(cb, _userObject, false);
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps, btScalar fixedTimeStep)
{
	return Native->stepSimulation(timeStep, maxSubSteps, fixedTimeStep);
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps)
{
	return Native->stepSimulation(timeStep, maxSubSteps);
}

int DynamicsWorld::StepSimulation(btScalar timeStep)
{
	return Native->stepSimulation(timeStep);
}

void DynamicsWorld::SynchronizeMotionStates()
{
	Native->synchronizeMotionStates();
}

#ifndef DISABLE_CONSTRAINTS
ConstraintSolver^ DynamicsWorld::ConstraintSolver::get()
{
	if (_constraintSolver == nullptr) {
		_constraintSolver = BulletSharp::ConstraintSolver::GetManaged(Native->getConstraintSolver());
	}
	return _constraintSolver;
}
void DynamicsWorld::ConstraintSolver::set(BulletSharp::ConstraintSolver^ solver)
{
	_constraintSolver = solver;
	Native->setConstraintSolver(solver->_native);
}
#endif

#pragma managed(push, off)
void World_GetGravity(btDynamicsWorld* world, btVector3* gravity)
{
	*gravity = world->getGravity();
}
#pragma managed(pop)

Vector3 DynamicsWorld::Gravity::get()
{
	btVector3* gravityTemp = ALIGNED_NEW(btVector3);
	World_GetGravity(Native, gravityTemp);
	Vector3 gravity = Math::BtVector3ToVector3(gravityTemp);
	ALIGNED_FREE(gravityTemp);
	return gravity;
}
void DynamicsWorld::Gravity::set(Vector3 gravity)
{
	VECTOR3_DEF(gravity);
	Native->setGravity(VECTOR3_USE(gravity));
	VECTOR3_DEL(gravity);
}
#ifndef DISABLE_CONSTRAINTS
int DynamicsWorld::NumConstraints::get()
{
	return Native->getNumConstraints();
}
#endif
ContactSolverInfo^ DynamicsWorld::SolverInfo::get()
{
	return gcnew ContactSolverInfo(&Native->getSolverInfo());
}

DynamicsWorldType DynamicsWorld::WorldType::get()
{
	return (DynamicsWorldType) Native->getWorldType();
}

Object^ DynamicsWorld::WorldUserInfo::get()
{
	return _userObject;
}
void DynamicsWorld::WorldUserInfo::set(Object^ worldUserInfo)
{
	_userObject = worldUserInfo;
}
