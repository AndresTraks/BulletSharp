#include "StdAfx.h"

#ifndef DISABLE_HACD

#include "Hacd.h"
#include "StringConv.h"

Hacd::~Hacd()
{
	this->!Hacd();
}

Hacd::!Hacd()
{
	if (_native == 0)
	{
		return;
	}

	const HACD::Vec3<HACD::Real>* pointsPtr = _native->GetPoints();
    if (pointsPtr)
    {
        delete[] pointsPtr;
        _native->SetPoints(0);
    }

    const HACD::Vec3<long>* trianglesPtr = _native->GetTriangles();
    if (trianglesPtr)
    {
        delete[] trianglesPtr;
        _native->SetTriangles(0);
    }

	delete _native;
	_native = NULL;
}

bool Hacd::CallbackFunctionUnmanaged(IntPtr msg, double progress, double globalConcavity, IntPtr n)
{
    String^ msg2 = Marshal::PtrToStringAnsi(msg);
    return _callbackFunction(msg2, progress, globalConcavity, n.ToInt32());
}

Hacd::Hacd()
{
	_native = new HACD::HACD();
}

bool Hacd::Compute(bool fullCH, bool exportDistPoints)
{
	return _native->Compute(fullCH, exportDistPoints);
}

bool Hacd::Compute(bool fullCH)
{
	return _native->Compute(fullCH);
}

bool Hacd::Compute()
{
	return _native->Compute();
}

void Hacd::DenormalizeData()
{
	_native->DenormalizeData();
}

bool Hacd::GetCH(int numCH, [Out] array<Vector3>^% points, [Out] array<long>^% triangles)
{
	size_t nPoints = _native->GetNPointsCH(numCH);
	size_t nTriangles = _native->GetNTrianglesCH(numCH);

	HACD::Vec3<HACD::Real>* pointsCH = new HACD::Vec3<HACD::Real>[nPoints];
	HACD::Vec3<long>* trianglesCH = new HACD::Vec3<long>[nTriangles];

	bool ret = _native->GetCH(numCH, pointsCH, trianglesCH);

	if (!ret)
	{
		//points = nullptr;
		//triangles = nullptr;
		return false;
	}

	points = gcnew array<Vector3>(nPoints);
	triangles = gcnew array<long>(nTriangles*3);

	// points
	for(size_t v = 0; v < nPoints; v++)
	{
		points[v] = Vector3(pointsCH[v].X(), pointsCH[v].Y(), pointsCH[v].Z());
	}
	// triangles
	for(size_t f = 0; f < nTriangles; f++)
	{
		triangles[3*f] = trianglesCH[f].X();
		triangles[3*f+1] = trianglesCH[f].Y();
		triangles[3*f+2] = trianglesCH[f].Z();
	}

	delete [] pointsCH;
	delete [] trianglesCH;

	return ret;
}

int Hacd::GetNPointsCH(int numCH)
{
	return _native->GetNPointsCH(numCH);
}

int Hacd::GetNTrianglesCH(int numCH)
{
	return _native->GetNTrianglesCH(numCH);
}

array<HACD::Real>^ Hacd::GetPoints()
{
    const HACD::Vec3<HACD::Real>* pointsPtr = _native->GetPoints();
    int pointsLen = NPoints * 3;
    if (pointsLen == 0 || pointsPtr == 0)
    {
        return gcnew array<double>(0);
    }
    array<HACD::Real>^ pointsArray = gcnew array<HACD::Real>(pointsLen);
    Marshal::Copy(IntPtr((void*)pointsPtr), pointsArray, 0, pointsLen);
    return pointsArray;
}

array<Int64>^ Hacd::GetTriangles()
{
    const HACD::Vec3<long>* trianglesPtr = _native->GetTriangles();
    int trianglesLen = NTriangles * 3;
    if (trianglesLen == 0 || trianglesPtr == 0)
    {
        return gcnew array<Int64>(0);
    }
    array<Int64>^ trianglesArray = gcnew array<Int64>(trianglesLen);
    Marshal::Copy(IntPtr((void*)trianglesPtr), trianglesArray, 0, trianglesLen);
    return trianglesArray;
}

void Hacd::NormalizeData()
{
	_native->NormalizeData();
}

bool Hacd::Save(String^ fileName, bool uniColor, long numCluster)
{
	const char* fileNameTemp = StringConv::ManagedToUnmanaged(fileName);
	bool ret = _native->Save(fileNameTemp, uniColor, numCluster);
	StringConv::FreeUnmanagedString(fileNameTemp);
	return ret;
}

bool Hacd::Save(String^ fileName, bool uniColor)
{
	const char* fileNameTemp = StringConv::ManagedToUnmanaged(fileName);
	bool ret = _native->Save(fileNameTemp, uniColor);
	StringConv::FreeUnmanagedString(fileNameTemp);
	return ret;
}

bool Hacd::AddExtraDistPoints::get()
{
	return _native->GetAddExtraDistPoints();
}
void Hacd::AddExtraDistPoints::set(bool addExtraDistPoints)
{
	_native->SetAddExtraDistPoints(addExtraDistPoints);
}

bool Hacd::AddFacesPoints::get()
{
	return _native->GetAddFacesPoints();
}
void Hacd::AddFacesPoints::set(bool addFacesPoints)
{
	_native->SetAddFacesPoints(addFacesPoints);
}

bool Hacd::AddNeighboursDistPoints::get()
{
	return _native->GetAddNeighboursDistPoints();
}
void Hacd::AddNeighboursDistPoints::set(bool addNeighboursDistPoints)
{
	_native->SetAddNeighboursDistPoints(addNeighboursDistPoints);
}

void Hacd::SetPoints(ICollection<HACD::Real>^ points)
{
	array<HACD::Real>^ pointsArray = dynamic_cast<array<HACD::Real>^>(points);
    int arrayLen = points->Count;
    if (!pointsArray)
    {
        pointsArray = gcnew array<HACD::Real>(arrayLen);
        points->CopyTo(pointsArray, 0);
    }

    HACD::Vec3<HACD::Real>* pointsPtr = (HACD::Vec3<HACD::Real>*)_native->GetPoints();
    if (pointsPtr)
    {
        delete[] pointsPtr;
    }

    int nPoints = arrayLen / 3;
    pointsPtr = new HACD::Vec3<HACD::Real>[nPoints];
    Marshal::Copy(pointsArray, 0, IntPtr(pointsPtr), arrayLen);
    _native->SetPoints(pointsPtr);
    _native->SetNPoints(nPoints);
}

void Hacd::SetPoints(ICollection<Vector3>^ points)
{
	int nPoints = points->Count, i = 0;

	_points = new HACD::Vec3<HACD::Real>[nPoints];
	for each(Vector3 point in points)
	{
		_points[i++] = HACD::Vec3<HACD::Real>(Vector_X(point), Vector_Y(point), Vector_Z(point));
	}

	_native->SetPoints(_points);
	_native->SetNPoints(nPoints);
}

void Hacd::SetTriangles(ICollection<long>^ triangles)
{
	int count = triangles->Count, i = 0;

	_triangles = new HACD::Vec3<long>[count];
	IEnumerator<long>^ enumerator = triangles->GetEnumerator();
	while(enumerator->MoveNext())
	{
		long x = enumerator->Current;
		enumerator->MoveNext();
		long y = enumerator->Current;
		enumerator->MoveNext();
		long z = enumerator->Current;
		_triangles[i++] = HACD::Vec3<long>(x, y, z);
	}

	_native->SetTriangles(_triangles);
	_native->SetNTriangles(count / 3);
}

void Hacd::SetTriangles(ICollection<int>^ triangles)
{
	int count = triangles->Count, i = 0;

	_triangles = new HACD::Vec3<long>[count];
	IEnumerator<int>^ enumerator = triangles->GetEnumerator();
	while(enumerator->MoveNext())
	{
		int x = enumerator->Current;
		enumerator->MoveNext();
		int y = enumerator->Current;
		enumerator->MoveNext();
		int z = enumerator->Current;
		_triangles[i++] = HACD::Vec3<long>(x, y, z);
	}

	_native->SetTriangles(_triangles);
	_native->SetNTriangles(count / 3);
}

Hacd::CallBackFunction^ Hacd::CallBack::get()
{
    return _callbackFunction;
}
void Hacd::CallBack::set(CallBackFunction^ callBack)
{
    if (!_callbackFunctionUnmanaged)
    {
        _callbackFunctionUnmanaged = gcnew CallbackFunctionUnmanagedDelegate(this, &Hacd::CallbackFunctionUnmanaged);
    }
    _callbackFunction = callBack;
    if (_callbackFunction)
    {
        _native->SetCallBack((HACD::CallBackFunction)Marshal::GetFunctionPointerForDelegate(_callbackFunctionUnmanaged).ToPointer());
    }
    else
    {
        _native->SetCallBack(0);
    }
}

double Hacd::CompacityWeight::get()
{
	return _native->GetCompacityWeight();
}
void Hacd::CompacityWeight::set(double alpha)
{
	_native->SetCompacityWeight(alpha);
}

double Hacd::Concavity::get()
{
	return _native->GetConcavity();
}
void Hacd::Concavity::set(double concavity)
{
	_native->SetConcavity(concavity);
}

double Hacd::ConnectDist::get()
{
	return _native->GetConnectDist();
}
void Hacd::ConnectDist::set(double ccConnectDist)
{
	_native->SetConnectDist(ccConnectDist);
}

int Hacd::NClusters::get()
{
	return _native->GetNClusters();
}
void Hacd::NClusters::set(int nClusters)
{
	_native->SetNClusters(nClusters);
}

int Hacd::NPoints::get()
{
	return _native->GetNPoints();
}
void Hacd::NPoints::set(int nPoints)
{
	_native->SetNPoints(nPoints);
}

int Hacd::NTriangles::get()
{
	return _native->GetNTriangles();
}
void Hacd::NTriangles::set(int nTriangles)
{
	_native->SetNTriangles(nTriangles);
}

int Hacd::NumVerticesPerConvexHull::get()
{
	return _native->GetNVerticesPerCH();
}
void Hacd::NumVerticesPerConvexHull::set(int nVerticesPerCH)
{
	_native->SetNVerticesPerCH(nVerticesPerCH);
}
/*
LongArray Hacd::Partition::get()
{
	return _native->GetPartition();
}
*/
double Hacd::ScaleFactor::get()
{
	return _native->GetScaleFactor();
}
void Hacd::ScaleFactor::set(double scale)
{
	_native->SetScaleFactor(scale);
}

double Hacd::VolumeWeight::get()
{
	return _native->GetVolumeWeight();
}
void Hacd::VolumeWeight::set(double beta)
{
	_native->SetVolumeWeight(beta);
}

#endif
