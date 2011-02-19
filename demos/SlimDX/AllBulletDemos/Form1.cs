using System;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Threading;
using System.Windows.Forms;

namespace AllBulletDemos
{
    public partial class Form1 : Form
    {
        IDisposable game = null;
        Form form;
        Point prevPosition = Point.Empty;

        public Form1()
        {
            FormClosed += new FormClosedEventHandler(Form1_FormClosed);

            InitializeComponent();

            string[] filePaths = Directory.GetFiles(Application.StartupPath, "*.exe");
            foreach (string file in filePaths)
            {
                try
                {
                    Assembly demo = Assembly.LoadFile(file);
                    Type[] types = demo.GetExportedTypes();
                    foreach (Type type in types)
                    {
                        if (type.BaseType.Name.Equals("Game"))
                        {
                            listBox1.Items.Add(Path.GetFileNameWithoutExtension(file));
                            break;
                        }
                    }
                }
                catch
                {
                }
            }
        }

        void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            TryCloseForm();
        }

        public delegate void InvokeDelegate();

        void CloseForm()
        {
            if (prevPosition.IsEmpty)
                prevPosition = form.Location;
            form.Close();
            form = null;
        }

        void DisposeGame()
        {
            game.Dispose();
            game = null;
        }

        void TryCloseForm()
        {
            if (game != null)
            {
                form.BeginInvoke(new InvokeDelegate(CloseForm));
                while (form != null)
                    Thread.Sleep(100);
                game = null;
            }
        }

        void SetLocation()
        {
            form.Location = prevPosition;
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            TryCloseForm();

            if (listBox1.SelectedItem == null)
                return;

            Assembly demo = Assembly.Load(listBox1.SelectedItem.ToString());
            Type[] types = demo.GetExportedTypes();
            foreach (Type type in types)
            {
                if (type.BaseType.Name.Equals("Game"))
                {
                    game = (IDisposable)type.InvokeMember(null, BindingFlags.CreateInstance, null, null, null);

                    bool librariesOk = (bool)type.InvokeMember("TestLibraries", BindingFlags.InvokeMethod, null, game, null);
                    if (librariesOk == false)
                        return;
                    
                    new Thread(DemoThread).Start();
                    while (form == null)
                    {
                        form = (Form)game.GetType().InvokeMember("Form", BindingFlags.GetProperty, null, game, null);
                    }
                    form.HandleCreated += new EventHandler(form_HandleCreated);
                    break;
                }
            }
        }

        void form_HandleCreated(object sender, EventArgs e)
        {
            form.BeginInvoke(new InvokeDelegate(SetLocation));
        }

        void DemoThread()
        {
            game.GetType().InvokeMember("Run", BindingFlags.InvokeMethod, null, game, null);
            if (form == null || form.IsDisposed)
                DisposeGame();
            else
                form.BeginInvoke(new InvokeDelegate(DisposeGame));
        }
    }
}
