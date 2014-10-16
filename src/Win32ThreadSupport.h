#pragma once

#include "ThreadSupportInterface.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class Win32ThreadConstructionInfo : IDisposable
		{
		private:
			const char* _uniqueName;

		internal:
			::Win32ThreadSupport::Win32ThreadConstructionInfo* _native;

		public:
			!Win32ThreadConstructionInfo();
		protected:
			~Win32ThreadConstructionInfo();

		public:
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc, int numThreads, int threadStackSize);
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc, int numThreads);
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc);

			property Win32LSMemorySetupFunc LSMemorySetupFunc
			{
				Win32LSMemorySetupFunc get();
				void set(Win32LSMemorySetupFunc value);
			}

			property int NumThreads
			{
				int get();
				void set(int value);
			}

			property int ThreadStackSize
			{
				int get();
				void set(int value);
			}

			property String^ UniqueName
			{
				String^ get();
				void set(String^ value);
			}

			property Win32ThreadFunc UserThreadFunc
			{
				Win32ThreadFunc get();
				void set(Win32ThreadFunc value);
			}
		};

		public ref class Win32ThreadSupport : ThreadSupportInterface
		{
		public:
			Win32ThreadSupport(Win32ThreadConstructionInfo^ threadConstructionInfo);

			//bool IsTaskCompleted(unsigned int^ puiArgument0, unsigned int^ puiArgument1,
			//	int timeOutInMilliseconds);
			void StartThreads(Win32ThreadConstructionInfo^ threadInfo);
		};
	};
};
