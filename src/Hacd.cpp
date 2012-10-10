#include "StdAfx.h"

#ifndef DISABLE_HACD

#include "Hacd.h"
#include "StringConv.h"

Hacd::Hacd::Hacd()
{
	_native = new HACD::HACD();
}

bool Hacd::Hacd::Compute(bool fullCH, bool exportDistPoints)
{
	return _native->Compute(fullCH, exportDistPoints);
}

bool Hacd::Hacd::Compute(bool fullCH)
{
	return _native->Compute(fullCH);
}

bool Hacd::Hacd::Compute()
{
	return _native->Compute();
}

void Hacd::Hacd::DenormalizeData()
{
	return _native->DenormalizeData();
}

bool Hacd::Hacd::GetCH(int numCH, [Out] array<Vector3>^% points, [Out] array<long>^% triangles)
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

int Hacd::Hacd::GetNPointsCH(int numCH)
{
	return _native->GetNPointsCH(numCH);
}

int Hacd::Hacd::GetNTrianglesCH(int numCH)
{
	return _native->GetNTrianglesCH(numCH);
}

void Hacd::Hacd::NormalizeData()
{
	return _native->NormalizeData();
}

bool Hacd::Hacd::Save(String^ fileName, bool uniColor, long numCluster)
{
	const char* fileNameTemp = StringConv::ManagedToUnmanaged(fileName);
	bool ret = _native->Save(fileNameTemp, uniColor, numCluster);
	StringConv::FreeUnmanagedString(fileNameTemp);
	return ret;
}

bool Hacd::Hacd::Save(String^ fileName, bool uniColor)
{
	const char* fileNameTemp = StringConv::ManagedToUnmanaged(fileName);
	bool ret = _native->Save(fileNameTemp, uniColor);
	StringConv::FreeUnmanagedString(fileNameTemp);
	return ret;
}

void Hacd::Hacd::SetPoints(ICollection<Vector3>^ points)
{
	int count = points->Count, i = 0;

	_points = new HACD::Vec3<HACD::Real>[count];
	IEnumerator<Vector3>^ enumerator = points->GetEnumerator();
	while(enumerator->MoveNext())
	{
		Vector3 point = enumerator->Current;
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
		_points[i] = HACD::Vec3<HACD::Real>(point.x, point.y, point.z);
#else
		_points[i] = HACD::Vec3<HACD::Real>(point.X, point.Y, point.Z);
#endif
		i++;
	}

	_native->SetPoints(_points);
	_native->SetNPoints(count);
}

void Hacd::Hacd::SetTriangles(ICollection<long>^ triangles)
{
	int count = triangles->Count, i = 0;

	_triangles = new HACD::Vec3<long>[count];
	IEnumerator<long>^ enumerator = triangles->GetEnumerator();
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

bool BulletSharp::Hacd::Hacd::AddExtraDistPoints::get()
{
	return _native->GetAddExtraDistPoints();
}
void BulletSharp::Hacd::Hacd::AddExtraDistPoints::set(bool value)
{
	return _native->SetAddExtraDistPoints(value);
}

bool BulletSharp::Hacd::Hacd::AddFacesPoints::get()
{
	return _native->GetAddFacesPoints();
}
void BulletSharp::Hacd::Hacd::AddFacesPoints::set(bool value)
{
	return _native->SetAddFacesPoints(value);
}

bool BulletSharp::Hacd::Hacd::AddNeighboursDistPoints::get()
{
	return _native->GetAddNeighboursDistPoints();
}
void BulletSharp::Hacd::Hacd::AddNeighboursDistPoints::set(bool value)
{
	return _native->SetAddNeighboursDistPoints(value);
}

double BulletSharp::Hacd::Hacd::CompacityWeight::get()
{
	return _native->GetCompacityWeight();
}
void BulletSharp::Hacd::Hacd::CompacityWeight::set(double value)
{
	return _native->SetCompacityWeight(value);
}

double BulletSharp::Hacd::Hacd::Concavity::get()
{
	return _native->GetConcavity();
}
void BulletSharp::Hacd::Hacd::Concavity::set(double value)
{
	return _native->SetConcavity(value);
}

double BulletSharp::Hacd::Hacd::ConnectDist::get()
{
	return _native->GetConnectDist();
}
void BulletSharp::Hacd::Hacd::ConnectDist::set(double value)
{
	return _native->SetConnectDist(value);
}

int BulletSharp::Hacd::Hacd::NClusters::get()
{
	return _native->GetNClusters();
}
void BulletSharp::Hacd::Hacd::NClusters::set(int value)
{
	return _native->SetNClusters(value);
}

int BulletSharp::Hacd::Hacd::NPoints::get()
{
	return _native->GetNPoints();
}

int BulletSharp::Hacd::Hacd::VerticesPerConvexHull::get()
{
	return _native->GetNVerticesPerCH();
}
void BulletSharp::Hacd::Hacd::VerticesPerConvexHull::set(int value)
{
	return _native->SetNVerticesPerCH(value);
}

double BulletSharp::Hacd::Hacd::VolumeWeight::get()
{
	return _native->GetVolumeWeight();
}
void BulletSharp::Hacd::Hacd::VolumeWeight::set(double value)
{
	return _native->SetVolumeWeight(value);
}

double BulletSharp::Hacd::Hacd::ScaleFactor::get()
{
	return _native->GetScaleFactor();
}
void BulletSharp::Hacd::Hacd::ScaleFactor::set(double value)
{
	return _native->SetScaleFactor(value);
}

#endif