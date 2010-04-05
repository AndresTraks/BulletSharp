#pragma once

// Fully implemented as of 05 Apr 2010

#include "ConcaveShape.h"
#include "Enums.h"

namespace BulletSharp
{
	public ref class HeightfieldTerrainShape : ConcaveShape
	{
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
