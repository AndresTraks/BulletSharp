#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	public ref class HeightfieldTerrainShape : ConcaveShape
	{
	internal:
		HeightfieldTerrainShape(btHeightfieldTerrainShape* terrainShape);

	public:
		HeightfieldTerrainShape(int heightStickWidth, int heightStickLength, Stream^ heightfieldData,
			btScalar heightScale, btScalar minHeight, btScalar maxHeight, int upAxis,
			PhyScalarType heightDataType, bool flipQuadEdges);

		void SetUseDiamondSubdivision(bool useDiamondSubdivision);
		void SetUseDiamondSubdivision();

	internal:
		property btHeightfieldTerrainShape* UnmanagedPointer
		{
			virtual btHeightfieldTerrainShape* get() new;
		}
	};
};
