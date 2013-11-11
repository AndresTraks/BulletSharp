using System;
using System.Reflection;
using System.Windows.Forms;

namespace BasicDemo
{
#if WINDOWS || XBOX
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            try
            {
                Assembly.Load("MonoGame.Framework, Version=3.0.1.0, Culture=neutral, PublicKeyToken=null");
            }
            catch
            {
                MessageBox.Show("MonoGame 3.0.1 redistributable not installed.", "Error!");
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
#endif
}
