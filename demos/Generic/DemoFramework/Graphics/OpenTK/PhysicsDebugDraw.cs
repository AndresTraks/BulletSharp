using BulletSharp;
using OpenTK.Graphics.OpenGL;

namespace DemoFramework.OpenTK
{
    public class PhysicsDebugDraw : BufferedDebugDraw
    {
        public void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();

            if (lines.Count == 0)
                return;

            Vector3[] positionArray = new Vector3[lines.Count];
            int[] colorArray = new int[lines.Count];
            int i;
            for (i = 0; i < lines.Count; i++)
            {
                positionArray[i] = lines[i].Position;
                colorArray[i] = lines[i].Color;
            }
            lines.Clear();

            GL.EnableClientState(ArrayCap.VertexArray);
            GL.EnableClientState(ArrayCap.ColorArray);

            GL.VertexPointer(3, VertexPointerType.Float, 0, positionArray);
            GL.ColorPointer(3, ColorPointerType.UnsignedByte, sizeof(int), colorArray);
            GL.DrawArrays(PrimitiveType.Lines, 0, positionArray.Length);

            GL.DisableClientState(ArrayCap.ColorArray);
            GL.DisableClientState(ArrayCap.VertexArray);
        }
    }
};
