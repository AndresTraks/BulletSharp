#pragma once

namespace BulletSharp
{
	ref class FloatArray;

	namespace SoftBody
	{
		public ref class VertexBufferDescriptor
		{
		internal:
			btVertexBufferDescriptor* _native;

			VertexBufferDescriptor(btVertexBufferDescriptor* buffer);

		public:
			property BulletSharp::BufferType BufferType
			{
				BulletSharp::BufferType get();
			}

			property bool HasNormals
			{
				bool get();
			}

			property bool HasVertexPositions
			{
				bool get();
			}

			property int NormalOffset
			{
				int get();
			}

			property int NormalStride
			{
				int get();
			}

			property int VertexOffset
			{
				int get();
			}

			property int VertexStride
			{
				int get();
			}
		};

		public ref class CpuVertexBufferDescriptor : VertexBufferDescriptor
		{
		private:
			int _length;

		public:
			CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset, int vertexStride, int normalOffset, int normalStride);
			
			property FloatArray^ VertexBuffer
			{
				FloatArray^ get();
			}
		};
	};
};
