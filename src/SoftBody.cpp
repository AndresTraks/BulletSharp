#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "Collections.h"
#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"
#include "Dispatcher.h"
#include "RigidBody.h"
#include "SoftBody.h"
#include "SoftBodySolver.h"
#include "SparseSdf.h"
#include "StringConv.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif

using namespace BulletSharp::SoftBody;

SoftBodyCollisionShape::SoftBodyCollisionShape(btConvexShape* native)
	: ConvexShape(native)
{
}


SoftBodyWorldInfo::SoftBodyWorldInfo(btSoftBodyWorldInfo* native)
{
	_native = native;
	_preventDelete = true;
}

SoftBodyWorldInfo::~SoftBodyWorldInfo()
{
	this->!SoftBodyWorldInfo();
}

SoftBodyWorldInfo::!SoftBodyWorldInfo()
{
	if (!_preventDelete) {
		ALIGNED_FREE(_native);
	}
	_native = NULL;
}

SoftBodyWorldInfo::SoftBodyWorldInfo()
{
	_native = ALIGNED_NEW(btSoftBodyWorldInfo) ();
}

btScalar SoftBodyWorldInfo::AirDensity::get()
{
	return _native->air_density;
}
void SoftBodyWorldInfo::AirDensity::set(btScalar value)
{
	_native->air_density = value;
}

BroadphaseInterface^ SoftBodyWorldInfo::Broadphase::get()
{
	return _broadphase;
}
void SoftBodyWorldInfo::Broadphase::set(BroadphaseInterface^ value)
{
	_native->m_broadphase = GetUnmanagedNullable(value);
	_broadphase = value;
}

Dispatcher^ SoftBodyWorldInfo::Dispatcher::get()
{
	return _dispatcher;
}
void SoftBodyWorldInfo::Dispatcher::set(BulletSharp::Dispatcher^ value)
{
	_native->m_dispatcher = GetUnmanagedNullable(value);
	_dispatcher = value;
}

Vector3 SoftBodyWorldInfo::Gravity::get()
{
	return Math::BtVector3ToVector3(&_native->m_gravity);
}
void SoftBodyWorldInfo::Gravity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_gravity);
}

btScalar SoftBodyWorldInfo::MaxDisplacement::get()
{
	return _native->m_maxDisplacement;
}
void SoftBodyWorldInfo::MaxDisplacement::set(btScalar value)
{
	_native->m_maxDisplacement = value;
}

SparseSdf^ SoftBodyWorldInfo::SparseSdf::get()
{
	if (_sparseSdf == nullptr)
	{
		_sparseSdf = gcnew BulletSharp::SparseSdf(&_native->m_sparsesdf);
	}
	return _sparseSdf;
}

btScalar SoftBodyWorldInfo::WaterDensity::get()
{
	return _native->water_density;
}
void SoftBodyWorldInfo::WaterDensity::set(btScalar value)
{
	_native->water_density = value;
}

Vector3 SoftBodyWorldInfo::WaterNormal::get()
{
	return Math::BtVector3ToVector3(&_native->water_normal);
}
void SoftBodyWorldInfo::WaterNormal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->water_normal);
}

btScalar SoftBodyWorldInfo::WaterOffset::get()
{
	return _native->water_offset;
}
void SoftBodyWorldInfo::WaterOffset::set(btScalar value)
{
	_native->water_offset = value;
}


Joint::Specs::Specs(btSoftBody::Joint::Specs* native)
{
	_native = native;
}

Joint::Specs::~Specs()
{
	this->!Specs();
}

Joint::Specs::!Specs()
{
	ALIGNED_FREE(_native);
	_native = NULL;
}

btScalar Joint::Specs::Cfm::get()
{
	return _native->cfm;
}
void Joint::Specs::Cfm::set(btScalar value)
{
	_native->cfm = value;
}

btScalar Joint::Specs::Erp::get()
{
	return _native->erp;
}
void Joint::Specs::Erp::set(btScalar value)
{
	_native->erp = value;
}

btScalar Joint::Specs::Split::get()
{
	return _native->split;
}
void Joint::Specs::Split::set(btScalar value)
{
	_native->split = value;
}


Joint::Joint(btSoftBody::Joint* native)
{
	_native = native;
}

void Joint::Prepare(btScalar dt, int iterations)
{
	_native->Prepare(dt, iterations);
}

void Joint::Solve(btScalar dt, btScalar sor)
{
	_native->Solve(dt, sor);
}

void Joint::Terminate(btScalar dt)
{
	_native->Terminate(dt);
}

BodyArray^ Joint::Bodies::get()
{
	if (_bodies == nullptr)
	{
		_bodies = gcnew BodyArray(_native->m_bodies, 2);
	}
	return _bodies;
}

btScalar Joint::Cfm::get()
{
	return _native->m_cfm;
}
void Joint::Cfm::set(btScalar value)
{
	_native->m_cfm = value;
}

bool Joint::Delete::get()
{
	return _native->m_delete;
}
void Joint::Delete::set(bool value)
{
	_native->m_delete = value;
}

Vector3 Joint::Drift::get()
{
	return Math::BtVector3ToVector3(&_native->m_drift);
}
void Joint::Drift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_drift);
}

btScalar Joint::Erp::get()
{
	return _native->m_erp;
}
void Joint::Erp::set(btScalar value)
{
	_native->m_erp = value;
}

Matrix Joint::MassMatrix::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_massmatrix);
}
void Joint::MassMatrix::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_massmatrix);
}

Vector3Array^ BulletSharp::SoftBody::Joint::Refs::get()
{
	if (_refs == nullptr)
	{
		_refs = gcnew Vector3Array(_native->m_refs, 2);
	}
	return _refs;
}

Vector3 Joint::SDrift::get()
{
	return Math::BtVector3ToVector3(&_native->m_sdrift);
}
void Joint::SDrift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_sdrift);
}

btScalar Joint::Split::get()
{
	return _native->m_split;
}
void Joint::Split::set(btScalar value)
{
	_native->m_split = value;
}

Joint::JointType BulletSharp::SoftBody::Joint::Type::get()
{
	return (JointType)_native->Type();
}


void AJoint::IControl::PrepareUnmanaged(IntPtr aJoint)
{
    Prepare(gcnew AJoint(static_cast<btSoftBody::AJoint*>(aJoint.ToPointer())));
}

btScalar AJoint::IControl::SpeedUnmanaged(IntPtr aJoint, btScalar current)
{
    return Speed(gcnew AJoint(static_cast<btSoftBody::AJoint*>(aJoint.ToPointer())), current);
}

AJoint::IControl::IControl(btSoftBody::AJoint::IControl* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

AJoint::IControl::~IControl()
{
	this->!IControl();
}

AJoint::IControl::!IControl()
{
	if (!_preventDelete)
	{
		ALIGNED_FREE(_native);
	}
	_native = NULL;
}

AJoint::IControl::IControl()
{
	_prepare = gcnew PrepareUnmanagedDelegate(this, &IControl::PrepareUnmanaged);
	_speed = gcnew SpeedUnmanagedDelegate(this, &IControl::SpeedUnmanaged);
	_native = ALIGNED_NEW(AJointIControlWrapper) (
		(pIControl_Prepare) Marshal::GetFunctionPointerForDelegate(_prepare).ToPointer(),
		(pIControl_Speed) Marshal::GetFunctionPointerForDelegate(_speed).ToPointer());
}

AJoint::IControl^ AJoint::IControl::Default()
{
	if (_default == nullptr)
	{
		_default = gcnew IControl(btSoftBody::AJoint::IControl::Default(), true);
	}
	return _default;
}

void AJoint::IControl::Prepare(AJoint^ joint)
{
}

btScalar AJoint::IControl::Speed(AJoint^ joint, btScalar current)
{
	return current;
}


AJointIControlWrapper::AJointIControlWrapper(pIControl_Prepare PrepareCallback, pIControl_Speed SpeedCallback)
{
	_prepareCallback = PrepareCallback;
	_speedCallback = SpeedCallback;
}

void AJointIControlWrapper::Prepare(btSoftBody::AJoint* joint)
{
	_prepareCallback(joint);
}

btScalar AJointIControlWrapper::Speed(btSoftBody::AJoint* joint, btScalar current)
{
	return _speedCallback(joint, current);
}


#define Native static_cast<btSoftBody::AJoint::Specs*>(_native)

AJoint::Specs::Specs()
	: Joint::Specs(ALIGNED_NEW(btSoftBody::AJoint::Specs)())
{
}

Vector3 AJoint::Specs::Axis::get()
{
	return Math::BtVector3ToVector3(&Native->axis);
}
void AJoint::Specs::Axis::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->axis);
}

AJoint::IControl^ AJoint::Specs::Control::get()
{
	if (_iControl == nullptr)
	{
		_iControl = gcnew AJoint::IControl(Native->icontrol, true);
	}
	return _iControl;
}
void AJoint::Specs::Control::set(IControl^ value)
{
	Native->icontrol = value->_native;
	_iControl = value;
}


#undef Native
#define Native static_cast<btSoftBody::AJoint*>(_native)

AJoint::AJoint(btSoftBody::AJoint* native)
	: Joint(native)
{
}

Vector3Array^ AJoint::Axis::get()
{
	if (_axis == nullptr)
	{
		_axis = gcnew Vector3Array(Native->m_axis, 2);
	}
	return _axis;
}

AJoint::IControl^ AJoint::Control::get()
{
	if (_iControl == nullptr)
	{
		_iControl = gcnew AJoint::IControl(Native->m_icontrol, true);
	}
	return _iControl;
}
void AJoint::Control::set(IControl^ value)
{
	Native->m_icontrol = value->_native;
	_iControl = value;
}


Anchor::Anchor(btSoftBody::Anchor* native)
{
	_native = native;
}

RigidBody^ Anchor::Body::get()
{
	return (RigidBody^)CollisionObject::GetManaged(_native->m_body);
}
void Anchor::Body::set(RigidBody^ value)
{
	_native->m_body = (btRigidBody*)GetUnmanagedNullable(value);
}

Matrix Anchor::C0::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_c0);
}
void Anchor::C0::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_c0);
}

Vector3 Anchor::C1::get()
{
	return Math::BtVector3ToVector3(&_native->m_c1);
}
void Anchor::C1::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_c1);
}

btScalar Anchor::C2::get()
{
	return _native->m_c2;
}
void Anchor::C2::set(btScalar value)
{
	_native->m_c2 = value;
}

btScalar Anchor::Influence::get()
{
	return _native->m_influence;
}
void Anchor::Influence::set(btScalar value)
{
	_native->m_influence = value;
}

Vector3 Anchor::Local::get()
{
	return Math::BtVector3ToVector3(&_native->m_local);
}
void Anchor::Local::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_local);
}

BulletSharp::SoftBody::Node^ Anchor::Node::get()
{
	ReturnCachedObjectGcnewNullable(BulletSharp::SoftBody::Node, _node, _native->m_node);
}
void Anchor::Node::set(BulletSharp::SoftBody::Node^ value)
{
	_native->m_node = (btSoftBody::Node*)GetUnmanagedNullable(value);
	_node = value;
}


Body::Body(btSoftBody::Body* native)
{
	_native = native;
}

Body::~Body()
{
	this->!Body();
}

Body::!Body()
{
	ALIGNED_FREE(_native);
	_native = NULL;
}

Body::Body()
{
	_native = ALIGNED_NEW(btSoftBody::Body)();
}

Body::Body(BulletSharp::CollisionObject^ colObj)
{
	_native = ALIGNED_NEW(btSoftBody::Body) (GetUnmanagedNullable(colObj));
}

Body::Body(Cluster^ p)
{
	_native = ALIGNED_NEW(btSoftBody::Body) (p->_native);
}

void Body::Activate()
{
	_native->activate();
}

void Body::ApplyAImpulse(Impulse^ impulse)
{
	_native->applyAImpulse(*impulse->_native);
}

void Body::ApplyDAImpulse(Vector3 impulse)
{
	VECTOR3_CONV(impulse);
	_native->applyDAImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void Body::ApplyDCImpulse(Vector3 impulse)
{
	VECTOR3_CONV(impulse);
	_native->applyDCImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void Body::ApplyDImpulse(Vector3 impulse, Vector3 rPos)
{
	VECTOR3_CONV(impulse);
	VECTOR3_CONV(rPos);
	_native->applyDImpulse(VECTOR3_USE(impulse), VECTOR3_USE(rPos));
	VECTOR3_DEL(impulse);
	VECTOR3_DEL(rPos);
}

void Body::ApplyImpulse(Impulse^ impulse, Vector3 rPos)
{
	VECTOR3_CONV(rPos);
	_native->applyImpulse(*impulse->_native, VECTOR3_USE(rPos));
	VECTOR3_DEL(rPos);
}

void Body::ApplyVAImpulse(Vector3 impulse)
{
	VECTOR3_CONV(impulse);
	_native->applyVAImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void Body::ApplyVImpulse(Vector3 impulse, Vector3 rpos)
{
	VECTOR3_CONV(impulse);
	VECTOR3_CONV(rpos);
	_native->applyVImpulse(VECTOR3_USE(impulse), VECTOR3_USE(rpos));
	VECTOR3_DEL(impulse);
	VECTOR3_DEL(rpos);
}

#pragma managed(push, off)
void Body_GetAngularVelocity(btSoftBody::Body* body, btVector3* rPos, btVector3* velocity)
{
	*velocity = body->angularVelocity(*rPos);
}
#pragma managed(pop)
Vector3 Body::GetAngularVelocity(Vector3 rPos)
{
	VECTOR3_CONV(rPos);
	btVector3* velocityTemp = ALIGNED_NEW(btVector3);
	Body_GetAngularVelocity(_native, VECTOR3_PTR(rPos), velocityTemp);
	VECTOR3_DEL(rPos);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	ALIGNED_FREE(velocityTemp);
	return velocity;
}

#pragma managed(push, off)
void Body_GetVelocity(btSoftBody::Body* body, btVector3* rPos, btVector3* velocity)
{
	*velocity = body->velocity(*rPos);
}
#pragma managed(pop)
Vector3 Body::Velocity(Vector3 rPos)
{
	VECTOR3_CONV(rPos);
	btVector3* velocityTemp = ALIGNED_NEW(btVector3);
	Body_GetVelocity(_native, VECTOR3_PTR(rPos), velocityTemp);
	VECTOR3_DEL(rPos);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	ALIGNED_FREE(velocityTemp);
	return velocity;
}

#pragma managed(push, off)
void Body_GetAngularVelocity(btSoftBody::Body* body, btVector3* velocity)
{
	*velocity = body->angularVelocity();
}
#pragma managed(pop)
Vector3 Body::AngularVelocity::get()
{
	btVector3* velocityTemp = ALIGNED_NEW(btVector3);
	Body_GetAngularVelocity(_native, velocityTemp);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	ALIGNED_FREE(velocityTemp);
	return velocity;
}

CollisionObject^ Body::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_collisionObject);
}
void Body::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_native->m_collisionObject = GetUnmanagedNullable(value);
}

btScalar Body::InvMass::get()
{
	return _native->invMass();
}

Matrix Body::InvWorldInertia::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->invWorldInertia());
}

#pragma managed(push, off)
void Body_GetLinearVelocity(btSoftBody::Body* body, btVector3* velocity)
{
	*velocity = body->linearVelocity();
}
#pragma managed(pop)
Vector3 Body::LinearVelocity::get()
{
	btVector3* velocityTemp = ALIGNED_NEW(btVector3);
	Body_GetLinearVelocity(_native, velocityTemp);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	ALIGNED_FREE(velocityTemp);
	return velocity;
}

RigidBody^ Body::Rigid::get()
{
	return (RigidBody^)BulletSharp::CollisionObject::GetManaged(_native->m_rigid);
}
void Body::Rigid::set(RigidBody^ value)
{
	_native->m_rigid = (btRigidBody*)GetUnmanagedNullable(value);
}

Cluster^ Body::Soft::get()
{
	ReturnCachedObjectGcnewNullable(BulletSharp::SoftBody::Cluster, _soft, _native->m_soft);
}
void Body::Soft::set(Cluster^ value)
{
	_soft = value;
	_native->m_soft = GetUnmanagedNullable(value);
}

Matrix Body::XForm::get()
{
	// Unaligned btTransform::getIdentity() in the inline xform() method causes problems.
#ifdef BT_USE_SSE_IN_API
	if(_native->m_collisionObject) return Math::BtTransformToMatrix(&_native->m_collisionObject->getWorldTransform());
	if(_native->m_soft) return Math::BtTransformToMatrix(&_native->m_soft->m_framexform);
	return Matrix_Identity;
#else
	return Math::BtTransformToMatrix(&_native->xform());
#endif
}


#undef Native
#define Native static_cast<btSoftBody::CJoint*>(_native)

CJoint::CJoint(btSoftBody::CJoint* native)
	: Joint(native)
{
}

btScalar CJoint::Friction::get()
{
	return Native->m_friction;
}
void CJoint::Friction::set(btScalar value)
{
	Native->m_friction = value;
}

int CJoint::Life::get()
{
	return Native->m_life;
}
void CJoint::Life::set(int value)
{
	Native->m_life = value;
}

int CJoint::MaxLife::get()
{
	return Native->m_maxlife;
}
void CJoint::MaxLife::set(int value)
{
	Native->m_maxlife = value;
}

Vector3 CJoint::Normal::get()
{
	return Math::BtVector3ToVector3(&Native->m_normal);
}
void CJoint::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_normal);
}

Vector3Array^ CJoint::RPos::get()
{
	if (_rPos == nullptr)
	{
		_rPos = gcnew Vector3Array(Native->m_rpos, 2);
	}
	return _rPos;
}


Cluster::Cluster(btSoftBody::Cluster* native)
{
	_native = native;
}

btScalar Cluster::AngularDamping::get()
{
	return _native->m_adamping;
}
void Cluster::AngularDamping::set(btScalar value)
{
	_native->m_adamping = value;
}

Vector3 Cluster::AV::get()
{
	return Math::BtVector3ToVector3(&_native->m_av);
}
void Cluster::AV::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_av);
}

int Cluster::ClusterIndex::get()
{
	return _native->m_clusterIndex;
}
void Cluster::ClusterIndex::set(int value)
{
	_native->m_clusterIndex = value;
}

bool Cluster::Collide::get()
{
	return _native->m_collide;
}
void Cluster::Collide::set(bool value)
{
	_native->m_collide = value;
}

Vector3 Cluster::Com::get()
{
	return Math::BtVector3ToVector3(&_native->m_com);
}
void Cluster::Com::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_com);
}

bool Cluster::ContainsAnchor::get()
{
	return _native->m_containsAnchor;
}
void Cluster::ContainsAnchor::set(bool value)
{
	_native->m_containsAnchor = value;
}

Vector3Array^ Cluster::DImpulses::get()
{
	if (_dImpulses == nullptr)
	{
		_dImpulses = gcnew Vector3Array(_native->m_dimpulses, 2);
	}
	return _dImpulses;
}

AlignedVector3Array^ Cluster::FrameRefs::get()
{
	if (_frameRefs == nullptr)
	{
		_frameRefs = gcnew AlignedVector3Array(&_native->m_framerefs);
	}
	return _frameRefs;
}

Matrix Cluster::FrameTransform::get()
{
	return Math::BtTransformToMatrix(&_native->m_framexform);
}
void Cluster::FrameTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_framexform);
}

btScalar Cluster::IDMass::get()
{
	return _native->m_idmass;
}
void Cluster::IDMass::set(btScalar value)
{
	_native->m_idmass = value;
}

btScalar Cluster::IMass::get()
{
	return _native->m_imass;
}
void Cluster::IMass::set(btScalar value)
{
	_native->m_imass = value;
}

Matrix Cluster::InvWI::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_invwi);
}
void Cluster::InvWI::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_invwi);
}

#ifndef DISABLE_DBVT
DbvtNode^ Cluster::Leaf::get()
{
	ReturnCachedObjectGcnewNullable(DbvtNode, _leaf, _native->m_leaf);
}
void Cluster::Leaf::set(DbvtNode^ value)
{
	_leaf = value;
	_native->m_leaf = GetUnmanagedNullable(value);
}
#endif

btScalar Cluster::LinearDamping::get()
{
	return _native->m_ldamping;
}
void Cluster::LinearDamping::set(btScalar value)
{
	_native->m_ldamping = value;
}

Matrix Cluster::Locii::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_locii);
}
void Cluster::Locii::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_locii);
}

Vector3 Cluster::LV::get()
{
	return Math::BtVector3ToVector3(&_native->m_lv);
}
void Cluster::LV::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_lv);
}

AlignedScalarArray^ Cluster::Masses::get()
{
	if (_masses == nullptr)
	{
		_masses = gcnew AlignedScalarArray(&_native->m_masses);
	}
	return _masses;
}

btScalar Cluster::Matching::get()
{
	return _native->m_matching;
}
void Cluster::Matching::set(btScalar value)
{
	_native->m_matching = value;
}

btScalar Cluster::MaxSelfCollisionImpulse::get()
{
	return _native->m_maxSelfCollisionImpulse;
}
void Cluster::MaxSelfCollisionImpulse::set(btScalar value)
{
	_native->m_maxSelfCollisionImpulse = value;
}

int Cluster::NDImpulses::get()
{
	return _native->m_ndimpulses;
}

btScalar Cluster::NodeDamping::get()
{
	return _native->m_ndamping;
}
void Cluster::NodeDamping::set(btScalar value)
{
	_native->m_ndamping = value;
}

AlignedNodePtrArray^ Cluster::Nodes::get()
{
	if (_nodes == nullptr)
	{
		_nodes = gcnew AlignedNodePtrArray(&_native->m_nodes);
	}
	return _nodes;
}

int Cluster::NVImpulses::get()
{
	return _native->m_nvimpulses;
}

btScalar Cluster::SelfCollisionImpulseFactor::get()
{
	return _native->m_selfCollisionImpulseFactor;
}
void Cluster::SelfCollisionImpulseFactor::set(btScalar value)
{
	_native->m_selfCollisionImpulseFactor = value;
}

Vector3Array^ Cluster::VImpulses::get()
{
	if (_vImpulses == nullptr)
	{
		_vImpulses = gcnew Vector3Array(_native->m_vimpulses, 2);
	}
	return _vImpulses;
}


Config::Config(btSoftBody::Config* native)
{
	_native = native;
}

AeroModel Config::AeroModel::get()
{
	return (BulletSharp::SoftBody::AeroModel)_native->aeromodel;
}
void Config::AeroModel::set(BulletSharp::SoftBody::AeroModel value)
{
	_native->aeromodel = (btSoftBody::eAeroModel::_)value;
}

btScalar Config::Ahr::get()
{
	return _native->kAHR;
}
void Config::Ahr::set(btScalar value)
{
	_native->kAHR = value;
}

btScalar Config::Chr::get()
{
	return _native->kCHR;
}
void Config::Chr::set(btScalar value)
{
	_native->kCHR = value;
}

int Config::CIterations::get()
{
	return _native->citerations;
}
void Config::CIterations::set(int value)
{
	_native->citerations = value;
}

FCollisions Config::Collisions::get()
{
	return (FCollisions)_native->collisions;
}
void Config::Collisions::set(FCollisions value)
{
	_native->collisions = (int)value;
}

btScalar Config::DF::get()
{
	return _native->kDF;
}
void Config::DF::set(btScalar value)
{
	_native->kDF = value;
}

btScalar Config::DG::get()
{
	return _native->kDG;
}
void Config::DG::set(btScalar value)
{
	_native->kDG = value;
}

int Config::DIterations::get()
{
	return _native->diterations;
}
void Config::DIterations::set(int value)
{
	_native->diterations = value;
}

btScalar Config::DP::get()
{
	return _native->kDP;
}
void Config::DP::set(btScalar value)
{
	_native->kDP = value;
}

AlignedPSolverArray^ Config::DSequence::get()
{
	if (_dSequence == nullptr)
	{
		_dSequence = gcnew AlignedPSolverArray(&_native->m_dsequence);
	}
	return _dSequence;
}

btScalar Config::Khr::get()
{
	return _native->kKHR;
}
void Config::Khr::set(btScalar value)
{
	_native->kKHR = value;
}

btScalar Config::LF::get()
{
	return _native->kLF;
}
void Config::LF::set(btScalar value)
{
	_native->kLF = value;
}

btScalar Config::MaxVolume::get()
{
	return _native->maxvolume;
}
void Config::MaxVolume::set(btScalar value)
{
	_native->maxvolume = value;
}

btScalar Config::MT::get()
{
	return _native->kMT;
}
void Config::MT::set(btScalar value)
{
	_native->kMT = value;
}

int Config::PIterations::get()
{
	return _native->piterations;
}
void Config::PIterations::set(int value)
{
	_native->piterations = value;
}

btScalar Config::PR::get()
{
	return _native->kPR;
}
void Config::PR::set(btScalar value)
{
	_native->kPR = value;
}

AlignedPSolverArray^ Config::PSequence::get()
{
	if (_pSequence == nullptr)
	{
		_pSequence = gcnew AlignedPSolverArray(&_native->m_psequence);
	}
	return _pSequence;
}

btScalar Config::Shr::get()
{
	return _native->kSHR;
}
void Config::Shr::set(btScalar value)
{
	_native->kSHR = value;
}

btScalar Config::SkhrCl::get()
{
	return _native->kSKHR_CL;
}
void Config::SkhrCl::set(btScalar value)
{
	_native->kSKHR_CL = value;
}

btScalar Config::SrhrCl::get()
{
	return _native->kSRHR_CL;
}
void Config::SrhrCl::set(btScalar value)
{
	_native->kSRHR_CL = value;
}

btScalar Config::SshrCl::get()
{
	return _native->kSSHR_CL;
}
void Config::SshrCl::set(btScalar value)
{
	_native->kSSHR_CL = value;
}

btScalar Config::SKSplitCl::get()
{
	return _native->kSK_SPLT_CL;
}
void Config::SKSplitCl::set(btScalar value)
{
	_native->kSK_SPLT_CL = value;
}

btScalar Config::SRSplitCl::get()
{
	return _native->kSR_SPLT_CL;
}
void Config::SRSplitCl::set(btScalar value)
{
	_native->kSR_SPLT_CL = value;
}

btScalar Config::SSSplitCl::get()
{
	return _native->kSS_SPLT_CL;
}
void Config::SSSplitCl::set(btScalar value)
{
	_native->kSS_SPLT_CL = value;
}

btScalar Config::TimeScale::get()
{
	return _native->timescale;
}
void Config::TimeScale::set(btScalar value)
{
	_native->timescale = value;
}

btScalar Config::VC::get()
{
	return _native->kVC;
}
void Config::VC::set(btScalar value)
{
	_native->kVC = value;
}

btScalar Config::VCF::get()
{
	return _native->kVCF;
}
void Config::VCF::set(btScalar value)
{
	_native->kVCF = value;
}

int Config::VIterations::get()
{
	return _native->viterations;
}
void Config::VIterations::set(int value)
{
	_native->viterations = value;
}

AlignedVSolverArray^ Config::VSequence::get()
{
	if (_vSequence == nullptr)
	{
		_vSequence = gcnew AlignedVSolverArray(&_native->m_vsequence);
	}
	return _vSequence;
}


ContactInfo::ContactInfo(btSoftBody::sCti* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

ContactInfo::~ContactInfo()
{
	this->!ContactInfo();
}

ContactInfo::!ContactInfo()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

ContactInfo::ContactInfo()
{
	_native = new btSoftBody::sCti();
}

CollisionObject^ ContactInfo::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_colObj);
}
void ContactInfo::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_native->m_colObj = GetUnmanagedNullable(value);
}

Vector3 ContactInfo::Normal::get()
{
	return Math::BtVector3ToVector3(&_native->m_normal);
}
void ContactInfo::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_normal);
}

btScalar ContactInfo::Offset::get()
{
	return _native->m_offset;
}
void ContactInfo::Offset::set(btScalar value)
{
	_native->m_offset = value;
}


Element::Element(btSoftBody::Element* native)
{
	_native = native;
}

IntPtr Element::Tag::get()
{
	return IntPtr(_native->m_tag);
}
void Element::Tag::set(IntPtr value)
{
	_native->m_tag = value.ToPointer();
}


#undef Native
#define Native static_cast<btSoftBody::Feature*>(_native)

Feature::Feature(btSoftBody::Feature* native)
	: Element(native)
{
}

BulletSharp::SoftBody::Material^ Feature::Material::get()
{
	ReturnCachedObjectGcnewNullable(BulletSharp::SoftBody::Material, _material, Native->m_material);
}
void Feature::Material::set(BulletSharp::SoftBody::Material^ value)
{
	Native->m_material = (btSoftBody::Material*)value->_native;
	_material = value;
}


#undef Native
#define Native static_cast<btSoftBody::Face*>(_native)

Face::Face(btSoftBody::Face* native)
	: Feature(native)
{
}

#ifndef DISABLE_DBVT
DbvtNode^ Face::Leaf::get()
{
	ReturnCachedObjectGcnewNullable(DbvtNode, _leaf, Native->m_leaf);
}
void Face::Leaf::set(DbvtNode^ value)
{
	Native->m_leaf = GetUnmanagedNullable(value);
	_leaf = value;
}
#endif

NodePtrArray^ Face::N::get()
{
	if (_n == nullptr)
	{
		_n = gcnew NodePtrArray(Native->m_n, 3);
	}
	return _n;
}

Vector3 Face::Normal::get()
{
	return Math::BtVector3ToVector3(&Native->m_normal);
}
void Face::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_normal);
}

btScalar Face::RestArea::get()
{
	return Native->m_ra;
}
void Face::RestArea::set(btScalar value)
{
	Native->m_ra = value;
}


ImplicitFn::ImplicitFn()
{
	_eval = gcnew EvalUnmanagedDelegate(this, &ImplicitFn::EvalUnmanaged);
	_native = new ImplicitFnWrapper(
		(pImplicitFn_Eval) Marshal::GetFunctionPointerForDelegate(_eval).ToPointer());
}

btScalar ImplicitFn::EvalUnmanaged(IntPtr x)
{
	return Eval(Math::BtVector3ToVector3(static_cast<btVector3*>(x.ToPointer())));
}

ImplicitFn::~ImplicitFn()
{
	this->!ImplicitFn();
}

ImplicitFn::!ImplicitFn()
{
	delete _native;
	_native = NULL;
}


ImplicitFnWrapper::ImplicitFnWrapper(pImplicitFn_Eval evalCallback)
{
	_evalCallback = evalCallback;
}

btScalar ImplicitFnWrapper::Eval(const btVector3& x)
{
	return _evalCallback(x);
}


Impulse::Impulse(btSoftBody::Impulse* native)
{
	_native = native;
}

Impulse::~Impulse()
{
	this->!Impulse();
}

Impulse::!Impulse()
{
	delete _native;
	_native = NULL;
}

Impulse::Impulse()
{
	_native = new btSoftBody::Impulse();
}

#pragma managed(push, off)
btSoftBody::Impulse* Impulse_Negative(btSoftBody::Impulse* impulse)
{
	btSoftBody::Impulse* impulseNew = new btSoftBody::Impulse();
	*impulseNew = -*impulse;
	return impulseNew;
}
#pragma managed(pop)
Impulse^ Impulse::operator-(Impulse^ i)
{
	return gcnew Impulse(Impulse_Negative(i->_native));
}

#pragma managed(push, off)
btSoftBody::Impulse* Impulse_Multiply(btSoftBody::Impulse* impulse, btScalar x)
{
	btSoftBody::Impulse* impulseNew = new btSoftBody::Impulse();
	*impulseNew = (*impulse) * x;
	return impulseNew;
}
#pragma managed(pop)
Impulse^ Impulse::operator*(Impulse^ i, btScalar x)
{
	return gcnew Impulse(Impulse_Multiply(i->_native, x));
}

bool Impulse::AsDrift::get()
{
	return _native->m_asDrift != 0;
}
void Impulse::AsDrift::set(bool value)
{
	_native->m_asDrift = value;
}

bool Impulse::AsVelocity::get()
{
	return _native->m_asVelocity != 0;
}
void Impulse::AsVelocity::set(bool value)
{
	_native->m_asVelocity = value;
}

Vector3 Impulse::Drift::get()
{
	return Math::BtVector3ToVector3(&_native->m_drift);
}
void Impulse::Drift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_drift);
}

Vector3 Impulse::Velocity::get()
{
	return Math::BtVector3ToVector3(&_native->m_velocity);
}
void Impulse::Velocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_velocity);
}


#undef Native
#define Native static_cast<btSoftBody::Link*>(_native)

Link::Link(btSoftBody::Link* native)
	: Feature(native)
{
}

btScalar Link::C0::get()
{
	return Native->m_c0;
}
void Link::C0::set(btScalar value)
{
	Native->m_c0 = value;
}

btScalar Link::C1::get()
{
	return Native->m_c1;
}
void Link::C1::set(btScalar value)
{
	Native->m_c1 = value;
}

btScalar Link::C2::get()
{
	return Native->m_c2;
}
void Link::C2::set(btScalar value)
{
	Native->m_c2 = value;
}

Vector3 Link::C3::get()
{
	return Math::BtVector3ToVector3(&Native->m_c3);
}
void Link::C3::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_c3);
}

bool Link::IsBending::get()
{
	return Native->m_bbending != 0;
}
void Link::IsBending::set(bool value)
{
	Native->m_bbending = value;
}

NodePtrArray^ Link::Nodes::get()
{
	if (_nodes == nullptr)
	{
		_nodes = gcnew NodePtrArray(Native->m_n, 2);
	}
	return _nodes;
}

btScalar Link::RestLength::get()
{
	return Native->m_rl;
}
void Link::RestLength::set(btScalar value)
{
	Native->m_rl = value;
}


#undef Native
#define Native static_cast<btSoftBody::LJoint::Specs*>(_native)

LJoint::Specs::Specs()
	: Joint::Specs(ALIGNED_NEW(btSoftBody::LJoint::Specs)())
{
}

Vector3 LJoint::Specs::Position::get()
{
	return Math::BtVector3ToVector3(&Native->position);
}
void LJoint::Specs::Position::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->position);
}


#undef Native
#define Native static_cast<btSoftBody::LJoint*>(_native)

LJoint::LJoint(btSoftBody::LJoint* native)
	: Joint(native)
{
}

Vector3Array^ BulletSharp::SoftBody::LJoint::RPos::get()
{
	if (_rPos == nullptr)
	{
		_rPos = gcnew Vector3Array(Native->m_rpos, 2);
	}
	return _rPos;
}


#undef Native
#define Native static_cast<btSoftBody::Material*>(_native)

BulletSharp::SoftBody::Material::Material(btSoftBody::Material* native)
	: Element(native)
{
}

btScalar BulletSharp::SoftBody::Material::Ast::get()
{
	return Native->m_kAST;
}
void BulletSharp::SoftBody::Material::Ast::set(btScalar value)
{
	Native->m_kAST = value;
}

FMaterial BulletSharp::SoftBody::Material::Flags::get()
{
	return (FMaterial)Native->m_flags;
}
void BulletSharp::SoftBody::Material::Flags::set(FMaterial value)
{
	Native->m_flags = (int)value;
}

btScalar BulletSharp::SoftBody::Material::Lst::get()
{
	return Native->m_kLST;
}
void BulletSharp::SoftBody::Material::Lst::set(btScalar value)
{
	Native->m_kLST = value;
}

btScalar BulletSharp::SoftBody::Material::Vst::get()
{
	return Native->m_kVST;
}
void BulletSharp::SoftBody::Material::Vst::set(btScalar value)
{
	Native->m_kVST = value;
}


#undef Native
#define Native static_cast<btSoftBody::Node*>(_native)

BulletSharp::SoftBody::Node::Node(btSoftBody::Node* native)
	: Feature(native)
{
}

void BulletSharp::SoftBody::Node::GetNormal([Out] Vector3% normal)
{
	BtVector3ToVector3Fast(&Native->m_n, normal);
}

void BulletSharp::SoftBody::Node::GetX([Out] Vector3% x)
{
	BtVector3ToVector3Fast(&Native->m_x, x);
}

btScalar BulletSharp::SoftBody::Node::Area::get()
{
	return Native->m_area;
}
void BulletSharp::SoftBody::Node::Area::set(btScalar value)
{
	Native->m_area = value;
}

Vector3 BulletSharp::SoftBody::Node::Force::get()
{
	return Math::BtVector3ToVector3(&Native->m_f);
}
void BulletSharp::SoftBody::Node::Force::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_f);
}

btScalar BulletSharp::SoftBody::Node::InverseMass::get()
{
	return Native->m_im;
}
void BulletSharp::SoftBody::Node::InverseMass::set(btScalar value)
{
	Native->m_im = value;
}

bool BulletSharp::SoftBody::Node::IsAttached::get()
{
	return Native->m_battach != 0;
}
void BulletSharp::SoftBody::Node::IsAttached::set(bool value)
{
	Native->m_battach = value;
}

#ifndef DISABLE_DBVT
DbvtNode^ BulletSharp::SoftBody::Node::Leaf::get()
{
	ReturnCachedObjectGcnewNullable(DbvtNode, _leaf, Native->m_leaf);
}
void BulletSharp::SoftBody::Node::Leaf::set(DbvtNode^ value)
{
	Native->m_leaf = GetUnmanagedNullable(value);
	_leaf = value;
}
#endif

Vector3 BulletSharp::SoftBody::Node::Normal::get()
{
	return Math::BtVector3ToVector3(&Native->m_n);
}
void BulletSharp::SoftBody::Node::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_n);
}

Vector3 BulletSharp::SoftBody::Node::Q::get()
{
	return Math::BtVector3ToVector3(&Native->m_q);
}
void BulletSharp::SoftBody::Node::Q::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_q);
}

Vector3 BulletSharp::SoftBody::Node::Velocity::get()
{
	return Math::BtVector3ToVector3(&Native->m_v);
}
void BulletSharp::SoftBody::Node::Velocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_v);
}

Vector3 BulletSharp::SoftBody::Node::X::get()
{
	return BtVector3ToVector3FastRet(&Native->m_x);
}
void BulletSharp::SoftBody::Node::X::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_x);
}


#undef Native
#define Native static_cast<btSoftBody::Note*>(_native)

Note::Note(btSoftBody::Note* native)
	: Element(native)
{
}

ScalarArray^ Note::Coords::get()
{
	if (_coords == nullptr)
	{
		_coords = gcnew ScalarArray(&Native->m_coords[0], 4);
	}
	return _coords;
}

NodePtrArray^ Note::Nodes::get()
{
	if (_nodes == nullptr)
	{
		_nodes = gcnew NodePtrArray(&Native->m_nodes[0], 4);
	}
	return _nodes;
}

Vector3 Note::Offset::get()
{
	return Math::BtVector3ToVector3(&Native->m_offset);
}
void Note::Offset::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_offset);
}

int Note::Rank::get()
{
	return Native->m_rank;
}
void Note::Rank::set(int value)
{
	Native->m_rank = value;
}

String^ Note::Text::get()
{
	return StringConv::UnmanagedToManaged(Native->m_text);
}
void Note::Text::set(String^ value)
{
	// TODO: cleanup
	Native->m_text = StringConv::ManagedToUnmanaged(value);
}


BulletSharp::SoftBody::Pose::Pose(btSoftBody::Pose* native)
{
	_native = native;
}

Matrix BulletSharp::SoftBody::Pose::Aqq::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_aqq);
}
void BulletSharp::SoftBody::Pose::Aqq::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_aqq);
}

Vector3 BulletSharp::SoftBody::Pose::Com::get()
{
	return Math::BtVector3ToVector3(&_native->m_com);
}
void BulletSharp::SoftBody::Pose::Com::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_com);
}

bool BulletSharp::SoftBody::Pose::IsFrameValid::get()
{
	return _native->m_bframe;
}
void BulletSharp::SoftBody::Pose::IsFrameValid::set(bool value)
{
	_native->m_bframe = value;
}

bool BulletSharp::SoftBody::Pose::IsVolumeValid::get()
{
	return _native->m_bvolume;
}
void BulletSharp::SoftBody::Pose::IsVolumeValid::set(bool value)
{
	_native->m_bvolume = value;
}

AlignedVector3Array^ BulletSharp::SoftBody::Pose::Positions::get()
{
	if (_positions == nullptr)
	{
		_positions = gcnew AlignedVector3Array(&_native->m_pos);
	}
	return _positions;
}

Matrix BulletSharp::SoftBody::Pose::Rotation::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_rot);
}
void BulletSharp::SoftBody::Pose::Rotation::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_rot);
}

Matrix BulletSharp::SoftBody::Pose::Scale::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_scl);
}
void BulletSharp::SoftBody::Pose::Scale::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_scl);
}

btScalar BulletSharp::SoftBody::Pose::Volume::get()
{
	return _native->m_volume;
}
void BulletSharp::SoftBody::Pose::Volume::set(btScalar value)
{
	_native->m_volume = value;
}

AlignedScalarArray^ BulletSharp::SoftBody::Pose::Weights::get()
{
	return gcnew AlignedScalarArray(&_native->m_wgh);
}


/*
#define Native static_cast<btSoftBody::RayFromToCaster*>(_native)

RayFromToCaster::RayFromToCaster(btSoftBody::RayFromToCaster* native)
	: ICollide(native)
{
}

RayFromToCaster::RayFromToCaster(Vector3 rayFrom, Vector3 rayTo, btScalar mxt)
	: ICollide(0)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	_native = new btSoftBody::RayFromToCaster(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo),
		mxt);
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

btScalar RayFromToCaster::RayFromToTriangle(Vector3 rayFrom, Vector3 rayTo,
	Vector3 rayNormalizedDirection, Vector3 a, Vector3 b, Vector3 c, btScalar maxt)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	VECTOR3_CONV(rayNormalizedDirection);
	VECTOR3_CONV(a);
	VECTOR3_CONV(b);
	VECTOR3_CONV(c);
	btScalar ret = btSoftBody::RayFromToCaster::rayFromToTriangle(VECTOR3_USE(rayFrom),
		VECTOR3_USE(rayTo), VECTOR3_USE(rayNormalizedDirection), VECTOR3_USE(a), VECTOR3_USE(b),
		VECTOR3_USE(c), maxt);
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	VECTOR3_DEL(rayNormalizedDirection);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);
	return ret;
}

btScalar RayFromToCaster::RayFromToTriangle(Vector3 rayFrom, Vector3 rayTo,
	Vector3 rayNormalizedDirection, Vector3 a, Vector3 b, Vector3 c)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	VECTOR3_CONV(rayNormalizedDirection);
	VECTOR3_CONV(a);
	VECTOR3_CONV(b);
	VECTOR3_CONV(c);
	btScalar ret = btSoftBody::RayFromToCaster::rayFromToTriangle(VECTOR3_USE(rayFrom),
		VECTOR3_USE(rayTo), VECTOR3_USE(rayNormalizedDirection), VECTOR3_USE(a), VECTOR3_USE(b),
		VECTOR3_USE(c));
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	VECTOR3_DEL(rayNormalizedDirection);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);
	return ret;
}

Face^ RayFromToCaster::Face::get()
{
	return Native->m_face;
}
void RayFromToCaster::Face::set(Face^ value)
{
	Native->m_face = (btSoftBody::Face*)value->_native;
}

btScalar RayFromToCaster::Mint::get()
{
	return Native->m_mint;
}
void RayFromToCaster::Mint::set(btScalar value)
{
	Native->m_mint = value;
}

Vector3 RayFromToCaster::RayFrom::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayFrom);
}
void RayFromToCaster::RayFrom::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayFrom);
}

Vector3 RayFromToCaster::RayNormalizedDirection::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayNormalizedDirection);
}
void RayFromToCaster::RayNormalizedDirection::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayNormalizedDirection);
}

Vector3 RayFromToCaster::RayTo::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayTo);
}
void RayFromToCaster::RayTo::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayTo);
}

int RayFromToCaster::Tests::get()
{
	return Native->m_tests;
}
void RayFromToCaster::Tests::set(int value)
{
	Native->m_tests = value;
}
*/


RigidContact::RigidContact(btSoftBody::RContact* native)
{
	_native = native;
}
/*
RigidContact::~RigidContact()
{
	this->!RigidContact();
}

RigidContact::!RigidContact()
{
	delete _native;
	_native = NULL;
}

RigidContact::RigidContact()
{
	_native = new btSoftBody::RContact();
}
*/
Matrix RigidContact::C0::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_c0);
}
void RigidContact::C0::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_c0);
}

Vector3 RigidContact::C1::get()
{
	return Math::BtVector3ToVector3(&_native->m_c1);
}
void RigidContact::C1::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_c1);
}

btScalar RigidContact::C2::get()
{
	return _native->m_c2;
}
void RigidContact::C2::set(btScalar value)
{
	_native->m_c2 = value;
}

btScalar RigidContact::C3::get()
{
	return _native->m_c3;
}
void RigidContact::C3::set(btScalar value)
{
	_native->m_c3 = value;
}

btScalar RigidContact::C4::get()
{
	return _native->m_c4;
}
void RigidContact::C4::set(btScalar value)
{
	_native->m_c4 = value;
}

BulletSharp::SoftBody::Node^ RigidContact::Node::get()
{
	ReturnCachedObjectGcnewNullable(BulletSharp::SoftBody::Node, _node, _native->m_node);
}
void RigidContact::Node::set(BulletSharp::SoftBody::Node^ value)
{
	_native->m_node = (btSoftBody::Node*)GetUnmanagedNullable(value);
	_node = value;
}

ContactInfo^ RigidContact::ContactInfo::get()
{
	return gcnew BulletSharp::SoftBody::ContactInfo(&_native->m_cti, true);
}


SoftContact::SoftContact(btSoftBody::SContact* native)
{
	_native = native;
}

ScalarArray^ SoftContact::Cfm::get()
{
	if (_cfm == nullptr)
	{
		_cfm = gcnew ScalarArray(_native->m_cfm, 2);
	}
	return _cfm;
}

BulletSharp::SoftBody::Face^ SoftContact::Face::get()
{
	if (_face == nullptr)
	{
		_face = gcnew BulletSharp::SoftBody::Face(_native->m_face);
	}
	return _face;
}
void SoftContact::Face::set(BulletSharp::SoftBody::Face^ value)
{
	_native->m_face = (btSoftBody::Face*)GetUnmanagedNullable(value);
}

btScalar SoftContact::Friction::get()
{
	return _native->m_friction;
}
void SoftContact::Friction::set(btScalar value)
{
	_native->m_friction = value;
}

btScalar SoftContact::Margin::get()
{
	return _native->m_margin;
}
void SoftContact::Margin::set(btScalar value)
{
	_native->m_margin = value;
}

BulletSharp::SoftBody::Node^ SoftContact::Node::get()
{
	ReturnCachedObjectGcnewNullable(BulletSharp::SoftBody::Node, _node, _native->m_node);
}
void SoftContact::Node::set(BulletSharp::SoftBody::Node^ value)
{
	_node = value;
	_native->m_node = (btSoftBody::Node*)GetUnmanagedNullable(value);
}

Vector3 SoftContact::Normal::get()
{
	return Math::BtVector3ToVector3(&_native->m_normal);
}
void SoftContact::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_normal);
}

Vector3 SoftContact::Weights::get()
{
	return Math::BtVector3ToVector3(&_native->m_weights);
}
void SoftContact::Weights::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_weights);
}


/*
SoftBody::sMedium::sMedium(btSoftBody::sMedium* native)
{
	_native = native;
}

SoftBody::sMedium::~sMedium()
{
	this->!sMedium();
}

SoftBody::sMedium::!sMedium()
{
	delete _native;
	_native = NULL;
}

SoftBody::sMedium::sMedium()
{
	_native = new btSoftBody::sMedium();
}

btScalar SoftBody::sMedium::Density::get()
{
	return _native->m_density;
}
void SoftBody::sMedium::Density::set(btScalar value)
{
	_native->m_density = value;
}

btScalar SoftBody::sMedium::Pressure::get()
{
	return _native->m_pressure;
}
void SoftBody::sMedium::Pressure::set(btScalar value)
{
	_native->m_pressure = value;
}

Vector3 SoftBody::sMedium::Velocity::get()
{
	return Math::BtVector3ToVector3(&_native->m_velocity);
}
void SoftBody::sMedium::Velocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_velocity);
}
*/


SolverState::SolverState(btSoftBody::SolverState* native)
{
	_native = native;
}

btScalar SolverState::InverseSdt::get()
{
	return _native->isdt;
}
void SolverState::InverseSdt::set(btScalar value)
{
	_native->isdt = value;
}

btScalar SolverState::RadialMargin::get()
{
	return _native->radmrg;
}
void SolverState::RadialMargin::set(btScalar value)
{
	_native->radmrg = value;
}

btScalar SolverState::Sdt::get()
{
	return _native->sdt;
}
void SolverState::Sdt::set(btScalar value)
{
	_native->sdt = value;
}

btScalar SolverState::UpdateMargin::get()
{
	return _native->updmrg;
}
void SolverState::UpdateMargin::set(btScalar value)
{
	_native->updmrg = value;
}

btScalar SolverState::VelocityMargin::get()
{
	return _native->velmrg;
}
void SolverState::VelocityMargin::set(btScalar value)
{
	_native->velmrg = value;
}


#undef Native
#define Native static_cast<btSoftBody::Tetra*>(_native)

Tetra::Tetra(btSoftBody::Tetra* native)
	: Feature(native)
{
}

Vector3Array^ Tetra::C0::get()
{
	if (_c0 == nullptr)
	{
		_c0 = gcnew Vector3Array(Native->m_c0, 4);
	}
	return _c0;
}

btScalar Tetra::C1::get()
{
	return Native->m_c1;
}
void Tetra::C1::set(btScalar value)
{
	Native->m_c1 = value;
}

btScalar Tetra::C2::get()
{
	return Native->m_c2;
}
void Tetra::C2::set(btScalar value)
{
	Native->m_c2 = value;
}

#ifndef DISABLE_DBVT
DbvtNode^ Tetra::Leaf::get()
{
	ReturnCachedObjectGcnewNullable(DbvtNode, _leaf, Native->m_leaf);
}
void Tetra::Leaf::set(DbvtNode^ value)
{
	Native->m_leaf = GetUnmanagedNullable(value);
	_leaf = value;
}
#endif

NodePtrArray^ Tetra::Nodes::get()
{
	if (_nodes == nullptr)
	{
		_nodes = gcnew NodePtrArray(Native->m_n, 4);
	}
	return _nodes;
}

btScalar Tetra::RestVolume::get()
{
	return Native->m_rv;
}
void Tetra::RestVolume::set(btScalar value)
{
	Native->m_rv = value;
}


#undef Native
#define Native static_cast<btSoftBody*>(_native)

BulletSharp::SoftBody::SoftBody::SoftBody(btSoftBody* native)
	: CollisionObject(native)
{
	_collisionShape = gcnew SoftBodyCollisionShape(static_cast<btConvexShape*>(_native->getCollisionShape()));
	_collisionShape->_preventDelete = true;
	_aJointControls = gcnew List<AJoint::IControl^>();
}

BulletSharp::SoftBody::SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo, array<Vector3>^ x, array<btScalar>^ m)
	: CollisionObject(0)
{
	pin_ptr<Vector3> x_ptr;
	pin_ptr<btScalar> m_ptr;
	int length;

	if (x->Length != 0 && m->Length != 0)
	{
		if (x->Length != m->Length)
			throw gcnew InvalidOperationException("Arrays must have the same length.");
		length = x->Length;
	}
	else if (x->Length == 0 && m->Length == 0)
	{
		length = 0;
	}
	else
	{
		length = (x->Length != 0) ? x->Length : m->Length;
	}

	if (x->Length != 0)
		x_ptr = &x[0];
	else
		x_ptr = nullptr;

	if (m->Length != 0)
		m_ptr = &m[0];
	else
		m_ptr = nullptr;

	UnmanagedPointer = new btSoftBody(worldInfo->_native, length, (btVector3*)x_ptr, m_ptr);

	_collisionShape = gcnew SoftBodyCollisionShape(static_cast<btConvexShape*>(_native->getCollisionShape()));
	_collisionShape->_preventDelete = true;
	_worldInfo = worldInfo;
}

BulletSharp::SoftBody::SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo, Vector3Array^ x, ScalarArray^ m)
	: CollisionObject(0)
{
	int length;

	if (x != nullptr && m != nullptr)
	{
		if (x->Count != m->Count)
			throw gcnew InvalidOperationException("Arrays must have the same length.");
		length = x->Count;
	}
	else if (x == nullptr && m == nullptr)
	{
		length = 0;
	}
	else
	{
		length = (x != nullptr) ? x->Count : m->Count;
	}

	UnmanagedPointer = new btSoftBody(worldInfo->_native, length,
		(btVector3*)GetUnmanagedNullable(x), (btScalar*)GetUnmanagedNullable(m));

	_collisionShape = gcnew SoftBodyCollisionShape(static_cast<btConvexShape*>(_native->getCollisionShape()));
	_collisionShape->_preventDelete = true;
	_worldInfo = worldInfo;
}

BulletSharp::SoftBody::SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo)
	: CollisionObject(new btSoftBody(worldInfo->_native))
{
	_collisionShape = gcnew SoftBodyCollisionShape(static_cast<btConvexShape*>(_native->getCollisionShape()));
	_collisionShape->_preventDelete = true;
	_worldInfo = worldInfo;
}

BulletSharp::SoftBody::SoftBody::~SoftBody()
{
	this->!SoftBody();
}

BulletSharp::SoftBody::SoftBody::!SoftBody()
{
	if (this->IsDisposed)
		return;
	delete _collisionShape;
}

void BulletSharp::SoftBody::SoftBody::AddAeroForceToFace(Vector3 windVelocity, int faceIndex)
{
	VECTOR3_CONV(windVelocity);
	Native->addAeroForceToFace(VECTOR3_USE(windVelocity), faceIndex);
	VECTOR3_DEL(windVelocity);
}

void BulletSharp::SoftBody::SoftBody::AddAeroForceToNode(Vector3 windVelocity, int nodeIndex)
{
	VECTOR3_CONV(windVelocity);
	Native->addAeroForceToNode(VECTOR3_USE(windVelocity), nodeIndex);
	VECTOR3_DEL(windVelocity);
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force)
{
	VECTOR3_CONV(force);
	Native->addForce(VECTOR3_USE(force));
	VECTOR3_DEL(force);
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force, int node)
{
	VECTOR3_CONV(force);
	Native->addForce(VECTOR3_USE(force), node);
	VECTOR3_DEL(force);
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity, int node)
{
	VECTOR3_CONV(velocity);
	Native->addVelocity(VECTOR3_USE(velocity), node);
	VECTOR3_DEL(velocity);
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity)
{
	VECTOR3_CONV(velocity);
	Native->addVelocity(VECTOR3_USE(velocity));
	VECTOR3_DEL(velocity);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, Vector3 localPivot, bool disableCollisionBetweenLinkedBodies,
	btScalar influence)
{
	VECTOR3_CONV(localPivot);
	Native->appendAnchor(node, (btRigidBody*)body->_native, VECTOR3_USE(localPivot),
		disableCollisionBetweenLinkedBodies, influence);
	VECTOR3_DEL(localPivot);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, Vector3 localPivot, bool disableCollisionBetweenLinkedBodies)
{
	VECTOR3_CONV(localPivot);
	Native->appendAnchor(node, (btRigidBody*)body->_native, VECTOR3_USE(localPivot),
		disableCollisionBetweenLinkedBodies);
	VECTOR3_DEL(localPivot);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, Vector3 localPivot)
{
	VECTOR3_CONV(localPivot);
	Native->appendAnchor(node, (btRigidBody*)body->_native, VECTOR3_USE(localPivot));
	VECTOR3_DEL(localPivot);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies,
	btScalar influence)
{
	Native->appendAnchor(node, (btRigidBody*)body->_native, disableCollisionBetweenLinkedBodies,
		influence);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies)
{
	Native->appendAnchor(node, (btRigidBody*)body->_native, disableCollisionBetweenLinkedBodies);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body)
{
	Native->appendAnchor(node, (btRigidBody*)body->_native);
}

void BulletSharp::SoftBody::SoftBody::StoreAngularJointControlRef(AJoint::Specs^ specs)
{
	if (specs->Control != nullptr && specs->Control != AJoint::IControl::Default())
	{
		_aJointControls->Add(specs->Control);
	}
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, Body^ body)
{
	StoreAngularJointControlRef(specs);
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native, *body->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs)
{
	StoreAngularJointControlRef(specs);
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, SoftBody^ body)
{
	StoreAngularJointControlRef(specs);
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native, (btSoftBody*)body->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, Cluster^ body0, Body^ body1)
{
	StoreAngularJointControlRef(specs);
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native, body0->_native,
		*body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int model, Material^ material)
{
	Native->appendFace(model, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int model)
{
	Native->appendFace(model);
}

void BulletSharp::SoftBody::SoftBody::AppendFace()
{
	Native->appendFace();
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int node0, int node1, int node2, Material^ material)
{
	Native->appendFace(node0, node1, node2, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int node0, int node1, int node2)
{
	Native->appendFace(node0, node1, node2);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, SoftBody^ body)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native, (btSoftBody*)body->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, Body^ body)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native, *body->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, Cluster^ body0, Body^ body1)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native, body0->_native,
		*body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1, Material^ material, bool bcheckexist)
{
	Native->appendLink(node0, node1, (btSoftBody::Material*)GetUnmanagedNullable(material), bcheckexist);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1, Material^ material)
{
	Native->appendLink(node0, node1, (btSoftBody::Material*)GetUnmanagedNullable(material));
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1)
{
	Native->appendLink(node0, node1);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int model, Material^ material)
{
	Native->appendLink(model, (btSoftBody::Material*)GetUnmanagedNullable(material));
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int model)
{
	Native->appendLink(model);
}

void BulletSharp::SoftBody::SoftBody::AppendLink()
{
	Native->appendLink();
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1, Material^ material, bool bcheckexist)
{
	Native->appendLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native,
		(btSoftBody::Material*)GetUnmanagedNullable(material), bcheckexist);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1, Material^ material)
{
	Native->appendLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native,
		(btSoftBody::Material*)GetUnmanagedNullable(material));
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1)
{
	Native->appendLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native);
}

BulletSharp::SoftBody::Material^ BulletSharp::SoftBody::SoftBody::AppendMaterial()
{
	return gcnew Material(Native->appendMaterial());
}

void BulletSharp::SoftBody::SoftBody::AppendNode(Vector3 x, btScalar m)
{
	VECTOR3_CONV(x);
	Native->appendNode(VECTOR3_USE(x), m);
	VECTOR3_DEL(x);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Face^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	Native->appendNote(textTemp, VECTOR3_USE(o), (btSoftBody::Face*)feature->_native);
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Link^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	Native->appendNote(textTemp, VECTOR3_USE(o), (btSoftBody::Link*)feature->_native);
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Node^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	Native->appendNote(textTemp, VECTOR3_USE(o), (btSoftBody::Node*)feature->_native);
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1,
	Node^ n2, Node^ n3)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	VECTOR4_CONV(c);
	Native->appendNote(textTemp, VECTOR3_USE(o), VECTOR4_USE(c), (btSoftBody::Node*)n0->_native,
		(btSoftBody::Node*)n1->_native, (btSoftBody::Node*)n2->_native, (btSoftBody::Node*)n3->_native);
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	VECTOR4_DEL(c);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1,
	Node^ n2)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	VECTOR4_CONV(c);
	Native->appendNote(textTemp, VECTOR3_USE(o), VECTOR4_USE(c), (btSoftBody::Node*)n0->_native,
		(btSoftBody::Node*)n1->_native, (btSoftBody::Node*)n2->_native);
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	VECTOR4_DEL(c);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	VECTOR4_CONV(c);
	Native->appendNote(textTemp, VECTOR3_USE(o), VECTOR4_USE(c), (btSoftBody::Node*)n0->_native,
		(btSoftBody::Node*)n1->_native);
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	VECTOR4_DEL(c);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	VECTOR4_CONV(c);
	Native->appendNote(textTemp, VECTOR3_USE(o), VECTOR4_USE(c), (btSoftBody::Node*)n0->_native);
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	VECTOR4_DEL(c);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	VECTOR4_CONV(c);
	Native->appendNote(textTemp, VECTOR3_USE(o), VECTOR4_USE(c));
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	VECTOR4_DEL(c);
}

#pragma managed(push, off)
void SoftBody_AppendNote(btSoftBody* body, const char* text, btVector3* c)
{
	body->appendNote(text, *c);
}
#pragma managed(pop)
void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_CONV(o);
	SoftBody_AppendNote(Native, textTemp, VECTOR3_PTR(o));
	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
}

void BulletSharp::SoftBody::SoftBody::AppendTetra(int model, Material^ material)
{
	Native->appendTetra(model, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendTetra(int node0, int node1, int node2, int node3, Material^ material)
{
	Native->appendTetra(node0, node1, node2, node3, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendTetra(int node0, int node1, int node2, int node3)
{
	Native->appendTetra(node0, node1, node2, node3);
}

void BulletSharp::SoftBody::SoftBody::ApplyClusters(bool drift)
{
	Native->applyClusters(drift);
}

void BulletSharp::SoftBody::SoftBody::ApplyForces()
{
	Native->applyForces();
}

bool BulletSharp::SoftBody::SoftBody::CheckContact(CollisionObjectWrapper^ colObjWrap, Vector3 x, btScalar margin,
	ContactInfo^ cti)
{
	VECTOR3_CONV(x);
	bool ret = Native->checkContact(colObjWrap->_native, VECTOR3_USE(x), margin, *cti->_native);
	VECTOR3_DEL(x);
	return ret;
}

bool BulletSharp::SoftBody::SoftBody::CheckFace(int node0, int node1, int node2)
{
	return Native->checkFace(node0, node1, node2);
}

bool BulletSharp::SoftBody::SoftBody::CheckLink(Node^ node0, Node^ node1)
{
	return Native->checkLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native);
}

bool BulletSharp::SoftBody::SoftBody::CheckLink(int node0, int node1)
{
	return Native->checkLink(node0, node1);
}

void BulletSharp::SoftBody::SoftBody::CleanupClusters()
{
	_aJointControls->Clear();
	Native->cleanupClusters();
}

void BulletSharp::SoftBody::SoftBody::ClusterAImpulse(Cluster^ cluster, Impulse^ impulse)
{
	btSoftBody::clusterAImpulse(cluster->_native, *impulse->_native);
}

#pragma managed(push, off)
void SoftBody_ClusterCOM(btSoftBody* softBody, int cluster, btVector3* com)
{
	*com = softBody->clusterCom(cluster);
}
#pragma managed(pop)
Vector3 BulletSharp::SoftBody::SoftBody::ClusterCom(int cluster)
{
	btVector3* tempClusterCom = ALIGNED_NEW(btVector3);
	SoftBody_ClusterCOM(Native, cluster, tempClusterCom);
	Vector3 com = Math::BtVector3ToVector3(tempClusterCom);
	ALIGNED_FREE(tempClusterCom);
	return com;
}

#pragma managed(push, off)
void SoftBody_ClusterCOM(btSoftBody::Cluster* cluster, btVector3* com)
{
	*com = btSoftBody::clusterCom(cluster);
}
#pragma managed(pop)
Vector3 BulletSharp::SoftBody::SoftBody::ClusterCom(Cluster^ cluster)
{
	btVector3* tempClusterCom = ALIGNED_NEW(btVector3);
	SoftBody_ClusterCOM(cluster->_native, tempClusterCom);
	Vector3 com = Math::BtVector3ToVector3(tempClusterCom);
	ALIGNED_FREE(tempClusterCom);
	return com;
}

void BulletSharp::SoftBody::SoftBody::ClusterDAImpulse(Cluster^ cluster, Vector3 impulse)
{
	VECTOR3_CONV(impulse);
	btSoftBody::clusterDAImpulse(cluster->_native, VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void BulletSharp::SoftBody::SoftBody::ClusterDCImpulse(Cluster^ cluster, Vector3 impulse)
{
	VECTOR3_CONV(impulse);
	btSoftBody::clusterDCImpulse(cluster->_native, VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void BulletSharp::SoftBody::SoftBody::ClusterDImpulse(Cluster^ cluster, Vector3 rPos, Vector3 impulse)
{
	VECTOR3_CONV(rPos);
	VECTOR3_CONV(impulse);
	btSoftBody::clusterDImpulse(cluster->_native, VECTOR3_USE(rPos), VECTOR3_USE(impulse));
	VECTOR3_DEL(rPos);
	VECTOR3_DEL(impulse);
}

void BulletSharp::SoftBody::SoftBody::ClusterImpulse(Cluster^ cluster, Vector3 rPos, Impulse^ impulse)
{
	VECTOR3_CONV(rPos);
	btSoftBody::clusterImpulse(cluster->_native, VECTOR3_USE(rPos), *impulse->_native);
	VECTOR3_DEL(rPos);
}

void BulletSharp::SoftBody::SoftBody::ClusterVAImpulse(Cluster^ cluster, Vector3 impulse)
{
	VECTOR3_CONV(impulse);
	btSoftBody::clusterVAImpulse(cluster->_native, VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

#pragma managed(push, off)
void SoftBody_ClusterVelocity(btSoftBody::Cluster* cluster, btVector3* rPos, btVector3* velocity)
{
	*velocity = btSoftBody::clusterVelocity(cluster, *rPos);
}
#pragma managed(pop)
Vector3 BulletSharp::SoftBody::SoftBody::ClusterVelocity(Cluster^ cluster, Vector3 rPos)
{
	btVector3* tempVelocity = ALIGNED_NEW(btVector3);
	VECTOR3_CONV(rPos);
	SoftBody_ClusterVelocity(cluster->_native, VECTOR3_PTR(rPos), tempVelocity);
	VECTOR3_DEL(rPos);
	Vector3 velocity = Math::BtVector3ToVector3(tempVelocity);
	ALIGNED_FREE(tempVelocity);
	return velocity;
}

void BulletSharp::SoftBody::SoftBody::ClusterVImpulse(Cluster^ cluster, Vector3 rPos, Vector3 impulse)
{
	VECTOR3_CONV(rPos);
	VECTOR3_CONV(impulse);
	btSoftBody::clusterVImpulse(cluster->_native, VECTOR3_USE(rPos), VECTOR3_USE(impulse));
	VECTOR3_DEL(rPos);
	VECTOR3_DEL(impulse);
}

bool BulletSharp::SoftBody::SoftBody::CutLink(int node0, int node1, btScalar position)
{
	return Native->cutLink(node0, node1, position);
}

bool BulletSharp::SoftBody::SoftBody::CutLink(Node^ node0, Node^ node1, btScalar position)
{
	return Native->cutLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native,
		position);
}

void BulletSharp::SoftBody::SoftBody::DampClusters()
{
	Native->dampClusters();
}

void BulletSharp::SoftBody::SoftBody::DefaultCollisionHandler(CollisionObjectWrapper^ pcoWrap)
{
	Native->defaultCollisionHandler(pcoWrap->_native);
}

void BulletSharp::SoftBody::SoftBody::DefaultCollisionHandler(SoftBody^ psb)
{
	Native->defaultCollisionHandler((btSoftBody*)psb->_native);
}

#pragma managed(push, off)
void SoftBody_EvaluateCom(btSoftBody* softBody, btVector3* result)
{
	*result = softBody->evaluateCom();
}
#pragma managed(pop)

Vector3 BulletSharp::SoftBody::SoftBody::EvaluateCom()
{
	btVector3* result = ALIGNED_NEW(btVector3);
	SoftBody_EvaluateCom(Native, result);
	Vector3 ret = Math::BtVector3ToVector3(result);
	ALIGNED_FREE(result);
	return ret;
}

int BulletSharp::SoftBody::SoftBody::GenerateBendingConstraints(int distance, Material^ material)
{
	return Native->generateBendingConstraints(distance, (btSoftBody::Material*)material->_native);
}

int BulletSharp::SoftBody::SoftBody::GenerateBendingConstraints(int distance)
{
	return Native->generateBendingConstraints(distance);
}

int BulletSharp::SoftBody::SoftBody::GenerateClusters(int k, int maxIterations)
{
	return Native->generateClusters(k, maxIterations);
}

int BulletSharp::SoftBody::SoftBody::GenerateClusters(int k)
{
	return Native->generateClusters(k);
}

void BulletSharp::SoftBody::SoftBody::GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);

	Native->getAabb(*aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

int BulletSharp::SoftBody::SoftBody::GetFaceVertexData([Out] array<Vector3>^% vertices)
{
	btAlignedObjectArray<btSoftBody::Face>* faceArray = &Native->m_faces;
	int faceCount = faceArray->size();
	if (faceCount == 0) {
		return 0;
	}

	int vertexCount = faceCount * 3;

	if (vertices == nullptr || vertices->Length != vertexCount) {
		vertices = gcnew array<Vector3>(vertexCount);
	}

	int i, j;
	pin_ptr<Vector3> vPtr = &vertices[0];
	for (i = 0; i < faceCount; i++) {
		for (j = 0; j < 3; j++) {
			btSoftBody::Node* n = faceArray->at(i).m_n[j];
			Math::BtVector3ToVector3(&n->m_x, *vPtr++);
		}
	}

	return vertexCount;
}

int BulletSharp::SoftBody::SoftBody::GetFaceVertexNormalData([Out] array<Vector3>^% data)
{
	btAlignedObjectArray<btSoftBody::Face>* faceArray = &Native->m_faces;
	int faceCount = faceArray->size();
	if (faceCount == 0) {
		return 0;
	}

	int vertexCount = faceCount * 3;
	int vertexNormalCount = vertexCount * 2;

	if (data == nullptr || data->Length != vertexNormalCount) {
		data = gcnew array<Vector3>(vertexNormalCount);
	}

	int i, j;
	pin_ptr<Vector3> vPtr = &data[0];
	for (i = 0; i < faceCount; i++) {
		for (j = 0; j < 3; j++) {
			btSoftBody::Node* n = faceArray->at(i).m_n[j];
			Math::BtVector3ToVector3(&n->m_x, *vPtr++);
			Math::BtVector3ToVector3(&n->m_n, *vPtr++);
		}
	}

	return vertexCount;
}

int BulletSharp::SoftBody::SoftBody::GetFaceVertexNormalData([Out] array<Vector3>^% vertices, [Out] array<Vector3>^% normals)
{
	btAlignedObjectArray<btSoftBody::Face>* faceArray = &Native->m_faces;
	int faceCount = faceArray->size();
	if (faceCount == 0) {
		return 0;
	}

	int vertexCount = faceCount * 3;

	if (vertices == nullptr || vertices->Length != vertexCount) {
		vertices = gcnew array<Vector3>(vertexCount);
	}
	if (normals == nullptr || normals->Length != vertexCount) {
		normals = gcnew array<Vector3>(vertexCount);
	}

	int i, j;
	pin_ptr<Vector3> vPtr = &vertices[0];
	pin_ptr<Vector3> nPtr = &normals[0];
	for (i = 0; i < faceCount; i++) {
		for (j = 0; j < 3; j++) {
			btSoftBody::Node* n = faceArray->at(i).m_n[j];
			Math::BtVector3ToVector3(&n->m_x, *vPtr++);
			Math::BtVector3ToVector3(&n->m_n, *nPtr++);
		}
	}

	return vertexCount;
}

int BulletSharp::SoftBody::SoftBody::GetLinkVertexData([Out] array<Vector3>^% vertices)
{
	btAlignedObjectArray<btSoftBody::Link>* linkArray = &Native->m_links;
	int linkCount = linkArray->size();
	if (linkCount == 0) {
		return 0;
	}

	int vertexCount = linkCount * 2;

	if (vertices == nullptr || vertices->Length != vertexCount) {
		vertices = gcnew array<Vector3>(vertexCount);
	}

	int i;
	pin_ptr<Vector3> vPtr = &vertices[0];
	for (i = 0; i < linkCount; i++) {
		btSoftBody::Link* l = &linkArray->at(i);
		Math::BtVector3ToVector3(&l->m_n[0]->m_x, *vPtr++);
		Math::BtVector3ToVector3(&l->m_n[1]->m_x, *vPtr++);
	}

	return vertexCount;
}

int BulletSharp::SoftBody::SoftBody::GetLinkVertexNormalData([Out] array<Vector3>^% data)
{
	btAlignedObjectArray<btSoftBody::Link>* linkArray = &Native->m_links;
	int linkCount = linkArray->size();
	if (linkCount == 0) {
		return 0;
	}

	int vertexCount = linkCount * 2;
	int vertexNormalCount = vertexCount * 2;

	if (data == nullptr || data->Length != vertexNormalCount) {
		data = gcnew array<Vector3>(vertexNormalCount);
	}

	int i;
	pin_ptr<Vector3> vPtr = &data[0];
	for (i = 0; i < linkCount; i++) {
		btSoftBody::Link* l = &linkArray->at(i);
		Math::BtVector3ToVector3(&l->m_n[0]->m_x, *vPtr);
		vPtr += 2;
		Math::BtVector3ToVector3(&l->m_n[1]->m_x, *vPtr);
		vPtr += 2;
	}

	return vertexCount;
}

btScalar BulletSharp::SoftBody::SoftBody::GetMass(int node)
{
	return Native->getMass(node);
}
/*
psolver_t BulletSharp::SoftBody::SoftBody::GetSolver(btSoftBody::ePSolver::_ solver)
{
	return btSoftBody::getSolver(solver->_native);
}

vsolver_t BulletSharp::SoftBody::SoftBody::GetSolver(btSoftBody::eVSolver::_ solver)
{
	return btSoftBody::getSolver(solver->_native);
}
*/
int BulletSharp::SoftBody::SoftBody::GetTetraVertexData([Out] array<Vector3>^% vertices)
{
	btAlignedObjectArray<btSoftBody::Tetra>* tetraArray = &Native->m_tetras;
	int tetraCount = tetraArray->size();
	if (tetraCount == 0) {
		return 0;
	}

	int vertexCount = tetraCount * 12;

	if (vertices == nullptr || vertices->Length != vertexCount) {
		vertices = gcnew array<Vector3>(vertexCount);
	}

	int i;
	pin_ptr<Vector3> vPtr = &vertices[0];
	Vector3 v0, v1, v2, v3;
	for (i = 0; i < tetraCount; i++) {
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[0]->m_x, v0);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[1]->m_x, v1);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[2]->m_x, v2);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[3]->m_x, v3);

		*vPtr++ = v0;
		*vPtr++ = v1;
		*vPtr++ = v2;

		*vPtr++ = v0;
		*vPtr++ = v1;
		*vPtr++ = v3;

		*vPtr++ = v1;
		*vPtr++ = v2;
		*vPtr++ = v3;

		*vPtr++ = v2;
		*vPtr++ = v0;
		*vPtr++ = v3;
	}

	return vertexCount;
}

int BulletSharp::SoftBody::SoftBody::GetTetraVertexNormalData([Out] array<Vector3>^% data)
{
	btAlignedObjectArray<btSoftBody::Tetra>* tetraArray = &Native->m_tetras;
	int tetraCount = tetraArray->size();
	if (tetraCount == 0) {
		return 0;
	}

	int vertexCount = tetraCount * 12;
	int vertexNormalCount = vertexCount * 2;

	if (data == nullptr || data->Length != vertexNormalCount) {
		data = gcnew array<Vector3>(vertexNormalCount);
	}

	int i;
	pin_ptr<Vector3> vPtr = &data[0];
	Vector3 v0, v1, v2, v3;
	Vector3 v10, v02, normal;
	for (i = 0; i < tetraCount; i++) {
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[0]->m_x, v0);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[1]->m_x, v1);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[2]->m_x, v2);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[3]->m_x, v3);
		v10 = v1 - v0;
		v02 = v0 - v2;

		Vector3_Cross(v10, v02, normal);
		*vPtr++ = v0;
		*vPtr++ = normal;
		*vPtr++ = v1;
		*vPtr++ = normal;
		*vPtr++ = v2;
		*vPtr++ = normal;

		Vector3_Cross(v10, v3 - v0, normal);
		*vPtr++ = v0;
		*vPtr++ = normal;
		*vPtr++ = v1;
		*vPtr++ = normal;
		*vPtr++ = v3;
		*vPtr++ = normal;

		Vector3_Cross(v2 - v1, v3 - v1, normal);
		*vPtr++ = v1;
		*vPtr++ = normal;
		*vPtr++ = v2;
		*vPtr++ = normal;
		*vPtr++ = v3;
		*vPtr++ = normal;

		Vector3_Cross(v02, v3 - v2, normal);
		*vPtr++ = v2;
		*vPtr++ = normal;
		*vPtr++ = v0;
		*vPtr++ = normal;
		*vPtr++ = v3;
		*vPtr++ = normal;
	}

	return vertexCount;
}

int BulletSharp::SoftBody::SoftBody::GetTetraVertexNormalData([Out] array<Vector3>^% vertices, [Out] array<Vector3>^% normals)
{
	btAlignedObjectArray<btSoftBody::Tetra>* tetraArray = &Native->m_tetras;
	int tetraCount = tetraArray->size();
	if (tetraCount == 0) {
		return 0;
	}

	int vertexCount = tetraCount * 12;

	if (vertices == nullptr || vertices->Length != vertexCount) {
		vertices = gcnew array<Vector3>(vertexCount);
	}
	if (normals == nullptr || normals->Length != vertexCount) {
		normals = gcnew array<Vector3>(vertexCount);
	}

	int i;
	pin_ptr<Vector3> vPtr = &vertices[0];
	pin_ptr<Vector3> nPtr = &normals[0];
	Vector3 v0, v1, v2, v3;
	Vector3 v10, v02, normal;
	for (i = 0; i < tetraCount; i++) {
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[0]->m_x, v0);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[1]->m_x, v1);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[2]->m_x, v2);
		Math::BtVector3ToVector3(&tetraArray->at(i).m_n[3]->m_x, v3);
		v10 = v1 - v0;
		v02 = v0 - v2;

		Vector3_Cross(v10, v02, normal);
		*vPtr++ = v0;
		*nPtr++ = normal;
		*vPtr++ = v1;
		*nPtr++ = normal;
		*vPtr++ = v2;
		*nPtr++ = normal;

		Vector3_Cross(v10, v3 - v0, normal);
		*vPtr++ = v0;
		*nPtr++ = normal;
		*vPtr++ = v1;
		*nPtr++ = normal;
		*vPtr++ = v3;
		*nPtr++ = normal;

		Vector3_Cross(v2 - v1, v3 - v1, normal);
		*vPtr++ = v1;
		*nPtr++ = normal;
		*vPtr++ = v2;
		*nPtr++ = normal;
		*vPtr++ = v3;
		*nPtr++ = normal;

		Vector3_Cross(v02, v3 - v2, normal);
		*vPtr++ = v2;
		*nPtr++ = normal;
		*vPtr++ = v0;
		*nPtr++ = normal;
		*vPtr++ = v3;
		*nPtr++ = normal;
	}

	return vertexCount;
}

int BulletSharp::SoftBody::SoftBody::GetVertexNormalData([Out] array<Vector3>^% data)
{
	if (Native->m_faces.size()) {
		return GetFaceVertexNormalData(data);
	} else if (Native->m_tetras.size()) {
		return GetTetraVertexNormalData(data);
	}
	return GetLinkVertexNormalData(data);
}

int BulletSharp::SoftBody::SoftBody::GetVertexNormalData([Out] array<Vector3>^% vertices, [Out] array<Vector3>^% normals)
{
	if (Native->m_faces.size()) {
		return GetFaceVertexNormalData(vertices, normals);
	} else if (Native->m_tetras.size()) {
		return GetTetraVertexNormalData(vertices, normals);
	}
	return GetLinkVertexData(vertices);
}
/*
void BulletSharp::SoftBody::SoftBody::IndicesToPointers(array<int>^ map)
{
	Native->indicesToPointers(map->_native);
}
*/
void BulletSharp::SoftBody::SoftBody::IndicesToPointers()
{
	Native->indicesToPointers();
}

void BulletSharp::SoftBody::SoftBody::InitDefaults()
{
	Native->initDefaults();
}

void BulletSharp::SoftBody::SoftBody::InitializeClusters()
{
	Native->initializeClusters();
}

void BulletSharp::SoftBody::SoftBody::InitializeFaceTree()
{
	Native->initializeFaceTree();
}

void BulletSharp::SoftBody::SoftBody::IntegrateMotion()
{
	Native->integrateMotion();
}

void BulletSharp::SoftBody::SoftBody::PointersToIndices()
{
	Native->pointersToIndices();
}

void BulletSharp::SoftBody::SoftBody::PredictMotion(btScalar deltaTime)
{
	Native->predictMotion(deltaTime);
}

void BulletSharp::SoftBody::SoftBody::PrepareClusters(int iterations)
{
	Native->prepareClusters(iterations);
}

void BulletSharp::SoftBody::SoftBody::PSolveAnchors(SoftBody^ psb, btScalar kst, btScalar ti)
{
	btSoftBody::PSolve_Anchors((btSoftBody*)psb->_native, kst, ti);
}

void BulletSharp::SoftBody::SoftBody::PSolveLinks(SoftBody^ psb, btScalar kst, btScalar ti)
{
	btSoftBody::PSolve_Links((btSoftBody*)psb->_native, kst, ti);
}

void BulletSharp::SoftBody::SoftBody::PSolveRContacts(SoftBody^ psb, btScalar kst, btScalar ti)
{
	btSoftBody::PSolve_RContacts((btSoftBody*)psb->_native, kst, ti);
}

void BulletSharp::SoftBody::SoftBody::PSolveSContacts(SoftBody^ psb, btScalar __unnamed1, btScalar ti)
{
	btSoftBody::PSolve_SContacts((btSoftBody*)psb->_native, __unnamed1, ti);
}

void BulletSharp::SoftBody::SoftBody::RandomizeConstraints()
{
	Native->randomizeConstraints();
}

int BulletSharp::SoftBody::SoftBody::RayTest(Vector3 rayFrom, Vector3 rayTo, [Out] btScalar% mint, [Out] EFeature% feature,
	[Out] int% index, bool countOnly)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	btScalar mintTemp = mint;
	btSoftBody::eFeature::_ featureTemp;
	int indexTemp;
	int ret = Native->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), mintTemp,
		featureTemp, indexTemp, countOnly);
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	mint = mintTemp;
	feature = (EFeature)featureTemp;
	index = indexTemp;
	return ret;
}

bool BulletSharp::SoftBody::SoftBody::RayTest(Vector3 rayFrom, Vector3 rayTo, SRayCast^ results)
{
	btSoftBody::sRayCast* rayCast = new btSoftBody::sRayCast();
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	bool ret = Native->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *rayCast);
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	results->Body = this;
	results->Feature = (EFeature)rayCast->feature;
	results->Fraction = rayCast->fraction;
	results->Index = rayCast->index;
	delete rayCast;
	return ret;
}

void BulletSharp::SoftBody::SoftBody::Refine(ImplicitFn^ ifn, btScalar accurary, bool cut)
{
	Native->refine(ifn->_native, accurary, cut);
}

void BulletSharp::SoftBody::SoftBody::ReleaseCluster(int index)
{
	Native->releaseCluster(index);
}

void BulletSharp::SoftBody::SoftBody::ReleaseClusters()
{
	Native->releaseClusters();
}

void BulletSharp::SoftBody::SoftBody::ResetLinkRestLengths()
{
	Native->resetLinkRestLengths();
}

void BulletSharp::SoftBody::SoftBody::Rotate(Quaternion rotation)
{
	QUATERNION_CONV(rotation);
	Native->rotate(QUATERNION_USE(rotation));
	QUATERNION_DEL(rotation);
}

void BulletSharp::SoftBody::SoftBody::Scale(Vector3 scale)
{
	VECTOR3_CONV(scale);
	Native->scale(VECTOR3_USE(scale));
	VECTOR3_DEL(scale);
}

void BulletSharp::SoftBody::SoftBody::SetMass(int node, btScalar mass)
{
	Native->setMass(node, mass);
}

void BulletSharp::SoftBody::SoftBody::SetPose(bool volume, bool frame)
{
	Native->setPose(volume, frame);
}

void BulletSharp::SoftBody::SoftBody::SetSolver(ESolverPresets preset)
{
	Native->setSolver((btSoftBody::eSolverPresets::_)preset);
}

void BulletSharp::SoftBody::SoftBody::SetTotalDensity(btScalar density)
{
	Native->setTotalDensity(density);
}

void BulletSharp::SoftBody::SoftBody::SetTotalMass(btScalar mass, bool fromFaces)
{
	Native->setTotalMass(mass, fromFaces);
}

void BulletSharp::SoftBody::SoftBody::SetTotalMass(btScalar mass)
{
	Native->setTotalMass(mass);
}

void BulletSharp::SoftBody::SoftBody::SetVelocity(Vector3 velocity)
{
	VECTOR3_CONV(velocity);
	Native->setVelocity(VECTOR3_USE(velocity));
	VECTOR3_DEL(velocity);
}

void BulletSharp::SoftBody::SoftBody::SetVolumeDensity(btScalar density)
{
	Native->setVolumeDensity(density);
}

void BulletSharp::SoftBody::SoftBody::SetVolumeMass(btScalar mass)
{
	Native->setVolumeMass(mass);
}

void BulletSharp::SoftBody::SoftBody::SolveClusters(AlignedSoftBodyArray^ bodies)
{
	btSoftBody::solveClusters(*(btSoftBody::tSoftBodyArray*)bodies->_native);
}

void BulletSharp::SoftBody::SoftBody::SolveClusters(btScalar sor)
{
	Native->solveClusters(sor);
}

void BulletSharp::SoftBody::SoftBody::SolveCommonConstraints(array<SoftBody^>^ bodies, int iterations)
{
	int len = bodies->Length;
	btSoftBody** bodiesTemp = new btSoftBody*[len];

	int i;
	for (i=0; i<len; i++)
		bodiesTemp[i] = (btSoftBody*)bodies[i]->_native;

	btSoftBody::solveCommonConstraints(bodiesTemp, len, iterations);

	delete[] bodiesTemp;
}

void BulletSharp::SoftBody::SoftBody::SolveConstraints()
{
	Native->solveConstraints();
}

void BulletSharp::SoftBody::SoftBody::StaticSolve(int iterations)
{
	Native->staticSolve(iterations);
}

void BulletSharp::SoftBody::SoftBody::Transform(Matrix transform)
{
	TRANSFORM_CONV(transform);
	Native->transform(TRANSFORM_USE(transform));
	TRANSFORM_DEL(transform);
}

void BulletSharp::SoftBody::SoftBody::Translate(Vector3 translation)
{
	VECTOR3_CONV(translation);
	Native->translate(VECTOR3_USE(translation));
	VECTOR3_DEL(translation);
}

void BulletSharp::SoftBody::SoftBody::Translate(btScalar x, btScalar y, btScalar z)
{
	Translate(Vector3(x,y,z));
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::SoftBody::Upcast(CollisionObject^ colObj)
{
	btSoftBody* body = btSoftBody::upcast(colObj->_native);
	return (BulletSharp::SoftBody::SoftBody^)CollisionObject::GetManaged(body);
}

void BulletSharp::SoftBody::SoftBody::UpdateArea(bool averageArea)
{
	Native->updateArea(averageArea);
}

void BulletSharp::SoftBody::SoftBody::UpdateArea()
{
	Native->updateArea();
}

void BulletSharp::SoftBody::SoftBody::UpdateBounds()
{
	Native->updateBounds();
}

void BulletSharp::SoftBody::SoftBody::UpdateClusters()
{
	Native->updateClusters();
}

void BulletSharp::SoftBody::SoftBody::UpdateConstants()
{
	Native->updateConstants();
}

void BulletSharp::SoftBody::SoftBody::UpdateLinkConstants()
{
	Native->updateLinkConstants();
}

void BulletSharp::SoftBody::SoftBody::UpdateNormals()
{
	Native->updateNormals();
}

void BulletSharp::SoftBody::SoftBody::UpdatePose()
{
	Native->updatePose();
}

void BulletSharp::SoftBody::SoftBody::VSolveLinks(SoftBody^ psb, btScalar kst)
{
	btSoftBody::VSolve_Links((btSoftBody*)psb->_native, kst);
}

AlignedAnchorArray^ BulletSharp::SoftBody::SoftBody::Anchors::get()
{
	if (_anchors == nullptr)
	{
		_anchors = gcnew AlignedAnchorArray(&Native->m_anchors);
	}
	return _anchors;
}

Vector3Array^ BulletSharp::SoftBody::SoftBody::Bounds::get()
{
	if (_bounds == nullptr)
	{
		_bounds = gcnew Vector3Array(Native->m_bounds, 2);
	}
	return _bounds;
}

Config^ BulletSharp::SoftBody::SoftBody::Cfg::get()
{
	if (_config == nullptr)
	{
		_config = gcnew Config(&Native->m_cfg);
	}
	return _config;
}
/*
AlignedObjectArray BulletSharp::SoftBody::SoftBody::ClusterConnectivity::get()
{
	return Native->m_clusterConnectivity;
}
*/
#ifndef DISABLE_DBVT
Dbvt^ BulletSharp::SoftBody::SoftBody::ClusterDbvt::get()
{
	if (_clusterDbvt == nullptr)
	{
		_clusterDbvt = gcnew Dbvt(&Native->m_cdbvt, true);
	}
	return _clusterDbvt;
}
#endif

int BulletSharp::SoftBody::SoftBody::ClusterCount::get()
{
	return Native->clusterCount();
}

AlignedClusterArray^ BulletSharp::SoftBody::SoftBody::Clusters::get()
{
	if (_clusters == nullptr)
	{
		_clusters = gcnew AlignedClusterArray(&Native->m_clusters);
	}
	return _clusters;
}

AlignedCollisionObjectArray^ BulletSharp::SoftBody::SoftBody::CollisionDisabledObjects::get()
{
	if (_collisionDisabledObjects == nullptr)
	{
		_collisionDisabledObjects = gcnew AlignedCollisionObjectArray((btCollisionObjectArray*)&Native->m_collisionDisabledObjects);
	}
	return _collisionDisabledObjects;
}

AlignedFaceArray^ BulletSharp::SoftBody::SoftBody::Faces::get()
{
	if (_faces == nullptr)
	{
		_faces = gcnew AlignedFaceArray(&Native->m_faces);
	}
	return _faces;
}

#ifndef DISABLE_DBVT
Dbvt^ BulletSharp::SoftBody::SoftBody::FaceDbvt::get()
{
	if (_faceDbvt == nullptr)
	{
		_faceDbvt = gcnew Dbvt(&Native->m_fdbvt, true);
	}
	return _faceDbvt;
}
#endif

Matrix BulletSharp::SoftBody::SoftBody::InitialWorldTransform::get()
{
	return Math::BtTransformToMatrix(&Native->m_initialWorldTransform);
}
void BulletSharp::SoftBody::SoftBody::InitialWorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &Native->m_initialWorldTransform);
}

AlignedJointArray^ BulletSharp::SoftBody::SoftBody::Joints::get()
{
	if (_joints == nullptr)
	{
		_joints = gcnew AlignedJointArray(&Native->m_joints);
	}
	return _joints;
}

AlignedLinkArray^ BulletSharp::SoftBody::SoftBody::Links::get()
{
	if (_links == nullptr)
	{
		_links = gcnew AlignedLinkArray(&Native->m_links);
	}
	return _links;
}

AlignedMaterialArray^ BulletSharp::SoftBody::SoftBody::Materials::get()
{
	if (_materials == nullptr)
	{
		_materials = gcnew AlignedMaterialArray(&Native->m_materials);
	}
	return _materials;
}

#ifndef DISABLE_DBVT
Dbvt^ BulletSharp::SoftBody::SoftBody::NodeDbvt::get()
{
	if (_clusterDbvt == nullptr)
	{
		_clusterDbvt = gcnew Dbvt(&Native->m_ndbvt, true);
	}
	return _clusterDbvt;
}
#endif

BulletSharp::SoftBody::AlignedNodeArray^ BulletSharp::SoftBody::SoftBody::Nodes::get()
{
	if (_nodes == nullptr)
	{
		_nodes = gcnew BulletSharp::SoftBody::AlignedNodeArray(&Native->m_nodes);
	}
	return _nodes;
}

BulletSharp::SoftBody::AlignedNoteArray^ BulletSharp::SoftBody::SoftBody::Notes::get()
{
	if (_notes == nullptr)
	{
		_notes = gcnew BulletSharp::SoftBody::AlignedNoteArray(&Native->m_notes);
	}
	return _notes;
}

BulletSharp::SoftBody::Pose^ BulletSharp::SoftBody::SoftBody::Pose::get()
{
	if (_pose == nullptr)
	{
		_pose = gcnew BulletSharp::SoftBody::Pose(&Native->m_pose);
	}
	return _pose;
}

btScalar BulletSharp::SoftBody::SoftBody::RestLengthScale::get()
{
	return Native->getRestLengthScale();
}
void BulletSharp::SoftBody::SoftBody::RestLengthScale::set(btScalar restLength)
{
	Native->setRestLengthScale(restLength);
}

BulletSharp::SoftBody::AlignedRigidContactArray^ BulletSharp::SoftBody::SoftBody::RigidContacts::get()
{
	if (_rigidContacts == nullptr)
	{
		_rigidContacts = gcnew AlignedRigidContactArray(&Native->m_rcontacts);
	}
	return _rigidContacts;
}

SoftBodySolver^ BulletSharp::SoftBody::SoftBody::SoftBodySolver::get()
{
	return _softBodySolver;
}
void BulletSharp::SoftBody::SoftBody::SoftBodySolver::set(BulletSharp::SoftBody::SoftBodySolver^ softBodySolver)
{
	Native->setSoftBodySolver(GetUnmanagedNullable(softBodySolver));
	_softBodySolver = softBodySolver;
}

BulletSharp::SoftBody::AlignedSoftContactArray^ BulletSharp::SoftBody::SoftBody::SoftContacts::get()
{
	if (_softContacts == nullptr)
	{
		_softContacts = gcnew AlignedSoftContactArray(&Native->m_scontacts);
	}
	return _softContacts;
}

SolverState^ BulletSharp::SoftBody::SoftBody::SolverState::get()
{
	if (_solverState == nullptr)
	{
		_solverState = gcnew BulletSharp::SoftBody::SolverState(&Native->m_sst);
	}
	return _solverState;
}

Object^ BulletSharp::SoftBody::SoftBody::Tag::get()
{
	return _tag;
}
void BulletSharp::SoftBody::SoftBody::Tag::set(Object^ value)
{
	_tag = value;
}

BulletSharp::SoftBody::AlignedTetraArray^ BulletSharp::SoftBody::SoftBody::Tetras::get()
{
	if (_tetras == nullptr)
	{
		_tetras = gcnew BulletSharp::SoftBody::AlignedTetraArray(&Native->m_tetras);
	}
	return _tetras;
}

btScalar BulletSharp::SoftBody::SoftBody::TimeAccumulator::get()
{
	return Native->m_timeacc;
}
void BulletSharp::SoftBody::SoftBody::TimeAccumulator::set(btScalar value)
{
	Native->m_timeacc = value;
}

btScalar BulletSharp::SoftBody::SoftBody::TotalMass::get()
{
	return Native->getTotalMass();
}
void BulletSharp::SoftBody::SoftBody::TotalMass::set(btScalar value)
{
	Native->setTotalMass(value);
}

bool BulletSharp::SoftBody::SoftBody::UpdateRuntimeConstants::get()
{
	return Native->m_bUpdateRtCst;
}
void BulletSharp::SoftBody::SoftBody::UpdateRuntimeConstants::set(bool value)
{
	Native->m_bUpdateRtCst = value;
}

AlignedIntArray^ BulletSharp::SoftBody::SoftBody::UserIndexMapping::get()
{
	if (_userIndexMapping == nullptr)
	{
		_userIndexMapping = gcnew AlignedIntArray(&Native->m_userIndexMapping);
	}
	return _userIndexMapping;
}

Vector3 BulletSharp::SoftBody::SoftBody::WindVelocity::get()
{
	return Math::BtVector3ToVector3(&Native->getWindVelocity());
}
void BulletSharp::SoftBody::SoftBody::WindVelocity::set(Vector3 velocity)
{
	Math::Vector3ToBtVector3(velocity, &Native->m_windVelocity);
}

btScalar BulletSharp::SoftBody::SoftBody::Volume::get()
{
	return Native->getVolume();
}

SoftBodyWorldInfo^ BulletSharp::SoftBody::SoftBody::WorldInfo::get()
{
	return _worldInfo;
}
void BulletSharp::SoftBody::SoftBody::WorldInfo::set(SoftBodyWorldInfo^ value)
{
	Native->m_worldInfo = value->_native;
	_worldInfo = value;
}

#endif
