#include "StdAfx.h"

#ifndef DISABLE_BVH
#ifndef DISABLE_GIMPACT

#include "AlignedObjectArray.h"
#include "BoxCollision.h"
#include "Collections.h"
#include "GImpactBvh.h"
#include "GImpactQuantizedBvh.h"
#include "TriangleShapeEx.h"

QuantizedBvhNode::QuantizedBvhNode()
{
	_node = new BT_QUANTIZED_BVH_NODE();
}

QuantizedBvhNode::QuantizedBvhNode(BT_QUANTIZED_BVH_NODE* node)
{
	_node = node;
}

QuantizedBvhNode::QuantizedBvhNode(const BT_QUANTIZED_BVH_NODE* node)
{
	_node = (BT_QUANTIZED_BVH_NODE*)node;
}

bool QuantizedBvhNode::TestQuantizedBoxOverlap(array<unsigned short>^ quantizedMin, array<unsigned short>^ quantizedMax)
{
	pin_ptr<unsigned short> quantizedMinPtr = &quantizedMin[0];
	pin_ptr<unsigned short> quantizedMaxPtr = &quantizedMax[0];

	//TYPO:
	//return _node->testQuantizedBoxOverlap(quantizedMinPtr, quantizedMaxPtr);
	return _node->testQuantizedBoxOverlapp(quantizedMinPtr, quantizedMaxPtr);
}

int QuantizedBvhNode::DataIndex::get()
{
	return _node->getDataIndex();
}
void QuantizedBvhNode::DataIndex::set(int value)
{
	_node->setDataIndex(value);
}

int QuantizedBvhNode::EscapeIndex::get()
{
	return _node->getEscapeIndex();
}
void QuantizedBvhNode::EscapeIndex::set(int value)
{
	_node->setEscapeIndex(value);
}

int QuantizedBvhNode::EscapeIndexOrDataIndex::get()
{
	return _node->m_escapeIndexOrDataIndex;
}
void QuantizedBvhNode::EscapeIndexOrDataIndex::set(int value)
{
	_node->m_escapeIndexOrDataIndex = value;
}

UShortArray^ QuantizedBvhNode::QuantizedAabbMin::get()
{
	return gcnew UShortArray(_node->m_quantizedAabbMin, 3);
}

UShortArray^ QuantizedBvhNode::QuantizedAabbMax::get()
{
	return gcnew UShortArray(_node->m_quantizedAabbMax, 3);
}

bool QuantizedBvhNode::IsLeafNode::get()
{
	return _node->isLeafNode();
}


GImpactQuantizedBvh::GImpactQuantizedBvh(btGImpactQuantizedBvh* bvh)
{
	_native = bvh;
}

GImpactQuantizedBvh::GImpactQuantizedBvh()
{
	_native = new btGImpactQuantizedBvh();
}

GImpactQuantizedBvh::GImpactQuantizedBvh(PrimitiveManagerBase^ primitiveManager)
{
	_native = new btGImpactQuantizedBvh(primitiveManager->_native);
}

bool GImpactQuantizedBvh::BoxQuery(Aabb^ box, [Out] AlignedIntArray^% collided_results)
{
	return _native->boxQuery(*box->_native, *(btAlignedObjectArray<int>*)collided_results->_native);
}

bool GImpactQuantizedBvh::BoxQueryTrans(Aabb^ box, Matrix transform, [Out] AlignedIntArray^% collided_results)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	bool ret = _native->boxQueryTrans(*box->_native, *transformTemp, *(btAlignedObjectArray<int>*)collided_results->_native);
	ALIGNED_FREE(transformTemp);
	return ret;
}

void GImpactQuantizedBvh::BuildSet()
{
	_native->buildSet();
}

void GImpactQuantizedBvh::FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2, Matrix trans2, [Out] PairSet^% collision_pairs)
{
	btTransform* trans1Temp = Math::MatrixToBtTransform(trans1);
	btTransform* trans2Temp = Math::MatrixToBtTransform(trans2);
	btPairSet* collision_pairsTemp = new btPairSet();

	btGImpactBvh::find_collision(boxset1->_native, *trans1Temp, boxset2->_native, *trans2Temp, *collision_pairsTemp);
	collision_pairs = gcnew PairSet(collision_pairsTemp);

	ALIGNED_FREE(trans1Temp);
	ALIGNED_FREE(trans2Temp);
}

int GImpactQuantizedBvh::GetEscapeNodeIndex(int nodeIndex)
{
	return _native->getEscapeNodeIndex(nodeIndex);
}

int GImpactQuantizedBvh::GetLeftNode(int nodeIndex)
{
	return _native->getLeftNode(nodeIndex);
}

void GImpactQuantizedBvh::GetNodeBound(int nodeIndex, [Out] Aabb^% bound)
{
	btAABB* boundTemp = new btAABB;
	_native->getNodeBound(nodeIndex, *boundTemp);
	bound = gcnew Aabb(boundTemp);
}

int GImpactQuantizedBvh::GetNodeData(int nodeIndex)
{
	return _native->getNodeData(nodeIndex);
}

QuantizedBvhNode^ GImpactQuantizedBvh::GetNodePointer(int index)
{
	return gcnew QuantizedBvhNode(_native->get_node_pointer(index));
}

QuantizedBvhNode^ GImpactQuantizedBvh::GetNodePointer()
{
	return gcnew QuantizedBvhNode(_native->get_node_pointer());
}

void GImpactQuantizedBvh::GetNodeTriangle(int nodeIndex, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle;
	_native->getNodeTriangle(nodeIndex, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

int GImpactQuantizedBvh::GetRightNode(int nodeIndex)
{
	return _native->getRightNode(nodeIndex);
}

bool GImpactQuantizedBvh::IsLeafNode(int nodeIndex)
{
	return _native->isLeafNode(nodeIndex);
}

bool GImpactQuantizedBvh::RayQuery(Vector3 ray_dir, Vector3 ray_origin, [Out] AlignedIntArray^% collided_results)
{
	VECTOR3_DEF(ray_dir);
	VECTOR3_DEF(ray_origin);
	btAlignedObjectArray<int>* collided_resultsTemp = new btAlignedObjectArray<int>();

	bool ret = _native->rayQuery(VECTOR3_USE(ray_dir), VECTOR3_USE(ray_origin), *collided_resultsTemp);
	collided_results = gcnew AlignedIntArray(collided_resultsTemp);

	VECTOR3_DEL(ray_dir);
	VECTOR3_DEL(ray_origin);

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

//float GImpactQuantizedBvh::AverageTreeCollisionTime::get()
//{
//	return btGImpactQuantizedBvh::getAverageTreeCollisionTime();
//}

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
	return gcnew PrimitiveManagerBase(_native->getPrimitiveManager());
}
void GImpactQuantizedBvh::PrimitiveManager::set(PrimitiveManagerBase^ value)
{
	_native->setPrimitiveManager(value->_native);
}

#endif
#endif
