#pragma once

using namespace System::Collections::Generic;

namespace BulletSharp
{
	public ref class CL
	{
	public:
		static IntPtr CreateCommandQueue(IntPtr context, IntPtr device, CLCommandQueueProperties properties, [Out]cl_int% errorCode);
		static IntPtr CreateContextFromType(List<KeyValuePair<CLContext, IntPtr>>^ properties, CLDeviceType deviceType, [Out]cl_int% errorCode);
		static cl_int GetContextInfo(IntPtr clContext, CLContext param, [Out]array<IntPtr>^% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]int% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]bool% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]unsigned long long% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]String^% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]array<int>^% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]CLCommandQueueProperties% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]CLDeviceLocalMemoryType% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]CLDeviceType% paramValue);
		static cl_int GetPlatformIDs(cl_uint numEntries, array<IntPtr>^% platforms, [Out]cl_uint% numPlatforms);
		static cl_int GetPlatformInfo(IntPtr platform, CLPlatform param, [Out]String^% paramValue);
	};
};
