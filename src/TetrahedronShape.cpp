#include "StdAfx.h"

#include "TetrahedronShape.h"

BU_Simplex1to4::BU_Simplex1to4(btBU_Simplex1to4* shape)
: PolyhedralConvexAabbCachingShape(shape)
{
}

BU_Simplex1to4::BU_Simplex1to4()
: PolyhedralConvexAabbCachingShape(new btBU_Simplex1to4())
{
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0)
: PolyhedralConvexAabbCachingShape(0)
{
	btVector3* pt0Temp = Math::Vector3ToBtVector3(pt0);
	
	UnmanagedPointer = new btBU_Simplex1to4(*pt0Temp);
	
	delete pt0Temp;
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0, Vector3 pt1)
: PolyhedralConvexAabbCachingShape(0)
{
	btVector3* pt0Temp = Math::Vector3ToBtVector3(pt0);
	btVector3* pt1Temp = Math::Vector3ToBtVector3(pt1);
	
	UnmanagedPointer = new btBU_Simplex1to4(*pt0Temp, *pt1Temp);
	
	delete pt0Temp;
	delete pt1Temp;
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0, Vector3 pt1, Vector3 pt2)
: PolyhedralConvexAabbCachingShape(0)
{
	btVector3* pt0Temp = Math::Vector3ToBtVector3(pt0);
	btVector3* pt1Temp = Math::Vector3ToBtVector3(pt1);
	btVector3* pt2Temp = Math::Vector3ToBtVector3(pt2);
	
	UnmanagedPointer = new btBU_Simplex1to4(*pt0Temp, *pt1Temp, *pt2Temp);
	
	delete pt0Temp;
	delete pt1Temp;
	delete pt2Temp;
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0, Vector3 pt1, Vector3 pt2, Vector3 pt3)
: PolyhedralConvexAabbCachingShape(0)
{
	btVector3* pt0Temp = Math::Vector3ToBtVector3(pt0);
	btVector3* pt1Temp = Math::Vector3ToBtVector3(pt1);
	btVector3* pt2Temp = Math::Vector3ToBtVector3(pt2);
	btVector3* pt3Temp = Math::Vector3ToBtVector3(pt3);
	
	UnmanagedPointer = new btBU_Simplex1to4(*pt0Temp, *pt1Temp, *pt2Temp, *pt3Temp);
	
	delete pt0Temp;
	delete pt1Temp;
	delete pt2Temp;
	delete pt3Temp;
}

void BU_Simplex1to4::AddVertex(Vector3 pt)
{
	btVector3* ptTemp = Math::Vector3ToBtVector3(pt);
	UnmanagedPointer->addVertex(*ptTemp);
	delete ptTemp;
}

int BU_Simplex1to4::GetIndex(int i)
{
	return UnmanagedPointer->getIndex(i);
}

void BU_Simplex1to4::Reset()
{
	UnmanagedPointer->reset();
}

btBU_Simplex1to4* BU_Simplex1to4::UnmanagedPointer::get()
{
	return (btBU_Simplex1to4*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}
