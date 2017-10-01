#pragma once

namespace BulletSharp
{
	public ref class TaskScheduler abstract
	{
	internal:
		btITaskScheduler* _native;

		TaskScheduler(btITaskScheduler* native);

	public:
		property int MaxNumThreads
		{
			int get();
		}

		property String^ Name
		{
			String^ get();
		}

		property int NumThreads
		{
			int get();
			void set(int numThreads);
		}
	};

	public ref class TaskSchedulerSequential sealed : TaskScheduler
	{
	internal:
		TaskSchedulerSequential(btITaskScheduler* native);
	};

	public ref class TaskSchedulerOpenMP sealed : TaskScheduler
	{
	internal:
		TaskSchedulerOpenMP(btITaskScheduler* native);
	};

	public ref class TaskSchedulerTbb sealed : TaskScheduler
	{
	internal:
		TaskSchedulerTbb(btITaskScheduler* native);
	};

	public ref class TaskSchedulerPpl sealed : TaskScheduler
	{
	internal:
		TaskSchedulerPpl(btITaskScheduler* native);
	};

	public ref class Threads
	{
	private:
		static TaskSchedulerOpenMP^ _taskSchedulerOpenMP;
		static TaskSchedulerPpl^ _taskSchedulerPpl;
		static TaskSchedulerSequential^ _taskSchedulerSequential;
		static TaskSchedulerTbb^ _taskSchedulerTbb;
		static TaskScheduler^ _taskScheduler;

	public:
		property static TaskScheduler^ TaskScheduler
		{
			BulletSharp::TaskScheduler^ get();
			void set(BulletSharp::TaskScheduler^ taskScheduler);
		}

		static TaskSchedulerOpenMP^ GetOpenMPTaskScheduler();
		static TaskSchedulerPpl^ GetPplTaskScheduler();
		static TaskSchedulerSequential^ GetSequentialTaskScheduler();
		static TaskSchedulerTbb^ GetTbbTaskScheduler();
	};
}
