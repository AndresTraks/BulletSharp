using System;
using System.Reflection;
using System.Windows.Forms;

namespace BasicDemo
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            try
            {
                Assembly.Load("Microsoft.Xna.Framework, Version=3.1.0.0, Culture=neutral, PublicKeyToken=6d5c3888ef60e27d");
            }
            catch
            {
                MessageBox.Show("XNA 3.1 redistributable not installed.", "Error!");
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

            using (BasicDemo game = new BasicDemo())
            {
                game.Run();
            }
        }
    }
}

