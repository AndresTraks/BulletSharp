#pragma once

#include "ThreadSupportInterface.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class Win32ThreadConstructionInfo
		{
		internal:
			::Win32ThreadSupport::Win32ThreadConstructionInfo* _native;

		public:
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc);
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc, int threadCount);
		};

		public ref class Win32ThreadSupport : ThreadSupportInterface
		{
		public:
			Win32ThreadSupport(Win32ThreadConstructionInfo^ info);
		};
	};
};
