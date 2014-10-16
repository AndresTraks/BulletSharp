#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "TriangleBuffer.h"

BulletTriangle::BulletTriangle(const btTriangle* triangle)
{
	vertex0 = Math::BtVector3ToVector3(&triangle->m_vertex0);
	vertex1 = Math::BtVector3ToVector3(&triangle->m_vertex1);
	vertex2 = Math::BtVector3ToVector3(&triangle->m_vertex2);
	partId = triangle->m_partId;
	triangleIndex = triangle->m_triangleIndex;
}

BulletTriangle::BulletTriangle()
{
}

BulletTriangle::BulletTriangle(const BulletTriangle^ &triangle)
{
	vertex0 = triangle->vertex0;
	vertex1 = triangle->vertex1;
	vertex2 = triangle->vertex2;
	partId = triangle->partId;
	triangleIndex = triangle->triangleIndex;
}


#define Native static_cast<btTriangleBuffer*>(_native)

TriangleBuffer::TriangleBuffer()
	: TriangleCallback(new btTriangleBuffer())
{
}

void TriangleBuffer::ClearBuffer()
{
	Native->clearBuffer();
}

BulletTriangle^ TriangleBuffer::GetTriangle(int index)
{
	const btTriangle* triangle = &Native->getTriangle(index);
	if (triangle == 0)
		return nullptr;
	return gcnew BulletTriangle(triangle);
}

int TriangleBuffer::NumTriangles::get()
{
	return Native->getNumTriangles();
}

#endif
