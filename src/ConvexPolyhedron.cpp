#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "ConvexPolyhedron.h"

Face::Face(btFace* native)
{
	_native = native;
}

Face::~Face()
{
	this->!Face();
}

Face::!Face()
{
	delete _native;
	_native = NULL;
}

Face::Face()
{
	_native = new btFace();
}

/*
AlignedIntArray^ Face::ConnectedFaces::get()
{
	return gcnew AlignedIntArray(&_native->m_connectedFaces);
}
*/

AlignedIntArray^ Face::Indices::get()
{
	if (_indices == nullptr)
	{
		_indices = gcnew AlignedIntArray(&_native->m_indices);
	}
	return _indices;
}

ScalarArray^ Face::Plane::get()
{
	if (_plane == nullptr)
	{
		_plane = gcnew ScalarArray(_native->m_plane, 4);
	}
	return _plane;
}


ConvexPolyhedron::ConvexPolyhedron(btConvexPolyhedron* native)
{
	_native = native;
}

ConvexPolyhedron::~ConvexPolyhedron()
{
	this->!ConvexPolyhedron();
}

ConvexPolyhedron::!ConvexPolyhedron()
{
	delete _native;
	_native = NULL;
}

ConvexPolyhedron::ConvexPolyhedron()
{
	_native = new btConvexPolyhedron();
}

void ConvexPolyhedron::Initialize()
{
	_native->initialize();
}

void ConvexPolyhedron::ProjectRef(Matrix% transform, Vector3% direction, [Out] btScalar% minProj,
	[Out] btScalar% maxProj, [Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax)
{
	TRANSFORM_CONV(transform);
	VECTOR3_CONV(direction);
	btScalar minProjTemp;
	btScalar maxProjTemp;
	btVector3* witnesPtMinTemp = ALIGNED_NEW(btVector3);
	btVector3* witnesPtMaxTemp = ALIGNED_NEW(btVector3);
	_native->project(TRANSFORM_USE(transform), VECTOR3_USE(direction), minProjTemp, maxProjTemp,
		VECTOR3_USE(witnesPtMin), VECTOR3_USE(witnesPtMax));
	VECTOR3_DEL(direction);
	TRANSFORM_DEL(transform);
	witnesPtMin = Math::BtVector3ToVector3(witnesPtMinTemp);
	witnesPtMax = Math::BtVector3ToVector3(witnesPtMaxTemp);
	ALIGNED_FREE(witnesPtMaxTemp);
	ALIGNED_FREE(witnesPtMinTemp);
}

void ConvexPolyhedron::Project(Matrix transform, Vector3 direction, [Out] btScalar% minProj, [Out] btScalar% maxProj,
	[Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax)
{
	TRANSFORM_CONV(transform);
	VECTOR3_CONV(direction);
	btScalar minProjTemp;
	btScalar maxProjTemp;
	btVector3* witnesPtMinTemp = ALIGNED_NEW(btVector3);
	btVector3* witnesPtMaxTemp = ALIGNED_NEW(btVector3);
	_native->project(TRANSFORM_USE(transform), VECTOR3_USE(direction), minProjTemp, maxProjTemp,
		VECTOR3_USE(witnesPtMin), VECTOR3_USE(witnesPtMax));
	VECTOR3_DEL(direction);
	TRANSFORM_DEL(transform);
	witnesPtMin = Math::BtVector3ToVector3(witnesPtMinTemp);
	witnesPtMax = Math::BtVector3ToVector3(witnesPtMaxTemp);
	ALIGNED_FREE(witnesPtMaxTemp);
	ALIGNED_FREE(witnesPtMinTemp);
	minProj = minProjTemp;
	maxProj = maxProjTemp;
}

bool ConvexPolyhedron::TestContainment()
{
	return _native->testContainment();
}

Vector3 ConvexPolyhedron::C::get()
{
	return Math::BtVector3ToVector3(&_native->mC);
}
void ConvexPolyhedron::C::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->mC);
}

Vector3 ConvexPolyhedron::E::get()
{
	return Math::BtVector3ToVector3(&_native->mE);
}
void ConvexPolyhedron::E::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->mE);
}

Vector3 ConvexPolyhedron::Extents::get()
{
	return Math::BtVector3ToVector3(&_native->m_extents);
}
void ConvexPolyhedron::Extents::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_extents);
}
/*
AlignedFaceArray^ ConvexPolyhedron::Faces::get()
{
	return _native->m_faces;
}
*/
bool ConvexPolyhedron::IsDisposed::get()
{
	return _native == NULL;
}

Vector3 ConvexPolyhedron::LocalCenter::get()
{
	return Math::BtVector3ToVector3(&_native->m_localCenter);
}
void ConvexPolyhedron::LocalCenter::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_localCenter);
}

btScalar ConvexPolyhedron::Radius::get()
{
	return _native->m_radius;
}
void ConvexPolyhedron::Radius::set(btScalar value)
{
	_native->m_radius = value;
}

AlignedVector3Array^ ConvexPolyhedron::UniqueEdges::get()
{
	if (_uniqueEdges == nullptr)
	{
		_uniqueEdges = gcnew AlignedVector3Array(&_native->m_uniqueEdges);
	}
	return _uniqueEdges;
}

AlignedVector3Array^ ConvexPolyhedron::Vertices::get()
{
	if (_vertices == nullptr)
	{
		_vertices = gcnew AlignedVector3Array(&_native->m_vertices);
	}
	return _vertices;
}

#endif
