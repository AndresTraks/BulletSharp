using System.IO;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using Device = SharpDX.Direct3D10.Device;

namespace DemoFramework
{
    public class Model
    {
        ShaderResourceView textureView;
        Device device;

        int indexCount;
        readonly VertexBufferBinding[] nullBinding = new VertexBufferBinding[3];
        VertexBufferBinding[] binding;

        Buffer indices;
        Buffer normals;
        Buffer vertices;
        //Buffer texCoords;

        public Model(Device device, string effectName, string meshName)
        {
            this.device = device;
        }

        public static Model CreateBox(Device device, float x, float y, float z)
        {
            Model mesh = new Model(device, "shader.fx", "box");
            return mesh;
        }

        public void Draw()
        {
            //effect.GetVariableByName("model_texture").AsShaderResource().SetResource(textureView);
            //device.InputAssembler.SetInputLayout(layout);
            //device.InputAssembler.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
            device.InputAssembler.SetIndexBuffer(indices, Format.R32_UInt, 0);
            device.InputAssembler.SetVertexBuffers(0, binding);

            //effect.GetTechniqueByIndex(0).GetPassByIndex(0).Apply();
            device.DrawIndexed(indexCount, 0, 0);

            device.InputAssembler.SetIndexBuffer(null, Format.Unknown, 0);
            device.InputAssembler.SetVertexBuffers(0, nullBinding);
        }
    }
}
