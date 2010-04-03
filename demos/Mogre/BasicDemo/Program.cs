using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace BasicDemo
{
    class Program
    {
        [STAThread]
        static void Main()
        {
            try
            {
                Assembly.Load("Mogre");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "Could not load Mogre!");
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

            try
            {
                BasicDemo app = new BasicDemo();
                app.Go();
            }
            catch (System.Runtime.InteropServices.SEHException)
            {
                // Check if it's an Ogre Exception
                if (Mogre.OgreException.IsThrown)
                    Example.ShowOgreException();
                else
                    throw;
            }
        }
    }
}
