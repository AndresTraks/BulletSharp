#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "StringConv.h"
#include "AlignedObjectArray.h"
#include "Collections.h"
#include "MultiBody.h"
#include "MultiBodyLink.h"
#include "MultiBodyLinkCollider.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

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

void MultiBody::AddBaseConstraintForce(Vector3 f)
{
	VECTOR3_CONV(f);
	_native->addBaseConstraintForce(VECTOR3_USE(f));
	VECTOR3_DEL(f);
}

void MultiBody::AddBaseConstraintTorque(Vector3 t)
{
	VECTOR3_CONV(t);
	_native->addBaseConstraintTorque(VECTOR3_USE(t));
	VECTOR3_DEL(t);
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

void MultiBody::AddJointTorque(int i, btScalar q)
{
	_native->addJointTorque(i, q);
}

void MultiBody::AddJointTorqueMultiDof(int i, array<btScalar>^ q)
{
	pin_ptr<btScalar> qPtr = &q[0];
	_native->addJointTorqueMultiDof(i, qPtr);
}

void MultiBody::AddJointTorqueMultiDof(int i, int dof, btScalar q)
{
	_native->addJointTorqueMultiDof(i, dof, q);
}

void MultiBody::AddLinkConstraintForce(int i, Vector3 f)
{
	VECTOR3_CONV(f);
	_native->addLinkConstraintForce(i, VECTOR3_USE(f));
	VECTOR3_DEL(f);
}

void MultiBody::AddLinkConstraintTorque(int i, Vector3 t)
{
	VECTOR3_CONV(t);
	_native->addLinkConstraintTorque(i, VECTOR3_USE(t));
	VECTOR3_DEL(t);
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

void MultiBody::ApplyDeltaVeeMultiDof(array<btScalar>^ deltaVee, btScalar multiplier)
{
	pin_ptr<btScalar> deltaVeePtr = &deltaVee[0];
	_native->applyDeltaVeeMultiDof(deltaVeePtr, multiplier);
}

void MultiBody::ApplyDeltaVeeMultiDof2(array<btScalar>^ deltaVee, btScalar multiplier)
{
	pin_ptr<btScalar> deltaVeePtr = &deltaVee[0];
	_native->applyDeltaVeeMultiDof2(deltaVeePtr, multiplier);
}

void MultiBody::CalcAccelerationDeltasMultiDof(array<btScalar>^ force, array<btScalar>^ output,
	AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV)
{
	pin_ptr<btScalar> forcePtr = &force[0];
	pin_ptr<btScalar> outputPtr = &output[0];
	_native->calcAccelerationDeltasMultiDof(forcePtr, outputPtr, *(btAlignedObjectArray<btScalar>*)scratchR->_native,
		*(btAlignedObjectArray<btVector3>*)scratchV->_native);
}

int MultiBody::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}

void MultiBody::CheckMotionAndSleepIfRequired(btScalar timestep)
{
	_native->checkMotionAndSleepIfRequired(timestep);
}

void MultiBody::ClearConstraintForces()
{
	_native->clearConstraintForces();
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
void MultiBody::ComputeAccelerationsArticulatedBodyAlgorithmMultiDof(btScalar deltaTime,
	AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV, AlignedMatrix3x3Array^ scratchM,
	bool isConstraintPass)
{
	_native->computeAccelerationsArticulatedBodyAlgorithmMultiDof(deltaTime, **(btAlignedObjectArray<btScalar>*)scratchR->_native,
		*(btAlignedObjectArray<btVector3>*)scratchV->_native, *(btAlignedObjectArray<btMatrix3x3>*)scratchM->_native, isConstraintPass);
}

void MultiBody::ComputeAccelerationsArticulatedBodyAlgorithmMultiDof(btScalar deltaTime,
	AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV, AlignedMatrix3x3Array^ scratchM)
{
	_native->computeAccelerationsArticulatedBodyAlgorithmMultiDof(deltaTime, **(btAlignedObjectArray<btScalar>*)scratchR->_native,
		*(btAlignedObjectArray<btVector3>*)scratchV->_native, *(btAlignedObjectArray<btMatrix3x3>*)scratchM->_native);
}

void MultiBody::FillConstraintJacobianMultiDof(int link, Vector3 contactPoint, Vector3 normalAng,
	Vector3 normalLin, array<btScalar>^ jac, AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV,
	AlignedMatrix3x3Array^ scratchM)
{
	VECTOR3_CONV(contactPoint);
	VECTOR3_CONV(normalAng);
	VECTOR3_CONV(normalLin);
	pin_ptr<btScalar> jacPtr = &jac[0];
	_native->fillConstraintJacobianMultiDof(link, VECTOR3_USE(contactPoint), VECTOR3_USE(normalAng),
		VECTOR3_USE(normalLin), jacPtr, *(btAlignedObjectArray<btScalar>*)scratchR->_native, *(btAlignedObjectArray<btVector3>*)scratchV->_native,
		*(btAlignedObjectArray<btMatrix3x3>*)scratchM->_native);
	VECTOR3_DEL(contactPoint);
	VECTOR3_DEL(normalAng);
	VECTOR3_DEL(normalLin);
}

void MultiBody::FillContactJacobianMultiDof(int link, Vector3 contactPoint, Vector3 normal,
	array<btScalar>^ jac, AlignedScalarArray^ scratchR, AlignedVector3Array^ scratchV,
	AlignedMatrix3x3Array^ scratchM)
{
	VECTOR3_CONV(contactPoint);
	VECTOR3_CONV(normal);
	pin_ptr<btScalar> jacPtr = &jac[0];
	_native->fillContactJacobianMultiDof(link, VECTOR3_USE(contactPoint), VECTOR3_USE(normal),
		jacPtr, *(btAlignedObjectArray<btScalar>*)scratchR->_native, *(btAlignedObjectArray<btVector3>*)scratchV->_native, *(btAlignedObjectArray<btMatrix3x3>*)scratchM->_native);
	VECTOR3_DEL(contactPoint);
	VECTOR3_DEL(normal);
}
*/
void MultiBody::FinalizeMultiDof()
{
	_native->finalizeMultiDof();
}
/*
void MultiBody::ForwardKinematics(AlignedQuaternionArray^ scratchQ, AlignedVector3Array^ scratchM)
{
	_native->forwardKinematics(*(btAlignedObjectArray<btQuaternion>*)scratchQ->_native, *(btAlignedObjectArray<btVector3>*)scratchM->_native);
}
*/
btScalar MultiBody::GetJointPos(int i)
{
	return _native->getJointPos(i);
}
/*
array<btScalar>^ MultiBody::GetJointPosMultiDof(int i)
{
	return _native->getJointPosMultiDof(i);
}
*/
btScalar MultiBody::GetJointTorque(int i)
{
	return _native->getJointTorque(i);
}
/*
array<btScalar>^ MultiBody::GetJointTorqueMultiDof(int i)
{
	return _native->getJointTorqueMultiDof(i);
}
*/
btScalar MultiBody::GetJointVel(int i)
{
	return _native->getJointVel(i);
}
/*
array<btScalar>^ MultiBody::GetJointVelMultiDof(int i)
{
	return _native->getJointVelMultiDof(i);
}
*/
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

bool MultiBody::InternalNeedsJointFeedback()
{
	return _native->internalNeedsJointFeedback();
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

void MultiBody::ProcessDeltaVeeMultiDof2()
{
	_native->processDeltaVeeMultiDof2();
}

#ifndef DISABLE_SERIALIZE
String^ MultiBody::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	return gcnew String(_native->serialize(dataBuffer.ToPointer(), serializer->_native));
}
#endif

void MultiBody::SetJointPos(int i, btScalar q)
{
	_native->setJointPos(i, q);
}

void MultiBody::SetJointPosMultiDof(int i, array<btScalar>^ q)
{
	pin_ptr<btScalar> qPtr = &q[0];
	_native->setJointPosMultiDof(i, qPtr);
}

void MultiBody::SetJointVel(int i, btScalar qdot)
{
	_native->setJointVel(i, qdot);
}

void MultiBody::SetJointVelMultiDof(int i, array<btScalar>^ qdot)
{
	pin_ptr<btScalar> qdotPtr = &qdot[0];
	_native->setJointVelMultiDof(i, qdotPtr);
}

void MultiBody::SetPosUpdated(bool updated)
{
	_native->setPosUpdated(updated);
}

void MultiBody::SetupFixed(int linkIndex, btScalar mass, Vector3 inertia, int parent,
	Quaternion rotParentToThis, Vector3 parentComToThisPivotOffset, Vector3 thisPivotToThisComOffset)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(parentComToThisPivotOffset);
	VECTOR3_CONV(thisPivotToThisComOffset);
	_native->setupFixed(linkIndex, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(parentComToThisPivotOffset), VECTOR3_USE(thisPivotToThisComOffset));
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(parentComToThisPivotOffset);
	VECTOR3_DEL(thisPivotToThisComOffset);
}

void MultiBody::SetupPlanar(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis,
	Vector3 rotationAxis, Vector3 parentComToThisComOffset, bool disableParentCollision)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(rotationAxis);
	VECTOR3_CONV(parentComToThisComOffset);
	_native->setupPlanar(i, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(rotationAxis), VECTOR3_USE(parentComToThisComOffset), disableParentCollision);
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(rotationAxis);
	VECTOR3_DEL(parentComToThisComOffset);
}

void MultiBody::SetupPlanar(int i, btScalar mass, Vector3 inertia, int parent, Quaternion rotParentToThis,
	Vector3 rotationAxis, Vector3 parentComToThisComOffset)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(rotationAxis);
	VECTOR3_CONV(parentComToThisComOffset);
	_native->setupPlanar(i, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(rotationAxis), VECTOR3_USE(parentComToThisComOffset));
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(rotationAxis);
	VECTOR3_DEL(parentComToThisComOffset);
}

void MultiBody::SetupPrismatic(int i, btScalar mass, Vector3 inertia, int parent,
	Quaternion rotParentToThis, Vector3 jointAxis, Vector3 parentComToThisPivotOffset,
	Vector3 thisPivotToThisComOffset, bool disableParentCollision)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(jointAxis);
	VECTOR3_CONV(parentComToThisPivotOffset);
	VECTOR3_CONV(thisPivotToThisComOffset);
	_native->setupPrismatic(i, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(jointAxis), VECTOR3_USE(parentComToThisPivotOffset), VECTOR3_USE(thisPivotToThisComOffset),
		disableParentCollision);
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(jointAxis);
	VECTOR3_DEL(parentComToThisPivotOffset);
	VECTOR3_DEL(thisPivotToThisComOffset);
}

void MultiBody::SetupRevolute(int linkIndex, btScalar mass, Vector3 inertia, int parentIndex,
	Quaternion rotParentToThis, Vector3 jointAxis, Vector3 parentComToThisPivotOffset,
	Vector3 thisPivotToThisComOffset, bool disableParentCollision)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(jointAxis);
	VECTOR3_CONV(parentComToThisPivotOffset);
	VECTOR3_CONV(thisPivotToThisComOffset);
	_native->setupRevolute(linkIndex, mass, VECTOR3_USE(inertia), parentIndex, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(jointAxis), VECTOR3_USE(parentComToThisPivotOffset), VECTOR3_USE(thisPivotToThisComOffset),
		disableParentCollision);
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(jointAxis);
	VECTOR3_DEL(parentComToThisPivotOffset);
	VECTOR3_DEL(thisPivotToThisComOffset);
}

void MultiBody::SetupRevolute(int linkIndex, btScalar mass, Vector3 inertia, int parentIndex,
	Quaternion rotParentToThis, Vector3 jointAxis, Vector3 parentComToThisPivotOffset,
	Vector3 thisPivotToThisComOffset)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(jointAxis);
	VECTOR3_CONV(parentComToThisPivotOffset);
	VECTOR3_CONV(thisPivotToThisComOffset);
	_native->setupRevolute(linkIndex, mass, VECTOR3_USE(inertia), parentIndex, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(jointAxis), VECTOR3_USE(parentComToThisPivotOffset), VECTOR3_USE(thisPivotToThisComOffset));
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(jointAxis);
	VECTOR3_DEL(parentComToThisPivotOffset);
	VECTOR3_DEL(thisPivotToThisComOffset);
}

void MultiBody::SetupSpherical(int linkIndex, btScalar mass, Vector3 inertia, int parent,
	Quaternion rotParentToThis, Vector3 parentComToThisPivotOffset, Vector3 thisPivotToThisComOffset,
	bool disableParentCollision)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(parentComToThisPivotOffset);
	VECTOR3_CONV(thisPivotToThisComOffset);
	_native->setupSpherical(linkIndex, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(parentComToThisPivotOffset), VECTOR3_USE(thisPivotToThisComOffset),
		disableParentCollision);
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(parentComToThisPivotOffset);
	VECTOR3_DEL(thisPivotToThisComOffset);
}

void MultiBody::SetupSpherical(int linkIndex, btScalar mass, Vector3 inertia, int parent,
	Quaternion rotParentToThis, Vector3 parentComToThisPivotOffset, Vector3 thisPivotToThisComOffset)
{
	VECTOR3_CONV(inertia);
	QUATERNION_CONV(rotParentToThis);
	VECTOR3_CONV(parentComToThisPivotOffset);
	VECTOR3_CONV(thisPivotToThisComOffset);
	_native->setupSpherical(linkIndex, mass, VECTOR3_USE(inertia), parent, QUATERNION_USE(rotParentToThis),
		VECTOR3_USE(parentComToThisPivotOffset), VECTOR3_USE(thisPivotToThisComOffset));
	VECTOR3_DEL(inertia);
	QUATERNION_DEL(rotParentToThis);
	VECTOR3_DEL(parentComToThisPivotOffset);
	VECTOR3_DEL(thisPivotToThisComOffset);
}

void MultiBody::StepPositionsMultiDof(btScalar deltaTime, array<btScalar>^ pq, array<btScalar>^ pqd)
{
	pin_ptr<btScalar> pqPtr = &pq[0];
	pin_ptr<btScalar> pqdPtr = &pqd[0];
	_native->stepPositionsMultiDof(deltaTime, pqPtr, pqdPtr);
}

void MultiBody::StepPositionsMultiDof(btScalar deltaTime, array<btScalar>^ pq)
{
	pin_ptr<btScalar> pqPtr = &pq[0];
	_native->stepPositionsMultiDof(deltaTime, pqPtr);
}

void MultiBody::StepPositionsMultiDof(btScalar deltaTime)
{
	_native->stepPositionsMultiDof(deltaTime);
}
/*
void MultiBody::UpdateCollisionObjectWorldTransforms(AlignedQuaternionArray^ scratchQ,
	AlignedVector3Array^ scratchM)
{
	_native->updateCollisionObjectWorldTransforms(*(btAlignedObjectArray<btQuaternion>*)scratchQ->_native, *(btAlignedObjectArray<btVector3>*)scratchM->_native);
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
void MultiBody::AngularDamping::set(btScalar damp)
{
	_native->setAngularDamping(damp);
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

String^ MultiBody::BaseName::get()
{
	return StringConv::UnmanagedToManaged(_native->getBaseName());
}
/*
void MultiBody::BaseName::set(String^ name)
{
	_native->setBaseName(name->_native);
}
*/
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
/*
Matrix MultiBody::BaseWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->getBaseWorldTransform());
}
void MultiBody::BaseWorldTransform::set(Matrix tr)
{
	TRANSFORM_CONV(tr);
	_native->setBaseWorldTransform(TRANSFORM_USE(tr));
	TRANSFORM_DEL(tr);
}
*/
bool MultiBody::CanSleep::get()
{
	return _native->getCanSleep();
}
void MultiBody::CanSleep::set(bool canSleep)
{
	_native->setCanSleep(canSleep);
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

bool MultiBody::IsPosUpdated::get()
{
	return _native->isPosUpdated();
}

bool MultiBody::IsUsingGlobalVelocities::get()
{
	return _native->isUsingGlobalVelocities();
}
void MultiBody::IsUsingGlobalVelocities::set(bool use)
{
	_native->useGlobalVelocities(use);
}

bool MultiBody::IsUsingRK4Integration::get()
{
	return _native->isUsingRK4Integration();
}
void MultiBody::IsUsingRK4Integration::set(bool use)
{
	_native->useRK4Integration(use);
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

btScalar MultiBody::MaxCoordinateVelocity::get()
{
	return _native->getMaxCoordinateVelocity();
}
void MultiBody::MaxCoordinateVelocity::set(btScalar maxVel)
{
	_native->setMaxCoordinateVelocity(maxVel);
}

int MultiBody::NumDofs::get()
{
	return _native->getNumDofs();
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

int MultiBody::NumPosVars::get()
{
	return _native->getNumPosVars();
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
