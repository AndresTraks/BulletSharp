#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#pragma managed(push, off)
#include <BulletMultiThreaded/Win32ThreadSupport.h>
#include <BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h>
#pragma managed(pop)

#include "StringConv.h"
#include "Win32ThreadSupport.h"

MultiThreaded::Win32ThreadSupport::Win32ThreadConstructionInfo::Win32ThreadConstructionInfo(String^ uniqueName,
	Win32ThreadFunc userThreadFunc, Win32lsMemorySetupFunc lsMemoryFunc)
{
	const char* uniqueNameTemp = StringConv::ManagedToUnmanaged(uniqueName);
	::Win32ThreadFunc threadFunc;
	::Win32lsMemorySetupFunc memorySetupFunc;

	switch(userThreadFunc)
	{
	case Win32ThreadFunc::ProcessCollisionTask:
		threadFunc = processCollisionTask;
	}

	switch(lsMemoryFunc)
	{
	case Win32lsMemorySetupFunc::CreateCollisionLocalStoreMemory:
		memorySetupFunc = createCollisionLocalStoreMemory;
	}

	_info = new ::Win32ThreadSupport::Win32ThreadConstructionInfo((char*)uniqueNameTemp, threadFunc, memorySetupFunc);

	StringConv::FreeUnmanagedString(uniqueNameTemp);
}

MultiThreaded::Win32ThreadSupport::Win32ThreadConstructionInfo::Win32ThreadConstructionInfo(String^ uniqueName,
	Win32ThreadFunc userThreadFunc, Win32lsMemorySetupFunc lsMemoryFunc, int numThreads)
{
	const char* uniqueNameTemp = StringConv::ManagedToUnmanaged(uniqueName);
	::Win32ThreadFunc threadFunc = 0;
	::Win32lsMemorySetupFunc memorySetupFunc = 0;

	switch(userThreadFunc)
	{
	case Win32ThreadFunc::ProcessCollisionTask:
		threadFunc = processCollisionTask;
	}

	switch(lsMemoryFunc)
	{
	case Win32lsMemorySetupFunc::CreateCollisionLocalStoreMemory:
		memorySetupFunc = createCollisionLocalStoreMemory;
	}

	_info = new ::Win32ThreadSupport::Win32ThreadConstructionInfo((char*)uniqueNameTemp, threadFunc, memorySetupFunc, numThreads);

	StringConv::FreeUnmanagedString(uniqueNameTemp);
}

::Win32ThreadSupport::Win32ThreadConstructionInfo* MultiThreaded::Win32ThreadSupport::Win32ThreadConstructionInfo::UnmanagedPointer::get()
{
	return _info;
}


MultiThreaded::Win32ThreadSupport::Win32ThreadSupport(Win32ThreadConstructionInfo^ info)
: ThreadSupportInterface(new ::Win32ThreadSupport(*info->UnmanagedPointer))
{
}

#endif
