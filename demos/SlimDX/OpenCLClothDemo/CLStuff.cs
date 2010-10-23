using BulletSharp;
using System;

namespace OpenCLClothDemo
{
    class CLStuff
    {
        public static IntPtr cxMainContext;
        public static IntPtr device;
        public static IntPtr commandQueue;

        public static void InitCL()
        {
            int ciErrNum = 0;
            cxMainContext = OclCommon.CreateContextFromType(CLDeviceType.All, ref ciErrNum);
            device = OclUtils.GetMaxFlopsDev(cxMainContext);
            commandQueue = MiniCL.CreateCommandQueue(cxMainContext, device, CLCommandQueueProperties.None, out ciErrNum);
        }
    }
}
