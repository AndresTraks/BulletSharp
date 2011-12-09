using System;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using System.Xml;

namespace DemoFramework
{
    public class LibraryManager
    {
        static string settingsFilename = "settings.xml";
        public static string GraphicsLibraryName
        {
            get;
            set;
        }

        static string[] supportedLibraries = new string[] { "SharpDX (DirectX 10)", "SlimDX (DirectX 9)", "OpenTK (OpenGL)" };
        public static string[] GetSupportedLibraries()
        {
            return supportedLibraries;
        }

        public static bool IsLibraryAvailable(string library)
        {
            string[] assemblyNames;
            switch (library)
            {
                case "SharpDX (DirectX 10)":
                    assemblyNames = new string[] { "DemoFramework.SharpDX", "SharpDX", "SharpDX.Direct3D10", "SharpDX.DXGI", "SharpDX.D3DCompiler" };
                    break;
                case "SlimDX (DirectX 9)":
                    assemblyNames = new string[] { "DemoFramework.SlimDX", "SlimDX, Version=4.0.12.43, Culture=neutral, PublicKeyToken=b1b0c32fd1ffe4f9" };
                    break;
                case "OpenTK (OpenGL)":
                    assemblyNames = new string[] { "DemoFramework.OpenTK", "OpenTK" };
                    break;
                default:
                    return false;
            }

            try
            {
                foreach (string assemblyName in assemblyNames)
                {
                    Assembly.Load(assemblyName);
                }
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        public static Graphics GetGraphics(Demo demo)
        {
            Type graphicsType;
            Assembly assembly;
            switch (LibraryManager.GraphicsLibraryName)
            {
                case "SharpDX (DirectX 10)":
                    assembly = Assembly.Load("DemoFramework.SharpDX");
                    graphicsType = assembly.GetType("DemoFramework.SharpDX.SharpDXGraphics");
                    break;
                case "SlimDX (DirectX 9)":
                    assembly = Assembly.Load("DemoFramework.SlimDX");
                    graphicsType = assembly.GetType("DemoFramework.SlimDX.SlimDXGraphics");
                    break;
                case "OpenTK (OpenGL)":
                    assembly = Assembly.Load("DemoFramework.OpenTK");
                    graphicsType = assembly.GetType("DemoFramework.OpenTK.OpenTKGraphics");
                    break;
                default:
                    return null;
            }
            return graphicsType.InvokeMember(null, BindingFlags.CreateInstance, null, null, new[] { demo }) as Graphics;
        }

        public static bool Initialize()
        {
            Application.EnableVisualStyles();

            // Check if BulletSharp exists
            try
            {
                Assembly.Load("BulletSharp");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "BulletSharp Error!");
                return false;
            }


            // Load settings
            XmlDocument settings = new XmlDocument();
            XmlElement root;
            try
            {
                settings.Load(settingsFilename);
                root = settings.DocumentElement;
            }
            catch (FileNotFoundException)
            {
                // Create an empty settings file
                root = settings.CreateElement("settings");
                settings.AppendChild(root);
                settings.Save(settingsFilename);
            }

            XmlElement graphics;
            XmlNodeList l = root.GetElementsByTagName("graphicsframework");
            if (l.Count == 1)
            {
                graphics = l.Item(0) as XmlElement;
                GraphicsLibraryName = graphics.GetAttribute("value");
            }
            else
            {
                // No library selected yet, select one now
                Application.Run(new LibrarySelection());

                // Nothing selected
                if (GraphicsLibraryName == null)
                {
                    return false;
                }

                graphics = settings.CreateElement("graphicsframework");
                graphics.SetAttribute("value", GraphicsLibraryName);
                root.AppendChild(graphics);
                settings.Save(settingsFilename);
            }

            return true;
        }
    }
}
