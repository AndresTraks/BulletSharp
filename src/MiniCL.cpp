#include "StdAfx.h"

#include "MiniCL.h"
#include "StringConv.h"

IntPtr MiniCL::CreateCommandQueue(IntPtr context, IntPtr device, CLCommandQueueProperties properties, [Out]cl_int% errorCode)
{
	cl_int ciErrNum;
	cl_command_queue commandQueue = clCreateCommandQueue((cl_context)context.ToPointer(),
		(cl_device_id)device.ToPointer(), (cl_command_queue_properties)properties, &ciErrNum);
	errorCode = ciErrNum;
	return IntPtr(commandQueue);
}

IntPtr MiniCL::CreateContextFromType(List<KeyValuePair<CLContext, String^>>^ properties, CLDeviceType deviceType, [Out]cl_int% errorCode)
{
	cl_context_properties* propertiesTemp = new cl_context_properties[properties->Count * 2 + 1];
	int i;
	for (i=0; i<properties->Count; i++)
	{
		propertiesTemp[i*2] = (cl_context_properties)properties[i].Key;
		propertiesTemp[i*2+1] = (cl_context_properties)StringConv::ManagedToUnmanaged(properties[i].Value);
	}
	propertiesTemp[i*2] = 0;

	cl_int err;
	cl_context retContext = clCreateContextFromType(propertiesTemp, (cl_device_type)deviceType, NULL, NULL, &err);
	errorCode = err;

	delete[] propertiesTemp;
	return IntPtr(retContext);
}

cl_int MiniCL::GetContextInfo(IntPtr clContext, CLContext param, [Out]array<IntPtr>^% paramValue)
{
	cl_int ret;

	size_t szParmDataBytes;
	ret = clGetContextInfo((cl_context)clContext.ToPointer(), (cl_context_info)param, 0, NULL, &szParmDataBytes);
	if (ret != CL_SUCCESS)
		return ret;

	cl_device_id* cdDevices = (cl_device_id*) malloc(szParmDataBytes);
    size_t device_count = szParmDataBytes / sizeof(cl_device_id);

	ret = clGetContextInfo((cl_context)clContext.ToPointer(), (cl_context_info)param, szParmDataBytes, cdDevices, NULL);
	if (ret != CL_SUCCESS)
		return ret;
	paramValue = gcnew array<IntPtr>(device_count);
	unsigned int i;
	for (i=0; i<device_count; i++)
	{
		paramValue[i] = IntPtr(cdDevices[i*sizeof(cl_device_id)]);
	}
	return ret;
}

cl_int MiniCL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]int% paramValue)
{
	int paramValueTemp;

	cl_int ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, sizeof(paramValueTemp), &paramValueTemp, NULL);

	if (ret != CL_SUCCESS)
		return ret;
	paramValue = paramValueTemp;
	return ret;
}

cl_int MiniCL::GetPlatformIDs(cl_uint numEntries, array<String^>^% platforms, [Out]cl_uint% numPlatforms)
{
	cl_uint numPlatformsTemp;
	cl_platform_id* platformsTemp = 0;

	if (platforms != nullptr)
		platformsTemp = new cl_platform_id[platforms->Length];

	cl_int ret = clGetPlatformIDs(numEntries, platformsTemp, &numPlatformsTemp);
	if (ret != CL_SUCCESS)
		return ret;

	numPlatforms = numPlatformsTemp;

	if (platforms != nullptr)
	{
		unsigned int i;
		for (i=0; i<numPlatforms; i++)
			platforms[i] = gcnew String((char*)platformsTemp[i]);
	}

	delete[] platformsTemp;

	return ret;
}

cl_int MiniCL::GetPlatformInfo(String^ platform, CLPlatform param, [Out]String^% paramValue)
{
	const char* platformTemp = StringConv::ManagedToUnmanaged(platform);
	char pbuf[128];
	cl_int ret = clGetPlatformInfo((cl_platform_id)platformTemp, (cl_platform_info)param, sizeof(pbuf), pbuf, NULL);
	if (ret != 0)
		return ret;
	StringConv::FreeUnmanagedString(platformTemp);
	paramValue = gcnew String(pbuf);
	return ret;
}
