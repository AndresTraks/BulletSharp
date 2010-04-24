#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btSimulationIslandManager.h>
#pragma managed(pop)

#include "Dispatcher.h"
#include "CollisionWorld.h"
#include "SimulationIslandManager.h"

SimulationIslandManager::SimulationIslandManager()
{
	_manager = new btSimulationIslandManager();
}

SimulationIslandManager::SimulationIslandManager(btSimulationIslandManager* manager)
{
	_manager = manager;
}

SimulationIslandManager::~SimulationIslandManager()
{
	this->!SimulationIslandManager();
}

SimulationIslandManager::!SimulationIslandManager()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_manager = NULL;
	
	OnDisposed( this, nullptr );
}

//void SimulationIslandManager::BuildAndProcessIslands(Dispatcher^ dispatcher, CollisionWorld^ collisionWorld, IslandCallback^ callback)
//{
//	UnmanagedPointer->buildAndProcessIslands(dispatcher->UnmanagedPointer, collisionWorld->UnmanagedPointer, callback->UnmanagedPointer);
//}

void SimulationIslandManager::BuildIslands(Dispatcher^ dispatcher, CollisionWorld^ colWorld)
{
	UnmanagedPointer->buildIslands(dispatcher->UnmanagedPointer, colWorld->UnmanagedPointer);
}

void SimulationIslandManager::FindUnions(Dispatcher^ dispatcher, CollisionWorld^ colWorld)
{
	UnmanagedPointer->findUnions(dispatcher->UnmanagedPointer, colWorld->UnmanagedPointer);
}

void SimulationIslandManager::InitUnionFind(int n)
{
	UnmanagedPointer->initUnionFind(n);
}

void SimulationIslandManager::UpdateActivationState(CollisionWorld^ colWorld, Dispatcher^ dispatcher)
{
	UnmanagedPointer->updateActivationState(colWorld->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

void SimulationIslandManager::StoreIslandActivationState(CollisionWorld^ world)
{
	UnmanagedPointer->storeIslandActivationState(world->UnmanagedPointer);
}

bool SimulationIslandManager::IsDisposed::get()
{
	return (_manager == NULL);
}

bool SimulationIslandManager::SplitIslands::get()
{
	return UnmanagedPointer->getSplitIslands();
}
void SimulationIslandManager::SplitIslands::set(bool value)
{
	UnmanagedPointer->setSplitIslands(value);
}

btSimulationIslandManager* SimulationIslandManager::UnmanagedPointer::get()
{
	return _manager;
}
void SimulationIslandManager::UnmanagedPointer::set(btSimulationIslandManager* value)
{
	_manager = value;
}
