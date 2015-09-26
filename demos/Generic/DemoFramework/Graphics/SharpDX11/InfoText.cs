using System;
using System.Globalization;
using SharpDX;
using SharpDX.Direct2D1;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DirectWrite;
using SharpDX.DXGI;

namespace DemoFramework.SharpDX11
{
    public class InfoText : IDisposable
    {
        Color4 color = new Color4(1, 1, 1, 1);
        Color4 clearColor;
        float fps = -1;
        string textString = "";
        RectangleF rect;
        CultureInfo culture = CultureInfo.InvariantCulture;
        Guid pixelFormat = SharpDX.WIC.PixelFormat.Format32bppPRGBA;

        TextFormat _textFormat;
        DeviceContext _immediateContext;
        WicRenderTarget _wicRenderTarget;
        SharpDX.WIC.Bitmap _wicBitmap;
        SolidColorBrush _sceneColorBrush;
        Texture2D _renderTexture;
        public ShaderResourceView OverlayBufferRes;

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

        const int _width = 256;
        public float Width
        {
            get { return _width; }
        }
        const int _height = 256;
        public float Height
        {
            get { return _height; }
        }

        public InfoText(SharpDX.Direct3D11.Device device)
        {
            _immediateContext = device.ImmediateContext;
            rect.Size = new Size2F(Width, Height);

            var factoryWic = new SharpDX.WIC.ImagingFactory();
            _wicBitmap = new SharpDX.WIC.Bitmap(factoryWic, _width, _height, pixelFormat, SharpDX.WIC.BitmapCreateCacheOption.CacheOnLoad);
            var renderTargetProperties = new RenderTargetProperties(RenderTargetType.Default,
                new SharpDX.Direct2D1.PixelFormat(SharpDX.DXGI.Format.R8G8B8A8_UNorm,
                    SharpDX.Direct2D1.AlphaMode.Premultiplied), 0, 0, RenderTargetUsage.None,
                    SharpDX.Direct2D1.FeatureLevel.Level_DEFAULT);
            factoryWic.Dispose();

            var factory2D = new SharpDX.Direct2D1.Factory();
            _wicRenderTarget = new WicRenderTarget(factory2D, _wicBitmap, renderTargetProperties);
            _wicRenderTarget.TextAntialiasMode = TextAntialiasMode.Default;
            factory2D.Dispose();

            var factoryDWrite = new SharpDX.DirectWrite.Factory(SharpDX.DirectWrite.FactoryType.Shared);
            _textFormat = new TextFormat(factoryDWrite, "Tahoma", 20);
            factoryDWrite.Dispose();

            _sceneColorBrush = new SolidColorBrush(_wicRenderTarget, color);
            clearColor = color;
            clearColor.Alpha = 0;

            _renderTexture = new Texture2D(device, new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.ShaderResource,
                CpuAccessFlags = CpuAccessFlags.Write,
                Format = Format.R8G8B8A8_UNorm,
                Height = _height,
                Width = _width,
                MipLevels = 1,
                OptionFlags = ResourceOptionFlags.None,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Dynamic
            });

            OverlayBufferRes = new ShaderResourceView(device, _renderTexture, new ShaderResourceViewDescription()
            {
                Format = _renderTexture.Description.Format,
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
            if (_renderTexture != null)
            {
                _renderTexture.Dispose();
                _renderTexture = null;
            }

            if (_wicBitmap != null)
            {
                _wicBitmap.Dispose();
                _wicBitmap = null;
            }

            if (_wicRenderTarget != null)
            {
                _wicRenderTarget.Dispose();
                _wicRenderTarget = null;
            }

            if (_sceneColorBrush != null)
            {
                _sceneColorBrush.Dispose();
                _sceneColorBrush = null;
            }

            if (OverlayBufferRes != null)
            {
                OverlayBufferRes.Dispose();
                OverlayBufferRes = null;
            }

            if (_textFormat != null)
            {
                _textFormat.Dispose();
                _textFormat = null;
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

                _wicRenderTarget.BeginDraw();
                _wicRenderTarget.Clear(clearColor);
                _wicRenderTarget.DrawText(textString, _textFormat, rect, _sceneColorBrush);
                _wicRenderTarget.EndDraw();

                var bitmapLock = _wicBitmap.Lock(SharpDX.WIC.BitmapLockFlags.Read);
                DataStream stream;
                _immediateContext.MapSubresource(_renderTexture, 0, 0, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None, out stream);
                stream.WriteRange(bitmapLock.Data.DataPointer, _width * _height * 4);
                _immediateContext.UnmapSubresource(_renderTexture, 0);
                stream.Dispose();
                bitmapLock.Dispose();
            }
        }
    }
}
