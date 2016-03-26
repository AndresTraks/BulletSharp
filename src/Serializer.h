#pragma once

namespace BulletSharp
{
	ref class DataStream;

	// Not to be confused with Mogre::Serializer
	public ref class Serializer abstract
	{
	internal:
		btSerializer* _native;

		Serializer(btSerializer* native);

		~Serializer();
		!Serializer();

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

		property int NumChunks
		{
			int get();
		}

		property int SerializationFlags
		{
			int get();
			void set(int flags);
		}
	};
/*
	public ref class BulletSerializedArrays
	{
	internal:
		btBulletSerializedArrays* _native;

		BulletSerializedArrays(btBulletSerializedArrays* native);

		~BulletSerializedArrays();
		!BulletSerializedArrays();

	public:
		BulletSerializedArrays();

		property AlignedQuantizedBvhDoubleDataArray^ BvhsDouble
		{
			AlignedQuantizedBvhDoubleDataArray^ get();
			void set(AlignedQuantizedBvhDoubleDataArray^ value);
		}

		property AlignedQuantizedBvhFloatDataArray^ BvhsFloat
		{
			AlignedQuantizedBvhFloatDataArray^ get();
			void set(AlignedQuantizedBvhFloatDataArray^ value);
		}

		property AlignedCollisionObjectDoubleDataArray^ CollisionObjectDataDouble
		{
			AlignedCollisionObjectDoubleDataArray^ get();
			void set(AlignedCollisionObjectDoubleDataArray^ value);
		}

		property AlignedCollisionObjectFloatDataArray^ CollisionObjectDataFloat
		{
			AlignedCollisionObjectFloatDataArray^ get();
			void set(AlignedCollisionObjectFloatDataArray^ value);
		}

		property AlignedCollisionShapeDataArray^ ColShapeData
		{
			AlignedCollisionShapeDataArray^ get();
			void set(AlignedCollisionShapeDataArray^ value);
		}

		property AlignedTypedConstraintDataArray^ ConstraintData
		{
			AlignedTypedConstraintDataArray^ get();
			void set(AlignedTypedConstraintDataArray^ value);
		}

		property AlignedTypedConstraintDoubleDataArray^ ConstraintDataDouble
		{
			AlignedTypedConstraintDoubleDataArray^ get();
			void set(AlignedTypedConstraintDoubleDataArray^ value);
		}

		property AlignedTypedConstraintFloatDataArray^ ConstraintDataFloat
		{
			AlignedTypedConstraintFloatDataArray^ get();
			void set(AlignedTypedConstraintFloatDataArray^ value);
		}

		property AlignedDynamicsWorldDoubleDataArray^ DynamicWorldInfoDataDouble
		{
			AlignedDynamicsWorldDoubleDataArray^ get();
			void set(AlignedDynamicsWorldDoubleDataArray^ value);
		}

		property AlignedDynamicsWorldFloatDataArray^ DynamicWorldInfoDataFloat
		{
			AlignedDynamicsWorldFloatDataArray^ get();
			void set(AlignedDynamicsWorldFloatDataArray^ value);
		}

		property AlignedRigidBodyDoubleDataArray^ RigidBodyDataDouble
		{
			AlignedRigidBodyDoubleDataArray^ get();
			void set(AlignedRigidBodyDoubleDataArray^ value);
		}

		property AlignedRigidBodyFloatDataArray^ RigidBodyDataFloat
		{
			AlignedRigidBodyFloatDataArray^ get();
			void set(AlignedRigidBodyFloatDataArray^ value);
		}

		property AlignedbtSoftBodyDoubleDataArray^ SoftBodyDoubleData
		{
			AlignedbtSoftBodyDoubleDataArray^ get();
			void set(AlignedbtSoftBodyDoubleDataArray^ value);
		}

		property AlignedSoftBodyFloatDataArray^ SoftBodyFloatData
		{
			AlignedSoftBodyFloatDataArray^ get();
			void set(AlignedSoftBodyFloatDataArray^ value);
		}
	};
*/
	public ref class DefaultSerializer : Serializer
	{
	public:
		DefaultSerializer(int totalSize);
		DefaultSerializer();

		//IntPtr InternalAlloc(int size);
		void WriteHeader([Out] String^% buffer);
	};
};
