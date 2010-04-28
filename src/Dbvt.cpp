#include "StdAfx.h"

#ifndef DISABLE_DBVT

#include "AlignedObjectArray.h"
#include "Dbvt.h"
#include "DbvtBroadphase.h"

// Unmanaged functions to let us use unmanaged classes
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
	delete c;
	delete e;
}
void DbvtAabbMm_FromCR(btDbvtAabbMm* out, btVector3* c, btScalar r)
{
	*out = btDbvtAabbMm::FromCR(*c, r);
	delete c;
}
void DbvtAabbMm_FromMM(btDbvtAabbMm* out, btVector3* mi, btVector3* mx)
{
	*out = btDbvtAabbMm::FromMM(*mi, *mx);
	delete mi;
	delete mx;
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
	_aabbMm = aabbMm;
}

Vector3 DbvtAabbMm::Center()
{
	btVector3* center = new btVector3;
	DbvtAabbMm_Center(_aabbMm, center);
	Vector3 v = Math::BtVector3ToVector3(center);
	delete center;
	return v;
}

Vector3 DbvtAabbMm::Lengths()
{
	btVector3* lengths = new btVector3;
	DbvtAabbMm_Center(_aabbMm, lengths);
	Vector3 v = Math::BtVector3ToVector3(lengths);
	delete lengths;
	return v;
}

Vector3 DbvtAabbMm::Extents()
{
	btVector3* extents = new btVector3;
	DbvtAabbMm_Center(_aabbMm, extents);
	Vector3 v = Math::BtVector3ToVector3(extents);
	delete extents;
	return v;
}

Vector3 DbvtAabbMm::Mins()
{
	btVector3* mins = new btVector3;
	DbvtAabbMm_Center(_aabbMm, mins);
	Vector3 v = Math::BtVector3ToVector3(mins);
	delete mins;
	return v;
}

Vector3 DbvtAabbMm::Maxs()
{
	btVector3* maxs = new btVector3;
	DbvtAabbMm_Center(_aabbMm, maxs);
	Vector3 v = Math::BtVector3ToVector3(maxs);
	delete maxs;
	return v;
}

DbvtAabbMm^ DbvtAabbMm::FromCE(Vector3 c, Vector3 e)
{
	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromCE(aabbMm, Math::Vector3ToBtVector3(c), Math::Vector3ToBtVector3(e));
	return gcnew DbvtAabbMm(aabbMm);
}

DbvtAabbMm^ DbvtAabbMm::FromCR(Vector3 c, btScalar r)
{
	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromCR(aabbMm, Math::Vector3ToBtVector3(c), r);
	return gcnew DbvtAabbMm(aabbMm);
}

DbvtAabbMm^ DbvtAabbMm::FromMM(Vector3 mi, Vector3 mx)
{
	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromMM(aabbMm, Math::Vector3ToBtVector3(mi), Math::Vector3ToBtVector3(mx));
	return gcnew DbvtAabbMm(aabbMm);
}

DbvtAabbMm^ DbvtAabbMm::FromPoints(array<Vector3>^ pts)
{
	btVector3* pointsTemp = new btVector3[pts->Length];
	for(int i=0; i<pts->Length; i++)
		BulletSharp::Math::Vector3ToBtVector3(pts[i], &pointsTemp[i]);

	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromPoints(aabbMm, pointsTemp, pts->Length);
	delete[] pointsTemp;
	return gcnew DbvtAabbMm(aabbMm);
}

void DbvtAabbMm::Expand(Vector3 e)
{
	btVector3* eTemp = Math::Vector3ToBtVector3(e);
	_aabbMm->Expand(*eTemp);
	delete eTemp;
}

void DbvtAabbMm::SignedExpand(Vector3 e)
{
	btVector3* eTemp = Math::Vector3ToBtVector3(e);
	_aabbMm->SignedExpand(*eTemp);
	delete eTemp;
}

bool DbvtAabbMm::Contain(DbvtAabbMm^ a)
{
	return _aabbMm->Contain(*a->UnmanagedPointer);
}

int DbvtAabbMm::Classify(Vector3 n, btScalar o, int s)
{
	btVector3* nTemp = Math::Vector3ToBtVector3(n);
	int ret =  _aabbMm->Classify(*nTemp, 0, s);
	delete nTemp;
	return ret;
}

btScalar DbvtAabbMm::ProjectMinimum(Vector3 v, unsigned signs)
{
	btVector3* vTemp = Math::Vector3ToBtVector3(v);
	btScalar ret = _aabbMm->ProjectMinimum(*vTemp, signs);
	delete vTemp;
	return ret;
}

btDbvtAabbMm* DbvtAabbMm::UnmanagedPointer::get()
{
	return _aabbMm;
}
void DbvtAabbMm::UnmanagedPointer::set(btDbvtAabbMm* value)
{
	_aabbMm = value;
}

DbvtVolume::DbvtVolume(btDbvtVolume* volume)
: DbvtAabbMm(volume)
{
}

btDbvtVolume* DbvtVolume::UnmanagedPointer::get()
{
	return (btDbvtVolume*)DbvtAabbMm::UnmanagedPointer;
}


DbvtNode::DbvtNode(btDbvtNode* node)
{
	_node = node;
}

array<DbvtNode^>^ DbvtNode::Childs::get()
{
	array<DbvtNode^>^ childs = gcnew array<DbvtNode^>(2);
	childs[0] = gcnew DbvtNode(_node->childs[0]);
	childs[1] = gcnew DbvtNode(_node->childs[1]);
	return childs;
}
void DbvtNode::Childs::set(array<DbvtNode^>^ value)
{
	_node->childs[0] = value[0]->UnmanagedPointer;
	_node->childs[1] = value[1]->UnmanagedPointer;
}

IntPtr DbvtNode::Data::get()
{
	return IntPtr(_node->data);
}
void DbvtNode::Data::set(IntPtr value)
{
	_node->data = value.ToPointer();
}

int DbvtNode::DataAsInt::get()
{
	return _node->dataAsInt;
}
void DbvtNode::DataAsInt::set(int value)
{
	_node->dataAsInt = value;
}

DbvtNode^ DbvtNode::Parent::get()
{
	return gcnew DbvtNode(_node->parent);
}
void DbvtNode::Parent::set(DbvtNode^ value)
{
	_node->parent = value->UnmanagedPointer;
}

DbvtVolume^ DbvtNode::Volume::get()
{
	return gcnew DbvtVolume(&_node->volume);
}
void DbvtNode::Volume::set(DbvtVolume^ value)
{
	DbvtNode_SetVolume(_node, value->UnmanagedPointer);
}

bool DbvtNode::IsInternal::get()
{
	return _node->isinternal();
}

bool DbvtNode::IsLeaf::get()
{
	return _node->isleaf();
}

btDbvtNode* DbvtNode::UnmanagedPointer::get()
{
	return _node;
}
void DbvtNode::UnmanagedPointer::set(btDbvtNode* value)
{
	_node = value;
}


Dbvt::ICollide::ICollide(btDbvt::ICollide* iCollide)
{
	_iCollide = iCollide;
}

Dbvt::ICollide::~ICollide()
{
	this->!ICollide();
}

Dbvt::ICollide::!ICollide()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_iCollide = NULL;
	
	OnDisposed( this, nullptr );
}

bool Dbvt::ICollide::AllLeaves(DbvtNode^ n)
{
	return _iCollide->AllLeaves(n->UnmanagedPointer);
}

bool Dbvt::ICollide::Descent(DbvtNode^ n)
{
	return _iCollide->Descent(n->UnmanagedPointer);
}

void Dbvt::ICollide::Process(DbvtNode^ n, btScalar s)
{
	_iCollide->Process(n->UnmanagedPointer, s);
}

void Dbvt::ICollide::Process(DbvtNode^ n)
{
	_iCollide->Process(n->UnmanagedPointer);
}

void Dbvt::ICollide::Process(DbvtNode^ na, DbvtNode^ nb)
{
	_iCollide->Process(na->UnmanagedPointer, na->UnmanagedPointer);
}

bool Dbvt::ICollide::IsDisposed::get()
{
	return (_iCollide == NULL);
}

btDbvt::ICollide* Dbvt::ICollide::UnmanagedPointer::get()
{
	return _iCollide;
}
void Dbvt::ICollide::UnmanagedPointer::set(btDbvt::ICollide* value)
{
	_iCollide = value;
}


Dbvt::IWriter::IWriter(btDbvt::IWriter* iWriter)
{
	_iWriter = iWriter;
}

Dbvt::IWriter::~IWriter()
{
	this->!IWriter();
}

Dbvt::IWriter::!IWriter()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_iWriter = NULL;
	
	OnDisposed( this, nullptr );
}

void Dbvt::IWriter::Prepare(DbvtNode^ root, int numnodes)
{
	_iWriter->Prepare(root->UnmanagedPointer, numnodes);
}

void Dbvt::IWriter::WriteLeaf(DbvtNode^ n, int index, int parent)
{
	_iWriter->WriteLeaf(n->UnmanagedPointer, index, parent);
}

void Dbvt::IWriter::WriteNode(DbvtNode^ n, int index, int parent, int child0, int child1)
{
	_iWriter->WriteNode(n->UnmanagedPointer, index, parent, child0, child1);
}

bool Dbvt::IWriter::IsDisposed::get()
{
	return (_iWriter == NULL);
}

btDbvt::IWriter* Dbvt::IWriter::UnmanagedPointer::get()
{
	return _iWriter;
}
void Dbvt::IWriter::UnmanagedPointer::set(btDbvt::IWriter* value)
{
	_iWriter = value;
}


Dbvt::IClone::IClone(btDbvt::IClone* iClone)
{
	_iClone = iClone;
}

Dbvt::IClone::~IClone()
{
	this->!IClone();
}

Dbvt::IClone::!IClone()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_iClone = NULL;
	
	OnDisposed( this, nullptr );
}

void Dbvt::IClone::CloneLeaf(DbvtNode^ n)
{
	_iClone->CloneLeaf(n->UnmanagedPointer);
}

bool Dbvt::IClone::IsDisposed::get()
{
	return (_iClone == NULL);
}

btDbvt::IClone* Dbvt::IClone::UnmanagedPointer::get()
{
	return _iClone;
}
void Dbvt::IClone::UnmanagedPointer::set(btDbvt::IClone* value)
{
	_iClone = value;
}


Dbvt::StkNn::StkNn(btDbvt::sStkNN* stkNn)
{
	_stkNn = stkNn;
}

Dbvt::StkNn::StkNn()
{
	_stkNn = new btDbvt::sStkNN();
}

Dbvt::StkNn::StkNn(DbvtNode^ na, DbvtNode^ nb)
{
	_stkNn = new btDbvt::sStkNN(na->UnmanagedPointer, nb->UnmanagedPointer);
}

btDbvt::sStkNN* Dbvt::StkNn::UnmanagedPointer::get()
{
	return _stkNn;
}
void Dbvt::StkNn::UnmanagedPointer::set(btDbvt::sStkNN* value)
{
	_stkNn = value;
}


Dbvt::StkNp::StkNp(btDbvt::sStkNP* stkNp)
{
	_stkNp = stkNp;
}

Dbvt::StkNp::StkNp(DbvtNode^ n, unsigned m)
{
	_stkNp = new btDbvt::sStkNP(n->UnmanagedPointer, m);
}

btDbvt::sStkNP* Dbvt::StkNp::UnmanagedPointer::get()
{
	return _stkNp;
}
void Dbvt::StkNp::UnmanagedPointer::set(btDbvt::sStkNP* value)
{
	_stkNp = value;
}


Dbvt::StkNps::StkNps(btDbvt::sStkNPS* stkNps)
{
	_stkNps = stkNps;
}

Dbvt::StkNps::StkNps()
{
	_stkNps = new btDbvt::sStkNPS();
}

Dbvt::StkNps::StkNps(DbvtNode^ n, unsigned m, btScalar v)
{
	_stkNps = new btDbvt::sStkNPS(n->UnmanagedPointer, m, v);
}

btDbvt::sStkNPS* Dbvt::StkNps::UnmanagedPointer::get()
{
	return _stkNps;
}
void Dbvt::StkNps::UnmanagedPointer::set(btDbvt::sStkNPS* value)
{
	_stkNps = value;
}


Dbvt::StkCln::StkCln(btDbvt::sStkCLN* stkCln)
{
	_stkCln = stkCln;
}

Dbvt::StkCln::StkCln(DbvtNode^ na, DbvtNode^ nb)
{
	_stkCln = new btDbvt::sStkCLN(na->UnmanagedPointer, nb->UnmanagedPointer);
}

btDbvt::sStkCLN* Dbvt::StkCln::UnmanagedPointer::get()
{
	return _stkCln;
}
void Dbvt::StkCln::UnmanagedPointer::set(btDbvt::sStkCLN* value)
{
	_stkCln = value;
}


Dbvt::Dbvt()
{
	_dbvt = new btDbvt();
}

Dbvt::Dbvt(btDbvt* dbvt)
{
	_dbvt = dbvt;
}

Dbvt::~Dbvt()
{
	this->!Dbvt();
}

Dbvt::!Dbvt()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_dbvt = NULL;
	
	OnDisposed( this, nullptr );
}

int Dbvt::Allocate(IntArray^ ifree, StkNpsArray^ stock, StkNps^ value)
{
	return btDbvt::allocate(*ifree->UnmanagedPointer, *stock->UnmanagedPointer, *value->UnmanagedPointer);
}

void Dbvt::Benchmark()
{
	btDbvt::benchmark();
}

void Dbvt::Clear()
{
	_dbvt->clear();
}

void Dbvt::Clone(Dbvt^ dest, IClone^ iclone)
{
	_dbvt->clone(*dest->UnmanagedPointer, iclone->UnmanagedPointer);
}

void Dbvt::Clone(Dbvt^ dest)
{
	_dbvt->clone(*dest->UnmanagedPointer);
}

void Dbvt::CollideKdop(DbvtNode^ root, array<Vector3>^ normals,
	array<btScalar>^ offsets, int count, Dbvt::ICollide^ policy)
{
	btVector3* btNormals = new btVector3[normals->Length];
	btScalar* btOffsets = new btScalar[offsets->Length];

	for(int i=0; i<count; i++)
		BulletSharp::Math::Vector3ToBtVector3(normals[i], &btNormals[i]);
	for(int i=0; i<count; i++)
		btOffsets[i] = offsets[i];

	btDbvt::collideKDOP(root->UnmanagedPointer, btNormals, btOffsets,
		normals->Length, *policy->UnmanagedPointer);

	delete[] btNormals;
	delete[] btOffsets;
}

void Dbvt::CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets,
	Vector3 sortaxis, int count, ICollide^ policy, bool fullsort)
{
	btVector3* btNormals = new btVector3[normals->Length];
	btScalar* btOffsets = new btScalar[offsets->Length];

	for(int i=0; i<count; i++)
		BulletSharp::Math::Vector3ToBtVector3(normals[i], &btNormals[i]);
	for(int i=0; i<count; i++)
		btOffsets[i] = offsets[i];

	btVector3* sortaxisTemp = Math::Vector3ToBtVector3(sortaxis);

	btDbvt::collideOCL(root->UnmanagedPointer, btNormals, btOffsets, *sortaxisTemp,
		count, *policy->UnmanagedPointer, fullsort);

	delete[] btNormals;
	delete[] btOffsets;
	delete sortaxisTemp;
}

void Dbvt::CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets,
	Vector3 sortaxis, int count, ICollide^ policy)
{
	btVector3* btNormals = new btVector3[normals->Length];
	btScalar* btOffsets = new btScalar[offsets->Length];

	for(int i=0; i<count; i++)
		BulletSharp::Math::Vector3ToBtVector3(normals[i], &btNormals[i]);
	for(int i=0; i<count; i++)
		btOffsets[i] = offsets[i];

	btVector3* sortaxisTemp = Math::Vector3ToBtVector3(sortaxis);

	btDbvt::collideOCL(root->UnmanagedPointer, btNormals, btOffsets,
		*sortaxisTemp, count, *policy->UnmanagedPointer);

	delete[] btNormals;
	delete[] btOffsets;
	delete sortaxisTemp;
}

void Dbvt::CollideTT(DbvtNode^ root0, DbvtNode^ root1, ICollide^ policy)
{
	_dbvt->collideTT(root0->UnmanagedPointer, root1->UnmanagedPointer, *policy->UnmanagedPointer);
}

void Dbvt::CollideTTPersistentStack(DbvtNode^ root0, DbvtNode^ root1, ICollide^ policy)
{
	_dbvt->collideTTpersistentStack(root0->UnmanagedPointer,
		root1->UnmanagedPointer, *policy->UnmanagedPointer);
}

void Dbvt::CollideTU(DbvtNode^ root, ICollide^ policy)
{
	btDbvt::collideTU(root->UnmanagedPointer, *policy->UnmanagedPointer);
}

void Dbvt::CollideTV(DbvtNode^ root, DbvtVolume^ volume, ICollide^ policy)
{
	_dbvt->collideTV(root->UnmanagedPointer, *volume->UnmanagedPointer, *policy->UnmanagedPointer);
}

int Dbvt::CountLeaves(DbvtNode^ node)
{
	return btDbvt::countLeaves(node->UnmanagedPointer);
}

bool Dbvt::Empty()
{
	return _dbvt->empty();
}

void Dbvt::EnumLeaves(DbvtNode^ root, ICollide^ policy)
{
	btDbvt::enumLeaves(root->UnmanagedPointer, *policy->UnmanagedPointer);
}

void Dbvt::EnumNodes(DbvtNode^ root, ICollide^ policy)
{
	btDbvt::enumNodes(root->UnmanagedPointer, *policy->UnmanagedPointer);
}

void Dbvt::ExtractLeaves(DbvtNode^ node, DbvtNodeArray^ leaves)
{
	btDbvt::extractLeaves(node->UnmanagedPointer, *leaves->UnmanagedPointer);
}

DbvtNode^ Dbvt::Insert(DbvtVolume^ box, IntPtr data)
{
	return gcnew DbvtNode(_dbvt->insert(*box->UnmanagedPointer, data.ToPointer()));
}

int Dbvt::MaxDepth(DbvtNode^ node)
{
	return btDbvt::maxdepth(node->UnmanagedPointer);
}

int Dbvt::Nearest(array<int>^ i, StkNps^ a, btScalar v, int l, int h)
{
	int* bti = new int[i->Length];
	int j;
	for (j=0; j<i->Length; j++)
		bti[j] = i[j];
	return btDbvt::nearest(bti, a->UnmanagedPointer, v, l, h);
}

void Dbvt::OptimizeBottomUp()
{
	_dbvt->optimizeBottomUp();
}

void Dbvt::OptimizeIncremental(int passes)
{
	_dbvt->optimizeIncremental(passes);
}

void Dbvt::OptimizeTopDown(int bu_treshold)
{
	_dbvt->optimizeTopDown(bu_treshold);
}

void Dbvt::OptimizeTopDown()
{
	_dbvt->optimizeTopDown();
}

void Dbvt::RayTest(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo, ICollide^ policy)
{
	btVector3* rayFromTemp = Math::Vector3ToBtVector3(rayFrom);
	btVector3* rayToTemp = Math::Vector3ToBtVector3(rayTo);

	btDbvt::rayTest(root->UnmanagedPointer, *rayFromTemp, *rayToTemp, *policy->UnmanagedPointer);

	delete rayFromTemp;
	delete rayToTemp;
}

void Dbvt::RayTestInternal(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo,
	Vector3 rayDirectionInverse, array<unsigned int>^ signs,
	btScalar lambda_max, Vector3 aabbMin, Vector3 aabbMax, ICollide^ policy)
{
	unsigned int* btSigns = new unsigned int[3];
	btSigns[0] = signs[0];
	btSigns[1] = signs[1];
	btSigns[2] = signs[2];

	btVector3* rayFromTemp = Math::Vector3ToBtVector3(rayFrom);
	btVector3* rayToTemp = Math::Vector3ToBtVector3(rayTo);
	btVector3* rayDirectionInverseTemp = Math::Vector3ToBtVector3(rayDirectionInverse);
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	_dbvt->rayTestInternal(root->UnmanagedPointer, *rayFromTemp, *rayToTemp, *rayDirectionInverseTemp,
		btSigns, lambda_max, *aabbMinTemp, *aabbMaxTemp, *policy->UnmanagedPointer
	);

	delete rayFromTemp;
	delete rayToTemp;
	delete rayDirectionInverseTemp;
	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void Dbvt::Remove(DbvtNode^ leaf)
{
	_dbvt->remove(leaf->UnmanagedPointer);
}

bool Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume, btScalar margin)
{
	return _dbvt->update(leaf->UnmanagedPointer, *volume->UnmanagedPointer, margin);
}

bool Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity)
{
	return _dbvt->update(leaf->UnmanagedPointer, *volume->UnmanagedPointer, *Math::Vector3ToBtVector3(velocity));
}

bool Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity, btScalar margin)
{
	return _dbvt->update(leaf->UnmanagedPointer, *volume->UnmanagedPointer,
		*Math::Vector3ToBtVector3(velocity), margin);
}

void Dbvt::Update(DbvtNode^ leaf, DbvtVolume^ volume)
{
	_dbvt->update(leaf->UnmanagedPointer, *volume->UnmanagedPointer);
}

void Dbvt::Update(DbvtNode^ leaf, int lookahead)
{
	_dbvt->update(leaf->UnmanagedPointer, lookahead);
}

void Dbvt::Update(DbvtNode^ leaf)
{
	_dbvt->update(leaf->UnmanagedPointer);
}

void Dbvt::Write(IWriter^ iwriter)
{
	_dbvt->write(iwriter->UnmanagedPointer);
}

DbvtNode^ Dbvt::Free::get()
{
	if (_dbvt->m_free == nullptr)
		return nullptr;
	return gcnew DbvtNode(_dbvt->m_free);
}
void Dbvt::Free::set(DbvtNode^ value)
{
	_dbvt->m_free = value->UnmanagedPointer;
}

int Dbvt::Leaves::get()
{
	return _dbvt->m_leaves;
}
void Dbvt::Leaves::set(int value)
{
	_dbvt->m_leaves = value;
}

int Dbvt::Lkhd::get()
{
	return _dbvt->m_lkhd;
}
void Dbvt::Lkhd::set(int value)
{
	_dbvt->m_lkhd = value;
}

unsigned Dbvt::Opath::get()
{
	return _dbvt->m_opath;
}
void Dbvt::Opath::set(unsigned value)
{
	_dbvt->m_opath = value;
}

DbvtNode^ Dbvt::Root::get()
{
	if (_dbvt->m_root == nullptr)
		return nullptr;
	return gcnew DbvtNode(_dbvt->m_root);
}
void Dbvt::Root::set(DbvtNode^ value)
{
	_dbvt->m_root = value->UnmanagedPointer;
}

StkNnArray^ Dbvt::Stack::get()
{
	return gcnew StkNnArray(&_dbvt->m_stkStack);
}

void Dbvt::Stack::set(StkNnArray^ value)
{
	_dbvt->m_stkStack = *value->UnmanagedPointer;
}

bool Dbvt::IsDisposed::get()
{
	return (_dbvt == NULL);
}

btDbvt* Dbvt::UnmanagedPointer::get()
{
	return _dbvt;
}
void Dbvt::UnmanagedPointer::set(btDbvt* value)
{
	_dbvt = value;
}

#endif
