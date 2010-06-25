#include "StdAfx.h"

#include "ConvexCast.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConvexCast::CastResult::CastResult(btConvexCast::CastResult* castResult)
{
	_castResult = castResult;
}

ConvexCast::CastResult::~CastResult()
{
	this->!CastResult();
}

ConvexCast::CastResult::!CastResult()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_castResult = NULL;

	OnDisposed( this, nullptr );
}

ConvexCast::CastResult::CastResult()
{
	_castResult = new btConvexCast::CastResult();
}

#ifndef DISABLE_DEBUGDRAW
void ConvexCast::CastResult::DebugDraw (btScalar fraction)
{
	_castResult->DebugDraw(fraction);
}
#endif

void ConvexCast::CastResult::DrawCoordSystem (Matrix trans)
{
	btTransform* transTemp = Math::MatrixToBtTransform(trans);
	_castResult->drawCoordSystem(*transTemp);
	delete transTemp;
}

btScalar ConvexCast::CastResult::AllowedPenetration::get()
{
	return _castResult->m_allowedPenetration;
}
void ConvexCast::CastResult::AllowedPenetration::set(btScalar value)
{
	_castResult->m_allowedPenetration = value;
}

DebugDraw^ ConvexCast::CastResult::DebugDrawer::get()
{
	return gcnew BulletSharp::DebugDraw((DebugDrawWrapper*)_castResult->m_debugDrawer);
}
void ConvexCast::CastResult::DebugDrawer::set(BulletSharp::DebugDraw^ value)
{
	_castResult->m_debugDrawer = value->UnmanagedPointer;
}

btScalar ConvexCast::CastResult::Fraction::get()
{
	return _castResult->m_fraction;
}
void ConvexCast::CastResult::Fraction::set(btScalar value)
{
	_castResult->m_fraction = value;
}

Vector3 ConvexCast::CastResult::HitPoint::get()
{
	return Math::BtVector3ToVector3(&_castResult->m_hitPoint);
}
void ConvexCast::CastResult::HitPoint::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_castResult->m_hitPoint);
}

Matrix ConvexCast::CastResult::HitTransformA::get()
{
	return Math::BtTransformToMatrix(&_castResult->m_hitTransformA);
}
void ConvexCast::CastResult::HitTransformA::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_castResult->m_hitTransformA);
}

Matrix ConvexCast::CastResult::HitTransformB::get()
{
	return Math::BtTransformToMatrix(&_castResult->m_hitTransformB);
}
void ConvexCast::CastResult::HitTransformB::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_castResult->m_hitTransformB);
}

Vector3 ConvexCast::CastResult::Normal::get()
{
	return Math::BtVector3ToVector3(&_castResult->m_normal);
}
void ConvexCast::CastResult::Normal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_castResult->m_normal);
}

bool ConvexCast::CastResult::IsDisposed::get()
{
	return (_castResult == NULL);
}

btConvexCast::CastResult* ConvexCast::CastResult::UnmanagedPointer::get()
{
	return _castResult;
}
void ConvexCast::CastResult::UnmanagedPointer::set(btConvexCast::CastResult* value)
{
	_castResult = value;
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
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_convexCast = NULL;

	OnDisposed( this, nullptr );
}

bool ConvexCast::CalcTimeOfImpact(Matrix fromA, Matrix toA, Matrix fromB, Matrix toB, CastResult^ result)
{
	btTransform* fromATemp = Math::MatrixToBtTransform(fromA);
	btTransform* toATemp = Math::MatrixToBtTransform(toA);
	btTransform* fromBTemp = Math::MatrixToBtTransform(fromB);
	btTransform* toBTemp = Math::MatrixToBtTransform(toB);

	bool ret = _convexCast->calcTimeOfImpact(*fromATemp, *toATemp, *fromBTemp, *toBTemp, *result->UnmanagedPointer);

	delete fromATemp;
	delete toATemp;
	delete fromBTemp;
	delete toBTemp;

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
