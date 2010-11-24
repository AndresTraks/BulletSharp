#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "HeightfieldTerrainShape.h"

HeightfieldTerrainShape::HeightfieldTerrainShape(btHeightfieldTerrainShape* terrainShape)
: ConcaveShape(terrainShape)
{
}

HeightfieldTerrainShape::HeightfieldTerrainShape(int heightStickWidth, int heightStickLength, Stream^ heightfieldData,
	btScalar heightScale, btScalar minHeight, btScalar maxHeight, int upAxis,
	PhyScalarType heightDataType, bool flipQuadEdges)
: ConcaveShape(0)
{
	int typeSize;
	switch (heightDataType)
	{
	case PhyScalarType::PhyUChar:
		typeSize = 1;
		break;
	case PhyScalarType::PhyShort:
		typeSize = 2;
		break;
	case PhyScalarType::PhyFloat:
		typeSize = 4;
		break;
	default:
		throw gcnew ArgumentException("Data type can only be PhyUChar, PhyShort or PhyFloat.", "heightDataType");
	}

	int dataSize = heightStickWidth * heightStickLength * typeSize;

	cli::array<unsigned char,1>^ dataManaged = gcnew cli::array<unsigned char,1>(dataSize);
	heightfieldData->Read(dataManaged, 0, dataSize);

	cli::pin_ptr<unsigned char> dataPtr = &dataManaged[0];
	char* data = new char[dataSize];
	memcpy(data, dataPtr, dataSize);

	UnmanagedPointer = new btHeightfieldTerrainShape(heightStickWidth, heightStickLength, data,
		heightScale, minHeight, maxHeight, upAxis, (PHY_ScalarType)heightDataType, flipQuadEdges);
}

void HeightfieldTerrainShape::SetUseDiamondSubdivision(bool useDiamondSubdivision)
{
	UnmanagedPointer->setUseDiamondSubdivision(useDiamondSubdivision);
}

void HeightfieldTerrainShape::SetUseDiamondSubdivision()
{
	UnmanagedPointer->setUseDiamondSubdivision();
}

btHeightfieldTerrainShape* HeightfieldTerrainShape::UnmanagedPointer::get()
{
	return (btHeightfieldTerrainShape*)ConcaveShape::UnmanagedPointer;
}

#endif
