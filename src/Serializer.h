#pragma once

namespace BulletSharp
{
	public ref class Serializer
	{
	private:
		btSerializer* _serializer;
	
	internal:
		Serializer(btSerializer* serializer);
	
	public:
		//void FinalizeChunk(Chunk^ chunk, String^, int chunkCode, IntPtr oldPtr);
		//String^ FindNameForPointer(Object^ obj);
		//Object^ FindObject(Object^ oldPtr);
		void FinishSerialization();
		//void RegisterNameForObject(Object^ obj, String^ name);
		void SerializeName(String^ name);
		void StartSerialization();

		property IntPtr BufferPointer
		{
			IntPtr get();
		}

		property int CurrentBufferSize
		{
			int get();
		}

	internal:
		property btSerializer* UnmanagedPointer
		{
			btSerializer* get();
			void set(btSerializer* value);
		}
	};

	public ref class DefaultSerializer : Serializer
	{
	public:
		DefaultSerializer(int totalSize);

	internal:
		property btDefaultSerializer* UnmanagedPointer
		{
			btDefaultSerializer* get();
		}
	};
};
