using System;
using System.Reflection;
using System.Windows.Forms;

namespace DemoFramework
{
    public static class LibraryTest
    {
        public static bool Test()
        {
            try
            {
                Assembly.Load("SlimDX, Version=4.0.13.43, Culture=neutral, PublicKeyToken=b1b0c32fd1ffe4f9");
            }
            catch
            {
                MessageBox.Show("SlimDX(v4.0.13.43) not installed." +
                    "Please download it from http://slimdx.org.", "Error!");
                return false;
            }

            try
            {
                Assembly.Load("BulletSharp");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "BulletSharp Error!");
                return false;
            }

            return true;
        }
    }
}
