using System;
using System.Globalization;
using SharpDX;
using SharpDX.Direct3D10;

namespace DemoFramework
{
    public class InfoText : IDisposable
    {
        Font font;
        Color4 color = new Color4(1, 1, 0, 0);
        float fps = -1;
        string fpsString = "";
        Rectangle topRect = new Rectangle(0, 0, 210, 20);
        Rectangle bottomRect = new Rectangle(0, 20, 210, 200);

        public bool IsEnabled { get; set; }
        public string Text { get; set; }

        public InfoText(Device device)
        {
            font = new Font(device, 20, 0, FontWeight.Normal, 0, false, FontCharacterSet.Default,
              FontPrecision.Default, FontQuality.ClearTypeNatural, FontPitchAndFamily.DontCare, "tahoma");
            IsEnabled = true;
            Text = "";
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        void Dispose(bool isDisposing)
        {
            if (isDisposing)
            {
                font.Release();
            }
        }

        public void OnRender(float framesPerSecond)
        {
            if (IsEnabled == false)
                return;

            if (fps != framesPerSecond)
            {
                fps = framesPerSecond;
                fpsString = string.Format("FPS: {0}", fps.ToString("0.00", CultureInfo.InvariantCulture));
                //font.PreloadText(fpsString);
            }
            font.DrawText(null, fpsString, topRect, FontDrawFlags.Left, color);

            if (Text.Length > 0)
                font.DrawText(null, Text, bottomRect, FontDrawFlags.Left, color);
        }
    }
}
