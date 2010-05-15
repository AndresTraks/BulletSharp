#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "Dispatcher.h"
#include "RigidBody.h"
#include "SoftBody.h"
#include "SparseSdf.h"

using namespace BulletSharp::SoftBody;

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


Config::Config(btSoftBody::Config* config)
{
	_config = config;
}

AeroModel Config::AeroModel::get()
{
	return (BulletSharp::SoftBody::AeroModel)_config->aeromodel;
}
void Config::AeroModel::set(BulletSharp::SoftBody::AeroModel value)
{
	_config->aeromodel = (btSoftBody::eAeroModel::_)value;
}

btScalar Config::DG::get()
{
	return _config->kDG;
}
void Config::DG::set(btScalar value)
{
	_config->kDG = value;
}

btScalar Config::LF::get()
{
	return _config->kLF;
}
void Config::LF::set(btScalar value)
{
	_config->kLF = value;
}

FCollisions Config::Collisions::get()
{
	return (FCollisions)UnmanagedPointer->collisions;
}
void Config::Collisions::set(FCollisions value)
{
	UnmanagedPointer->collisions = (int)value;
}

int Config::PIterations::get()
{
	return UnmanagedPointer->piterations;
}
void Config::PIterations::set(int value)
{
	UnmanagedPointer->piterations = value;
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
	_element = element;
}

btSoftBody::Element* Element::UnmanagedPointer::get()
{
	return _element;
}
void Element::UnmanagedPointer::set(btSoftBody::Element* element)
{
	_element = element;
}


Feature::Feature(btSoftBody::Feature* feature)
: Element(feature)
{
}

btSoftBody::Feature* Feature::UnmanagedPointer::get()
{
	return (btSoftBody::Feature*)Element::UnmanagedPointer;
}


Face::Face(btSoftBody::Face* face)
: Feature(face)
{
}

array<Node^>^ Face::n::get()
{
	array<Node^>^ nodeArray = gcnew array<Node^>(3);
	nodeArray[0] = gcnew Node(UnmanagedPointer->m_n[0]);
	nodeArray[1] = gcnew Node(UnmanagedPointer->m_n[1]);
	nodeArray[2] = gcnew Node(UnmanagedPointer->m_n[2]);
	return nodeArray;
}
void Face::n::set(array<Node^>^ value)
{
	UnmanagedPointer->m_n[0] = value[0]->UnmanagedPointer;
	UnmanagedPointer->m_n[1] = value[1]->UnmanagedPointer;
	UnmanagedPointer->m_n[2] = value[2]->UnmanagedPointer;
}

Vector3 Face::Normal::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_normal);
}
void Face::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_normal);
}

btSoftBody::Face* Face::UnmanagedPointer::get()
{
	return (btSoftBody::Face*)Feature::UnmanagedPointer;
}


Link::Link(btSoftBody::Link* link)
: Feature(link)
{
}


Material::Material(btSoftBody::Material* material)
: Element(material)
{
}

btScalar Material::Ast::get()
{
	return UnmanagedPointer->m_kAST;
}
void Material::Ast::set(btScalar value)
{
	UnmanagedPointer->m_kAST = value;
}

FMaterial Material::Flags::get()
{
	return (FMaterial)UnmanagedPointer->m_flags;
}
void Material::Flags::set(FMaterial value)
{
	UnmanagedPointer->m_flags = (int)value;
}

btScalar Material::Lst::get()
{
	return UnmanagedPointer->m_kLST;
}
void Material::Lst::set(btScalar value)
{
	UnmanagedPointer->m_kAST = value;
}

btScalar Material::Vst::get()
{
	return UnmanagedPointer->m_kVST;
}
void Material::Vst::set(btScalar value)
{
	UnmanagedPointer->m_kVST = value;
}

btSoftBody::Material* Material::UnmanagedPointer::get()
{
	return (btSoftBody::Material*)Element::UnmanagedPointer;
}


Node::Node(btSoftBody::Node* node)
: Feature(node)
{
}

Vector3 Node::x::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_x);
}
void Node::x::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_x);
}

btSoftBody::Node* Node::UnmanagedPointer::get()
{
	return (btSoftBody::Node*)Feature::UnmanagedPointer;
}


Note::Note(btSoftBody::Note* note)
: Element(note)
{
}


Tetra::Tetra(btSoftBody::Tetra* tetra)
: Feature(tetra)
{
}


BulletSharp::SoftBody::SoftBody::SoftBody(btSoftBody* body)
: CollisionObject(body)
{
}

BulletSharp::SoftBody::SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo, int node_count, Vector3 x, btScalar m)
: CollisionObject(0)
{
	btVector3* xTemp = Math::Vector3ToBtVector3(x);
	UnmanagedPointer = new btSoftBody(worldInfo->UnmanagedPointer, node_count, xTemp, &m);
	delete xTemp;
}

BulletSharp::SoftBody::Material^ BulletSharp::SoftBody::SoftBody::AppendMaterial()
{
	return gcnew Material(UnmanagedPointer->appendMaterial());
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force, int node)
{
	btVector3* forceTemp = Math::Vector3ToBtVector3(force);
	UnmanagedPointer->addForce(*forceTemp, node);
	delete forceTemp;
}

void BulletSharp::SoftBody::SoftBody::AddForce(Vector3 force)
{
	UnmanagedPointer->addForce(*Math::Vector3ToBtVector3(force));
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity, int node)
{
	btVector3* velocityTemp = Math::Vector3ToBtVector3(velocity);
	UnmanagedPointer->addVelocity(*velocityTemp, node);
	delete velocityTemp;
}

void BulletSharp::SoftBody::SoftBody::AddVelocity(Vector3 velocity)
{
	UnmanagedPointer->addVelocity(*Math::Vector3ToBtVector3(velocity));
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies)
{
	UnmanagedPointer->appendAnchor(node, body->UnmanagedPointer, disableCollisionBetweenLinkedBodies);
}

void BulletSharp::SoftBody::SoftBody::AppendAnchor(int node, RigidBody^ body)
{
	UnmanagedPointer->appendAnchor(node, body->UnmanagedPointer);
}

int BulletSharp::SoftBody::SoftBody::GenerateBendingConstraints(int distance, Material^ mat)
{
	return UnmanagedPointer->generateBendingConstraints(distance, mat->UnmanagedPointer);
}

int BulletSharp::SoftBody::SoftBody::GenerateBendingConstraints(int distance)
{
	return UnmanagedPointer->generateBendingConstraints(distance);
}

int BulletSharp::SoftBody::SoftBody::GenerateClusters(int k, int maxIterations)
{
	return UnmanagedPointer->generateClusters(k, maxIterations);
}

int BulletSharp::SoftBody::SoftBody::GenerateClusters(int k)
{
	return UnmanagedPointer->generateClusters(k);
}

void BulletSharp::SoftBody::SoftBody::Scale(Vector3 scale)
{
	btVector3* scaleTemp = Math::Vector3ToBtVector3(scale);
	UnmanagedPointer->scale(*scaleTemp);
	delete scaleTemp;
}

void BulletSharp::SoftBody::SoftBody::SetVolumeMass(btScalar mass)
{
	UnmanagedPointer->setVolumeMass(mass);
}

void BulletSharp::SoftBody::SoftBody::StaticSolve(int iterations)
{
	UnmanagedPointer->staticSolve(iterations);
}

void BulletSharp::SoftBody::SoftBody::Transform(Matrix transform)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	UnmanagedPointer->transform(*transformTemp);
	delete transformTemp;
}

void BulletSharp::SoftBody::SoftBody::Translate(Vector3 translation)
{
	btVector3* translationTemp = Math::Vector3ToBtVector3(translation);
	UnmanagedPointer->translate(*translationTemp);
	delete translationTemp;
}

void BulletSharp::SoftBody::SoftBody::Translate(btScalar x, btScalar y, btScalar z)
{
	Translate(Vector3(x,y,z));
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::SoftBody::Upcast(CollisionObject^ colObj)
{
	btSoftBody* body = btSoftBody::upcast(colObj->UnmanagedPointer);
	if (body == nullptr)
		return nullptr;
	return gcnew SoftBody(body);
}

Config^ BulletSharp::SoftBody::SoftBody::Cfg::get()
{
	return gcnew Config(&UnmanagedPointer->m_cfg);
}
void BulletSharp::SoftBody::SoftBody::Cfg::set(Config^ value)
{
	UnmanagedPointer->m_cfg = *value->UnmanagedPointer;
}

FaceArray^ BulletSharp::SoftBody::SoftBody::Faces::get()
{
	return gcnew FaceArray(&UnmanagedPointer->m_faces);
}
void BulletSharp::SoftBody::SoftBody::Faces::set(FaceArray^ value)
{
	UnmanagedPointer->m_faces = *value->UnmanagedPointer;
}

MaterialArray^ BulletSharp::SoftBody::SoftBody::Materials::get()
{
	return gcnew MaterialArray(&UnmanagedPointer->m_materials);
}
void BulletSharp::SoftBody::SoftBody::Materials::set(MaterialArray^ value)
{
	UnmanagedPointer->m_materials = *value->UnmanagedPointer;
}

BulletSharp::SoftBody::NodeArray^ BulletSharp::SoftBody::SoftBody::Nodes::get()
{
	return gcnew NodeArray(&UnmanagedPointer->m_nodes);
}
void BulletSharp::SoftBody::SoftBody::Nodes::set(NodeArray^ value)
{
	UnmanagedPointer->m_nodes = *value->UnmanagedPointer;
}

btScalar BulletSharp::SoftBody::SoftBody::TotalMass::get()
{
	return UnmanagedPointer->getTotalMass();
}
void BulletSharp::SoftBody::SoftBody::TotalMass::set(btScalar value)
{
	UnmanagedPointer->setTotalMass(value);
}

btSoftBody* BulletSharp::SoftBody::SoftBody::UnmanagedPointer::get()
{
	return (btSoftBody*)CollisionObject::UnmanagedPointer;
}

#endif
