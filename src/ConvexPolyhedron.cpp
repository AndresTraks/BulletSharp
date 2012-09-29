#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "ConvexPolyhedron.h"

Face::Face()
{
	_unmanaged = new btFace();
}

/*
AlignedIntArray^ Face::ConnectedFaces::get()
{
	return gcnew AlignedIntArray(&_unmanaged->m_connectedFaces);
}
void Face::ConnectedFaces::set(AlignedIntArray^ value)
{
	_unmanaged->m_connectedFaces = *(btAlignedObjectArray<int>*)value->_unmanaged;
}
*/

AlignedIntArray^ Face::Indices::get()
{
	return gcnew AlignedIntArray(&_unmanaged->m_indices);
}

ScalarArray^ Face::Plane::get()
{
	return gcnew ScalarArray(_unmanaged->m_plane, 4);
}


ConvexPolyhedron::ConvexPolyhedron(btConvexPolyhedron* convexPolyhedron)
{
	_unmanaged = convexPolyhedron;
}

ConvexPolyhedron::ConvexPolyhedron()
{
	_unmanaged = new btConvexPolyhedron();
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

	//delete _unmanaged;
	_unmanaged = NULL;

	OnDisposed(this, nullptr);
}

bool ConvexPolyhedron::IsDisposed::get()
{
	return _unmanaged == NULL;
}

void ConvexPolyhedron::Initialize()
{
	_unmanaged->initialize();
}

void ConvexPolyhedron::Project(Matrix transform, Vector3 direction, [Out] btScalar% minProj, [Out] btScalar% maxProj, [Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	VECTOR3_DEF(direction);
	btScalar minProjTemp;
	btScalar maxProjTemp;
	btVector3* witnesPtMinTemp = new btVector3;
	btVector3* witnesPtMaxTemp = new btVector3;
	
	_unmanaged->project(*transformTemp, VECTOR3_USE(direction), minProjTemp, maxProjTemp, VECTOR3_USE(witnesPtMin), VECTOR3_USE(witnesPtMax));
	minProj = minProjTemp;
	maxProj = maxProjTemp;
	witnesPtMin = Math::BtVector3ToVector3(witnesPtMinTemp);
	witnesPtMax = Math::BtVector3ToVector3(witnesPtMaxTemp);

	delete witnesPtMaxTemp;
	delete witnesPtMinTemp;
	VECTOR3_DEL(direction);
	delete transformTemp;
}

bool ConvexPolyhedron::TestContainment()
{
	return _unmanaged->testContainment();
}

Vector3 ConvexPolyhedron::C::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->mC);
}
void ConvexPolyhedron::C::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->mC);
}

Vector3 ConvexPolyhedron::E::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->mE);
}
void ConvexPolyhedron::E::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->mE);
}

Vector3 ConvexPolyhedron::Extents::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_extents);
}
void ConvexPolyhedron::Extents::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_extents);
}

Vector3 ConvexPolyhedron::LocalCenter::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_localCenter);
}
void ConvexPolyhedron::LocalCenter::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_localCenter);
}

btScalar ConvexPolyhedron::Radius::get()
{
	return _unmanaged->m_radius;
}
void ConvexPolyhedron::Radius::set(btScalar value)
{
	_unmanaged->m_radius = value;
}

AlignedVector3Array^ ConvexPolyhedron::UniqueEdges::get()
{
	return gcnew AlignedVector3Array(&_unmanaged->m_uniqueEdges);
}

AlignedVector3Array^ ConvexPolyhedron::Vertices::get()
{
	return gcnew AlignedVector3Array(&_unmanaged->m_vertices);
}

#endif