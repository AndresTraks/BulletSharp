#include "StdAfx.h"

#include "BulletMaterial.h"

BulletMaterial::BulletMaterial(btMaterial* material)
{
	_material = material;
}

BulletMaterial::BulletMaterial()
{
	_material = new btMaterial();
}

BulletMaterial::BulletMaterial(btScalar fric, btScalar rest)
{
	_material = new btMaterial(fric, rest);
}

btScalar BulletMaterial::Friction::get()
{
	return _material->m_friction;
}
void BulletMaterial::Friction::set(btScalar value)
{
	_material->m_friction = value;
}

btScalar BulletMaterial::Restitution::get()
{
	return _material->m_restitution;
}
void BulletMaterial::Restitution::set(btScalar value)
{
	_material->m_restitution = value;
}
