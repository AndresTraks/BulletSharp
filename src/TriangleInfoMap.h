#pragma once

namespace BulletSharp
{
	ref class Serializer;

	public ref class TriangleInfoMap
	{
	private:
		btTriangleInfoMap* _triangleInfoMap;

	public:
		TriangleInfoMap();

		void Clear();
#ifndef DISABLE_SERIALIZE
		int	CalculateSerializeBufferSize();
		String^ Serialize(IntPtr dataBuffer, Serializer^ serializer);
		//void Deserialize(struct btTriangleInfoMapData& data);
#endif

		property btScalar ConvexEpsilon
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar EdgeDistanceThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar EqualVertexThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar PlanarEpsilon
		{
			btScalar get();
			void set(btScalar value);
		}

		property int Size
		{
			int get();
		}

		property btScalar ZeroAreaThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

	internal:
		property btTriangleInfoMap* UnmanagedPointer
		{
			virtual btTriangleInfoMap* get();
			void set(btTriangleInfoMap* value);
		}
	};
};
