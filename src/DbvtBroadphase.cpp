#include "StdAfx.h"

#include "DbvtBroadphase.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

DbvtBroadphase::DbvtBroadphase()
: BroadphaseInterface(new btDbvtBroadphase())
{
}

DbvtBroadphase::DbvtBroadphase(BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(new btDbvtBroadphase(pairCache->UnmanagedPointer))
{
}

void DbvtBroadphase::Benchmark(BroadphaseInterface^ broadphase)
{
	btDbvtBroadphase::benchmark(broadphase->UnmanagedPointer);
}

void DbvtBroadphase::Collide(Dispatcher^ dispatcher)
{
	UnmanagedPointer->collide(dispatcher->UnmanagedPointer);
}

void DbvtBroadphase::Optimize()
{
	UnmanagedPointer->optimize();
}

void DbvtBroadphase::PerformDeferredRemoval(Dispatcher^ dispatcher)
{
	UnmanagedPointer->performDeferredRemoval(dispatcher->UnmanagedPointer);
}

btScalar DbvtBroadphase::VelocityPrediction::get()
{
	return UnmanagedPointer->getVelocityPrediction();
}

void DbvtBroadphase::VelocityPrediction::set(btScalar prediction)
{
	UnmanagedPointer->setVelocityPrediction(prediction);
}

btDbvtBroadphase* DbvtBroadphase::UnmanagedPointer::get()
{
	return (btDbvtBroadphase*)BroadphaseInterface::UnmanagedPointer;
}
