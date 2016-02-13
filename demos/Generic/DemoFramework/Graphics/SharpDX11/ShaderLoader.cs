using SharpDX.D3DCompiler;
using System.IO;
using System.Reflection;

namespace DemoFramework.SharpDX11
{
    public class ShaderLoader
    {
        public static ShaderBytecode FromResource(Assembly assembly, string sourceName, ShaderFlags flags)
        {
            return FromResource(assembly, new[] { sourceName }, flags);
        }

        public static ShaderBytecode FromResource(Assembly assembly, string[] sourceNames, ShaderFlags flags)
        {
            string assemblyName = assembly.GetName().Name;
            string shaderSource = "";
            foreach (string source in sourceNames)
            {
                using (var stream = assembly.GetManifestResourceStream(string.Format("{0}.{1}", assemblyName, source)))
                {
                    StreamReader reader = new StreamReader(stream);
                    shaderSource += reader.ReadToEnd();
                }
            }
            return ShaderBytecode.Compile(shaderSource, "fx_5_0", flags);
        }
    }
}
