#include "StdAfx.h"

#include "Dbvt.h"

Dbvt::Dbvt()
{
	_dbvt = new btDbvt();
}

Dbvt::Dbvt(btDbvt* dbvt)
{
	_dbvt = dbvt;
}

Dbvt::~Dbvt()
{
	this->!Dbvt();
}

Dbvt::!Dbvt()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_dbvt = NULL;
	
	OnDisposed( this, nullptr );
}

bool Dbvt::IsDisposed::get()
{
	return (_dbvt == NULL);
}

btDbvt* Dbvt::UnmanagedPointer::get()
{
	return _dbvt;
}
void Dbvt::UnmanagedPointer::set(btDbvt* value)
{
	_dbvt = value;
}
