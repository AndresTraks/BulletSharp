using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using BulletSharp;
using SharpDX.DXGI;
using SharpDX.Direct3D10;
using DataStream = global::SharpDX.DataStream;
using Device = SharpDX.Direct3D10.Device;

namespace DemoFramework.SharpDX
{
    [StructLayout(LayoutKind.Sequential)]
    public struct PositionColored
    {
        public static readonly int Stride = Vector3.SizeInBytes + sizeof(int);

        public Vector3 Position;
        public int Color;

        public PositionColored(Vector3 pos, int col)
        {
            Position = pos;
            Color = col;
        }
    }

    public class PhysicsDebugDraw : DebugDraw
    {
        Device device;
        InputAssemblerStage inputAssembler;
        InputLayout inputLayout;
        List<PositionColored> lines = new List<PositionColored>();
        BufferDescription vertexBufferDesc;

        public PhysicsDebugDraw(SharpDXGraphics graphics)
        {
            device = graphics.Device;
            inputAssembler = device.InputAssembler;

            InputElement[] elements = new InputElement[]
            {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("COLOR", 0, Format.R8G8B8A8_UNorm, 12, 0, InputClassification.PerVertexData, 0)
            };
            inputLayout = new InputLayout(device, graphics.GetDebugDrawPass().Description.Signature, elements);
            
            vertexBufferDesc = new BufferDescription()
            {
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.VertexBuffer,
            };
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color fromColor, Color toColor)
        {
            /*
            PositionColored[] vertices = new PositionColored[2];
            vertices[0] = new PositionColored(from, fromColor.ToArgb());
            vertices[1] = new PositionColored(to, toColor.ToArgb());
            device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
            */
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color color)
        {
            int intColor = color.ToArgb();
            lines.Add(new PositionColored(from, intColor));
            lines.Add(new PositionColored(to, intColor));
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Color color)
        {/*
            var p1 = bbMin;
            var p2 = new Vector3(bbMax.X, bbMin.Y, bbMin.Z);
            var p3 = new Vector3(bbMax.X, bbMax.Y, bbMin.Z);
            var p4 = new Vector3(bbMin.X, bbMax.Y, bbMin.Z);
            var p5 = new Vector3(bbMin.X, bbMin.Y, bbMax.Z);
            var p6 = new Vector3(bbMax.X, bbMin.Y, bbMax.Z);
            var p7 = bbMax;
            var p8 = new Vector3(bbMin.X, bbMax.Y, bbMax.Z);

            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(p1, intColor), new PositionColored(p2, intColor),
                new PositionColored(p2, intColor), new PositionColored(p3, intColor),
                new PositionColored(p3, intColor), new PositionColored(p4, intColor),
                new PositionColored(p4, intColor), new PositionColored(p1, intColor),
                
                new PositionColored(p1, intColor), new PositionColored(p5, intColor),
                new PositionColored(p2, intColor), new PositionColored(p6, intColor),
                new PositionColored(p3, intColor), new PositionColored(p7, intColor),
                new PositionColored(p4, intColor), new PositionColored(p8, intColor),
                
                new PositionColored(p5, intColor), new PositionColored(p6, intColor),
                new PositionColored(p6, intColor), new PositionColored(p7, intColor),
                new PositionColored(p7, intColor), new PositionColored(p8, intColor),
                new PositionColored(p8, intColor), new PositionColored(p5, intColor),
            };

            device.DrawUserPrimitives(PrimitiveType.LineList, 12, vertices);*/
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Color color)
        {/*
            var p1 = Vector3.TransformCoordinate(bbMin, trans);
            var p2 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMin.Y, bbMin.Z), trans);
            var p3 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMax.Y, bbMin.Z), trans);
            var p4 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMax.Y, bbMin.Z), trans);
            var p5 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMin.Y, bbMax.Z), trans);
            var p6 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMin.Y, bbMax.Z), trans);
            var p7 = Vector3.TransformCoordinate(bbMax, trans);
            var p8 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMax.Y, bbMax.Z), trans);

            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(p1, intColor), new PositionColored(p2, intColor),
                new PositionColored(p2, intColor), new PositionColored(p3, intColor),
                new PositionColored(p3, intColor), new PositionColored(p4, intColor),
                new PositionColored(p4, intColor), new PositionColored(p1, intColor),
                
                new PositionColored(p1, intColor), new PositionColored(p5, intColor),
                new PositionColored(p2, intColor), new PositionColored(p6, intColor),
                new PositionColored(p3, intColor), new PositionColored(p7, intColor),
                new PositionColored(p4, intColor), new PositionColored(p8, intColor),
                
                new PositionColored(p5, intColor), new PositionColored(p6, intColor),
                new PositionColored(p6, intColor), new PositionColored(p7, intColor),
                new PositionColored(p7, intColor), new PositionColored(p8, intColor),
                new PositionColored(p8, intColor), new PositionColored(p5, intColor),
            };

            device.DrawUserPrimitives(PrimitiveType.LineList, 12, vertices);*/
        }

        public override void DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Color color, float __unnamed004)
        {
            int intColor = color.ToArgb();
            lines.Add(new PositionColored(v0, intColor));
            lines.Add(new PositionColored(v1, intColor));
            lines.Add(new PositionColored(v2, intColor));
            lines.Add(new PositionColored(v0, intColor));
        }

        public override void DrawTransform(Matrix transform, float orthoLen)
        {
            Vector3 start = new Vector3(transform.M41, transform.M42, transform.M43);

            lines.Add(new PositionColored(start, 0xff0000));
            lines.Add(new PositionColored(start + new Vector3(orthoLen, 0, 0), 0xff0000));
            lines.Add(new PositionColored(start, 0x00ff00));
            lines.Add(new PositionColored(start + new Vector3(0, orthoLen, 0), 0x00ff00));
            lines.Add(new PositionColored(start, 0x0000ff));
            lines.Add(new PositionColored(start + new Vector3(0, 0, orthoLen), 0x0000ff));
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color color, bool drawSect)
        {
            DrawArc(center, normal, axis, radiusA, radiusB, minAngle, maxAngle, color, drawSect, 10.0f);
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color color, bool drawSect, float stepDegrees)
        {/*
            Vector3 vx = axis;
            Vector3 vy = Vector3.Cross(normal, axis);
            float step = stepDegrees * ((float)Math.PI / 180.0f);
            int nSteps = (int)((maxAngle - minAngle) / step);
            if (nSteps == 0)
                nSteps = 1;

            Vector3 next = center + radiusA * vx * (float)Math.Cos(minAngle) + radiusB * vy * (float)Math.Sin(minAngle);

            if (drawSect)
                DrawLine(center, next, color);

            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[nSteps + 1];
            vertices[0].Position = next;
            vertices[0].Color = intColor;
            for (int i = 1; i <= nSteps; i++)
            {
                float angle = minAngle + (maxAngle - minAngle) * (float)i / (float)nSteps;
                next = center + radiusA * vx * (float)Math.Cos(angle) + radiusB * vy * (float)Math.Sin(angle);
                vertices[i].Position = next;
                vertices[i].Color = intColor;
            }
            device.DrawUserPrimitives(PrimitiveType.LineStrip, nSteps, vertices);

            if (drawSect)
                DrawLine(center, next, color);*/
        }

        public virtual void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();

            if (lines.Count == 0)
                return;

            inputAssembler.InputLayout = inputLayout;

            vertexBufferDesc.SizeInBytes = PositionColored.Stride * lines.Count;
            Buffer vertexBuffer;
            using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(lines.ToArray());
                vertexBuffer = new Buffer(device, data, vertexBufferDesc);
            }

            inputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, PositionColored.Stride, 0));
            inputAssembler.PrimitiveTopology = global::SharpDX.Direct3D.PrimitiveTopology.LineList;

            device.Draw(lines.Count, 0);

            vertexBuffer.Dispose();
            lines.Clear();
        }
    }
};
