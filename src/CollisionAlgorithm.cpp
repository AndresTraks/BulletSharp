#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "CollisionObject.h"
#include "Dispatcher.h"
#include "ManifoldResult.h"

CollisionAlgorithmConstructionInfo::CollisionAlgorithmConstructionInfo()
{
	_info = new btCollisionAlgorithmConstructionInfo();
}

CollisionAlgorithmConstructionInfo::CollisionAlgorithmConstructionInfo(
	BulletSharp::Dispatcher^ dispatcher, int temp)
{
	_info = new btCollisionAlgorithmConstructionInfo(dispatcher->UnmanagedPointer, temp);
}

btCollisionAlgorithmConstructionInfo* CollisionAlgorithmConstructionInfo::UnmanagedPointer::get()
{
	return _info;
}

void CollisionAlgorithmConstructionInfo::UnmanagedPointer::set(btCollisionAlgorithmConstructionInfo* value)
{
	_info = value;
}

BulletSharp::Dispatcher^ CollisionAlgorithmConstructionInfo::Dispatcher::get()
{
	return gcnew BulletSharp::Dispatcher(_info->m_dispatcher1);
}

void CollisionAlgorithmConstructionInfo::Dispatcher::set(BulletSharp::Dispatcher^ value)
{
	_info->m_dispatcher1 = value->UnmanagedPointer;
}

CollisionAlgorithm::CollisionAlgorithm(btCollisionAlgorithm* algorithm)
{
	_algorithm = algorithm;
}

CollisionAlgorithm::~CollisionAlgorithm()
{
	this->!CollisionAlgorithm();
}

CollisionAlgorithm::!CollisionAlgorithm()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_algorithm = NULL;
	
	OnDisposed( this, nullptr );
}

btScalar CollisionAlgorithm::CalculateTimeOfImpact(CollisionObject^ body0,
	CollisionObject^ body1, DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut)
{
	return _algorithm->calculateTimeOfImpact(body0->UnmanagedPointer, body1->UnmanagedPointer,
		*dispatchInfo->UnmanagedPointer, resultOut->UnmanagedPointer);
}

void CollisionAlgorithm::ProcessCollision(CollisionObject^ body0, CollisionObject^ body1,
	DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut)
{
	_algorithm->processCollision(body0->UnmanagedPointer, body1->UnmanagedPointer,
		*dispatchInfo->UnmanagedPointer, resultOut->UnmanagedPointer);
}

bool CollisionAlgorithm::IsDisposed::get()
{
	return (_algorithm == NULL);
}

btCollisionAlgorithm* CollisionAlgorithm::UnmanagedPointer::get()
{
	return _algorithm;
}
void CollisionAlgorithm::UnmanagedPointer::set(btCollisionAlgorithm* value)
{
	_algorithm = value;
}
