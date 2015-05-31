#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Collections.h"
#include "RigidBody.h"
#include "TypedConstraint.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

JointFeedback::~JointFeedback()
{
	this->!JointFeedback();
}

JointFeedback::!JointFeedback()
{
	delete _native;
	_native = NULL;
}

JointFeedback::JointFeedback()
{
	_native = new btJointFeedback();
}

Vector3 JointFeedback::AppliedForceBodyA::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedForceBodyA);
}
void JointFeedback::AppliedForceBodyA::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedForceBodyA);
}

Vector3 JointFeedback::AppliedForceBodyB::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedForceBodyB);
}
void JointFeedback::AppliedForceBodyB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedForceBodyB);
}

Vector3 JointFeedback::AppliedTorqueBodyA::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedTorqueBodyA);
}
void JointFeedback::AppliedTorqueBodyA::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedTorqueBodyA);
}

Vector3 JointFeedback::AppliedTorqueBodyB::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedTorqueBodyB);
}
void JointFeedback::AppliedTorqueBodyB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedTorqueBodyB);
}


TypedConstraint::ConstraintInfo1::~ConstraintInfo1()
{
	this->!ConstraintInfo1();
}

TypedConstraint::ConstraintInfo1::!ConstraintInfo1()
{
	delete _native;
	_native = NULL;
}

TypedConstraint::ConstraintInfo1::ConstraintInfo1()
{
	_native = new btTypedConstraint::btConstraintInfo1();
}

int TypedConstraint::ConstraintInfo1::Nub::get()
{
	return _native->nub;
}
void TypedConstraint::ConstraintInfo1::Nub::set(int value)
{
	_native->nub = value;
}

int TypedConstraint::ConstraintInfo1::NumConstraintRows::get()
{
	return _native->m_numConstraintRows;
}
void TypedConstraint::ConstraintInfo1::NumConstraintRows::set(int value)
{
	_native->m_numConstraintRows = value;
}


TypedConstraint::ConstraintInfo2::~ConstraintInfo2()
{
	this->!ConstraintInfo2();
}

TypedConstraint::ConstraintInfo2::!ConstraintInfo2()
{
	delete _native;
	_native = NULL;
}

TypedConstraint::ConstraintInfo2::ConstraintInfo2()
{
	_native = new btTypedConstraint::btConstraintInfo2();
}

ScalarArray^ TypedConstraint::ConstraintInfo2::Cfm::get()
{
	if (_cfm == nullptr)
	{
		_cfm = gcnew ScalarArray(_native->cfm, 3);
	}
	return _cfm;
}

ScalarArray^ TypedConstraint::ConstraintInfo2::ConstraintError::get()
{
	if (_constraintError == nullptr)
	{
		_constraintError = gcnew ScalarArray(_native->m_constraintError, 3);
	}
	return _constraintError;
}

btScalar TypedConstraint::ConstraintInfo2::Damping::get()
{
	return _native->m_damping;
}
void TypedConstraint::ConstraintInfo2::Damping::set(btScalar value)
{
	_native->m_damping = value;
}

btScalar TypedConstraint::ConstraintInfo2::Erp::get()
{
	return _native->erp;
}
void TypedConstraint::ConstraintInfo2::Erp::set(btScalar value)
{
	_native->erp = value;
}
/*
int^ TypedConstraint::ConstraintInfo2::Findex::get()
{
	return _native->findex;
}
void TypedConstraint::ConstraintInfo2::Findex::set(int^ value)
{
	_native->findex = value->_native;
}
*/
btScalar TypedConstraint::ConstraintInfo2::Fps::get()
{
	return _native->fps;
}
void TypedConstraint::ConstraintInfo2::Fps::set(btScalar value)
{
	_native->fps = value;
}

ScalarArray^ TypedConstraint::ConstraintInfo2::J1angularAxis::get()
{
	if (_j1angularAxis == nullptr)
	{
		_j1angularAxis = gcnew ScalarArray(_native->m_J1angularAxis, 3);
	}
	return _j1angularAxis;
}

ScalarArray^ TypedConstraint::ConstraintInfo2::J1linearAxis::get()
{
	if (_j1linearAxis == nullptr)
	{
		_j1linearAxis = gcnew ScalarArray(_native->m_J1linearAxis, 3);
	}
	return _j1linearAxis;
}

ScalarArray^ TypedConstraint::ConstraintInfo2::J2angularAxis::get()
{
	if (_j2angularAxis == nullptr)
	{
		_j2angularAxis = gcnew ScalarArray(_native->m_J2angularAxis, 3);
	}
	return _j2angularAxis;
}

ScalarArray^ TypedConstraint::ConstraintInfo2::J2linearAxis::get()
{
	if (_j2linearAxis == nullptr)
	{
		_j2linearAxis = gcnew ScalarArray(_native->m_J2angularAxis, 3);
	}
	return _j2linearAxis;
}

ScalarArray^ TypedConstraint::ConstraintInfo2::LowerLimit::get()
{
	if (_lowerLimit == nullptr)
	{
		_lowerLimit = gcnew ScalarArray(_native->m_lowerLimit, 3);
	}
	return _lowerLimit;
}

int TypedConstraint::ConstraintInfo2::NumIterations::get()
{
	return _native->m_numIterations;
}
void TypedConstraint::ConstraintInfo2::NumIterations::set(int value)
{
	_native->m_numIterations = value;
}

int TypedConstraint::ConstraintInfo2::Rowskip::get()
{
	return _native->rowskip;
}
void TypedConstraint::ConstraintInfo2::Rowskip::set(int value)
{
	_native->rowskip = value;
}

ScalarArray^ TypedConstraint::ConstraintInfo2::UpperLimit::get()
{
	if (_upperLimit == nullptr)
	{
		_upperLimit = gcnew ScalarArray(_native->m_upperLimit, 3);
	}
	return _upperLimit;
}


TypedConstraint::TypedConstraint(btTypedConstraint* native)
{
	if (native)
		UnmanagedPointer = native;
}

TypedConstraint^ TypedConstraint::GetManaged(btTypedConstraint* typedConstraint)
{
	if (typedConstraint == 0)
		return nullptr;

	if (typedConstraint->getUserConstraintId() != -1)
		return static_cast<TypedConstraint^>(VoidPtrToGCHandle(typedConstraint->getUserConstraintPtr()).Target);

	throw gcnew NotImplementedException();
}

TypedConstraint::~TypedConstraint()
{
	this->!TypedConstraint();
}

TypedConstraint::!TypedConstraint()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);

	if (_native->getUserConstraintId() != -1)
	{
		VoidPtrToGCHandle(_native->getUserConstraintPtr()).Free();
	}

	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
	
	OnDisposed(this, nullptr);
}

void TypedConstraint::BuildJacobian()
{
	_native->buildJacobian();
}

#ifndef DISABLE_SERIALIZE
int TypedConstraint::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}
#endif

void TypedConstraint::EnableFeedback(bool needsFeedback)
{
	_native->enableFeedback(needsFeedback);
}

RigidBody^ TypedConstraint::GetFixedBody()
{
	if (!_fixedBody)
	{
		RigidBodyConstructionInfo cinfo(0, nullptr, nullptr);
		_fixedBody = gcnew RigidBody(%cinfo);
		_fixedBody->SetMassProps(0, Vector3_Zero);
	}
	return _fixedBody;
}

void TypedConstraint::GetInfo1(ConstraintInfo1^ info)
{
	_native->getInfo1(info->_native);
}

void TypedConstraint::GetInfo2(ConstraintInfo2^ info)
{
	_native->getInfo2(info->_native);
}

btScalar TypedConstraint::GetParam(ConstraintParam num, int axis)
{
	return _native->getParam((int)num, axis);
}

btScalar TypedConstraint::GetParam(ConstraintParam num)
{
	return _native->getParam((int)num);
}

#ifndef DISABLE_INTERNAL
btScalar TypedConstraint::InternalGetAppliedImpulse()
{
	return _native->internalGetAppliedImpulse();
}
#endif

void TypedConstraint::InternalSetAppliedImpulse(btScalar appliedImpulse)
{
	_native->internalSetAppliedImpulse(appliedImpulse);
}

#ifndef DISABLE_SERIALIZE
String^ TypedConstraint::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	return gcnew String(_native->serialize(dataBuffer.ToPointer(), serializer->_native));
}
#endif

void TypedConstraint::SetParam(ConstraintParam num, btScalar value, int axis)
{
	_native->setParam((int)num, value, axis);
}

void TypedConstraint::SetParam(ConstraintParam num, btScalar value)
{
	_native->setParam((int)num, value);
}
/*
void TypedConstraint::SetupSolverConstraint(ConstraintArray^ ca, int solverBodyA,
	int solverBodyB, btScalar timeStep)
{
	_native->setupSolverConstraint(*ca->_native, solverBodyA, solverBodyB, timeStep);
}
*/
btScalar TypedConstraint::AppliedImpulse::get()
{
	return _native->getAppliedImpulse();
}

btScalar TypedConstraint::BreakingImpulseThreshold::get()
{
	return _native->getBreakingImpulseThreshold();
}
void TypedConstraint::BreakingImpulseThreshold::set(btScalar threshold)
{
	_native->setBreakingImpulseThreshold(threshold);
}

TypedConstraintType TypedConstraint::ConstraintType::get()
{
	return (TypedConstraintType)_native->getConstraintType();
}

btScalar TypedConstraint::DebugDrawSize::get()
{
	return _native->getDbgDrawSize();
}
void TypedConstraint::DebugDrawSize::set(btScalar dbgDrawSize)
{
	_native->setDbgDrawSize(dbgDrawSize);
}

bool TypedConstraint::IsDisposed::get()
{
	return (_native == NULL);
}

bool TypedConstraint::IsEnabled::get()
{
	return _native->isEnabled();
}
void TypedConstraint::IsEnabled::set(bool enabled)
{
	_native->setEnabled(enabled);
}

BulletSharp::JointFeedback^ TypedConstraint::JointFeedback::get()
{
	return _jointFeedback;
}
void TypedConstraint::JointFeedback::set(BulletSharp::JointFeedback^ jointFeedback)
{
	_native->setJointFeedback(GetUnmanagedNullable(jointFeedback));
	_jointFeedback = jointFeedback;
}

bool TypedConstraint::NeedsFeedback::get()
{
	return _native->needsFeedback();
}
void TypedConstraint::NeedsFeedback::set(bool value)
{
	return _native->enableFeedback(value);
}

int TypedConstraint::OverrideNumSolverIterations::get()
{
	return _native->getOverrideNumSolverIterations();
}
void TypedConstraint::OverrideNumSolverIterations::set(int overideNumIterations)
{
	_native->setOverrideNumSolverIterations(overideNumIterations);
}

RigidBody^ TypedConstraint::RigidBodyA::get()
{
	return _rigidBodyA;
}

RigidBody^ TypedConstraint::RigidBodyB::get()
{
	return _rigidBodyB;
}

int TypedConstraint::Uid::get()
{
	return _native->getUid();
}

Object^ TypedConstraint::UserObject::get()
{
	return _userObject;
}
void TypedConstraint::UserObject::set(Object^ value)
{
	_userObject = value;
}

int TypedConstraint::UserConstraintType::get()
{
	return _native->getUserConstraintType();
}
void TypedConstraint::UserConstraintType::set(int value)
{
	return _native->setUserConstraintType(value);
}

btTypedConstraint* TypedConstraint::UnmanagedPointer::get()
{
	return _native;
}
void TypedConstraint::UnmanagedPointer::set(btTypedConstraint* value)
{
	_native = value;

	if (_native->getUserConstraintId() == -1)
	{
		GCHandle handle = GCHandle::Alloc(this);
		void* obj = GCHandleToVoidPtr(handle);
		_native->setUserConstraintPtr(obj);
	}
}


#ifdef _BT_USE_CENTER_LIMIT_
#ifdef IN_PARALLELL_SOLVER

AngularLimit::AngularLimit(btAngularLimit* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

AngularLimit::~AngularLimit()
{
	this->!AngularLimit();
}

AngularLimit::!AngularLimit()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

AngularLimit::AngularLimit()
{
	_native = new btAngularLimit();
}

void AngularLimit::Fit(btScalar% angle)
{
	btScalar angleTemp = angle;
	_native->fit(angleTemp);
	angle = angleTemp;
}

void AngularLimit::Set(btScalar low, btScalar high, btScalar softness, btScalar biasFactor,
	btScalar relaxationFactor)
{
	_native->set(low, high, softness, biasFactor, relaxationFactor);
}

void AngularLimit::Set(btScalar low, btScalar high, btScalar softness, btScalar biasFactor)
{
	_native->set(low, high, softness, biasFactor);
}

void AngularLimit::Set(btScalar low, btScalar high, btScalar softness)
{
	_native->set(low, high, softness);
}

void AngularLimit::Set(btScalar low, btScalar high)
{
	_native->set(low, high);
}

void AngularLimit::Test(btScalar angle)
{
	_native->test(angle);
}

btScalar AngularLimit::BiasFactor::get()
{
	return _native->getBiasFactor();
}

btScalar AngularLimit::Correction::get()
{
	return _native->getCorrection();
}

btScalar AngularLimit::Error::get()
{
	return _native->getError();
}

btScalar AngularLimit::HalfRange::get()
{
	return _native->getHalfRange();
}

btScalar AngularLimit::High::get()
{
	return _native->getHigh();
}

bool AngularLimit::IsLimit::get()
{
	return _native->isLimit();
}

btScalar AngularLimit::Low::get()
{
	return _native->getLow();
}

btScalar AngularLimit::RelaxationFactor::get()
{
	return _native->getRelaxationFactor();
}

btScalar AngularLimit::Sign::get()
{
	return _native->getSign();
}

btScalar AngularLimit::Softness::get()
{
	return _native->getSoftness();
}

#endif
#endif

#endif
