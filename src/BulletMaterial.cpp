#include "StdAfx.h"

#include "BulletMaterial.h"

BulletMaterial::BulletMaterial(btMaterial* material)
{
	Friction = material->m_friction;
	Restitution = material->m_restitution;
}

BulletMaterial::BulletMaterial(btScalar fric, btScalar rest)
{
	Friction = fric;
	Restitution = rest;
}
