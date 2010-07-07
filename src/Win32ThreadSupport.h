#pragma once

#include "ThreadSupportInterface.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class Win32ThreadSupport : ThreadSupportInterface
		{
		public:
			enum class Win32ThreadFunc
			{
				ProcessCollisionTask
			};

			enum class Win32lsMemorySetupFunc
			{
				CreateCollisionLocalStoreMemory
			};

			ref class Win32ThreadConstructionInfo
			{
			private:
				::Win32ThreadSupport::Win32ThreadConstructionInfo* _info;

			public:
				Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
					Win32lsMemorySetupFunc lsMemoryFunc);
				Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
					Win32lsMemorySetupFunc lsMemoryFunc, int numThreads);

			internal:
				property ::Win32ThreadSupport::Win32ThreadConstructionInfo* UnmanagedPointer
				{
					::Win32ThreadSupport::Win32ThreadConstructionInfo* get();
				}
			};

			Win32ThreadSupport(Win32ThreadConstructionInfo^ info);
		};
	};
};
