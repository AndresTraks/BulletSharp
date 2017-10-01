#include "StdAfx.h"

#include "StringConv.h"
#include "Threads.h"

#ifndef DISABLE_MULTITHREADING

#define Native static_cast<btCollisionDispatcher*>(_native)

TaskScheduler::TaskScheduler(btITaskScheduler* native)
{
	_native = native;
}

int TaskScheduler::MaxNumThreads::get()
{
	return _native->getMaxNumThreads();
}

String^ TaskScheduler::Name::get()
{
	return StringConv::UnmanagedToManaged(_native->getName());
}

int TaskScheduler::NumThreads::get()
{
	return _native->getNumThreads();
}

void TaskScheduler::NumThreads::set(int numThreads)
{
	_native->setNumThreads(numThreads);
}


TaskSchedulerSequential::TaskSchedulerSequential(btITaskScheduler* native)
	: TaskScheduler(native)
{
}


TaskSchedulerOpenMP::TaskSchedulerOpenMP(btITaskScheduler* native)
	: TaskScheduler(native)
{
}


TaskSchedulerTbb::TaskSchedulerTbb(btITaskScheduler* native)
	: TaskScheduler(native)
{
}


TaskSchedulerPpl::TaskSchedulerPpl(btITaskScheduler* native)
	: TaskScheduler(native)
{
}


TaskScheduler^ Threads::TaskScheduler::get()
{
	return _taskScheduler;
}

void Threads::TaskScheduler::set(BulletSharp::TaskScheduler^ taskScheduler)
{
	_taskScheduler = taskScheduler;
	btSetTaskScheduler(taskScheduler != nullptr ? taskScheduler->_native : nullptr);
}

TaskSchedulerOpenMP^ Threads::GetOpenMPTaskScheduler()
{
	if (_taskSchedulerOpenMP == nullptr)
	{
		btITaskScheduler* native = btGetOpenMPTaskScheduler();
		if (native != nullptr)
		{
			_taskSchedulerOpenMP = gcnew TaskSchedulerOpenMP(native);
		}
	}
	return _taskSchedulerOpenMP;
}

TaskSchedulerPpl^ BulletSharp::Threads::GetPplTaskScheduler()
{
	if (_taskSchedulerPpl == nullptr)
	{
		btITaskScheduler* native = btGetPPLTaskScheduler();
		if (native != nullptr)
		{
			_taskSchedulerPpl = gcnew TaskSchedulerPpl(native);
		}
	}
	return _taskSchedulerPpl;
}

TaskSchedulerSequential^ Threads::GetSequentialTaskScheduler()
{
	if (_taskSchedulerSequential == nullptr)
	{
		_taskSchedulerSequential = gcnew TaskSchedulerSequential(btGetSequentialTaskScheduler());
	}
	return _taskSchedulerSequential;
}

TaskSchedulerTbb^ BulletSharp::Threads::GetTbbTaskScheduler()
{
	if (_taskSchedulerTbb == nullptr)
	{
		btITaskScheduler* native = btGetTBBTaskScheduler();
		if (native != nullptr)
		{
			_taskSchedulerTbb = gcnew TaskSchedulerTbb(native);
		}
	}
	return _taskSchedulerTbb;
}

#endif
