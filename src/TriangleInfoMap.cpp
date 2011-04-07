#include "StdAfx.h"

#include "TriangleInfoMap.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

TriangleInfoMap::TriangleInfoMap()
{
	_triangleInfoMap = new btTriangleInfoMap();
}

void TriangleInfoMap::Clear()
{
	_triangleInfoMap->clear();
}

#ifndef DISABLE_SERIALIZE
int	TriangleInfoMap::CalculateSerializeBufferSize()
{
	return _triangleInfoMap->calculateSerializeBufferSize();
}

String^ TriangleInfoMap::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	const char* name = UnmanagedPointer->serialize(dataBuffer.ToPointer(), serializer->UnmanagedPointer);
	return gcnew String(name);
}
#endif

btScalar TriangleInfoMap::ConvexEpsilon::get()
{
	return _triangleInfoMap->m_convexEpsilon;
}
void TriangleInfoMap::ConvexEpsilon::set(btScalar value)
{
	_triangleInfoMap->m_convexEpsilon = value;
}

btScalar TriangleInfoMap::EdgeDistanceThreshold::get()
{
	return _triangleInfoMap->m_edgeDistanceThreshold;
}
void TriangleInfoMap::EdgeDistanceThreshold::set(btScalar value)
{
	_triangleInfoMap->m_edgeDistanceThreshold = value;
}

btScalar TriangleInfoMap::EqualVertexThreshold::get()
{
	return _triangleInfoMap->m_equalVertexThreshold;
}
void TriangleInfoMap::EqualVertexThreshold::set(btScalar value)
{
	_triangleInfoMap->m_equalVertexThreshold = value;
}

btScalar TriangleInfoMap::MaxEdgeAngleThreshold::get()
{
	return _triangleInfoMap->m_maxEdgeAngleThreshold;
}
void TriangleInfoMap::MaxEdgeAngleThreshold::set(btScalar value)
{
	_triangleInfoMap->m_maxEdgeAngleThreshold = value;
}

btScalar TriangleInfoMap::PlanarEpsilon::get()
{
	return _triangleInfoMap->m_planarEpsilon;
}
void TriangleInfoMap::PlanarEpsilon::set(btScalar value)
{
	_triangleInfoMap->m_planarEpsilon = value;
}

int TriangleInfoMap::Size::get()
{
	return _triangleInfoMap->size();
}

btScalar TriangleInfoMap::ZeroAreaThreshold::get()
{
	return _triangleInfoMap->m_zeroAreaThreshold;
}
void TriangleInfoMap::ZeroAreaThreshold::set(btScalar value)
{
	_triangleInfoMap->m_zeroAreaThreshold = value;
}

btTriangleInfoMap* TriangleInfoMap::UnmanagedPointer::get()
{
	return _triangleInfoMap;
}
void TriangleInfoMap::UnmanagedPointer::set(btTriangleInfoMap* value)
{
	_triangleInfoMap = value;
}
