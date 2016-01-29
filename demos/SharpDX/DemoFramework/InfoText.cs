using SharpDX;
using SharpDX.Direct2D1;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DirectWrite;
using SharpDX.DXGI;
using System;
using TextAntialiasMode = SharpDX.Direct2D1.TextAntialiasMode;

namespace DemoFramework
{
    public class InfoText : IDisposable
    {
        Color4 color = new Color4(1, 1, 1, 1);
        Color4 clearColor;
        RectangleF rect;
        Guid pixelFormat = SharpDX.WIC.PixelFormat.Format32bppPRGBA;
        long _bitmapSize;
        bool _isDisposed;

        TextFormat _textFormat;
        SharpDX.Direct3D11.DeviceContext _immediateContext;
        WicRenderTarget _wicRenderTarget;
        SharpDX.WIC.Bitmap _wicBitmap;
        SolidColorBrush _sceneColorBrush;
        Texture2D _renderTexture;
        public ShaderResourceView OverlayBufferRes;

        public bool IsEnabled { get; set; } = true;

        bool _isDirty;
        string _text = "";
        public string Text
        {
            get { return _text; }
            set
            {
                _text = value;
                _isDirty = true;
            }
        }

        public float Height { get { return rect.Height; } }
        public float Width { get { return rect.Width; } }

        public InfoText(SharpDX.Direct3D11.Device device, int width, int height)
        {
            _immediateContext = device.ImmediateContext;
            rect.Size = new Size2F(width, height);
            _bitmapSize = width * height * 4;

            using (var factoryWic = new SharpDX.WIC.ImagingFactory())
            {
                _wicBitmap = new SharpDX.WIC.Bitmap(factoryWic,
                    width, height, pixelFormat, SharpDX.WIC.BitmapCreateCacheOption.CacheOnLoad);
            }

            var renderTargetProperties = new RenderTargetProperties(RenderTargetType.Default,
                new SharpDX.Direct2D1.PixelFormat(SharpDX.DXGI.Format.R8G8B8A8_UNorm,
                    SharpDX.Direct2D1.AlphaMode.Premultiplied), 0, 0, RenderTargetUsage.None,
                    SharpDX.Direct2D1.FeatureLevel.Level_DEFAULT);

            using (var factory2D = new SharpDX.Direct2D1.Factory())
            {
                _wicRenderTarget = new WicRenderTarget(factory2D, _wicBitmap, renderTargetProperties);
                _wicRenderTarget.TextAntialiasMode = TextAntialiasMode.Default;
            }

            using (var factoryDWrite = new SharpDX.DirectWrite.Factory(SharpDX.DirectWrite.FactoryType.Shared))
            {
                _textFormat = new TextFormat(factoryDWrite, "Tahoma", 20);
            }

            _sceneColorBrush = new SolidColorBrush(_wicRenderTarget, color);
            clearColor = color;
            clearColor.Alpha = 0;

            _renderTexture = new Texture2D(device, new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.ShaderResource,
                CpuAccessFlags = CpuAccessFlags.Write,
                Format = Format.R8G8B8A8_UNorm,
                Height = height,
                Width = width,
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
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposing || _isDisposed) return;

            Console.WriteLine("dsdfksdniof");
            _renderTexture.Dispose();
            _wicBitmap.Dispose();
            _wicRenderTarget.Dispose();
            _sceneColorBrush.Dispose();
            OverlayBufferRes.Dispose();
            _textFormat.Dispose();

            _isDisposed = true;
        }

        public void Render()
        {
            if (!_isDirty) return;
            if (!IsEnabled) return;

            _wicRenderTarget.BeginDraw();
            _wicRenderTarget.Clear(clearColor);
            _wicRenderTarget.DrawText(_text, _textFormat, rect, _sceneColorBrush);
            _wicRenderTarget.EndDraw();

            var bitmapLock = _wicBitmap.Lock(SharpDX.WIC.BitmapLockFlags.Read);
            DataStream stream;
            _immediateContext.MapSubresource(_renderTexture, 0, 0, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None, out stream);
            stream.WriteRange(bitmapLock.Data.DataPointer, _bitmapSize);
            _immediateContext.UnmapSubresource(_renderTexture, 0);
            stream.Dispose();
            bitmapLock.Dispose();
        }
    }
}
