#pragma once

namespace BulletSharp
{
#ifndef DISABLE_BVH
	ref class UShortArray;
	#ifndef DISABLE_SERIALIZE
	ref class Serializer;
	#endif

	public ref class QuantizedBvhNode
	{
	internal:
		btQuantizedBvhNode* _native;

		QuantizedBvhNode(btQuantizedBvhNode* native);

		~QuantizedBvhNode();
		!QuantizedBvhNode();

	public:
		QuantizedBvhNode();

		property int EscapeIndex
		{
			int get();
		}

		property int EscapeIndexOrTriangleIndex
		{
			int get();
			void set(int value);
		}

		property bool IsLeafNode
		{
			bool get();
		}

		property int PartId
		{
			int get();
		}

		property UShortArray^ QuantizedAabbMax
		{
			UShortArray^ get();
		}

		property UShortArray^ QuantizedAabbMin
		{
			UShortArray^ get();
		}

		property int TriangleIndex
		{
			int get();
		}
	};

	public ref class OptimizedBvhNode
	{
	internal:
		btOptimizedBvhNode* _native;

		OptimizedBvhNode(btOptimizedBvhNode* native);

		~OptimizedBvhNode();
		!OptimizedBvhNode();

	public:
		OptimizedBvhNode();

		property Vector3 AabbMaxOrg
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AabbMinOrg
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property int EscapeIndex
		{
			int get();
			void set(int value);
		}

		property int SubPart
		{
			int get();
			void set(int value);
		}

		property int TriangleIndex
		{
			int get();
			void set(int value);
		}
	};

	public ref class NodeOverlapCallback abstract
	{
	internal:
		btNodeOverlapCallback* _native;

		NodeOverlapCallback(btNodeOverlapCallback* native);

		~NodeOverlapCallback();
		!NodeOverlapCallback();

	public:
		void ProcessNode(int subPart, int triangleIndex);
	};
#endif
	public ref class QuantizedBvh
	{
	public:
		enum class TraversalMode
		{
			Stackless = btQuantizedBvh::TRAVERSAL_STACKLESS,
			StacklessCacheFriendly = btQuantizedBvh::TRAVERSAL_STACKLESS_CACHE_FRIENDLY,
			Recursive = btQuantizedBvh::TRAVERSAL_RECURSIVE
		};

	internal:
		btQuantizedBvh* _native;

	private:
		bool _preventDelete;

	internal:
		QuantizedBvh(btQuantizedBvh* native, bool preventDelete);

		~QuantizedBvh();
		!QuantizedBvh();

	public:
#ifndef DISABLE_BVH
		QuantizedBvh();

		void BuildInternal();
#ifndef DISABLE_SERIALIZE
		unsigned int CalculateSerializeBufferSize();
		int CalculateSerializeBufferSizeNew();
		//void DeSerializeDouble(QuantizedBvhDoubleData^ quantizedBvhDoubleData);
		//void DeSerializeFloat(QuantizedBvhFloatData^ quantizedBvhFloatData);
		static QuantizedBvh^ DeSerializeInPlace(IntPtr alignedDataBuffer, unsigned int dataBufferSize,
			bool swapEndian);
#endif
/*
		void Quantize(unsigned short^ out, Vector3 point, int isMax);
		void QuantizeWithClamp(unsigned short^ out, Vector3 point2, int isMax);
*/
		void ReportAabbOverlappingNodex(NodeOverlapCallback^ nodeCallback, Vector3 aabbMin,
			Vector3 aabbMax);
		void ReportBoxCastOverlappingNodex(NodeOverlapCallback^ nodeCallback, Vector3 raySource,
			Vector3 rayTarget, Vector3 aabbMin, Vector3 aabbMax);
		void ReportRayOverlappingNodex(NodeOverlapCallback^ nodeCallback, Vector3 raySource,
			Vector3 rayTarget);
#ifndef DISABLE_SERIALIZE
		bool Serialize(IntPtr alignedDataBuffer, unsigned int dataBufferSize, bool swapEndian);
		String^ Serialize(IntPtr dataBuffer, Serializer^ serializer);
#endif
		void SetQuantizationValues(Vector3 bvhAabbMin, Vector3 bvhAabbMax, btScalar quantizationMargin);
		void SetQuantizationValues(Vector3 bvhAabbMin, Vector3 bvhAabbMax);
		void SetTraversalMode(TraversalMode traversalMode);
		//Vector3 UnQuantize(unsigned short^ vecIn);

#ifndef DISABLE_SERIALIZE
		property unsigned int AlignmentSerializationPadding
		{
			static unsigned int get();
		}
#endif
#endif
		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool IsQuantized
		{
			bool get();
		}
#ifndef DISABLE_BVH
/*
		property QuantizedNodeArray^ LeafNodeArray
		{
			QuantizedNodeArray^ get();
		}

		property QuantizedNodeArray^ QuantizedNodeArray
		{
			BulletSharp::QuantizedNodeArray^ get();
		}

		property BvhSubtreeInfoArray^ SubtreeInfoArray
		{
			BvhSubtreeInfoArray^ get();
		}
*/
#endif
	};
};
