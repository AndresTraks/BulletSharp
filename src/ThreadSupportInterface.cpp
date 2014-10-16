#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "Collections.h"
#include "ThreadSupportInterface.h"

using namespace BulletSharp::MultiThreaded;

MultiThreaded::Barrier::Barrier(btBarrier* native)
{
	_native = native;
}

void MultiThreaded::Barrier::Sync()
{
	_native->sync();
}

int MultiThreaded::Barrier::MaxCount::get()
{
	return _native->getMaxCount();
}
void MultiThreaded::Barrier::MaxCount::set(int n)
{
	_native->setMaxCount(n);
}

bool MultiThreaded::Barrier::IsDisposed::get()
{
	return (_native == NULL);
}


MultiThreaded::CriticalSection::CriticalSection(btCriticalSection* native)
{
	_native = native;
}

unsigned int MultiThreaded::CriticalSection::GetSharedParam(int i)
{
	return _native->getSharedParam(i);
}

void MultiThreaded::CriticalSection::Lock()
{
	_native->lock();
}

void MultiThreaded::CriticalSection::SetSharedParam(int i, unsigned int p)
{
	_native->setSharedParam(i, p);
}

void MultiThreaded::CriticalSection::Unlock()
{
	_native->unlock();
}

UIntArray^ MultiThreaded::CriticalSection::CommonBuff::get()
{
	return gcnew UIntArray(_native->mCommonBuff, 32);
}

bool MultiThreaded::CriticalSection::IsDisposed::get()
{
	return (_native == NULL);
}


MultiThreaded::ThreadSupportInterface::ThreadSupportInterface(btThreadSupportInterface* native)
{
	_native = native;
}

MultiThreaded::ThreadSupportInterface::~ThreadSupportInterface()
{
	this->!ThreadSupportInterface();
}

MultiThreaded::ThreadSupportInterface::!ThreadSupportInterface()
{
	delete _native;
	_native = NULL;
}

Barrier^ MultiThreaded::ThreadSupportInterface::CreateBarrier()
{
	return gcnew Barrier(_native->createBarrier());
}

CriticalSection^ MultiThreaded::ThreadSupportInterface::CreateCriticalSection()
{
	return gcnew CriticalSection(_native->createCriticalSection());
}

void MultiThreaded::ThreadSupportInterface::DeleteBarrier(Barrier^ barrier)
{
	_native->deleteBarrier(barrier->_native);
}

void MultiThreaded::ThreadSupportInterface::DeleteCriticalSection(CriticalSection^ criticalSection)
{
	_native->deleteCriticalSection(criticalSection->_native);
}

IntPtr MultiThreaded::ThreadSupportInterface::GetThreadLocalMemory(int taskId)
{
	return IntPtr(_native->getThreadLocalMemory(taskId));
}

void MultiThreaded::ThreadSupportInterface::SendRequest(uint32_t uiCommand, ppu_address_t uiArgument0,
	uint32_t uiArgument1)
{
	_native->sendRequest(uiCommand, uiArgument0, uiArgument1);
}

void MultiThreaded::ThreadSupportInterface::StartSpu()
{
	_native->startSPU();
}

void MultiThreaded::ThreadSupportInterface::StopSpu()
{
	_native->stopSPU();
}

void MultiThreaded::ThreadSupportInterface::WaitForResponse([Out] unsigned int% puiArgument0, [Out] unsigned int% puiArgument1)
{
	uint32_t puiArgument0Temp;
	uint32_t puiArgument1Temp;

	_native->waitForResponse(&puiArgument0Temp, &puiArgument1Temp);

	puiArgument0 = puiArgument0Temp;
	puiArgument1 = puiArgument1Temp;
}

int MultiThreaded::ThreadSupportInterface::NumTasks::get()
{
	return _native->getNumTasks();
}
void MultiThreaded::ThreadSupportInterface::NumTasks::set(int numTasks)
{
	_native->setNumTasks(numTasks);
}

bool MultiThreaded::ThreadSupportInterface::IsDisposed::get()
{
	return (_native == NULL);
}

#endif
