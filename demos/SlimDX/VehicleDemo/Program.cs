using System;
using System.Reflection;
using System.Windows.Forms;

namespace VehicleDemo
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            try
            {
                Assembly.Load("SlimDX, Version=2.0.9.42, Culture=neutral, PublicKeyToken=b1b0c32fd1ffe4f9");
            }
            catch
            {
                MessageBox.Show("SlimDX(v2.0.9.42) not installed." +
                    "Please download it from http://slimdx.org.", "Error!");
                return;
            }

            try
            {
                Assembly.Load("BulletSharp");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "BulletSharp Error!");
                return;
            }

            VehicleDemo game = new VehicleDemo();
            game.Run();
            game.Dispose();
        }
    }
}
