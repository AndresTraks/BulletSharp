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
        object currentGame = null;
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
                        if (type.BaseType.Name == "Game")
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

        public delegate void InvokeDelegate(Form form);

        void CloseForm(Form form)
        {
            if (prevPosition.IsEmpty)
                prevPosition = form.Location;
            form.Close();
        }

        void TryCloseForm()
        {
            if (currentGame != null)
            {
                Form form = (Form)
                currentGame.GetType().InvokeMember("Form", BindingFlags.GetProperty, null, currentGame, null);
                form.BeginInvoke(new InvokeDelegate(CloseForm), form);
            }
        }

        void SetLocation(Form form)
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
                if (type.BaseType.Name == "Game")
                {
                    currentGame = type.InvokeMember(null, BindingFlags.CreateInstance, null, null, null);
                    new Thread(DemoThread).Start();
                    Form form = null;
                    while (form == null)
                    {
                        form = (Form)
                        currentGame.GetType().InvokeMember("Form", BindingFlags.GetProperty, null, currentGame, null);
                    }
                    form.HandleCreated += new EventHandler(form_HandleCreated);
                    break;
                }
            }
        }

        void form_HandleCreated(object sender, EventArgs e)
        {
            Form form = (Form)
                        currentGame.GetType().InvokeMember("Form", BindingFlags.GetProperty, null, currentGame, null);
            form.BeginInvoke(new InvokeDelegate(SetLocation), form);
        }

        void DemoThread()
        {
            currentGame.GetType().InvokeMember("Run", BindingFlags.InvokeMethod, null, currentGame, null);
        }
    }
}
