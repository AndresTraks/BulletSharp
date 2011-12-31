using System;
using System.Globalization;
using SharpDX;
using SharpDX.Direct3D10;

namespace DemoFramework
{
    public class InfoText : IDisposable
    {
        Font font;
        Color4 color = new Color4(1, 0, 0, 1);
        float fps = -1;
        string textString = "";
        Rectangle rect = new Rectangle(0, 0, 210, 200);
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
            font = new Font(device, 20, 0, FontWeight.Normal, 0, false, FontCharacterSet.Default,
              FontPrecision.Default, FontQuality.ClearTypeNatural, FontPitchAndFamily.DontCare, "tahoma");
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
                font.Dispose();
            }
        }

        public void OnRender(float framesPerSecond)
        {
            if (_isEnabled == false)
                return;

            if (fps != framesPerSecond)
            {
                fps = framesPerSecond;
                textString = string.Format("FPS: {0}\n{1}", fps.ToString("0.00", culture), _text);
            }
            font.DrawText(null, textString, rect, FontDrawFlags.Left, color);
        }
    }
}
