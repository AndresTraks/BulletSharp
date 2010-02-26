#include "StdAfx.h"

#include "Dispatcher.h"

Dispatcher::Dispatcher(btDispatcher* dispatcher)
{
	_dispatcher = dispatcher;
}

Dispatcher::~Dispatcher()
{
	this->!Dispatcher();
}

Dispatcher::!Dispatcher()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_dispatcher = NULL;
	
	OnDisposed( this, nullptr );
}

bool Dispatcher::IsDisposed::get()
{
	return (_dispatcher == NULL);
}

btDispatcher* Dispatcher::UnmanagedPointer::get()
{
	return _dispatcher;
}
void Dispatcher::UnmanagedPointer::set(btDispatcher* value)
{
	_dispatcher = value;
}
