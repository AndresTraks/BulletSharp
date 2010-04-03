using System;
using System.Collections.Generic;
using Mogre;

namespace BasicDemo
{
    public abstract class Example
    {
        public static void ShowOgreException()
        {
            if (OgreException.IsThrown)
                System.Windows.Forms.MessageBox.Show(OgreException.LastException.FullDescription, "An exception has occured!", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
        }

        protected Root root;
        protected Camera camera;
        protected Viewport viewport;
        protected SceneManager sceneMgr;
        protected RenderWindow window;
        protected MOIS.InputManager inputManager;
        protected MOIS.Keyboard inputKeyboard;
        protected MOIS.Mouse inputMouse;

        protected bool shutDown = false;

        public virtual void Go()
        {
            if (!Setup())
                return;

            root.StartRendering();

            // clean up
            DestroyScene();

            root.Dispose();
            root = null;
        }

        public virtual bool Setup()
        {
            root = new Root();

            bool carryOn = Configure();
            if (!carryOn) return false;

            SetupResources();
            ChooseSceneManager();
            CreateCamera();
            CreateViewports();

            // Set default mipmap level (NB some APIs ignore this)
            TextureManager.Singleton.DefaultNumMipmaps = 5;

            // Create any resource listeners (for loading screens)
            CreateResourceListener();
            LoadResources();

            // Create the scene
            CreateScene();

            CreateFrameListener();

            CreateInput();

            return true;

        }

        /// <summary>
        /// Configures the application - returns false if the user chooses to abandon configuration.
        /// </summary>
        public virtual bool Configure()
        {
            // Show the configuration dialog and initialise the system
            // You can skip this and use root.restoreConfig() to load configuration
            // settings if you were sure there are valid ones saved in ogre.cfg
            if (root.ShowConfigDialog())
            {
                // If returned true, user clicked OK so initialise
                // Here we choose to let the system create a default rendering window by passing 'true'
                window = root.Initialise(true, "BulletSharp Mogre Demo");
                return true;
            }
            else
            {
                return false;
            }
        }

        public virtual void ChooseSceneManager()
        {
            sceneMgr = root.CreateSceneManager(SceneType.ST_GENERIC, "SceneMgr");
        }

        public virtual void CreateCamera()
        {
            /*
            // Create the camera
            camera = sceneMgr.CreateCamera("PlayerCam");

            // Position it at 500 in Z direction
            camera.Position = new Vector3(0, 0, 500);
            // Look back along -Z
            camera.LookAt(new Vector3(0, 0, -300));
            camera.NearClipDistance = 5;
            */
        }

        public virtual void CreateFrameListener()
        {
            root.FrameStarted += new FrameListener.FrameStartedHandler(ExampleApp_FrameStarted);
        }

        bool ExampleApp_FrameStarted(FrameEvent evt)
        {
            if (window.IsClosed)
                return false;

            HandleInput(evt);

            return !shutDown;
        }

        protected virtual void HandleInput(FrameEvent evt)
        {
        }

        protected void TakeScreenshot()
        {
            string[] temp = System.IO.Directory.GetFiles(Environment.CurrentDirectory, "screenshot*.jpg");
            string fileName = string.Format("screenshot{0}.jpg", temp.Length + 1);

            TakeScreenshot(fileName);
        }

        protected void TakeScreenshot(string fileName)
        {
            window.WriteContentsToFile(fileName);
        }

        public virtual void CreateInput()
        {
            LogManager.Singleton.LogMessage("*** Initializing OIS ***");
            MOIS.ParamList pl = new MOIS.ParamList();
            IntPtr windowHnd;
            window.GetCustomAttribute("WINDOW", out windowHnd);
            pl.Insert("WINDOW", windowHnd.ToString());

            pl.Insert("w32_mouse", "DISCL_FOREGROUND");
            pl.Insert("w32_mouse", "DISCL_NONEXCLUSIVE");

            inputManager = MOIS.InputManager.CreateInputSystem(pl);

            //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
            inputKeyboard = (MOIS.Keyboard)inputManager.CreateInputObject(MOIS.Type.OISKeyboard, true);
            inputMouse = (MOIS.Mouse)inputManager.CreateInputObject(MOIS.Type.OISMouse, true);
        }

        public abstract void CreateScene();    // pure virtual - this has to be overridden

        public virtual void DestroyScene() { }    // Optional to override this

        public virtual void CreateViewports()
        {
            // Create one viewport, entire window
            viewport = window.AddViewport(camera);
            viewport.BackgroundColour = new ColourValue(0, 0, 0);

            // Alter the camera aspect ratio to match the viewport
            camera.AspectRatio = ((float)viewport.ActualWidth) / ((float)viewport.ActualHeight);
        }

        /// Method which will define the source of resources (other than current folder)
        public virtual void SetupResources()
        {
            if (System.IO.File.Exists("resources.cfg") == false)
                return;

            // Load resource paths from config file
            ConfigFile cf = new ConfigFile();
            cf.Load("resources.cfg", "\t:=", true);

            // Go through all sections & settings in the file
            ConfigFile.SectionIterator seci = cf.GetSectionIterator();

            String secName, typeName, archName;

            // Normally we would use the foreach syntax, which enumerates the values, but in this case we need CurrentKey too;
            while (seci.MoveNext())
            {
                secName = seci.CurrentKey;
                ConfigFile.SettingsMultiMap settings = seci.Current;
                foreach (KeyValuePair<string, string> pair in settings)
                {
                    typeName = pair.Key;
                    archName = pair.Value;
                    ResourceGroupManager.Singleton.AddResourceLocation(archName, typeName, secName);
                }
            }
        }

        /// Optional override method where you can create resource listeners (e.g. for loading screens)
        public virtual void CreateResourceListener()
        {

        }

        /// Optional override method where you can perform resource group loading
        /// Must at least do ResourceGroupManager.Singleton.InitialiseAllResourceGroups();
        public virtual void LoadResources()
        {
            // Initialise, parse scripts etc
            ResourceGroupManager.Singleton.InitialiseAllResourceGroups();
        }
    }
}
