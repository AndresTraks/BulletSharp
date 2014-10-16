#include "StdAfx.h"

#include "TriangleInfoMap.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

TriangleInfoMap::TriangleInfoMap(btTriangleInfoMap* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

TriangleInfoMap::~TriangleInfoMap()
{
	this->!TriangleInfoMap();
}

TriangleInfoMap::!TriangleInfoMap()
{
	if (!_preventDelete)
	{
		delete _native;
		_native = NULL;
	}
}

TriangleInfoMap::TriangleInfoMap()
{
	_native = new btTriangleInfoMap();
}

void TriangleInfoMap::Clear()
{
	_native->clear();
}

#ifndef DISABLE_SERIALIZE
int	TriangleInfoMap::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}

String^ TriangleInfoMap::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	return gcnew String(_native->serialize(dataBuffer.ToPointer(), serializer->_native));
}
#endif

btScalar TriangleInfoMap::ConvexEpsilon::get()
{
	return _native->m_convexEpsilon;
}
void TriangleInfoMap::ConvexEpsilon::set(btScalar value)
{
	_native->m_convexEpsilon = value;
}

btScalar TriangleInfoMap::EdgeDistanceThreshold::get()
{
	return _native->m_edgeDistanceThreshold;
}
void TriangleInfoMap::EdgeDistanceThreshold::set(btScalar value)
{
	_native->m_edgeDistanceThreshold = value;
}

btScalar TriangleInfoMap::EqualVertexThreshold::get()
{
	return _native->m_equalVertexThreshold;
}
void TriangleInfoMap::EqualVertexThreshold::set(btScalar value)
{
	_native->m_equalVertexThreshold = value;
}

btScalar TriangleInfoMap::MaxEdgeAngleThreshold::get()
{
	return _native->m_maxEdgeAngleThreshold;
}
void TriangleInfoMap::MaxEdgeAngleThreshold::set(btScalar value)
{
	_native->m_maxEdgeAngleThreshold = value;
}

btScalar TriangleInfoMap::PlanarEpsilon::get()
{
	return _native->m_planarEpsilon;
}
void TriangleInfoMap::PlanarEpsilon::set(btScalar value)
{
	_native->m_planarEpsilon = value;
}

int TriangleInfoMap::Size::get()
{
	return _native->size();
}

btScalar TriangleInfoMap::ZeroAreaThreshold::get()
{
	return _native->m_zeroAreaThreshold;
}
void TriangleInfoMap::ZeroAreaThreshold::set(btScalar value)
{
	_native->m_zeroAreaThreshold = value;
}
