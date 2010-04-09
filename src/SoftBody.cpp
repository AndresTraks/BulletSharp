#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "Dispatcher.h"
#include "RigidBody.h"
#include "SoftBody.h"
#include "SparseSdf.h"

#pragma managed(push, off)
btSoftBodyWorldInfo* SoftBodyWorldInfo_New()
{
	btSoftBodyWorldInfo* info = new btSoftBodyWorldInfo();
	memset(info, 0, sizeof(btSoftBodyWorldInfo));
	return info;
}
#pragma managed(pop)

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
	_info->m_broadphase = value->UnmanagedPointer;
}

Dispatcher^ SoftBodyWorldInfo::Dispatcher::get()
{
	if (_info->m_dispatcher == nullptr)
		return nullptr;
	return gcnew BulletSharp::Dispatcher(_info->m_dispatcher);
}
void SoftBodyWorldInfo::Dispatcher::set(BulletSharp::Dispatcher^ value)
{
	_info->m_dispatcher = value->UnmanagedPointer;
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
void SoftBodyWorldInfo::SparseSdf::set(BulletSharp::SparseSdf^ value)
{
	_info->m_sparsesdf = *value->UnmanagedPointer;
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


SoftBody::Config::Config(btSoftBody::Config* config)
{
	_config = config;
}

SoftBody::AeroModel SoftBody::Config::AeroModel::get()
{
	return (SoftBody::AeroModel)_config->aeromodel;
}
void SoftBody::Config::AeroModel::set(SoftBody::AeroModel value)
{
	_config->aeromodel = (btSoftBody::eAeroModel::_)value;
}

btScalar SoftBody::Config::DG::get()
{
	return _config->kDG;
}
void SoftBody::Config::DG::set(btScalar value)
{
	_config->kDG = value;
}

btScalar SoftBody::Config::LF::get()
{
	return _config->kLF;
}
void SoftBody::Config::LF::set(btScalar value)
{
	_config->kLF = value;
}

SoftBody::FCollisions SoftBody::Config::Collisions::get()
{
	return (FCollisions)UnmanagedPointer->collisions;
}
void SoftBody::Config::Collisions::set(SoftBody::FCollisions value)
{
	UnmanagedPointer->collisions = (int)value;
}

int SoftBody::Config::PIterations::get()
{
	return UnmanagedPointer->piterations;
}
void SoftBody::Config::PIterations::set(int value)
{
	UnmanagedPointer->piterations = value;
}

btSoftBody::Config* SoftBody::Config::UnmanagedPointer::get()
{
	return _config;
}
void SoftBody::Config::UnmanagedPointer::set(btSoftBody::Config* value)
{
	_config = value;
}


SoftBody::Element::Element(btSoftBody::Element* element)
{
	_element = element;
}

btSoftBody::Element* SoftBody::Element::UnmanagedPointer::get()
{
	return _element;
}
void SoftBody::Element::UnmanagedPointer::set(btSoftBody::Element* element)
{
	_element = element;
}


SoftBody::Feature::Feature(btSoftBody::Feature* feature)
: Element(feature)
{
}

btSoftBody::Feature* SoftBody::Feature::UnmanagedPointer::get()
{
	return (btSoftBody::Feature*)Element::UnmanagedPointer;
}


SoftBody::Face::Face(btSoftBody::Face* face)
: Feature(face)
{
}

array<SoftBody::Node^>^ SoftBody::Face::n::get()
{
	array<SoftBody::Node^>^ nodeArray = gcnew array<Node^>(3);
	nodeArray[0] = gcnew SoftBody::Node(UnmanagedPointer->m_n[0]);
	nodeArray[1] = gcnew SoftBody::Node(UnmanagedPointer->m_n[1]);
	nodeArray[2] = gcnew SoftBody::Node(UnmanagedPointer->m_n[2]);
	return nodeArray;
}
void SoftBody::Face::n::set(array<SoftBody::Node^>^ value)
{
	UnmanagedPointer->m_n[0] = value[0]->UnmanagedPointer;
	UnmanagedPointer->m_n[1] = value[1]->UnmanagedPointer;
	UnmanagedPointer->m_n[2] = value[2]->UnmanagedPointer;
}

Vector3 SoftBody::Face::Normal::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_normal);
}
void SoftBody::Face::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_normal);
}

btSoftBody::Face* SoftBody::Face::UnmanagedPointer::get()
{
	return (btSoftBody::Face*)Feature::UnmanagedPointer;
}


SoftBody::Link::Link(btSoftBody::Link* link)
: Feature(link)
{
}


SoftBody::Material::Material(btSoftBody::Material* material)
: Element(material)
{
}

btScalar SoftBody::Material::Ast::get()
{
	return UnmanagedPointer->m_kAST;
}
void SoftBody::Material::Ast::set(btScalar value)
{
	UnmanagedPointer->m_kAST = value;
}

SoftBody::FMaterial SoftBody::Material::Flags::get()
{
	return (FMaterial)UnmanagedPointer->m_flags;
}
void SoftBody::Material::Flags::set(FMaterial value)
{
	UnmanagedPointer->m_flags = (int)value;
}

btScalar SoftBody::Material::Lst::get()
{
	return UnmanagedPointer->m_kLST;
}
void SoftBody::Material::Lst::set(btScalar value)
{
	UnmanagedPointer->m_kAST = value;
}

btScalar SoftBody::Material::Vst::get()
{
	return UnmanagedPointer->m_kVST;
}
void SoftBody::Material::Vst::set(btScalar value)
{
	UnmanagedPointer->m_kVST = value;
}

btSoftBody::Material* SoftBody::Material::UnmanagedPointer::get()
{
	return (btSoftBody::Material*)Element::UnmanagedPointer;
}


SoftBody::Node::Node(btSoftBody::Node* node)
: Feature(node)
{
}

Vector3 SoftBody::Node::x::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_x);
}
void SoftBody::Node::x::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_x);
}

btSoftBody::Node* SoftBody::Node::UnmanagedPointer::get()
{
	return (btSoftBody::Node*)Feature::UnmanagedPointer;
}


SoftBody::Note::Note(btSoftBody::Note* note)
: Element(note)
{
}


SoftBody::Tetra::Tetra(btSoftBody::Tetra* tetra)
: Feature(tetra)
{
}


SoftBody::SoftBody(btSoftBody* body)
: CollisionObject(body)
{
}

SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo, int node_count, Vector3 x, btScalar m)
: CollisionObject(new btSoftBody(worldInfo->UnmanagedPointer, node_count, Math::Vector3ToBtVector3(x), &m))
{
}

SoftBody::Material^ SoftBody::AppendMaterial()
{
	return gcnew Material(UnmanagedPointer->appendMaterial());
}

void SoftBody::AddForce(Vector3 force, int node)
{
	UnmanagedPointer->addForce(*Math::Vector3ToBtVector3(force), node);
}

void SoftBody::AddForce(Vector3 force)
{
	UnmanagedPointer->addForce(*Math::Vector3ToBtVector3(force));
}

void SoftBody::AddVelocity(Vector3 velocity, int node)
{
	UnmanagedPointer->addVelocity(*Math::Vector3ToBtVector3(velocity), node);
}

void SoftBody::AddVelocity(Vector3 velocity)
{
	UnmanagedPointer->addVelocity(*Math::Vector3ToBtVector3(velocity));
}

void SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies)
{
	UnmanagedPointer->appendAnchor(node, body->UnmanagedPointer, disableCollisionBetweenLinkedBodies);
}

void SoftBody::AppendAnchor(int node, RigidBody^ body)
{
	UnmanagedPointer->appendAnchor(node, body->UnmanagedPointer);
}

int SoftBody::GenerateBendingConstraints(int distance, SoftBody::Material^ mat)
{
	return UnmanagedPointer->generateBendingConstraints(distance, mat->UnmanagedPointer);
}

int SoftBody::GenerateBendingConstraints(int distance)
{
	return UnmanagedPointer->generateBendingConstraints(distance);
}

int SoftBody::GenerateClusters(int k, int maxIterations)
{
	return UnmanagedPointer->generateClusters(k, maxIterations);
}

int SoftBody::GenerateClusters(int k)
{
	return UnmanagedPointer->generateClusters(k);
}

void SoftBody::Scale(Vector3 scale)
{
	UnmanagedPointer->scale(*Math::Vector3ToBtVector3(scale));
}

void SoftBody::SetVolumeMass(btScalar mass)
{
	UnmanagedPointer->setVolumeMass(mass);
}

void SoftBody::StaticSolve(int iterations)
{
	UnmanagedPointer->staticSolve(iterations);
}

void SoftBody::Transform(Matrix transform)
{
	UnmanagedPointer->transform(*Math::MatrixToBtTransform(transform));
}

void SoftBody::Translate(Vector3 translation)
{
	UnmanagedPointer->translate(*Math::Vector3ToBtVector3(translation));
}

void SoftBody::Translate(btScalar x, btScalar y, btScalar z)
{
	Translate(Vector3(x,y,z));
}

SoftBody^ SoftBody::Upcast(CollisionObject^ colObj)
{
	btSoftBody* body = btSoftBody::upcast(colObj->UnmanagedPointer);
	if (body == nullptr)
		return nullptr;
	return gcnew SoftBody(body);
}

SoftBody::Config^ SoftBody::Cfg::get()
{
	return gcnew Config(&UnmanagedPointer->m_cfg);
}
void SoftBody::Cfg::set(SoftBody::Config^ value)
{
	UnmanagedPointer->m_cfg = *value->UnmanagedPointer;
}

BulletSharp::FaceArray^ SoftBody::Faces::get()
{
	return gcnew FaceArray(&UnmanagedPointer->m_faces);
}
void SoftBody::Faces::set(BulletSharp::FaceArray^ value)
{
	UnmanagedPointer->m_faces = *value->UnmanagedPointer;
}

BulletSharp::MaterialArray^ SoftBody::Materials::get()
{
	return gcnew MaterialArray(&UnmanagedPointer->m_materials);
}
void SoftBody::Materials::set(BulletSharp::MaterialArray^ value)
{
	UnmanagedPointer->m_materials = *value->UnmanagedPointer;
}

BulletSharp::NodeArray^ SoftBody::Nodes::get()
{
	return gcnew NodeArray(&UnmanagedPointer->m_nodes);
}
void SoftBody::Nodes::set(BulletSharp::NodeArray^ value)
{
	UnmanagedPointer->m_nodes = *value->UnmanagedPointer;
}

btScalar SoftBody::TotalMass::get()
{
	return UnmanagedPointer->getTotalMass();
}
void SoftBody::TotalMass::set(btScalar value)
{
	UnmanagedPointer->setTotalMass(value);
}

btSoftBody* SoftBody::UnmanagedPointer::get()
{
	return (btSoftBody*)CollisionObject::UnmanagedPointer;
}

#endif
