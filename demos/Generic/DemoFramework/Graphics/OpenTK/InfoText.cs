using System;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace DemoFramework.OpenTK
{
    /// <summary>
    /// Uses System.Drawing for 2d text rendering.
    /// </summary>
    public class InfoText : IDisposable
    {
        Font font = new Font(FontFamily.GenericSerif, 12, FontStyle.Bold);
        Brush brush = Brushes.Red;
        Bitmap bmp;
        System.Drawing.Graphics gfx;
        int texture;
        Rectangle dirtyRegion;
        bool graphicsInitialized = false;
        int width = 270;
        int height = 150;
        GLControl glControl;

        bool _isEnabled = true;
        public bool IsEnabled
        {
            get { return _isEnabled; }
            set { _isEnabled = value; }
        }

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

        public InfoText(GLControl glControl)
        {
            this.glControl = glControl;
        }

        void InitializeGraphics()
        {
            if (GraphicsContext.CurrentContext == null)
                throw new InvalidOperationException("No GraphicsContext is current on the calling thread.");

            bmp = new Bitmap(width, height, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            gfx = System.Drawing.Graphics.FromImage(bmp);
            gfx.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

            texture = GL.GenTexture();
            GL.BindTexture(TextureTarget.Texture2D, texture);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, bmp.Width, bmp.Height, 0,
                PixelFormat.Rgba, PixelType.UnsignedByte, IntPtr.Zero);

            graphicsInitialized = true;
        }

        /// <summary>
        /// Clears the backing store.
        /// </summary>
        public void Clear()
        {
            gfx.Clear(Color.FromArgb(0));
            dirtyRegion = new Rectangle(0, 0, bmp.Width, bmp.Height);
        }

        public void OnRender()
        {
            if (!_isEnabled) return;

            if (!graphicsInitialized)
                InitializeGraphics();

            if (_isDirty)
            {
                Clear();
                gfx.DrawString(_text, font, brush, 0, 0);

                SizeF size = gfx.MeasureString(_text, font);
                dirtyRegion =
                    Rectangle.Round(RectangleF.Union(dirtyRegion, new RectangleF(0, 0, size.Width, size.Height)));
                dirtyRegion = Rectangle.Intersect(dirtyRegion, new Rectangle(0, 0, bmp.Width, bmp.Height));


                // Update bitmap
                if (dirtyRegion != RectangleF.Empty)
                {
                    System.Drawing.Imaging.BitmapData data = bmp.LockBits(dirtyRegion,
                        System.Drawing.Imaging.ImageLockMode.ReadOnly,
                        System.Drawing.Imaging.PixelFormat.Format32bppArgb);

                    GL.BindTexture(TextureTarget.Texture2D, texture);
                    GL.TexSubImage2D(TextureTarget.Texture2D, 0,
                        dirtyRegion.X, dirtyRegion.Y, dirtyRegion.Width, dirtyRegion.Height,
                        PixelFormat.Bgra, PixelType.UnsignedByte, data.Scan0);

                    bmp.UnlockBits(data);

                    dirtyRegion = Rectangle.Empty;
                }

                _isDirty = false;
            }

            //Render bitmap
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0, glControl.Width, 0, glControl.Height, -1.0, 1.0);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();

            GL.Disable(EnableCap.DepthTest);
            GL.Enable(EnableCap.Texture2D);
            GL.Disable(EnableCap.Lighting);
            GL.Enable(EnableCap.Blend);
            GL.BlendFunc(BlendingFactorSrc.SrcAlpha, BlendingFactorDest.OneMinusSrcAlpha);

            GL.BindTexture(TextureTarget.Texture2D, texture);

            GL.Begin(PrimitiveType.Quads);
            GL.TexCoord2(0.0f, 1.0f); GL.Vertex2(0, 0);
            GL.TexCoord2(0.0f, 0.0f); GL.Vertex2(0, height);
            GL.TexCoord2(1.0f, 0.0f); GL.Vertex2(width, height);
            GL.TexCoord2(1.0f, 1.0f); GL.Vertex2(width, 0);
            GL.End();

            GL.Disable(EnableCap.Texture2D);
        }

        void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (bmp != null)
                {
                    bmp.Dispose();
                    bmp = null;
                }
                if (gfx != null)
                {
                    gfx.Dispose();
                    gfx = null;
                }
                if (GraphicsContext.CurrentContext != null)
                    GL.DeleteTexture(texture);
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~InfoText()
        {
            Console.WriteLine("[Warning] Resource leaked: {0}.", typeof(TextRenderer));
        }
    }
}
