using System;
using System.Reflection;
using System.Windows.Forms;

namespace SimplestDemo
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            try
            {
                Assembly.Load("SlimDX, Version=4.0.13.43, Culture=neutral, PublicKeyToken=b1b0c32fd1ffe4f9");
            }
            catch
            {
                MessageBox.Show("SlimDX(4.0.13.43) not installed." +
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

            SimplestDemo game = new SimplestDemo();
            game.Dispose();
        }
    }
}
