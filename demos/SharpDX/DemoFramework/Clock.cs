using System.Diagnostics;

namespace DemoFramework
{
    public class Clock
    {
        Stopwatch physicsTimer = new Stopwatch();
        Stopwatch renderTimer = new Stopwatch();
        Stopwatch frameTimer = new Stopwatch();

        long _frameCount;
        public long FrameCount { get { return _frameCount; } }

        public float PhysicsAverage
        {
            get
            {
                if (_frameCount == 0) return 0;
                return (((float)physicsTimer.ElapsedTicks / Stopwatch.Frequency) / _frameCount) * 1000.0f;
            }
        }

        public float RenderAverage
        {
            get
            {
                if (_frameCount == 0) return 0;
                return (((float)renderTimer.ElapsedTicks / Stopwatch.Frequency) / _frameCount) * 1000.0f;
            }
        }

        public void StartPhysics()
        {
            physicsTimer.Start();
        }

        public void StopPhysics()
        {
            physicsTimer.Stop();
        }

        public void StartRender()
        {
            renderTimer.Start();
        }

        public void StopRender()
        {
            renderTimer.Stop();
        }

        public float GetFrameDelta()
        {
            _frameCount++;

            float delta = (float)frameTimer.ElapsedTicks / Stopwatch.Frequency;
            frameTimer.Restart();
            return delta;
        }

        public void Reset()
        {
            _frameCount = 0;
            physicsTimer.Reset();
            renderTimer.Reset();
        }
    }
}
