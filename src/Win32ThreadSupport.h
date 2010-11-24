#pragma once

#include "ThreadSupportInterface.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class Win32ThreadConstructionInfo
		{
		private:
			::Win32ThreadSupport::Win32ThreadConstructionInfo* _info;

		public:
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc);
			Win32ThreadConstructionInfo(String^ uniqueName, Win32ThreadFunc userThreadFunc,
				Win32LSMemorySetupFunc lsMemoryFunc, int threadCount);

		internal:
			property ::Win32ThreadSupport::Win32ThreadConstructionInfo* UnmanagedPointer
			{
				::Win32ThreadSupport::Win32ThreadConstructionInfo* get();
			}
		};

		public ref class Win32ThreadSupport : ThreadSupportInterface
		{
		public:
			Win32ThreadSupport(Win32ThreadConstructionInfo^ info);
		};
	};
};
