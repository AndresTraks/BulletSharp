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
	GImpactQuantizedBvh_SetBound(_node, value->UnmanagedPointer);
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
	_primitiveManager = primitiveManager;
}

PrimitiveManagerBase::~PrimitiveManagerBase()
{
	this->!PrimitiveManagerBase();
}

PrimitiveManagerBase::!PrimitiveManagerBase()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_primitiveManager = NULL;

	OnDisposed( this, nullptr );
}

void PrimitiveManagerBase::GetPrimitiveBox(int prim_index, [Out] Aabb^% primbox)
{
	btAABB* primboxTemp = new btAABB;
	_primitiveManager->get_primitive_box(prim_index, *primboxTemp);
	primbox = gcnew Aabb(primboxTemp);
}

void PrimitiveManagerBase::GetPrimitiveTriangle(int prim_index, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle;
	_primitiveManager->get_primitive_triangle(prim_index, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

bool PrimitiveManagerBase::IsTriMesh::get()
{
	return _primitiveManager->is_trimesh();
}

int PrimitiveManagerBase::PrimitiveCount::get()
{
	return _primitiveManager->get_primitive_count();
}

bool PrimitiveManagerBase::IsDisposed::get()
{
	return (_primitiveManager == NULL);
}

btPrimitiveManagerBase* PrimitiveManagerBase::UnmanagedPointer::get()
{
	return _primitiveManager;
}
void PrimitiveManagerBase::UnmanagedPointer::set(btPrimitiveManagerBase* value)
{
	_primitiveManager = value;
}


GImpactBvh::GImpactBvh(btGImpactBvh* bvh)
{
	_bvh = bvh;
}

GImpactBvh::GImpactBvh(PrimitiveManagerBase^ primitive_manager)
{
	_bvh = new btGImpactBvh(primitive_manager->UnmanagedPointer);
}

GImpactBvh::GImpactBvh()
{
	_bvh = new btGImpactBvh();
}

bool GImpactBvh::BoxQuery(Aabb^ box, [Out] IntArray^% collided_results)
{
	return _bvh->boxQuery(*box->UnmanagedPointer, *collided_results->UnmanagedPointer);
}

bool GImpactBvh::BoxQueryTrans(Aabb^ box, Matrix transform, [Out] IntArray^% collided_results)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	bool ret = _bvh->boxQueryTrans(*box->UnmanagedPointer, *transformTemp, *collided_results->UnmanagedPointer);
	delete transformTemp;
	return ret;
}

void GImpactBvh::BuildSet()
{
	_bvh->buildSet();
}

void GImpactBvh::FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2, Matrix trans2, [Out] PairSet^% collision_pairs)
{
	btTransform* trans1Temp = Math::MatrixToBtTransform(trans1);
	btTransform* trans2Temp = Math::MatrixToBtTransform(trans2);
	btPairSet* collision_pairsTemp = new btPairSet();

	btGImpactBvh::find_collision(boxset1->UnmanagedPointer, *trans1Temp, boxset2->UnmanagedPointer, *trans2Temp, *collision_pairsTemp);
	collision_pairs = gcnew PairSet(collision_pairsTemp);

	delete trans1Temp;
	delete trans2Temp;
}

int GImpactBvh::GetEscapeNodeIndex(int nodeIndex)
{
	return _bvh->getEscapeNodeIndex(nodeIndex);
}

int GImpactBvh::GetLeftNode(int nodeIndex)
{
	return _bvh->getLeftNode(nodeIndex);
}

void GImpactBvh::GetNodeBound(int nodeIndex, [Out] Aabb^% bound)
{
	btAABB* boundTemp = new btAABB;
	_bvh->getNodeBound(nodeIndex, *boundTemp);
	bound = gcnew Aabb(boundTemp);
}

int GImpactBvh::GetNodeData(int nodeIndex)
{
	return _bvh->getNodeData(nodeIndex);
}

GimBvhTreeNode^ GImpactBvh::GetNodePointer(int index)
{
	return gcnew GimBvhTreeNode(_bvh->get_node_pointer(index));
}

GimBvhTreeNode^ GImpactBvh::GetNodePointer()
{
	return gcnew GimBvhTreeNode(_bvh->get_node_pointer());
}

void GImpactBvh::GetNodeTriangle(int nodeIndex, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle;
	_bvh->getNodeTriangle(nodeIndex, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

int GImpactBvh::GetRightNode(int nodeIndex)
{
	return _bvh->getRightNode(nodeIndex);
}

bool GImpactBvh::IsLeafNode(int nodeIndex)
{
	return _bvh->isLeafNode(nodeIndex);
}

bool GImpactBvh::RayQuery(Vector3 ray_dir, Vector3 ray_origin, [Out] IntArray^% collided_results)
{
	btVector3* ray_dirTemp = Math::Vector3ToBtVector3(ray_dir);
	btVector3* ray_originTemp = Math::Vector3ToBtVector3(ray_origin);
	btAlignedObjectArray<int>* collided_resultsTemp = new btAlignedObjectArray<int>();

	bool ret = _bvh->rayQuery(*ray_dirTemp, *ray_originTemp, *collided_resultsTemp);
	collided_results = gcnew IntArray(collided_resultsTemp);

	delete ray_dirTemp;
	delete ray_originTemp;

	return ret;
}

void GImpactBvh::SetNodeBound(int nodeIndex, Aabb^ bound)
{
	_bvh->setNodeBound(nodeIndex, *bound->UnmanagedPointer);
}

void GImpactBvh::Update()
{
	_bvh->update();
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
	GImpactBvh_GlobalBox(_bvh, aabb);
	return gcnew Aabb(aabb);
}

bool GImpactBvh::HasHierarchy::get()
{
	return _bvh->hasHierarchy();
}

bool GImpactBvh::IsTrimesh::get()
{
	return _bvh->isTrimesh();
}

int GImpactBvh::NodeCount::get()
{
	return _bvh->getNodeCount();
}

PrimitiveManagerBase^ GImpactBvh::PrimitiveManager::get()
{
	return gcnew PrimitiveManagerBase(_bvh->getPrimitiveManager());
}
void GImpactBvh::PrimitiveManager::set(PrimitiveManagerBase^ value)
{
	_bvh->setPrimitiveManager(value->UnmanagedPointer);
}

btGImpactBvh* GImpactBvh::UnmanagedPointer::get()
{
	return _bvh;
}
void GImpactBvh::UnmanagedPointer::set(btGImpactBvh* value)
{
	_bvh = value;
}

#endif
#endif
