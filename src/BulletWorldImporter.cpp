#include "StdAfx.h"

#ifndef DISABLE_SERIALIZE

#pragma managed(push, off)
#include <..\Extras\Serialize\BulletWorldImporter\btBulletWorldImporter.h>
#pragma managed(pop)

#include "BulletWorldImporter.h"
#include "StringConv.h"

Serialize::BulletWorldImporter::BulletWorldImporter(DynamicsWorld^ world)
{
	if (world == nullptr)
		_importer = new btBulletWorldImporter(0);
	else
		_importer = new btBulletWorldImporter(world->UnmanagedPointer);
}

Serialize::BulletWorldImporter::BulletWorldImporter()
{
	_importer = new btBulletWorldImporter();
}

Serialize::BulletWorldImporter::~BulletWorldImporter()
{
	this->!BulletWorldImporter();
}

Serialize::BulletWorldImporter::!BulletWorldImporter()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	delete _importer;
	_importer = NULL;
	
	OnDisposed( this, nullptr );
}

void Serialize::BulletWorldImporter::DeleteAllData()
{
	_importer->deleteAllData();
}

bool Serialize::BulletWorldImporter::LoadFile(String^ filename)
{
	const char* filenameTemp = StringConv::ManagedToUnmanaged(filename);
	bool ret = _importer->loadFile(filenameTemp);
	StringConv::FreeUnmanagedString(filenameTemp);
	return ret;
}

bool Serialize::BulletWorldImporter::IsDisposed::get()
{
	return (_importer == NULL);
}

bool Serialize::BulletWorldImporter::NumBvhs::get()
{
	return _importer->getNumBvhs();
}

bool Serialize::BulletWorldImporter::NumConstraints::get()
{
	return _importer->getNumConstraints();
}

bool Serialize::BulletWorldImporter::NumCollisionShapes::get()
{
	return _importer->getNumCollisionShapes();
}

bool Serialize::BulletWorldImporter::NumRigidBodies::get()
{
	return _importer->getNumRigidBodies();
}

bool Serialize::BulletWorldImporter::NumTriangleInfoMaps::get()
{
	return _importer->getNumTriangleInfoMaps();
}

bool Serialize::BulletWorldImporter::VerboseMode::get()
{
	return _importer->getVerboseMode();
}
void Serialize::BulletWorldImporter::VerboseMode::set(bool value)
{
	_importer->setVerboseMode(value);
}

#endif
