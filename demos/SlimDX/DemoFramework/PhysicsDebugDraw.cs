using System;
using System.Collections.Generic;
using BulletSharp;
using SlimDX;
using SlimDX.Direct3D9;

namespace DemoFramework
{
    public class PhysicsDebugDraw : DebugDraw
    {
        protected Device device;

        public PhysicsDebugDraw(Device device)
        {
            this.device = device;
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color4 fromColor, Color4 toColor)
        {
            PositionColored[] vertices = new PositionColored[2];
            vertices[0] = new PositionColored(from, fromColor.ToArgb());
            vertices[1] = new PositionColored(to, toColor.ToArgb());
            device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color4 color)
        {
            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[2];
            vertices[0] = new PositionColored(from, intColor);
            vertices[1] = new PositionColored(to, intColor);
            device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Color4 color)
        {
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

            device.DrawUserPrimitives(PrimitiveType.LineList, 12, vertices);
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Color4 color)
        {
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

            device.DrawUserPrimitives(PrimitiveType.LineList, 12, vertices);
        }

        public override void DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Color4 color, float __unnamed004)
        {
            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(v0, intColor),
                new PositionColored(v1, intColor),
                new PositionColored(v2, intColor),
                new PositionColored(v0, intColor),
            };

            device.DrawUserPrimitives(PrimitiveType.LineStrip, 3, vertices);
        }

        public override void DrawTransform(Matrix transform, float orthoLen)
        {
            Vector3 start = new Vector3(transform.M41, transform.M42, transform.M43);

            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(start, 0xff0000), new PositionColored(start + new Vector3(orthoLen,0,0), 0xff0000),
                new PositionColored(start, 0x00ff00), new PositionColored(start + new Vector3(0,orthoLen,0), 0x00ff00),
                new PositionColored(start, 0x0000ff), new PositionColored(start + new Vector3(0,0,orthoLen), 0x0000ff),
            };

            device.DrawUserPrimitives(PrimitiveType.LineList, 3, vertices);
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color4 color, bool drawSect)
        {
            DrawArc(center, normal, axis, radiusA, radiusB, minAngle, maxAngle, color, drawSect, 10.0f);
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color4 color, bool drawSect, float stepDegrees)
        {
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
            vertices[0] = new PositionColored(next, intColor);
            for (int i = 1; i <= nSteps; i++)
            {
                float angle = minAngle + (maxAngle - minAngle) * (float)i / (float)nSteps;
                next = center + radiusA * vx * (float)Math.Cos(angle) + radiusB * vy * (float)Math.Sin(angle);
                vertices[i] = new PositionColored(next, intColor);
            }
            device.DrawUserPrimitives(PrimitiveType.LineStrip, nSteps, vertices);

            if (drawSect)
                DrawLine(center, next, color);
        }

        public virtual void DrawDebugWorld(DynamicsWorld world)
        {
            device.SetRenderState(RenderState.Lighting, false);
            device.SetTransform(TransformState.World, Matrix.Identity);
            device.VertexFormat = PositionColored.FVF;
            world.DebugDrawWorld();
            device.SetRenderState(RenderState.Lighting, true);
        }
    }

    // PhysicsDebugDrawLineGathering is useful for large scenes,
    // because it batches the graphics device calls into a single call.
    public class PhysicsDebugDrawLineGathering : PhysicsDebugDraw
    {
        List<PositionColored> lineBuffer = new List<PositionColored>();

        public PhysicsDebugDrawLineGathering(Device device)
            : base(device)
        {
            this.DebugMode = DebugDrawModes.DrawWireframe;
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color4 color)
        {
            int intColor = color.ToArgb();
            lineBuffer.Add(new PositionColored(from, intColor));
            lineBuffer.Add(new PositionColored(to, intColor));
        }

        public override void DrawTransform(Matrix transform, float orthoLen)
        {
            Vector3 start = new Vector3(transform.M41, transform.M42, transform.M43);

            lineBuffer.Add(new PositionColored(start, 0xff0000));
            lineBuffer.Add(new PositionColored(start + new Vector3(orthoLen, 0, 0), 0xff0000));
            lineBuffer.Add(new PositionColored(start, 0x00ff00));
            lineBuffer.Add(new PositionColored(start + new Vector3(0, orthoLen, 0), 0x00ff00));
            lineBuffer.Add(new PositionColored(start, 0x0000ff));
            lineBuffer.Add(new PositionColored(start + new Vector3(0, 0, orthoLen), 0x0000ff));
        }

        public override void DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Color4 color, float __unnamed004)
        {
            int intColor = color.ToArgb();
            lineBuffer.Add(new PositionColored(v0, intColor));
            lineBuffer.Add(new PositionColored(v1, intColor));
            lineBuffer.Add(new PositionColored(v2, intColor));
            lineBuffer.Add(new PositionColored(v0, intColor));
        }

        public override void DrawDebugWorld(DynamicsWorld world)
        {
            int lighting = device.GetRenderState(RenderState.Lighting);
            device.SetRenderState(RenderState.Lighting, false);
            device.SetTransform(TransformState.World, Matrix.Identity);
            device.VertexFormat = PositionColored.FVF;

            world.DebugDrawWorld();
            DrawBuffer();

            device.SetRenderState(RenderState.Lighting, lighting);
        }

        public void DrawBuffer()
        {
            if (lineBuffer.Count == 0)
                return;

            PositionColored[] lineArray = new PositionColored[lineBuffer.Count];
            lineBuffer.CopyTo(lineArray);
            device.DrawUserPrimitives(PrimitiveType.LineList, lineBuffer.Count / 2, lineArray);
            lineBuffer.Clear();
        }
    };
};
