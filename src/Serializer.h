#pragma once

namespace BulletSharp
{
	ref class DataStream;

	// Not to be confused with Mogre::Serializer
	public ref class Serializer abstract : IDisposable
	{
	internal:
		btSerializer* _native;
		Serializer(btSerializer* native);

	public:
		!Serializer();
	protected:
		~Serializer();

	public:
		//Chunk^ Allocate(int size, int numElements);
		//void FinalizeChunk(Chunk^ chunk, char^ structType, int chunkCode, IntPtr oldPtr);
		//String^ FindNameForPointer(IntPtr ptr);
		//IntPtr FindPointer(IntPtr oldPtr);
		void FinishSerialization();
		//IntPtr GetUniquePointer(IntPtr oldPtr);
		void RegisterNameForObject(Object^ obj, String^ name);
		void SerializeName(String^ name);
		void StartSerialization();

		DataStream^ Serializer::LockBuffer();

		property IntPtr BufferPointer
		{
			IntPtr get();
		}

		property int CurrentBufferSize
		{
			int get();
		}

		property int SerializationFlags
		{
			int get();
			void set(int flags);
		}
	};

	public ref class DefaultSerializer : Serializer
	{
	public:
		DefaultSerializer(int totalSize);
		DefaultSerializer();

		//IntPtr InternalAlloc(int size);
		void WriteHeader([Out] String^% buffer);
	};
};
