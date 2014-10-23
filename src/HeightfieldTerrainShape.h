#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	public ref class HeightfieldTerrainShape : ConcaveShape
	{
	public:
		HeightfieldTerrainShape(int heightStickWidth, int heightStickLength, System::IO::Stream^ heightfieldData,
			btScalar heightScale, btScalar minHeight, btScalar maxHeight, int upAxis,
			PhyScalarType heightDataType, bool flipQuadEdges);

		void SetUseDiamondSubdivision(bool useDiamondSubdivision);
		void SetUseDiamondSubdivision();
		void SetUseZigzagSubdivision(bool useZigzagSubdivision);
		void SetUseZigzagSubdivision();
	};
};
