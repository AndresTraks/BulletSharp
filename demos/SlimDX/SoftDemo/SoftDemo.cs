using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using BulletSharp.SoftBody;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.RawInput;

namespace SoftDemo
{
    class SoftDemo : Game
    {
        Vector3 eye = new Vector3(20, 20, 80);
        Vector3 target = new Vector3(0, 0, 10);

        Light light;
        SlimDX.Direct3D9.Material softBodyMaterial;

        Point lastMousePos;
        Vector3 impact;
        SRayCast results = new SRayCast();
        Node node;
        Vector3 goal;
        bool drag;

        Physics Physics
        {
            get { return (Physics)PhysicsContext; }
            set { PhysicsContext = value; }
        }

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - SoftBody Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            Physics = new Physics();
            Physics.World.SetInternalTickCallback(PickingPreTickCallback, this, true);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 75;
            light.Position = new Vector3(10, 25, 0);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 1.0f;

            softBodyMaterial = new SlimDX.Direct3D9.Material();
            softBodyMaterial.Diffuse = Color.White;
            softBodyMaterial.Ambient = new Color4(Ambient);

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box\n\n" +
                "B - Previous Demo\n" +
                "N - Next Demo";

            Freelook.SetEyeTarget(eye, target);

            base.OnInitialize();
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);

            Device.SetRenderState(RenderState.CullMode, Cull.None);
        }

        void PickingPreTickCallback(DynamicsWorld world, float timeStep)
        {
            if (drag)
            {
                Vector3 rayFrom = Freelook.Eye;
                Vector3 rayTo = GetRayTo(lastMousePos, Freelook.Eye, Freelook.Target, FieldOfView);
                Vector3 rayDir = (rayTo - rayFrom);
                rayDir.Normalize();
                Vector3 N = (Freelook.Target - Freelook.Eye);
                N.Normalize();
                float O = Vector3.Dot(impact, N);
                float den = Vector3.Dot(N, rayDir);
                if ((den * den) > 0)
                {
                    float num = O - Vector3.Dot(N, rayFrom);
                    float hit = num / den;
                    if ((hit > 0) && (hit < 1500))
                    {
                        goal = rayFrom + rayDir * hit;
                    }
                }
                Vector3 delta = goal - node.X;
                float maxdrag = 10;
                if (delta.LengthSquared() > (maxdrag * maxdrag))
                {
                    delta.Normalize();
                    delta *= maxdrag;
                }
                node.Velocity += delta / timeStep;
            }
        }

        protected override void OnHandleInput()
        {
            base.OnHandleInput();

            if (Input.MousePressed == MouseButtonFlags.RightDown)
            {
                results.Fraction = 1;
                if (pickConstraint == null)
                {
                    Vector3 rayFrom = Freelook.Eye;
                    Vector3 rayTo = GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView);
                    Vector3 rayDir = (rayTo - rayFrom);
                    rayDir.Normalize();
                    AlignedSoftBodyArray sbs = ((SoftRigidDynamicsWorld)Physics.World).SoftBodyArray;
                    for (int ib = 0; ib < sbs.Count; ++ib)
                    {
                        SoftBody psb = sbs[ib];
                        SRayCast res = new SRayCast();
                        if (psb.RayTest(rayFrom, rayTo, res))
                        {
                            results = res;
                        }
                    }
                    if (results.Fraction < 1)
                    {
                        impact = rayFrom + (rayTo - rayFrom) * results.Fraction;
                        drag = false;
                        lastMousePos = Input.MousePoint;
                        node = null;
                        switch (results.Feature)
                        {
                            case EFeature.Face:
                                {
                                    Face f = results.Body.Faces[results.Index];
                                    node = f.N[0];
                                    for (int i = 1; i < 3; ++i)
                                    {
                                        if ((node.X - impact).LengthSquared() >
                                            (f.N[i].X - impact).LengthSquared())
                                        {
                                            node = f.N[i];
                                        }
                                    }
                                }
                                break;
                        }
                        if (node != null)
                            goal = node.X;
                        //return;
                    }
                }
            }
            else if (Input.MousePressed == MouseButtonFlags.RightUp)
            {
                if((!drag)&&Physics.cutting&&(results.Fraction<1))
			    {
				    //ImplicitSphere isphere = new ImplicitSphere(impact,1);
				    //results.Body.Refine(isphere,0.0001,true);
			    }
			    results.Fraction=1;
			    drag=false;
            }

            // Mouse movement
            if (Input.MouseDown == MouseButtonFlags.RightDown)
            {
                if (node != null && (results.Fraction < 1))
                {
                    if (!drag)
                    {
                        int x = Input.MousePoint.X - lastMousePos.X;
                        int y = Input.MousePoint.Y - lastMousePos.Y;
                        if ((x * x) + (y * y) > 6)
                        {
                            drag = true;
                        }
                    }
                    if (drag)
                    {
                        lastMousePos = Input.MousePoint;
                    }
                }
            }

            Physics.HandleInput(Input, FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Device.SetTransform(TransformState.View, Freelook.View);

            foreach (CollisionObject colObj in Physics.World.CollisionObjectArray)
            {
                if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    if (IsDebugDrawEnabled)
                        continue;

                    Device.Material = softBodyMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    MeshFactory.Render(colObj);
                }
                else
                {
                    RigidBody body = RigidBody.Upcast(colObj);
                    Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);

                    if ((string)body.UserObject == "Ground")
                        Device.Material = GroundMaterial;
                    else if (colObj.ActivationState == ActivationState.ActiveTag)
                        Device.Material = ActiveMaterial;
                    else
                        Device.Material = PassiveMaterial;

                    MeshFactory.Render(colObj.CollisionShape);
                }
            }

            DebugDrawWorld();

            Fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }

        public SlimDX.Direct3D9.Device Device
        {
            get { return Device9; }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            SoftDemo game = new SoftDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
