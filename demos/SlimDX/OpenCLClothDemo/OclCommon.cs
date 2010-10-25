using System;
using System.Collections.Generic;
using BulletSharp;

namespace OpenCLClothDemo
{
    class OclCommon
    {
        static string platformVendor = "MiniCL, SCEA";
        //static string platformVendor = "Advanced Micro Devices, Inc.";

        public static IntPtr CreateContextFromType(CLDeviceType deviceType, ref int error)
        {
            uint numPlatforms;
            IntPtr platform = IntPtr.Zero;
            IntPtr[] platforms = null;
            int ciErrNum = MiniCL.GetPlatformIDs(0, ref platforms, out numPlatforms);
            if (ciErrNum != 0)
            {
                error = ciErrNum;
                return IntPtr.Zero;
            }

            if (numPlatforms > 0)
            {
                platforms = new IntPtr[numPlatforms];
                ciErrNum = MiniCL.GetPlatformIDs(numPlatforms, ref platforms, out numPlatforms);
                if (ciErrNum != 0)
                {
                    error = ciErrNum;
                    return IntPtr.Zero;
                }
                
                for (int i = 0; i < numPlatforms; ++i)
                {
                    string vendor;
                    ciErrNum = MiniCL.GetPlatformInfo(platforms[i], CLPlatform.Vendor, out vendor);
                    if (ciErrNum != 0)
                    {
                        error = ciErrNum;
                        return IntPtr.Zero;
                    }

                    platform = platforms[i];
                    if (vendor == platformVendor)
                        break;
                }
            }

            List<KeyValuePair<CLContext, IntPtr>> properties = new List<KeyValuePair<CLContext, IntPtr>>();
            properties.Add(new KeyValuePair<CLContext, IntPtr>(CLContext.Platform, platform));
            return MiniCL.CreateContextFromType(properties, deviceType, out error);
        }
    }
}
