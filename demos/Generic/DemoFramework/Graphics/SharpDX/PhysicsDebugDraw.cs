using BulletSharp;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using DataStream = global::SharpDX.DataStream;
using Device = SharpDX.Direct3D10.Device;

namespace DemoFramework.SharpDX
{
    public class PhysicsDebugDraw : BufferedDebugDraw
    {
        Device device;
        InputAssemblerStage inputAssembler;
        InputLayout inputLayout;
        BufferDescription vertexBufferDesc;
        PositionColored[] lineArray = new PositionColored[0];
        Buffer vertexBuffer;
        VertexBufferBinding vertexBufferBinding;

        public PhysicsDebugDraw(SharpDXGraphics graphics)
        {
            device = graphics.Device;
            inputAssembler = device.InputAssembler;

            InputElement[] elements = new InputElement[]
            {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("COLOR", 0, Format.R8G8B8A8_UNorm, 12, 0, InputClassification.PerVertexData, 0)
            };
            inputLayout = new InputLayout(device, graphics.GetDebugDrawPass().Description.Signature, elements);

            vertexBufferDesc = new BufferDescription()
            {
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.VertexBuffer,
                CpuAccessFlags = CpuAccessFlags.Write
            };

            vertexBufferBinding = new VertexBufferBinding(null, PositionColored.Stride, 0);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (vertexBuffer != null)
                {
                    vertexBuffer.Dispose();
                    vertexBuffer = null;
                }
            }

            base.Dispose(disposing);
        }

        public void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();

            if (lines.Count == 0)
                return;

            inputAssembler.InputLayout = inputLayout;

            if (lineArray.Length != lines.Count)
            {
                lineArray = new PositionColored[lines.Count];
                lines.CopyTo(lineArray);

                if (vertexBuffer != null)
                {
                    vertexBuffer.Dispose();
                }
                vertexBufferDesc.SizeInBytes = PositionColored.Stride * lines.Count;
                using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
                {
                    data.WriteRange(lineArray);
                    data.Position = 0;
                    vertexBuffer = new Buffer(device, data, vertexBufferDesc);
                }
                vertexBufferBinding.Buffer = vertexBuffer;
            }
            else
            {
                lines.CopyTo(lineArray);
                using (var map = vertexBuffer.Map(MapMode.WriteDiscard))
                {
                    map.WriteRange(lineArray);
                }
                vertexBuffer.Unmap();
            }

            inputAssembler.SetVertexBuffers(0, vertexBufferBinding);
            inputAssembler.PrimitiveTopology = global::SharpDX.Direct3D.PrimitiveTopology.LineList;

            device.Draw(lines.Count, 0);

            lines.Clear();
        }
    }
};
