using BulletSharp;

namespace BulletSharpTest
{
    class DebugDrawTest2 : DebugDraw
    {
        DebugDrawModes _debugMode;

        public override DebugDrawModes DebugMode
        {
            get
            {
                return _debugMode;
            }
            set
            {
                _debugMode = value;
            }
        }

        public override void Draw3dText(ref Vector3 location, string textString)
        {
            throw new System.NotImplementedException();
        }
#if BT_USE_DOUBLE_PRECISION
        public override void DrawContactPoint(ref Vector3 pointOnB, ref Vector3 normalOnB, double distance, int lifeTime, System.Drawing.Color color)
#else
        public override void DrawContactPoint(ref Vector3 pointOnB, ref Vector3 normalOnB, float distance, int lifeTime, System.Drawing.Color color)
#endif
        {
            throw new System.NotImplementedException();
        }

        public override void DrawLine(ref Vector3 from, ref Vector3 to, System.Drawing.Color color)
        {
            throw new System.NotImplementedException();
        }

        public override void ReportErrorWarning(string warningString)
        {
            throw new System.NotImplementedException();
        }
    }
}