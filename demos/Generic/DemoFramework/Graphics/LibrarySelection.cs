using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace DemoFramework
{
    public partial class LibrarySelection : Form
    {
        public LibrarySelection()
        {
            InitializeComponent();

            string[] supportedLibraries = LibraryManager.GetSupportedLibraries();
            foreach (string library in supportedLibraries)
            {
                if (LibraryManager.IsLibraryAvailable(library))
                {
                    libraryList.Items.Add(library);
                    logText.Text += library + " OK\r\n";
                }
                else
                {
                    logText.Text += library + " not loaded\r\n";
                }
            }
            if (libraryList.Items.Count != 0)
                libraryList.SelectedIndex = 0;
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            LibraryManager.GraphicsLibraryName = libraryList.SelectedItem as string;
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
