#pragma once

#include "ThreadSupportInterface.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class Win32ThreadConstructionInfo
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
				Win32LSMemorySetupFunc lsMemoryFunc);
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc, int threadCount);

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
			Win32ThreadSupport(Win32ThreadConstructionInfo^ info);
		};
	};
};
