#include "StdAfx.h"

#ifndef DISABLE_GIMPACT
#ifndef DISABLE_BVH

#include "AlignedObjectArray.h"
#include "BoxCollision.h"
#include "GImpactBvh.h"
#include "TriangleShapeEx.h"

/*
GimPair::GimPair(GIM_PAIR* native)
{
	_native = native;
}

GimPair::~GimPair()
{
	this->!GimPair();
}

GimPair::!GimPair()
{
	delete _native;
	_native = NULL;
}

GimPair::GimPair()
{
	_native = new GIM_PAIR();
}

GimPair::GimPair(GimPair^ p)
{
	_native = new GIM_PAIR(*p->_native);
}

GimPair::GimPair(int index1, int index2)
{
	_native = new GIM_PAIR(index1, index2);
}

int GimPair::Index1::get()
{
	return _native->m_index1;
}
void GimPair::Index1::set(int value)
{
	_native->m_index1 = value;
}

int GimPair::Index2::get()
{
	return _native->m_index2;
}
void GimPair::Index2::set(int value)
{
	_native->m_index2 = value;
}
*/


PairSet::PairSet(btPairSet* native)
{
}

PairSet::PairSet()
{
	_native = new btPairSet();
}

void PairSet::PushPair(int index1, int index2)
{
	_native->push_pair(index1, index2);
}

void PairSet::PushPairInv(int index1, int index2)
{
	_native->push_pair_inv(index1, index2);
}


/*
GimBvhData::GimBvhData(GIM_BVH_DATA* native)
{
	_native = native;
}

GimBvhData::~GimBvhData()
{
	this->!GimBvhData();
}

GimBvhData::!GimBvhData()
{
	delete _native;
	_native = NULL;
}

GimBvhData::GimBvhData()
{
	_native = new GIM_BVH_DATA();
}

Aabb^ GimBvhData::Bound::get()
{
	return gcnew Aabb(&_native->m_bound);
}
void GimBvhData::Bound::set(Aabb^ value)
{
	_native->m_bound = value->_native;
}

int GimBvhData::Data::get()
{
	return _native->m_data;
}
void GimBvhData::Data::set(int value)
{
	_native->m_data = value;
}
*/


GimBvhTreeNode::GimBvhTreeNode(GIM_BVH_TREE_NODE* native)
{
	_native = native;
}

GimBvhTreeNode::~GimBvhTreeNode()
{
	this->!GimBvhTreeNode();
}

GimBvhTreeNode::!GimBvhTreeNode()
{
	delete _native;
	_native = NULL;
}

GimBvhTreeNode::GimBvhTreeNode()
{
	_native = new GIM_BVH_TREE_NODE();
}

#pragma managed(push, off)
void GImpactQuantizedBvh_SetBound(GIM_BVH_TREE_NODE* node, btAABB* aabb)
{
	node->m_bound = *aabb;
}
#pragma managed(pop)
Aabb^ GimBvhTreeNode::Bound::get()
{
	return gcnew Aabb(&_native->m_bound, true);
}
void GimBvhTreeNode::Bound::set(Aabb^ value)
{
	GImpactQuantizedBvh_SetBound(_native, value->_native);
}

int GimBvhTreeNode::DataIndex::get()
{
	return _native->getDataIndex();
}
void GimBvhTreeNode::DataIndex::set(int index)
{
	_native->setDataIndex(index);
}

int GimBvhTreeNode::EscapeIndex::get()
{
	return _native->getEscapeIndex();
}
void GimBvhTreeNode::EscapeIndex::set(int index)
{
	_native->setEscapeIndex(index);
}

bool GimBvhTreeNode::IsLeafNode::get()
{
	return _native->isLeafNode();
}


/*
GimBvhDataArray::GimBvhDataArray(GIM_BVH_DATA_ARRAY* native)
{
	_native = native;
}

GimBvhDataArray::GimBvhDataArray()
{
	_native = new GIM_BVH_DATA_ARRAY();
}


GimBvhTreeNodeArray::GimBvhTreeNodeArray(GIM_BVH_TREE_NODE_ARRAY* native)
{
	_native = native;
}

GimBvhTreeNodeArray::GimBvhTreeNodeArray()
{
	_native = new GIM_BVH_TREE_NODE_ARRAY();
}
*/


BvhTree::BvhTree(btBvhTree* native)
{
	_native = native;
}

BvhTree::~BvhTree()
{
	this->!BvhTree();
}

BvhTree::!BvhTree()
{
	delete _native;
	_native = NULL;
}

BvhTree::BvhTree()
{
	_native = new btBvhTree();
}
/*
void BvhTree::BuildTree(GimBvhDataArray^ primitiveBoxes)
{
	_native->build_tree(*(GIM_BVH_DATA_ARRAY*)primitiveBoxes->_native);
}
*/
void BvhTree::ClearNodes()
{
	_native->clearNodes();
}

int BvhTree::GetEscapeNodeIndex(int nodeIndex)
{
	return _native->getEscapeNodeIndex(nodeIndex);
}

int BvhTree::GetLeftNode(int nodeIndex)
{
	return _native->getLeftNode(nodeIndex);
}

void BvhTree::GetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->getNodeBound(nodeIndex, *bound->_native);
}

int BvhTree::GetNodeData(int nodeIndex)
{
	return _native->getNodeData(nodeIndex);
}
/*
GimBvhTreeNode^ BvhTree::GetNodePointer(int index)
{
	return _native->get_node_pointer(index);
}

GimBvhTreeNode^ BvhTree::GetNodePointer()
{
	return _native->get_node_pointer();
}
*/
int BvhTree::GetRightNode(int nodeIndex)
{
	return _native->getRightNode(nodeIndex);
}

bool BvhTree::IsLeafNode(int nodeIndex)
{
	return _native->isLeafNode(nodeIndex);
}

void BvhTree::SetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->setNodeBound(nodeIndex, *bound->_native);
}

int BvhTree::NodeCount::get()
{
	return _native->getNodeCount();
}


PrimitiveManagerBase::PrimitiveManagerBase(btPrimitiveManagerBase* native)
{
	_native = native;
}

PrimitiveManagerBase::~PrimitiveManagerBase()
{
	this->!PrimitiveManagerBase();
}

PrimitiveManagerBase::!PrimitiveManagerBase()
{
	if (this->IsDisposed)
		return;

	delete _native;
	_native = NULL;
}

void PrimitiveManagerBase::GetPrimitiveBox(int primIndex, Aabb^ primbox)
{
	_native->get_primitive_box(primIndex, *primbox->_native);
}

void PrimitiveManagerBase::GetPrimitiveTriangle(int primIndex, PrimitiveTriangle^ triangle)
{
	_native->get_primitive_triangle(primIndex, *triangle->_native);
}

bool PrimitiveManagerBase::IsDisposed::get()
{
	return (_native == NULL);
}

bool PrimitiveManagerBase::IsTrimesh::get()
{
	return _native->is_trimesh();
}

int PrimitiveManagerBase::PrimitiveCount::get()
{
	return _native->get_primitive_count();
}


GImpactBvh::GImpactBvh(btGImpactBvh* native)
{
	_native = native;
}

GImpactBvh::~GImpactBvh()
{
	this->!GImpactBvh();
}

GImpactBvh::!GImpactBvh()
{
	delete _native;
	_native = NULL;
}

GImpactBvh::GImpactBvh()
{
	_native = new btGImpactBvh();
}

GImpactBvh::GImpactBvh(PrimitiveManagerBase^ primitiveManager)
{
	_native = new btGImpactBvh(GetUnmanagedNullable(primitiveManager));
	_primitiveManager = primitiveManager;
}

bool GImpactBvh::BoxQuery(Aabb^ box, AlignedIntArray^ collidedResults)
{
	return _native->boxQuery(*box->_native, *(btAlignedObjectArray<int>*)collidedResults->_native);
}

bool GImpactBvh::BoxQueryTrans(Aabb^ box, Matrix transform, AlignedIntArray^ collidedResults)
{
	TRANSFORM_CONV(transform);
	bool ret = _native->boxQueryTrans(*box->_native, TRANSFORM_USE(transform), *(btAlignedObjectArray<int>*)collidedResults->_native);
	TRANSFORM_DEL(transform);
	return ret;
}

void GImpactBvh::BuildSet()
{
	_native->buildSet();
}

void GImpactBvh::FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2,
	Matrix trans2, PairSet^ collisionPairs)
{
	TRANSFORM_CONV(trans1);
	TRANSFORM_CONV(trans2);
	btGImpactBvh::find_collision(boxset1->_native, TRANSFORM_USE(trans1), boxset2->_native,
		TRANSFORM_USE(trans2), *collisionPairs->_native);
	TRANSFORM_DEL(trans1);
	TRANSFORM_DEL(trans2);
}
/*
GimBvhTreeNode^ GImpactBvh::GetNodePointer(int index)
{
	return _native->get_node_pointer(index);
}

GimBvhTreeNode^ GImpactBvh::GetNodePointer()
{
	return _native->get_node_pointer();
}
*/
int GImpactBvh::GetEscapeNodeIndex(int nodeIndex)
{
	return _native->getEscapeNodeIndex(nodeIndex);
}

int GImpactBvh::GetLeftNode(int nodeIndex)
{
	return _native->getLeftNode(nodeIndex);
}

void GImpactBvh::GetNodeBound(int nodeIndex, Aabb^ bound)
{
	_native->getNodeBound(nodeIndex, *bound->_native);
}

int GImpactBvh::GetNodeData(int nodeIndex)
{
	return _native->getNodeData(nodeIndex);
}
/*
GimBvhTreeNode^ GImpactBvh::GetNodePointer(int index)
{
	return gcnew GimBvhTreeNode(_native->get_node_pointer(index));
}

GimBvhTreeNode^ GImpactBvh::GetNodePointer()
{
	return gcnew GimBvhTreeNode(_native->get_node_pointer());
}
*/
void GImpactBvh::GetNodeTriangle(int nodeIndex, PrimitiveTriangle^ triangle)
{
	_native->getNodeTriangle(nodeIndex, *triangle->_native);
}

int GImpactBvh::GetRightNode(int nodeIndex)
{
	return _native->getRightNode(nodeIndex);
}

bool GImpactBvh::IsLeafNode(int nodeIndex)
{
	return _native->isLeafNode(nodeIndex);
}

bool GImpactBvh::RayQuery(Vector3 rayDir, Vector3 rayOrigin, AlignedIntArray^ collidedResults)
{
	VECTOR3_CONV(rayDir);
	VECTOR3_CONV(rayOrigin);
	bool ret = _native->rayQuery(VECTOR3_USE(rayDir), VECTOR3_USE(rayOrigin), *(btAlignedObjectArray<int>*)collidedResults->_native);
	VECTOR3_DEL(rayDir);
	VECTOR3_DEL(rayOrigin);
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
	return gcnew Aabb(aabb, false);
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
	return _primitiveManager;
}
void GImpactBvh::PrimitiveManager::set(PrimitiveManagerBase^ primitiveManager)
{
	_native->setPrimitiveManager(GetUnmanagedNullable(primitiveManager));
	_primitiveManager = primitiveManager;
}

#endif
#endif
