using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.Drawing;
using System.Globalization;

namespace DemoFramework
{
    public class FpsDisplay : IDisposable
    {
        Sprite fontSprite;
        SlimDX.Direct3D9.Font font;

        public bool IsEnabled
        {
            get;
            set;
        }

        public string Text
        {
            get;
            set;
        }

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

        public void OnRender(float frameDelta)
        {
            if (IsEnabled == false)
                return;

            fontSprite.Begin(SlimDX.Direct3D9.SpriteFlags.AlphaBlend);

            fontSprite.Transform = Matrix.Translation(0, 0, 0.5f);
            font.DrawString(fontSprite, "FPS: " + frameDelta.ToString("0.00", CultureInfo.InvariantCulture), 0, 0, Color.Red.ToArgb());

            if (Text.Length > 0)
                font.DrawString(fontSprite, Text, 0, 20, Color.Red.ToArgb());

            fontSprite.End();
        }

        public void OnResourceLoad()
        {
            fontSprite.OnResetDevice();
            font.OnResetDevice();
        }

        public void OnResourceUnload()
        {
            fontSprite.OnLostDevice();
            font.OnLostDevice();
        }
    }
}
