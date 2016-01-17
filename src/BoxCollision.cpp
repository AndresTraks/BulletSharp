#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "BoxCollision.h"

Aabb::Aabb(btAABB* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

Aabb::~Aabb()
{
	this->!Aabb();
}

Aabb::!Aabb()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

Aabb::Aabb()
{
	_native = new btAABB();
}

Aabb::Aabb(Vector3 v1, Vector3 v2, Vector3 v3)
{
	VECTOR3_CONV(v1);
	VECTOR3_CONV(v2);
	VECTOR3_CONV(v3);
	_native = new btAABB(VECTOR3_USE(v1), VECTOR3_USE(v2), VECTOR3_USE(v3));
	VECTOR3_DEL(v1);
	VECTOR3_DEL(v2);
	VECTOR3_DEL(v3);
}

Aabb::Aabb(Vector3 v1, Vector3 v2, Vector3 v3, btScalar margin)
{
	VECTOR3_CONV(v1);
	VECTOR3_CONV(v2);
	VECTOR3_CONV(v3);
	_native = new btAABB(VECTOR3_USE(v1), VECTOR3_USE(v2), VECTOR3_USE(v3), margin);
	VECTOR3_DEL(v1);
	VECTOR3_DEL(v2);
	VECTOR3_DEL(v3);
}

Aabb::Aabb(Aabb^ other)
{
	_native = new btAABB(*other->_native);
}

Aabb::Aabb(Aabb^ other, btScalar margin)
{
	_native = new btAABB(*other->_native, margin);
}

void Aabb::AppyTransform(Matrix trans)
{
	TRANSFORM_CONV(trans);
	_native->appy_transform(TRANSFORM_USE(trans));
	TRANSFORM_DEL(trans);
}
/*
void Aabb::AppyTransformTransCache(BT_BOX_BOX_TRANSFORM_CACHE^ trans)
{
	_native->appy_transform_trans_cache(*trans->_native);
}
*/
bool Aabb::CollidePlane(Vector4 plane)
{
	VECTOR4_CONV(plane);
	bool ret = _native->collide_plane(VECTOR4_USE(plane));
	VECTOR4_DEL(plane);
	return ret;
}

bool Aabb::CollideRay(Vector3 vorigin, Vector3 vdir)
{
	VECTOR3_CONV(vorigin);
	VECTOR3_CONV(vdir);
	bool ret = _native->collide_ray(VECTOR3_USE(vorigin), VECTOR3_USE(vdir));
	VECTOR3_DEL(vorigin);
	VECTOR3_DEL(vdir);
	return ret;
}

bool Aabb::CollideTriangleExact(Vector3 p1, Vector3 p2, Vector3 p3, Vector4 trianglePlane)
{
	VECTOR3_CONV(p1);
	VECTOR3_CONV(p2);
	VECTOR3_CONV(p3);
	VECTOR4_CONV(trianglePlane);
	bool ret = _native->collide_triangle_exact(VECTOR3_USE(p1), VECTOR3_USE(p2), VECTOR3_USE(p3),
		VECTOR4_USE(trianglePlane));
	VECTOR3_DEL(p1);
	VECTOR3_DEL(p2);
	VECTOR3_DEL(p3);
	VECTOR4_DEL(trianglePlane);
	return ret;
}

void Aabb::CopyWithMargin(Aabb^ other, btScalar margin)
{
	_native->copy_with_margin(*other->_native, margin);
}

void Aabb::FindIntersection(Aabb^ other, Aabb^ intersection)
{
	_native->find_intersection(*other->_native, *intersection->_native);
}

void Aabb::GetCenterExtend([Out] Vector3% center, [Out] Vector3% extend)
{
	btVector3* centerTemp = ALIGNED_NEW(btVector3);
	btVector3* extendTemp = ALIGNED_NEW(btVector3);
	_native->get_center_extend(*centerTemp, *extendTemp);
	Math::BtVector3ToVector3(centerTemp, center);
	Math::BtVector3ToVector3(extendTemp, extend);
	ALIGNED_FREE(centerTemp);
	ALIGNED_FREE(extendTemp);
}

bool Aabb::HasCollision(Aabb^ other)
{
	return _native->has_collision(*other->_native);
}

void Aabb::IncrementMargin(btScalar margin)
{
	_native->increment_margin(margin);
}

void Aabb::Invalidate()
{
	_native->invalidate();
}

void Aabb::Merge(Aabb^ box)
{
	_native->merge(*box->_native);
}
/*
bool Aabb::OverlappingTransCache(Aabb^ box, BT_BOX_BOX_TRANSFORM_CACHE^ transcache,
	bool fulltest)
{
	return _native->overlapping_trans_cache(*box->_native, *transcache->_native, fulltest);
}
*/
bool Aabb::OverlappingTransConservative(Aabb^ box, Matrix trans1To0)
{
	TRANSFORM_CONV(trans1To0);
	bool ret = _native->overlapping_trans_conservative(*box->_native, TRANSFORM_USE(trans1To0));
	TRANSFORM_DEL(trans1To0);
	return ret;
}
/*
bool Aabb::OverlappingTransConservative2(Aabb^ box, BT_BOX_BOX_TRANSFORM_CACHE^ trans1To0)
{
	return _native->overlapping_trans_conservative2(*box->_native, *trans1To0->_native);
}

eBT_PLANE_INTERSECTION_TYPE Aabb::PlaneClassify(Vector4 plane)
{
	return _native->plane_classify(*(btVector4*)plane->_native);
}
*/
void Aabb::ProjectionInterval(Vector3 direction, [Out] btScalar% vmin, [Out] btScalar% vmax)
{
	VECTOR3_CONV(direction);
	btScalar vminTemp, vmaxTemp;
	_native->projection_interval(VECTOR3_USE(direction), vminTemp, vmaxTemp);
	VECTOR3_DEL(direction);
	vmin = vminTemp;
	vmax = vmaxTemp;
}

Vector3 Aabb::Max::get()
{
	return Math::BtVector3ToVector3(&_native->m_max);
}
void Aabb::Max::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_max);
}

Vector3 Aabb::Min::get()
{
	return Math::BtVector3ToVector3(&_native->m_min);
}
void Aabb::Min::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_min);
}

#endif
