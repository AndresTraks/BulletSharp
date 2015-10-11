using BulletSharp;

namespace BulletSharpTest
{
    class DebugDrawTest : IDebugDraw
    {
        DebugDrawModes _debugMode = DebugDrawModes.DrawWireframe | DebugDrawModes.DrawAabb;

        public DebugDrawModes DebugMode
        {
            get
            {
                return _debugMode;
            }
            set
            {
                throw new System.NotImplementedException();
            }
        }

        public void Draw3dText(ref Vector3 location, string textString)
        {
            throw new System.NotImplementedException();
        }

        public void DrawAabb(ref Vector3 from, ref Vector3 to, System.Drawing.Color color)
        {
            //throw new System.NotImplementedException();
        }

        public void DrawArc(ref Vector3 center, ref Vector3 normal, ref Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, System.Drawing.Color color, bool drawSect, float stepDegrees)
        {
            throw new System.NotImplementedException();
        }

        public void DrawArc(ref Vector3 center, ref Vector3 normal, ref Vector3 axis, double radiusA, double radiusB, double minAngle, double maxAngle, System.Drawing.Color color, bool drawSect, double stepDegrees)
        {
            throw new System.NotImplementedException();
        }

        public void DrawArc(ref Vector3 center, ref Vector3 normal, ref Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, System.Drawing.Color color, bool drawSect)
        {
            throw new System.NotImplementedException();
        }

        public void DrawArc(ref Vector3 center, ref Vector3 normal, ref Vector3 axis, double radiusA, double radiusB, double minAngle, double maxAngle, System.Drawing.Color color, bool drawSect)
        {
            throw new System.NotImplementedException();
        }

        public void DrawBox(ref Vector3 bbMin, ref Vector3 bbMax, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawBox(ref Vector3 bbMin, ref Vector3 bbMax, ref Matrix trans, System.Drawing.Color color)
        {
            //throw new System.NotImplementedException();
        }

        public void DrawCapsule(float radius, float halfHeight, int upAxis, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawCapsule(double radius, double halfHeight, int upAxis, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawCone(float radius, float height, int upAxis, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawCone(double radius, double height, int upAxis, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawContactPoint(ref Vector3 PointOnB, ref Vector3 normalOnB, float distance, int lifeTime, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawContactPoint(ref Vector3 PointOnB, ref Vector3 normalOnB, double distance, int lifeTime, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawCylinder(float radius, float halfHeight, int upAxis, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawCylinder(double radius, double halfHeight, int upAxis, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawLine(ref Vector3 from, ref Vector3 to, System.Drawing.Color fromColor, System.Drawing.Color toColor)
        {
            throw new System.NotImplementedException();
        }

        public void DrawLine(ref Vector3 from, ref Vector3 to, System.Drawing.Color color)
        {
            //throw new System.NotImplementedException();
        }

        public void DrawPlane(ref Vector3 planeNormal, float planeConst, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawPlane(ref Vector3 planeNormal, double planeConst, ref Matrix transform, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSphere(ref Vector3 p, float radius, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSphere(ref Vector3 p, double radius, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSphere(float radius, ref Matrix transform, System.Drawing.Color color)
        {
            //throw new System.NotImplementedException();
        }

        public void DrawSphere(double radius, ref Matrix transform, System.Drawing.Color color)
        {
            //throw new System.NotImplementedException();
        }

        public void DrawSpherePatch(ref Vector3 center, ref Vector3 up, ref Vector3 axis, float radius, float minTh, float maxTh, float minPs, float maxPs, System.Drawing.Color color, float stepDegrees, bool drawCenter)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSpherePatch(ref Vector3 center, ref Vector3 up, ref Vector3 axis, double radius, double minTh, double maxTh, double minPs, double maxPs, System.Drawing.Color color, double stepDegrees, bool drawCenter)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSpherePatch(ref Vector3 center, ref Vector3 up, ref Vector3 axis, float radius, float minTh, float maxTh, float minPs, float maxPs, System.Drawing.Color color, float stepDegrees)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSpherePatch(ref Vector3 center, ref Vector3 up, ref Vector3 axis, double radius, double minTh, double maxTh, double minPs, double maxPs, System.Drawing.Color color, double stepDegrees)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSpherePatch(ref Vector3 center, ref Vector3 up, ref Vector3 axis, float radius, float minTh, float maxTh, float minPs, float maxPs, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawSpherePatch(ref Vector3 center, ref Vector3 up, ref Vector3 axis, double radius, double minTh, double maxTh, double minPs, double maxPs, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public void DrawTransform(ref Matrix transform, float orthoLen)
        {
            throw new System.NotImplementedException();
        }

        public void DrawTransform(ref Matrix transform, double orthoLen)
        {
            throw new System.NotImplementedException();
        }

        public void DrawTriangle(ref Vector3 v0, ref Vector3 v1, ref Vector3 v2, ref Vector3 __unnamed3, ref Vector3 __unnamed4, ref Vector3 __unnamed5, System.Drawing.Color color, float alpha)
        {
            throw new System.NotImplementedException();
        }

        public void DrawTriangle(ref Vector3 v0, ref Vector3 v1, ref Vector3 v2, ref Vector3 __unnamed3, ref Vector3 __unnamed4, ref Vector3 __unnamed5, System.Drawing.Color color, double alpha)
        {
            throw new System.NotImplementedException();
        }

        public void DrawTriangle(ref Vector3 v0, ref Vector3 v1, ref Vector3 v2, System.Drawing.Color color, float alpha)
        {
            throw new System.NotImplementedException();
        }

        public void DrawTriangle(ref Vector3 v0, ref Vector3 v1, ref Vector3 v2, System.Drawing.Color color, double alpha)
        {
            throw new System.NotImplementedException();
        }

        public void FlushLines()
        {
            //throw new System.NotImplementedException();
        }

        public void ReportErrorWarning(string warningString)
        {
            throw new System.NotImplementedException();
        }
    }
}
