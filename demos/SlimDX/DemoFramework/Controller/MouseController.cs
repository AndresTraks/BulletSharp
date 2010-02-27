using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.DirectInput;

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

        bool IsLeftDragging = false, IsRightDragging = false;
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
            if (input.MouseDown != MouseButtons.None)
            {
                // Don't allow both actions at once
                if (IsLeftDragging == false && IsRightDragging == false)
                {
                    // When mouse button is clicked, store cursor position and angles
                    if ((input.MouseDown & MouseButtons.Left) == MouseButtons.Left)
                    {
                        IsLeftDragging = true;
                        MouseOrigin = input.MousePoint;

                        // Get normalized Vector
                        Vector3 Norm = Vector3.Normalize(Vector);

                        // Calculate angles from the vector
                        AngleOriginX = Math.Atan2(Norm.Z, Norm.X);
                        AngleOriginY = Math.Asin(Norm.Y);
                    }
                    else if ((input.MouseDown & MouseButtons.Right) == MouseButtons.Right)
                    {
                        IsRightDragging = true;
                        MouseOrigin = input.MousePoint;
                    }
                }
            }

            if (IsLeftDragging == true)
            {
                // Calculate how much to change the angles
                AngleDeltaX = -(input.MousePoint.X - MouseOrigin.X) * sensitivity;
                AngleDeltaY = (input.MousePoint.Y - MouseOrigin.Y) * sensitivity;

                if ((input.MouseUp & MouseButtons.Left) == MouseButtons.Left)
                {
                    // Mouse button released
                    IsLeftDragging = false;
                }
                else
                {
                    // Button still pressed, update Vector
                    SetByAngles(AngleOriginX + AngleDeltaX, AngleOriginY + AngleDeltaY);
                }
            }
            else if (IsRightDragging == true)
            {
                if ((input.MouseUp & MouseButtons.Right) == MouseButtons.Right)
                {
                    IsRightDragging = false;
                    RightDragX += RightDragDeltaX;
                    RightDragY += RightDragDeltaY;
                }
                else
                {
                    RightDragDeltaX = (input.MousePoint.X - MouseOrigin.X);
                    RightDragDeltaY = (input.MousePoint.Y - MouseOrigin.Y);
                    DragPoint = new Vector2(RightDragDeltaX + RightDragX,
                        RightDragDeltaY + RightDragY);
                }
            }
            else
            {
                return false;
            }
            return true;
        }
    }
}
