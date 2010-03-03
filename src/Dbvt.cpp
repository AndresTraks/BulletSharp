#include "StdAfx.h"

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
	_aabbMm = aabbMm;
}

Vector3 DbvtAabbMm::Center()
{
	btVector3* center = new btVector3;
	DbvtAabbMm_Center(_aabbMm, center);
	Vector3 v = Math::BtVec3ToVector3(center);
	delete center;
	return v;
}

Vector3 DbvtAabbMm::Lengths()
{
	btVector3* lengths = new btVector3;
	DbvtAabbMm_Center(_aabbMm, lengths);
	Vector3 v = Math::BtVec3ToVector3(lengths);
	delete lengths;
	return v;
}

Vector3 DbvtAabbMm::Extents()
{
	btVector3* extents = new btVector3;
	DbvtAabbMm_Center(_aabbMm, extents);
	Vector3 v = Math::BtVec3ToVector3(extents);
	delete extents;
	return v;
}

Vector3 DbvtAabbMm::Mins()
{
	btVector3* mins = new btVector3;
	DbvtAabbMm_Center(_aabbMm, mins);
	Vector3 v = Math::BtVec3ToVector3(mins);
	delete mins;
	return v;
}

Vector3 DbvtAabbMm::Maxs()
{
	btVector3* maxs = new btVector3;
	DbvtAabbMm_Center(_aabbMm, maxs);
	Vector3 v = Math::BtVec3ToVector3(maxs);
	delete maxs;
	return v;
}

DbvtAabbMm^ DbvtAabbMm::FromCE(Vector3 c, Vector3 e)
{
	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromCE(aabbMm, Math::Vector3ToBtVec3(c), Math::Vector3ToBtVec3(e));
	return gcnew DbvtAabbMm(aabbMm);
}

DbvtAabbMm^ DbvtAabbMm::FromCR(Vector3 c, btScalar r)
{
	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromCR(aabbMm, Math::Vector3ToBtVec3(c), r);
	return gcnew DbvtAabbMm(aabbMm);
}

DbvtAabbMm^ DbvtAabbMm::FromMM(Vector3 mi, Vector3 mx)
{
	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromMM(aabbMm, Math::Vector3ToBtVec3(mi), Math::Vector3ToBtVec3(mx));
	return gcnew DbvtAabbMm(aabbMm);
}

DbvtAabbMm^ DbvtAabbMm::FromPoints(array<Vector3>^ pts)
{
	btVector3* btPoints = new btVector3[pts->Length];
	for(int i=0; i<pts->Length; i++)
		BulletSharp::Math::Vector3ToBtVec3(pts[i], &btPoints[i]);

	btDbvtAabbMm* aabbMm = new btDbvtAabbMm;
	DbvtAabbMm_FromPoints(aabbMm, btPoints, pts->Length);
	return gcnew DbvtAabbMm(aabbMm);
}

void DbvtAabbMm::Expand(Vector3 e)
{
	_aabbMm->Expand(*Math::Vector3ToBtVec3(e));
}

void DbvtAabbMm::SignedExpand(Vector3 e)
{
	_aabbMm->SignedExpand(*Math::Vector3ToBtVec3(e));
}

bool DbvtAabbMm::Contain(DbvtAabbMm^ a)
{
	return _aabbMm->Contain(*a->UnmanagedPointer);
}

int DbvtAabbMm::Classify(Vector3 n, btScalar o, int s)
{
	return _aabbMm->Classify(*Math::Vector3ToBtVec3(n), 0, s);
}

btScalar DbvtAabbMm::ProjectMinimum(Vector3 v, unsigned signs)
{
	return _aabbMm->ProjectMinimum(*Math::Vector3ToBtVec3(v), signs);
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


btDbvt::sStkNN* Dbvt::StkNn::UnmanagedPointer::get()
{
	return _stkNn;
}
void Dbvt::StkNn::UnmanagedPointer::set(btDbvt::sStkNN* value)
{
	_stkNn = value;
}


btDbvt::sStkNP* Dbvt::StkNp::UnmanagedPointer::get()
{
	return _stkNp;
}
void Dbvt::StkNp::UnmanagedPointer::set(btDbvt::sStkNP* value)
{
	_stkNp = value;
}


btDbvt::sStkNPS* Dbvt::StkNps::UnmanagedPointer::get()
{
	return _stkNps;
}
void Dbvt::StkNps::UnmanagedPointer::set(btDbvt::sStkNPS* value)
{
	_stkNps = value;
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

int Dbvt::Allocate(array<int>^ ifree, array<StkNps^>^ stock, StkNps^ value)
{
	btAlignedObjectArray<int> btIFree = btAlignedObjectArray<int>();
	btAlignedObjectArray<btDbvt::sStkNPS> btStock = btAlignedObjectArray<btDbvt::sStkNPS>();
	for each(int ifree_v in ifree)
		btIFree.push_back(ifree_v);
	for each(StkNps^ stock_v in stock)
		btStock.push_back(*stock_v->UnmanagedPointer);


	return btDbvt::allocate(btIFree, btStock, *value->UnmanagedPointer);
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
		BulletSharp::Math::Vector3ToBtVec3(normals[i], &btNormals[i]);
	for(int i=0; i<count; i++)
		btOffsets[i] = offsets[i];

	btDbvt::collideKDOP(root->UnmanagedPointer, btNormals, btOffsets,
		normals->Length, *policy->UnmanagedPointer);
}

void Dbvt::CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets,
	Vector3 sortaxis, int count, ICollide^ policy, bool fullsort)
{
	btVector3* btNormals = new btVector3[normals->Length];
	btScalar* btOffsets = new btScalar[offsets->Length];

	for(int i=0; i<count; i++)
		BulletSharp::Math::Vector3ToBtVec3(normals[i], &btNormals[i]);
	for(int i=0; i<count; i++)
		btOffsets[i] = offsets[i];

	btDbvt::collideOCL(root->UnmanagedPointer, btNormals, btOffsets, *Math::Vector3ToBtVec3(sortaxis),
		count, *policy->UnmanagedPointer, fullsort);
}

void Dbvt::CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets,
	Vector3 sortaxis, int count, ICollide^ policy)
{
	btVector3* btNormals = new btVector3[normals->Length];
	btScalar* btOffsets = new btScalar[offsets->Length];

	for(int i=0; i<count; i++)
		BulletSharp::Math::Vector3ToBtVec3(normals[i], &btNormals[i]);
	for(int i=0; i<count; i++)
		btOffsets[i] = offsets[i];

	btDbvt::collideOCL(root->UnmanagedPointer, btNormals, btOffsets,
		*Math::Vector3ToBtVec3(sortaxis), count, *policy->UnmanagedPointer);
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
