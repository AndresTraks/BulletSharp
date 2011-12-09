using System;
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
            {
                okButton.Enabled = true;
                libraryList.SelectedIndex = 0;
            }

            libraryList.DoubleClick += new EventHandler(libraryList_DoubleClick);
        }

        void libraryList_DoubleClick(object sender, EventArgs e)
        {
            LibraryManager.GraphicsLibraryName = libraryList.SelectedItem as string;
            Close();
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
