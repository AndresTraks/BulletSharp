using BulletSharp;
using System;

namespace OpenCLClothDemo
{
    class CLStuff
    {
        public static IntPtr cxMainContext;
        public static IntPtr device;
        public static IntPtr commandQueue;

        // BulletSharp has to be compiled with CL support if these types can't be found. See Stdafx.h
        public static CLDeviceType deviceType = CLDeviceType.All;

        public static void InitCL()
        {
            int ciErrNum = 0;
            cxMainContext = OclCommon.CreateContextFromType(deviceType, ref ciErrNum);
            if (ciErrNum != 0)
            {
                System.Windows.Forms.MessageBox.Show("OpenCL CreateContextFromType failed, error " + ciErrNum);
                return;
            }

            int numDev = OclUtils.GetNumDevices(cxMainContext);
	        if (numDev == 0)
	        {
                System.Windows.Forms.MessageBox.Show("No OpenCL devices found.");
                return;
	        }

            device = OclUtils.GetDevice(cxMainContext, 0);

            OclUtils.PrintDeviceInfo(device);

            commandQueue = CL.CreateCommandQueue(cxMainContext, device, CLCommandQueueProperties.None, out ciErrNum);
            if (ciErrNum != 0)
            {
                System.Windows.Forms.MessageBox.Show("OpenCL CreateCommandQueue failed, error " + ciErrNum);
            }
        }
    }
}
