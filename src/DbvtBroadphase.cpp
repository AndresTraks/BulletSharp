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

#define Native static_cast<btDbvtProxy*>(_native)

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
	btDbvtNode* leaf = Native->leaf;
	ReturnCachedObjectGcnewNullable(DbvtNode, _leaf, leaf);
}
void DbvtProxy::Leaf::set(DbvtNode^ value)
{
	Native->leaf = GetUnmanagedNullable(value);
}

DbvtProxyPtrArray^ DbvtProxy::Links::get()
{
	return gcnew DbvtProxyPtrArray(Native->links, 2);
}

int DbvtProxy::Stage::get()
{
	return Native->stage;
}
void DbvtProxy::Stage::set(int value)
{
	Native->stage = value;
}

#endif


#undef Native
#define Native static_cast<btDbvtBroadphase*>(_native)

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
	btDbvtBroadphase::benchmark(broadphase->_native);
}

void DbvtBroadphase::Collide(Dispatcher^ dispatcher)
{
	Native->collide(dispatcher->_native);
}

int DbvtBroadphase::CUpdates::get()
{
	return Native->m_cupdates;
}
void DbvtBroadphase::CUpdates::set(int value)
{
	Native->m_cupdates = value;
}

int DbvtBroadphase::DUpdates::get()
{
	return Native->m_dupdates;
}
void DbvtBroadphase::DUpdates::set(int value)
{
	Native->m_dupdates = value;
}

int DbvtBroadphase::FixedLeft::get()
{
	return Native->m_fixedleft;
}
void DbvtBroadphase::FixedLeft::set(int value)
{
	Native->m_fixedleft = value;
}

int DbvtBroadphase::FUpdates::get()
{
	return Native->m_fupdates;
}
void DbvtBroadphase::FUpdates::set(int value)
{
	Native->m_fupdates = value;
}

int DbvtBroadphase::NewPairs::get()
{
	return Native->m_newpairs;
}
void DbvtBroadphase::NewPairs::set(int value)
{
	Native->m_newpairs = value;
}

void DbvtBroadphase::Optimize()
{
	Native->optimize();
}

void DbvtBroadphase::PerformDeferredRemoval(Dispatcher^ dispatcher)
{
	Native->performDeferredRemoval(dispatcher->_native);
}

void DbvtBroadphase::SetAabbForceUpdate(BroadphaseProxy^ absproxy,
	Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	Native->setAabbForceUpdate(absproxy->UnmanagedPointer,
		VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), dispatcher->_native);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

BulletSharp::OverlappingPairCache^ DbvtBroadphase::PairCache::get()
{
	return dynamic_cast<BulletSharp::OverlappingPairCache^>(
		BulletSharp::OverlappingPairCache::GetManaged(Native->m_paircache));
}
void DbvtBroadphase::PairCache::set(BulletSharp::OverlappingPairCache^ value)
{
	Native->m_paircache = value->UnmanagedPointer;
}

int DbvtBroadphase::CId::get()
{
	return Native->m_cid;
}
void DbvtBroadphase::CId::set(int value)
{
	Native->m_cid = value;
}

bool DbvtBroadphase::DeferredCollide::get()
{
	return Native->m_deferedcollide;
}
void DbvtBroadphase::DeferredCollide::set(bool value)
{
	Native->m_deferedcollide = value;
}

int DbvtBroadphase::GId::get()
{
	return Native->m_gid;
}
void DbvtBroadphase::GId::set(int value)
{
	Native->m_gid = value;
}

bool DbvtBroadphase::NeedCleanup::get()
{
	return Native->m_needcleanup;
}
void DbvtBroadphase::NeedCleanup::set(bool value)
{
	Native->m_needcleanup = value;
}

int DbvtBroadphase::PId::get()
{
	return Native->m_pid;
}
void DbvtBroadphase::PId::set(int value)
{
	Native->m_pid = value;
}

btScalar DbvtBroadphase::Prediction::get()
{
	return Native->m_prediction;
}
void DbvtBroadphase::Prediction::set(btScalar value)
{
	Native->m_prediction = value;
}

bool DbvtBroadphase::ReleasePairCache::get()
{
	return Native->m_releasepaircache;
}
void DbvtBroadphase::ReleasePairCache::set(bool value)
{
	Native->m_releasepaircache = value;
}

DbvtArray^ DbvtBroadphase::Sets::get()
{
	return gcnew DbvtArray(Native->m_sets, 2);
}

int DbvtBroadphase::StageCurrent::get()
{
	return Native->m_stageCurrent;
}
void DbvtBroadphase::StageCurrent::set(int value)
{
	Native->m_stageCurrent = value;
}

DbvtProxyPtrArray^ DbvtBroadphase::StageRoots::get()
{
	return gcnew DbvtProxyPtrArray(Native->m_stageRoots, StageCount+1);
}

unsigned int DbvtBroadphase::UpdatesCall::get()
{
	return Native->m_updates_call;
}
void DbvtBroadphase::UpdatesCall::set(unsigned int value)
{
	Native->m_updates_call = value;
}

unsigned int DbvtBroadphase::UpdatesDone::get()
{
	return Native->m_updates_done;
}
void DbvtBroadphase::UpdatesDone::set(unsigned int value)
{
	Native->m_updates_done = value;
}

btScalar DbvtBroadphase::UpdatesRatio::get()
{
	return Native->m_updates_ratio;
}
void DbvtBroadphase::UpdatesRatio::set(btScalar value)
{
	Native->m_updates_ratio = value;
}

btScalar DbvtBroadphase::VelocityPrediction::get()
{
	return Native->getVelocityPrediction();
}
void DbvtBroadphase::VelocityPrediction::set(btScalar value)
{
	Native->setVelocityPrediction(value);
}

#endif
