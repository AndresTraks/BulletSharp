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
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.VertexBuffer,
            };
        }

        public override void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();

            if (lines.Count == 0)
                return;

            inputAssembler.InputLayout = inputLayout;

            vertexBufferDesc.SizeInBytes = PositionColored.Stride * lines.Count;
            Buffer vertexBuffer;
            using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(lines.ToArray());
                vertexBuffer = new Buffer(device, data, vertexBufferDesc);
            }

            inputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, PositionColored.Stride, 0));
            inputAssembler.PrimitiveTopology = global::SharpDX.Direct3D.PrimitiveTopology.LineList;

            device.Draw(lines.Count, 0);

            vertexBuffer.Dispose();
            lines.Clear();
        }
    }
};
