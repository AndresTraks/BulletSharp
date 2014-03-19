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

QuantizedBvhTree::QuantizedBvhTree()
{
	_native = new btQuantizedBvhTree();
}
/*
void QuantizedBvhTree::BuildTree(GimBvhDataArray^ primitive_boxes)
{
	_native->build_tree(*(GIM_BVH_DATA_ARRAY*)primitive_boxes->_native);
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
int QuantizedBvhTree::GetEscapeNodeIndex(int NodeIndex)
{
	return _native->getEscapeNodeIndex(NodeIndex);
}

int QuantizedBvhTree::GetLeftNode(int NodeIndex)
{
	return _native->getLeftNode(NodeIndex);
}

void QuantizedBvhTree::GetNodeBound(int NodeIndex, Aabb^ bound)
{
	_native->getNodeBound(NodeIndex, *bound->_native);
}

int QuantizedBvhTree::GetNodeData(int NodeIndex)
{
	return _native->getNodeData(NodeIndex);
}

int QuantizedBvhTree::GetRightNode(int NodeIndex)
{
	return _native->getRightNode(NodeIndex);
}

bool QuantizedBvhTree::IsLeafNode(int NodeIndex)
{
	return _native->isLeafNode(NodeIndex);
}

void QuantizedBvhTree::QuantizePoint(UShortArray^ quantizedpoint, Vector3 point)
{
	VECTOR3_DEF(point);
	_native->quantizePoint((unsigned short*)quantizedpoint->_native, VECTOR3_USE(point));
	VECTOR3_DEL(point);
}

void QuantizedBvhTree::SetNodeBound(int NodeIndex, Aabb^ bound)
{
	_native->setNodeBound(NodeIndex, *bound->_native);
}

bool QuantizedBvhTree::TestQuantizedBoxOverlap(int NodeIndex, UShortArray^ quantizedMin,
	UShortArray^ quantizedMax)
{
	return _native->testQuantizedBoxOverlapp(NodeIndex, (unsigned short*)quantizedMin->_native, (unsigned short*)quantizedMax->_native);
}

int QuantizedBvhTree::NodeCount::get()
{
	return _native->getNodeCount();
}


GImpactQuantizedBvh::GImpactQuantizedBvh(btGImpactQuantizedBvh* native)
{
	_native = native;
}

GImpactQuantizedBvh::GImpactQuantizedBvh()
{
	_native = new btGImpactQuantizedBvh();
}

GImpactQuantizedBvh::GImpactQuantizedBvh(PrimitiveManagerBase^ primitive_manager)
{
	_primitiveManagerBase = primitive_manager;
	_native = new btGImpactQuantizedBvh(primitive_manager->_native);
}

bool GImpactQuantizedBvh::BoxQuery(Aabb^ box, AlignedIntArray^ collided_results)
{
	return _native->boxQuery(*box->_native, *(btAlignedObjectArray<int>*)collided_results->_native);
}

bool GImpactQuantizedBvh::BoxQueryTrans(Aabb^ box, Matrix transform, AlignedIntArray^ collided_results)
{
	TRANSFORM_CONV(transform);
	bool ret = _native->boxQueryTrans(*box->_native, TRANSFORM_USE(transform), *(btAlignedObjectArray<int>*)collided_results->_native);
	TRANSFORM_DEL(transform);
	return ret;
}

void GImpactQuantizedBvh::BuildSet()
{
	_native->buildSet();
}

void GImpactQuantizedBvh::FindCollision(GImpactQuantizedBvh^ boxset1, Matrix trans1,
	GImpactQuantizedBvh^ boxset2, Matrix trans2, PairSet^ collision_pairs)
{
	TRANSFORM_CONV(trans1);
	TRANSFORM_CONV(trans2);
	btGImpactQuantizedBvh::find_collision(boxset1->_native, TRANSFORM_USE(trans1),
		boxset2->_native, TRANSFORM_USE(trans2), *collision_pairs->_native);
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
int GImpactQuantizedBvh::GetEscapeNodeIndex(int nodeindex)
{
	return _native->getEscapeNodeIndex(nodeindex);
}

int GImpactQuantizedBvh::GetLeftNode(int nodeindex)
{
	return _native->getLeftNode(nodeindex);
}

void GImpactQuantizedBvh::GetNodeBound(int nodeindex, Aabb^ bound)
{
	_native->getNodeBound(nodeindex, *bound->_native);
}

int GImpactQuantizedBvh::GetNodeData(int nodeindex)
{
	return _native->getNodeData(nodeindex);
}

void GImpactQuantizedBvh::GetNodeTriangle(int nodeindex, PrimitiveTriangle^ triangle)
{
	_native->getNodeTriangle(nodeindex, *triangle->_native);
}

int GImpactQuantizedBvh::GetRightNode(int nodeindex)
{
	return _native->getRightNode(nodeindex);
}

bool GImpactQuantizedBvh::IsLeafNode(int nodeindex)
{
	return _native->isLeafNode(nodeindex);
}

bool GImpactQuantizedBvh::RayQuery(Vector3 ray_dir, Vector3 ray_origin, AlignedIntArray^ collided_results)
{
	VECTOR3_DEF(ray_dir);
	VECTOR3_DEF(ray_origin);
	return _native->rayQuery(VECTOR3_USE(ray_dir), VECTOR3_USE(ray_origin), *(btAlignedObjectArray<int>*)collided_results->_native);
	VECTOR3_DEL(ray_dir);
	VECTOR3_DEL(ray_origin);
}

void GImpactQuantizedBvh::SetNodeBound(int nodeindex, Aabb^ bound)
{
	_native->setNodeBound(nodeindex, *bound->_native);
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
	return gcnew Aabb(aabb);
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
	return _primitiveManagerBase;
}
void GImpactQuantizedBvh::PrimitiveManager::set(PrimitiveManagerBase^ primitive_manager)
{
	_primitiveManagerBase = primitive_manager;
	_native->setPrimitiveManager(primitive_manager->_native);
}

#endif
#endif
