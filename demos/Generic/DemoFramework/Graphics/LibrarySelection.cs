using System;
using System.Windows.Forms;

namespace DemoFramework
{
    public partial class LibrarySelection : Form
    {
        public LibrarySelection()
        {
            InitializeComponent();

            AcceptButton = runButton;
            CancelButton = cancelButton;

            string[] supportedLibraries = GraphicsLibraryManager.GetSupportedLibraries();
            int selectLibrary = 0;
            foreach (string library in supportedLibraries)
            {
                if (GraphicsLibraryManager.IsLibraryAvailable(library))
                {
                    int index = libraryList.Items.Add(library);
                    logText.Text += library + " OK\r\n";
                    if (library.Equals(GraphicsLibraryManager.GraphicsLibraryName))
                    {
                        selectLibrary = index;
                    }
                }
                else
                {
                    logText.Text += library + " not loaded\r\n";
                }
            }

            if (libraryList.Items.Count != 0)
            {
                runButton.Enabled = true;
                libraryList.SelectedIndex = selectLibrary;
            }
            GraphicsLibraryManager.GraphicsLibraryName = null;

            libraryList.DoubleClick += new EventHandler(libraryList_DoubleClick);
        }

        void libraryList_DoubleClick(object sender, EventArgs e)
        {
            GraphicsLibraryManager.GraphicsLibraryName = libraryList.SelectedItem as string;
            Close();
        }

        private void runButton_Click(object sender, EventArgs e)
        {
            GraphicsLibraryManager.GraphicsLibraryName = libraryList.SelectedItem as string;
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
