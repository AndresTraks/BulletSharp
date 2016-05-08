using Microsoft.Xna.Framework;
using System;

namespace DemoFramework
{
    public class MouseController
    {
        private Input _input;
        private Point _mousePoint;
        private double _angleOriginX, _angleOriginY;

        public Vector3 Vector { get; set; }
        public float Sensitivity { get; set; }

        public MouseController(Input input)
        {
            _input = input;
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
            if (!_input.LeftPressed) return false;

            // When mouse button is clicked, store cursor position and angles
            if (_input.LeftClick)
            {
                _mousePoint = _input.MousePoint;

                // Calculate angles from the vector
                _angleOriginX = Math.Atan2(Vector.Z, Vector.X);
                _angleOriginY = Math.Asin(Vector.Y);

                SetByAngles(_angleOriginX, _angleOriginY);
            }
            else
            {
                // Calculate how much to change the angles
                double angleDeltaX = (_input.MousePoint.X - _mousePoint.X) * Sensitivity;
                double angleDeltaY = (_input.MousePoint.Y - _mousePoint.Y) * Sensitivity;

                SetByAngles(_angleOriginX + angleDeltaX, _angleOriginY + angleDeltaY);
            }

            return true;
        }
    }
}
