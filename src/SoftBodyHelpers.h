#pragma once

namespace BulletSharp
{
	namespace SoftBody
	{
		ref class SoftBody;
		ref class SoftBodyWorldInfo;

		public ref class SoftBodyHelpers sealed
		{
		private:
			SoftBodyHelpers() {};
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
				bool faceLinks, bool tetraLinks, bool facesFromTetras);
			static SoftBody^ CreateFromTetGenFile(SoftBodyWorldInfo^ worldInfo,
				String^ elementFilename, String^ faceFilename, String^ nodeFilename,
				bool faceLinks, bool tetraLinks, bool facesFromTetras);
			//static SoftBody^ CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
			//	array<btScalar> vertices, array<int> triangles, int ntriangles,
			//	bool randomizeConstraints);
			//static SoftBody^ CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
			//	array<btScalar> vertices, array<int> triangles, int ntriangles,
			//	bool randomizeConstraints);
			static SoftBody^ CreatePatch(SoftBodyWorldInfo^ worldInfo,
				Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
				int resx, int resy, int fixeds, bool gendiags);
			//static SoftBody^ CreatePatchUV(SoftBodyWorldInfo^ worldInfo,
			//	Vector3 corner00, Vector3 corner10, Vector3 corner01, Vector3 corner11,
			//	int resx, int resy, int fixeds, bool gendiags, array<float> texCoords);
			static SoftBody^ CreateRope(SoftBodyWorldInfo^ worldInfo,
				Vector3 from, Vector3 to, int res, int fixeds);
		};
	};
};
