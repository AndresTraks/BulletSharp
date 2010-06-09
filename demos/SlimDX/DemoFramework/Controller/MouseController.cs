using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.RawInput;

namespace DemoFramework
{
    public class MouseController
    {
        public Vector3 Vector
        {
            get { return vector; }
            set { vector = value; }
        }

        public Vector2 DragPoint
        {
            get;
            private set;
        }

        public float Sensitivity
        {
            get;
            set;
        }

        Vector3 vector;
        double sensitivity = 0.01f;

        Point MouseOrigin;
        double AngleOriginX, AngleOriginY;
        double AngleDeltaX, AngleDeltaY;
        int RightDragX, RightDragY;
        int RightDragDeltaX, RightDragDeltaY;

        public MouseController()
        {
            SetByAngles(0, 0);
        }

        // HorizontalAngle - left-right movement (parallel to XZ-plane)
        // VerticalAngle - up-down movement (angle between Vector and Y-axis)
        public void SetByAngles(double horizontalAngle, double verticalAngle)
        {
            vector.X = (float)(Math.Cos(horizontalAngle) * Math.Cos(verticalAngle));
            vector.Z = (float)(Math.Sin(horizontalAngle) * Math.Cos(verticalAngle));
            vector.Y = (float)Math.Sin(verticalAngle);
        }

        public bool Update(Input input)
        {
            // Don't allow both actions at once
            if ((input.MouseDown & (MouseButtonFlags.LeftDown | MouseButtonFlags.RightDown))
                != (MouseButtonFlags.LeftDown | MouseButtonFlags.RightDown))
            {
                // When mouse button is clicked, store cursor position and angles
                if ((input.MousePressed & MouseButtonFlags.LeftDown) == MouseButtonFlags.LeftDown)
                {
                    MouseOrigin = input.MousePoint;

                    // Get normalized Vector
                    Vector3 Norm = Vector3.Normalize(Vector);

                    // Calculate angles from the vector
                    AngleOriginX = Math.Atan2(Norm.Z, Norm.X);
                    AngleOriginY = Math.Asin(Norm.Y);
                }
                else if ((input.MousePressed & MouseButtonFlags.RightDown) == MouseButtonFlags.RightDown)
                {
                    MouseOrigin = input.MousePoint;
                }
            }

            if ((input.MousePressed & MouseButtonFlags.RightUp) == MouseButtonFlags.RightUp)
            {
                RightDragX += RightDragDeltaX;
                RightDragY += RightDragDeltaY;
            }

            if ((input.MouseDown & MouseButtonFlags.LeftDown) == MouseButtonFlags.LeftDown)
            {
                // Calculate how much to change the angles
                AngleDeltaX = -(input.MousePoint.X - MouseOrigin.X) * sensitivity;
                AngleDeltaY = (input.MousePoint.Y - MouseOrigin.Y) * sensitivity;

                SetByAngles(AngleOriginX + AngleDeltaX, AngleOriginY + AngleDeltaY);
            }
            else if ((input.MouseDown & MouseButtonFlags.RightDown) == MouseButtonFlags.RightDown)
            {
                RightDragDeltaX = (input.MousePoint.X - MouseOrigin.X);
                RightDragDeltaY = (input.MousePoint.Y - MouseOrigin.Y);
                DragPoint = new Vector2(RightDragDeltaX + RightDragX,
                    RightDragDeltaY + RightDragY);
            }
            else
            {
                return false;
            }
            return true;
        }
    }
}
