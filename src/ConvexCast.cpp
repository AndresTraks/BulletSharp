#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexCast.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConvexCast::CastResult::CastResult(btConvexCast::CastResult* native)
{
	_native = native;
}

ConvexCast::CastResult::~CastResult()
{
	this->!CastResult();
}

ConvexCast::CastResult::!CastResult()
{
	delete _native;
	_native = NULL;
}

ConvexCast::CastResult::CastResult()
{
	_native = new btConvexCast::CastResult();
}

#ifndef DISABLE_DEBUGDRAW
void ConvexCast::CastResult::DebugDraw(btScalar fraction)
{
	_native->DebugDraw(fraction);
}
#endif

void ConvexCast::CastResult::DrawCoordSystem(Matrix trans)
{
	TRANSFORM_CONV(trans);
	_native->drawCoordSystem(TRANSFORM_USE(trans));
	TRANSFORM_DEL(trans);
}

void ConvexCast::CastResult::ReportFailure(int errNo, int numIterations)
{
	_native->reportFailure(errNo, numIterations);
}

btScalar ConvexCast::CastResult::AllowedPenetration::get()
{
	return _native->m_allowedPenetration;
}
void ConvexCast::CastResult::AllowedPenetration::set(btScalar value)
{
	_native->m_allowedPenetration = value;
}

#ifndef DISABLE_DEBUGDRAW
IDebugDraw^ ConvexCast::CastResult::DebugDrawer::get()
{
	return _debugDrawer;
}
void ConvexCast::CastResult::DebugDrawer::set(IDebugDraw^ value)
{
	if (_debugDrawer)
	{
		if (_debugDrawer == value) {
			return;
		}

		// Clear IDebugDraw wrapper
		if (!dynamic_cast<BulletSharp::DebugDraw^>(_debugDrawer)) {
			delete _native->m_debugDrawer;
		}
	}

	_debugDrawer = value;
	if (!value) {
		_native->m_debugDrawer = 0;
		return;
	}

	BulletSharp::DebugDraw^ cast = dynamic_cast<BulletSharp::DebugDraw^>(value);
	if (cast != nullptr) {
		_native->m_debugDrawer = cast->_native;
	} else {
		// Create IDebugDraw wrapper, remember to delete it
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(value, false);
		_native->m_debugDrawer = wrapper;
	}
}
#endif

btScalar ConvexCast::CastResult::Fraction::get()
{
	return _native->m_fraction;
}
void ConvexCast::CastResult::Fraction::set(btScalar value)
{
	_native->m_fraction = value;
}

Vector3 ConvexCast::CastResult::HitPoint::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitPoint);
}
void ConvexCast::CastResult::HitPoint::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitPoint);
}

Matrix ConvexCast::CastResult::HitTransformA::get()
{
	return Math::BtTransformToMatrix(&_native->m_hitTransformA);
}
void ConvexCast::CastResult::HitTransformA::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_hitTransformA);
}

Matrix ConvexCast::CastResult::HitTransformB::get()
{
	return Math::BtTransformToMatrix(&_native->m_hitTransformB);
}
void ConvexCast::CastResult::HitTransformB::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_hitTransformB);
}

Vector3 ConvexCast::CastResult::Normal::get()
{
	return Math::BtVector3ToVector3(&_native->m_normal);
}
void ConvexCast::CastResult::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_normal);
}

bool ConvexCast::CastResult::IsDisposed::get()
{
	return (_native == NULL);
}


ConvexCast::ConvexCast(btConvexCast* native)
{
	_native = native;
}

ConvexCast::~ConvexCast()
{
	this->!ConvexCast();
}

ConvexCast::!ConvexCast()
{
	if (this->IsDisposed)
		return;

	delete _native;
	_native = NULL;
}

bool ConvexCast::CalcTimeOfImpact(Matrix fromA, Matrix toA, Matrix fromB, Matrix toB,
	CastResult^ result)
{
	TRANSFORM_CONV(fromA);
	TRANSFORM_CONV(toA);
	TRANSFORM_CONV(fromB);
	TRANSFORM_CONV(toB);
	bool ret = _native->calcTimeOfImpact(TRANSFORM_USE(fromA), TRANSFORM_USE(toA),
		TRANSFORM_USE(fromB), TRANSFORM_USE(toB), *result->_native);
	TRANSFORM_DEL(fromA);
	TRANSFORM_DEL(toA);
	TRANSFORM_DEL(fromB);
	TRANSFORM_DEL(toB);
	return ret;
}

bool ConvexCast::IsDisposed::get()
{
	return (_native == NULL);
}

#endif
