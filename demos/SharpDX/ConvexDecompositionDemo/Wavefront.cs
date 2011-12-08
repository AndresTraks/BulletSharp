using System.Collections.Generic;
using System.Globalization;
using System.IO;
using SharpDX;

namespace ConvexDecompositionDemo
{
    class WavefrontObj
    {
        Vector2 ToVector2(string f0, string f1)
        {
            return new Vector2(float.Parse(f0, CultureInfo.InvariantCulture),
                float.Parse(f1, CultureInfo.InvariantCulture));
        }

        Vector3 ToVector3(string f0, string f1, string f2)
        {
            return new Vector3(float.Parse(f0, CultureInfo.InvariantCulture),
                float.Parse(f1, CultureInfo.InvariantCulture),
                float.Parse(f2, CultureInfo.InvariantCulture));
        }

        void GetVertex(string[] faceVertex)
        {
            int vindex = int.Parse(faceVertex[0]);
            Vector3 position = vertices[vindex - 1];

            // Search for a duplicate
            int i;
            for (i = 0; i < finalVertices.Count; i++)
            {
                if (finalVertices[i].Equals(position))
                {
                    indices.Add(i);
                    return;
                }
            }

            finalVertices.Add(position);
            indices.Add(finalVertices.Count - 1);
        }

        void ProcessLine(string line)
        {
            string[] parts = line.Split(new char[] { ' ' }, System.StringSplitOptions.RemoveEmptyEntries);
            string cmd = parts[0];

            if (cmd.Equals("v"))
            {
                vertices.Add(ToVector3(parts[1], parts[2], parts[3]));
            }
            else if (cmd.Equals("vt"))
            {
                texels.Add(ToVector2(parts[1], parts[2]));
            }
            else if (cmd.Equals("vn"))
            {
                normals.Add(ToVector3(parts[1], parts[2], parts[3]));
            }
            else if (cmd.Equals("f"))
            {
                List<Vector3> faceVerts = new List<Vector3>();

                for (int i = 1; i < parts.Length; i++)
                {
                    string[] v = parts[i].Split(new char[] { '/' }, System.StringSplitOptions.RemoveEmptyEntries);
                    GetVertex(v);
                }

                int vcount = parts.Length - 1;
            }
        }

        // load a wavefront obj returns number of triangles that were loaded.  Data is persists until the class is destructed.
        public int LoadObj(string fname)
        {
            int ret = 0;
            triCount = 0;

            indices = new List<int>();
            normals = new List<Vector3>();
            texels = new List<Vector2>();
            vertices = new List<Vector3>();
            finalVertices = new List<Vector3>();

            FileStream file = File.OpenRead(fname);
            StreamReader reader = new StreamReader(file);
            while (!reader.EndOfStream)
            {
                ProcessLine(reader.ReadLine());
            }
            file.Dispose();

            if (vertices.Count > 0)
            {
                triCount = indices.Count / 3;
                ret = triCount;
            }

            vertices = null;

            return ret;
        }

        public int triCount;
        List<int> indices;
        public List<Vector3> normals;
        public List<Vector2> texels;
        List<Vector3> vertices;

        List<Vector3> finalVertices;

        public List<int> Indices
        {
            get { return indices; }
        }

        public List<Vector3> Vertices
        {
            get { return finalVertices; }
        }
    }
}
