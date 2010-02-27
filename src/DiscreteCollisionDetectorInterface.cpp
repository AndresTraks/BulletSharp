#include "StdAfx.h"

#include "DiscreteCollisionDetectorInterface.h"

DiscreteCollisionDetectorInterface::Result::Result(
	btDiscreteCollisionDetectorInterface::Result* result)
{
	_result = result;
}

DiscreteCollisionDetectorInterface::Result::~Result()
{
	this->DiscreteCollisionDetectorInterface::Result::!Result();
}

DiscreteCollisionDetectorInterface::Result::!Result()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_result = NULL;
	
	OnDisposed( this, nullptr );
}

bool DiscreteCollisionDetectorInterface::Result::IsDisposed::get()
{
	return (_result == NULL);
}

btDiscreteCollisionDetectorInterface::Result* DiscreteCollisionDetectorInterface::Result::UnmanagedPointer::get()
{
	return _result;
}
void DiscreteCollisionDetectorInterface::Result::UnmanagedPointer::set(btDiscreteCollisionDetectorInterface::Result* value)
{
	_result = value;
}


DiscreteCollisionDetectorInterface::DiscreteCollisionDetectorInterface(
	btDiscreteCollisionDetectorInterface* detectorInterface)
{
	_detectorInterface = detectorInterface;
}

DiscreteCollisionDetectorInterface::~DiscreteCollisionDetectorInterface()
{
	this->!DiscreteCollisionDetectorInterface();
}

DiscreteCollisionDetectorInterface::!DiscreteCollisionDetectorInterface()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_detectorInterface = NULL;
	
	OnDisposed( this, nullptr );
}

bool DiscreteCollisionDetectorInterface::IsDisposed::get()
{
	return (_detectorInterface == NULL);
}

btDiscreteCollisionDetectorInterface* DiscreteCollisionDetectorInterface::UnmanagedPointer::get()
{
	return _detectorInterface;
}
void DiscreteCollisionDetectorInterface::UnmanagedPointer::set(btDiscreteCollisionDetectorInterface* value)
{
	_detectorInterface = value;
}
