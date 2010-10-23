#pragma once

#include <MiniCL/cl.h>

using namespace System::Collections::Generic;

namespace BulletSharp
{
	[Flags]
	public enum class CLCommandQueueProperties
	{
		None = 0,
		OutOfOrderExecModeEnable = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE,
		ProfilingEnable = CL_QUEUE_PROFILING_ENABLE
	};

	public enum class CLContext
	{
		ReferenceCount = CL_CONTEXT_REFERENCE_COUNT,
		NumDevices = CL_CONTEXT_NUM_DEVICES,
		Devices = CL_CONTEXT_DEVICES,
		Properties = CL_CONTEXT_PROPERTIES,
		Platform = CL_CONTEXT_PLATFORM
	};

	public enum class CLDevice
	{
		Type = CL_DEVICE_TYPE,
		VendorID = CL_DEVICE_VENDOR_ID,
		MaxComputeUnits = CL_DEVICE_MAX_COMPUTE_UNITS,
		MaxWorkItemDimensions = CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
		MaxWorkGroupSize = CL_DEVICE_MAX_WORK_GROUP_SIZE,
		MaxWorkItemSizes = CL_DEVICE_MAX_WORK_ITEM_SIZES,
		PreferredVectorWidthChar = CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,
		PreferredVectorWidthShort = CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,
		PreferredVectorWidthInt = CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,
		PreferredVectorWidthLong = CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,
		PreferredVectorWidthFloat = CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
		PreferredVectorWidthDouble = CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
		MaxClockFrequency = CL_DEVICE_MAX_CLOCK_FREQUENCY
	};

	public enum class CLDeviceType
	{
		Default = CL_DEVICE_TYPE_DEFAULT,
		Cpu = CL_DEVICE_TYPE_CPU,
		Gpu = CL_DEVICE_TYPE_GPU,
		Accelerator = CL_DEVICE_TYPE_ACCELERATOR,
		Debug = CL_DEVICE_TYPE_DEBUG,
		All = CL_DEVICE_TYPE_ALL
	};

	public enum class CLPlatform
	{
		Profile = CL_PLATFORM_PROFILE,
		Version = CL_PLATFORM_VERSION,
		Name = CL_PLATFORM_NAME,
		Vendor = CL_PLATFORM_VENDOR,
		Extensions = CL_PLATFORM_EXTENSIONS
	};

	public ref class MiniCL
	{
	public:
		static IntPtr CreateCommandQueue(IntPtr context, IntPtr device, CLCommandQueueProperties properties, [Out]cl_int% errorCode);
		static IntPtr CreateContextFromType(List<KeyValuePair<CLContext, String^>>^ properties, CLDeviceType deviceType, [Out]cl_int% errorCode);
		static cl_int GetContextInfo(IntPtr clContext, CLContext param, [Out]array<IntPtr>^% paramValue);
		static cl_int GetDeviceInfo(IntPtr device, CLDevice param, [Out]int% paramValue);
		static cl_int GetPlatformIDs(cl_uint numEntries, array<String^>^% platforms, [Out]cl_uint% numPlatforms);
		static cl_int GetPlatformInfo(String^ platform, CLPlatform param, [Out]String^% paramValue);
	};
};
