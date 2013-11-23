using System;
using BulletSharp;

namespace OpenCLClothDemo
{
    class OclUtils
    {
        public static uint GetNumPlatforms(ref int pErrNum)
        {
	        uint numPlatforms;
            IntPtr[] platforms = new IntPtr[0];
            int ciErrNum = CL.GetPlatformIDs(0, ref platforms, out numPlatforms);

	        if(ciErrNum != 0)
	        {
		        if(pErrNum != 0) 
			        pErrNum = ciErrNum;
	        }
	        return numPlatforms;
        }

        public static IntPtr GetDevice(IntPtr cxMainContext, uint deviceIndex)
        {
            // get the list of GPU devices associated with context
            IntPtr[] devices;
            CL.GetContextInfo(cxMainContext, CLContext.Devices, out devices);
            return devices[deviceIndex];
        }

        public static int GetNumDevices(IntPtr cxMainContext)
        {
            IntPtr[] devices;
            CL.GetContextInfo(cxMainContext, CLContext.Devices, out devices);
            return devices.Length;
        }

        public static void PrintDeviceInfo(IntPtr device)
        {
            string deviceString;

            CL.GetDeviceInfo(device, CLDevice.Name, out deviceString);
            Console.WriteLine("  CL_DEVICE_NAME:\t\t\t" + deviceString);

            CL.GetDeviceInfo(device, CLDevice.Vendor, out deviceString);
            Console.WriteLine("  CL_DEVICE_VENDOR:\t\t\t" + deviceString);

            CL.GetDeviceInfo(device, CLDevice.DriverVersion, out deviceString);
            Console.WriteLine("  CL_DEVICE_VERSION:\t\t\t" + deviceString);

            CLDeviceType deviceType;
            CL.GetDeviceInfo(device, CLDevice.Type, out deviceType);

            if ((deviceType & CLDeviceType.Cpu) == CLDeviceType.Cpu)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_CPU");
            if ((deviceType & CLDeviceType.Gpu) == CLDeviceType.Gpu)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_GPU");
            if ((deviceType & CLDeviceType.Accelerator) == CLDeviceType.Accelerator)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_DEFAULT");
            if ((deviceType & CLDeviceType.Default) == CLDeviceType.Default)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_DEFAULT");

            int computeUnits;
            CL.GetDeviceInfo(device, CLDevice.MaxComputeUnits, out computeUnits);
            Console.WriteLine("  CL_DEVICE_MAX_COMPUTE_UNITS:\t\t" + computeUnits);

            int workitemDims;
            CL.GetDeviceInfo(device, CLDevice.MaxWorkItemDimensions, out workitemDims);
            Console.WriteLine("  CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:\t" + workitemDims);

            int[] workitemSizes;
            CL.GetDeviceInfo(device, CLDevice.MaxWorkItemSizes, out workitemSizes);
            Console.WriteLine("  CL_DEVICE_MAX_WORK_ITEM_SIZES:\t" + workitemSizes[0] + " / " + workitemSizes[1] + " / " + workitemSizes[2]);

            int workgroupSize;
            CL.GetDeviceInfo(device, CLDevice.MaxWorkGroupSize, out workgroupSize);
            Console.WriteLine("  CL_DEVICE_MAX_WORK_GROUP_SIZE:\t" + workgroupSize);

            int clockFrequency;
            CL.GetDeviceInfo(device, CLDevice.MaxClockFrequency, out clockFrequency);
            Console.WriteLine("  CL_DEVICE_MAX_CLOCK_FREQUENCY:\t" + clockFrequency + " MHz");

            int addrBits;
            CL.GetDeviceInfo(device, CLDevice.AddressBits, out addrBits);
            Console.WriteLine("  CL_DEVICE_ADDRESS_BITS:\t\t" + addrBits);

            ulong maxMemAllocSize;
            CL.GetDeviceInfo(device, CLDevice.MaxMemAllocSize, out maxMemAllocSize);
            Console.WriteLine("  CL_DEVICE_MAX_MEM_ALLOC_SIZE:\t\t" + maxMemAllocSize / (1024 * 1024) + " MByte");

            ulong globalMemSize;
            CL.GetDeviceInfo(device, CLDevice.GlobalMemSize, out globalMemSize);
            Console.WriteLine("  CL_DEVICE_GLOBAL_MEM_SIZE:\t\t" + globalMemSize / (1024 * 1024) + " MByte");

            bool errorCorrectionSupport;
            CL.GetDeviceInfo(device, CLDevice.ErrorCorrectionSupport, out errorCorrectionSupport);
            Console.WriteLine("  CL_DEVICE_ERROR_CORRECTION_SUPPORT:\t" + (errorCorrectionSupport ? "yes" : "no"));

            CLDeviceLocalMemoryType localMemType;
            CL.GetDeviceInfo(device, CLDevice.LocalMemType, out localMemType);
            Console.WriteLine("  CL_DEVICE_LOCAL_MEM_TYPE:\t\t" + localMemType);

            ulong localMemSize;
            CL.GetDeviceInfo(device, CLDevice.LocalMemSize, out localMemSize);
            Console.WriteLine("  CL_DEVICE_LOCAL_MEM_SIZE:\t\t" + localMemSize / 1024 + " KByte");

            ulong constantBufferSize;
            CL.GetDeviceInfo(device, CLDevice.MaxConstantBufferSize, out constantBufferSize);
            Console.WriteLine("  CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:\t" + constantBufferSize / 1024 + " KByte");

            CLCommandQueueProperties queueProperties;
            CL.GetDeviceInfo(device, CLDevice.Type, out queueProperties);

            if ((queueProperties & CLCommandQueueProperties.OutOfOrderExecModeEnable) == CLCommandQueueProperties.OutOfOrderExecModeEnable)
                Console.WriteLine("  CL_DEVICE_QUEUE_PROPERTIES:\t\tCL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
            if ((queueProperties & CLCommandQueueProperties.ProfilingEnable) == CLCommandQueueProperties.ProfilingEnable)
                Console.WriteLine("  CL_DEVICE_QUEUE_PROPERTIES:\t\tCL_QUEUE_PROFILING_ENABLE");

            bool imageSupport;
            CL.GetDeviceInfo(device, CLDevice.ImageSupport, out imageSupport);
            Console.WriteLine("  CL_DEVICE_IMAGE_SUPPORT:\t\t" + imageSupport);

            int maxReadImageArgs;
            CL.GetDeviceInfo(device, CLDevice.MaxReadImageArgs, out maxReadImageArgs);
            Console.WriteLine("  CL_DEVICE_MAX_READ_IMAGE_ARGS:\t" + maxReadImageArgs);

            int maxWriteImageArgs;
            CL.GetDeviceInfo(device, CLDevice.MaxWriteImageArgs, out maxWriteImageArgs);
            Console.WriteLine("  CL_DEVICE_MAX_WRITE_IMAGE_ARGS:\t" + maxWriteImageArgs);

            int dim;
            Console.Write("\n  CL_DEVICE_IMAGE <dim>");
            CL.GetDeviceInfo(device, CLDevice.Image2DMaxWidth, out dim);
            Console.WriteLine("\t\t\t2D_MAX_WIDTH\t " + dim);
            CL.GetDeviceInfo(device, CLDevice.Image2DMaxHeight, out dim);
            Console.WriteLine("\t\t\t\t\t2D_MAX_HEIGHT\t " + dim);
            CL.GetDeviceInfo(device, CLDevice.Image3DMaxWidth, out dim);
            Console.WriteLine("\t\t\t\t\t3D_MAX_WIDTH\t " + dim);
            CL.GetDeviceInfo(device, CLDevice.Image3DMaxHeight, out dim);
            Console.WriteLine("\t\t\t\t\t3D_MAX_HEIGHT\t " + dim);
            CL.GetDeviceInfo(device, CLDevice.Image3DMaxDepth, out dim);
            Console.WriteLine("\t\t\t\t\t3D_MAX_DEPTH\t " + dim);

            CL.GetDeviceInfo(device, CLDevice.Extensions, out deviceString);
            if (deviceString.Length == 0)
                Console.WriteLine("\n  CL_DEVICE_EXTENSIONS: None");
            else
                Console.WriteLine("\n  CL_DEVICE_EXTENSIONS:" + deviceString);

            Console.Write("  CL_DEVICE_PREFERRED_VECTOR_WIDTH_<t>\t");
            int[] vecWidth = new int[6];
            CL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthChar, out vecWidth[0]);
            CL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthShort, out vecWidth[1]);
            CL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthInt, out vecWidth[2]);
            CL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthLong, out vecWidth[3]);
            CL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthFloat, out vecWidth[4]);
            CL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthDouble, out vecWidth[5]);
            Console.WriteLine("CHAR {0}, SHORT {1}, INT {2}, LONG {4}, FLOAT {3}, DOUBLE {5}\n\n\n",
                vecWidth[0], vecWidth[1], vecWidth[2], vecWidth[3], vecWidth[4], vecWidth[5]);
        }
    }
}
