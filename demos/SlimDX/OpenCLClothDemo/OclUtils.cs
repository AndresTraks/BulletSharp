using System;
using BulletSharp;

namespace OpenCLClothDemo
{
    class OclUtils
    {
        public static IntPtr GetMaxFlopsDev(IntPtr cxMainContext)
        {
            // get the list of GPU devices associated with context
            IntPtr[] devices;
            MiniCL.GetContextInfo(cxMainContext, CLContext.Devices, out devices);

            int maxFlops = 0;
            IntPtr maxFlopsDevice = devices[0];

            foreach (IntPtr device in devices)
            {
                int computeUnits;
                MiniCL.GetDeviceInfo(device, CLDevice.MaxComputeUnits, out computeUnits);

                int clockCrequency;
                MiniCL.GetDeviceInfo(device, CLDevice.MaxClockFrequency, out clockCrequency);

                int flops = computeUnits * clockCrequency;
                if (flops > maxFlops)
                {
                    maxFlops = flops;
                    maxFlopsDevice = device;
                }
            }

            return maxFlopsDevice;
        }

        public static void PrintDeviceInfo(IntPtr device)
        {
            string deviceString;

            MiniCL.GetDeviceInfo(device, CLDevice.Name, out deviceString);
            Console.WriteLine("  CL_DEVICE_NAME:\t\t\t" + deviceString);

            MiniCL.GetDeviceInfo(device, CLDevice.Vendor, out deviceString);
            Console.WriteLine("  CL_DEVICE_VENDOR:\t\t\t" + deviceString);

            MiniCL.GetDeviceInfo(device, CLDevice.DriverVersion, out deviceString);
            Console.WriteLine("  CL_DEVICE_VERSION:\t\t\t" + deviceString);

            CLDeviceType deviceType;
            MiniCL.GetDeviceInfo(device, CLDevice.Type, out deviceType);

            if ((deviceType & CLDeviceType.Cpu) == CLDeviceType.Cpu)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_CPU");
            if ((deviceType & CLDeviceType.Cpu) == CLDeviceType.Gpu)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_GPU");
            if ((deviceType & CLDeviceType.Cpu) == CLDeviceType.Accelerator)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_DEFAULT");
            if ((deviceType & CLDeviceType.Cpu) == CLDeviceType.Default)
                Console.WriteLine("  CL_DEVICE_TYPE:\t\t\tCL_DEVICE_TYPE_DEFAULT");

            int computeUnits;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxComputeUnits, out computeUnits);
            Console.WriteLine("  CL_DEVICE_MAX_COMPUTE_UNITS:\t\t" + computeUnits);

            int workitemDims;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxWorkItemDimensions, out workitemDims);
            Console.WriteLine("  CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:\t" + workitemDims);

            int[] workitemSizes;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxWorkItemSizes, out workitemSizes);
            Console.WriteLine("  CL_DEVICE_MAX_WORK_ITEM_SIZES:\t" + workitemSizes[0] + " / " + workitemSizes[1] + " / " + workitemSizes[2]);

            int workgroupSize;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxWorkGroupSize, out workgroupSize);
            Console.WriteLine("  CL_DEVICE_MAX_WORK_GROUP_SIZE:\t" + workgroupSize);

            int clockFrequency;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxClockFrequency, out clockFrequency);
            Console.WriteLine("  CL_DEVICE_MAX_CLOCK_FREQUENCY:\t" + clockFrequency + " MHz");

            int addrBits;
            MiniCL.GetDeviceInfo(device, CLDevice.AddressBits, out addrBits);
            Console.WriteLine("  CL_DEVICE_ADDRESS_BITS:\t\t" + addrBits);

            ulong maxMemAllocSize;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxMemAllocSize, out maxMemAllocSize);
            Console.WriteLine("  CL_DEVICE_MAX_MEM_ALLOC_SIZE:\t\t" + maxMemAllocSize / (1024 * 1024) + " MByte");

            ulong globalMemSize;
            MiniCL.GetDeviceInfo(device, CLDevice.GlobalMemSize, out globalMemSize);
            Console.WriteLine("  CL_DEVICE_GLOBAL_MEM_SIZE:\t\t" + globalMemSize / (1024 * 1024) + " MByte");

            bool errorCorrectionSupport;
            MiniCL.GetDeviceInfo(device, CLDevice.ErrorCorrectionSupport, out errorCorrectionSupport);
            Console.WriteLine("  CL_DEVICE_ERROR_CORRECTION_SUPPORT:\t" + (errorCorrectionSupport ? "yes" : "no"));

            CLDeviceLocalMemoryType localMemType;
            MiniCL.GetDeviceInfo(device, CLDevice.LocalMemType, out localMemType);
            Console.WriteLine("  CL_DEVICE_LOCAL_MEM_TYPE:\t\t" + localMemType);

            ulong localMemSize;
            MiniCL.GetDeviceInfo(device, CLDevice.LocalMemSize, out localMemSize);
            Console.WriteLine("  CL_DEVICE_LOCAL_MEM_SIZE:\t\t" + localMemSize / 1024 + " KByte");

            ulong constantBufferSize;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxConstantBufferSize, out constantBufferSize);
            Console.WriteLine("  CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:\t" + constantBufferSize / 1024 + " KByte");

            CLCommandQueueProperties queueProperties;
            MiniCL.GetDeviceInfo(device, CLDevice.Type, out queueProperties);

            if ((queueProperties & CLCommandQueueProperties.OutOfOrderExecModeEnable) == CLCommandQueueProperties.OutOfOrderExecModeEnable)
                Console.WriteLine("  CL_DEVICE_QUEUE_PROPERTIES:\t\tCL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
            if ((queueProperties & CLCommandQueueProperties.ProfilingEnable) == CLCommandQueueProperties.ProfilingEnable)
                Console.WriteLine("  CL_DEVICE_QUEUE_PROPERTIES:\t\tCL_QUEUE_PROFILING_ENABLE");

            bool imageSupport;
            MiniCL.GetDeviceInfo(device, CLDevice.ImageSupport, out imageSupport);
            Console.WriteLine("  CL_DEVICE_IMAGE_SUPPORT:\t\t" + imageSupport);

            int maxReadImageArgs;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxReadImageArgs, out maxReadImageArgs);
            Console.WriteLine("  CL_DEVICE_MAX_READ_IMAGE_ARGS:\t" + maxReadImageArgs);

            int maxWriteImageArgs;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxWriteImageArgs, out maxWriteImageArgs);
            Console.WriteLine("  CL_DEVICE_MAX_WRITE_IMAGE_ARGS:\t" + maxWriteImageArgs);

            int dim;
            Console.Write("\n  CL_DEVICE_IMAGE <dim>");
            MiniCL.GetDeviceInfo(device, CLDevice.Image2DMaxWidth, out dim);
            Console.WriteLine("\t\t\t2D_MAX_WIDTH\t " + dim);
            MiniCL.GetDeviceInfo(device, CLDevice.Image2DMaxHeight, out dim);
            Console.WriteLine("\t\t\t\t\t2D_MAX_HEIGHT\t " + dim);
            MiniCL.GetDeviceInfo(device, CLDevice.Image3DMaxWidth, out dim);
            Console.WriteLine("\t\t\t\t\t3D_MAX_WIDTH\t " + dim);
            MiniCL.GetDeviceInfo(device, CLDevice.Image3DMaxHeight, out dim);
            Console.WriteLine("\t\t\t\t\t3D_MAX_HEIGHT\t " + dim);
            MiniCL.GetDeviceInfo(device, CLDevice.Image3DMaxDepth, out dim);
            Console.WriteLine("\t\t\t\t\t3D_MAX_DEPTH\t " + dim);

            MiniCL.GetDeviceInfo(device, CLDevice.Extensions, out deviceString);
            if (deviceString.Length == 0)
                Console.WriteLine("\n  CL_DEVICE_EXTENSIONS: None");
            else
                Console.WriteLine("\n  CL_DEVICE_EXTENSIONS:" + deviceString);

            Console.Write("  CL_DEVICE_PREFERRED_VECTOR_WIDTH_<t>\t");
            int[] vecWidth = new int[6];
            MiniCL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthChar, out vecWidth[0]);
            MiniCL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthShort, out vecWidth[1]);
            MiniCL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthInt, out vecWidth[2]);
            MiniCL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthLong, out vecWidth[3]);
            MiniCL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthFloat, out vecWidth[4]);
            MiniCL.GetDeviceInfo(device, CLDevice.PreferredVectorWidthDouble, out vecWidth[5]);
            Console.WriteLine("CHAR {0}, SHORT {1}, INT {2}, LONG {4}, FLOAT {3}, DOUBLE {5}\n\n\n",
                vecWidth[0], vecWidth[1], vecWidth[2], vecWidth[3], vecWidth[4], vecWidth[5]);
        }
    }
}
