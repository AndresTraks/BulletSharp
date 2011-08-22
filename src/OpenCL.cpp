#include "StdAfx.h"

#ifdef __OPENCL_CL_H

#include "OpenCL.h"
#include "StringConv.h"

IntPtr CL::CreateCommandQueue(IntPtr context, IntPtr device, CLCommandQueueProperties properties, [Out]cl_int% errorCode)
{
	cl_int ciErrNum;
	cl_command_queue commandQueue = clCreateCommandQueue((cl_context)context.ToPointer(),
		(cl_device_id)device.ToPointer(), (cl_command_queue_properties)properties, &ciErrNum);
	errorCode = ciErrNum;
	return IntPtr(commandQueue);
}

IntPtr CL::CreateContextFromType(List<KeyValuePair<CLContext, IntPtr>>^ properties, CLDeviceType deviceType, [Out]cl_int% errorCode)
{
	cl_context_properties* propertiesTemp = new cl_context_properties[properties->Count * 2 + 1];
	int i;
	for (i=0; i<properties->Count; i++)
	{
		propertiesTemp[i*2] = (cl_context_properties)properties[i].Key;
		propertiesTemp[i*2+1] = (cl_context_properties)properties[i].Value.ToPointer();
	}
	propertiesTemp[i*2] = 0;

	cl_int err;
	cl_context retContext = clCreateContextFromType(propertiesTemp, (cl_device_type)deviceType, NULL, NULL, &err);
	errorCode = err;

	delete[] propertiesTemp;
	return IntPtr(retContext);
}

cl_int CL::GetContextInfo(IntPtr clContext, CLContext param, [Out]array<IntPtr>^% paramValue)
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
	{
		free(cdDevices);
		return ret;
	}

	paramValue = gcnew array<IntPtr>(device_count);
	unsigned int i;
	for (i=0; i<device_count; i++)
	{
		paramValue[i] = IntPtr(cdDevices[i*sizeof(cl_device_id)]);
	}
	
	free(cdDevices);
	return CL_SUCCESS;
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]int% paramValue)
{
	int paramValueTemp;

	cl_int ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, sizeof(paramValueTemp), &paramValueTemp, NULL);
	if (ret != CL_SUCCESS)
		return ret;

	paramValue = paramValueTemp;
	return CL_SUCCESS;
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]bool% paramValue)
{
	return GetDeviceInfo(device, param, (int)paramValue);
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]unsigned long long% paramValue)
{
	unsigned long long paramValueTemp;

	cl_int ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, sizeof(paramValueTemp), &paramValueTemp, NULL);
	if (ret != CL_SUCCESS)
		return ret;

	paramValue = paramValueTemp;
	return CL_SUCCESS;
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]String^% paramValue)
{
	cl_int ret;

	size_t szParmDataBytes = 1024;
	
	//ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, 0, NULL, &szParmDataBytes);
	//if (ret != CL_SUCCESS)
	//	return ret;

	char* paramValueTemp = (char*) malloc(szParmDataBytes);

	ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, szParmDataBytes, paramValueTemp, NULL);
	if (ret != CL_SUCCESS)
	{
		free(paramValueTemp);
		return ret;
	}

	paramValue = gcnew String(paramValueTemp);

	free(paramValueTemp);
	return CL_SUCCESS;
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]array<int>^% paramValue)
{
	// Assume param is CL_DEVICE_MAX_WORK_ITEM_SIZES.

	cl_uint dimensions;
	cl_int ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(dimensions), &dimensions, NULL);
	if (ret != CL_SUCCESS)
		return ret;

	dimensions = (dimensions >= 3) ? dimensions : 3;

	paramValue = gcnew array<int>(dimensions);
	pin_ptr<int> paramValuePtr = &paramValue[0];

	ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, dimensions * sizeof(int), paramValuePtr, NULL);
	return CL_SUCCESS;
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]CLCommandQueueProperties% paramValue)
{
	cl_command_queue_properties paramValueTemp;

	cl_int ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, sizeof(paramValueTemp), &paramValueTemp, NULL);
	if (ret != CL_SUCCESS)
		return ret;

	paramValue = (CLCommandQueueProperties)paramValueTemp;
	return CL_SUCCESS;
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]CLDeviceLocalMemoryType% paramValue)
{
	cl_device_local_mem_type paramValueTemp;

	cl_int ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, sizeof(paramValueTemp), &paramValueTemp, NULL);
	if (ret != CL_SUCCESS)
		return ret;

	paramValue = (CLDeviceLocalMemoryType)paramValueTemp;
	return CL_SUCCESS;
}

cl_int CL::GetDeviceInfo(IntPtr device, CLDevice param, [Out]CLDeviceType% paramValue)
{
	cl_device_type paramValueTemp;

	cl_int ret = clGetDeviceInfo((cl_device_id)device.ToPointer(), (cl_context_info)param, sizeof(paramValueTemp), &paramValueTemp, NULL);
	if (ret != CL_SUCCESS)
		return ret;

	paramValue = (CLDeviceType)paramValueTemp;
	return CL_SUCCESS;
}

cl_int CL::GetPlatformIDs(cl_uint numEntries, array<IntPtr>^% platforms, [Out]cl_uint% numPlatforms)
{
	cl_uint numPlatformsTemp;
	cl_platform_id* platformsTemp;
	cl_int ret;

	if (numEntries == 0)
	{
		// Get only the number of platforms available.
		ret = clGetPlatformIDs(0, NULL, &numPlatformsTemp);
		if (ret == CL_SUCCESS)
		{
			numPlatforms = numPlatformsTemp;
		}
		return ret;
	}

	if (platforms != nullptr)
		platformsTemp = new cl_platform_id[platforms->Length];
	else
		platformsTemp = 0;

	ret = clGetPlatformIDs(numEntries, platformsTemp, &numPlatformsTemp);
	if (ret != CL_SUCCESS)
		return ret;

	numPlatforms = numPlatformsTemp;

	if (platforms != nullptr)
	{
		unsigned int i;
		for (i=0; i<numPlatforms; i++)
			platforms[i] = IntPtr(platformsTemp[i]);
	}

	delete[] platformsTemp;

	return CL_SUCCESS;
}

cl_int CL::GetPlatformInfo(IntPtr platform, CLPlatform param, [Out]String^% paramValue)
{
	char pbuf[128];
	
	cl_int ret = clGetPlatformInfo((cl_platform_id)platform.ToPointer(), (cl_platform_info)param, sizeof(pbuf), pbuf, NULL);
	if (ret != 0)
		return ret;
	
	paramValue = gcnew String(pbuf);
	return CL_SUCCESS;
}

#endif
