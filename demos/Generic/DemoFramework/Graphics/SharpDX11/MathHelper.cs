using SharpDX;

namespace DemoFramework.SharpDX11
{
    static class MathHelper
    {
        public static Matrix Convert(ref BulletSharp.Matrix m)
        {
            return new Matrix(
                m.M11, m.M12, m.M13, m.M14,
                m.M21, m.M22, m.M23, m.M24,
                m.M31, m.M32, m.M33, m.M34,
                m.M41, m.M42, m.M43, m.M44);
        }

        public static BulletSharp.Matrix Convert(ref Matrix m)
        {
            return new BulletSharp.Matrix
            {
                M11 = m.M11,
                M12 = m.M12,
                M13 = m.M13,
                M14 = m.M14,
                M21 = m.M21,
                M22 = m.M22,
                M23 = m.M23,
                M24 = m.M24,
                M31 = m.M31,
                M32 = m.M32,
                M33 = m.M33,
                M34 = m.M34,
                M41 = m.M41,
                M42 = m.M42,
                M43 = m.M43,
                M44 = m.M44
            };
        }

        public static Vector3 Convert(BulletSharp.Vector3 v)
        {
            return new Vector3(v.X, v.Y, v.Z);
        }
    }
}
