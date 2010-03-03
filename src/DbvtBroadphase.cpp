#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "Dbvt.h"
#include "DbvtBroadphase.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

DbvtProxy::DbvtProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
	CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask)
: BroadphaseProxy(new btDbvtProxy(*Math::Vector3ToBtVec3(aabbMin),
	*Math::Vector3ToBtVec3(aabbMax), userPtr.ToPointer(),
	(short int)collisionFilterGroup, (short int)collisionFilterMask))
{
}

DbvtProxy::DbvtProxy(btDbvtProxy* proxy)
: BroadphaseProxy(proxy)
{
}

DbvtNode^ DbvtProxy::Leaf::get()
{
	return gcnew DbvtNode(UnmanagedPointer->leaf);
}
void DbvtProxy::Leaf::set(DbvtNode^ value)
{
	UnmanagedPointer->leaf = value->UnmanagedPointer;
}

btDbvtProxy* DbvtProxy::UnmanagedPointer::get()
{
	return (btDbvtProxy*)BroadphaseProxy::UnmanagedPointer;
}


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

void DbvtBroadphase::SetAabbForceUpdate(BroadphaseProxy^ absproxy,
	Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	UnmanagedPointer->setAabbForceUpdate(absproxy->UnmanagedPointer,
		*Math::Vector3ToBtVec3(aabbMin), *Math::Vector3ToBtVec3(aabbMax),
		dispatcher->UnmanagedPointer
	);
}

array<Dbvt^>^ DbvtBroadphase::Sets::get()
{
	array<Dbvt^>^ sets = gcnew array<Dbvt^>(2);
	sets[0] = gcnew Dbvt(&UnmanagedPointer->m_sets[0]);
	sets[1] = gcnew Dbvt(&UnmanagedPointer->m_sets[1]);
	return sets;
}
void DbvtBroadphase::Sets::set(array<Dbvt^>^ value)
{
	UnmanagedPointer->m_sets[0] = *value[0]->UnmanagedPointer;
	UnmanagedPointer->m_sets[1] = *value[1]->UnmanagedPointer;
}

array<DbvtProxy^>^ DbvtBroadphase::StageRoots::get()
{
	array<DbvtProxy^>^ stageRoots = gcnew array<DbvtProxy^>(StageCount+1);
	int i;
	for (i=0; i<StageCount+1; i++)
		stageRoots[i] = gcnew DbvtProxy(UnmanagedPointer->m_stageRoots[i]);
	return stageRoots;
}
void DbvtBroadphase::StageRoots::set(array<DbvtProxy^>^ value)
{
	int i;
	for (i=0; i<StageCount+1; i++)
		UnmanagedPointer->m_stageRoots[i] = value[i]->UnmanagedPointer;
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
