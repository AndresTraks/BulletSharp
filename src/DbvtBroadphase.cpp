#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "Collections.h"
#include "DbvtBroadphase.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif


#ifndef DISABLE_DBVT

#define Unmanaged static_cast<btDbvtProxy*>(_unmanaged)

DbvtProxy::DbvtProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
	CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
: BroadphaseProxy(0)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_clientObject = userObject;

	UnmanagedPointer = new btDbvtProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), 0,
		(short int)collisionFilterGroup, (short int)collisionFilterMask);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

DbvtProxy::DbvtProxy(btDbvtProxy* proxy)
: BroadphaseProxy(proxy)
{
}

DbvtNode^ DbvtProxy::Leaf::get()
{
	btDbvtNode* leaf = Unmanaged->leaf;
	ReturnCachedObjectNullable(DbvtNode, _leaf, leaf);
}
void DbvtProxy::Leaf::set(DbvtNode^ value)
{
	Unmanaged->leaf = GetUnmanagedNullable(value);
}

DbvtProxyPtrArray^ DbvtProxy::Links::get()
{
	return gcnew DbvtProxyPtrArray(Unmanaged->links, 2);
}

int DbvtProxy::Stage::get()
{
	return Unmanaged->stage;
}
void DbvtProxy::Stage::set(int value)
{
	Unmanaged->stage = value;
}

#endif


#undef Unmanaged
#define Unmanaged static_cast<btDbvtBroadphase*>(_unmanaged)

DbvtBroadphase::DbvtBroadphase(btDbvtBroadphase* broadphase)
: BroadphaseInterface(broadphase)
{
}

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
	btDbvtBroadphase::benchmark(broadphase->_unmanaged);
}

void DbvtBroadphase::Collide(Dispatcher^ dispatcher)
{
	Unmanaged->collide(dispatcher->_unmanaged);
}

int DbvtBroadphase::CUpdates::get()
{
	return Unmanaged->m_cupdates;
}
void DbvtBroadphase::CUpdates::set(int value)
{
	Unmanaged->m_cupdates = value;
}

int DbvtBroadphase::DUpdates::get()
{
	return Unmanaged->m_dupdates;
}
void DbvtBroadphase::DUpdates::set(int value)
{
	Unmanaged->m_dupdates = value;
}

int DbvtBroadphase::FixedLeft::get()
{
	return Unmanaged->m_fixedleft;
}
void DbvtBroadphase::FixedLeft::set(int value)
{
	Unmanaged->m_fixedleft = value;
}

int DbvtBroadphase::FUpdates::get()
{
	return Unmanaged->m_fupdates;
}
void DbvtBroadphase::FUpdates::set(int value)
{
	Unmanaged->m_fupdates = value;
}

int DbvtBroadphase::NewPairs::get()
{
	return Unmanaged->m_newpairs;
}
void DbvtBroadphase::NewPairs::set(int value)
{
	Unmanaged->m_newpairs = value;
}

void DbvtBroadphase::Optimize()
{
	Unmanaged->optimize();
}

void DbvtBroadphase::PerformDeferredRemoval(Dispatcher^ dispatcher)
{
	Unmanaged->performDeferredRemoval(dispatcher->_unmanaged);
}

void DbvtBroadphase::SetAabbForceUpdate(BroadphaseProxy^ absproxy,
	Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	Unmanaged->setAabbForceUpdate(absproxy->UnmanagedPointer,
		VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), dispatcher->_unmanaged);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

BulletSharp::OverlappingPairCache^ DbvtBroadphase::PairCache::get()
{
	return dynamic_cast<BulletSharp::OverlappingPairCache^>(
		BulletSharp::OverlappingPairCache::GetManaged(Unmanaged->m_paircache));
}
void DbvtBroadphase::PairCache::set(BulletSharp::OverlappingPairCache^ value)
{
	Unmanaged->m_paircache = value->UnmanagedPointer;
}

int DbvtBroadphase::CId::get()
{
	return Unmanaged->m_cid;
}
void DbvtBroadphase::CId::set(int value)
{
	Unmanaged->m_cid = value;
}

bool DbvtBroadphase::DeferredCollide::get()
{
	return Unmanaged->m_deferedcollide;
}
void DbvtBroadphase::DeferredCollide::set(bool value)
{
	Unmanaged->m_deferedcollide = value;
}

int DbvtBroadphase::GId::get()
{
	return Unmanaged->m_gid;
}
void DbvtBroadphase::GId::set(int value)
{
	Unmanaged->m_gid = value;
}

bool DbvtBroadphase::NeedCleanup::get()
{
	return Unmanaged->m_needcleanup;
}
void DbvtBroadphase::NeedCleanup::set(bool value)
{
	Unmanaged->m_needcleanup = value;
}

int DbvtBroadphase::PId::get()
{
	return Unmanaged->m_pid;
}
void DbvtBroadphase::PId::set(int value)
{
	Unmanaged->m_pid = value;
}

btScalar DbvtBroadphase::Prediction::get()
{
	return Unmanaged->m_prediction;
}
void DbvtBroadphase::Prediction::set(btScalar value)
{
	Unmanaged->m_prediction = value;
}

bool DbvtBroadphase::ReleasePairCache::get()
{
	return Unmanaged->m_releasepaircache;
}
void DbvtBroadphase::ReleasePairCache::set(bool value)
{
	Unmanaged->m_releasepaircache = value;
}

DbvtArray^ DbvtBroadphase::Sets::get()
{
	return gcnew DbvtArray(Unmanaged->m_sets, 2);
}

int DbvtBroadphase::StageCurrent::get()
{
	return Unmanaged->m_stageCurrent;
}
void DbvtBroadphase::StageCurrent::set(int value)
{
	Unmanaged->m_stageCurrent = value;
}

DbvtProxyPtrArray^ DbvtBroadphase::StageRoots::get()
{
	return gcnew DbvtProxyPtrArray(Unmanaged->m_stageRoots, StageCount+1);
}

unsigned int DbvtBroadphase::UpdatesCall::get()
{
	return Unmanaged->m_updates_call;
}
void DbvtBroadphase::UpdatesCall::set(unsigned int value)
{
	Unmanaged->m_updates_call = value;
}

unsigned int DbvtBroadphase::UpdatesDone::get()
{
	return Unmanaged->m_updates_done;
}
void DbvtBroadphase::UpdatesDone::set(unsigned int value)
{
	Unmanaged->m_updates_done = value;
}

btScalar DbvtBroadphase::UpdatesRatio::get()
{
	return Unmanaged->m_updates_ratio;
}
void DbvtBroadphase::UpdatesRatio::set(btScalar value)
{
	Unmanaged->m_updates_ratio = value;
}

btScalar DbvtBroadphase::VelocityPrediction::get()
{
	return Unmanaged->getVelocityPrediction();
}
void DbvtBroadphase::VelocityPrediction::set(btScalar value)
{
	Unmanaged->setVelocityPrediction(value);
}

#endif
