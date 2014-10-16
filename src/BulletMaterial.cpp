#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BulletMaterial.h"

BulletMaterial::BulletMaterial(btMaterial* native)
{
	friction = native->m_friction;
	restitution = native->m_restitution;
}

BulletMaterial::BulletMaterial(btScalar fric, btScalar rest)
{
	friction = fric;
	restitution = rest;
}

btScalar BulletMaterial::Friction::get()
{
	return friction;
}
void BulletMaterial::Friction::set(btScalar value)
{
	friction = value;
}

btScalar BulletMaterial::Restitution::get()
{
	return restitution;
}
void BulletMaterial::Restitution::set(btScalar value)
{
	restitution = value;
}

#endif
