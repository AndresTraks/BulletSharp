#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "ThreadSupportInterface.h"

using namespace BulletSharp::MultiThreaded;

MultiThreaded::Barrier::Barrier(btBarrier* barrier)
{
	_barrier = barrier;
}

MultiThreaded::Barrier::~Barrier()
{
	this->!Barrier();
}

MultiThreaded::Barrier::!Barrier()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_barrier = NULL;

	OnDisposed( this, nullptr );
}

void MultiThreaded::Barrier::Sync()
{
	return _barrier->sync();
}

int MultiThreaded::Barrier::MaxCount::get()
{
	return _barrier->getMaxCount();
}
void MultiThreaded::Barrier::MaxCount::set(int value)
{
	_barrier->setMaxCount(value);
}

bool MultiThreaded::Barrier::IsDisposed::get()
{
	return (_barrier == NULL);
}


MultiThreaded::CriticalSection::CriticalSection(btCriticalSection* criticalSection)
{
	_criticalSection = criticalSection;
}

MultiThreaded::CriticalSection::~CriticalSection()
{
	this->!CriticalSection();
}

MultiThreaded::CriticalSection::!CriticalSection()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_criticalSection = NULL;

	OnDisposed( this, nullptr );
}

array<unsigned int>^ MultiThreaded::CriticalSection::CommonBuff::get()
{
	array<unsigned int>^ commonBuffTemp = gcnew array<unsigned int>(32);

	int i;
	for (i=0; i<32; i++)
		commonBuffTemp[i] = _criticalSection->mCommonBuff[i];

	return commonBuffTemp;
}
void MultiThreaded::CriticalSection::CommonBuff::set(array<unsigned int>^ value)
{
	int i;
	for (i=0; i<32; i++)
		_criticalSection->mCommonBuff[i] = value[i];
}

unsigned int MultiThreaded::CriticalSection::GetSharedParam(int i)
{
	return _criticalSection->getSharedParam(i);
}

void MultiThreaded::CriticalSection::SetSharedParam(int i, unsigned int p)
{
	return _criticalSection->setSharedParam(i, p);
}

void MultiThreaded::CriticalSection::Lock()
{
	_criticalSection->lock();
}

void MultiThreaded::CriticalSection::Unlock()
{
	_criticalSection->unlock();
}

bool MultiThreaded::CriticalSection::IsDisposed::get()
{
	return (_criticalSection == NULL);
}


MultiThreaded::ThreadSupportInterface::ThreadSupportInterface(btThreadSupportInterface* threadSupport)
{
	_threadSupport = threadSupport;
}

MultiThreaded::ThreadSupportInterface::~ThreadSupportInterface()
{
	this->!ThreadSupportInterface();
}

MultiThreaded::ThreadSupportInterface::!ThreadSupportInterface()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_threadSupport = NULL;

	OnDisposed( this, nullptr );
}

Barrier^ MultiThreaded::ThreadSupportInterface::CreateBarrier()
{
	return gcnew Barrier(_threadSupport->createBarrier());
}

CriticalSection^ MultiThreaded::ThreadSupportInterface::CreateCriticalSection()
{
	return gcnew CriticalSection(_threadSupport->createCriticalSection());
}

IntPtr MultiThreaded::ThreadSupportInterface::GetThreadLocalMemory(int taskId)
{
	return IntPtr(_threadSupport->getThreadLocalMemory(taskId));
}

void MultiThreaded::ThreadSupportInterface::SendRequest(uint32_t uiCommand, ppu_address_t uiArgument0, uint32_t uiArgument1)
{
	_threadSupport->sendRequest(uiCommand, uiArgument0, uiArgument1);
}

void MultiThreaded::ThreadSupportInterface::StartSpu()
{
	_threadSupport->startSPU();
}

void MultiThreaded::ThreadSupportInterface::StopSpu()
{
	_threadSupport->stopSPU();
}

void MultiThreaded::ThreadSupportInterface::WaitForResponse([Out] unsigned int% puiArgument0, [Out] unsigned int% puiArgument1)
{
	uint32_t puiArgument0Temp;
	uint32_t puiArgument1Temp;

	_threadSupport->waitForResponse(&puiArgument0Temp, &puiArgument1Temp);

	puiArgument0 = puiArgument0Temp;
	puiArgument1 = puiArgument1Temp;
}

int MultiThreaded::ThreadSupportInterface::NumTasks::get()
{
	return _threadSupport->getNumTasks();
}
void MultiThreaded::ThreadSupportInterface::NumTasks::set(int value)
{
	_threadSupport->setNumTasks(value);
}

bool MultiThreaded::ThreadSupportInterface::IsDisposed::get()
{
	return (_threadSupport == NULL);
}

btThreadSupportInterface* MultiThreaded::ThreadSupportInterface::UnmanagedPointer::get()
{
	return _threadSupport;
}

#endif
