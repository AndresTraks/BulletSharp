using System;
using System.Reflection;
using System.Windows.Forms;

namespace BasicDemo
{
    public static class Program
    {
        [STAThread]
        static void Main()
        {
            try
            {
                Assembly.Load("BulletSharp");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "BulletSharp Error!");
                return;
            }

            using (var game = new BasicDemo())
                game.Run();
        }
    }
}
