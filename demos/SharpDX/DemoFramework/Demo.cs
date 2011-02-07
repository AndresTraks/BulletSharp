using System;
using System.Drawing;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using SharpDX.Windows;
using Buffer = SharpDX.Direct3D10.Buffer;
using Device = SharpDX.Direct3D10.Device;

namespace DemoFramework
{
    public class Demo : IDisposable
    {
        public RenderForm Form
        {
            get;
            private set;
        }

        Device _device;
        public Device Device
        {
            get { return _device; }
        }

        SwapChain _swapChain;
        public SwapChain SwapChain
        {
            get { return _swapChain; }
        }

        public float AspectRatio
        {
            get { return (float)Width / (float)Height; }
        }

        public RenderTargetView RenderView { get; private set; }
        public DepthStencilView DepthStencilView { get; private set; }
        DepthStencilState depthStencilState;

        public Effect Effect { get; private set; }
        public EffectTechnique Technique { get; private set; }
        public EffectPass Pass { get; private set; }

        protected int Width { get; set; }
        protected int Height { get; set; }
        protected int FullScreenWidth { get; set; }
        protected int FullScreenHeight { get; set; }
        protected float NearPlane { get; set; }
        protected float FarPlane { get; set; }
        protected Vector3 Eye { get; set; }
        protected Vector3 Target { get; set; }

        ShaderConstants constants = new ShaderConstants();

        protected InfoText Info { get; set; }

        protected Color4 Ambient { get; set; }
        protected MeshFactory MeshFactory { get; private set; }

        Clock clock = new Clock();
        float frameAccumulator;
        int frameCount;

        public float FrameDelta { get; private set; }
        public float FramesPerSecond { get; private set; }

        public PhysicsContext PhysicsContext { get; set; }

        
        [StructLayout(LayoutKind.Sequential)]
        struct ShaderConstants
        {
            public Matrix World;
            public Matrix WorldInverseTranspose;
            public Matrix View;
            public Matrix Projection;
            public Color4 Color;
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
                //apiContext.Dispose();
                Form.Dispose();
            }
        }

        public bool TestLibraries()
        {
            /*
            try
            {
                Assembly.Load("SharpDX, Version=2.0.10.43, Culture=neutral, PublicKeyToken=b1b0c32fd1ffe4f9");
            }
            catch
            {
                MessageBox.Show("SharpDX(v2.0.10.43) not installed." +
                    "Please download it from http://code.google.com/p/sharpdx.", "Error!");
                return false;
            }
            */

            try
            {
                Assembly.Load("BulletSharp");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "BulletSharp Error!");
                return false;
            }

            return true;
        }

        protected virtual void OnInitializeDevice()
        {
            Form.ClientSize = new System.Drawing.Size(Width, Height);

            // SwapChain description
            var desc = new SwapChainDescription()
            {
                BufferCount = 1,
                ModeDescription = new ModeDescription(Form.ClientSize.Width, Form.ClientSize.Height, new Rational(60, 1), Format.R8G8B8A8_UNorm),
                IsWindowed = true,
                OutputHandle = Form.Handle,
                SampleDescription = new SampleDescription(1, 0),
                SwapEffect = SwapEffect.Discard,
                Usage = Usage.RenderTargetOutput
            };

            // Create Device and SwapChain
            Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.Debug, desc, out _device, out _swapChain);

            // Ignore all windows events
            Factory factory = SwapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(Form.Handle, WindowAssociationFlags.IgnoreAll);

            // New RenderTargetView from the backbuffer
            Texture2D backBuffer = Texture2D.FromSwapChain<Texture2D>(SwapChain, 0);
            RenderView = new RenderTargetView(Device, backBuffer);

            Texture2DDescription depthDesc = new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.DepthStencil,
                CpuAccessFlags = CpuAccessFlags.None,
                Format = Format.D32_Float,
                Height = Height,
                Width = Width,
                MipLevels = 1,
                OptionFlags = ResourceOptionFlags.None,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default
            };
            Texture2D depthBuffer = new Texture2D(Device, depthDesc);
            DepthStencilView = new DepthStencilView(Device, depthBuffer);
        }

        void Initialize()
        {
            //ShaderFlags shaderFlags = ShaderFlags.None;
            ShaderFlags shaderFlags = ShaderFlags.Debug | ShaderFlags.SkipOptimization;
            ShaderBytecode shaderByteCode = ShaderBytecode.CompileFromFile("shader.fx", "fx_4_0", shaderFlags, EffectFlags.None);

            Effect = new Effect(Device, shaderByteCode);
            Technique = Effect.GetTechniqueByIndex(0);
            Pass = Technique.GetPassByIndex(0);

            BufferDescription constantsDesc = new BufferDescription()
            {
                SizeInBytes = Marshal.SizeOf(typeof(ShaderConstants)),
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.ConstantBuffer,
                CpuAccessFlags = CpuAccessFlags.Write,
                OptionFlags = ResourceOptionFlags.None
            };

            Buffer constantsBuffer = new Buffer(Device, constantsDesc);
            EffectConstantBuffer effectConstantBuffer = Effect.GetConstantBufferByIndex(0);
            effectConstantBuffer.SetConstantBuffer(constantsBuffer);

            RasterizerStateDescription desc = new RasterizerStateDescription()
            {
                CullMode = CullMode.None,
                FillMode = FillMode.Solid,
                IsFrontCounterClockwise = true,
                DepthBias = 0,
                DepthBiasClamp = 0,
                SlopeScaledDepthBias = 0,
                IsDepthClipEnabled = true,
            };
            Device.Rasterizer.State = new RasterizerState(Device, desc);

            DepthStencilStateDescription depthDesc = new DepthStencilStateDescription()
            {
                IsDepthEnabled = true,
                IsStencilEnabled = false,
                DepthWriteMask = DepthWriteMask.All,
                DepthComparison = Comparison.Less
            };
            depthStencilState = new DepthStencilState(Device, depthDesc);

            OnInitialize();
        }

        protected void SetBuffer(Matrix world, Color color)
        {
            constants.World = world;
            constants.WorldInverseTranspose = Matrix.Transpose(Matrix.Invert(world));
            constants.Color = (Color4)color;

            EffectConstantBuffer effectConstantBuffer = Effect.GetConstantBufferByIndex(0);
            Buffer constantsBuffer = effectConstantBuffer.GetConstantBuffer();
            DataStream c = constantsBuffer.Map(MapMode.WriteDiscard);
            Marshal.StructureToPtr(constants, c.DataPointer, false);
            constantsBuffer.Unmap();
        }

        void Render()
        {
            frameAccumulator += FrameDelta;
            ++frameCount;
            if (frameAccumulator >= 1.0f)
            {
                FramesPerSecond = frameCount / frameAccumulator;

                frameAccumulator = 0.0f;
                frameCount = 0;
            }

            Device.Rasterizer.SetViewports(new Viewport(0, 0, Width, Height));
            
            constants.View = Matrix.LookAtLH(Eye, Target, Vector3.UnitY);
            constants.Projection = Matrix.PerspectiveFovLH((float)Math.PI / 4, AspectRatio, NearPlane, FarPlane);

            //BlendStateDescription desc = new BlendStateDescription()
            //{
            //    BlendEnable = true
            //};
            //BlendState transBlendState = new BlendState(Device, desc);
            //Device.OutputMerger.SetBlendState(transBlendState);

            Device.OutputMerger.SetDepthStencilState(depthStencilState, 0);
            Device.OutputMerger.SetTargets(DepthStencilView, RenderView);

            OnRender();

            SwapChain.Present(0, PresentFlags.None);
        }

        /// <summary>
        /// Updates sample state.
        /// </summary>
        private void Update()
        {
            FrameDelta = clock.Update();
            OnUpdate();
        }

        /// <summary>
        /// Runs the demo.
        /// </summary>
        public void Run()
        {
            bool isFormClosed = false;
            bool formIsResizing = false;

            Form = new RenderForm();
            /*
            currentFormWindowState = Form.WindowState;
            Form.Resize += (o, args) =>
            {
                if (Form.WindowState != currentFormWindowState)
                {
                    if (togglingFullScreen == false)
                        HandleResize(o, args);
                }

                currentFormWindowState = Form.WindowState;
            };
            */
            Form.ResizeBegin += (o, args) => { formIsResizing = true; };
            Form.ResizeEnd += (o, args) =>
            {
                formIsResizing = false;
                Width = Form.ClientSize.Width;
                Height = Form.ClientSize.Height;
            };
            /*
            Form.Closed += (o, args) => { isFormClosed = true; };


            // initialize input
            SlimDX.RawInput.Device.RegisterDevice(UsagePage.Generic, UsageId.Keyboard, DeviceFlags.None);
            SlimDX.RawInput.Device.RegisterDevice(UsagePage.Generic, UsageId.Mouse, DeviceFlags.None);

            Input = new Input(Form);

            SlimDX.RawInput.Device.KeyboardInput += Device_KeyboardInput;
            SlimDX.RawInput.Device.MouseInput += Device_MouseInput;
            */

            Width = 1024;
            Height = 768;
            FullScreenWidth = Screen.PrimaryScreen.Bounds.Width;
            FullScreenHeight = Screen.PrimaryScreen.Bounds.Height;
            NearPlane = 0.1f;
            FarPlane = 200.0f;
            /*
            FieldOfView = (float)Math.PI / 4;
            Freelook = new FreeLook();*/
            Ambient = (Color4)Color.Gray;

            OnInitializeDevice();

            Info = new InfoText(Device);
            MeshFactory = new MeshFactory(Device);

            Initialize();

            clock.Start();
            MessagePump.Run(Form, () =>
            {
                Update();
                Render();
            });
        }

        protected virtual void OnInitialize() { }

        protected virtual void OnRender() { }

        protected virtual void OnUpdate()
        {
            //Freelook.Update(FrameDelta, Input);
            PhysicsContext.Update(FrameDelta);
        }
    }
}
