#include "StdAfx.h"

#ifndef DISABLE_BVH
#ifndef DISABLE_GIMPACT

#include "AlignedObjectArray.h"
#include "BoxCollision.h"
#include "Collections.h"
#include "GImpactBvh.h"
#include "GImpactQuantizedBvh.h"
#include "TriangleShapeEx.h"

GImpactQuantizedBvhNode::GImpactQuantizedBvhNode(BT_QUANTIZED_BVH_NODE* native)
{
	_native = native;
}

GImpactQuantizedBvhNode::~GImpactQuantizedBvhNode()
{
	this->!GImpactQuantizedBvhNode();
}

GImpactQuantizedBvhNode::!GImpactQuantizedBvhNode()
{
	delete _native;
	_native = NULL;
}

GImpactQuantizedBvhNode::GImpactQuantizedBvhNode()
{
	_native = new BT_QUANTIZED_BVH_NODE();
}

bool GImpactQuantizedBvhNode::TestQuantizedBoxOverlap(array<unsigned short>^ quantizedMin,
	array<unsigned short>^ quantizedMax)
{
	pin_ptr<unsigned short> quantizedMinPtr = &quantizedMin[0];
	pin_ptr<unsigned short> quantizedMaxPtr = &quantizedMax[0];
	return _native->testQuantizedBoxOverlapp(quantizedMinPtr, quantizedMaxPtr);
}

int GImpactQuantizedBvhNode::DataIndex::get()
{
	return _native->getDataIndex();
}
void GImpactQuantizedBvhNode::DataIndex::set(int index)
{
	_native->setDataIndex(index);
}

int GImpactQuantizedBvhNode::EscapeIndex::get()
{
	return _native->getEscapeIndex();
}
void GImpactQuantizedBvhNode::EscapeIndex::set(int index)
{
	_native->setEscapeIndex(index);
}

int GImpactQuantizedBvhNode::EscapeIndexOrDataIndex::get()
{
	return _native->m_escapeIndexOrDataIndex;
}
void GImpactQuantizedBvhNode::EscapeIndexOrDataIndex::set(int value)
{
	_native->m_escapeIndexOrDataIndex = value;
}

bool GImpactQuantizedBvhNode::IsLeafNode::get()
{
	return _native->isLeafNode();
}

UShortArray^ GImpactQuantizedBvhNode::QuantizedAabbMax::get()
{
	return gcnew UShortArray(_native->m_quantizedAabbMax, 3);
}

UShortArray^ GImpactQuantizedBvhNode::QuantizedAabbMin::get()
{
	return gcnew UShortArray(_native->m_quantizedAabbMin, 3);
}


GimGImpactQuantizedBvhNodeArray::GimGImpactQuantizedBvhNodeArray(GIM_QUANTIZED_BVH_NODE_ARRAY* native)
{
	_native = native;
}

GimGImpactQuantizedBvhNodeArray::GimGImpactQuantizedBvhNodeArray()
{
	_native = new GIM_QUANTIZED_BVH_NODE_ARRAY();
}


QuantizedBvhTree::QuantizedBvhTree(btQuantizedBvhTree* native)
{
	_native = native;
}

QuantizedBvhTree::~QuantizedBvhTree()
{
	this->!QuantizedBvhTree();
}

QuantizedBvhTree::!QuantizedBvhTree()
{
	delete _native;
	_native = NULL;
}

QuantizedBvhTree::QuantizedBvhTree()
{
	_native = new btQuantizedBvhTree();
}
/*
void QuantizedBvhTree::BuildTree(GimBvhDataArray^ primitiveBoxes)
{
	_native->build_tree(*(GIM_BVH_DATA_ARRAY*)primitiveBoxes->_native);
}
*/
void QuantizedBvhTree::ClearNodes()
{
	_native->clearNodes();
}
/*
GImpactQuantizedBvhNode^ QuantizedBvhTree::GetNodePointer(int index)
{
	return _native->get_node_pointer(index);
}

GImpactQuantizedBvhNode^ QuantizedBvhTree::GetNodePointer()
{
	return _native->get_node_pointer();
}
*/
int QuantizedBvhTree::GetEscapeNodeIndex(int nodeIndex)
{
	return _native->getEscapeNodeIndex(nodeIndex);
}

int QuantizedBvhTree::GetLeftNode(int nodeIndex)
{
	return _native->getLeftNode(nodeIndex);
}

void QuantizedBvhTree::GetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->getNodeBound(nodeIndex, *bound->_native);
}

int QuantizedBvhTree::GetNodeData(int nodeIndex)
{
	return _native->getNodeData(nodeIndex);
}

int QuantizedBvhTree::GetRightNode(int nodeIndex)
{
	return _native->getRightNode(nodeIndex);
}

bool QuantizedBvhTree::IsLeafNode(int nodeIndex)
{
	return _native->isLeafNode(nodeIndex);
}

void QuantizedBvhTree::QuantizePoint(UShortArray^ quantizedpoint, Vector3 point)
{
	VECTOR3_CONV(point);
	_native->quantizePoint((unsigned short*)quantizedpoint->_native, VECTOR3_USE(point));
	VECTOR3_DEL(point);
}

void QuantizedBvhTree::SetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->setNodeBound(nodeIndex, *bound->_native);
}

bool QuantizedBvhTree::TestQuantizedBoxOverlap(int nodeIndex, UShortArray^ quantizedMin,
	UShortArray^ quantizedMax)
{
	return _native->testQuantizedBoxOverlapp(nodeIndex, (unsigned short*)quantizedMin->_native, (unsigned short*)quantizedMax->_native);
}

int QuantizedBvhTree::NodeCount::get()
{
	return _native->getNodeCount();
}


GImpactQuantizedBvh::GImpactQuantizedBvh(btGImpactQuantizedBvh* native)
{
	_native = native;
}

GImpactQuantizedBvh::~GImpactQuantizedBvh()
{
	this->!GImpactQuantizedBvh();
}

GImpactQuantizedBvh::!GImpactQuantizedBvh()
{
	delete _native;
	_native = NULL;
}

GImpactQuantizedBvh::GImpactQuantizedBvh()
{
	_native = new btGImpactQuantizedBvh();
}

GImpactQuantizedBvh::GImpactQuantizedBvh(PrimitiveManagerBase^ primitiveManager)
{
	_primitiveManager = primitiveManager;
	_native = new btGImpactQuantizedBvh(primitiveManager->_native);
}

bool GImpactQuantizedBvh::BoxQuery(Aabb^ box, AlignedIntArray^ collidedResults)
{
	return _native->boxQuery(*box->_native, *(btAlignedObjectArray<int>*)collidedResults->_native);
}

bool GImpactQuantizedBvh::BoxQueryTrans(Aabb^ box, Matrix transform, AlignedIntArray^ collidedResults)
{
	TRANSFORM_CONV(transform);
	bool ret = _native->boxQueryTrans(*box->_native, TRANSFORM_USE(transform), *(btAlignedObjectArray<int>*)collidedResults->_native);
	TRANSFORM_DEL(transform);
	return ret;
}

void GImpactQuantizedBvh::BuildSet()
{
	_native->buildSet();
}

void GImpactQuantizedBvh::FindCollision(GImpactQuantizedBvh^ boxset1, Matrix trans1,
	GImpactQuantizedBvh^ boxset2, Matrix trans2, PairSet^ collisionPairs)
{
	TRANSFORM_CONV(trans1);
	TRANSFORM_CONV(trans2);
	btGImpactQuantizedBvh::find_collision(boxset1->_native, TRANSFORM_USE(trans1),
		boxset2->_native, TRANSFORM_USE(trans2), *collisionPairs->_native);
	TRANSFORM_DEL(trans1);
	TRANSFORM_DEL(trans2);
}
/*
GImpactQuantizedBvhNode^ GImpactQuantizedBvh::GetNodePointer(int index)
{
	return _native->get_node_pointer(index);
}

GImpactQuantizedBvhNode^ GImpactQuantizedBvh::GetNodePointer()
{
	return _native->get_node_pointer();
}
*/
int GImpactQuantizedBvh::GetEscapeNodeIndex(int nodeIndex)
{
	return _native->getEscapeNodeIndex(nodeIndex);
}

int GImpactQuantizedBvh::GetLeftNode(int nodeIndex)
{
	return _native->getLeftNode(nodeIndex);
}

void GImpactQuantizedBvh::GetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->getNodeBound(nodeIndex, *bound->_native);
}

int GImpactQuantizedBvh::GetNodeData(int nodeIndex)
{
	return _native->getNodeData(nodeIndex);
}

void GImpactQuantizedBvh::GetNodeTriangle(int nodeIndex, PrimitiveTriangle^ triangle)
{
	_native->getNodeTriangle(nodeIndex, *triangle->_native);
}

int GImpactQuantizedBvh::GetRightNode(int nodeIndex)
{
	return _native->getRightNode(nodeIndex);
}

bool GImpactQuantizedBvh::IsLeafNode(int nodeIndex)
{
	return _native->isLeafNode(nodeIndex);
}

bool GImpactQuantizedBvh::RayQuery(Vector3 rayDir, Vector3 rayOrigin, AlignedIntArray^ collidedResults)
{
	VECTOR3_CONV(rayDir);
	VECTOR3_CONV(rayOrigin);
	bool ret = _native->rayQuery(VECTOR3_USE(rayDir), VECTOR3_USE(rayOrigin), *(btAlignedObjectArray<int>*)collidedResults->_native);
	VECTOR3_DEL(rayDir);
	VECTOR3_DEL(rayOrigin);
	return ret;
}

void GImpactQuantizedBvh::SetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->setNodeBound(nodeIndex, *bound->_native);
}

void GImpactQuantizedBvh::Update()
{
	_native->update();
}

#pragma managed(push, off)
void GImpactQuantizedBvh_GlobalBox(btGImpactQuantizedBvh* bvh, btAABB* aabb)
{
	*aabb = bvh->getGlobalBox();
}
#pragma managed(pop)
Aabb^ GImpactQuantizedBvh::GlobalBox::get()
{
	btAABB* aabb = new btAABB;
	GImpactQuantizedBvh_GlobalBox(_native, aabb);
	return gcnew Aabb(aabb, false);
}

bool GImpactQuantizedBvh::HasHierarchy::get()
{
	return _native->hasHierarchy();
}

bool GImpactQuantizedBvh::IsTrimesh::get()
{
	return _native->isTrimesh();
}

int GImpactQuantizedBvh::NodeCount::get()
{
	return _native->getNodeCount();
}

PrimitiveManagerBase^ GImpactQuantizedBvh::PrimitiveManager::get()
{
	return _primitiveManager;
}
void GImpactQuantizedBvh::PrimitiveManager::set(PrimitiveManagerBase^ primitiveManager)
{
	_primitiveManager = primitiveManager;
	_native->setPrimitiveManager(primitiveManager->_native);
}

#endif
#endif
