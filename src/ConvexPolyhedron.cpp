#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "ConvexPolyhedron.h"

Face::Face()
{
	_face = new btFace();
}

/*
AlignedIntArray^ Face::ConnectedFaces::get()
{
	return gcnew AlignedIntArray(&_face->m_connectedFaces);
}
void Face::ConnectedFaces::set(AlignedIntArray^ value)
{
	_face->m_connectedFaces = *(btAlignedObjectArray<int>*)value->_unmanaged;
}
*/

AlignedIntArray^ Face::Indices::get()
{
	return gcnew AlignedIntArray(&_face->m_indices);
}
void Face::Indices::set(AlignedIntArray^ value)
{
	_face->m_indices = *(btAlignedObjectArray<int>*)value->_unmanaged;
}

ScalarArray^ Face::Plane::get()
{
	return gcnew ScalarArray(_face->m_plane, 4);
}

btFace* Face::UnmanagedPointer::get()
{
	return _face;
}
void Face::UnmanagedPointer::set(btFace* value)
{
	_face = value;
}


ConvexPolyhedron::ConvexPolyhedron(btConvexPolyhedron* convexPolyhedron)
{
	_convexPolyhedron = convexPolyhedron;
}

ConvexPolyhedron::ConvexPolyhedron()
{
	_convexPolyhedron = new btConvexPolyhedron();
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

	_convexPolyhedron = NULL;

	OnDisposed(this, nullptr);
}

bool ConvexPolyhedron::IsDisposed::get()
{
	return _convexPolyhedron == NULL;
}

void ConvexPolyhedron::Initialize()
{
	_convexPolyhedron->initialize();
}

void ConvexPolyhedron::Project(Matrix transform, Vector3 direction, [Out] btScalar% min, [Out] btScalar% max)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	btVector3* directionTemp = Math::Vector3ToBtVector3(direction);
	btScalar minTemp;
	btScalar maxTemp;
	
	_convexPolyhedron->project(*transformTemp, *directionTemp, minTemp, maxTemp);
	min = minTemp;
	max = maxTemp;
	
	delete directionTemp;
	delete transformTemp;
}

bool ConvexPolyhedron::TestContainment()
{
	return _convexPolyhedron->testContainment();
}

Vector3 ConvexPolyhedron::C::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->mC);
}
void ConvexPolyhedron::C::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->mC);
}

Vector3 ConvexPolyhedron::E::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->mE);
}
void ConvexPolyhedron::E::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->mE);
}

Vector3 ConvexPolyhedron::Extents::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->m_extents);
}
void ConvexPolyhedron::Extents::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->m_extents);
}

Vector3 ConvexPolyhedron::LocalCenter::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->m_localCenter);
}
void ConvexPolyhedron::LocalCenter::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->m_localCenter);
}

btScalar ConvexPolyhedron::Radius::get()
{
	return _convexPolyhedron->m_radius;
}
void ConvexPolyhedron::Radius::set(btScalar value)
{
	_convexPolyhedron->m_radius = value;
}

AlignedVector3Array^ ConvexPolyhedron::UniqueEdges::get()
{
	return gcnew AlignedVector3Array(&_convexPolyhedron->m_uniqueEdges);
}
void ConvexPolyhedron::UniqueEdges::set(AlignedVector3Array^ value)
{
	_convexPolyhedron->m_uniqueEdges = *(btAlignedObjectArray<btVector3>*)value->_unmanaged;
}

AlignedVector3Array^ ConvexPolyhedron::Vertices::get()
{
	return gcnew AlignedVector3Array(&_convexPolyhedron->m_vertices);
}
void ConvexPolyhedron::Vertices::set(AlignedVector3Array^ value)
{
	_convexPolyhedron->m_vertices = *(btAlignedObjectArray<btVector3>*)value->_unmanaged;
}

btConvexPolyhedron* ConvexPolyhedron::UnmanagedPointer::get()
{
	return _convexPolyhedron;
}
void ConvexPolyhedron::UnmanagedPointer::set(btConvexPolyhedron* value)
{
	_convexPolyhedron = value;
}

#endif