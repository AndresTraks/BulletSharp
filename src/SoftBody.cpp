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
	_info = info;
}

SoftBodyWorldInfo::SoftBodyWorldInfo()
{
	_info = SoftBodyWorldInfo_New();
}

btScalar SoftBodyWorldInfo::AirDensity::get()
{
	return _info->air_density;
}
void SoftBodyWorldInfo::AirDensity::set(btScalar value)
{
	_info->air_density = value;
}

BroadphaseInterface^ SoftBodyWorldInfo::Broadphase::get()
{
	if (_info->m_broadphase == nullptr)
		return nullptr;
	return gcnew BroadphaseInterface(_info->m_broadphase);
}
void SoftBodyWorldInfo::Broadphase::set(BroadphaseInterface^ value)
{
	_info->m_broadphase = GetUnmanagedNullable(value);
}

Dispatcher^ SoftBodyWorldInfo::Dispatcher::get()
{
	if (_info->m_dispatcher == nullptr)
		return nullptr;
	return gcnew BulletSharp::Dispatcher(_info->m_dispatcher);
}
void SoftBodyWorldInfo::Dispatcher::set(BulletSharp::Dispatcher^ value)
{
	_info->m_dispatcher = GetUnmanagedNullable(value);
}

Vector3 SoftBodyWorldInfo::Gravity::get()
{
	return Math::BtVector3ToVector3(&_info->m_gravity);
}
void SoftBodyWorldInfo::Gravity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->m_gravity);
}

SparseSdf^ SoftBodyWorldInfo::SparseSdf::get()
{
	return gcnew BulletSharp::SparseSdf(&_info->m_sparsesdf);
}

btScalar SoftBodyWorldInfo::WaterDensity::get()
{
	return _info->water_density;
}
void SoftBodyWorldInfo::WaterDensity::set(btScalar value)
{
	_info->water_density = value;
}

Vector3 SoftBodyWorldInfo::WaterNormal::get()
{
	return Math::BtVector3ToVector3(&_info->water_normal);
}
void SoftBodyWorldInfo::WaterNormal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_info->water_normal);
}

btScalar SoftBodyWorldInfo::WaterOffset::get()
{
	return _info->water_offset;
}
void SoftBodyWorldInfo::WaterOffset::set(btScalar value)
{
	_info->water_offset = value;
}

btSoftBodyWorldInfo* SoftBodyWorldInfo::UnmanagedPointer::get()
{
	return _info;
}
void SoftBodyWorldInfo::UnmanagedPointer::set(btSoftBodyWorldInfo* value)
{
	_info = value;
}


Anchor::Anchor(btSoftBody::Anchor* anchor)
{
	_anchor = anchor;
}

Anchor::Anchor()
{
	_anchor = new btSoftBody::Anchor();
}

RigidBody^ Anchor::Body::get()
{
	btRigidBody* body = _anchor->m_body;
	ReturnCachedObjectUpcast((RigidBody^)CollisionObject, _body, body);
}
void Anchor::Body::set(RigidBody^ value)
{
	_anchor->m_body = GetUnmanagedNullable(value);
}

Matrix Anchor::C0::get()
{
	return Math::BtMatrix3x3ToMatrix(&_anchor->m_c0);
}
void Anchor::C0::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_anchor->m_c0);
}

Vector3 Anchor::C1::get()
{
	return Math::BtVector3ToVector3(&_anchor->m_c1);
}
void Anchor::C1::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_anchor->m_c1);
}

btScalar Anchor::C2::get()
{
	return _anchor->m_c2;
}
void Anchor::C2::set(btScalar value)
{
	_anchor->m_c2 = value;
}

Vector3 Anchor::Local::get()
{
	return Math::BtVector3ToVector3(&_anchor->m_local);
}
void Anchor::Local::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_anchor->m_local);
}

btScalar Anchor::Influence::get()
{
	return _anchor->m_influence;
}
void Anchor::Influence::set(btScalar value)
{
	_anchor->m_influence = value;
}

BulletSharp::SoftBody::Node^ Anchor::Node::get()
{
	if (_anchor->m_node == nullptr)
		return nullptr;
	return gcnew BulletSharp::SoftBody::Node(_anchor->m_node);
}
void Anchor::Node::set(BulletSharp::SoftBody::Node^ value)
{
	_anchor->m_node = (btSoftBody::Node*)GetUnmanagedNullableNew(value);
}

btSoftBody::Anchor* Anchor::UnmanagedPointer::get()
{
	return _anchor;
}
void Anchor::UnmanagedPointer::set(btSoftBody::Anchor* value)
{
	_anchor = value;
}


Body::Body(btSoftBody::Body* body)
{
	_body = body;
}

Body::Body()
{
	_body = new btSoftBody::Body();
}

Body::Body(Cluster^ p)
{
	_body = new btSoftBody::Body(p->UnmanagedPointer);
}

Body::Body(BulletSharp::CollisionObject^ colObj)
{
	_body = new btSoftBody::Body(GetUnmanagedNullable(colObj));
}

void Body::Activate()
{
	_body->activate();
}

void Body::ApplyDImpulse(Vector3 impulse, Vector3 rPos)
{
	btVector3* impulseTemp = Math::Vector3ToBtVector3(impulse);
	btVector3* rPosTemp = Math::Vector3ToBtVector3(rPos);
	_body->applyDImpulse(*impulseTemp, *rPosTemp);
	delete impulseTemp;
	delete rPosTemp;
}

void Body::ApplyImpulse(Impulse^ impulse, Vector3 rPos)
{
	btVector3* rPosTemp = Math::Vector3ToBtVector3(rPos);
	_body->applyImpulse(*impulse->UnmanagedPointer, *rPosTemp);
	delete rPosTemp;
}

void Body::ApplyVAImpulse(Vector3 impulse)
{
	btVector3* impulseTemp = Math::Vector3ToBtVector3(impulse);
	_body->applyVAImpulse(*impulseTemp);
	delete impulseTemp;
}

void Body::ApplyDAImpulse(Vector3 impulse)
{
	btVector3* impulseTemp = Math::Vector3ToBtVector3(impulse);
	_body->applyDAImpulse(*impulseTemp);
	delete impulseTemp;
}

void Body::ApplyAImpulse(Impulse^ impulse)
{
	_body->applyAImpulse(*impulse->UnmanagedPointer);
}

void Body::ApplyDCImpulse(Vector3 impulse)
{
	btVector3* impulseTemp = Math::Vector3ToBtVector3(impulse);
	_body->applyDCImpulse(*impulseTemp);
	delete impulseTemp;
}

void Body_GetAngularVelocity(btSoftBody::Body* body, btVector3* rpos, btVector3* velocity)
{
	*velocity = body->angularVelocity(*rpos);
}
Vector3 Body::GetAngularVelocity(Vector3 rPos)
{
	btVector3* rposTemp = Math::Vector3ToBtVector3(rPos);
	btVector3* velocityTemp = new btVector3;
	Body_GetAngularVelocity(_body, rposTemp, velocityTemp);
	delete rposTemp;
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
	btVector3* rposTemp = Math::Vector3ToBtVector3(rPos);
	btVector3* velocityTemp = new btVector3;
	Body_GetVelocity(_body, rposTemp, velocityTemp);
	delete rposTemp;
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
	Body_GetAngularVelocity(_body, velocityTemp);
	return Math::BtVector3ToVector3(velocityTemp);
}

CollisionObject^ Body::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_body->m_collisionObject);
}
void Body::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_body->m_collisionObject = GetUnmanagedNullable(value);
}

btScalar Body::InvMass::get()
{
	return _body->invMass();
}

Matrix Body::InvWorldInertia::get()
{
	return Math::BtMatrix3x3ToMatrix(&_body->invWorldInertia());
}

void Body_GetLinearVelocity(btSoftBody::Body* body, btVector3* velocity)
{
	*velocity = body->linearVelocity();
}
Vector3 Body::LinearVelocity::get()
{
	btVector3* velocityTemp = new btVector3;
	Body_GetLinearVelocity(_body, velocityTemp);
	Vector3 velocity = Math::BtVector3ToVector3(velocityTemp);
	delete velocityTemp;
	return velocity;
}

RigidBody^ Body::Rigid::get()
{
	return (RigidBody^)BulletSharp::CollisionObject::GetManaged(_body->m_rigid);
}
void Body::Rigid::set(RigidBody^ value)
{
	_body->m_rigid = GetUnmanagedNullable(value);
}

Cluster^ Body::Soft::get()
{
	if (_body->m_soft == 0)
		return nullptr;
	return gcnew Cluster(_body->m_soft);
}
void Body::Soft::set(Cluster^ value)
{
	_body->m_soft = GetUnmanagedNullable(value);
}

Matrix Body::XForm::get()
{
	return Math::BtTransformToMatrix(&_body->xform());
}

btSoftBody::Body* Body::UnmanagedPointer::get()
{
	return _body;
}
void Body::UnmanagedPointer::set(btSoftBody::Body* value)
{
	_body = value;
}


Cluster::Cluster(btSoftBody::Cluster* cluster)
{
	_cluster = cluster;
}

Cluster::Cluster()
{
	_cluster = new btSoftBody::Cluster();
}

btScalar Cluster::AngularDamping::get()
{
	return _cluster->m_adamping;
}
void Cluster::AngularDamping::set(btScalar value)
{
	_cluster->m_adamping = value;
}

Vector3 Cluster::AV::get()
{
	return Math::BtVector3ToVector3(&_cluster->m_av);
}
void Cluster::AV::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_cluster->m_av);
}

int Cluster::ClusterIndex::get()
{
	return _cluster->m_clusterIndex;
}
void Cluster::ClusterIndex::set(int value)
{
	_cluster->m_clusterIndex = value;
}

bool Cluster::Collide::get()
{
	return _cluster->m_collide;
}
void Cluster::Collide::set(bool value)
{
	_cluster->m_collide = value;
}

Vector3 Cluster::Com::get()
{
	return Math::BtVector3ToVector3(&_cluster->m_com);
}
void Cluster::Com::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_cluster->m_com);
}

bool Cluster::ContainsAnchor::get()
{
	return _cluster->m_containsAnchor;
}
void Cluster::ContainsAnchor::set(bool value)
{
	_cluster->m_containsAnchor = value;
}

Vector3Array^ Cluster::DImpulses::get()
{
	return gcnew Vector3Array(_cluster->m_dimpulses, 2);
}

AlignedVector3Array^ Cluster::FrameRefs::get()
{
	return gcnew AlignedVector3Array(&_cluster->m_framerefs);
}

Matrix Cluster::FrameXForm::get()
{
	return Math::BtTransformToMatrix(&_cluster->m_framexform);
}
void Cluster::FrameXForm::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_cluster->m_framexform);
}

btScalar Cluster::IDMass::get()
{
	return _cluster->m_idmass;
}
void Cluster::IDMass::set(btScalar value)
{
	_cluster->m_idmass = value;
}

btScalar Cluster::IMass::get()
{
	return _cluster->m_imass;
}
void Cluster::IMass::set(btScalar value)
{
	_cluster->m_imass = value;
}

Matrix Cluster::InvWI::get()
{
	return Math::BtMatrix3x3ToMatrix(&_cluster->m_invwi);
}
void Cluster::InvWI::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_cluster->m_invwi);
}

#ifndef DISABLE_DBVT
DbvtNode^ Cluster::Leaf::get()
{
	if (_cluster->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(_cluster->m_leaf);
}
void Cluster::Leaf::set(DbvtNode^ value)
{
	_cluster->m_leaf = GetUnmanagedNullable(value);
}
#endif

btScalar Cluster::LinearDamping::get()
{
	return _cluster->m_ldamping;
}
void Cluster::LinearDamping::set(btScalar value)
{
	_cluster->m_ldamping = value;
}

Matrix Cluster::Locii::get()
{
	return Math::BtMatrix3x3ToMatrix(&_cluster->m_locii);
}
void Cluster::Locii::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_cluster->m_locii);
}

Vector3 Cluster::LV::get()
{
	return Math::BtVector3ToVector3(&_cluster->m_lv);
}
void Cluster::LV::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_cluster->m_lv);
}

AlignedScalarArray^ Cluster::Masses::get()
{
	return gcnew AlignedScalarArray(&_cluster->m_masses);
}

btScalar Cluster::Matching::get()
{
	return _cluster->m_matching;
}
void Cluster::Matching::set(btScalar value)
{
	_cluster->m_matching = value;
}

btScalar Cluster::MaxSelfCollisionImpulse::get()
{
	return _cluster->m_maxSelfCollisionImpulse;
}
void Cluster::MaxSelfCollisionImpulse::set(btScalar value)
{
	_cluster->m_maxSelfCollisionImpulse = value;
}

int Cluster::NDImpulses::get()
{
	return _cluster->m_ndimpulses;
}

btScalar Cluster::NodeDamping::get()
{
	return _cluster->m_ndamping;
}
void Cluster::NodeDamping::set(btScalar value)
{
	_cluster->m_ndamping = value;
}

AlignedNodePtrArray^ Cluster::Nodes::get()
{
	return gcnew AlignedNodePtrArray(&_cluster->m_nodes);
}

int Cluster::NVImpulses::get()
{
	return _cluster->m_nvimpulses;
}

btScalar Cluster::SelfCollisionImpulseFactor::get()
{
	return _cluster->m_selfCollisionImpulseFactor;
}
void Cluster::SelfCollisionImpulseFactor::set(btScalar value)
{
	_cluster->m_selfCollisionImpulseFactor = value;
}

Vector3Array^ Cluster::VImpulses::get()
{
	return gcnew Vector3Array(_cluster->m_vimpulses, 2);
}

btSoftBody::Cluster* Cluster::UnmanagedPointer::get()
{
	return _cluster;
}
void Cluster::UnmanagedPointer::set(btSoftBody::Cluster* value)
{
	_cluster = value;
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
	return UnmanagedPointer->piterations;
}
void Config::PIterations::set(int value)
{
	UnmanagedPointer->piterations = value;
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
	_unmanaged = element;
}

Element::Element()
{
	_unmanaged = new btSoftBody::Element();
}

Object^ Element::Tag::get()
{
	void* obj = _unmanaged->m_tag;
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}
void Element::Tag::set(Object^ value)
{
	void* obj = _unmanaged->m_tag;
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_unmanaged->m_tag = GCHandleToVoidPtr(handle);
}


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
	if (((btSoftBody::Feature*)_unmanaged)->m_material == 0)
		return nullptr;
	return gcnew BulletSharp::SoftBody::Material(((btSoftBody::Feature*)_unmanaged)->m_material);
}
void Feature::Material::set(BulletSharp::SoftBody::Material^ value)
{
	((btSoftBody::Feature*)_unmanaged)->m_material = (btSoftBody::Material*)GetUnmanagedNullableNew(value);
}


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
	if (((btSoftBody::Face*)_unmanaged)->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(((btSoftBody::Face*)_unmanaged)->m_leaf);
}
void Face::Leaf::set(DbvtNode^ value)
{
	((btSoftBody::Face*)_unmanaged)->m_leaf = GetUnmanagedNullable(value);
}
#endif

NodePtrArray^ Face::N::get()
{
	ReturnCachedObjectStatic(NodePtrArray, _n, ((btSoftBody::Face*)_unmanaged)->m_n, 3);
}

Vector3 Face::Normal::get()
{
	return Math::BtVector3ToVector3(&((btSoftBody::Face*)_unmanaged)->m_normal);
}
void Face::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Face*)_unmanaged)->m_normal);
}

btScalar Face::RestArea::get()
{
	return ((btSoftBody::Face*)_unmanaged)->m_ra;
}
void Face::RestArea::set(btScalar value)
{
	((btSoftBody::Face*)_unmanaged)->m_ra = value;
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
	return _specs->cfm;
}
void BulletSharp::SoftBody::Joint::Specs::Cfm::set(btScalar value)
{
	_specs->cfm = value;
}

btScalar BulletSharp::SoftBody::Joint::Specs::Erp::get()
{
	return _specs->erp;
}
void BulletSharp::SoftBody::Joint::Specs::Erp::set(btScalar value)
{
	_specs->erp = value;
}

btScalar BulletSharp::SoftBody::Joint::Specs::Split::get()
{
	return _specs->split;
}
void BulletSharp::SoftBody::Joint::Specs::Split::set(btScalar value)
{
	_specs->split = value;
}

btSoftBody::Joint::Specs* BulletSharp::SoftBody::Joint::Specs::UnmanagedPointer::get()
{
	return _specs;
}
void BulletSharp::SoftBody::Joint::Specs::UnmanagedPointer::set(btSoftBody::Joint::Specs* value)
{
	_specs = value;
}


BulletSharp::SoftBody::Joint::Joint(btSoftBody::Joint* joint)
{
	_joint = joint;
}

void BulletSharp::SoftBody::Joint::Prepare(btScalar dt, int iterations)
{
	_joint->Prepare(dt, iterations);
}

void BulletSharp::SoftBody::Joint::Solve(btScalar dt, btScalar sor)
{
	_joint->Solve(dt, sor);
}

void BulletSharp::SoftBody::Joint::Terminate(btScalar dt)
{
	_joint->Terminate(dt);
}

BodyArray^ BulletSharp::SoftBody::Joint::Bodies::get()
{
	return gcnew BodyArray(_joint->m_bodies, 2);
}

btScalar BulletSharp::SoftBody::Joint::Cfm::get()
{
	return _joint->m_cfm;
}
void BulletSharp::SoftBody::Joint::Cfm::set(btScalar value)
{
	_joint->m_cfm = value;
}

bool BulletSharp::SoftBody::Joint::Delete::get()
{
	return _joint->m_delete;
}
void BulletSharp::SoftBody::Joint::Delete::set(bool value)
{
	_joint->m_delete = value;
}

Vector3 BulletSharp::SoftBody::Joint::Drift::get()
{
	return Math::BtVector3ToVector3(&_joint->m_drift);
}
void BulletSharp::SoftBody::Joint::Drift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_joint->m_drift);
}

btScalar BulletSharp::SoftBody::Joint::Erp::get()
{
	return _joint->m_erp;
}
void BulletSharp::SoftBody::Joint::Erp::set(btScalar value)
{
	_joint->m_erp = value;
}

Matrix BulletSharp::SoftBody::Joint::MassMatrix::get()
{
	return Math::BtMatrix3x3ToMatrix(&_joint->m_massmatrix);
}
void BulletSharp::SoftBody::Joint::MassMatrix::set(Matrix value)
{
	Math::MatrixToBtMatrix3x3(value, &_joint->m_massmatrix);
}

Vector3Array^ BulletSharp::SoftBody::Joint::Refs::get()
{
	return gcnew Vector3Array(_joint->m_refs, 2);
}

Vector3 BulletSharp::SoftBody::Joint::SDrift::get()
{
	return Math::BtVector3ToVector3(&_joint->m_sdrift);
}
void BulletSharp::SoftBody::Joint::SDrift::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_joint->m_sdrift);
}

btScalar BulletSharp::SoftBody::Joint::Split::get()
{
	return _joint->m_split;
}
void BulletSharp::SoftBody::Joint::Split::set(btScalar value)
{
	_joint->m_split = value;
}

Joint::JointType BulletSharp::SoftBody::Joint::Type::get()
{
	return (JointType)_joint->Type();
}

btSoftBody::Joint* Joint::UnmanagedPointer::get()
{
	return _joint;
}

void Joint::UnmanagedPointer::set(btSoftBody::Joint* value)
{
	_joint = value;
}


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
	return gcnew Vector3Array(UnmanagedPointer->m_rpos, 2);
}

btSoftBody::LJoint* BulletSharp::SoftBody::LJoint::UnmanagedPointer::get()
{
	return (btSoftBody::LJoint*) Joint::UnmanagedPointer;
}


BulletSharp::SoftBody::LJoint::Specs::Specs()
{
	UnmanagedPointer = new btSoftBody::LJoint::Specs();
}

Vector3 BulletSharp::SoftBody::LJoint::Specs::Position::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->position);
}
void BulletSharp::SoftBody::LJoint::Specs::Position::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->position);
}

btSoftBody::LJoint::Specs* BulletSharp::SoftBody::LJoint::Specs::UnmanagedPointer::get()
{
	return (btSoftBody::LJoint::Specs*)Joint::Specs::UnmanagedPointer;
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


BulletSharp::SoftBody::AJoint::Specs::Specs()
{
	UnmanagedPointer = new btSoftBody::AJoint::Specs();
	AJoint::IControl^ iControl = gcnew AJoint::IControl();
	UnmanagedPointer->icontrol = iControl->UnmanagedPointer;
}

Vector3 BulletSharp::SoftBody::AJoint::Specs::Axis::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->axis);
}
void BulletSharp::SoftBody::AJoint::Specs::Axis::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->axis);
}

AJoint::IControl^ BulletSharp::SoftBody::AJoint::Specs::IControl::get()
{
	return gcnew AJoint::IControl((AJointIControlWrapper*)UnmanagedPointer->icontrol);
}
void BulletSharp::SoftBody::AJoint::Specs::IControl::set(AJoint::IControl^ value)
{
	UnmanagedPointer->icontrol = value->UnmanagedPointer;
}

btSoftBody::AJoint::Specs* BulletSharp::SoftBody::AJoint::Specs::UnmanagedPointer::get()
{
	return (btSoftBody::AJoint::Specs*)Joint::Specs::UnmanagedPointer;
}


void BulletSharp::SoftBody::AJoint::IControl::Prepare(AJoint^ joint)
{
	_iControl->basePrepare(joint->UnmanagedPointer);
}

btScalar BulletSharp::SoftBody::AJoint::IControl::Speed(AJoint^ joint, btScalar current)
{
	return _iControl->baseSpeed(joint->UnmanagedPointer, current);
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


AJoint::AJoint(btSoftBody::AJoint* joint)
: Joint(joint)
{
}

Vector3Array^ AJoint::Axis::get()
{
	return gcnew Vector3Array(UnmanagedPointer->m_axis, 2);
}

AJoint::IControl^ AJoint::Control::get()
{
	return gcnew AJoint::IControl((AJointIControlWrapper*)UnmanagedPointer->m_icontrol);
}
void AJoint::Control::set(AJoint::IControl^ value)
{
	UnmanagedPointer->m_icontrol = value->UnmanagedPointer;
}

btSoftBody::AJoint* BulletSharp::SoftBody::AJoint::UnmanagedPointer::get()
{
	return (btSoftBody::AJoint*)Joint::UnmanagedPointer;
}


CJoint::CJoint(btSoftBody::CJoint* joint)
: Joint(joint)
{
}

btScalar CJoint::Friction::get()
{
	return UnmanagedPointer->m_friction;
}
void CJoint::Friction::set(btScalar value)
{
	UnmanagedPointer->m_friction = value;
}

int CJoint::Life::get()
{
	return UnmanagedPointer->m_life;
}
void CJoint::Life::set(int value)
{
	UnmanagedPointer->m_life = value;
}

int CJoint::MaxLife::get()
{
	return UnmanagedPointer->m_maxlife;
}
void CJoint::MaxLife::set(int value)
{
	UnmanagedPointer->m_maxlife = value;
}

Vector3 CJoint::Normal::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_normal);
}
void CJoint::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_normal);
}

Vector3Array^ CJoint::RPos::get()
{
	return gcnew Vector3Array(UnmanagedPointer->m_rpos, 2);
}

btSoftBody::CJoint* BulletSharp::SoftBody::CJoint::UnmanagedPointer::get()
{
	return (btSoftBody::CJoint*)Joint::UnmanagedPointer;
}


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
	return ((btSoftBody::Link*)_unmanaged)->m_c0;
}
void Link::C0::set(btScalar value)
{
	((btSoftBody::Link*)_unmanaged)->m_c0 = value;
}

btScalar Link::C1::get()
{
	return ((btSoftBody::Link*)_unmanaged)->m_c1;
}
void Link::C1::set(btScalar value)
{
	((btSoftBody::Link*)_unmanaged)->m_c1 = value;
}

btScalar Link::C2::get()
{
	return ((btSoftBody::Link*)_unmanaged)->m_c2;
}
void Link::C2::set(btScalar value)
{
	((btSoftBody::Link*)_unmanaged)->m_c2 = value;
}

Vector3 Link::C3::get()
{
	return Math::BtVector3ToVector3(&((btSoftBody::Link*)_unmanaged)->m_c3);
}
void Link::C3::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Link*)_unmanaged)->m_c3);
}

bool Link::IsBending::get()
{
	return ((btSoftBody::Link*)_unmanaged)->m_bbending != 0;
}
void Link::IsBending::set(bool value)
{
	((btSoftBody::Link*)_unmanaged)->m_bbending = value;
}

NodePtrArray^ Link::Nodes::get()
{
	ReturnCachedObjectStatic(NodePtrArray, _nodePtrArray, ((btSoftBody::Link*)_unmanaged)->m_n, 2);
}

btScalar Link::RestLength::get()
{
	return ((btSoftBody::Link*)_unmanaged)->m_rl;
}
void Link::RestLength::set(btScalar value)
{
	((btSoftBody::Link*)_unmanaged)->m_rl = value;
}


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
	return ((btSoftBody::Material*)_unmanaged)->m_kAST;
}
void BulletSharp::SoftBody::Material::Ast::set(btScalar value)
{
	((btSoftBody::Material*)_unmanaged)->m_kAST = value;
}

FMaterial BulletSharp::SoftBody::Material::Flags::get()
{
	return (FMaterial)((btSoftBody::Material*)_unmanaged)->m_flags;
}
void BulletSharp::SoftBody::Material::Flags::set(FMaterial value)
{
	((btSoftBody::Material*)_unmanaged)->m_flags = (int)value;
}

btScalar BulletSharp::SoftBody::Material::Lst::get()
{
	return ((btSoftBody::Material*)_unmanaged)->m_kLST;
}
void BulletSharp::SoftBody::Material::Lst::set(btScalar value)
{
	((btSoftBody::Material*)_unmanaged)->m_kLST = value;
}

btScalar BulletSharp::SoftBody::Material::Vst::get()
{
	return ((btSoftBody::Material*)_unmanaged)->m_kVST;
}
void BulletSharp::SoftBody::Material::Vst::set(btScalar value)
{
	((btSoftBody::Material*)_unmanaged)->m_kVST = value;
}


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
	BtVector3ToVector3Fast(&((btSoftBody::Node*)_unmanaged)->m_n, normal);
}

void BulletSharp::SoftBody::Node::GetX([Out] Vector3% x)
{
	BtVector3ToVector3Fast(&((btSoftBody::Node*)_unmanaged)->m_x, x);
}

btScalar BulletSharp::SoftBody::Node::Area::get()
{
	return ((btSoftBody::Node*)_unmanaged)->m_area;
}
void BulletSharp::SoftBody::Node::Area::set(btScalar value)
{
	((btSoftBody::Node*)_unmanaged)->m_area = value;
}

Vector3 BulletSharp::SoftBody::Node::Force::get()
{
	return Math::BtVector3ToVector3(&((btSoftBody::Node*)_unmanaged)->m_f);
}
void BulletSharp::SoftBody::Node::Force::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Node*)_unmanaged)->m_f);
}

btScalar BulletSharp::SoftBody::Node::InverseMass::get()
{
	return ((btSoftBody::Node*)_unmanaged)->m_im;
}
void BulletSharp::SoftBody::Node::InverseMass::set(btScalar value)
{
	((btSoftBody::Node*)_unmanaged)->m_im = value;
}

bool BulletSharp::SoftBody::Node::IsAttached::get()
{
	return ((btSoftBody::Node*)_unmanaged)->m_battach != 0;
}
void BulletSharp::SoftBody::Node::IsAttached::set(bool value)
{
	((btSoftBody::Node*)_unmanaged)->m_battach = value;
}

#ifndef DISABLE_DBVT
DbvtNode^ BulletSharp::SoftBody::Node::Leaf::get()
{
	if (((btSoftBody::Node*)_unmanaged)->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(((btSoftBody::Node*)_unmanaged)->m_leaf);
}
void BulletSharp::SoftBody::Node::Leaf::set(DbvtNode^ value)
{
	((btSoftBody::Node*)_unmanaged)->m_leaf = GetUnmanagedNullable(value);
}
#endif

Vector3 BulletSharp::SoftBody::Node::Normal::get()
{
	return Math::BtVector3ToVector3(&((btSoftBody::Node*)_unmanaged)->m_n);
}
void BulletSharp::SoftBody::Node::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Node*)_unmanaged)->m_n);
}

Vector3 BulletSharp::SoftBody::Node::Q::get()
{
	return Math::BtVector3ToVector3(&((btSoftBody::Node*)_unmanaged)->m_q);
}
void BulletSharp::SoftBody::Node::Q::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Node*)_unmanaged)->m_q);
}

Vector3 BulletSharp::SoftBody::Node::Velocity::get()
{
	return Math::BtVector3ToVector3(&((btSoftBody::Node*)_unmanaged)->m_v);
}
void BulletSharp::SoftBody::Node::Velocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Node*)_unmanaged)->m_v);
}

Vector3 BulletSharp::SoftBody::Node::X::get()
{
	return BtVector3ToVector3FastRet(&((btSoftBody::Node*)_unmanaged)->m_x);
}
void BulletSharp::SoftBody::Node::X::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Node*)_unmanaged)->m_x);
}


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
	return gcnew ScalarArray(&((btSoftBody::Note*)_unmanaged)->m_coords[0], 4);
}

NodePtrArray^ Note::Nodes::get()
{
	return gcnew NodePtrArray(&((btSoftBody::Note*)_unmanaged)->m_nodes[0], 4);
}

Vector3 Note::Offset::get()
{
	return Math::BtVector3ToVector3(&((btSoftBody::Note*)_unmanaged)->m_offset);
}
void Note::Offset::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btSoftBody::Note*)_unmanaged)->m_offset);
}

int Note::Rank::get()
{
	return ((btSoftBody::Note*)_unmanaged)->m_rank;
}
void Note::Rank::set(int value)
{
	((btSoftBody::Note*)_unmanaged)->m_rank = value;
}

String^ Note::Text::get()
{
	return StringConv::UnmanagedToManaged(((btSoftBody::Note*)_unmanaged)->m_text);
}
void Note::Text::set(String^ value)
{
	((btSoftBody::Note*)_unmanaged)->m_text = StringConv::ManagedToUnmanaged(value);
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
	_rigidContact->m_node = (btSoftBody::Node*)GetUnmanagedNullableNew(value);
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
	_softContact->m_face = (btSoftBody::Face*)GetUnmanagedNullableNew(value);
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
	_softContact->m_node = (btSoftBody::Node*)GetUnmanagedNullableNew(value);
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
	_rayCast->body = (btSoftBody*)GetUnmanagedNullableNew(value);
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
	return gcnew Vector3Array(((btSoftBody::Tetra*)_unmanaged)->m_c0, 4);
}

btScalar Tetra::C1::get()
{
	return ((btSoftBody::Tetra*)_unmanaged)->m_c1;
}
void Tetra::C1::set(btScalar value)
{
	((btSoftBody::Tetra*)_unmanaged)->m_c1 = value;
}

btScalar Tetra::C2::get()
{
	return ((btSoftBody::Tetra*)_unmanaged)->m_c2;
}
void Tetra::C2::set(btScalar value)
{
	((btSoftBody::Tetra*)_unmanaged)->m_c2 = value;
}

NodePtrArray^ Tetra::Nodes::get()
{
	return gcnew NodePtrArray(((btSoftBody::Tetra*)_unmanaged)->m_n, 4);
}

#ifndef DISABLE_DBVT
DbvtNode^ Tetra::Leaf::get()
{
	if (((btSoftBody::Face*)_unmanaged)->m_leaf == 0)
		return nullptr;
	return gcnew DbvtNode(((btSoftBody::Face*)_unmanaged)->m_leaf);
}
void Tetra::Leaf::set(DbvtNode^ value)
{
	((btSoftBody::Tetra*)_unmanaged)->m_leaf = GetUnmanagedNullable(value);
}
#endif

btScalar Tetra::RestVolume::get()
{
	return ((btSoftBody::Tetra*)_unmanaged)->m_rv;
}
void Tetra::RestVolume::set(btScalar value)
{
	((btSoftBody::Tetra*)_unmanaged)->m_rv = value;
}


#define Unmanaged static_cast<btSoftBody*>(_unmanaged)

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

	UnmanagedPointer = new btSoftBody(worldInfo->UnmanagedPointer, length, (btVector3*)x_ptr, m_ptr);
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

	UnmanagedPointer = new btSoftBody(worldInfo->UnmanagedPointer, length,
		(btVector3*)GetUnmanagedNullableNew(x), (btScalar*)GetUnmanagedNullableNew(m));
}

BulletSharp::SoftBody::SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo)
: CollisionObject(new btSoftBody(worldInfo->UnmanagedPointer))
{
}

void BulletSharp::SoftBody::SoftBody::AddAeroForceToFace(Vector3 windVelocity, int faceIndex)
{
	btVector3* windVelocityTemp = Math::Vector3ToBtVector3(windVelocity);
	Unmanaged->addAeroForceToFace(*windVelocityTemp, faceIndex);
	delete windVelocityTemp;
}

void BulletSharp::SoftBody::SoftBody::AddAeroForceToNode(Vector3 windVelocity, int nodeIndex)
{
	btVector3* windVelocityTemp = Math::Vector3ToBtVector3(windVelocity);
	Unmanaged->addAeroForceToNode(*windVelocityTemp, nodeIndex);
	delete windVelocityTemp;
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force, int node)
{
	btVector3* forceTemp = Math::Vector3ToBtVector3(force);
	Unmanaged->addForce(*forceTemp, node);
	delete forceTemp;
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force)
{
	btVector3* forceTemp = Math::Vector3ToBtVector3(force);
	Unmanaged->addForce(*forceTemp);
	delete forceTemp;
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity, int node)
{
	btVector3* velocityTemp = Math::Vector3ToBtVector3(velocity);
	Unmanaged->addVelocity(*velocityTemp, node);
	delete velocityTemp;
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity)
{
	btVector3* velocityTemp = Math::Vector3ToBtVector3(velocity);
	Unmanaged->addVelocity(*velocityTemp);
	delete velocityTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies, btScalar influence)
{
	Unmanaged->appendAnchor(node, body->UnmanagedPointer, disableCollisionBetweenLinkedBodies, influence);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies)
{
	Unmanaged->appendAnchor(node, body->UnmanagedPointer, disableCollisionBetweenLinkedBodies);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body)
{
	Unmanaged->appendAnchor(node, body->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, Vector3 localPivot, bool disableCollisionBetweenLinkedBodies)
{
	btVector3* localPivotTemp = Math::Vector3ToBtVector3(localPivot);
	Unmanaged->appendAnchor(node, body->UnmanagedPointer, *localPivotTemp, disableCollisionBetweenLinkedBodies);
	delete localPivotTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, Vector3 localPivot)
{
	btVector3* localPivotTemp = Math::Vector3ToBtVector3(localPivot);
	Unmanaged->appendAnchor(node, body->UnmanagedPointer, *localPivotTemp);
	delete localPivotTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int node0, int node1, int node2, Material^ material)
{
	Unmanaged->appendFace(node0, node1, node2, (btSoftBody::Material*)material->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int node0, int node1, int node2)
{
	Unmanaged->appendFace(node0, node1, node2);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int model, Material^ material)
{
	Unmanaged->appendFace(model, (btSoftBody::Material*)material->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendFace(int model)
{
	Unmanaged->appendFace(model);
}

void BulletSharp::SoftBody::SoftBody::AppendFace()
{
	Unmanaged->appendFace();
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, Cluster^ body0, Body^ body1)
{
	Unmanaged->appendLinearJoint(*specs->UnmanagedPointer, body0->UnmanagedPointer, *body1->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, Body^ body1)
{
	Unmanaged->appendLinearJoint(*specs->UnmanagedPointer, *body1->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs)
{
	Unmanaged->appendLinearJoint(*specs->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::AppendLinearJoint(LJoint::Specs^ specs, SoftBody^ body1)
{
	Unmanaged->appendLinearJoint(*specs->UnmanagedPointer, (btSoftBody*)body1->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, Cluster^ body0, Body^ body1)
{
	Unmanaged->appendAngularJoint(*specs->UnmanagedPointer, body0->UnmanagedPointer, *body1->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, Body^ body1)
{
	Unmanaged->appendAngularJoint(*specs->UnmanagedPointer, *body1->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs)
{
	Unmanaged->appendAngularJoint(*specs->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::AppendAngularJoint(AJoint::Specs^ specs, SoftBody^ body1)
{
	Unmanaged->appendAngularJoint(*specs->UnmanagedPointer, (btSoftBody*)body1->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1, Material^ material, bool bCheckExist)
{
	Unmanaged->appendLink(node0, node1, (btSoftBody::Material*)material->_unmanaged, bCheckExist);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1, Material^ material)
{
	Unmanaged->appendLink(node0, node1, (btSoftBody::Material*)material->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int node0, int node1)
{
	Unmanaged->appendLink(node0, node1);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1, Material^ material, bool bCheckExist)
{
	Unmanaged->appendLink((btSoftBody::Node*)node0->_unmanaged, (btSoftBody::Node*)node1->_unmanaged, (btSoftBody::Material*)material->_unmanaged, bCheckExist);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1, Material^ material)
{
	Unmanaged->appendLink((btSoftBody::Node*)node0->_unmanaged, (btSoftBody::Node*)node1->_unmanaged, (btSoftBody::Material*)material->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(Node^ node0, Node^ node1)
{
	Unmanaged->appendLink((btSoftBody::Node*)node0->_unmanaged, (btSoftBody::Node*)node1->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int model, Material^ material)
{
	Unmanaged->appendLink(model, (btSoftBody::Material*)material->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendLink(int model)
{
	Unmanaged->appendLink(model);
}

void BulletSharp::SoftBody::SoftBody::AppendLink()
{
	Unmanaged->appendLink();
}

BulletSharp::SoftBody::Material^ BulletSharp::SoftBody::SoftBody::AppendMaterial()
{
	return gcnew Material(Unmanaged->appendMaterial());
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2, Node^ n3)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Unmanaged->appendNote(textTemp, *oTemp, *cTemp, (btSoftBody::Node*)n0->_unmanaged, (btSoftBody::Node*)n1->_unmanaged,
		(btSoftBody::Node*)n2->_unmanaged, (btSoftBody::Node*)n3->_unmanaged);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Unmanaged->appendNote(textTemp, *oTemp, *cTemp, (btSoftBody::Node*)n0->_unmanaged, (btSoftBody::Node*)n1->_unmanaged,
		(btSoftBody::Node*)n2->_unmanaged);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Unmanaged->appendNote(textTemp, *oTemp, *cTemp, (btSoftBody::Node*)n0->_unmanaged, (btSoftBody::Node*)n1->_unmanaged);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Unmanaged->appendNote(textTemp, *oTemp, *cTemp, (btSoftBody::Node*)n0->_unmanaged);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Vector4 c)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);
	btVector4* cTemp = Math::Vector4ToBtVector4(c);

	Unmanaged->appendNote(textTemp, *oTemp, *cTemp);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
	delete cTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNode(Vector3 x, btScalar m)
{
	btVector3* xTemp = Math::Vector3ToBtVector3(x);
	Unmanaged->appendNode(*xTemp, m);
	delete xTemp;
}

void SoftBody_AppendNote(btSoftBody* body, const char* text, btVector3* c)
{
	body->appendNote(text, *c);
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);

	SoftBody_AppendNote(Unmanaged, textTemp, oTemp);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Node^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);

	Unmanaged->appendNote(textTemp, *oTemp, (btSoftBody::Node*)feature->_unmanaged);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Link^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);

	Unmanaged->appendNote(textTemp, *oTemp, (btSoftBody::Link*)feature->_unmanaged);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendNote(String^ text, Vector3 o, Face^ feature)
{
	const char* textTemp = StringConv::ManagedToUnmanaged(text);
	btVector3* oTemp = Math::Vector3ToBtVector3(o);

	Unmanaged->appendNote(textTemp, *oTemp, (btSoftBody::Face*)feature->_unmanaged);

	StringConv::FreeUnmanagedString(textTemp);
	delete oTemp;
}

void BulletSharp::SoftBody::SoftBody::AppendTetra(int model, Material^ material)
{
	Unmanaged->appendTetra(model, (btSoftBody::Material*)material->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendTetra(int node0, int node1, int node2, int node3, Material^ material)
{
	Unmanaged->appendTetra(node0, node1, node2, node3, (btSoftBody::Material*)material->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::AppendTetra(int node0, int node1, int node2, int node3)
{
	Unmanaged->appendTetra(node0, node1, node2, node3);
}

void BulletSharp::SoftBody::SoftBody::ApplyClusters(bool drift)
{
	Unmanaged->applyClusters(drift);
}

void BulletSharp::SoftBody::SoftBody::ApplyForces()
{
	Unmanaged->applyForces();
}

bool BulletSharp::SoftBody::SoftBody::CheckFace(int node0, int node1, int node2)
{
	return Unmanaged->checkFace(node0, node1, node2);
}

bool BulletSharp::SoftBody::SoftBody::CheckLink(int node0, int node1)
{
	return Unmanaged->checkLink(node0, node1);
}

bool BulletSharp::SoftBody::SoftBody::CheckLink(Node^ node0, Node^ node1)
{
	return Unmanaged->checkLink((btSoftBody::Node*)node0->_unmanaged, (btSoftBody::Node*)node1->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::CleanupClusters()
{
	Unmanaged->cleanupClusters();
}

void SoftBody_ClusterCOM(btSoftBody::Cluster* cluster, btVector3* com)
{
	*com = btSoftBody::clusterCom(cluster);
}
Vector3 BulletSharp::SoftBody::SoftBody::ClusterCom(Cluster^ cluster)
{
	btVector3* tempClusterCom = new btVector3;
	SoftBody_ClusterCOM(cluster->UnmanagedPointer, tempClusterCom);
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
	SoftBody_ClusterCOM(UnmanagedPointer, cluster, tempClusterCom);
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
	btVector3* tempRpos = Math::Vector3ToBtVector3(rpos);
	SoftBody_ClusterVelocity(cluster->UnmanagedPointer, tempRpos, tempVelocity);
	Vector3 velocity = Math::BtVector3ToVector3(tempVelocity);
	delete tempVelocity;
	delete tempRpos;
	return velocity;
}

void BulletSharp::SoftBody::SoftBody::ClusterVImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse)
{
	btVector3* tempRpos = Math::Vector3ToBtVector3(rpos);
	btVector3* tempImpulse = Math::Vector3ToBtVector3(impulse);
	btSoftBody::clusterVImpulse(cluster->UnmanagedPointer, *tempRpos, *tempImpulse);
	delete tempRpos;
	delete tempImpulse;
}

void BulletSharp::SoftBody::SoftBody::ClusterDImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse)
{
	btVector3* tempRpos = Math::Vector3ToBtVector3(rpos);
	btVector3* tempImpulse = Math::Vector3ToBtVector3(impulse);
	btSoftBody::clusterDImpulse(cluster->UnmanagedPointer, *tempRpos, *tempImpulse);
	delete tempRpos;
	delete tempImpulse;
}

void BulletSharp::SoftBody::SoftBody::ClusterImpulse(Cluster^ cluster, Vector3 rpos, Impulse^ impulse)
{
	btVector3* tempRpos = Math::Vector3ToBtVector3(rpos);
	btSoftBody::clusterImpulse(cluster->UnmanagedPointer, *tempRpos, *impulse->UnmanagedPointer);
	delete tempRpos;
}

void BulletSharp::SoftBody::SoftBody::ClusterVAImpulse(Cluster^ cluster, Vector3 impulse)
{
	btVector3* tempImpulse = Math::Vector3ToBtVector3(impulse);
	btSoftBody::clusterVAImpulse(cluster->UnmanagedPointer, *tempImpulse);
	delete tempImpulse;
}

void BulletSharp::SoftBody::SoftBody::ClusterDAImpulse(Cluster^ cluster, Vector3 impulse)
{
	btVector3* tempImpulse = Math::Vector3ToBtVector3(impulse);
	btSoftBody::clusterDAImpulse(cluster->UnmanagedPointer, *tempImpulse);
	delete tempImpulse;
}

void BulletSharp::SoftBody::SoftBody::ClusterAImpulse(Cluster^ cluster, Impulse^ impulse)
{
	btSoftBody::clusterAImpulse(cluster->UnmanagedPointer, *impulse->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBody::ClusterDCImpulse(Cluster^ cluster, Vector3 impulse)
{
	btVector3* tempImpulse = Math::Vector3ToBtVector3(impulse);
	btSoftBody::clusterDCImpulse(cluster->UnmanagedPointer, *tempImpulse);
	delete tempImpulse;
}

bool BulletSharp::SoftBody::SoftBody::CutLink(int node0, int node1, btScalar position)
{
	return Unmanaged->cutLink(node0, node1, position);
}

bool BulletSharp::SoftBody::SoftBody::CutLink(Node^ node0, Node^ node1, btScalar position)
{
	return Unmanaged->cutLink((btSoftBody::Node*)node0->_unmanaged, (btSoftBody::Node*)node1->_unmanaged, position);
}

void BulletSharp::SoftBody::SoftBody::DampClusters()
{
	Unmanaged->dampClusters();
}

void BulletSharp::SoftBody::SoftBody::DefaultCollisionHandler(CollisionObjectWrapper^ pco)
{
	Unmanaged->defaultCollisionHandler(pco->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::DefaultCollisionHandler(SoftBody^ psb)
{
	Unmanaged->defaultCollisionHandler((btSoftBody*)psb->_unmanaged);
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
	SoftBody_EvaluateCom(Unmanaged, result);
	Vector3 ret = Math::BtVector3ToVector3(result);
	delete result;
	return ret;
}

int BulletSharp::SoftBody::SoftBody::GenerateBendingConstraints(int distance, Material^ material)
{
	return Unmanaged->generateBendingConstraints(distance, (btSoftBody::Material*)material->_unmanaged);
}

int BulletSharp::SoftBody::SoftBody::GenerateBendingConstraints(int distance)
{
	return Unmanaged->generateBendingConstraints(distance);
}

int BulletSharp::SoftBody::SoftBody::GenerateClusters(int k, int maxIterations)
{
	return Unmanaged->generateClusters(k, maxIterations);
}

int BulletSharp::SoftBody::SoftBody::GenerateClusters(int k)
{
	return Unmanaged->generateClusters(k);
}

void BulletSharp::SoftBody::SoftBody::GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	Unmanaged->getAabb(*aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

int BulletSharp::SoftBody::SoftBody::GetFaceVertexData([Out] array<Vector3>^% vertices)
{
	btAlignedObjectArray<btSoftBody::Face>* faceArray = &Unmanaged->m_faces;
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
	btAlignedObjectArray<btSoftBody::Face>* faceArray = &Unmanaged->m_faces;
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
	btAlignedObjectArray<btSoftBody::Face>* faceArray = &Unmanaged->m_faces;
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
	btAlignedObjectArray<btSoftBody::Link>* linkArray = &Unmanaged->m_links;
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
	btAlignedObjectArray<btSoftBody::Link>* linkArray = &Unmanaged->m_links;
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
	btAlignedObjectArray<btSoftBody::Tetra>* tetraArray = &Unmanaged->m_tetras;
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
	btAlignedObjectArray<btSoftBody::Tetra>* tetraArray = &Unmanaged->m_tetras;
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
	btAlignedObjectArray<btSoftBody::Tetra>* tetraArray = &Unmanaged->m_tetras;
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
	if (Unmanaged->m_faces.size()) {
		return GetFaceVertexNormalData(data);
	} else if (Unmanaged->m_tetras.size()) {
		return GetTetraVertexNormalData(data);
	}
	return GetLinkVertexNormalData(data);
}

int BulletSharp::SoftBody::SoftBody::GetVertexNormalData([Out] array<Vector3>^% vertices, [Out] array<Vector3>^% normals)
{
	if (Unmanaged->m_faces.size()) {
		return GetFaceVertexNormalData(vertices, normals);
	} else if (Unmanaged->m_tetras.size()) {
		return GetTetraVertexNormalData(vertices, normals);
	}
	return GetLinkVertexData(vertices);
}

btScalar BulletSharp::SoftBody::SoftBody::GetMass(int node)
{
	return Unmanaged->getMass(node);
}

void BulletSharp::SoftBody::SoftBody::IndicesToPointers()
{
	Unmanaged->indicesToPointers();
}

void BulletSharp::SoftBody::SoftBody::InitDefaults()
{
	Unmanaged->initDefaults();
}

void BulletSharp::SoftBody::SoftBody::IntegrateMotion()
{
	Unmanaged->integrateMotion();
}

void BulletSharp::SoftBody::SoftBody::InitializeClusters()
{
	Unmanaged->initializeClusters();
}

void BulletSharp::SoftBody::SoftBody::InitializeFaceTree()
{
	Unmanaged->initializeFaceTree();
}

void BulletSharp::SoftBody::SoftBody::PointersToIndices()
{
	Unmanaged->pointersToIndices();
}

void BulletSharp::SoftBody::SoftBody::PredictMotion(btScalar dt)
{
	Unmanaged->predictMotion(dt);
}

void BulletSharp::SoftBody::SoftBody::PrepareClusters(int iterations)
{
	Unmanaged->prepareClusters(iterations);
}

void BulletSharp::SoftBody::SoftBody::RandomizeConstraints()
{
	Unmanaged->randomizeConstraints();
}

bool BulletSharp::SoftBody::SoftBody::RayTest(Vector3 rayFrom, Vector3 rayTo, SRayCast^ results)
{
	btVector3* rayFromTemp = Math::Vector3ToBtVector3(rayFrom);
	btVector3* rayToTemp = Math::Vector3ToBtVector3(rayTo);

	bool ret = Unmanaged->rayTest(*rayFromTemp, *rayToTemp, *results->UnmanagedPointer);

	delete rayFromTemp;
	delete rayToTemp;
	return ret;
}

void BulletSharp::SoftBody::SoftBody::Refine(ImplicitFn^ ifn, btScalar accurary, bool cut)
{
	Unmanaged->refine(ifn->UnmanagedPointer, accurary, cut);
}

void BulletSharp::SoftBody::SoftBody::ReleaseCluster(int index)
{
	Unmanaged->releaseCluster(index);
}

void BulletSharp::SoftBody::SoftBody::ReleaseClusters()
{
	Unmanaged->releaseClusters();
}

void BulletSharp::SoftBody::SoftBody::Rotate(Quaternion rotation)
{
	btQuaternion* rotationTemp = Math::QuaternionToBtQuat(rotation);
	Unmanaged->rotate(*rotationTemp);
	delete rotationTemp;
}

void BulletSharp::SoftBody::SoftBody::Scale(Vector3 scale)
{
	btVector3* scaleTemp = Math::Vector3ToBtVector3(scale);
	Unmanaged->scale(*scaleTemp);
	delete scaleTemp;
}

void BulletSharp::SoftBody::SoftBody::SetMass(int node, btScalar mass)
{
	Unmanaged->setMass(node, mass);
}

void BulletSharp::SoftBody::SoftBody::SetPose(bool bVolume, bool bFrame)
{
	Unmanaged->setPose(bVolume, bFrame);
}

void BulletSharp::SoftBody::SoftBody::SetSolver(ESolverPresets preset)
{
	Unmanaged->setSolver((btSoftBody::eSolverPresets::_)preset);
}

void BulletSharp::SoftBody::SoftBody::SetTotalDensity(btScalar density)
{
	Unmanaged->setTotalDensity(density);
}

void BulletSharp::SoftBody::SoftBody::SetTotalMass(btScalar mass, bool fromFaces)
{
	Unmanaged->setTotalMass(mass, fromFaces);
}

void BulletSharp::SoftBody::SoftBody::SetTotalMass(btScalar mass)
{
	Unmanaged->setTotalMass(mass);
}

void BulletSharp::SoftBody::SoftBody::SetVelocity(Vector3 velocity)
{
	btVector3* velocityTemp = Math::Vector3ToBtVector3(velocity);
	Unmanaged->setVelocity(*velocityTemp);
	delete velocityTemp;
}

void BulletSharp::SoftBody::SoftBody::SetVolumeDensity(btScalar density)
{
	Unmanaged->setVolumeDensity(density);
}

void BulletSharp::SoftBody::SoftBody::SetVolumeMass(btScalar mass)
{
	Unmanaged->setVolumeMass(mass);
}

void BulletSharp::SoftBody::SoftBody::SolveClusters(btScalar sor)
{
	Unmanaged->solveClusters(sor);
}

void BulletSharp::SoftBody::SoftBody::SolveClusters(AlignedSoftBodyArray^ bodies)
{
	btSoftBody::solveClusters(*(btSoftBody::tSoftBodyArray*)bodies->_unmanaged);
}

void BulletSharp::SoftBody::SoftBody::SolveCommonConstraints(array<SoftBody^>^ bodies, int iterations)
{
	int len = bodies->Length;
	btSoftBody** bodiesTemp = new btSoftBody*[len];

	int i;
	for (i=0; i<len; i++)
		bodiesTemp[i] = (btSoftBody*)bodies[i]->_unmanaged;

	btSoftBody::solveCommonConstraints(bodiesTemp, len, iterations);

	delete[] bodiesTemp;
}

void BulletSharp::SoftBody::SoftBody::SolveConstraints()
{
	Unmanaged->solveConstraints();
}

void BulletSharp::SoftBody::SoftBody::StaticSolve(int iterations)
{
	Unmanaged->staticSolve(iterations);
}

void BulletSharp::SoftBody::SoftBody::Transform(Matrix transform)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	Unmanaged->transform(*transformTemp);
	delete transformTemp;
}

void BulletSharp::SoftBody::SoftBody::Translate(Vector3 translation)
{
	btVector3* translationTemp = Math::Vector3ToBtVector3(translation);
	Unmanaged->translate(*translationTemp);
	delete translationTemp;
}

void BulletSharp::SoftBody::SoftBody::Translate(btScalar x, btScalar y, btScalar z)
{
	Translate(Vector3(x,y,z));
}

void BulletSharp::SoftBody::SoftBody::UpdateBounds()
{
	Unmanaged->updateBounds();
}

void BulletSharp::SoftBody::SoftBody::UpdateClusters()
{
	Unmanaged->updateClusters();
}

void BulletSharp::SoftBody::SoftBody::UpdateConstants()
{
	Unmanaged->updateConstants();
}

void BulletSharp::SoftBody::SoftBody::UpdateNormals()
{
	Unmanaged->updateNormals();
}

void BulletSharp::SoftBody::SoftBody::UpdatePose()
{
	Unmanaged->updatePose();
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::SoftBody::Upcast(CollisionObject^ colObj)
{
	btSoftBody* body = btSoftBody::upcast(colObj->UnmanagedPointer);
	return (BulletSharp::SoftBody::SoftBody^)CollisionObject::GetManaged(body);
}

AlignedAnchorArray^ BulletSharp::SoftBody::SoftBody::Anchors::get()
{
	return gcnew AlignedAnchorArray(&Unmanaged->m_anchors);
}

Vector3Array^ BulletSharp::SoftBody::SoftBody::Bounds::get()
{
	return gcnew Vector3Array(Unmanaged->m_bounds, 2);
}

AlignedClusterArray^ BulletSharp::SoftBody::SoftBody::Clusters::get()
{
	return gcnew AlignedClusterArray(&Unmanaged->m_clusters);
}

Config^ BulletSharp::SoftBody::SoftBody::Cfg::get()
{
	return gcnew Config(&Unmanaged->m_cfg);
}

int BulletSharp::SoftBody::SoftBody::ClusterCount::get()
{
	return Unmanaged->clusterCount();
}

AlignedCollisionObjectArray^ BulletSharp::SoftBody::SoftBody::CollisionDisabledObjects::get()
{
	return gcnew AlignedCollisionObjectArray((btAlignedObjectArray<btCollisionObject*>*)&Unmanaged->m_collisionDisabledObjects);
}

AlignedFaceArray^ BulletSharp::SoftBody::SoftBody::Faces::get()
{
	btAlignedObjectArray<btSoftBody::Face>* faceArray = &Unmanaged->m_faces;
	ReturnCachedObjectNew(AlignedFaceArray, _alignedFaceArray, faceArray);
}

AlignedJointArray^ BulletSharp::SoftBody::SoftBody::Joints::get()
{
	return gcnew AlignedJointArray(&Unmanaged->m_joints);
}

AlignedLinkArray^ BulletSharp::SoftBody::SoftBody::Links::get()
{
	btSoftBody::tLinkArray* linkArray = &Unmanaged->m_links;
	ReturnCachedObjectNew(AlignedLinkArray, _alignedLinkArray, linkArray);
}

Matrix BulletSharp::SoftBody::SoftBody::InitialWorldTransform::get()
{
	return Math::BtTransformToMatrix(&Unmanaged->m_initialWorldTransform);
}
void BulletSharp::SoftBody::SoftBody::InitialWorldTransform::set(Matrix value)
{
	return Math::MatrixToBtTransform(value, &Unmanaged->m_initialWorldTransform);
}

AlignedMaterialArray^ BulletSharp::SoftBody::SoftBody::Materials::get()
{
	return gcnew AlignedMaterialArray(&Unmanaged->m_materials);
}

BulletSharp::SoftBody::AlignedNodeArray^ BulletSharp::SoftBody::SoftBody::Nodes::get()
{
	return gcnew AlignedNodeArray(&Unmanaged->m_nodes);
}

BulletSharp::SoftBody::AlignedNoteArray^ BulletSharp::SoftBody::SoftBody::Notes::get()
{
	return gcnew AlignedNoteArray(&Unmanaged->m_notes);
}

BulletSharp::SoftBody::Pose^ BulletSharp::SoftBody::SoftBody::Pose::get()
{
	return gcnew BulletSharp::SoftBody::Pose(&Unmanaged->m_pose);
}

BulletSharp::SoftBody::AlignedRigidContactArray^ BulletSharp::SoftBody::SoftBody::RigidContacts::get()
{
	return gcnew AlignedRigidContactArray(&Unmanaged->m_rcontacts);
}

SoftBodySolver^ BulletSharp::SoftBody::SoftBody::SoftBodySolver::get()
{
	return gcnew BulletSharp::SoftBody::SoftBodySolver(Unmanaged->getSoftBodySolver());
}
void BulletSharp::SoftBody::SoftBody::SoftBodySolver::set(BulletSharp::SoftBody::SoftBodySolver^ value)
{
	Unmanaged->setSoftBodySolver(value->UnmanagedPointer);
}

BulletSharp::SoftBody::AlignedSoftContactArray^ BulletSharp::SoftBody::SoftBody::SoftContacts::get()
{
	return gcnew AlignedSoftContactArray(&Unmanaged->m_scontacts);
}

SolverState^ BulletSharp::SoftBody::SoftBody::SolverState::get()
{
	return gcnew BulletSharp::SoftBody::SolverState(&Unmanaged->m_sst);
}
void BulletSharp::SoftBody::SoftBody::SolverState::set(BulletSharp::SoftBody::SolverState^ value)
{
	Unmanaged->m_sst = *value->UnmanagedPointer;
}

Object^ BulletSharp::SoftBody::SoftBody::Tag::get()
{
	void* obj = Unmanaged->m_tag;
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}
void BulletSharp::SoftBody::SoftBody::Tag::set(Object^ value)
{
	void* obj = Unmanaged->m_tag;
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	Unmanaged->m_tag = GCHandleToVoidPtr(handle);
}

BulletSharp::SoftBody::AlignedTetraArray^ BulletSharp::SoftBody::SoftBody::Tetras::get()
{
	btAlignedObjectArray<btSoftBody::Tetra>* tetras = &Unmanaged->m_tetras;
	ReturnCachedObjectNew(AlignedTetraArray, _alignedTetraArray, tetras);
}

btScalar BulletSharp::SoftBody::SoftBody::TimeAccumulator::get()
{
	return Unmanaged->m_timeacc;
}
void BulletSharp::SoftBody::SoftBody::TimeAccumulator::set(btScalar value)
{
	Unmanaged->m_timeacc = value;
}

btScalar BulletSharp::SoftBody::SoftBody::TotalMass::get()
{
	return Unmanaged->getTotalMass();
}
void BulletSharp::SoftBody::SoftBody::TotalMass::set(btScalar value)
{
	Unmanaged->setTotalMass(value);
}

bool BulletSharp::SoftBody::SoftBody::UpdateRuntimeConstants::get()
{
	return Unmanaged->m_bUpdateRtCst;
}
void BulletSharp::SoftBody::SoftBody::UpdateRuntimeConstants::set(bool value)
{
	Unmanaged->m_bUpdateRtCst = value;
}

AlignedIntArray^ BulletSharp::SoftBody::SoftBody::UserIndexMapping::get()
{
	return gcnew AlignedIntArray(&Unmanaged->m_userIndexMapping);
}

btScalar BulletSharp::SoftBody::SoftBody::Volume::get()
{
	return Unmanaged->getVolume();
}

Vector3 BulletSharp::SoftBody::SoftBody::WindVelocity::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getWindVelocity());
}
void BulletSharp::SoftBody::SoftBody::WindVelocity::set(Vector3 value)
{
	btVector3* tempWindVelocity = Math::Vector3ToBtVector3(value);
	Unmanaged->setWindVelocity(*tempWindVelocity);
	delete tempWindVelocity;
}

SoftBodyWorldInfo^ BulletSharp::SoftBody::SoftBody::WorldInfo::get()
{
	return gcnew SoftBodyWorldInfo(Unmanaged->getWorldInfo());
}
void BulletSharp::SoftBody::SoftBody::WorldInfo::set(SoftBodyWorldInfo^ value)
{
	Unmanaged->m_worldInfo = value->UnmanagedPointer;
}

#ifndef DISABLE_DBVT
Dbvt^ BulletSharp::SoftBody::SoftBody::ClusterDbvt::get()
{
	return gcnew Dbvt(&UnmanagedPointer->m_cdbvt);
}
void BulletSharp::SoftBody::SoftBody::ClusterDbvt::set(Dbvt^ value)
{
	UnmanagedPointer->m_cdbvt = *value->UnmanagedPointer;
}

Dbvt^ BulletSharp::SoftBody::SoftBody::FaceDbvt::get()
{
	return gcnew Dbvt(&UnmanagedPointer->m_fdbvt);
}
void BulletSharp::SoftBody::SoftBody::FaceDbvt::set(Dbvt^ value)
{
	UnmanagedPointer->m_fdbvt = *value->UnmanagedPointer;
}

Dbvt^ BulletSharp::SoftBody::SoftBody::NodeDbvt::get()
{
	return gcnew Dbvt(&UnmanagedPointer->m_ndbvt);
}
void BulletSharp::SoftBody::SoftBody::NodeDbvt::set(Dbvt^ value)
{
	UnmanagedPointer->m_ndbvt = *value->UnmanagedPointer;
}
#endif

btSoftBody* BulletSharp::SoftBody::SoftBody::UnmanagedPointer::get()
{
	return (btSoftBody*)CollisionObject::UnmanagedPointer;
}

#endif
