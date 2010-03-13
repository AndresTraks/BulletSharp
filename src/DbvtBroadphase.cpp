#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "DbvtBroadphase.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif


#ifndef DISABLE_DBVT

DbvtProxy::DbvtProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
	CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask)
: BroadphaseProxy(new btDbvtProxy(*Math::Vector3ToBtVector3(aabbMin),
	*Math::Vector3ToBtVector3(aabbMax), userPtr.ToPointer(),
	(short int)collisionFilterGroup, (short int)collisionFilterMask))
{
}

DbvtProxy::DbvtProxy(btDbvtProxy* proxy)
: BroadphaseProxy(proxy)
{
}

DbvtNode^ DbvtProxy::Leaf::get()
{
	if (UnmanagedPointer->leaf == nullptr)
		return nullptr;
	return gcnew DbvtNode(UnmanagedPointer->leaf);
}
void DbvtProxy::Leaf::set(DbvtNode^ value)
{
	UnmanagedPointer->leaf = value->UnmanagedPointer;
}

array<DbvtProxy^>^ DbvtProxy::Links::get()
{
	array<DbvtProxy^>^ links = gcnew array<DbvtProxy^>(2);
	
	if (UnmanagedPointer->links[0] == nullptr)
		links[0] = nullptr;
	else
		links[0] = gcnew DbvtProxy(UnmanagedPointer->links[0]);
	
	if (UnmanagedPointer->links[1] == nullptr)
		links[1] = nullptr;
	else
		links[1] = gcnew DbvtProxy(UnmanagedPointer->links[1]);
	
	return links;
}
void DbvtProxy::Links::set(array<DbvtProxy^>^ value)
{
	UnmanagedPointer->links[0] = value[0]->UnmanagedPointer;
	UnmanagedPointer->links[1] = value[1]->UnmanagedPointer;
}

int DbvtProxy::Stage::get()
{
	return UnmanagedPointer->stage;
}
void DbvtProxy::Stage::set(int value)
{
	UnmanagedPointer->stage = value;
}

btDbvtProxy* DbvtProxy::UnmanagedPointer::get()
{
	return (btDbvtProxy*)BroadphaseProxy::UnmanagedPointer;
}

#endif


DbvtBroadphase::DbvtBroadphase()
: BroadphaseInterface(new btDbvtBroadphase())
{
}

DbvtBroadphase::DbvtBroadphase(BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(new btDbvtBroadphase(pairCache->UnmanagedPointer))
{
}

#ifndef DISABLE_DBVT

void DbvtBroadphase::Benchmark(BroadphaseInterface^ broadphase)
{
	btDbvtBroadphase::benchmark(broadphase->UnmanagedPointer);
}

void DbvtBroadphase::Collide(Dispatcher^ dispatcher)
{
	UnmanagedPointer->collide(dispatcher->UnmanagedPointer);
}

int DbvtBroadphase::CUpdates::get()
{
	return UnmanagedPointer->m_cupdates;
}
void DbvtBroadphase::CUpdates::set(int value)
{
	UnmanagedPointer->m_cupdates = value;
}

int DbvtBroadphase::DUpdates::get()
{
	return UnmanagedPointer->m_dupdates;
}
void DbvtBroadphase::DUpdates::set(int value)
{
	UnmanagedPointer->m_dupdates = value;
}

int DbvtBroadphase::FixedLeft::get()
{
	return UnmanagedPointer->m_fixedleft;
}
void DbvtBroadphase::FixedLeft::set(int value)
{
	UnmanagedPointer->m_fixedleft = value;
}

int DbvtBroadphase::FUpdates::get()
{
	return UnmanagedPointer->m_fupdates;
}
void DbvtBroadphase::FUpdates::set(int value)
{
	UnmanagedPointer->m_fupdates = value;
}

int DbvtBroadphase::NewPairs::get()
{
	return UnmanagedPointer->m_newpairs;
}
void DbvtBroadphase::NewPairs::set(int value)
{
	UnmanagedPointer->m_newpairs = value;
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
		*Math::Vector3ToBtVector3(aabbMin), *Math::Vector3ToBtVector3(aabbMax),
		dispatcher->UnmanagedPointer
	);
}

BulletSharp::OverlappingPairCache^ DbvtBroadphase::PairCache::get()
{
	return gcnew BulletSharp::OverlappingPairCache(UnmanagedPointer->m_paircache);
}
void DbvtBroadphase::PairCache::set(BulletSharp::OverlappingPairCache^ value)
{
	UnmanagedPointer->m_paircache = value->UnmanagedPointer;
}

int DbvtBroadphase::CId::get()
{
	return UnmanagedPointer->m_cid;
}
void DbvtBroadphase::CId::set(int value)
{
	UnmanagedPointer->m_cid = value;
}

bool DbvtBroadphase::DeferredCollide::get()
{
	return UnmanagedPointer->m_deferedcollide;
}
void DbvtBroadphase::DeferredCollide::set(bool value)
{
	UnmanagedPointer->m_deferedcollide = value;
}

int DbvtBroadphase::GId::get()
{
	return UnmanagedPointer->m_gid;
}
void DbvtBroadphase::GId::set(int value)
{
	UnmanagedPointer->m_gid = value;
}

bool DbvtBroadphase::NeedCleanup::get()
{
	return UnmanagedPointer->m_needcleanup;
}
void DbvtBroadphase::NeedCleanup::set(bool value)
{
	UnmanagedPointer->m_needcleanup = value;
}

int DbvtBroadphase::PId::get()
{
	return UnmanagedPointer->m_pid;
}
void DbvtBroadphase::PId::set(int value)
{
	UnmanagedPointer->m_pid = value;
}

btScalar DbvtBroadphase::Prediction::get()
{
	return UnmanagedPointer->m_prediction;
}
void DbvtBroadphase::Prediction::set(btScalar value)
{
	UnmanagedPointer->m_prediction = value;
}

bool DbvtBroadphase::ReleasePairCache::get()
{
	return UnmanagedPointer->m_releasepaircache;
}
void DbvtBroadphase::ReleasePairCache::set(bool value)
{
	UnmanagedPointer->m_releasepaircache = value;
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

int DbvtBroadphase::StageCurrent::get()
{
	return UnmanagedPointer->m_stageCurrent;
}
void DbvtBroadphase::StageCurrent::set(int value)
{
	UnmanagedPointer->m_stageCurrent = value;
}

array<DbvtProxy^>^ DbvtBroadphase::StageRoots::get()
{
	array<DbvtProxy^>^ stageRoots = gcnew array<DbvtProxy^>(StageCount+1);
	int i;
	for (i=0; i<StageCount+1; i++)
	{
		if (UnmanagedPointer->m_stageRoots[i] == 0)
			stageRoots[i] = nullptr;
		else
			stageRoots[i] = gcnew DbvtProxy(UnmanagedPointer->m_stageRoots[i]);
	}
	return stageRoots;
}
void DbvtBroadphase::StageRoots::set(array<DbvtProxy^>^ value)
{
	int i;
	for (i=0; i<StageCount+1; i++)
		UnmanagedPointer->m_stageRoots[i] = value[i]->UnmanagedPointer;
}

unsigned int DbvtBroadphase::UpdatesCall::get()
{
	return UnmanagedPointer->m_updates_call;
}
void DbvtBroadphase::UpdatesCall::set(unsigned int value)
{
	UnmanagedPointer->m_updates_call = value;
}

unsigned int DbvtBroadphase::UpdatesDone::get()
{
	return UnmanagedPointer->m_updates_done;
}
void DbvtBroadphase::UpdatesDone::set(unsigned int value)
{
	UnmanagedPointer->m_updates_done = value;
}

btScalar DbvtBroadphase::UpdatesRatio::get()
{
	return UnmanagedPointer->m_updates_ratio;
}
void DbvtBroadphase::UpdatesRatio::set(btScalar value)
{
	UnmanagedPointer->m_updates_ratio = value;
}

btScalar DbvtBroadphase::VelocityPrediction::get()
{
	return UnmanagedPointer->getVelocityPrediction();
}
void DbvtBroadphase::VelocityPrediction::set(btScalar value)
{
	UnmanagedPointer->setVelocityPrediction(value);
}

btDbvtBroadphase* DbvtBroadphase::UnmanagedPointer::get()
{
	return (btDbvtBroadphase*)BroadphaseInterface::UnmanagedPointer;
}

#endif
