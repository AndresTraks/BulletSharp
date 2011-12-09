using System;
using System.Windows.Forms;
using SlimDX.Direct3D9;

namespace DemoFramework.SlimDX
{
    /// <summary>
    /// Provides creation and management functionality for a Direct3D9 rendering device and related objects.
    /// </summary>
    public class DeviceContext9 : IDisposable
    {
        #region Public Interface

        internal DeviceContext9(Form form, DeviceSettings9 settings)
        {
            if (form.Handle == IntPtr.Zero)
                throw new ArgumentException("Value must be a valid window handle.", "handle");
            if (settings == null)
                throw new ArgumentNullException("settings");

            this.settings = settings;

            PresentParameters = new PresentParameters();
            PresentParameters.BackBufferFormat = Format.X8R8G8B8;
            PresentParameters.BackBufferCount = 1;
            PresentParameters.BackBufferWidth = form.ClientSize.Width;
            PresentParameters.BackBufferHeight = form.ClientSize.Height;
            PresentParameters.Multisample = settings.MultisampleType;
            PresentParameters.SwapEffect = SwapEffect.Discard;
            PresentParameters.EnableAutoDepthStencil = true;
            PresentParameters.AutoDepthStencilFormat = Format.D24S8;
            PresentParameters.PresentFlags = PresentFlags.DiscardDepthStencil;
            PresentParameters.PresentationInterval = PresentInterval.Immediate;
            PresentParameters.Windowed = settings.Windowed;
            PresentParameters.DeviceWindowHandle = form.Handle;

            direct3D = new Direct3D();
            Device = new Device(direct3D, settings.AdapterOrdinal, DeviceType.Hardware, form.Handle, settings.CreationFlags, PresentParameters);
        }

        /// <summary>
        /// Performs object finalization.
        /// </summary>
        ~DeviceContext9()
        {
            Dispose(false);
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        /// <param name="disposeManagedResources">If true, managed resources should be
        /// disposed of in addition to unmanaged resources.</param>
        protected virtual void Dispose(bool disposeManagedResources)
        {
            if (disposeManagedResources)
            {
                Device.Dispose();
                direct3D.Dispose();
            }
        }

        /// <summary>
        /// Gets the underlying Direct3D9 device.
        /// </summary>
        public Device Device
        {
            get;
            private set;
        }

        public PresentParameters PresentParameters
        {
            get;
            private set;
        }

        #endregion
        #region Implementation Detail

        DeviceSettings9 settings;
        Direct3D direct3D;

        #endregion
    }
}
