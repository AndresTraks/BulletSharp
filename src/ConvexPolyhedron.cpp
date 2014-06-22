#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "ConvexPolyhedron.h"

Face::Face()
{
	_native = new btFace();
}

/*
AlignedIntArray^ Face::ConnectedFaces::get()
{
	return gcnew AlignedIntArray(&_native->m_connectedFaces);
}
void Face::ConnectedFaces::set(AlignedIntArray^ value)
{
	_native->m_connectedFaces = *(btAlignedObjectArray<int>*)value->_native;
}
*/

AlignedIntArray^ Face::Indices::get()
{
	return gcnew AlignedIntArray(&_native->m_indices);
}

ScalarArray^ Face::Plane::get()
{
	return gcnew ScalarArray(_native->m_plane, 4);
}


ConvexPolyhedron::ConvexPolyhedron(btConvexPolyhedron* convexPolyhedron)
{
	_native = convexPolyhedron;
}

ConvexPolyhedron::ConvexPolyhedron()
{
	_native = new btConvexPolyhedron();
}

ConvexPolyhedron::~ConvexPolyhedron()
{
	this->!ConvexPolyhedron();
}

ConvexPolyhedron::!ConvexPolyhedron()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	//delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

bool ConvexPolyhedron::IsDisposed::get()
{
	return _native == NULL;
}

void ConvexPolyhedron::Initialize()
{
	_native->initialize();
}

void ConvexPolyhedron::Project(Matrix transform, Vector3 direction, [Out] btScalar% minProj, [Out] btScalar% maxProj, [Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	VECTOR3_DEF(direction);
	btScalar minProjTemp;
	btScalar maxProjTemp;
	btVector3* witnesPtMinTemp = ALIGNED_NEW(btVector3);
	btVector3* witnesPtMaxTemp = ALIGNED_NEW(btVector3);
	
	_native->project(*transformTemp, VECTOR3_USE(direction), minProjTemp, maxProjTemp, VECTOR3_USE(witnesPtMin), VECTOR3_USE(witnesPtMax));
	minProj = minProjTemp;
	maxProj = maxProjTemp;
	witnesPtMin = Math::BtVector3ToVector3(witnesPtMinTemp);
	witnesPtMax = Math::BtVector3ToVector3(witnesPtMaxTemp);

	ALIGNED_FREE(witnesPtMaxTemp);
	ALIGNED_FREE(witnesPtMinTemp);
	VECTOR3_DEL(direction);
	ALIGNED_FREE(transformTemp);
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
	return gcnew AlignedVector3Array(&_native->m_uniqueEdges);
}

AlignedVector3Array^ ConvexPolyhedron::Vertices::get()
{
	return gcnew AlignedVector3Array(&_native->m_vertices);
}

#endif