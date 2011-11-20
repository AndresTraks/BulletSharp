#include "StdAfx.h"

#ifndef DISABLE_HACD

#include "Hacd.h"

Hacd::Hacd::Hacd()
{
	_unmanaged = new HACD::HACD();
}

void Hacd::Hacd::Compute()
{
	_unmanaged->Compute();
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

void Hacd::Hacd::SetTriangles(ICollection<int>^ triangles)
{
	int count = triangles->Count, i = 0;

	_triangles = new HACD::Vec3<long>[count];
	IEnumerator<int>^ enumerator = triangles->GetEnumerator();
	while(enumerator->MoveNext())
	{
		_triangles[i] = enumerator->Current;
		i++;
	}

	_unmanaged->SetTriangles(_triangles);
	_unmanaged->SetNTriangles(count);
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

double BulletSharp::Hacd::Hacd::CompacityWeight::get()
{
	return _unmanaged->GetCompacityWeight();
}

void BulletSharp::Hacd::Hacd::CompacityWeight::set(double value)
{
	return _unmanaged->SetCompacityWeight(value);
}

#endif