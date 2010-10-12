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
                Assembly.Load("Microsoft.Xna.Framework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553");
            }
            catch
            {
                MessageBox.Show("XNA 4.0 redistributable not installed.", "Error!");
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
