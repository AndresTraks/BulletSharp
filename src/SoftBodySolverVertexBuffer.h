#pragma once

namespace BulletSharp
{
	ref class FloatArray;

	namespace SoftBody
	{
		public ref class VertexBufferDescriptor abstract
		{
		internal:
			btVertexBufferDescriptor* _native;

			VertexBufferDescriptor(btVertexBufferDescriptor* native);

			~VertexBufferDescriptor();
			!VertexBufferDescriptor();

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
			FloatArray^ _vertexBuffer;

		public:
			CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset, int vertexStride);
			CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset, int vertexStride,
				int normalOffset, int normalStride);

			property IntPtr BasePointer
			{
				IntPtr get();
			}

			property FloatArray^ VertexBuffer
			{
				FloatArray^ get();
			}
		};
	};
};
