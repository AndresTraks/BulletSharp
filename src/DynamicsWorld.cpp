#include "StdAfx.h"

#include "AlignedObjectArray.h"
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
	_constraints = gcnew System::Collections::Generic::List<TypedConstraint^>();
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
	_constraints->Add(constraint);
	Native->addConstraint(constraint->_native, disableCollisionsBetweenLinkedBodies);
}

void DynamicsWorld::AddConstraint(TypedConstraint^ constraint)
{
	_constraints->Add(constraint);
	Native->addConstraint(constraint->_native);
}
#endif

void DynamicsWorld::AddRigidBody(RigidBody^ body)
{
	_collisionObjectArray->Add(body);
}

void DynamicsWorld::AddRigidBody(RigidBody^ body, CollisionFilterGroups group, CollisionFilterGroups mask)
{
	_collisionObjectArray->Add(body, (short)group, (short)mask);
}

void DynamicsWorld::AddRigidBody(RigidBody^ body, short group, short mask)
{
	_collisionObjectArray->Add(body, group, mask);
}

void DynamicsWorld::ClearForces()
{
	Native->clearForces();
}
#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ DynamicsWorld::GetConstraint(int index)
{
	//TODO: Enable this once deserialization of constraints is handled.
	//System::Diagnostics::Debug::Assert(((btDynamicsWorld*)_native)->getConstraint(index) == _constraints[index]->_native);
    //return _constraints[index];
	return TypedConstraint::GetManaged(Native->getConstraint(index));
}
#endif

void DynamicsWorld::InternalTickCallbackUnmanaged(IntPtr world, btScalar timeStep)
{
    _callback(this, timeStep);
}

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
	//int itemIndex = _constraints->IndexOf(constraint);
    //int lastIndex = _constraints->Count - 1;
    //_constraints[itemIndex] = _constraints[lastIndex];
    //_constraints->RemoveAt(lastIndex);
	Native->removeConstraint(constraint->_native);
	_constraints->Remove(constraint);
}
#endif
void DynamicsWorld::RemoveRigidBody(RigidBody^ body)
{
	_collisionObjectArray->Remove(body);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo,
	bool isPreTick)
{
	if (_callback != cb)
	{
		_callback = cb;
		if (cb != nullptr)
		{
			if (_callbackUnmanaged == nullptr)
			{
				_callbackUnmanaged = gcnew InternalTickCallbackUnmanagedDelegate(this, &DynamicsWorld::InternalTickCallbackUnmanaged);
			}
			Native->setInternalTickCallback((btInternalTickCallback)Marshal::GetFunctionPointerForDelegate(_callbackUnmanaged).ToPointer(), 0, isPreTick);
		}
		else
		{
			_callbackUnmanaged = nullptr;
			Native->setInternalTickCallback(0, 0, isPreTick);
		}
	}
	_userObject = worldUserInfo;
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
	VECTOR3_CONV(gravity);
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
	return gcnew ContactSolverInfo(&Native->getSolverInfo(), true);
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
