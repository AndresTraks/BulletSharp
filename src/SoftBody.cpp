#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletSoftBody/btSoftBody.h>
#pragma managed(pop)

#include "BroadphaseInterface.h"
#include "Dispatcher.h"
#include "SoftBody.h"

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
	return Math::BtVec3ToVector3(&_info->m_gravity);
}
void SoftBodyWorldInfo::Gravity::set(Vector3 value)
{
	Math::Vector3ToBtVec3(value, &_info->m_gravity);
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
	return Math::BtVec3ToVector3(&_info->water_normal);
}
void SoftBodyWorldInfo::WaterNormal::set(Vector3 value)
{
	Math::Vector3ToBtVec3(value, &_info->water_normal);
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

SoftBody::Config^ SoftBody::Cfg::get()
{
	return gcnew Config(&UnmanagedPointer->m_cfg);
}
void SoftBody::Cfg::set(SoftBody::Config^ value)
{
	UnmanagedPointer->m_cfg = *value->UnmanagedPointer;
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


SoftBody::SoftBody(btSoftBody* body)
: CollisionObject(body)
{
}

SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo, int node_count, Vector3 x, btScalar m)
: CollisionObject(new btSoftBody(worldInfo->UnmanagedPointer, node_count, Math::Vector3ToBtVec3(x), &m))
{
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
	UnmanagedPointer->scale(*Math::Vector3ToBtVec3(scale));
}

void SoftBody::SetVolumeMass(btScalar mass)
{
	UnmanagedPointer->setVolumeMass(mass);
}

void SoftBody::Translate(Vector3 translation)
{
	UnmanagedPointer->translate(*Math::Vector3ToBtVec3(translation));
}

void SoftBody::Translate(btScalar x, btScalar y, btScalar z)
{
	Translate(Vector3(x,y,z));
}

btSoftBody* SoftBody::UnmanagedPointer::get()
{
	return (btSoftBody*)CollisionObject::UnmanagedPointer;
}
