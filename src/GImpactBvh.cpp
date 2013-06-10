#include "StdAfx.h"

#ifndef DISABLE_GIMPACT
#ifndef DISABLE_BVH

#include "AlignedObjectArray.h"
#include "BoxCollision.h"
#include "GImpactBvh.h"
#include "TriangleShapeEx.h"

PairSet::PairSet()
{
	_pairSet = new btPairSet();
}

PairSet::PairSet(btPairSet* pairSet)
{
	_pairSet = pairSet;
}

void PairSet::PushPair(int index1, int index2)
{
	_pairSet->push_pair(index1, index2);
}

void PairSet::PushPairInv(int index1, int index2)
{
	_pairSet->push_pair_inv(index1, index2);
}


GimBvhTreeNode::GimBvhTreeNode()
{
	_node = new GIM_BVH_TREE_NODE();
}

GimBvhTreeNode::GimBvhTreeNode(GIM_BVH_TREE_NODE* node)
{
	_node = node;
}

GimBvhTreeNode::GimBvhTreeNode(const GIM_BVH_TREE_NODE* node)
{
	_node = (GIM_BVH_TREE_NODE*)node;
}

#pragma managed(push, off)
void GImpactQuantizedBvh_SetBound(GIM_BVH_TREE_NODE* node, btAABB* aabb)
{
	node->m_bound = *aabb;
}
#pragma managed(pop)
Aabb^ GimBvhTreeNode::Bound::get()
{
	return gcnew Aabb(&_node->m_bound);
}
void GimBvhTreeNode::Bound::set(Aabb^ value)
{
	GImpactQuantizedBvh_SetBound(_node, value->_native);
}

int GimBvhTreeNode::DataIndex::get()
{
	return _node->getDataIndex();
}
void GimBvhTreeNode::DataIndex::set(int value)
{
	_node->setDataIndex(value);
}

int GimBvhTreeNode::EscapeIndex::get()
{
	return _node->getEscapeIndex();
}
void GimBvhTreeNode::EscapeIndex::set(int value)
{
	_node->setEscapeIndex(value);
}

bool GimBvhTreeNode::IsLeafNode::get()
{
	return _node->isLeafNode();
}


PrimitiveManagerBase::PrimitiveManagerBase(btPrimitiveManagerBase* primitiveManager)
{
	_native = primitiveManager;
}

PrimitiveManagerBase::~PrimitiveManagerBase()
{
	this->!PrimitiveManagerBase();
}

PrimitiveManagerBase::!PrimitiveManagerBase()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

void PrimitiveManagerBase::GetPrimitiveBox(int prim_index, [Out] Aabb^% primbox)
{
	btAABB* primboxTemp = new btAABB;
	_native->get_primitive_box(prim_index, *primboxTemp);
	primbox = gcnew Aabb(primboxTemp);
}

void PrimitiveManagerBase::GetPrimitiveTriangle(int prim_index, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle;
	_native->get_primitive_triangle(prim_index, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

bool PrimitiveManagerBase::IsTriMesh::get()
{
	return _native->is_trimesh();
}

int PrimitiveManagerBase::PrimitiveCount::get()
{
	return _native->get_primitive_count();
}

bool PrimitiveManagerBase::IsDisposed::get()
{
	return (_native == NULL);
}


GImpactBvh::GImpactBvh(btGImpactBvh* bvh)
{
	_native = bvh;
}

GImpactBvh::GImpactBvh(PrimitiveManagerBase^ primitive_manager)
{
	_native = new btGImpactBvh(primitive_manager->_native);
}

GImpactBvh::GImpactBvh()
{
	_native = new btGImpactBvh();
}

bool GImpactBvh::BoxQuery(Aabb^ box, [Out] AlignedIntArray^% collided_results)
{
	return _native->boxQuery(*box->_native, *(btAlignedObjectArray<int>*)collided_results->_native);
}

bool GImpactBvh::BoxQueryTrans(Aabb^ box, Matrix transform, [Out] AlignedIntArray^% collided_results)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	bool ret = _native->boxQueryTrans(*box->_native, *transformTemp, *(btAlignedObjectArray<int>*)collided_results->_native);
	ALIGNED_FREE(transformTemp);
	return ret;
}

void GImpactBvh::BuildSet()
{
	_native->buildSet();
}

void GImpactBvh::FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2, Matrix trans2, [Out] PairSet^% collision_pairs)
{
	btTransform* trans1Temp = Math::MatrixToBtTransform(trans1);
	btTransform* trans2Temp = Math::MatrixToBtTransform(trans2);
	btPairSet* collision_pairsTemp = new btPairSet();

	btGImpactBvh::find_collision(boxset1->_native, *trans1Temp, boxset2->_native, *trans2Temp, *collision_pairsTemp);
	collision_pairs = gcnew PairSet(collision_pairsTemp);

	ALIGNED_FREE(trans1Temp);
	ALIGNED_FREE(trans2Temp);
}

int GImpactBvh::GetEscapeNodeIndex(int nodeIndex)
{
	return _native->getEscapeNodeIndex(nodeIndex);
}

int GImpactBvh::GetLeftNode(int nodeIndex)
{
	return _native->getLeftNode(nodeIndex);
}

void GImpactBvh::GetNodeBound(int nodeIndex, [Out] Aabb^% bound)
{
	btAABB* boundTemp = new btAABB;
	_native->getNodeBound(nodeIndex, *boundTemp);
	bound = gcnew Aabb(boundTemp);
}

int GImpactBvh::GetNodeData(int nodeIndex)
{
	return _native->getNodeData(nodeIndex);
}

GimBvhTreeNode^ GImpactBvh::GetNodePointer(int index)
{
	return gcnew GimBvhTreeNode(_native->get_node_pointer(index));
}

GimBvhTreeNode^ GImpactBvh::GetNodePointer()
{
	return gcnew GimBvhTreeNode(_native->get_node_pointer());
}

void GImpactBvh::GetNodeTriangle(int nodeIndex, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle;
	_native->getNodeTriangle(nodeIndex, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

int GImpactBvh::GetRightNode(int nodeIndex)
{
	return _native->getRightNode(nodeIndex);
}

bool GImpactBvh::IsLeafNode(int nodeIndex)
{
	return _native->isLeafNode(nodeIndex);
}

bool GImpactBvh::RayQuery(Vector3 ray_dir, Vector3 ray_origin, [Out] AlignedIntArray^% collided_results)
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

void GImpactBvh::SetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->setNodeBound(nodeIndex, *bound->_native);
}

void GImpactBvh::Update()
{
	_native->update();
}

//float GImpactBvh::AverageTreeCollisionTime::get()
//{
//	return btGImpactBvh::getAverageTreeCollisionTime();
//}

#pragma managed(push, off)
void GImpactBvh_GlobalBox(btGImpactBvh* bvh, btAABB* aabb)
{
	*aabb = bvh->getGlobalBox();
}
#pragma managed(pop)
Aabb^ GImpactBvh::GlobalBox::get()
{
	btAABB* aabb = new btAABB;
	GImpactBvh_GlobalBox(_native, aabb);
	return gcnew Aabb(aabb);
}

bool GImpactBvh::HasHierarchy::get()
{
	return _native->hasHierarchy();
}

bool GImpactBvh::IsTrimesh::get()
{
	return _native->isTrimesh();
}

int GImpactBvh::NodeCount::get()
{
	return _native->getNodeCount();
}

PrimitiveManagerBase^ GImpactBvh::PrimitiveManager::get()
{
	return gcnew PrimitiveManagerBase(_native->getPrimitiveManager());
}
void GImpactBvh::PrimitiveManager::set(PrimitiveManagerBase^ value)
{
	_native->setPrimitiveManager(value->_native);
}

#endif
#endif
