#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletSoftBody/btSoftBody.h>
#pragma managed(pop)

#include "SoftBody.h"

btSoftBodyWorldInfo* SoftBodyWorldInfo::UnmanagedPointer::get()
{
	return _info;
}
void SoftBodyWorldInfo::UnmanagedPointer::set(btSoftBodyWorldInfo* value)
{
	_info = value;
}

SoftBody::SoftBody(btSoftBody* body)
: CollisionObject(body)
{
}

SoftBody::SoftBody(SoftBodyWorldInfo^ worldInfo, int node_count, Vector3 x, btScalar m)
: CollisionObject(new btSoftBody(worldInfo->UnmanagedPointer, node_count, Math::Vector3ToBtVec3(x), &m))
{
}
