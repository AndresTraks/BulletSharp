using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using BulletSharp;

namespace DemoFramework
{
    public abstract class BufferedDebugDraw : DebugDraw
    {
        protected List<PositionColored> lines = new List<PositionColored>();

        public virtual int colorToInt(ref Color c)
        {
            return c.R + (c.G << 8) + (c.B << 16);
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color fromColor, Color toColor)
        {
            lines.Add(new PositionColored(ref from, colorToInt(ref fromColor)));
            lines.Add(new PositionColored(ref to, colorToInt(ref toColor)));
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color color)
        {
            int intColor = colorToInt(ref color);
            lines.Add(new PositionColored(ref from, intColor));
            lines.Add(new PositionColored(ref to, intColor));
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Color color)
        {
            var p1 = bbMin;
            var p2 = new Vector3(bbMax.X, bbMin.Y, bbMin.Z);
            var p3 = new Vector3(bbMax.X, bbMax.Y, bbMin.Z);
            var p4 = new Vector3(bbMin.X, bbMax.Y, bbMin.Z);
            var p5 = new Vector3(bbMin.X, bbMin.Y, bbMax.Z);
            var p6 = new Vector3(bbMax.X, bbMin.Y, bbMax.Z);
            var p7 = bbMax;
            var p8 = new Vector3(bbMin.X, bbMax.Y, bbMax.Z);

            int intColor = colorToInt(ref color);
            lines.Add(new PositionColored(ref p1, intColor)); lines.Add(new PositionColored(ref p2, intColor));
            lines.Add(new PositionColored(ref p2, intColor)); lines.Add(new PositionColored(ref p3, intColor));
            lines.Add(new PositionColored(ref p3, intColor)); lines.Add(new PositionColored(ref p4, intColor));
            lines.Add(new PositionColored(ref p4, intColor)); lines.Add(new PositionColored(ref p1, intColor));

            lines.Add(new PositionColored(ref p1, intColor)); lines.Add(new PositionColored(ref p5, intColor));
            lines.Add(new PositionColored(ref p2, intColor)); lines.Add(new PositionColored(ref p6, intColor));
            lines.Add(new PositionColored(ref p3, intColor)); lines.Add(new PositionColored(ref p7, intColor));
            lines.Add(new PositionColored(ref p4, intColor)); lines.Add(new PositionColored(ref p8, intColor));

            lines.Add(new PositionColored(ref p5, intColor)); lines.Add(new PositionColored(ref p6, intColor));
            lines.Add(new PositionColored(ref p6, intColor)); lines.Add(new PositionColored(ref p7, intColor));
            lines.Add(new PositionColored(ref p7, intColor)); lines.Add(new PositionColored(ref p8, intColor));
            lines.Add(new PositionColored(ref p8, intColor)); lines.Add(new PositionColored(ref p5, intColor));
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Color color)
        {
            var p1 = Vector3.TransformCoordinate(bbMin, trans);
            var p2 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMin.Y, bbMin.Z), trans);
            var p3 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMax.Y, bbMin.Z), trans);
            var p4 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMax.Y, bbMin.Z), trans);
            var p5 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMin.Y, bbMax.Z), trans);
            var p6 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMin.Y, bbMax.Z), trans);
            var p7 = Vector3.TransformCoordinate(bbMax, trans);
            var p8 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMax.Y, bbMax.Z), trans);

            int intColor = colorToInt(ref color);
            lines.Add(new PositionColored(ref p1, intColor)); lines.Add(new PositionColored(ref p2, intColor));
            lines.Add(new PositionColored(ref p2, intColor)); lines.Add(new PositionColored(ref p3, intColor));
            lines.Add(new PositionColored(ref p3, intColor)); lines.Add(new PositionColored(ref p4, intColor));
            lines.Add(new PositionColored(ref p4, intColor)); lines.Add(new PositionColored(ref p1, intColor));

            lines.Add(new PositionColored(ref p1, intColor)); lines.Add(new PositionColored(ref p5, intColor));
            lines.Add(new PositionColored(ref p2, intColor)); lines.Add(new PositionColored(ref p6, intColor));
            lines.Add(new PositionColored(ref p3, intColor)); lines.Add(new PositionColored(ref p7, intColor));
            lines.Add(new PositionColored(ref p4, intColor)); lines.Add(new PositionColored(ref p8, intColor));

            lines.Add(new PositionColored(ref p5, intColor)); lines.Add(new PositionColored(ref p6, intColor));
            lines.Add(new PositionColored(ref p6, intColor)); lines.Add(new PositionColored(ref p7, intColor));
            lines.Add(new PositionColored(ref p7, intColor)); lines.Add(new PositionColored(ref p8, intColor));
            lines.Add(new PositionColored(ref p8, intColor)); lines.Add(new PositionColored(ref p5, intColor));
        }

        public override void DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Color color, float __unnamed004)
        {
            int intColor = colorToInt(ref color);
            lines.Add(new PositionColored(ref v0, intColor));
            lines.Add(new PositionColored(ref v1, intColor));
            lines.Add(new PositionColored(ref v2, intColor));
            lines.Add(new PositionColored(ref v0, intColor));
        }

        public override void DrawTransform(Matrix transform, float orthoLen)
        {
            Vector3 start = new Vector3(transform.M41, transform.M42, transform.M43);

            lines.Add(new PositionColored(ref start, 0xff0000));
            lines.Add(new PositionColored(start + new Vector3(orthoLen, 0, 0), 0xff0000));
            lines.Add(new PositionColored(ref start, 0x00ff00));
            lines.Add(new PositionColored(start + new Vector3(0, orthoLen, 0), 0x00ff00));
            lines.Add(new PositionColored(ref start, 0x0000ff));
            lines.Add(new PositionColored(start + new Vector3(0, 0, orthoLen), 0x0000ff));
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color color, bool drawSect)
        {
            DrawArc(center, normal, axis, radiusA, radiusB, minAngle, maxAngle, color, drawSect, 10.0f);
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color color, bool drawSect, float stepDegrees)
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

            int intColor = colorToInt(ref color);
            PositionColored last = new PositionColored(ref next, intColor);
            for (int i = 1; i <= nSteps; i++)
            {
                lines.Add(last);
                float angle = minAngle + (maxAngle - minAngle) * (float)i / (float)nSteps;
                next = center + radiusA * vx * (float)Math.Cos(angle) + radiusB * vy * (float)Math.Sin(angle);
                last = new PositionColored(ref next, intColor);
                lines.Add(last);
            }

            if (drawSect)
                DrawLine(center, next, color);
        }

        public abstract void DrawDebugWorld(DynamicsWorld world);
    }
};
