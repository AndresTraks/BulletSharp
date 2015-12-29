#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "CollisionWorld.h"
#include "Dispatcher.h"
#include "PersistentManifold.h"
#include "SimulationIslandManager.h"
#include "UnionFind.h"

/*
SimulationIslandManager::IslandCallback::IslandCallback(IslandCallback* native)
{
	_native = native;
}

SimulationIslandManager::IslandCallback::~IslandCallback()
{
	this->!IslandCallback();
}

SimulationIslandManager::IslandCallback::!IslandCallback()
{
	if (this->IsDisposed)
		return;

	delete _native;
	_native = NULL;
}

void SimulationIslandManager::IslandCallback::ProcessIsland(array<CollisionObject^>^ bodies,
	array<PersistentManifold>^ manifolds, int islandId)
{
	int numBodies = bodies->Length;
	int numManifolds = manifolds->Length;
	int i;

	btCollisionObject** bodiesTemp = new btCollisionObject*[numBodies];
	btPersistentManifold** manifoldsTemp = new btPersistentManifold*[numManifolds];

	for(i=0; i<numBodies; i++)
		bodiesTemp[i] = bodies[i]->_native;

	for(i=0; i<numManifolds; i++)
		manifoldsTemp[i] = manifolds[i]._native;

	_native->processIsland(bodiesTemp, numBodies, manifoldsTemp, numManifolds, islandId);

	delete[] bodiesTemp;
	delete[] manifoldsTemp;
}

bool SimulationIslandManager::IslandCallback::IsDisposed::get()
{
	return (_native == NULL);
}
*/


SimulationIslandManager::SimulationIslandManager(btSimulationIslandManager* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

SimulationIslandManager::~SimulationIslandManager()
{
	this->!SimulationIslandManager();
}

SimulationIslandManager::!SimulationIslandManager()
{
	if (this->IsDisposed)
		return;

	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

SimulationIslandManager::SimulationIslandManager()
{
	_native = new btSimulationIslandManager();
}
/*
void SimulationIslandManager::BuildAndProcessIslands(Dispatcher^ dispatcher, CollisionWorld^ collisionWorld,
	IslandCallback^ callback)
{
	_native->buildAndProcessIslands(dispatcher->_native, collisionWorld->_native,
		callback->_native);
}
*/
void SimulationIslandManager::BuildIslands(Dispatcher^ dispatcher, CollisionWorld^ colWorld)
{
	_native->buildIslands(dispatcher->_native, colWorld->_native);
}

void SimulationIslandManager::FindUnions(Dispatcher^ dispatcher, CollisionWorld^ colWorld)
{
	_native->findUnions(dispatcher->_native, colWorld->_native);
}

void SimulationIslandManager::InitUnionFind(int n)
{
	_native->initUnionFind(n);
}

void SimulationIslandManager::StoreIslandActivationState(CollisionWorld^ world)
{
	_native->storeIslandActivationState(world->_native);
}

void SimulationIslandManager::UpdateActivationState(CollisionWorld^ colWorld, Dispatcher^ dispatcher)
{
	_native->updateActivationState(colWorld->_native, dispatcher->_native);
}

bool SimulationIslandManager::IsDisposed::get()
{
	return (_native == NULL);
}

bool SimulationIslandManager::SplitIslands::get()
{
	return _native->getSplitIslands();
}
void SimulationIslandManager::SplitIslands::set(bool doSplitIslands)
{
	_native->setSplitIslands(doSplitIslands);
}

UnionFind^ SimulationIslandManager::UnionFind::get()
{
	return gcnew BulletSharp::UnionFind(&_native->getUnionFind());
}

#endif
