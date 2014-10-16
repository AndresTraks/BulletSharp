#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "CollisionObject.h"
#include "MultiBody.h"
#include "MultiBodyLink.h"
#include "MultiBodyLinkCollider.h"

MultiBody::MultiBody(btMultiBody* native)
{
	_native = native;
}

MultiBody::~MultiBody()
{
	this->!MultiBody();
}

MultiBody::!MultiBody()
{
	delete _native;
	_native = NULL;
}

MultiBody::MultiBody(int nLinks, btScalar mass, Vector3 inertia, bool fixedBase, bool canSleep)
{
	VECTOR3_CONV(inertia);
	_native = new btMultiBody(nLinks, mass, VECTOR3_USE(inertia), fixedBase, canSleep);
	VECTOR3_DEL(inertia);
}

void MultiBody::AddBaseForce(Vector3 f)
{
	VECTOR3_CONV(f);
	_native->addBaseForce(VECTOR3_USE(f));
	VECTOR3_DEL(f);
}

void MultiBody::AddBaseTorque(Vector3 t)
{
	VECTOR3_CONV(t);
	_native->addBaseTorque(VECTOR3_USE(t));
	VECTOR3_DEL(t);
}

void MultiBody::AddJointTorque(int i, btScalar Q)
{
	_native->addJointTorque(i, Q);
}

void MultiBody::AddLinkForce(int i, Vector3 f)
{
	VECTOR3_CONV(f);
	_native->addLinkForce(i, VECTOR3_USE(f));
	VECTOR3_DEL(f);
}

void MultiBody::AddLinkTorque(int i, Vector3 t)
{
	VECTOR3_CONV(t);
	_native->addLinkTorque(i, VECTOR3_USE(t));
	VECTOR3_DEL(t);
}

void MultiBody::ApplyDeltaVee(ScalarArray^ deltaVee, btScalar multiplier)
{
	_native->applyDeltaVee((btScalar*)deltaVee->_native, multiplier);
}

void MultiBody::ApplyDeltaVee(ScalarArray^ deltaVee)
{
	_native->applyDeltaVee((btScalar*)deltaVee->_native);
}

void MultiBody::CalcAccelerationDeltas(ScalarArray^ force, ScalarArray^ output, AlignedScalarArray^ scratchR,
	AlignedVector3Array^ scratchV)
{
	_native->calcAccelerationDeltas((btScalar*)force->_native, (btScalar*)output->_native, *(btAlignedObjectArray<btScalar>*)scratchR->_native,
		*(btAlignedObjectArray<btVector3>*)scratchV->_native);
}

void MultiBody::CheckMotionAndSleepIfRequired(btScalar timestep)
{
	_native->checkMotionAndSleepIfRequired(timestep);
}

void MultiBody::ClearForcesAndTorques()
{
	_native->clearForcesAndTorques();
}

void MultiBody::ClearVelocities()
{
	_native->clearVelocities();
}
/*
void MultiBody::FillContactJacobian(int link, Vector3 contactPoint, Vector3 normal,
	ScalarArray^ jac, AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV, AlignedMatrix3x3Array^ scratchM)
{
	VECTOR3_CONV(contactPoint);
	VECTOR3_CONV(normal);
	_native->fillContactJacobian(link, VECTOR3_USE(contactPoint), VECTOR3_USE(normal),
		(btScalar*)jac->_native, *(btAlignedObjectArray<btScalar>*)scratchR->_native, *(btAlignedObjectArray<btVector3>*)scratchV->_native, *(btAlignedObjectArray<btMatrix3x3>*)scratchM->_native);
	VECTOR3_DEL(contactPoint);
	VECTOR3_DEL(normal);
}
*/
btScalar MultiBody::GetJointPos(int i)
{
	return _native->getJointPos(i);
}

btScalar MultiBody::GetJointTorque(int i)
{
	return _native->getJointTorque(i);
}

btScalar MultiBody::GetJointVel(int i)
{
	return _native->getJointVel(i);
}

MultiBodyLink^ MultiBody::GetLink(int index)
{
	if (_links == nullptr) {
		_links = gcnew array<MultiBodyLink^>(_native->getNumLinks());
	}
	if (_links[index] == nullptr) {
		_links[index] = gcnew MultiBodyLink(&_native->getLink(index));
	}
	return _links[index];
}

Vector3 MultiBody::GetLinkForce(int i)
{
	return Math::BtVector3ToVector3(&_native->getLinkForce(i));
}

Vector3 MultiBody::GetLinkInertia(int i)
{
	return Math::BtVector3ToVector3(&_native->getLinkInertia(i));
}

btScalar MultiBody::GetLinkMass(int i)
{
	return _native->getLinkMass(i);
}

Vector3 MultiBody::GetLinkTorque(int i)
{
	return Math::BtVector3ToVector3(&_native->getLinkTorque(i));
}

int MultiBody::GetParent(int linkNum)
{
	return _native->getParent(linkNum);
}

Quaternion MultiBody::GetParentToLocalRot(int i)
{
	return Math::BtQuatToQuaternion(&_native->getParentToLocalRot(i));
}

Vector3 MultiBody::GetRVector(int i)
{
	return Math::BtVector3ToVector3(&_native->getRVector(i));
}

void MultiBody::GoToSleep()
{
	_native->goToSleep();
}

#pragma managed(push, off)
void MultiBody_LocalDirToWorld(btMultiBody* body, int i, btVector3* vec, btVector3* result)
{
	result = &body->localDirToWorld(i, *vec);
}
#pragma managed(pop)
Vector3 MultiBody::LocalDirToWorld(int i, Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* resultTemp = ALIGNED_NEW(btVector3);
	MultiBody_LocalDirToWorld(_native, i, VECTOR3_PTR(vec), resultTemp);
	Vector3 dir = Math::BtVector3ToVector3(resultTemp);
	VECTOR3_DEL(vec);
	ALIGNED_FREE(resultTemp);
	return dir;
}

#pragma managed(push, off)
void MultiBody_LocalPosToWorld(btMultiBody* body, int i, btVector3* vec, btVector3* result)
{
	result = &body->localPosToWorld(i, *vec);
}
#pragma managed(pop)
Vector3 MultiBody::LocalPosToWorld(int i, Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* resultTemp = ALIGNED_NEW(btVector3);
	MultiBody_LocalPosToWorld(_native, i, VECTOR3_PTR(vec), resultTemp);
	Vector3 dir = Math::BtVector3ToVector3(resultTemp);
	VECTOR3_DEL(vec);
	ALIGNED_FREE(resultTemp);
	return dir;
}

void MultiBody::SetCanSleep(bool canSleep)
{
	_native->setCanSleep(canSleep);
}

void MultiBody::SetJointPos(int i, btScalar q)
{
	_native->setJointPos(i, q);
}

void MultiBody::SetJointVel(int i, btScalar qdot)
{
	_native->setJointVel(i, qdot);
}

void MultiBody::SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent,
	Quaternion rotParentToThis, Vector3 jointAxis, Vector3 rVectorWhenQZero, bool disableParentCollision)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(jointAxis);
	VECTOR3_CONV(rVectorWhenQZero);
	_native->setupPrismatic(i, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(jointAxis), VECTOR3_USE(rVectorWhenQZero), disableParentCollision);
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(jointAxis);
	VECTOR3_DEL(rVectorWhenQZero);
}

void MultiBody::SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent,
	Quaternion rotParentToThis, Vector3 jointAxis, Vector3 rVectorWhenQZero)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(jointAxis);
	VECTOR3_CONV(rVectorWhenQZero);
	_native->setupPrismatic(i, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(jointAxis), VECTOR3_USE(rVectorWhenQZero));
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(jointAxis);
	VECTOR3_DEL(rVectorWhenQZero);
}

void MultiBody::SetupRevolute(int i, btScalar mass, Vector3 inertia, int parent, Quaternion zeroRotParentToThis,
	Vector3 jointAxis, Vector3 parentAxisPosition, Vector3 myAxisPosition, bool disableParentCollision)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(zeroRotParentToThis);
	VECTOR3_CONV(jointAxis);
	VECTOR3_CONV(parentAxisPosition);
	VECTOR3_CONV(myAxisPosition);
	_native->setupRevolute(i, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(zeroRotParentToThis),
		VECTOR3_USE(jointAxis), VECTOR3_USE(parentAxisPosition), VECTOR3_USE(myAxisPosition),
		disableParentCollision);
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(zeroRotParentToThis);
	VECTOR3_DEL(jointAxis);
	VECTOR3_DEL(parentAxisPosition);
	VECTOR3_DEL(myAxisPosition);
}

void MultiBody::SetupRevolute(int i, btScalar mass, Vector3 inertia, int parent, Quaternion zeroRotParentToThis,
	Vector3 jointAxis, Vector3 parentAxisPosition, Vector3 myAxisPosition)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(zeroRotParentToThis);
	VECTOR3_CONV(jointAxis);
	VECTOR3_CONV(parentAxisPosition);
	VECTOR3_CONV(myAxisPosition);
	_native->setupRevolute(i, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(zeroRotParentToThis),
		VECTOR3_USE(jointAxis), VECTOR3_USE(parentAxisPosition), VECTOR3_USE(myAxisPosition));
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(zeroRotParentToThis);
	VECTOR3_DEL(jointAxis);
	VECTOR3_DEL(parentAxisPosition);
	VECTOR3_DEL(myAxisPosition);
}

void MultiBody::StepPositions(btScalar dt)
{
	_native->stepPositions(dt);
}
/*
void MultiBody::StepVelocities(btScalar dt, AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV,
	AlignedMatrix3x3Array^ scratchM)
{
	_native->stepVelocities(dt, *scratchR->_native, *scratchV->_native, *scratchM->_native);
}
*/
void MultiBody::WakeUp()
{
	_native->wakeUp();
}

#pragma managed(push, off)
void MultiBody_WorldDirToLocal(btMultiBody* body, int i, btVector3* vec, btVector3* result)
{
	result = &body->worldDirToLocal(i, *vec);
}
#pragma managed(pop)
Vector3 MultiBody::WorldDirToLocal(int i, Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* resultTemp = ALIGNED_NEW(btVector3);
	MultiBody_WorldDirToLocal(_native, i, VECTOR3_PTR(vec), resultTemp);
	Vector3 dir = Math::BtVector3ToVector3(resultTemp);
	VECTOR3_DEL(vec);
	ALIGNED_FREE(resultTemp);
	return dir;
}

#pragma managed(push, off)
void MultiBody_WorldPosToLocal(btMultiBody* body, int i, btVector3* vec, btVector3* result)
{
	result = &body->worldPosToLocal(i, *vec);
}
#pragma managed(pop)
Vector3 MultiBody::WorldPosToLocal(int i, Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* resultTemp = ALIGNED_NEW(btVector3);
	MultiBody_WorldPosToLocal(_native, i, VECTOR3_PTR(vec), resultTemp);
	Vector3 dir = Math::BtVector3ToVector3(resultTemp);
	VECTOR3_DEL(vec);
	ALIGNED_FREE(resultTemp);
	return dir;
}

btScalar MultiBody::AngularDamping::get()
{
	return _native->getAngularDamping();
}

#pragma managed(push, off)
void MultiBody_GetAngularMomentum(btMultiBody* body, btVector3* result)
{
	result = &body->getAngularMomentum();
}
#pragma managed(pop)
Vector3 MultiBody::AngularMomentum::get()
{
	btVector3* valueTemp = ALIGNED_NEW(btVector3);
	MultiBody_GetAngularMomentum(_native, valueTemp);
	Vector3 value = Math::BtVector3ToVector3(valueTemp);
	ALIGNED_FREE(valueTemp);
	return value;
}

MultiBodyLinkCollider^ MultiBody::BaseCollider::get()
{
	return (MultiBodyLinkCollider^)CollisionObject::GetManaged(_native->getBaseCollider());
}
void MultiBody::BaseCollider::set(MultiBodyLinkCollider^ collider)
{
	_native->setBaseCollider((btMultiBodyLinkCollider*)collider->_native);
}

Vector3 MultiBody::BaseForce::get()
{
	return Math::BtVector3ToVector3(&_native->getBaseForce());
}

Vector3 MultiBody::BaseInertia::get()
{
	return Math::BtVector3ToVector3(&_native->getBaseInertia());
}
void MultiBody::BaseInertia::set(Vector3 inertia)
{
	VECTOR3_CONV(inertia);
	_native->setBaseInertia(VECTOR3_USE(inertia));
	VECTOR3_DEL(inertia);
}

btScalar MultiBody::BaseMass::get()
{
	return _native->getBaseMass();
}
void MultiBody::BaseMass::set(btScalar mass)
{
	_native->setBaseMass(mass);
}

#pragma managed(push, off)
void MultiBody_GetBaseOmega(btMultiBody* body, btVector3* result)
{
	result = &body->getBaseOmega();
}
#pragma managed(pop)
Vector3 MultiBody::BaseOmega::get()
{
	btVector3* valueTemp = ALIGNED_NEW(btVector3);
	MultiBody_GetBaseOmega(_native, valueTemp);
	Vector3 value = Math::BtVector3ToVector3(valueTemp);
	ALIGNED_FREE(valueTemp);
	return value;
}
void MultiBody::BaseOmega::set(Vector3 omega)
{
	VECTOR3_CONV(omega);
	_native->setBaseOmega(VECTOR3_USE(omega));
	VECTOR3_DEL(omega);
}

Vector3 MultiBody::BasePosition::get()
{
	return Math::BtVector3ToVector3(&_native->getBasePos());
}
void MultiBody::BasePosition::set(Vector3 pos)
{
	VECTOR3_CONV(pos);
	_native->setBasePos(VECTOR3_USE(pos));
	VECTOR3_DEL(pos);
}

Vector3 MultiBody::BaseTorque::get()
{
	return Math::BtVector3ToVector3(&_native->getBaseTorque());
}

#pragma managed(push, off)
void MultiBody_GetBaseVel(btMultiBody* body, btVector3* result)
{
	result = (btVector3*)&body->getBaseVel();
}
#pragma managed(pop)
Vector3 MultiBody::BaseVelocity::get()
{
	btVector3* valueTemp = ALIGNED_NEW(btVector3);
	MultiBody_GetBaseVel(_native, valueTemp);
	Vector3 value = Math::BtVector3ToVector3(valueTemp);
	ALIGNED_FREE(valueTemp);
	return value;
}
void MultiBody::BaseVelocity::set(Vector3 vel)
{
	VECTOR3_CONV(vel);
	_native->setBaseVel(VECTOR3_USE(vel));
	VECTOR3_DEL(vel);
}

int MultiBody::CompanionId::get()
{
	return _native->getCompanionId();
}
void MultiBody::CompanionId::set(int id)
{
	_native->setCompanionId(id);
}

bool MultiBody::HasFixedBase::get()
{
	return _native->hasFixedBase();
}

bool MultiBody::HasSelfCollision::get()
{
	return _native->hasSelfCollision();
}
void MultiBody::HasSelfCollision::set(bool hasSelfCollision)
{
	_native->setHasSelfCollision(hasSelfCollision);
}

bool MultiBody::IsAwake::get()
{
	return _native->isAwake();
}

btScalar MultiBody::KineticEnergy::get()
{
	return _native->getKineticEnergy();
}

btScalar MultiBody::LinearDamping::get()
{
	return _native->getLinearDamping();
}
void MultiBody::LinearDamping::set(btScalar damp)
{
	_native->setLinearDamping(damp);
}

btScalar MultiBody::MaxAppliedImpulse::get()
{
	return _native->getMaxAppliedImpulse();
}
void MultiBody::MaxAppliedImpulse::set(btScalar maxImp)
{
	_native->setMaxAppliedImpulse(maxImp);
}

int MultiBody::NumLinks::get()
{
	return _native->getNumLinks();
}
void MultiBody::NumLinks::set(int numLinks)
{
	_native->setNumLinks(numLinks);
	if (_links != nullptr)
	{
		Array::Resize(_links, numLinks);
	}
}

bool MultiBody::UseGyroTerm::get()
{
	return _native->getUseGyroTerm();
}
void MultiBody::UseGyroTerm::set(bool useGyro)
{
	_native->setUseGyroTerm(useGyro);
}

ScalarArray^ MultiBody::VelocityVector::get()
{
	return gcnew ScalarArray(_native->getVelocityVector(), 6 + _native->getNumLinks());
}

Quaternion MultiBody::WorldToBaseRot::get()
{
	return Math::BtQuatToQuaternion(&_native->getWorldToBaseRot());
}
void MultiBody::WorldToBaseRot::set(Quaternion rot)
{
	QUATERNION_CONV(rot);
	_native->setWorldToBaseRot(QUATERNION_USE(rot));
	QUATERNION_DEL(rot);
}

#endif
