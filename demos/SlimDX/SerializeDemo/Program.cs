using System;
using System.Reflection;
using System.Windows.Forms;

namespace SerializeDemo
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
            catch(Exception e)
            {
                MessageBox.Show(e.ToString(), "BulletSharp Error!");
                return;
            }

            SerializeDemo game = new SerializeDemo();
            game.Run();
            game.Dispose();
        }
    }
}
