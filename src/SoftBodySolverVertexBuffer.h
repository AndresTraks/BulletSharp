#pragma once

namespace BulletSharp
{
	ref class FloatArray;

	namespace SoftBody
	{
		public ref class VertexBufferDescriptor
		{
		private:
			btVertexBufferDescriptor* _buffer;

		internal:
			VertexBufferDescriptor(btVertexBufferDescriptor* buffer);

			property btVertexBufferDescriptor* UnmanagedPointer
			{
				btVertexBufferDescriptor* get();
				void set(btVertexBufferDescriptor* value);
			}
		};

		public ref class CpuVertexBufferDescriptor : VertexBufferDescriptor
		{
		public:
			CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset, int vertexStride, int normalOffset, int normalStride);

		internal:
			property btCPUVertexBufferDescriptor* UnmanagedPointer
			{
				btCPUVertexBufferDescriptor* get() new;
			}
		};
	};
};
