#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "StringConv.h"
#include "Win32ThreadSupport.h"

MultiThreaded::Win32ThreadConstructionInfo::Win32ThreadConstructionInfo(String^ uniqueName,
	BulletSharp::Win32ThreadFunc userThreadFunc, BulletSharp::Win32LSMemorySetupFunc lsMemoryFunc)
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
	case Win32LSMemorySetupFunc::CreateCollisionLocalStoreMemory:
		memorySetupFunc = createCollisionLocalStoreMemory;
	}

	_info = new ::Win32ThreadSupport::Win32ThreadConstructionInfo((char*)uniqueNameTemp, threadFunc, memorySetupFunc);

	StringConv::FreeUnmanagedString(uniqueNameTemp);
}

MultiThreaded::Win32ThreadConstructionInfo::Win32ThreadConstructionInfo(String^ uniqueName,
	BulletSharp::Win32ThreadFunc userThreadFunc, BulletSharp::Win32LSMemorySetupFunc lsMemoryFunc, int threadCount)
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
	case Win32LSMemorySetupFunc::CreateCollisionLocalStoreMemory:
		memorySetupFunc = createCollisionLocalStoreMemory;
	}

	_info = new ::Win32ThreadSupport::Win32ThreadConstructionInfo((char*)uniqueNameTemp, threadFunc, memorySetupFunc, threadCount);

	StringConv::FreeUnmanagedString(uniqueNameTemp);
}

::Win32ThreadSupport::Win32ThreadConstructionInfo* MultiThreaded::Win32ThreadConstructionInfo::UnmanagedPointer::get()
{
	return _info;
}


MultiThreaded::Win32ThreadSupport::Win32ThreadSupport(Win32ThreadConstructionInfo^ info)
: ThreadSupportInterface(new ::Win32ThreadSupport(*info->UnmanagedPointer))
{
}

#endif
