#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "StringConv.h"
#include "Win32ThreadSupport.h"

MultiThreaded::Win32ThreadConstructionInfo::~Win32ThreadConstructionInfo()
{
	this->!Win32ThreadConstructionInfo();
}

MultiThreaded::Win32ThreadConstructionInfo::!Win32ThreadConstructionInfo()
{
	if (_native) {
		StringConv::FreeUnmanagedString(_uniqueName);
		delete _native;
		_native = NULL;
	}
}

MultiThreaded::Win32ThreadConstructionInfo::Win32ThreadConstructionInfo(String^ uniqueName,
	BulletSharp::Win32ThreadFunc userThreadFunc, BulletSharp::Win32LSMemorySetupFunc lsMemoryFunc, int numThreads,
	int threadStackSize)
{
	_uniqueName = StringConv::ManagedToUnmanaged(uniqueName);
	::Win32ThreadFunc threadFunc;
	::Win32lsMemorySetupFunc memorySetupFunc;

	if (userThreadFunc == Win32ThreadFunc::ProcessCollisionTask) {
		threadFunc = processCollisionTask;
	} else if (userThreadFunc == Win32ThreadFunc::SolverThreadFunc) {
		threadFunc = SolverThreadFunc;
	} else {
		throw gcnew NotImplementedException();
	}

	if (lsMemoryFunc == Win32LSMemorySetupFunc::CreateCollisionLocalStoreMemory) {
		memorySetupFunc = createCollisionLocalStoreMemory;
	} else if (lsMemoryFunc == Win32LSMemorySetupFunc::SolverLSMemoryFunc) {
		memorySetupFunc = SolverlsMemoryFunc;
	} else {
		throw gcnew NotImplementedException();
	}

	_native = new ::Win32ThreadSupport::Win32ThreadConstructionInfo((char*)_uniqueName,
		threadFunc, memorySetupFunc, numThreads, threadStackSize);
}

MultiThreaded::Win32ThreadConstructionInfo::Win32ThreadConstructionInfo(String^ uniqueName,
	BulletSharp::Win32ThreadFunc userThreadFunc, BulletSharp::Win32LSMemorySetupFunc lsMemoryFunc, int numThreads)
{
	_uniqueName = StringConv::ManagedToUnmanaged(uniqueName);
	::Win32ThreadFunc threadFunc;
	::Win32lsMemorySetupFunc memorySetupFunc;

	if (userThreadFunc == Win32ThreadFunc::ProcessCollisionTask) {
		threadFunc = processCollisionTask;
	} else if (userThreadFunc == Win32ThreadFunc::SolverThreadFunc) {
		threadFunc = SolverThreadFunc;
	} else {
		throw gcnew NotImplementedException();
	}

	if (lsMemoryFunc == Win32LSMemorySetupFunc::CreateCollisionLocalStoreMemory) {
		memorySetupFunc = createCollisionLocalStoreMemory;
	} else if (lsMemoryFunc == Win32LSMemorySetupFunc::SolverLSMemoryFunc) {
		memorySetupFunc = SolverlsMemoryFunc;
	} else {
		throw gcnew NotImplementedException();
	}

	_native = new ::Win32ThreadSupport::Win32ThreadConstructionInfo((char*)_uniqueName,
		threadFunc, memorySetupFunc, numThreads);
}

MultiThreaded::Win32ThreadConstructionInfo::Win32ThreadConstructionInfo(String^ uniqueName,
	BulletSharp::Win32ThreadFunc userThreadFunc, BulletSharp::Win32LSMemorySetupFunc lsMemoryFunc)
{
	_uniqueName = StringConv::ManagedToUnmanaged(uniqueName);
	::Win32ThreadFunc threadFunc;
	::Win32lsMemorySetupFunc memorySetupFunc;

	if (userThreadFunc == Win32ThreadFunc::ProcessCollisionTask) {
		threadFunc = processCollisionTask;
	} else if (userThreadFunc == Win32ThreadFunc::SolverThreadFunc) {
		threadFunc = SolverThreadFunc;
	} else {
		throw gcnew NotImplementedException();
	}

	if (lsMemoryFunc == Win32LSMemorySetupFunc::CreateCollisionLocalStoreMemory) {
		memorySetupFunc = createCollisionLocalStoreMemory;
	} else if (lsMemoryFunc == Win32LSMemorySetupFunc::SolverLSMemoryFunc) {
		memorySetupFunc = SolverlsMemoryFunc;
	} else {
		throw gcnew NotImplementedException();
	}

	_native = new ::Win32ThreadSupport::Win32ThreadConstructionInfo((char*)_uniqueName,
		threadFunc, memorySetupFunc);
}

BulletSharp::Win32LSMemorySetupFunc MultiThreaded::Win32ThreadConstructionInfo::LSMemorySetupFunc::get()
{
	if (_native->m_lsMemoryFunc == createCollisionLocalStoreMemory) {
		return Win32LSMemorySetupFunc::CreateCollisionLocalStoreMemory;
	} else if (_native->m_lsMemoryFunc == SolverlsMemoryFunc) {
		return Win32LSMemorySetupFunc::SolverLSMemoryFunc;
	}
	throw gcnew NotImplementedException();
}
void MultiThreaded::Win32ThreadConstructionInfo::LSMemorySetupFunc::set(BulletSharp::Win32LSMemorySetupFunc value)
{
	if (value == Win32LSMemorySetupFunc::CreateCollisionLocalStoreMemory) {
		_native->m_lsMemoryFunc = createCollisionLocalStoreMemory;
	} else if (value == Win32LSMemorySetupFunc::SolverLSMemoryFunc) {
		_native->m_lsMemoryFunc = SolverlsMemoryFunc;
	}
}

int MultiThreaded::Win32ThreadConstructionInfo::NumThreads::get()
{
	return _native->m_numThreads;
}
void MultiThreaded::Win32ThreadConstructionInfo::NumThreads::set(int value)
{
	_native->m_numThreads = value;
}

int MultiThreaded::Win32ThreadConstructionInfo::ThreadStackSize::get()
{
	return _native->m_threadStackSize;
}
void MultiThreaded::Win32ThreadConstructionInfo::ThreadStackSize::set(int value)
{
	_native->m_threadStackSize = value;
}

String^ MultiThreaded::Win32ThreadConstructionInfo::UniqueName::get()
{
	return StringConv::UnmanagedToManaged(_native->m_uniqueName);
}
void MultiThreaded::Win32ThreadConstructionInfo::UniqueName::set(String^ value)
{
	StringConv::FreeUnmanagedString(_uniqueName);
	_uniqueName = StringConv::ManagedToUnmanaged(value);
}

BulletSharp::Win32ThreadFunc MultiThreaded::Win32ThreadConstructionInfo::UserThreadFunc::get()
{
	if (_native->m_userThreadFunc == processCollisionTask) {
		return Win32ThreadFunc::ProcessCollisionTask;
	} else if (_native->m_userThreadFunc == SolverThreadFunc) {
		return Win32ThreadFunc::SolverThreadFunc;
	}
	throw gcnew NotImplementedException();
}
void MultiThreaded::Win32ThreadConstructionInfo::UserThreadFunc::set(BulletSharp::Win32ThreadFunc value)
{
	if (value == Win32ThreadFunc::ProcessCollisionTask) {
		_native->m_userThreadFunc = processCollisionTask;
	} else if (value == Win32ThreadFunc::SolverThreadFunc) {
		_native->m_userThreadFunc = SolverThreadFunc;
	}
}


#define Native static_cast<::Win32ThreadSupport*>(_native)

MultiThreaded::Win32ThreadSupport::Win32ThreadSupport(Win32ThreadConstructionInfo^ threadConstructionInfo)
	: ThreadSupportInterface(new ::Win32ThreadSupport(*threadConstructionInfo->_native))
{
}
/*
bool MultiThreaded::Win32ThreadSupport::IsTaskCompleted(unsigned int^ puiArgument0, unsigned int^ puiArgument1,
	int timeOutInMilliseconds)
{
	return Native->isTaskCompleted(puiArgument0->_native, puiArgument1->_native, timeOutInMilliseconds);
}
*/
void MultiThreaded::Win32ThreadSupport::StartThreads(Win32ThreadConstructionInfo^ threadInfo)
{
	Native->startThreads(*threadInfo->_native);
}

#endif
