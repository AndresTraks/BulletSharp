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
    }
}
