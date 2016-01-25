using System;
using System.Reflection;
using System.Windows.Forms;

namespace DemoFramework
{
    public static class LibraryTest
    {
        public static bool Test()
        {
            foreach (string assemblyName in new[] { "SharpDX", "SharpDX.D3DCompiler", "SharpDX.Direct3D11", "SharpDX.DXGI" })
            {
                try
                {
                    Assembly.Load(assemblyName);
                }
                catch
                {
                    MessageBox.Show(assemblyName + ".dll not found.", "Error!");
                    return false;
                }
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
