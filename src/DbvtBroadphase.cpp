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

DbvtProxy::DbvtProxy(btDbvtProxy* native)
	: BroadphaseProxy(native)
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

DbvtBroadphaseStage DbvtProxy::Stage::get()
{
	return (DbvtBroadphaseStage)Native->stage;
}
void DbvtProxy::Stage::set(DbvtBroadphaseStage value)
{
	Native->stage = (int)value;
}

#endif


#undef Native
#define Native static_cast<btDbvtBroadphase*>(_native)

DbvtBroadphase::DbvtBroadphase(BulletSharp::OverlappingPairCache^ pairCache)
	: BroadphaseInterface(new btDbvtBroadphase((btOverlappingPairCache*)pairCache->_native))
{
	_overlappingPairCache = pairCache ? pairCache : gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

DbvtBroadphase::DbvtBroadphase()
	: BroadphaseInterface(new btDbvtBroadphase())
{
	_overlappingPairCache = gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
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
#endif

BroadphaseProxy^ DbvtBroadphase::CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
	BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
	short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	btBroadphaseProxy* proxy = _native->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		(int)shapeType, userPtr.ToPointer(), collisionFilterGroup, collisionFilterMask,
		dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
#ifndef DISABLE_DBVT
	return gcnew DbvtProxy(static_cast<btDbvtProxy*>(proxy));
#else
	return gcnew BroadphaseProxy(proxy);
#endif
}

#ifndef DISABLE_DBVT
void DbvtBroadphase::Optimize()
{
	Native->optimize();
}

void DbvtBroadphase::PerformDeferredRemoval(Dispatcher^ dispatcher)
{
	Native->performDeferredRemoval(dispatcher->_native);
}

void DbvtBroadphase::SetAabbForceUpdateRef(BroadphaseProxy^ absproxy, Vector3% aabbMin,
	Vector3% aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->setAabbForceUpdate(absproxy->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		dispatcher->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void DbvtBroadphase::SetAabbForceUpdate(BroadphaseProxy^ absproxy, Vector3 aabbMin,
	Vector3 aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->setAabbForceUpdate(absproxy->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		dispatcher->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

int DbvtBroadphase::CId::get()
{
	return Native->m_cid;
}
void DbvtBroadphase::CId::set(int value)
{
	Native->m_cid = value;
}

int DbvtBroadphase::CUpdates::get()
{
	return Native->m_cupdates;
}
void DbvtBroadphase::CUpdates::set(int value)
{
	Native->m_cupdates = value;
}

bool DbvtBroadphase::DeferredCollide::get()
{
	return Native->m_deferedcollide;
}
void DbvtBroadphase::DeferredCollide::set(bool value)
{
	Native->m_deferedcollide = value;
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

int DbvtBroadphase::NewPairs::get()
{
	return Native->m_newpairs;
}
void DbvtBroadphase::NewPairs::set(int value)
{
	Native->m_newpairs = value;
}

OverlappingPairCache^ DbvtBroadphase::PairCache::get()
{
	return OverlappingPairCache;
}
void DbvtBroadphase::PairCache::set(BulletSharp::OverlappingPairCache^ value)
{
	Native->m_paircache = (btOverlappingPairCache*)value->_native;
	_overlappingPairCache = value;
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
	if (!_sets) {
		_sets = gcnew DbvtArray(Native->m_sets, 2);
	}
	return _sets;
}

DbvtBroadphaseStage DbvtBroadphase::StageCurrent::get()
{
	return (DbvtBroadphaseStage)Native->m_stageCurrent;
}
void DbvtBroadphase::StageCurrent::set(DbvtBroadphaseStage value)
{
	Native->m_stageCurrent = (int)value;
}

DbvtProxyPtrArray^ DbvtBroadphase::StageRoots::get()
{
	if (!_stageRoots) {
		_stageRoots = gcnew DbvtProxyPtrArray(Native->m_stageRoots, sizeof(Native->m_stageRoots) / sizeof(btDbvtProxy*));
	}
	return _stageRoots;
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
void DbvtBroadphase::VelocityPrediction::set(btScalar prediction)
{
	Native->setVelocityPrediction(prediction);
}

#endif
