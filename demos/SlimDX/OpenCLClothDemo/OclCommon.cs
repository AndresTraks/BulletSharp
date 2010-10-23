using System;
using System.Collections.Generic;
using BulletSharp;

namespace OpenCLClothDemo
{
    class OclCommon
    {
        static string platformVendor = "MiniCL, SCEA";

        public static IntPtr CreateContextFromType(CLDeviceType deviceType, ref int error)
        {
            uint numPlatforms;
            string platform = null;
            string[] platforms = null;
            int ciErrNum = MiniCL.GetPlatformIDs(0, ref platforms, out numPlatforms);
            if (ciErrNum != 0)
            {
                error = ciErrNum;
                return IntPtr.Zero;
            }

            for (int i = 0; i < numPlatforms; ++i)
            {
                if (numPlatforms > 0)
                {
                    platforms = new string[numPlatforms];
                    ciErrNum = MiniCL.GetPlatformIDs(numPlatforms, ref platforms, out numPlatforms);
                    if (ciErrNum != 0)
                    {
                        error = ciErrNum;
                        return IntPtr.Zero;
                    }

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

            List<KeyValuePair<CLContext, string>> properties = new List<KeyValuePair<CLContext,string>>();
            properties.Add(new KeyValuePair<CLContext, string>(CLContext.Platform, platform));
            return MiniCL.CreateContextFromType(properties, deviceType, out error);
        }
    }
}
