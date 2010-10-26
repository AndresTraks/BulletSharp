#pragma once

#ifdef USE_MINICL
#include <MiniCL/cl.h>
#else if defined(USE_AMD_OPENCL)
#include <CL/cl.h>
#pragma comment(lib, "OpenCL.lib")
#endif

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
		MaxClockFrequency = CL_DEVICE_MAX_CLOCK_FREQUENCY,
		AddressBits = CL_DEVICE_ADDRESS_BITS,
		MaxReadImageArgs = CL_DEVICE_MAX_READ_IMAGE_ARGS,
		MaxWriteImageArgs = CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
		MaxMemAllocSize = CL_DEVICE_MAX_MEM_ALLOC_SIZE,
		Image2DMaxWidth = CL_DEVICE_IMAGE2D_MAX_WIDTH,
		Image2DMaxHeight = CL_DEVICE_IMAGE2D_MAX_HEIGHT,
		Image3DMaxWidth = CL_DEVICE_IMAGE3D_MAX_WIDTH,
		Image3DMaxHeight = CL_DEVICE_IMAGE3D_MAX_HEIGHT,
		Image3DMaxDepth = CL_DEVICE_IMAGE3D_MAX_DEPTH,
		ImageSupport = CL_DEVICE_IMAGE_SUPPORT,
		MaxParameterSize = CL_DEVICE_MAX_PARAMETER_SIZE,
		MaxSamplers = CL_DEVICE_MAX_SAMPLERS,
		MemBaseAddrAlign = CL_DEVICE_MEM_BASE_ADDR_ALIGN,
		MinDataTypeAlignSize = CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
		SingleFPConfig = CL_DEVICE_SINGLE_FP_CONFIG,
		GlobalMemCacheType = CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
		GlobalMemCachelineSize = CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
		GlobalMemCacheSize = CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
		GlobalMemSize = CL_DEVICE_GLOBAL_MEM_SIZE,
		MaxConstantBufferSize = CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
		MaxConstantArgs = CL_DEVICE_MAX_CONSTANT_ARGS,
		LocalMemType = CL_DEVICE_LOCAL_MEM_TYPE,
		LocalMemSize = CL_DEVICE_LOCAL_MEM_SIZE,
		ErrorCorrectionSupport = CL_DEVICE_ERROR_CORRECTION_SUPPORT,
		ProfilingTimerResolution = CL_DEVICE_PROFILING_TIMER_RESOLUTION,
		EndianLittle = CL_DEVICE_ENDIAN_LITTLE,
		Available = CL_DEVICE_AVAILABLE,
		CompilerAvailable = CL_DEVICE_COMPILER_AVAILABLE,
		ExecutionCapabilities = CL_DEVICE_EXECUTION_CAPABILITIES,
		QueueProperties = CL_DEVICE_QUEUE_PROPERTIES,
		Name = CL_DEVICE_NAME,
		Vendor = CL_DEVICE_VENDOR,
		DriverVersion = CL_DRIVER_VERSION,
		Extensions = CL_DEVICE_EXTENSIONS,
		Platform = CL_DEVICE_PLATFORM,
#ifdef USE_AMD_OPENCL
		//DoubleFPConfig = CL_DEVICE_DOUBLE_FP_CONFIG,
		//HalfFPConfig = CL_DEVICE_HALF_FP_CONFIG,
		PreferredVectorWidthHalf = CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,
		HostUnifiedMemory = CL_DEVICE_HOST_UNIFIED_MEMORY,
		NativeVectorWidthChar = CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,
		NativeVectorWidthShort = CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,
		NativeVectorWidthInt = CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,
		NativeVectorWidthLong = CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,
		NativeVectorWidthFloat = CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,
		NativeVectorWidthDouble = CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,
		NativeVectorWidthHalf = CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,
		OpenCLCVersion = CL_DEVICE_OPENCL_C_VERSION,
#endif
	};

	public enum class CLDeviceLocalMemoryType
	{
		Local = CL_LOCAL,
		Global = CL_GLOBAL
	};

	[Flags]
	public enum class CLDeviceType
	{
		None = 0,
		Default = CL_DEVICE_TYPE_DEFAULT,
		Cpu = CL_DEVICE_TYPE_CPU,
		Gpu = CL_DEVICE_TYPE_GPU,
		Accelerator = CL_DEVICE_TYPE_ACCELERATOR,
#ifdef USE_MINICL
		Debug = CL_DEVICE_TYPE_DEBUG,
#endif
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
