using BulletSharp;
using System;

namespace OpenCLClothDemo
{
    class CLStuff
    {
        public static IntPtr cxMainContext;
        public static IntPtr device;
        public static IntPtr commandQueue;
        public static CLDeviceType deviceType = CLDeviceType.Cpu;

        public static void InitCL()
        {
            int ciErrNum = 0;
            cxMainContext = OclCommon.CreateContextFromType(deviceType, ref ciErrNum);
            if (ciErrNum != 0)
            {
                System.Windows.Forms.MessageBox.Show("OpenCL CreateContextFromType failed, error " + ciErrNum);
                return;
            }

            device = OclUtils.GetMaxFlopsDev(cxMainContext);

            OclUtils.PrintDeviceInfo(device);

            commandQueue = CL.CreateCommandQueue(cxMainContext, device, CLCommandQueueProperties.None, out ciErrNum);
        }
    }
}
