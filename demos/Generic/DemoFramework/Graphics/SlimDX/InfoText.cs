using System;
using System.Globalization;
using SlimDX.Direct3D9;

namespace DemoFramework.SlimDX
{
    public class InfoText : IDisposable
    {
        Sprite fontSprite;
        Font font;
        int color = System.Drawing.Color.Red.ToArgb();
        float fps = -1;
        string textString = "";
        CultureInfo culture = CultureInfo.InvariantCulture;

        bool _isEnabled = true;
        public bool IsEnabled
        {
            get { return _isEnabled; }
            set { _isEnabled = value; }
        }

        string _text = "";
        public string Text
        {
            get { return _text; }
            set
            {
                _text = value;
                textString = string.Format("FPS: {0}\n{1}", fps.ToString("0.00", culture), value);
            }
        }

        public InfoText(Device device)
        {
            fontSprite = new Sprite(device);
            font = new Font(device, 20,
              0, FontWeight.Normal, 0, false, CharacterSet.Default,
              Precision.Default, FontQuality.ClearTypeNatural, PitchAndFamily.DontCare, "tahoma");
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
            if (_isEnabled == false)
                return;

            fontSprite.Begin(SpriteFlags.AlphaBlend);

            if (fps != framesPerSecond)
            {
                fps = framesPerSecond;
                textString = string.Format("FPS: {0}\n{1}", fps.ToString("0.00", culture), _text);
            }
            font.DrawString(fontSprite, textString, 0, 0, color);

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
