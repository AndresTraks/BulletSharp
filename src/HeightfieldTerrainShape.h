#pragma once

// Fully implemented as of 21 Oct 2010

#include "ConcaveShape.h"
#include "Enums.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#pragma managed(pop)

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
