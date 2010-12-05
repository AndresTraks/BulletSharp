#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Dispatcher.h"
#include "CollisionWorld.h"
#include "PersistentManifold.h"
#include "SimulationIslandManager.h"
#include "UnionFind.h"

void SimulationIslandManager::IslandCallback::ProcessIsland(array<CollisionObject^>^ bodies, array<PersistentManifold^>^ manifolds, int islandId)
{
	int numBodies = bodies->Length;
	int numManifolds = manifolds->Length;
	int i;

	btCollisionObject** bodiesTemp = new btCollisionObject*[numBodies];
	btPersistentManifold** manifoldsTemp = new btPersistentManifold*[numManifolds];

	for(i=0; i<numBodies; i++)
		bodiesTemp[i] = bodies[i]->UnmanagedPointer;

	for(i=0; i<numManifolds; i++)
		manifoldsTemp[i] = manifolds[i]->UnmanagedPointer;


	UnmanagedPointer->ProcessIsland(bodiesTemp, numBodies, manifoldsTemp, numManifolds, islandId);

	delete[] bodiesTemp;
	delete[] manifoldsTemp;
}

btSimulationIslandManager::IslandCallback* SimulationIslandManager::IslandCallback::UnmanagedPointer::get()
{
	return _islandCallback;
}
void SimulationIslandManager::IslandCallback::UnmanagedPointer::set(btSimulationIslandManager::IslandCallback* value)
{
	_islandCallback = value;
}

SimulationIslandManager::IslandCallback::~IslandCallback()
{
	this->!IslandCallback();
}

SimulationIslandManager::IslandCallback::!IslandCallback()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	_islandCallback = NULL;
	
	OnDisposed(this, nullptr);
}

bool SimulationIslandManager::IslandCallback::IsDisposed::get()
{
	return (_islandCallback == NULL);
}


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
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	_manager = NULL;
	
	OnDisposed(this, nullptr);
}

void SimulationIslandManager::BuildAndProcessIslands(Dispatcher^ dispatcher, CollisionWorld^ collisionWorld, IslandCallback^ callback)
{
	UnmanagedPointer->buildAndProcessIslands(dispatcher->UnmanagedPointer, collisionWorld->UnmanagedPointer, callback->UnmanagedPointer);
}

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

UnionFind^ SimulationIslandManager::UnionFind::get()
{
	return gcnew BulletSharp::UnionFind(&UnmanagedPointer->getUnionFind());
}

btSimulationIslandManager* SimulationIslandManager::UnmanagedPointer::get()
{
	return _manager;
}
void SimulationIslandManager::UnmanagedPointer::set(btSimulationIslandManager* value)
{
	_manager = value;
}

#endif
