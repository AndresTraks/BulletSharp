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
            string stringOut;

            MiniCL.GetDeviceInfo(device, CLDevice.Name, out stringOut);
            Console.WriteLine("  CL_DEVICE_NAME:\t\t\t" + stringOut);

            MiniCL.GetDeviceInfo(device, CLDevice.Vendor, out stringOut);
            Console.WriteLine("  CL_DEVICE_VENDOR:\t\t\t" + stringOut);

            MiniCL.GetDeviceInfo(device, CLDevice.DriverVersion, out stringOut);
            Console.WriteLine("  CL_DEVICE_VERSION:\t\t\t" + stringOut);

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

            int maxMemAllocSize;
            MiniCL.GetDeviceInfo(device, CLDevice.MaxMemAllocSize, out maxMemAllocSize);
            Console.WriteLine("  CL_DEVICE_MAX_MEM_ALLOC_SIZE:\t\t" + maxMemAllocSize / (1024 * 1024) + " MByte");

            int globalMemSize;
            MiniCL.GetDeviceInfo(device, CLDevice.GlobalMemSize, out globalMemSize);
            Console.WriteLine("  CL_DEVICE_GLOBAL_MEM_SIZE:\t\t" + globalMemSize / (1024 * 1024) + " MByte");

            bool errorCorrectionSupport;
            MiniCL.GetDeviceInfo(device, CLDevice.ErrorCorrectionSupport, out errorCorrectionSupport);
            Console.WriteLine("  CL_DEVICE_ERROR_CORRECTION_SUPPORT:\t" + (errorCorrectionSupport ? "yes" : "no"));
        }
    }
}
