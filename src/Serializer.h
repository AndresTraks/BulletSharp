#pragma once

namespace BulletSharp
{
	ref class DataStream;

	// Not to be confused with Mogre::Serializer
	public ref class Serializer
	{
	internal:
		btSerializer* _native;

		Serializer(btSerializer* serializer);

	public:
		//void FinalizeChunk(Chunk^ chunk, String^, int chunkCode, IntPtr oldPtr);
		//String^ FindNameForPointer(Object^ obj);
		//Object^ FindObject(Object^ oldPtr);
		void FinishSerialization();
		void RegisterNameForObject(Object^ obj, String^ name);
		void SerializeName(String^ name);
		void StartSerialization();

		DataStream^ Serializer::LockBuffer();

		property int CurrentBufferSize
		{
			int get();
		}
	};

	public ref class DefaultSerializer : Serializer
	{
	public:
		DefaultSerializer();

		void WriteHeader([Out] String^% buffer);
	};
};
