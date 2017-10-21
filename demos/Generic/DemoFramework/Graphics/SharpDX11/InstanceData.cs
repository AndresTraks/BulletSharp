using BulletSharp;
using System.Runtime.InteropServices;

namespace DemoFramework.SharpDX11
{
    [StructLayout(LayoutKind.Sequential)]
    public struct InstanceData
    {
        public Matrix WorldTransform;
        public uint Color;

        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(InstanceData));
    }

    public class InstanceDataList
    {
        private const int InitialCapacity = 16;
        private int _nextIndex;
        private InstanceData[] _array;
        private int _capacityAtLastClear = 1;

        public InstanceData[] Array => _array;
        public int Count => _nextIndex;

        public InstanceDataList()
        {
            _array = new InstanceData[InitialCapacity];
        }

        public void Add(ref Matrix transform, uint color)
        {
            EnsureCapacity();
            _array[_nextIndex].WorldTransform = transform;
            _array[_nextIndex].Color = color;
            _nextIndex++;
        }

        public void Add(uint color)
        {
            EnsureCapacity();
            _array[_nextIndex].WorldTransform = Matrix.Identity;
            _array[_nextIndex].Color = color;
            _nextIndex++;
        }

        public void Clear()
        {
            // If array was filled to less than half,
            // then allocate half the memory.
            if (_nextIndex < (_capacityAtLastClear >> 1) && _array.Length > InitialCapacity)
            {
                System.Array.Resize(ref _array, _array.Length >> 1);
            }

            _nextIndex = 0;
            _capacityAtLastClear = _array.Length;
        }

        private void EnsureCapacity()
        {
            if (_array.Length <= _nextIndex)
            {
                System.Array.Resize(ref _array, _array.Length << 1);
            }
        }
    }
}
