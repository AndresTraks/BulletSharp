using System;
using System.Drawing;
using SlimDX;
using SlimDX.RawInput;

namespace DemoFramework
{
    public class MouseController
    {
        public Vector3 Vector { get; set; }
        public float Sensitivity { get; set; }

        Input input;
        Point mouseOrigin;
        double angleOriginX, angleOriginY;

        public MouseController(Input input)
        {
            this.input = input;
            Sensitivity = 0.005f;
            SetByAngles(0, 0);
        }

        // HorizontalAngle - left-right movement (parallel to XZ-plane)
        // VerticalAngle - up-down movement (angle between Vector and Y-axis)
        public void SetByAngles(double horizontalAngle, double verticalAngle)
        {
            Vector = new Vector3(
                (float)(Math.Cos(horizontalAngle) * Math.Cos(verticalAngle)),
                (float)Math.Sin(verticalAngle),
                (float)(Math.Sin(horizontalAngle) * Math.Cos(verticalAngle)));
        }

        public bool Update()
        {
            if ((input.MouseDown & MouseButtonFlags.LeftDown) != MouseButtonFlags.LeftDown)
                return false;

            // When mouse button is clicked, store cursor position and angles
            if ((input.MousePressed & MouseButtonFlags.LeftDown) == MouseButtonFlags.LeftDown)
            {
                mouseOrigin = input.MousePoint;

                // Get normalized Vector
                Vector3 norm = Vector3.Normalize(Vector);

                // Calculate angles from the vector
                angleOriginX = Math.Atan2(norm.Z, norm.X);
                angleOriginY = Math.Asin(norm.Y);
            }

            // Calculate how much to change the angles
            double angleDeltaX = -(input.MousePoint.X - mouseOrigin.X) * Sensitivity;
            double angleDeltaY = (input.MousePoint.Y - mouseOrigin.Y) * Sensitivity;

            SetByAngles(angleOriginX + angleDeltaX, angleOriginY + angleDeltaY);

            return true;
        }
    }
}
