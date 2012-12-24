#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexCast.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConvexCast::CastResult::CastResult(btConvexCast::CastResult* castResult)
{
	_native = castResult;
}

ConvexCast::CastResult::CastResult()
{
	_native = new btConvexCast::CastResult();
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

#ifndef DISABLE_DEBUGDRAW
void ConvexCast::CastResult::DebugDraw (btScalar fraction)
{
	_native->DebugDraw(fraction);
}
#endif

void ConvexCast::CastResult::DrawCoordSystem (Matrix trans)
{
	btTransform* transTemp = Math::MatrixToBtTransform(trans);
	_native->drawCoordSystem(*transTemp);
	ALIGNED_FREE(transTemp);
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
	return DebugDraw::GetManaged(_native->m_debugDrawer);
}
void ConvexCast::CastResult::DebugDrawer::set(IDebugDraw^ value)
{
	_native->m_debugDrawer = DebugDraw::GetUnmanaged(value);
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


ConvexCast::ConvexCast(btConvexCast* convexCast)
{
	_convexCast = convexCast;
}

ConvexCast::~ConvexCast()
{
	this->!ConvexCast();
}

ConvexCast::!ConvexCast()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	_convexCast = NULL;

	OnDisposed(this, nullptr);
}

bool ConvexCast::CalcTimeOfImpact(Matrix fromA, Matrix toA, Matrix fromB, Matrix toB, CastResult^ result)
{
	btTransform* fromATemp = Math::MatrixToBtTransform(fromA);
	btTransform* toATemp = Math::MatrixToBtTransform(toA);
	btTransform* fromBTemp = Math::MatrixToBtTransform(fromB);
	btTransform* toBTemp = Math::MatrixToBtTransform(toB);

	bool ret = _convexCast->calcTimeOfImpact(*fromATemp, *toATemp, *fromBTemp, *toBTemp, *result->_native);

	ALIGNED_FREE(fromATemp);
	ALIGNED_FREE(toATemp);
	ALIGNED_FREE(fromBTemp);
	ALIGNED_FREE(toBTemp);

	return ret;
}

bool ConvexCast::IsDisposed::get()
{
	return (_convexCast == NULL);
}

btConvexCast* ConvexCast::UnmanagedPointer::get()
{
	return _convexCast;
}
void ConvexCast::UnmanagedPointer::set(btConvexCast* value)
{
	_convexCast = value;
}

#endif
