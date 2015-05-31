using System;
using System.Globalization;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DemoFramework.MonoGame
{
    public class InfoText : IDisposable
    {
        GraphicsDevice device;
        SpriteBatch spriteBatch;
        SpriteFont font;
        Color color = Color.Red;
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

        public InfoText(GraphicsDevice device)
        {
            this.device = device;
            //font = Content.Load<SpriteFont>("myFont");
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        void Dispose(bool isDisposing)
        {
            if (isDisposing && spriteBatch != null)
            {
                spriteBatch.Dispose();
            }
        }

        public void OnRender(float framesPerSecond)
        {
            if (_isEnabled == false)
                return;

            if (spriteBatch == null)
                return;

            spriteBatch.Begin();

            if (fps != framesPerSecond)
            {
                fps = framesPerSecond;
                textString = string.Format("FPS: {0}\n{1}", fps.ToString("0.00", culture), _text);
            }
            spriteBatch.DrawString(font, textString, Vector2.Zero, color);

            spriteBatch.End();
        }

        public void OnResetDevice()
        {
        }

        public void OnLostDevice()
        {
            spriteBatch = new SpriteBatch(device);
        }

        public void SetDevice(GraphicsDevice device)
        {
            this.device = device;
            //spriteBatch = new SpriteBatch(device);
        }
    }
}
