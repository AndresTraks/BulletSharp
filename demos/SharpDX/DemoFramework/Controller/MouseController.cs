using System;
using System.Drawing;
using System.Windows.Forms;
using SharpDX;
using SharpDX.Windows;

namespace DemoFramework
{
    public class MouseController
    {
        public Vector3 Vector { get; set; }
        public Vector2 DragPoint { get; private set; }
        public float Sensitivity { get; set; }
        public Input Input { get; set; }

        Point mouseOrigin;
        double angleOriginX, angleOriginY;
        double angleDeltaX, angleDeltaY;
        int rightDragX, rightDragY;
        int rightDragDeltaX, rightDragDeltaY;

        public MouseController(Input input)
        {
            Input = input;
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
            if ((Input.MouseDown & MouseButtons.Left) == MouseButtons.Left)
            {
                // When mouse button is clicked, store cursor position and angles
                if ((Input.MousePressed & MouseButtons.Left) == MouseButtons.Left)
                {
                    mouseOrigin = Input.MousePoint;

                    // Get normalized Vector
                    Vector3 norm = Vector3.Normalize(Vector);

                    // Calculate angles from the vector
                    angleOriginX = Math.Atan2(norm.Z, norm.X);
                    angleOriginY = Math.Asin(norm.Y);
                }

                // Calculate how much to change the angles
                angleDeltaX = -(Input.MousePoint.X - mouseOrigin.X) * Sensitivity;
                angleDeltaY = (Input.MousePoint.Y - mouseOrigin.Y) * Sensitivity;

                SetByAngles(angleOriginX + angleDeltaX, angleOriginY + angleDeltaY);

                return true;
            }

            if ((Input.MouseDown & MouseButtons.Right) == MouseButtons.Right)
            {
                if ((Input.MousePressed & MouseButtons.Right) == MouseButtons.Right)
                    mouseOrigin = Input.MousePoint;

                if ((Input.MouseDown & MouseButtons.Right) == MouseButtons.Right)
                {
                    rightDragDeltaX = Input.MousePoint.X - mouseOrigin.X;
                    rightDragDeltaY = Input.MousePoint.Y - mouseOrigin.Y;
                    DragPoint = new Vector2(rightDragDeltaX + rightDragX,
                        rightDragDeltaY + rightDragY);

                    return true;
                }
            }
            else if ((Input.MousePressed & MouseButtons.Right) == MouseButtons.Right)
            {
                rightDragX += rightDragDeltaX;
                rightDragY += rightDragDeltaY;
            }

            return false;
        }
    }
}
