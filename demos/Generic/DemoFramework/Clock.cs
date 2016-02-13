using System.Diagnostics;

namespace DemoFramework
{
    public class Clock
    {
        Stopwatch _physicsTimer = new Stopwatch();
        Stopwatch _renderTimer = new Stopwatch();
        Stopwatch _frameTimer = new Stopwatch();

        public long FrameCount { get; private set; }

        public float PhysicsAverage
        {
            get
            {
                if (FrameCount == 0) return 0;
                return (((float)_physicsTimer.ElapsedTicks / Stopwatch.Frequency) / FrameCount) * 1000.0f;
            }
        }

        public float RenderAverage
        {
            get
            {
                if (FrameCount == 0) return 0;
                return (((float)_renderTimer.ElapsedTicks / Stopwatch.Frequency) / FrameCount) * 1000.0f;
            }
        }

        public void StartPhysics()
        {
            _physicsTimer.Start();
        }

        public void StopPhysics()
        {
            _physicsTimer.Stop();
        }

        public void StartRender()
        {
            _renderTimer.Start();
        }

        public void StopRender()
        {
            _renderTimer.Stop();
        }

        public float GetFrameDelta()
        {
            FrameCount++;

            float delta = (float)_frameTimer.ElapsedTicks / Stopwatch.Frequency;
            _frameTimer.Restart();
            return delta;
        }

        public void Reset()
        {
            FrameCount = 0;
            _physicsTimer.Reset();
            _renderTimer.Reset();
        }
    }
}
