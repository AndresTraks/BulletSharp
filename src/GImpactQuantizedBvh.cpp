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
	_bvh = bvh;
}

GImpactQuantizedBvh::GImpactQuantizedBvh()
{
	_bvh = new btGImpactQuantizedBvh();
}

GImpactQuantizedBvh::GImpactQuantizedBvh(PrimitiveManagerBase^ primitiveManager)
{
	_bvh = new btGImpactQuantizedBvh(primitiveManager->UnmanagedPointer);
}

bool GImpactQuantizedBvh::BoxQuery(Aabb^ box, [Out] AlignedIntArray^% collided_results)
{
	return _bvh->boxQuery(*box->UnmanagedPointer, *collided_results->UnmanagedPointer);
}

bool GImpactQuantizedBvh::BoxQueryTrans(Aabb^ box, Matrix transform, [Out] AlignedIntArray^% collided_results)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	bool ret = _bvh->boxQueryTrans(*box->UnmanagedPointer, *transformTemp, *collided_results->UnmanagedPointer);
	delete transformTemp;
	return ret;
}

void GImpactQuantizedBvh::BuildSet()
{
	_bvh->buildSet();
}

void GImpactQuantizedBvh::FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2, Matrix trans2, [Out] PairSet^% collision_pairs)
{
	btTransform* trans1Temp = Math::MatrixToBtTransform(trans1);
	btTransform* trans2Temp = Math::MatrixToBtTransform(trans2);
	btPairSet* collision_pairsTemp = new btPairSet();

	btGImpactBvh::find_collision(boxset1->UnmanagedPointer, *trans1Temp, boxset2->UnmanagedPointer, *trans2Temp, *collision_pairsTemp);
	collision_pairs = gcnew PairSet(collision_pairsTemp);

	delete trans1Temp;
	delete trans2Temp;
}

int GImpactQuantizedBvh::GetEscapeNodeIndex(int nodeIndex)
{
	return _bvh->getEscapeNodeIndex(nodeIndex);
}

int GImpactQuantizedBvh::GetLeftNode(int nodeIndex)
{
	return _bvh->getLeftNode(nodeIndex);
}

void GImpactQuantizedBvh::GetNodeBound(int nodeIndex, [Out] Aabb^% bound)
{
	btAABB* boundTemp = new btAABB;
	_bvh->getNodeBound(nodeIndex, *boundTemp);
	bound = gcnew Aabb(boundTemp);
}

int GImpactQuantizedBvh::GetNodeData(int nodeIndex)
{
	return _bvh->getNodeData(nodeIndex);
}

QuantizedBvhNode^ GImpactQuantizedBvh::GetNodePointer(int index)
{
	return gcnew QuantizedBvhNode(_bvh->get_node_pointer(index));
}

QuantizedBvhNode^ GImpactQuantizedBvh::GetNodePointer()
{
	return gcnew QuantizedBvhNode(_bvh->get_node_pointer());
}

void GImpactQuantizedBvh::GetNodeTriangle(int nodeIndex, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle;
	_bvh->getNodeTriangle(nodeIndex, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

int GImpactQuantizedBvh::GetRightNode(int nodeIndex)
{
	return _bvh->getRightNode(nodeIndex);
}

bool GImpactQuantizedBvh::IsLeafNode(int nodeIndex)
{
	return _bvh->isLeafNode(nodeIndex);
}

bool GImpactQuantizedBvh::RayQuery(Vector3 ray_dir, Vector3 ray_origin, [Out] AlignedIntArray^% collided_results)
{
	btVector3* ray_dirTemp = Math::Vector3ToBtVector3(ray_dir);
	btVector3* ray_originTemp = Math::Vector3ToBtVector3(ray_origin);
	btAlignedObjectArray<int>* collided_resultsTemp = new btAlignedObjectArray<int>();

	bool ret = _bvh->rayQuery(*ray_dirTemp, *ray_originTemp, *collided_resultsTemp);
	collided_results = gcnew AlignedIntArray(collided_resultsTemp);

	delete ray_dirTemp;
	delete ray_originTemp;

	return ret;
}

void GImpactQuantizedBvh::SetNodeBound(int nodeIndex, Aabb^ bound)
{
	_bvh->setNodeBound(nodeIndex, *bound->UnmanagedPointer);
}

void GImpactQuantizedBvh::Update()
{
	_bvh->update();
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
	GImpactQuantizedBvh_GlobalBox(_bvh, aabb);
	return gcnew Aabb(aabb);
}

bool GImpactQuantizedBvh::HasHierarchy::get()
{
	return _bvh->hasHierarchy();
}

bool GImpactQuantizedBvh::IsTrimesh::get()
{
	return _bvh->isTrimesh();
}

int GImpactQuantizedBvh::NodeCount::get()
{
	return _bvh->getNodeCount();
}

PrimitiveManagerBase^ GImpactQuantizedBvh::PrimitiveManager::get()
{
	return gcnew PrimitiveManagerBase(_bvh->getPrimitiveManager());
}
void GImpactQuantizedBvh::PrimitiveManager::set(PrimitiveManagerBase^ value)
{
	_bvh->setPrimitiveManager(value->UnmanagedPointer);
}

#endif
#endif
