using System;
using Mogre;

namespace BasicDemo
{
    class BasicDemo : Example
    {
        ColourValue skyColor = new ColourValue(0.6f, 0.7f, 0.8f);
        bool areShadowsEnabled = true;

        MessageHook textInputHandler;
        SceneNode planeNode;
        Physics physics;

        public override void ChooseSceneManager()
        {
            sceneMgr = root.CreateSceneManager(SceneType.ST_GENERIC);
        }

        public override void CreateCamera()
        {
            camera = sceneMgr.CreateCamera("mainCamera");

            camera.Position = new Vector3(10, 20, 50);
            camera.LookAt(0, 1, 0);

            camera.NearClipDistance = 5;
        }

        public override void CreateViewports()
        {
            viewport = window.AddViewport(camera);
            viewport.BackgroundColour = skyColor;
        }

        public override void CreateScene()
        {
            // Set ambient light and fog
            sceneMgr.AmbientLight = new ColourValue(0, 0, 0);
            sceneMgr.SetFog(FogMode.FOG_LINEAR, skyColor, 0, 150, 300);

            // Create sun-light
            Light light = sceneMgr.CreateLight("Sun");
            light.Type = Light.LightTypes.LT_POINT;
            light.Position = new Vector3(150, 100, 150);

            sceneMgr.ShadowTechnique = ShadowTechnique.SHADOWTYPE_STENCIL_MODULATIVE;
		    sceneMgr.ShadowFarDistance = 100;
		    sceneMgr.ShadowColour = new ColourValue(0.7f, 0.7f, 0.7f);
		    sceneMgr.SetShadowTextureSize(512);

            // Ground
            Plane ground = new Plane(Vector3.UNIT_Y, 1);
            MeshManager.Singleton.CreatePlane("groundPlane", ResourceGroupManager.DEFAULT_RESOURCE_GROUP_NAME,
                ground, 500, 500, 20, 20, true, 1, 1, 1, Vector3.UNIT_Z);

            Entity groundEnt = sceneMgr.CreateEntity("groundPlaneEntity", "groundPlane");
            groundEnt.CastShadows = true;
            groundEnt.SetMaterialName("BoxMaterial/Ground");

            planeNode = sceneMgr.RootSceneNode.CreateChildSceneNode();
            planeNode.AttachObject(groundEnt);

            physics = new Physics(sceneMgr);
        }

        void textInputHandler_MessageReceived(object sender, EventArgs e)
        {
            //if (isKeyBoardFocused)
            //
        }

        public override void DestroyScene()
        {
            base.DestroyScene();

            physics.ExitPhysics();

            textInputHandler.MessageReceived -= textInputHandler_MessageReceived;
            if (textInputHandler != null)
                textInputHandler.Dispose();

            if (sceneMgr != null)
                sceneMgr.ClearScene();

            if (Root.Singleton != null)
                Root.Singleton.Dispose();
        }

        public override void CreateFrameListener()
        {
            base.CreateFrameListener();
            root.FrameStarted += new FrameListener.FrameStartedHandler(root_FrameStarted);
        }

       public override void CreateInput()
        {
            base.CreateInput();

            IntPtr windowHnd;
            window.GetCustomAttribute("WINDOW", out windowHnd);
            textInputHandler = new MessageHook(windowHnd);
            textInputHandler.MessageReceived += new EventHandler(textInputHandler_MessageReceived);

            inputKeyboard.KeyPressed += new MOIS.KeyListener.KeyPressedHandler(inputKeyboard_KeyPressed);
            inputMouse.MouseMoved += new MOIS.MouseListener.MouseMovedHandler(inputMouse_MouseMoved);
            inputMouse.MousePressed += new MOIS.MouseListener.MousePressedHandler(inputMouse_MousePressed);
            inputMouse.MouseReleased += new MOIS.MouseListener.MouseReleasedHandler(inputMouse_MouseReleased);

            MOIS.MouseState_NativePtr mouseState = inputMouse.MouseState;
            mouseState.width = viewport.ActualWidth;
            mouseState.height = viewport.ActualHeight;
        }

        bool inputKeyboard_KeyPressed(MOIS.KeyEvent e)
        {
            switch (e.key)
            {
                case MOIS.KeyCode.KC_F6:
                    switch (camera.PolygonMode)
                    {
                        case PolygonMode.PM_POINTS:
                            camera.PolygonMode = PolygonMode.PM_SOLID;
                            break;
                        case PolygonMode.PM_SOLID:
                            camera.PolygonMode = PolygonMode.PM_WIREFRAME;
                            break;
                        case PolygonMode.PM_WIREFRAME:
                            camera.PolygonMode = PolygonMode.PM_POINTS;
                            break;
                    }
                    break;
                case MOIS.KeyCode.KC_F7:
        			areShadowsEnabled = !areShadowsEnabled;
			        if(areShadowsEnabled)
                        sceneMgr.ShadowTechnique = ShadowTechnique.SHADOWTYPE_STENCIL_MODULATIVE;
    	    		else
                        sceneMgr.ShadowTechnique = ShadowTechnique.SHADOWTYPE_NONE;
                    break;
                case MOIS.KeyCode.KC_F8:
                    sceneMgr.ShowBoundingBoxes = !sceneMgr.ShowBoundingBoxes;
                    break;
                case MOIS.KeyCode.KC_SYSRQ:
                    TakeScreenshot();
                    break;
            }
            return true;
        }

        protected override void HandleInput(FrameEvent evt)
        {
            inputKeyboard.Capture();
            inputMouse.Capture();

            if (inputKeyboard.IsKeyDown(MOIS.KeyCode.KC_ESCAPE) || inputKeyboard.IsKeyDown(MOIS.KeyCode.KC_Q))
            {
                // stop rendering loop
                shutDown = true;
            }
        }

        bool inputMouse_MouseMoved(MOIS.MouseEvent arg)
        {
            return true;
        }

        bool inputMouse_MousePressed(MOIS.MouseEvent arg, MOIS.MouseButtonID id)
        {
            //if (id == MOIS.MouseButtonID.MB_Left)
            return true;
        }

        bool inputMouse_MouseReleased(MOIS.MouseEvent arg, MOIS.MouseButtonID id)
        {
            //if (id == MOIS.MouseButtonID.MB_Left)
            return true;
        }

        bool root_FrameStarted(FrameEvent evt)
        {
            physics.Update(evt.timeSinceLastFrame);
            return true;
        }
    }
}
