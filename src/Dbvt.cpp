#include "StdAfx.h"

#ifndef DISABLE_DBVT

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "Dbvt.h"
#include "DbvtBroadphase.h"

// Native functions to let us use unmanaged classes
#pragma managed(push, off)
void DbvtAabbMm_Center(btDbvtAabbMm* aabbMm, btVector3* center)
{
	*center = aabbMm->Center();
}
void DbvtAabbMm_Lengths(btDbvtAabbMm* aabbMm, btVector3* lengths)
{
	*lengths = aabbMm->Lengths();
}
void DbvtAabbMm_Extents(btDbvtAabbMm* aabbMm, btVector3* extents)
{
	*extents = aabbMm->Extents();
}
void DbvtAabbMm_Mins(btDbvtAabbMm* aabbMm, btVector3* mins)
{
	*mins = aabbMm->Mins();
}
void DbvtAabbMm_Maxs(btDbvtAabbMm* aabbMm, btVector3* maxs)
{
	*maxs = aabbMm->Maxs();
}
void DbvtAabbMm_FromCE(btDbvtAabbMm* out, btVector3* c, btVector3* e)
{
	*out = btDbvtAabbMm::FromCE(*c, *e);
}
void DbvtAabbMm_FromCR(btDbvtAabbMm* out, btVector3* c, btScalar r)
{
	*out = btDbvtAabbMm::FromCR(*c, r);
}
void DbvtAabbMm_FromMM(btDbvtAabbMm* out, btVector3* mi, btVector3* mx)
{
	*out = btDbvtAabbMm::FromMM(*mi, *mx);
}
void DbvtAabbMm_FromPoints(btDbvtAabbMm* out, btVector3* pts, int n)
{
	*out = btDbvtAabbMm::FromPoints(pts, n);
}

void DbvtNode_SetVolume(btDbvtNode* node, btDbvtVolume* volume)
{
	node->volume = *volume;
}
#pragma managed(pop)

DbvtAabbMm::DbvtAabbMm(btDbvtAabbMm* aabbMm)
{
	_native = aabbMm;
}

Vector3 DbvtAabbMm::Center()
{
	btVector3* center = new btVector3;
	DbvtAabbMm_Center(_native, center);
	Vector3 v = Math::BtVector3ToVector3(center);
	delete center;
	return v;
}

Vector3 DbvtAabbMm::Lengths()
{
	btVector3* lengths = new btVector3;
	DbvtAabbMm_Center(_native, lengths);
	Vector3 v = Math::BtVector3ToVector3(lengths);
	delete lengths;
	return v;
}

Vector3 DbvtAabbMm::Extents()
{
	btVector3* extents = new btVector3;
	DbvtAabbMm_Center(_native, extents);
	Vector3 v = Math::BtVector3ToVector3(extents);
	delete extents;
	return v;
}

Vector3 DbvtAabbMm::Mins()
{
	btVector3* mins = new btVector3;
	DbvtAabbMm_Center(_native, mins);
	Vector3 v = Math::BtVector3ToVector3(mins);
	delete mins;
	return v;
}

Vector3 DbvtAabbMm::Maxs()
{
	btVector3* maxs = new btVector3;
	DbvtAabbMm_Center(_native, maxs);
	Vector3 v = Math::BtVector3ToVector3(maxs);
	delete maxs;
	return v;
}

DbvtAabbMm^ DbvtAabbMm::FromCE(Vector3 c, Vector3 e)
{
	VECTOR3_DEF(c);
	VECTOR3_DEF(e);

	btDbvtAabbMm* aabbMmTemp = new btDbvtAabbMm;
	DbvtAabbMm_FromCE(aabbMmTemp, VECTOR3_PTR(c), VECTOR3_PTR(e));
	DbvtAabbMm^ aabbMm = gcnew DbvtAabbMm(aabbMmTemp);

	VECTOR3_DEL(c);
	VECTOR3_DEL(e);

	return aabbMm;
}

DbvtAabbMm^ DbvtAabbMm::FromCR(Vector3 c, btScalar r)
{
	VECTOR3_DEF(c);

	btDbvtAabbMm* aabbMmTemp = new btDbvtAabbMm;
	DbvtAabbMm_FromCR(aabbMmTemp, VECTOR3_PTR(c), r);
	DbvtAabbMm^ aabbMm = gcnew DbvtAabbMm(aabbMmTemp);

	VECTOR3_DEL(c);

	return aabbMm;
}

DbvtAabbMm^ DbvtAabbMm::FromMM(Vector3 mi, Vector3 mx)
{
	VECTOR3_DEF(mi);
	VECTOR3_DEF(mx);

	btDbvtAabbMm* aabbMmTemp = new btDbvtAabbMm;
	DbvtAabbMm_FromMM(aabbMmTemp, VECTOR3_PTR(mi), VECTOR3_PTR(mx));
	DbvtAabbMm^ aabbMm = gcnew DbvtAabbMm(aabbMmTemp);

	VECTOR3_DEL(mi);
	VECTOR3_DEL(mx);

	return aabbMm;
}

DbvtAabbMm^ DbvtAabbMm::FromPoints(array<Vector3>^ pts)
{
	btVector3* pointsTemp = Math::Vector3ArrayToUnmanaged(pts);
	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromPoints(aabbMm, pointsTemp, pts->Length);
	delete[] pointsTemp;
	return gcnew DbvtAabbMm(aabbMm);
}

void DbvtAabbMm::Expand(Vector3 e)
{
	VECTOR3_DEF(e);
	_native->Expand(VECTOR3_USE(e));
	VECTOR3_DEL(e);
}

void DbvtAabbMm::SignedExpand(Vector3 e)
{
	VECTOR3_DEF(e);
	_native->SignedExpand(VECTOR3_USE(e));
	VECTOR3_DEL(e);
}

bool DbvtAabbMm::Contain(DbvtAabbMm^ a)
{
	return _native->Contain(*a->_native);
}

int DbvtAabbMm::Classify(Vector3 n, btScalar o, int s)
{
	VECTOR3_DEF(n);
	int ret = _native->Classify(VECTOR3_USE(n), 0, s);
	VECTOR3_DEL(n);
	return ret;
}

btScalar DbvtAabbMm::ProjectMinimum(Vector3 v, unsigned signs)
{
	VECTOR3_DEF(v);
	btScalar ret = _native->ProjectMinimum(VECTOR3_USE(v), signs);
	VECTOR3_DEL(v);
	return ret;
}


DbvtVolume::DbvtVolume(btDbvtVolume* volume)
: DbvtAabbMm(volume)
{
}


DbvtNode::DbvtNode(btDbvtNode* node)
{
	_native = node;
}

DbvtNodePtrArray^ DbvtNode::Childs::get()
{
	return gcnew DbvtNodePtrArray(_native->childs, 2);
}

IntPtr DbvtNode::Data::get()
{
	return IntPtr(_native->data);
}
void DbvtNode::Data::set(IntPtr value)
{
	_native->data = value.ToPointer();
}

int DbvtNode::DataAsInt::get()
{
	return _native->dataAsInt;
}
void DbvtNode::DataAsInt::set(int value)
{
	_native->dataAsInt = value;
}

DbvtNode^ DbvtNode::Parent::get()
{
	if (_native->parent != 0)
		return nullptr;
	return gcnew DbvtNode(_native->parent);
}
void DbvtNode::Parent::set(DbvtNode^ value)
{
	_native->parent = GetUnmanagedNullable(value);
}

DbvtVolume^ DbvtNode::Volume::get()
{
	return gcnew DbvtVolume(&_native->volume);
}
void DbvtNode::Volume::set(DbvtVolume^ value)
{
	DbvtNode_SetVolume(_native, value->_native);
}

bool DbvtNode::IsInternal::get()
{
	return _native->isinternal();
}

bool DbvtNode::IsLeaf::get()
{
	return _native->isleaf();
}


Dbvt::ICollide::ICollide(btDbvt::ICollide* iCollide)
{
	_native = iCollide;
}

Dbvt::ICollide::~ICollide()
{
	this->!ICollide();
}

Dbvt::ICollide::!ICollide()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

bool Dbvt::ICollide::AllLeaves(DbvtNode^ n)
{
	return _native->AllLeaves(n->_native);
}

bool Dbvt::ICollide::Descent(DbvtNode^ n)
{
	return _native->Descent(n->_native);
}

void Dbvt::ICollide::Process(DbvtNode^ n, btScalar s)
{
	_native->Process(n->_native, s);
}

void Dbvt::ICollide::Process(DbvtNode^ n)
{
	_native->Process(n->_native);
}

void Dbvt::ICollide::Process(DbvtNode^ na, DbvtNode^ nb)
{
	_native->Process(na->_native, na->_native);
}

bool Dbvt::ICollide::IsDisposed::get()
{
	return (_native == NULL);
}


Dbvt::IWriter::IWriter(btDbvt::IWriter* iWriter)
{
	_native = iWriter;
}

Dbvt::IWriter::~IWriter()
{
	this->!IWriter();
}

Dbvt::IWriter::!IWriter()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

void Dbvt::IWriter::Prepare(DbvtNode^ root, int numnodes)
{
	_native->Prepare(root->_native, numnodes);
}

void Dbvt::IWriter::WriteLeaf(DbvtNode^ n, int index, int parent)
{
	_native->WriteLeaf(n->_native, index, parent);
}

void Dbvt::IWriter::WriteNode(DbvtNode^ n, int index, int parent, int child0, int child1)
{
	_native->WriteNode(n->_native, index, parent, child0, child1);
}

bool Dbvt::IWriter::IsDisposed::get()
{
	return (_native == NULL);
}


Dbvt::IClone::IClone(btDbvt::IClone* iClone)
{
	_native = iClone;
}

Dbvt::IClone::~IClone()
{
	this->!IClone();
}

Dbvt::IClone::!IClone()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

void Dbvt::IClone::CloneLeaf(DbvtNode^ n)
{
	_native->CloneLeaf(n->_native);
}

bool Dbvt::IClone::IsDisposed::get()
{
	return (_native == NULL);
}


Dbvt::StkNn::StkNn(btDbvt::sStkNN* stkNn)
{
	_native = stkNn;
}

Dbvt::StkNn::StkNn()
{
	_native = new btDbvt::sStkNN();
}

Dbvt::StkNn::StkNn(DbvtNode^ na, DbvtNode^ nb)
{
	_native = new btDbvt::sStkNN(na->_native, nb->_native);
}

DbvtNode^ Dbvt::StkNn::A::get()
{
	return gcnew DbvtNode((btDbvtNode*)_native->a);
}
void Dbvt::StkNn::A::set(DbvtNode^ value)
{
	_native->a = value->_native;
}

DbvtNode^ Dbvt::StkNn::B::get()
{
	return gcnew DbvtNode((btDbvtNode*)_native->b);
}
void Dbvt::StkNn::B::set(DbvtNode^ value)
{
	_native->b = value->_native;
}


Dbvt::StkNp::StkNp(btDbvt::sStkNP* stkNp)
{
	_native = stkNp;
}

Dbvt::StkNp::StkNp(DbvtNode^ n, unsigned m)
{
	_native = new btDbvt::sStkNP(n->_native, m);
}


Dbvt::StkNps::StkNps(btDbvt::sStkNPS* stkNps)
{
	_native = stkNps;
}

Dbvt::StkNps::StkNps()
{
	_native = new btDbvt::sStkNPS();
}

Dbvt::StkNps::StkNps(DbvtNode^ n, unsigned m, btScalar v)
{
	_native = new btDbvt::sStkNPS(n->_native, m, v);
}


Dbvt::StkCln::StkCln(btDbvt::sStkCLN* stkCln)
{
	_native = stkCln;
}

Dbvt::StkCln::StkCln(DbvtNode^ na, DbvtNode^ nb)
{
	_native = new btDbvt::sStkCLN(na->_native, nb->_native);
}


Dbvt::Dbvt()
{
	_native = new btDbvt();
}

Dbvt::Dbvt(btDbvt* dbvt)
{
	_native = dbvt;
}

Dbvt::~Dbvt()
{
	this->!Dbvt();
}

Dbvt::!Dbvt()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	_native = NULL;

	OnDisposed(this, nullptr);
}

int Dbvt::Allocate(AlignedIntArray^ ifree, AlignedStkNpsArray^ stock, StkNps^ value)
{
	return btDbvt::allocate(*((btAlignedObjectArray<int>*)ifree->_native), *((btAlignedObjectArray<btDbvt::sStkNPS>*)stock->_native), *value->_native);
}

void Dbvt::Benchmark()
{
	btDbvt::benchmark();
}

void Dbvt::Clear()
{
	_native->clear();
}

void Dbvt::Clone(Dbvt^ dest, IClone^ iclone)
{
	_native->clone(*dest->_native, iclone->_native);
}

void Dbvt::Clone(Dbvt^ dest)
{
	_native->clone(*dest->_native);
}

void Dbvt::CollideKdop(DbvtNode^ root, array<Vector3>^ normals,
	array<btScalar>^ offsets, int count, Dbvt::ICollide^ policy)
{
	btVector3* btNormals = Math::Vector3ArrayToUnmanaged(normals);
	btScalar* btOffsets = Math::BtScalarArrayToUnmanaged(offsets);

	btDbvt::collideKDOP(root->_native, btNormals, btOffsets, normals->Length, *policy->_native);

	delete[] btNormals;
	delete[] btOffsets;
}

void Dbvt::CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets,
	Vector3 sortaxis, int count, ICollide^ policy, bool fullsort)
{
	btVector3* btNormals = Math::Vector3ArrayToUnmanaged(normals);
	btScalar* btOffsets = Math::BtScalarArrayToUnmanaged(offsets);
	VECTOR3_DEF(sortaxis);

	btDbvt::collideOCL(root->_native, btNormals, btOffsets, VECTOR3_USE(sortaxis), count, *policy->_native, fullsort);

	delete[] btNormals;
	delete[] btOffsets;
	VECTOR3_DEL(sortaxis);
}

void Dbvt::CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets,
	Vector3 sortaxis, int count, ICollide^ policy)
{
	btVector3* btNormals = Math::Vector3ArrayToUnmanaged(normals);
	btScalar* btOffsets = Math::BtScalarArrayToUnmanaged(offsets, count);
	VECTOR3_DEF(sortaxis);

	btDbvt::collideOCL(root->_native, btNormals, btOffsets,
		VECTOR3_USE(sortaxis), count, *policy->_native);

	delete[] btNormals;
	delete[] btOffsets;
	VECTOR3_DEL(sortaxis);
}

void Dbvt::CollideTT(DbvtNode^ root0, DbvtNode^ root1, ICollide^ policy)
{
	_native->collideTT(root0->_native, root1->_native, *policy->_native);
}

void Dbvt::CollideTTPersistentStack(DbvtNode^ root0, DbvtNode^ root1, ICollide^ policy)
{
	_native->collideTTpersistentStack(root0->_native, root1->_native, *policy->_native);
}

void Dbvt::CollideTU(DbvtNode^ root, ICollide^ policy)
{
	btDbvt::collideTU(root->_native, *policy->_native);
}

void Dbvt::CollideTV(DbvtNode^ root, DbvtVolume^ volume, ICollide^ policy)
{
	_native->collideTV(root->_native, *volume->_native, *policy->_native);
}

int Dbvt::CountLeaves(DbvtNode^ node)
{
	return btDbvt::countLeaves(node->_native);
}

bool Dbvt::Empty()
{
	return _native->empty();
}

void Dbvt::EnumLeaves(DbvtNode^ root, ICollide^ policy)
{
	btDbvt::enumLeaves(root->_native, *policy->_native);
}

void Dbvt::EnumNodes(DbvtNode^ root, ICollide^ policy)
{
	btDbvt::enumNodes(root->_native, *policy->_native);
}

void Dbvt::ExtractLeaves(DbvtNode^ node, AlignedDbvtNodeArray^ leaves)
{
	btDbvt::extractLeaves(node->_native, *(btAlignedObjectArray<const btDbvtNode*>*)leaves->_native);
}

DbvtNode^ Dbvt::Insert(DbvtVolume^ box, IntPtr data)
{
	return gcnew DbvtNode(_native->insert(*box->_native, data.ToPointer()));
}

int Dbvt::MaxDepth(DbvtNode^ node)
{
	return btDbvt::maxdepth(node->_native);
}

int Dbvt::Nearest(array<int>^ i, StkNps^ a, btScalar v, int l, int h)
{
	pin_ptr<int> iPtr = &i[0];
	return btDbvt::nearest(iPtr, a->_native, v, l, h);
}

void Dbvt::OptimizeBottomUp()
{
	_native->optimizeBottomUp();
}

void Dbvt::OptimizeIncremental(int passes)
{
	_native->optimizeIncremental(passes);
}

void Dbvt::OptimizeTopDown(int bu_treshold)
{
	_native->optimizeTopDown(bu_treshold);
}

void Dbvt::OptimizeTopDown()
{
	_native->optimizeTopDown();
}

void Dbvt::RayTest(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo, ICollide^ policy)
{
	VECTOR3_DEF(rayFrom);
	VECTOR3_DEF(rayTo);

	btDbvt::rayTest(root->_native, VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *policy->_native);

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

#ifndef DISABLE_INTERNAL
void Dbvt::RayTestInternal(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo,
	Vector3 rayDirectionInverse, array<unsigned int>^ signs,
	btScalar lambda_max, Vector3 aabbMin, Vector3 aabbMax, ICollide^ policy)
{
	unsigned int* btSigns = new unsigned int[3];
	btSigns[0] = signs[0];
	btSigns[1] = signs[1];
	btSigns[2] = signs[2];

	VECTOR3_DEF(rayFrom);
	VECTOR3_DEF(rayTo);
	VECTOR3_DEF(rayDirectionInverse);
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_native->rayTestInternal(root->_native, VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo),
		VECTOR3_USE(rayDirectionInverse), btSigns, lambda_max, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		*policy->_native);

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	VECTOR3_DEL(rayDirectionInverse);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}
#endif

void Dbvt::Remove(DbvtNode^ leaf)
{
	_native->remove(leaf->_native);
}

bool Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume, btScalar margin)
{
	return _native->update(leaf->_native, *volume->_native, margin);
}

bool Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity)
{
	VECTOR3_DEF(velocity);
	bool ret = _native->update(leaf->_native, *volume->_native, VECTOR3_USE(velocity));
	VECTOR3_DEL(velocity);
	return ret;
}

bool Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity, btScalar margin)
{
	VECTOR3_DEF(velocity);
	bool ret = _native->update(leaf->_native, *volume->_native, VECTOR3_USE(velocity), margin);
	VECTOR3_DEL(velocity);
	return ret;
}

void Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume)
{
	_native->update(leaf->_native, *volume->_native);
}

void Dbvt::Update(DbvtNode^ leaf, int lookahead)
{
	_native->update(leaf->_native, lookahead);
}

void Dbvt::Update(DbvtNode^ leaf)
{
	_native->update(leaf->_native);
}

void Dbvt::Write(IWriter^ iwriter)
{
	_native->write(iwriter->_native);
}

DbvtNode^ Dbvt::Free::get()
{
	if (_native->m_free == nullptr)
		return nullptr;
	return gcnew DbvtNode(_native->m_free);
}
void Dbvt::Free::set(DbvtNode^ value)
{
	_native->m_free = GetUnmanagedNullable(value);
}

int Dbvt::Leaves::get()
{
	return _native->m_leaves;
}
void Dbvt::Leaves::set(int value)
{
	_native->m_leaves = value;
}

int Dbvt::Lkhd::get()
{
	return _native->m_lkhd;
}
void Dbvt::Lkhd::set(int value)
{
	_native->m_lkhd = value;
}

unsigned Dbvt::Opath::get()
{
	return _native->m_opath;
}
void Dbvt::Opath::set(unsigned value)
{
	_native->m_opath = value;
}

DbvtNode^ Dbvt::Root::get()
{
	if (_native->m_root == nullptr)
		return nullptr;
	return gcnew DbvtNode(_native->m_root);
}
void Dbvt::Root::set(DbvtNode^ value)
{
	_native->m_root = GetUnmanagedNullable(value);
}

AlignedStkNnArray^ Dbvt::Stack::get()
{
	return gcnew AlignedStkNnArray(&_native->m_stkStack);
}

void Dbvt::Stack::set(AlignedStkNnArray^ value)
{
	_native->m_stkStack = *(btAlignedObjectArray<btDbvt::sStkNN>*)value->_native;
}

bool Dbvt::IsDisposed::get()
{
	return (_native == NULL);
}

#endif
