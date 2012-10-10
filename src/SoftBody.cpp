#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "Collections.h"
#include "CollisionObjectWrapper.h"
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

#pragma managed(push, off)
btSoftBodyWorldInfo* SoftBodyWorldInfo_New()
{
	btSoftBodyWorldInfo* info = new btSoftBodyWorldInfo();
	memset(info, 0, sizeof(btSoftBodyWorldInfo));
	return info;
}
#pragma managed(pop)

SoftBodyWorldInfo::SoftBodyWorldInfo(btSoftBodyWorldInfo* info)
{
	_native = info;
}

SoftBodyWorldInfo::!SoftBodyWorldInfo()
{
	delete _native;
	_native = 0;
}

SoftBodyWorldInfo::~SoftBodyWorldInfo()
{
	this->!SoftBodyWorldInfo();
}

SoftBodyWorldInfo::SoftBodyWorldInfo()
{
	_native = SoftBodyWorldInfo_New();
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
	return BroadphaseInterface::GetManaged(_native->m_broadphase);
}
void SoftBodyWorldInfo::Broadphase::set(BroadphaseInterface^ value)
{
	_native->m_broadphase = GetUnmanagedNullable(value);
}

Dispatcher^ SoftBodyWorldInfo::Dispatcher::get()
{
	if (_native->m_dispatcher == nullptr)
		return nullptr;
	return gcnew BulletSharp::Dispatcher(_native->m_dispatcher);
}
void SoftBodyWorldInfo::Dispatcher::set(BulletSharp::Dispatcher^ value)
{
	_native->m_dispatcher = GetUnmanagedNullable(value);
}

Vector3 SoftBodyWorldInfo::Gravity::get()
{
	return Math::BtVector3ToVector3(&_native->m_gravity);
}
void SoftBodyWorldInfo::Gravity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_gravity);
}

SparseSdf^ SoftBodyWorldInfo::SparseSdf::get()
{
	return gcnew BulletSharp::SparseSdf(&_native->m_sparsesdf);
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


Anchor::Anchor(btSoftBody::Anchor* anchor)
{
	_native = anchor;
}

Anchor::Anchor()
{
	_native = new btSoftBody::Anchor();
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

Vector3 Anchor::Local::get()
{
	return Math::BtVector3ToVector3(&_native->m_local);
}
void Anchor::Local::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_local);
}

btScalar Anchor::Influence::get()
{
	return _native->m_influence;
}
void Anchor::Influence::set(btScalar value)
{
	_native->m_influence = value;
}

BulletSharp::SoftBody::Node^ Anchor::Node::get()
{
	if (_native->m_node == nullptr)
		return nullptr;
	return gcnew BulletSharp::SoftBody::Node(_native->m_node);
}
void Anchor::Node::set(BulletSharp::SoftBody::Node^ value)
{
	_native->m_node = (btSoftBody::Node*)GetUnmanagedNullable(value);
}


Body::Body(btSoftBody::Body* body)
{
	_native = body;
}

Body::Body()
{
	_native = new btSoftBody::Body();
}

Body::Body(Cluster^ p)
{
	_native = new btSoftBody::Body(p->_native);
}

Body::Body(BulletSharp::CollisionObject^ colObj)
{
	_native = new btSoftBody::Body(GetUnmanagedNullable(colObj));
}

void Body::Activate()
{
	_native->activate();
}

void Body::ApplyDImpulse(Vector3 impulse, Vector3 rPos)
{
	VECTOR3_DEF(impulse);
	VECTOR3_DEF(rPos);

	_native->applyDImpulse(VECTOR3_USE(impulse), VECTOR3_USE(rPos));

	VECTOR3_DEL(impulse);
	VECTOR3_DEL(rPos);
}

void Body::ApplyImpulse(Impulse^ impulse, Vector3 rPos)
{
	VECTOR3_DEF(rPos);
	_native->applyImpulse(*impulse->UnmanagedPointer, VECTOR3_USE(rPos));
	VECTOR3_DEL(rPos);
}

void Body::ApplyVAImpulse(Vector3 impulse)
{
	VECTOR3_DEF(impulse);
	_native->applyVAImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void Body::ApplyDAImpulse(Vector3 impulse)
{
	VECTOR3_DEF(impulse);
	_native->applyDAImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void Body::ApplyAImpulse(Impulse^ impulse)
{
	_native->applyAImpulse(*impulse->UnmanagedPointer);
}

void Body::ApplyDCImpulse(Vector3 impulse)
{
	VECTOR3_DEF(impulse);
	_native->applyDCImpulse(VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void Body_GetAngularVelocity(btSoftBody::Body* body, btVector3* rpos, btVector3* velocity)
{
	*velocity = body->angularVelocity(*rpos);
}
Vector3 Body::GetAngularVelocity(Vector3 rPos)
{
	VECTOR3_DEF(rPos);
	btVector3* velocityTemp = new btVector3;
	Body_GetAngularVelocity(_native, VECTOR3_PTR(rPos), velocityTemp);
	VECTOR3_DEL(rPos);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	delete velocityTemp;
	return velocity;
}

void Body_GetVelocity(btSoftBody::Body* body, btVector3* rpos, btVector3* velocity)
{
	*velocity = body->velocity(*rpos);
}
Vector3 Body::Velocity(Vector3 rPos)
{
	VECTOR3_DEF(rPos);
	btVector3* velocityTemp = new btVector3;
	Body_GetVelocity(_native, VECTOR3_PTR(rPos), velocityTemp);
	VECTOR3_DEL(rPos);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	delete velocityTemp;
	return velocity;
}

void Body_GetAngularVelocity(btSoftBody::Body* body, btVector3* velocity)
{
	*velocity = body->angularVelocity();
}
Vector3 Body::AngularVelocity::get()
{
	btVector3* velocityTemp = new btVector3;
	Body_GetAngularVelocity(_native, velocityTemp);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	delete velocityTemp;
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

void Body_GetLinearVelocity(btSoftBody::Body* body, btVector3* velocity)
{
	*velocity = body->linearVelocity();
}
Vector3 Body::LinearVelocity::get()
{
	btVector3* velocityTemp = new btVector3;
	Body_GetLinearVelocity(_native, velocityTemp);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	delete velocityTemp;
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
	if (_native->m_soft == 0)
		return nullptr;
	return gcnew Cluster(_native->m_soft);
}
void Body::Soft::set(Cluster^ value)
{
	_native->m_soft = GetUnmanagedNullable(value);
}

Matrix Body::XForm::get()
{
	return Math::BtTransformToMatrix(&_native->xform());
}


Cluster::Cluster(btSoftBody::Cluster* cluster)
{
	_native = cluster;
}

Cluster::Cluster()
{
	_native = new btSoftBody::Cluster();
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
	return gcnew Vector3Array(_native->m_dimpulses, 2);
}

AlignedVector3Array^ Cluster::FrameRefs::get()
{
	return gcnew AlignedVector3Array(&_native->m_framerefs);
}

Matrix Cluster::FrameXForm::get()
{
	return Math::BtTransformToMatrix(&_native->m_framexform);
}
void Cluster::FrameXForm::set(Matrix value)
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
	if (_native->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(_native->m_leaf);
}
void Cluster::Leaf::set(DbvtNode^ value)
{
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
	return gcnew AlignedScalarArray(&_native->m_masses);
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
	return gcnew AlignedNodePtrArray(&_native->m_nodes);
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
	return gcnew Vector3Array(_native->m_vimpulses, 2);
}


Config::Config(btSoftBody::Config* config)
{
	_config = config;
}

Config::Config()
{
	_config = new btSoftBody::Config();
}

AeroModel Config::AeroModel::get()
{
	return (BulletSharp::SoftBody::AeroModel)_config->aeromodel;
}
void Config::AeroModel::set(BulletSharp::SoftBody::AeroModel value)
{
	_config->aeromodel = (btSoftBody::eAeroModel::_)value;
}

btScalar Config::Ahr::get()
{
	return _config->kAHR;
}
void Config::Ahr::set(btScalar value)
{
	_config->kAHR = value;
}

btScalar Config::Chr::get()
{
	return _config->kCHR;
}
void Config::Chr::set(btScalar value)
{
	_config->kCHR = value;
}

int Config::CIterations::get()
{
	return _config->citerations;
}
void Config::CIterations::set(int value)
{
	_config->citerations = value;
}

FCollisions Config::Collisions::get()
{
	return (FCollisions)UnmanagedPointer->collisions;
}
void Config::Collisions::set(FCollisions value)
{
	UnmanagedPointer->collisions = (int)value;
}

btScalar Config::DF::get()
{
	return _config->kDF;
}
void Config::DF::set(btScalar value)
{
	_config->kDF = value;
}

btScalar Config::DG::get()
{
	return _config->kDG;
}
void Config::DG::set(btScalar value)
{
	_config->kDG = value;
}

int Config::DIterations::get()
{
	return _config->diterations;
}
void Config::DIterations::set(int value)
{
	_config->diterations = value;
}

btScalar Config::DP::get()
{
	return _config->kDP;
}
void Config::DP::set(btScalar value)
{
	_config->kDP = value;
}

AlignedPSolverArray^ Config::DSequence::get()
{
	return gcnew AlignedPSolverArray(&_config->m_dsequence);
}

btScalar Config::Khr::get()
{
	return _config->kKHR;
}
void Config::Khr::set(btScalar value)
{
	_config->kKHR = value;
}

btScalar Config::LF::get()
{
	return _config->kLF;
}
void Config::LF::set(btScalar value)
{
	_config->kLF = value;
}

btScalar Config::MaxVolume::get()
{
	return _config->maxvolume;
}
void Config::MaxVolume::set(btScalar value)
{
	_config->maxvolume = value;
}

btScalar Config::MT::get()
{
	return _config->kMT;
}
void Config::MT::set(btScalar value)
{
	_config->kMT = value;
}

int Config::PIterations::get()
{
	return _config->piterations;
}
void Config::PIterations::set(int value)
{
	_config->piterations = value;
}

btScalar Config::PR::get()
{
	return _config->kPR;
}
void Config::PR::set(btScalar value)
{
	_config->kPR = value;
}

AlignedPSolverArray^ Config::PSequence::get()
{
	return gcnew AlignedPSolverArray(&_config->m_psequence);
}

btScalar Config::Shr::get()
{
	return _config->kSHR;
}
void Config::Shr::set(btScalar value)
{
	_config->kSHR = value;
}

btScalar Config::SkhrCl::get()
{
	return _config->kSKHR_CL;
}
void Config::SkhrCl::set(btScalar value)
{
	_config->kSKHR_CL = value;
}

btScalar Config::SrhrCl::get()
{
	return _config->kSRHR_CL;
}
void Config::SrhrCl::set(btScalar value)
{
	_config->kSRHR_CL = value;
}

btScalar Config::SshrCl::get()
{
	return _config->kSSHR_CL;
}
void Config::SshrCl::set(btScalar value)
{
	_config->kSSHR_CL = value;
}

btScalar Config::SKSplitCl::get()
{
	return _config->kSK_SPLT_CL;
}
void Config::SKSplitCl::set(btScalar value)
{
	_config->kSK_SPLT_CL = value;
}

btScalar Config::SRSplitCl::get()
{
	return _config->kSR_SPLT_CL;
}
void Config::SRSplitCl::set(btScalar value)
{
	_config->kSR_SPLT_CL = value;
}

btScalar Config::SSSplitCl::get()
{
	return _config->kSS_SPLT_CL;
}
void Config::SSSplitCl::set(btScalar value)
{
	_config->kSS_SPLT_CL = value;
}

btScalar Config::TimeScale::get()
{
	return _config->timescale;
}
void Config::TimeScale::set(btScalar value)
{
	_config->timescale = value;
}

btScalar Config::VC::get()
{
	return _config->kVC;
}
void Config::VC::set(btScalar value)
{
	_config->kVC = value;
}

btScalar Config::VCF::get()
{
	return _config->kVCF;
}
void Config::VCF::set(btScalar value)
{
	_config->kVCF = value;
}

int Config::VIterations::get()
{
	return _config->viterations;
}
void Config::VIterations::set(int value)
{
	_config->viterations = value;
}

AlignedVSolverArray^ Config::VSequence::get()
{
	return gcnew AlignedVSolverArray(&_config->m_vsequence);
}

btSoftBody::Config* Config::UnmanagedPointer::get()
{
	return _config;
}
void Config::UnmanagedPointer::set(btSoftBody::Config* value)
{
	_config = value;
}


Element::Element(btSoftBody::Element* element)
{
	_native = element;
}

Element::Element()
{
	_native = new btSoftBody::Element();
}

Object^ Element::Tag::get()
{
	void* obj = _native->m_tag;
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}
void Element::Tag::set(Object^ value)
{
	void* obj = _native->m_tag;
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_native->m_tag = GCHandleToVoidPtr(handle);
}


#define Native (static_cast<btSoftBody::Feature*>(_native))

Feature::Feature(btSoftBody::Feature* feature)
: Element(feature)
{
}

Feature::Feature()
: Element(new btSoftBody::Feature())
{
}

BulletSharp::SoftBody::Material^ Feature::Material::get()
{
	if (Native->m_material == 0)
		return nullptr;
	return gcnew BulletSharp::SoftBody::Material(Native->m_material);
}
void Feature::Material::set(BulletSharp::SoftBody::Material^ value)
{
	Native->m_material = (btSoftBody::Material*)GetUnmanagedNullable(value);
}


#undef Native
#define Native (static_cast<btSoftBody::Face*>(_native))

Face::Face(btSoftBody::Face* face)
: Feature(face)
{
}

Face::Face()
: Feature(new btSoftBody::Face())
{
}

#ifndef DISABLE_DBVT
DbvtNode^ Face::Leaf::get()
{
	if (Native->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(Native->m_leaf);
}
void Face::Leaf::set(DbvtNode^ value)
{
	Native->m_leaf = GetUnmanagedNullable(value);
}
#endif

NodePtrArray^ Face::N::get()
{
	ReturnCachedObjectStaticParam(NodePtrArray, _n, Native->m_n, 3);
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
	_implicitFn = new ImplicitFnWrapper(this);
}

ImplicitFnWrapper* ImplicitFn::UnmanagedPointer::get()
{
	return _implicitFn;
}
void ImplicitFn::UnmanagedPointer::set(ImplicitFnWrapper* value)
{
	_implicitFn = value;
}


ImplicitFnWrapper::ImplicitFnWrapper(BulletSharp::SoftBody::ImplicitFn^ implicitFn)
{
	_implicitFn = implicitFn;
}

btScalar ImplicitFnWrapper::Eval(const btVector3& x)
{
	return _implicitFn->Eval(Math::BtVector3ToVector3(&x));
}


Impulse::Impulse(btSoftBody::Impulse* impulse)
{
	_impulse = impulse;
}

Impulse::Impulse()
{
	_impulse = new btSoftBody::Impulse();
}

bool Impulse::AsDrift::get()
{
	return _impulse->m_asDrift != 0;
}
void Impulse::AsDrift::set(bool value)
{
	_impulse->m_asDrift = value;
}

bool Impulse::AsVelocity::get()
{
	return _impulse->m_asVelocity != 0;
}
void Impulse::AsVelocity::set(bool value)
{
	_impulse->m_asVelocity = value;
}

Vector3 Impulse::Drift::get()
{
	return Math::BtVector3ToVector3(&_impulse->m_drift);
}
void Impulse::Drift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_impulse->m_drift);
}

Vector3 Impulse::Velocity::get()
{
	return Math::BtVector3ToVector3(&_impulse->m_velocity);
}
void Impulse::Velocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_impulse->m_velocity);
}

btSoftBody::Impulse* Impulse_Negative(btSoftBody::Impulse* impulse)
{
	btSoftBody::Impulse* impulseNew = new btSoftBody::Impulse();
	*impulseNew = -*impulse;
	return impulseNew;
}
Impulse^ Impulse::operator-(Impulse^ i)
{
	return gcnew Impulse(Impulse_Negative(i->UnmanagedPointer));
}

btSoftBody::Impulse* Impulse_Multiply(btSoftBody::Impulse* impulse, btScalar x)
{
	btSoftBody::Impulse* impulseNew = new btSoftBody::Impulse();
	*impulseNew = (*impulse) * x;
	return impulseNew;
}
Impulse^ Impulse::operator*(Impulse^ i, btScalar x)
{
	return gcnew Impulse(Impulse_Multiply(i->UnmanagedPointer, x));
}

btSoftBody::Impulse* BulletSharp::SoftBody::Impulse::UnmanagedPointer::get()
{
	return _impulse;
}
void BulletSharp::SoftBody::Impulse::UnmanagedPointer::set(btSoftBody::Impulse* value)
{
	_impulse = value;
}


btScalar BulletSharp::SoftBody::Joint::Specs::Cfm::get()
{
	return _native->cfm;
}
void BulletSharp::SoftBody::Joint::Specs::Cfm::set(btScalar value)
{
	_native->cfm = value;
}

btScalar BulletSharp::SoftBody::Joint::Specs::Erp::get()
{
	return _native->erp;
}
void BulletSharp::SoftBody::Joint::Specs::Erp::set(btScalar value)
{
	_native->erp = value;
}

btScalar BulletSharp::SoftBody::Joint::Specs::Split::get()
{
	return _native->split;
}
void BulletSharp::SoftBody::Joint::Specs::Split::set(btScalar value)
{
	_native->split = value;
}


Joint^ BulletSharp::SoftBody::Joint::GetManaged(btSoftBody::Joint* joint)
{
	if (joint == 0)
		return nullptr;

	btSoftBody::AJoint* ajoint = static_cast<btSoftBody::AJoint*>(joint);
	if (ajoint) {
		return gcnew AJoint(ajoint);
	}

	return gcnew Joint(joint);
}

BulletSharp::SoftBody::Joint::Joint(btSoftBody::Joint* joint)
{
	_native = joint;
}

void BulletSharp::SoftBody::Joint::Prepare(btScalar dt, int iterations)
{
	_native->Prepare(dt, iterations);
}

void BulletSharp::SoftBody::Joint::Solve(btScalar dt, btScalar sor)
{
	_native->Solve(dt, sor);
}

void BulletSharp::SoftBody::Joint::Terminate(btScalar dt)
{
	_native->Terminate(dt);
}

BodyArray^ BulletSharp::SoftBody::Joint::Bodies::get()
{
	return gcnew BodyArray(_native->m_bodies, 2);
}

btScalar BulletSharp::SoftBody::Joint::Cfm::get()
{
	return _native->m_cfm;
}
void BulletSharp::SoftBody::Joint::Cfm::set(btScalar value)
{
	_native->m_cfm = value;
}

bool BulletSharp::SoftBody::Joint::Delete::get()
{
	return _native->m_delete;
}
void BulletSharp::SoftBody::Joint::Delete::set(bool value)
{
	_native->m_delete = value;
}

Vector3 BulletSharp::SoftBody::Joint::Drift::get()
{
	return Math::BtVector3ToVector3(&_native->m_drift);
}
void BulletSharp::SoftBody::Joint::Drift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_drift);
}

btScalar BulletSharp::SoftBody::Joint::Erp::get()
{
	return _native->m_erp;
}
void BulletSharp::SoftBody::Joint::Erp::set(btScalar value)
{
	_native->m_erp = value;
}

Matrix BulletSharp::SoftBody::Joint::MassMatrix::get()
{
	return Math::BtMatrix3x3ToMatrix(&_native->m_massmatrix);
}
void BulletSharp::SoftBody::Joint::MassMatrix::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_native->m_massmatrix);
}

Vector3Array^ BulletSharp::SoftBody::Joint::Refs::get()
{
	return gcnew Vector3Array(_native->m_refs, 2);
}

Vector3 BulletSharp::SoftBody::Joint::SDrift::get()
{
	return Math::BtVector3ToVector3(&_native->m_sdrift);
}
void BulletSharp::SoftBody::Joint::SDrift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_sdrift);
}

btScalar BulletSharp::SoftBody::Joint::Split::get()
{
	return _native->m_split;
}
void BulletSharp::SoftBody::Joint::Split::set(btScalar value)
{
	_native->m_split = value;
}

Joint::JointType BulletSharp::SoftBody::Joint::Type::get()
{
	return (JointType)_native->Type();
}


#undef Native
#define Native static_cast<btSoftBody::LJoint*>(_native)

LJoint::LJoint(btSoftBody::LJoint* joint)
: Joint(joint)
{
}

BulletSharp::SoftBody::LJoint::LJoint()
: Joint(new btSoftBody::LJoint())
{
}

Vector3Array^ BulletSharp::SoftBody::LJoint::RPos::get()
{
	return gcnew Vector3Array(Native->m_rpos, 2);
}


#undef Native
#define Native static_cast<btSoftBody::LJoint::Specs*>(_native)

BulletSharp::SoftBody::LJoint::Specs::Specs()
{
	_native = new btSoftBody::LJoint::Specs();
}

Vector3 BulletSharp::SoftBody::LJoint::Specs::Position::get()
{
	return Math::BtVector3ToVector3(&Native->position);
}
void BulletSharp::SoftBody::LJoint::Specs::Position::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->position);
}


BulletSharp::SoftBody::AJoint::IControl::IControl()
{
	_iControl = new AJointIControlWrapper(this);
}

BulletSharp::SoftBody::AJoint::IControl::IControl(AJointIControlWrapper* iControl)
{
	_iControl = iControl;
}

AJoint::IControl^ BulletSharp::SoftBody::AJoint::IControl::Default::get()
{
	if (def == nullptr)
		def = gcnew AJoint::IControl();
	return def;
}

AJointIControlWrapper* BulletSharp::SoftBody::AJoint::IControl::UnmanagedPointer::get()
{
	return _iControl;
}
void BulletSharp::SoftBody::AJoint::IControl::UnmanagedPointer::set(AJointIControlWrapper* value)
{
	_iControl = value;
}


#undef Native
#define Native static_cast<btSoftBody::AJoint::Specs*>(_native)

BulletSharp::SoftBody::AJoint::Specs::Specs()
{
	_native = new btSoftBody::AJoint::Specs();
}

Vector3 BulletSharp::SoftBody::AJoint::Specs::Axis::get()
{
	return Math::BtVector3ToVector3(&Native->axis);
}
void BulletSharp::SoftBody::AJoint::Specs::Axis::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->axis);
}

AJoint::IControl^ BulletSharp::SoftBody::AJoint::Specs::IControl::get()
{
	return gcnew AJoint::IControl((AJointIControlWrapper*)Native->icontrol);
}
void BulletSharp::SoftBody::AJoint::Specs::IControl::set(AJoint::IControl^ value)
{
	Native->icontrol = value->UnmanagedPointer;
}


void BulletSharp::SoftBody::AJoint::IControl::Prepare(AJoint^ joint)
{
	_iControl->basePrepare((btSoftBody::AJoint*)joint->_native);
}

btScalar BulletSharp::SoftBody::AJoint::IControl::Speed(AJoint^ joint, btScalar current)
{
	return _iControl->baseSpeed((btSoftBody::AJoint*)joint->_native, current);
}


AJointIControlWrapper::AJointIControlWrapper(AJoint::IControl^ iControl)
{
	_iControl = iControl;
}

void AJointIControlWrapper::Prepare(btSoftBody::AJoint* joint)
{
	_iControl->Prepare(gcnew AJoint(joint));
}

btScalar AJointIControlWrapper::Speed(btSoftBody::AJoint* joint, btScalar current)
{
	return _iControl->Speed(gcnew AJoint(joint), current);
}

void AJointIControlWrapper::basePrepare(btSoftBody::AJoint* joint)
{
	IControl::Prepare(joint);
}

btScalar AJointIControlWrapper::baseSpeed(btSoftBody::AJoint* joint, btScalar current)
{
	return IControl::Speed(joint, current);
}


#undef Native
#define Native static_cast<btSoftBody::AJoint*>(_native)

AJoint::AJoint(btSoftBody::AJoint* joint)
: Joint(joint)
{
}

Vector3Array^ AJoint::Axis::get()
{
	return gcnew Vector3Array(Native->m_axis, 2);
}

AJoint::IControl^ AJoint::Control::get()
{
	return gcnew AJoint::IControl((AJointIControlWrapper*)Native->m_icontrol);
}
void AJoint::Control::set(AJoint::IControl^ value)
{
	Native->m_icontrol = value->UnmanagedPointer;
}


#undef Native
#define Native static_cast<btSoftBody::CJoint*>(_native)

CJoint::CJoint(btSoftBody::CJoint* joint)
: Joint(joint)
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
	return gcnew Vector3Array(Native->m_rpos, 2);
}


#undef Native
#define Native static_cast<btSoftBody::Link*>(_native)

Link::Link(btSoftBody::Link* link)
: Feature(link)
{
}

Link::Link()
: Feature(new btSoftBody::Link())
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
	ReturnCachedObjectStaticParam(NodePtrArray, _nodePtrArray, Native->m_n, 2);
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
#define Native static_cast<btSoftBody::Material*>(_native)

BulletSharp::SoftBody::Material::Material(btSoftBody::Material* material)
: Element(material)
{
}

BulletSharp::SoftBody::Material::Material()
: Element(new btSoftBody::Material())
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

BulletSharp::SoftBody::Node::Node(btSoftBody::Node* node)
: Feature(node)
{
}

BulletSharp::SoftBody::Node::Node()
: Feature(new btSoftBody::Node())
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
	if (Native->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(Native->m_leaf);
}
void BulletSharp::SoftBody::Node::Leaf::set(DbvtNode^ value)
{
	Native->m_leaf = GetUnmanagedNullable(value);
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

Note::Note(btSoftBody::Note* note)
: Element(note)
{
}

Note::Note()
: Element(new btSoftBody::Note())
{
}

ScalarArray^ Note::Coords::get()
{
	return gcnew ScalarArray(&Native->m_coords[0], 4);
}

NodePtrArray^ Note::Nodes::get()
{
	return gcnew NodePtrArray(&Native->m_nodes[0], 4);
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
	Native->m_text = StringConv::ManagedToUnmanaged(value);
}


// Keep "BulletSharp::SoftBody::" so that we wouldn't conflict with Mogre::Pose.
BulletSharp::SoftBody::Pose::Pose()
{
	_pose = new btSoftBody::Pose();
}

BulletSharp::SoftBody::Pose::Pose(btSoftBody::Pose* pose)
{
	_pose = pose;
}

Matrix BulletSharp::SoftBody::Pose::Aqq::get()
{
	return Math::BtMatrix3x3ToMatrix(&UnmanagedPointer->m_aqq);
}
void BulletSharp::SoftBody::Pose::Aqq::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &UnmanagedPointer->m_aqq);
}

Vector3 BulletSharp::SoftBody::Pose::Com::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_com);
}
void BulletSharp::SoftBody::Pose::Com::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_com);
}

bool BulletSharp::SoftBody::Pose::IsFrameValid::get()
{
	return _pose->m_bframe;
}
void BulletSharp::SoftBody::Pose::IsFrameValid::set(bool value)
{
	_pose->m_bframe = value;
}

bool BulletSharp::SoftBody::Pose::IsVolumeValid::get()
{
	return _pose->m_bvolume;
}
void BulletSharp::SoftBody::Pose::IsVolumeValid::set(bool value)
{
	_pose->m_bvolume = value;
}

AlignedVector3Array^ BulletSharp::SoftBody::Pose::Positions::get()
{
	return gcnew AlignedVector3Array(&_pose->m_pos);
}

Matrix BulletSharp::SoftBody::Pose::Rotation::get()
{
	return Math::BtMatrix3x3ToMatrix(&UnmanagedPointer->m_rot);
}
void BulletSharp::SoftBody::Pose::Rotation::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &UnmanagedPointer->m_rot);
}

Matrix BulletSharp::SoftBody::Pose::Scale::get()
{
	return Math::BtMatrix3x3ToMatrix(&UnmanagedPointer->m_scl);
}
void BulletSharp::SoftBody::Pose::Scale::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &UnmanagedPointer->m_scl);
}

btScalar BulletSharp::SoftBody::Pose::Volume::get()
{
	return _pose->m_volume;
}
void BulletSharp::SoftBody::Pose::Volume::set(btScalar value)
{
	_pose->m_volume = value;
}

AlignedScalarArray^ BulletSharp::SoftBody::Pose::Weights::get()
{
	return gcnew AlignedScalarArray(&_pose->m_wgh);
}

btSoftBody::Pose* BulletSharp::SoftBody::Pose::UnmanagedPointer::get()
{
	return _pose;
}
void BulletSharp::SoftBody::Pose::UnmanagedPointer::set(btSoftBody::Pose* value)
{
	_pose = value;
}


RigidContact::RigidContact(btSoftBody::RContact* rigidContact)
{
	_rigidContact = rigidContact;
}

RigidContact::RigidContact()
{
	_rigidContact = new btSoftBody::RContact();
}

Matrix RigidContact::C0::get()
{
	return Math::BtMatrix3x3ToMatrix(&_rigidContact->m_c0);
}
void RigidContact::C0::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_rigidContact->m_c0);
}

Vector3 RigidContact::C1::get()
{
	return Math::BtVector3ToVector3(&_rigidContact->m_c1);
}
void RigidContact::C1::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_rigidContact->m_c1);
}

btScalar RigidContact::C2::get()
{
	return _rigidContact->m_c2;
}
void RigidContact::C2::set(btScalar value)
{
	_rigidContact->m_c2 = value;
}

btScalar RigidContact::C3::get()
{
	return _rigidContact->m_c3;
}
void RigidContact::C3::set(btScalar value)
{
	_rigidContact->m_c3 = value;
}

btScalar RigidContact::C4::get()
{
	return _rigidContact->m_c4;
}
void RigidContact::C4::set(btScalar value)
{
	_rigidContact->m_c4 = value;
}

BulletSharp::SoftBody::Node^ RigidContact::Node::get()
{
	if (_rigidContact->m_node == nullptr)
		return nullptr;
	return gcnew BulletSharp::SoftBody::Node(_rigidContact->m_node);
}
void RigidContact::Node::set(BulletSharp::SoftBody::Node^ value)
{
	_rigidContact->m_node = (btSoftBody::Node*)GetUnmanagedNullable(value);
}

Scti^ RigidContact::Scti::get()
{
	return gcnew BulletSharp::SoftBody::Scti(&_rigidContact->m_cti);
}

btSoftBody::RContact* RigidContact::UnmanagedPointer::get()
{
	return _rigidContact;
}
void RigidContact::UnmanagedPointer::set(btSoftBody::RContact* value)
{
	_rigidContact = value;
}


Scti::Scti(btSoftBody::sCti* sCti)
{
	_sCti = sCti;
}

Scti::Scti()
{
	_sCti = new btSoftBody::sCti();
}

CollisionObject^ Scti::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_sCti->m_colObj);
}
void Scti::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_sCti->m_colObj = GetUnmanagedNullable(value);
}

Vector3 Scti::Normal::get()
{
	return Math::BtVector3ToVector3(&_sCti->m_normal);
}
void Scti::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_sCti->m_normal);
}

btScalar Scti::Offset::get()
{
	return _sCti->m_offset;
}
void Scti::Offset::set(btScalar value)
{
	_sCti->m_offset = value;
}

btSoftBody::sCti* Scti::UnmanagedPointer::get()
{
	return _sCti;
}
void Scti::UnmanagedPointer::set(btSoftBody::sCti* value)
{
	_sCti = value;
}


SoftContact::SoftContact(btSoftBody::SContact* softContact)
{
	_softContact = softContact;
}

SoftContact::SoftContact()
{
	_softContact = new btSoftBody::SContact();
}

ScalarArray^ SoftContact::Cfm::get()
{
	return gcnew ScalarArray(_softContact->m_cfm, 2);
}

BulletSharp::SoftBody::Face^ SoftContact::Face::get()
{
	if (_softContact->m_face == nullptr)
		return nullptr;
	return gcnew BulletSharp::SoftBody::Face(_softContact->m_face);
}
void SoftContact::Face::set(BulletSharp::SoftBody::Face^ value)
{
	_softContact->m_face = (btSoftBody::Face*)GetUnmanagedNullable(value);
}

btScalar SoftContact::Friction::get()
{
	return _softContact->m_friction;
}
void SoftContact::Friction::set(btScalar value)
{
	_softContact->m_friction = value;
}

BulletSharp::SoftBody::Node^ SoftContact::Node::get()
{
	if (_softContact->m_node == nullptr)
		return nullptr;
	return gcnew BulletSharp::SoftBody::Node(_softContact->m_node);
}
void SoftContact::Node::set(BulletSharp::SoftBody::Node^ value)
{
	_softContact->m_node = (btSoftBody::Node*)GetUnmanagedNullable(value);
}

Vector3 SoftContact::Normal::get()
{
	return Math::BtVector3ToVector3(&_softContact->m_normal);
}
void SoftContact::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_softContact->m_normal);
}

Vector3 SoftContact::Weights::get()
{
	return Math::BtVector3ToVector3(&_softContact->m_weights);
}
void SoftContact::Weights::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_softContact->m_weights);
}

btSoftBody::SContact* SoftContact::UnmanagedPointer::get()
{
	return _softContact;
}
void SoftContact::UnmanagedPointer::set(btSoftBody::SContact* value)
{
	_softContact = value;
}


SolverState::SolverState(btSoftBody::SolverState* solverState)
{
	_solverState = solverState;
}

btScalar SolverState::InverseSdt::get()
{
	return _solverState->isdt;
}
void SolverState::InverseSdt::set(btScalar value)
{
	_solverState->isdt = value;
}

btScalar SolverState::RadialMargin::get()
{
	return _solverState->radmrg;
}
void SolverState::RadialMargin::set(btScalar value)
{
	_solverState->radmrg = value;
}

btScalar SolverState::Sdt::get()
{
	return _solverState->sdt;
}
void SolverState::Sdt::set(btScalar value)
{
	_solverState->sdt = value;
}

btScalar SolverState::VelocityMargin::get()
{
	return _solverState->velmrg;
}
void SolverState::VelocityMargin::set(btScalar value)
{
	_solverState->velmrg = value;
}

btScalar SolverState::UpdateMargin::get()
{
	return _solverState->updmrg;
}
void SolverState::UpdateMargin::set(btScalar value)
{
	_solverState->updmrg = value;
}

btSoftBody::SolverState* SolverState::UnmanagedPointer::get()
{
	return _solverState;
}
void SolverState::UnmanagedPointer::set(btSoftBody::SolverState* value)
{
	_solverState = value;
}


SRayCast::SRayCast(btSoftBody::sRayCast* rayCast)
{
	_rayCast = rayCast;
}

SRayCast::SRayCast()
{
	_rayCast = new btSoftBody::sRayCast();
}

BulletSharp::SoftBody::SoftBody^ SRayCast::Body::get()
{
	return (BulletSharp::SoftBody::SoftBody^)CollisionObject::GetManaged(_rayCast->body);
}
void SRayCast::Body::set(BulletSharp::SoftBody::SoftBody^ value)
{
	_rayCast->body = (btSoftBody*)GetUnmanagedNullable(value);
}

EFeature SRayCast::Feature::get()
{
	return (EFeature)_rayCast->feature;
}
void SRayCast::Feature::set(EFeature value)
{
	_rayCast->feature = (btSoftBody::eFeature::_)value;
}

btScalar SRayCast::Fraction::get()
{
	return _rayCast->fraction;
}
void SRayCast::Fraction::set(btScalar value)
{
	_rayCast->fraction = value;
}

int SRayCast::Index::get()
{
	return _rayCast->index;
}
void SRayCast::Index::set(int value)
{
	_rayCast->index = value;
}

btSoftBody::sRayCast* SRayCast::UnmanagedPointer::get()
{
	return _rayCast;
}


#undef Native
#define Native static_cast<btSoftBody::Tetra*>(_native)

Tetra::Tetra(btSoftBody::Tetra* tetra)
: Feature(tetra)
{
}

Tetra::Tetra()
: Feature(new btSoftBody::Tetra())
{
}

Vector3Array^ Tetra::C0::get()
{
	return gcnew Vector3Array(Native->m_c0, 4);
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

NodePtrArray^ Tetra::Nodes::get()
{
	return gcnew NodePtrArray(Native->m_n, 4);
}

#ifndef DISABLE_DBVT
DbvtNode^ Tetra::Leaf::get()
{
	if (Native->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(Native->m_leaf);
}
void Tetra::Leaf::set(DbvtNode^ value)
{
	Native->m_leaf = GetUnmanagedNullable(value);
}
#endif

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

BulletSharp::SoftBody::SoftBody::SoftBody(btSoftBody* body)
: CollisionObject(body)
{
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
}

BulletSharp::SoftBody::SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo)
: CollisionObject(new btSoftBody(worldInfo->_native))
{
}

void BulletSharp::SoftBody::SoftBody::AddAeroForceToFace(Vector3 windVelocity, int faceIndex)
{
	VECTOR3_DEF(windVelocity);
	Native->addAeroForceToFace(VECTOR3_USE(windVelocity), faceIndex);
	VECTOR3_DEL(windVelocity);
}

void BulletSharp::SoftBody::SoftBody::AddAeroForceToNode(Vector3 windVelocity, int nodeIndex)
{
	VECTOR3_DEF(windVelocity);
	Native->addAeroForceToNode(VECTOR3_USE(windVelocity), nodeIndex);
	VECTOR3_DEL(windVelocity);
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force, int node)
{
	VECTOR3_DEF(force);
	Native->addForce(VECTOR3_USE(force), node);
	VECTOR3_DEL(force);
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force)
{
	VECTOR3_DEF(force);
	Native->addForce(VECTOR3_USE(force));
	VECTOR3_DEL(force);
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity, int node)
{
	VECTOR3_DEF(velocity);
	Native->addVelocity(VECTOR3_USE(velocity), node);
	VECTOR3_DEL(velocity);
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity)
{
	VECTOR3_DEF(velocity);
	Native->addVelocity(VECTOR3_USE(velocity));
	VECTOR3_DEL(velocity);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies, btScalar influence)
{
	Native->appendAnchor(node, (btRigidBody*)body->_native, disableCollisionBetweenLinkedBodies, influence);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies)
{
	Native->appendAnchor(node, (btRigidBody*)body->_native, disableCollisionBetweenLinkedBodies);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body)
{
	Native->appendAnchor(node, (btRigidBody*)body->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, Vector3 localPivot, bool disableCollisionBetweenLinkedBodies)
{
	VECTOR3_DEF(localPivot);
	Native->appendAnchor(node, (btRigidBody*)body->_native, VECTOR3_USE(localPivot), disableCollisionBetweenLinkedBodies);
	VECTOR3_DEL(localPivot);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, Vector3 localPivot)
{
	VECTOR3_DEF(localPivot);
	Native->appendAnchor(node, (btRigidBody*)body->_native, VECTOR3_USE(localPivot));
	VECTOR3_DEL(localPivot);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int node0, int node1, int node2, Material^ material)
{
	Native->appendFace(node0, node1, node2, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int node0, int node1, int node2)
{
	Native->appendFace(node0, node1, node2);
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

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, Cluster^ body0, Body^ body1)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native, body0->_native, *body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, Body^ body1)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native, *body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, SoftBody^ body1)
{
	Native->appendLinearJoint(*(btSoftBody::LJoint::Specs*)specs->_native, (btSoftBody*)body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, Cluster^ body0, Body^ body1)
{
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native, body0->_native, *body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, Body^ body1)
{
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native, *body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs)
{
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, SoftBody^ body1)
{
	Native->appendAngularJoint(*(btSoftBody::AJoint::Specs*)specs->_native, (btSoftBody*)body1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1, Material^ material, bool bCheckExist)
{
	Native->appendLink(node0, node1, (btSoftBody::Material*)material->_native, bCheckExist);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1, Material^ material)
{
	Native->appendLink(node0, node1, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1)
{
	Native->appendLink(node0, node1);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1, Material^ material, bool bCheckExist)
{
	Native->appendLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native, (btSoftBody::Material*)material->_native, bCheckExist);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1, Material^ material)
{
	Native->appendLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1)
{
	Native->appendLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int model, Material^ material)
{
	Native->appendLink(model, (btSoftBody::Material*)material->_native);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int model)
{
	Native->appendLink(model);
}

void BulletSharp::SoftBody::SoftBody::AppendLink()
{
	Native->appendLink();
}

BulletSharp::SoftBody::Material^ BulletSharp::SoftBody::SoftBody::AppendMaterial()
{
	return gcnew Material(Native->appendMaterial());
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2, Node^ n3)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Native->appendNote(textTemp, VECTOR3_USE(o), *cTemp, (btSoftBody::Node*)n0->_native, (btSoftBody::Node*)n1->_native,
		(btSoftBody::Node*)n2->_native, (btSoftBody::Node*)n3->_native);

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Native->appendNote(textTemp, VECTOR3_USE(o), *cTemp, (btSoftBody::Node*)n0->_native, (btSoftBody::Node*)n1->_native,
		(btSoftBody::Node*)n2->_native);

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Native->appendNote(textTemp, VECTOR3_USE(o), *cTemp, (btSoftBody::Node*)n0->_native, (btSoftBody::Node*)n1->_native);

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Native->appendNote(textTemp, VECTOR3_USE(o), *cTemp, (btSoftBody::Node*)n0->_native);

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Native->appendNote(textTemp, VECTOR3_USE(o), *cTemp);

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNode(Vector3 x, btScalar m)
{
	VECTOR3_DEF(x);
	Native->appendNode(VECTOR3_USE(x), m);
	VECTOR3_DEL(x);
}

void SoftBody_AppendNote(btSoftBody* body, const char* text, btVector3* c)
{
	body->appendNote(text, *c);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);

	SoftBody_AppendNote(Native, textTemp, VECTOR3_PTR(o));

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Node^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);

	Native->appendNote(textTemp, VECTOR3_USE(o), (btSoftBody::Node*)feature->_native);

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Link^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);

	Native->appendNote(textTemp, VECTOR3_USE(o), (btSoftBody::Link*)feature->_native);

	StringConv::FreeUnmanagedString(textTemp);
	VECTOR3_DEL(o);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Face^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	VECTOR3_DEF(o);

	Native->appendNote(textTemp, VECTOR3_USE(o), (btSoftBody::Face*)feature->_native);

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

bool BulletSharp::SoftBody::SoftBody::CheckFace(int node0, int node1, int node2)
{
	return Native->checkFace(node0, node1, node2);
}

bool BulletSharp::SoftBody::SoftBody::CheckLink(int node0, int node1)
{
	return Native->checkLink(node0, node1);
}

bool BulletSharp::SoftBody::SoftBody::CheckLink(Node^ node0, Node^ node1)
{
	return Native->checkLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native);
}

void BulletSharp::SoftBody::SoftBody::CleanupClusters()
{
	Native->cleanupClusters();
}

void SoftBody_ClusterCOM(btSoftBody::Cluster* cluster, btVector3* com)
{
	*com = btSoftBody::clusterCom(cluster);
}
Vector3 BulletSharp::SoftBody::SoftBody::ClusterCom(Cluster^ cluster)
{
	btVector3* tempClusterCom = new btVector3;
	SoftBody_ClusterCOM(cluster->_native, tempClusterCom);
	Vector3 com = Math::BtVector3ToVector3(tempClusterCom);
	delete tempClusterCom;
	return com;
}

void SoftBody_ClusterCOM(btSoftBody* softBody, int cluster, btVector3* com)
{
	*com = softBody->clusterCom(cluster);
}
Vector3 BulletSharp::SoftBody::SoftBody::ClusterCom(int cluster)
{
	btVector3* tempClusterCom = new btVector3;
	SoftBody_ClusterCOM(Native, cluster, tempClusterCom);
	Vector3 com = Math::BtVector3ToVector3(tempClusterCom);
	delete tempClusterCom;
	return com;
}

void SoftBody_ClusterVelocity(btSoftBody::Cluster* cluster, btVector3* rpos, btVector3* velocity)
{
	*velocity = btSoftBody::clusterVelocity(cluster, *rpos);
}
Vector3 BulletSharp::SoftBody::SoftBody::ClusterVelocity(Cluster^ cluster, Vector3 rpos)
{
	btVector3* tempVelocity = new btVector3;
	VECTOR3_DEF(rpos);
	SoftBody_ClusterVelocity(cluster->_native, VECTOR3_PTR(rpos), tempVelocity);
	VECTOR3_DEL(rpos);
	Vector3 velocity = Math::BtVector3ToVector3(tempVelocity);
	delete tempVelocity;
	return velocity;
}

void BulletSharp::SoftBody::SoftBody::ClusterVImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse)
{
	VECTOR3_DEF(rpos);
	VECTOR3_DEF(impulse);
	btSoftBody::clusterVImpulse(cluster->_native, VECTOR3_USE(rpos), VECTOR3_USE(impulse));
	VECTOR3_DEL(rpos);
	VECTOR3_DEL(impulse);
}

void BulletSharp::SoftBody::SoftBody::ClusterDImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse)
{
	VECTOR3_DEF(rpos);
	VECTOR3_DEF(impulse);
	btSoftBody::clusterDImpulse(cluster->_native, VECTOR3_USE(rpos), VECTOR3_USE(impulse));
	VECTOR3_DEL(rpos);
	VECTOR3_DEL(impulse);
}

void BulletSharp::SoftBody::SoftBody::ClusterImpulse(Cluster^ cluster, Vector3 rpos, Impulse^ impulse)
{
	VECTOR3_DEF(rpos);
	btSoftBody::clusterImpulse(cluster->_native, VECTOR3_USE(rpos), *impulse->UnmanagedPointer);
	VECTOR3_DEL(rpos);
}

void BulletSharp::SoftBody::SoftBody::ClusterVAImpulse(Cluster^ cluster, Vector3 impulse)
{
	VECTOR3_DEF(impulse);
	btSoftBody::clusterVAImpulse(cluster->_native, VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void BulletSharp::SoftBody::SoftBody::ClusterDAImpulse(Cluster^ cluster, Vector3 impulse)
{
	VECTOR3_DEF(impulse);
	btSoftBody::clusterDAImpulse(cluster->_native, VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

void BulletSharp::SoftBody::SoftBody::ClusterAImpulse(Cluster^ cluster, Impulse^ impulse)
{
	btSoftBody::clusterAImpulse(cluster->_native, *impulse->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::ClusterDCImpulse(Cluster^ cluster, Vector3 impulse)
{
	VECTOR3_DEF(impulse);
	btSoftBody::clusterDCImpulse(cluster->_native, VECTOR3_USE(impulse));
	VECTOR3_DEL(impulse);
}

bool BulletSharp::SoftBody::SoftBody::CutLink(int node0, int node1, btScalar position)
{
	return Native->cutLink(node0, node1, position);
}

bool BulletSharp::SoftBody::SoftBody::CutLink(Node^ node0, Node^ node1, btScalar position)
{
	return Native->cutLink((btSoftBody::Node*)node0->_native, (btSoftBody::Node*)node1->_native, position);
}

void BulletSharp::SoftBody::SoftBody::DampClusters()
{
	Native->dampClusters();
}

void BulletSharp::SoftBody::SoftBody::DefaultCollisionHandler(CollisionObjectWrapper^ pco)
{
	Native->defaultCollisionHandler(pco->_native);
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
	btVector3* result = new btVector3();
	SoftBody_EvaluateCom(Native, result);
	Vector3 ret = Math::BtVector3ToVector3(result);
	delete result;
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
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	Native->getAabb(*aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete aabbMinTemp;
	delete aabbMaxTemp;
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

btScalar BulletSharp::SoftBody::SoftBody::GetMass(int node)
{
	return Native->getMass(node);
}

void BulletSharp::SoftBody::SoftBody::IndicesToPointers()
{
	Native->indicesToPointers();
}

void BulletSharp::SoftBody::SoftBody::InitDefaults()
{
	Native->initDefaults();
}

void BulletSharp::SoftBody::SoftBody::IntegrateMotion()
{
	Native->integrateMotion();
}

void BulletSharp::SoftBody::SoftBody::InitializeClusters()
{
	Native->initializeClusters();
}

void BulletSharp::SoftBody::SoftBody::InitializeFaceTree()
{
	Native->initializeFaceTree();
}

void BulletSharp::SoftBody::SoftBody::PointersToIndices()
{
	Native->pointersToIndices();
}

void BulletSharp::SoftBody::SoftBody::PredictMotion(btScalar dt)
{
	Native->predictMotion(dt);
}

void BulletSharp::SoftBody::SoftBody::PrepareClusters(int iterations)
{
	Native->prepareClusters(iterations);
}

void BulletSharp::SoftBody::SoftBody::RandomizeConstraints()
{
	Native->randomizeConstraints();
}

bool BulletSharp::SoftBody::SoftBody::RayTest(Vector3 rayFrom, Vector3 rayTo, SRayCast^ results)
{
	VECTOR3_DEF(rayFrom);
	VECTOR3_DEF(rayTo);

	bool ret = Native->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *results->UnmanagedPointer);

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	return ret;
}

void BulletSharp::SoftBody::SoftBody::Refine(ImplicitFn^ ifn, btScalar accurary, bool cut)
{
	Native->refine(ifn->UnmanagedPointer, accurary, cut);
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
	btQuaternion* rotationTemp = Math::QuaternionToBtQuat(rotation);
	Native->rotate(*rotationTemp);
	delete rotationTemp;
}

void BulletSharp::SoftBody::SoftBody::Scale(Vector3 scale)
{
	VECTOR3_DEF(scale);
	Native->scale(VECTOR3_USE(scale));
	VECTOR3_DEL(scale);
}

void BulletSharp::SoftBody::SoftBody::SetMass(int node, btScalar mass)
{
	Native->setMass(node, mass);
}

void BulletSharp::SoftBody::SoftBody::SetPose(bool bVolume, bool bFrame)
{
	Native->setPose(bVolume, bFrame);
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
	VECTOR3_DEF(velocity);
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

void BulletSharp::SoftBody::SoftBody::SolveClusters(btScalar sor)
{
	Native->solveClusters(sor);
}

void BulletSharp::SoftBody::SoftBody::SolveClusters(AlignedSoftBodyArray^ bodies)
{
	btSoftBody::solveClusters(*(btSoftBody::tSoftBodyArray*)bodies->_native);
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
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	Native->transform(*transformTemp);
	delete transformTemp;
}

void BulletSharp::SoftBody::SoftBody::Translate(Vector3 translation)
{
	VECTOR3_DEF(translation);
	Native->translate(VECTOR3_USE(translation));
	VECTOR3_DEL(translation);
}

void BulletSharp::SoftBody::SoftBody::Translate(btScalar x, btScalar y, btScalar z)
{
	Translate(Vector3(x,y,z));
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

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::SoftBody::Upcast(CollisionObject^ colObj)
{
	btSoftBody* body = btSoftBody::upcast(colObj->_native);
	return (BulletSharp::SoftBody::SoftBody^)CollisionObject::GetManaged(body);
}

AlignedAnchorArray^ BulletSharp::SoftBody::SoftBody::Anchors::get()
{
	return gcnew AlignedAnchorArray(&Native->m_anchors);
}

Vector3Array^ BulletSharp::SoftBody::SoftBody::Bounds::get()
{
	return gcnew Vector3Array(Native->m_bounds, 2);
}

AlignedClusterArray^ BulletSharp::SoftBody::SoftBody::Clusters::get()
{
	return gcnew AlignedClusterArray(&Native->m_clusters);
}

Config^ BulletSharp::SoftBody::SoftBody::Cfg::get()
{
	return gcnew Config(&Native->m_cfg);
}

int BulletSharp::SoftBody::SoftBody::ClusterCount::get()
{
	return Native->clusterCount();
}

AlignedCollisionObjectArray^ BulletSharp::SoftBody::SoftBody::CollisionDisabledObjects::get()
{
	return gcnew AlignedCollisionObjectArray((btAlignedObjectArray<btCollisionObject*>*)&Native->m_collisionDisabledObjects);
}

AlignedFaceArray^ BulletSharp::SoftBody::SoftBody::Faces::get()
{
	ReturnCachedObjectStatic(AlignedFaceArray, _faces, &Native->m_faces);
}

AlignedJointArray^ BulletSharp::SoftBody::SoftBody::Joints::get()
{
	ReturnCachedObjectStatic(AlignedJointArray, _joints, &Native->m_joints);
}

AlignedLinkArray^ BulletSharp::SoftBody::SoftBody::Links::get()
{
	ReturnCachedObjectStatic(AlignedLinkArray, _links, &Native->m_links);
}

Matrix BulletSharp::SoftBody::SoftBody::InitialWorldTransform::get()
{
	return Math::BtTransformToMatrix(&Native->m_initialWorldTransform);
}
void BulletSharp::SoftBody::SoftBody::InitialWorldTransform::set(Matrix value)
{
	return Math::MatrixToBtTransform(value, &Native->m_initialWorldTransform);
}

AlignedMaterialArray^ BulletSharp::SoftBody::SoftBody::Materials::get()
{
	ReturnCachedObjectStatic(AlignedMaterialArray, _materials, &Native->m_materials);
}

BulletSharp::SoftBody::AlignedNodeArray^ BulletSharp::SoftBody::SoftBody::Nodes::get()
{
	ReturnCachedObjectStatic(AlignedNodeArray, _nodes, &Native->m_nodes);
}

BulletSharp::SoftBody::AlignedNoteArray^ BulletSharp::SoftBody::SoftBody::Notes::get()
{
	ReturnCachedObjectStatic(AlignedNoteArray, _notes, &Native->m_notes);
}

BulletSharp::SoftBody::Pose^ BulletSharp::SoftBody::SoftBody::Pose::get()
{
	return gcnew BulletSharp::SoftBody::Pose(&Native->m_pose);
}

btScalar BulletSharp::SoftBody::SoftBody::RestLengthScale::get()
{
	return Native->getRestLengthScale();
}
void BulletSharp::SoftBody::SoftBody::RestLengthScale::set(btScalar value)
{
	Native->setRestLengthScale(value);
}

BulletSharp::SoftBody::AlignedRigidContactArray^ BulletSharp::SoftBody::SoftBody::RigidContacts::get()
{
	return gcnew AlignedRigidContactArray(&Native->m_rcontacts);
}

SoftBodySolver^ BulletSharp::SoftBody::SoftBody::SoftBodySolver::get()
{
	return gcnew BulletSharp::SoftBody::SoftBodySolver(Native->getSoftBodySolver());
}
void BulletSharp::SoftBody::SoftBody::SoftBodySolver::set(BulletSharp::SoftBody::SoftBodySolver^ value)
{
	Native->setSoftBodySolver(value->UnmanagedPointer);
}

BulletSharp::SoftBody::AlignedSoftContactArray^ BulletSharp::SoftBody::SoftBody::SoftContacts::get()
{
	return gcnew AlignedSoftContactArray(&Native->m_scontacts);
}

SolverState^ BulletSharp::SoftBody::SoftBody::SolverState::get()
{
	return gcnew BulletSharp::SoftBody::SolverState(&Native->m_sst);
}
void BulletSharp::SoftBody::SoftBody::SolverState::set(BulletSharp::SoftBody::SolverState^ value)
{
	Native->m_sst = *value->UnmanagedPointer;
}

Object^ BulletSharp::SoftBody::SoftBody::Tag::get()
{
	void* obj = Native->m_tag;
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}
void BulletSharp::SoftBody::SoftBody::Tag::set(Object^ value)
{
	void* obj = Native->m_tag;
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	Native->m_tag = GCHandleToVoidPtr(handle);
}

BulletSharp::SoftBody::AlignedTetraArray^ BulletSharp::SoftBody::SoftBody::Tetras::get()
{
	ReturnCachedObjectStatic(AlignedTetraArray, _tetras, &Native->m_tetras);
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
	return gcnew AlignedIntArray(&Native->m_userIndexMapping);
}

btScalar BulletSharp::SoftBody::SoftBody::Volume::get()
{
	return Native->getVolume();
}

Vector3 BulletSharp::SoftBody::SoftBody::WindVelocity::get()
{
	return Math::BtVector3ToVector3(&Native->getWindVelocity());
}
void BulletSharp::SoftBody::SoftBody::WindVelocity::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Native->setWindVelocity(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

SoftBodyWorldInfo^ BulletSharp::SoftBody::SoftBody::WorldInfo::get()
{
	if (_worldInfo == nullptr)
	{
		_worldInfo = gcnew SoftBodyWorldInfo(Native->getWorldInfo());
	}
	return _worldInfo;
}
void BulletSharp::SoftBody::SoftBody::WorldInfo::set(SoftBodyWorldInfo^ value)
{
	Native->m_worldInfo = value->_native;
	_worldInfo = value;
}

#ifndef DISABLE_DBVT
Dbvt^ BulletSharp::SoftBody::SoftBody::ClusterDbvt::get()
{
	return gcnew Dbvt(&Native->m_cdbvt);
}
void BulletSharp::SoftBody::SoftBody::ClusterDbvt::set(Dbvt^ value)
{
	Native->m_cdbvt = *value->UnmanagedPointer;
}

Dbvt^ BulletSharp::SoftBody::SoftBody::FaceDbvt::get()
{
	return gcnew Dbvt(&Native->m_fdbvt);
}
void BulletSharp::SoftBody::SoftBody::FaceDbvt::set(Dbvt^ value)
{
	Native->m_fdbvt = *value->UnmanagedPointer;
}

Dbvt^ BulletSharp::SoftBody::SoftBody::NodeDbvt::get()
{
	return gcnew Dbvt(&Native->m_ndbvt);
}
void BulletSharp::SoftBody::SoftBody::NodeDbvt::set(Dbvt^ value)
{
	Native->m_ndbvt = *value->UnmanagedPointer;
}
#endif

#endif
