using BulletSharp;
using System;
using System.Globalization;
using System.IO;

namespace ConvexDecompositionDemo
{
    internal sealed class WavefrontWriter : IDisposable
    {
        private FileStream _outputFile;
        private StreamWriter _outputStream;
        private CultureInfo _floatFormat = new CultureInfo("en-US");

        private long _baseIndex = 0;
        private int _objectCount = 0;

        public WavefrontWriter(string filename)
        {
            var _outputFile = new FileStream(filename, FileMode.Create, FileAccess.Write);
            _outputStream = new StreamWriter(_outputFile);
        }

        public void OutputObject(Vector3[] hullVertices, int[] hullIndices)
        {
            _outputStream.WriteLine("## Object {0} with {1} vertices and {2} triangles.", _objectCount, hullVertices.Length, hullIndices.Length / 3);

            _outputStream.WriteLine("usemtl Material{0}", _baseIndex);
            _outputStream.WriteLine("o Object{0}", _baseIndex);

            foreach (Vector3 p in hullVertices)
            {
                _outputStream.WriteLine(string.Format(_floatFormat, "v {0:F9} {1:F9} {2:F9}", p.X, p.Y, p.Z));
            }

            for (int i = 0; i < hullIndices.Length; i += 3)
            {
                long index0 = _baseIndex + hullIndices[i];
                long index1 = _baseIndex + hullIndices[i + 1];
                long index2 = _baseIndex + hullIndices[i + 2];

                _outputStream.WriteLine("f {0} {1} {2}", index0 + 1, index1 + 1, index2 + 1);
            }
            _baseIndex += hullVertices.Length;
        }

        public void Dispose()
        {
            if (_outputStream != null)
            {
                _outputStream.Dispose();
                _outputStream = null;
            }

            if (_outputFile != null)
            {
                _outputFile.Dispose();
                _outputFile = null;
            }
        }
    }
}
