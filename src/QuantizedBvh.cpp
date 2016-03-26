#include "StdAfx.h"

#include "Collections.h"
#include "OptimizedBvh.h"
#include "QuantizedBvh.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

#ifndef DISABLE_BVH

QuantizedBvhNode::QuantizedBvhNode(btQuantizedBvhNode* native)
{
	_native = native;
}

QuantizedBvhNode::~QuantizedBvhNode()
{
	this->!QuantizedBvhNode();
}

QuantizedBvhNode::!QuantizedBvhNode()
{
	delete _native;
	_native = NULL;
}

QuantizedBvhNode::QuantizedBvhNode()
{
	_native = new btQuantizedBvhNode();
}

int QuantizedBvhNode::EscapeIndex::get()
{
	return _native->getEscapeIndex();
}

int QuantizedBvhNode::EscapeIndexOrTriangleIndex::get()
{
	return _native->m_escapeIndexOrTriangleIndex;
}
void QuantizedBvhNode::EscapeIndexOrTriangleIndex::set(int value)
{
	_native->m_escapeIndexOrTriangleIndex = value;
}

bool QuantizedBvhNode::IsLeafNode::get()
{
	return _native->isLeafNode();
}

int QuantizedBvhNode::PartId::get()
{
	return _native->getPartId();
}

UShortArray^ QuantizedBvhNode::QuantizedAabbMax::get()
{
	return gcnew UShortArray(_native->m_quantizedAabbMax, 3);
}

UShortArray^ QuantizedBvhNode::QuantizedAabbMin::get()
{
	return gcnew UShortArray(_native->m_quantizedAabbMin, 3);
}

int QuantizedBvhNode::TriangleIndex::get()
{
	return _native->getTriangleIndex();
}


OptimizedBvhNode::OptimizedBvhNode(btOptimizedBvhNode* native)
{
	_native = native;
}

OptimizedBvhNode::~OptimizedBvhNode()
{
	this->!OptimizedBvhNode();
}

OptimizedBvhNode::!OptimizedBvhNode()
{
	delete _native;
	_native = NULL;
}

OptimizedBvhNode::OptimizedBvhNode()
{
	_native = new btOptimizedBvhNode();
}

Vector3 OptimizedBvhNode::AabbMaxOrg::get()
{
	return Math::BtVector3ToVector3(&_native->m_aabbMaxOrg);
}
void OptimizedBvhNode::AabbMaxOrg::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_aabbMaxOrg);
}

Vector3 OptimizedBvhNode::AabbMinOrg::get()
{
	return Math::BtVector3ToVector3(&_native->m_aabbMinOrg);
}
void OptimizedBvhNode::AabbMinOrg::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_aabbMinOrg);
}

int OptimizedBvhNode::EscapeIndex::get()
{
	return _native->m_escapeIndex;
}
void OptimizedBvhNode::EscapeIndex::set(int value)
{
	_native->m_escapeIndex = value;
}

int OptimizedBvhNode::SubPart::get()
{
	return _native->m_subPart;
}
void OptimizedBvhNode::SubPart::set(int value)
{
	_native->m_subPart = value;
}

int OptimizedBvhNode::TriangleIndex::get()
{
	return _native->m_triangleIndex;
}
void OptimizedBvhNode::TriangleIndex::set(int value)
{
	_native->m_triangleIndex = value;
}


NodeOverlapCallback::NodeOverlapCallback(btNodeOverlapCallback* native)
{
	_native = native;
}

NodeOverlapCallback::~NodeOverlapCallback()
{
	this->!NodeOverlapCallback();
}

NodeOverlapCallback::!NodeOverlapCallback()
{
	delete _native;
	_native = NULL;
}

void NodeOverlapCallback::ProcessNode(int subPart, int triangleIndex)
{
	_native->processNode(subPart, triangleIndex);
}
#endif


QuantizedBvh::QuantizedBvh(btQuantizedBvh* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

QuantizedBvh::~QuantizedBvh()
{
	this->!QuantizedBvh();
}

QuantizedBvh::!QuantizedBvh()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

#ifndef DISABLE_BVH
QuantizedBvh::QuantizedBvh()
{
	_native = new btQuantizedBvh();
}

void QuantizedBvh::BuildInternal()
{
	_native->buildInternal();
}

#ifndef DISABLE_SERIALIZE
unsigned int QuantizedBvh::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}

int QuantizedBvh::CalculateSerializeBufferSizeNew()
{
	return _native->calculateSerializeBufferSizeNew();
}
/*
void QuantizedBvh::DeSerializeDouble(QuantizedBvhDoubleData^ quantizedBvhDoubleData)
{
	_native->deSerializeDouble(*quantizedBvhDoubleData->_native);
}

void QuantizedBvh::DeSerializeFloat(QuantizedBvhFloatData^ quantizedBvhFloatData)
{
	_native->deSerializeFloat(*quantizedBvhFloatData->_native);
}
*/
QuantizedBvh^ QuantizedBvh::DeSerializeInPlace(IntPtr alignedDataBuffer, unsigned int dataBufferSize,
	bool swapEndian)
{
	if (alignedDataBuffer == IntPtr::Zero) {
		return nullptr;
	}

	btQuantizedBvh* quantizedBvhPtr = btQuantizedBvh::deSerializeInPlace(alignedDataBuffer.ToPointer(), dataBufferSize,
		swapEndian);

	btOptimizedBvh* optimizedBvh = dynamic_cast<btOptimizedBvh*>(quantizedBvhPtr);
	if (optimizedBvh) {
		return gcnew OptimizedBvh(optimizedBvh, true);
	}

	return gcnew QuantizedBvh(quantizedBvhPtr, true);
}
#endif
/*
void QuantizedBvh::Quantize(unsigned short^ out, Vector3 point, int isMax)
{
	VECTOR3_CONV(point);
	_native->quantize(out->_native, VECTOR3_USE(point), isMax);
	VECTOR3_DEL(point);
}

void QuantizedBvh::QuantizeWithClamp(unsigned short^ out, Vector3 point2, int isMax)
{
	VECTOR3_CONV(point2);
	_native->quantizeWithClamp(out->_native, VECTOR3_USE(point2), isMax);
	VECTOR3_DEL(point2);
}
*/
void QuantizedBvh::ReportAabbOverlappingNodex(NodeOverlapCallback^ nodeCallback,
	Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->reportAabbOverlappingNodex(nodeCallback->_native, VECTOR3_USE(aabbMin),
		VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void QuantizedBvh::ReportBoxCastOverlappingNodex(NodeOverlapCallback^ nodeCallback,
	Vector3 raySource, Vector3 rayTarget, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(raySource);
	VECTOR3_CONV(rayTarget);
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->reportBoxCastOverlappingNodex(nodeCallback->_native, VECTOR3_USE(raySource),
		VECTOR3_USE(rayTarget), VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(raySource);
	VECTOR3_DEL(rayTarget);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void QuantizedBvh::ReportRayOverlappingNodex(NodeOverlapCallback^ nodeCallback, Vector3 raySource,
	Vector3 rayTarget)
{
	VECTOR3_CONV(raySource);
	VECTOR3_CONV(rayTarget);
	_native->reportRayOverlappingNodex(nodeCallback->_native, VECTOR3_USE(raySource),
		VECTOR3_USE(rayTarget));
	VECTOR3_DEL(raySource);
	VECTOR3_DEL(rayTarget);
}

#ifndef DISABLE_SERIALIZE
bool QuantizedBvh::Serialize(IntPtr alignedDataBuffer, unsigned int dataBufferSize,
	bool swapEndian)
{
	return _native->serialize(alignedDataBuffer.ToPointer(), dataBufferSize, swapEndian);
}

String^ QuantizedBvh::Serialize(IntPtr dataBuffer, Serializer^ serializer)
{
	return gcnew String(_native->serialize(dataBuffer.ToPointer(), serializer->_native));
}
#endif

void QuantizedBvh::SetQuantizationValues(Vector3 bvhAabbMin, Vector3 bvhAabbMax,
	btScalar quantizationMargin)
{
	VECTOR3_CONV(bvhAabbMin);
	VECTOR3_CONV(bvhAabbMax);
	_native->setQuantizationValues(VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax),
		quantizationMargin);
	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

void QuantizedBvh::SetQuantizationValues(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	VECTOR3_CONV(bvhAabbMin);
	VECTOR3_CONV(bvhAabbMax);
	_native->setQuantizationValues(VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax));
	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

void QuantizedBvh::SetTraversalMode(TraversalMode traversalMode)
{
	_native->setTraversalMode((btQuantizedBvh::btTraversalMode)traversalMode);
}
/*
Vector3 QuantizedBvh::UnQuantize(unsigned short^ vecIn)
{
	return Math::BtVector3ToVector3(&_native->unQuantize(vecIn->_native));
}
*/
#ifndef DISABLE_SERIALIZE
unsigned int QuantizedBvh::AlignmentSerializationPadding::get()
{
	return btQuantizedBvh::getAlignmentSerializationPadding();
}
#endif
#endif
bool QuantizedBvh::IsDisposed::get()
{
	return (_native == NULL);
}

bool QuantizedBvh::IsQuantized::get()
{
	return _native->isQuantized();
}
#ifndef DISABLE_BVH
/*
QuantizedNodeArray^ QuantizedBvh::LeafNodeArray::get()
{
	return _native->getLeafNodeArray();
}

QuantizedNodeArray^ QuantizedBvh::QuantizedNodeArray::get()
{
	return _native->getQuantizedNodeArray();
}

BvhSubtreeInfoArray^ QuantizedBvh::SubtreeInfoArray::get()
{
	return _native->getSubtreeInfoArray();
}
*/
#endif
