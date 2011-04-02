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
                Assembly.Load("SharpDX");
            }
            catch
            {
                MessageBox.Show("SharpDX.dll not found. " +
                    "Please download it from http://code.google.com/p/sharpdx.", "Error!");
                return false;
            }

            try
            {
                Assembly.Load("SharpDX.D3DCompiler");
            }
            catch
            {
                MessageBox.Show("SharpDX.D3DCompiler.dll not found. " +
                    "Please download it from http://code.google.com/p/sharpdx.", "Error!");
                return false;
            }

            try
            {
                Assembly.Load("SharpDX.Direct3D10");
            }
            catch
            {
                MessageBox.Show("SharpDX.Direct3D10.dll not found. " +
                    "Please download it from http://code.google.com/p/sharpdx.", "Error!");
                return false;
            }

            try
            {
                Assembly.Load("SharpDX.DXGI");
            }
            catch
            {
                MessageBox.Show("SharpDX.DXGI.dll not found. " +
                    "Please download it from http://code.google.com/p/sharpdx.", "Error!");
                return false;
            }

            /*
            try
            {
                Assembly.Load("SharpDX.Error");
            }
            catch
            {
                MessageBox.Show("SharpDX.Error.dll not found. " +
                    "Please download it from http://code.google.com/p/sharpdx.", "Error!");
                return false;
            }
            */

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
