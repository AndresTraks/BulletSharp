using System;
using System.Drawing;
using System.Globalization;
using SlimDX.Direct3D9;

namespace DemoFramework
{
    public class FpsDisplay : IDisposable
    {
        Sprite fontSprite;
        SlimDX.Direct3D9.Font font;
        int color = Color.Red.ToArgb();
        float fps = -1;
        string fpsString = "";

        public bool IsEnabled { get; set; }
        public string Text { get; set; }

        public FpsDisplay(Device device)
        {
            fontSprite = new Sprite(device);
            font = new SlimDX.Direct3D9.Font(device, 20,
              0, FontWeight.Normal, 0, false, CharacterSet.Default,
              Precision.Default, FontQuality.ClearTypeNatural, PitchAndFamily.DontCare, "tahoma");
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
                fontSprite.Dispose();
                font.Dispose();
            }
        }

        public void OnRender(float framesPerSecond)
        {
            if (IsEnabled == false)
                return;

            fontSprite.Begin(SlimDX.Direct3D9.SpriteFlags.AlphaBlend);

            if (fps != framesPerSecond)
            {
                fps = framesPerSecond;
                fpsString = string.Format("FPS: {0}", fps.ToString("0.00", CultureInfo.InvariantCulture));
            }
            font.DrawString(fontSprite, fpsString, 0, 0, color);

            if (Text.Length > 0)
                font.DrawString(fontSprite, Text, 0, 20, color);

            fontSprite.End();
        }

        public void OnResetDevice()
        {
            fontSprite.OnResetDevice();
            font.OnResetDevice();
        }

        public void OnLostDevice()
        {
            fontSprite.OnLostDevice();
            font.OnLostDevice();
        }
    }
}
