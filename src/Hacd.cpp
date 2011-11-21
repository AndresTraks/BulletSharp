#include "StdAfx.h"

#ifndef DISABLE_HACD

#include "Hacd.h"
#include "StringConv.h"

Hacd::Hacd::Hacd()
{
	_unmanaged = new HACD::HACD();
}

void Hacd::Hacd::Compute()
{
	_unmanaged->Compute();
}

bool Hacd::Hacd::GetCH(int numCH, [Out] array<Vector3>^% points, [Out] array<long>^% triangles)
{
	size_t nPoints = _unmanaged->GetNPointsCH(numCH);
	size_t nTriangles = _unmanaged->GetNTrianglesCH(numCH);

	HACD::Vec3<HACD::Real>* pointsCH = new HACD::Vec3<HACD::Real>[nPoints];
	HACD::Vec3<long>* trianglesCH = new HACD::Vec3<long>[nTriangles];

	bool ret = _unmanaged->GetCH(numCH, pointsCH, trianglesCH);

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
	return _unmanaged->GetNPointsCH(numCH);
}

int Hacd::Hacd::GetNTrianglesCH(int numCH)
{
	return _unmanaged->GetNTrianglesCH(numCH);
}

bool Hacd::Hacd::Save(String^ fileName, bool uniColor, long numCluster)
{
	const char* fileNameTemp = StringConv::ManagedToUnmanaged(fileName);
	bool ret = _unmanaged->Save(fileNameTemp, uniColor, numCluster);
	StringConv::FreeUnmanagedString(fileNameTemp);
	return ret;
}

bool Hacd::Hacd::Save(String^ fileName, bool uniColor)
{
	const char* fileNameTemp = StringConv::ManagedToUnmanaged(fileName);
	bool ret = _unmanaged->Save(fileNameTemp, uniColor);
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

	_unmanaged->SetPoints(_points);
	_unmanaged->SetNPoints(count);
}

void Hacd::Hacd::SetTriangles(ICollection<long>^ triangles)
{
	int count = triangles->Count, i = 0;

	_triangles = new HACD::Vec3<long>[count];
	IEnumerator<long>^ enumerator = triangles->GetEnumerator();
	while(enumerator->MoveNext())
	{
		_triangles[i] = enumerator->Current;
		i++;
	}

	_unmanaged->SetTriangles(_triangles);
	_unmanaged->SetNTriangles(count);
}

bool BulletSharp::Hacd::Hacd::AddExtraDistPoints::get()
{
	return _unmanaged->GetAddExtraDistPoints();
}
void BulletSharp::Hacd::Hacd::AddExtraDistPoints::set(bool value)
{
	return _unmanaged->SetAddExtraDistPoints(value);
}

bool BulletSharp::Hacd::Hacd::AddFacesPoints::get()
{
	return _unmanaged->GetAddFacesPoints();
}
void BulletSharp::Hacd::Hacd::AddFacesPoints::set(bool value)
{
	return _unmanaged->SetAddFacesPoints(value);
}

bool BulletSharp::Hacd::Hacd::AddNeighboursDistPoints::get()
{
	return _unmanaged->GetAddNeighboursDistPoints();
}
void BulletSharp::Hacd::Hacd::AddNeighboursDistPoints::set(bool value)
{
	return _unmanaged->SetAddNeighboursDistPoints(value);
}

double BulletSharp::Hacd::Hacd::CompacityWeight::get()
{
	return _unmanaged->GetCompacityWeight();
}
void BulletSharp::Hacd::Hacd::CompacityWeight::set(double value)
{
	return _unmanaged->SetCompacityWeight(value);
}

double BulletSharp::Hacd::Hacd::Concavity::get()
{
	return _unmanaged->GetConcavity();
}
void BulletSharp::Hacd::Hacd::Concavity::set(double value)
{
	return _unmanaged->SetConcavity(value);
}

int BulletSharp::Hacd::Hacd::NClusters::get()
{
	return _unmanaged->GetNClusters();
}
void BulletSharp::Hacd::Hacd::NClusters::set(int value)
{
	return _unmanaged->SetNClusters(value);
}

int BulletSharp::Hacd::Hacd::VerticesPerConvexHull::get()
{
	return _unmanaged->GetNVerticesPerCH();
}
void BulletSharp::Hacd::Hacd::VerticesPerConvexHull::set(int value)
{
	return _unmanaged->SetNVerticesPerCH(value);
}

double BulletSharp::Hacd::Hacd::VolumeWeight::get()
{
	return _unmanaged->GetVolumeWeight();
}
void BulletSharp::Hacd::Hacd::VolumeWeight::set(double value)
{
	return _unmanaged->SetVolumeWeight(value);
}

#endif