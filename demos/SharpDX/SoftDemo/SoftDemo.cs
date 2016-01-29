using BulletSharp;
using BulletSharp.SoftBody;
using DemoFramework;
using SharpDX;
using System;
using System.Linq;
using System.Windows.Forms;
using Point = System.Drawing.Point;

namespace SoftDemo
{
    class ImplicitSphere : ImplicitFn
    {
        Vector3 _center;
        float _sqRadius;

        public ImplicitSphere(Vector3 center, float radius)
        {
            _center = center;
            _sqRadius = radius * radius;
        }

        public override float Eval(Vector3 x)
        {
            return (x - _center).LengthSquared() - _sqRadius;
        }
    };

    public class SoftDemo : Demo
    {
        Vector3 eye = new Vector3(20, 20, 80);
        Vector3 target = new Vector3(0, 0, 10);

        Point lastMousePos;
        Vector3 impact;
        SRayCast results = new SRayCast();
        Node node;
        Vector3 goal;
        bool drag;

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();
            PhysicsContext.World.SetInternalTickCallback(PickingPreTickCallback, this, true);

            DemoText = "B - Previous Demo\n" +
                "N - Next Demo";
            Form.Text = "BulletSharp - SoftBody Demo";

            Freelook.SetEyeTarget(eye, target);
            CullingEnabled = false;

            base.OnInitialize();
        }

        void PickingPreTickCallback(DynamicsWorld world, float timeStep)
        {
            if (!drag) return;

            Vector3 rayFrom = Freelook.Eye;
            Vector3 rayTo = GetRayTo(lastMousePos, Freelook.Eye, Freelook.Target, FieldOfView);
            Vector3 rayDir = rayTo - rayFrom;
            rayDir.Normalize();
            Vector3 N = Freelook.Target - rayFrom;
            N.Normalize();
            float O = Vector3.Dot(impact, N);
            float den = Vector3.Dot(N, rayDir);
            if ((den * den) > 0)
            {
                float num = O - Vector3.Dot(N, rayFrom);
                float hit = num / den;
                if (hit > 0 && hit < 1500)
                {
                    goal = rayFrom + rayDir * hit;
                }
            }
            Vector3 delta = goal - node.X;
            float maxDrag = 10;
            if (delta.LengthSquared() > (maxDrag * maxDrag))
            {
                delta.Normalize();
                delta *= maxDrag;
            }
            node.Velocity += delta / timeStep;
        }

        protected override void OnHandleInput()
        {
            base.OnHandleInput();

            if (Input.MousePressed == MouseButtons.Right)
            {
                results.Fraction = 1;
                if (pickConstraint == null)
                {
                    Vector3 rayFrom = Freelook.Eye;
                    Vector3 rayTo = GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView);
                    Vector3 rayDir = rayTo - rayFrom;
                    rayDir.Normalize();

                    SRayCast res = new SRayCast();
                    var softBodies = (PhysicsContext.World as SoftRigidDynamicsWorld).SoftBodyArray;
                    if (softBodies.Any(b => b.RayTest(rayFrom, rayTo, res)))
                    {
                        results = res;
                        impact = rayFrom + (rayTo - rayFrom) * results.Fraction;
                        drag = !(PhysicsContext as Physics).cutting;
                        lastMousePos = Input.MousePoint;

                        NodePtrArray nodes;
                        switch (results.Feature)
                        {
                            case EFeature.Face:
                                nodes = results.Body.Faces[results.Index].N;
                                break;
                            case EFeature.Tetra:
                                nodes = results.Body.Tetras[results.Index].Nodes;
                                break;
                            default:
                                nodes = null;
                                break;
                        }
                        if (nodes != null)
                        {
                            node = nodes.Aggregate((min, n) =>
                                (n.X - impact).LengthSquared() <
                                (min.X - impact).LengthSquared() ? n : min
                            );
                            goal = node.X;
                        }
                        else
                        {
                            node = null;
                        }
                    }
                }
            }
            else if (Input.MouseReleased == MouseButtons.Right)
            {
                if (!drag && (PhysicsContext as Physics).cutting && results.Fraction < 1)
                {
                    using (var isphere = new ImplicitSphere(impact, 1))
                    {
                        results.Body.Refine(isphere, 0.0001f, true);
                    }
                }
                results.Fraction = 1;
                drag = false;
            }

            // Mouse movement
            if (Input.MouseDown == MouseButtons.Right)
            {
                if (node != null && results.Fraction < 1)
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

            (PhysicsContext as Physics).HandleInput(Input, FrameDelta);
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            if (LibraryTest.Test() == false)
                return;

            using (Demo demo = new SoftDemo())
            {
                demo.Run();
            }
        }
    }
}
