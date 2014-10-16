using System;
using System.Globalization;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using Device = SharpDX.Direct3D10.Device;

namespace DemoFramework.SharpDX
{
    public class InfoText : IDisposable
    {
        Device device;
        Font font;
        Color4 color = new Color4(1, 0, 0, 1);
        Color4 clearColor = new Color4(1, 0, 0, 0);
        float fps = -1;
        string textString = "";
        Rectangle rect = new Rectangle(0, 0, 256, 256);
        CultureInfo culture = CultureInfo.InvariantCulture;
        Texture2D renderTexture;
        RenderTargetView renderTextureView;
        RenderTargetView[] renderViews;
        OutputMergerStage outputMerger;

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

        public ShaderResourceView OverlayBufferRes;
        public float Width {
            get { return rect.Width; }
        }
        public float Height
        {
            get { return rect.Height; }
        }

        public InfoText(Device device)
        {
            this.device = device;
            outputMerger = device.OutputMerger;

            font = new Font(device, 20, 0, FontWeight.Normal, 0, false, FontCharacterSet.Default,
              FontPrecision.Default, FontQuality.ClearTypeNatural, FontPitchAndFamily.DontCare, "tahoma");

            renderTexture = new Texture2D(device, new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.RenderTarget | BindFlags.ShaderResource,
                CpuAccessFlags = CpuAccessFlags.None,
                Format = Format.R8G8B8A8_UNorm,
                Height = rect.Height,
                Width = rect.Width,
                MipLevels = 1,
                OptionFlags = ResourceOptionFlags.None,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default
            });
            renderTextureView = new RenderTargetView(device, renderTexture);
            renderViews = new[] { renderTextureView };

            OverlayBufferRes = new ShaderResourceView(device, renderTexture, new ShaderResourceViewDescription()
            {
                Format = Format.R8G8B8A8_UNorm,
                Dimension = ShaderResourceViewDimension.Texture2D,
                Texture2D = new ShaderResourceViewDescription.Texture2DResource()
                {
                    MipLevels = 1,
                    MostDetailedMip = 0
                }
            });
        }

        public void Dispose()
        {
            if (renderTexture != null)
            {
                renderTexture.Dispose();
                renderTexture = null;
            }

            if (renderTextureView != null)
            {
                renderTextureView.Dispose();
                renderTextureView = null;
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

                outputMerger.SetRenderTargets(1, renderViews, null);
                device.ClearRenderTargetView(renderTextureView, clearColor);
                font.DrawText(null, textString, rect, FontDrawFlags.Left, color);
            }
        }
    }
}
