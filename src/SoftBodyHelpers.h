#pragma once

namespace BulletSharp
{
	ref class SoftBody;
	ref class SoftBodyWorldInfo;

	public ref class SoftBodyHelpers
	{
	public:
		static float CalculateUV(int resx, int resy, int ix, int iy, int id);
		static SoftBody^ CreateEllipsoid(SoftBodyWorldInfo^ worldInfo,
			Vector3 center, Vector3 radius, int res);
		static SoftBody^ CreateFromConvexHull(SoftBodyWorldInfo^ worldInfo,
			array<Vector3>^ vertices, bool randomizeConstraints);
		static SoftBody^ CreateFromConvexHull(SoftBodyWorldInfo^ worldInfo,
			array<Vector3>^ vertices);
		static SoftBody^ CreateFromTetGenData(SoftBodyWorldInfo^ worldInfo,
			String^ ele, String^ face, String^ node,
			bool bfacelinks, bool btetralinks, bool bfacesfromtetras);
		static SoftBody^ CreateFromTetGenFile(SoftBodyWorldInfo^ worldInfo,
			String^ ele, String^ face, String^ node,
			bool bfacelinks, bool btetralinks, bool bfacesfromtetras);
	};
};
