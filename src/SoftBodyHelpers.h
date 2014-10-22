#pragma once

namespace BulletSharp
{
	interface class IDebugDraw;

	namespace SoftBody
	{
		ref class SoftBody;
		ref class SoftBodyWorldInfo;

		[Flags]
		public enum class DrawFlags
		{
			Nodes = fDrawFlags::Nodes,
			Links = fDrawFlags::Links,
			Faces = fDrawFlags::Faces,
			Tetras = fDrawFlags::Tetras,
			Normals = fDrawFlags::Normals,
			Contacts = fDrawFlags::Contacts,
			Anchors = fDrawFlags::Anchors,
			Notes = fDrawFlags::Notes,
			Clusters = fDrawFlags::Clusters,
			NodeTree = fDrawFlags::NodeTree,
			FaceTree = fDrawFlags::FaceTree,
			ClusterTree = fDrawFlags::ClusterTree,
			Joints = fDrawFlags::Joints,
			Std = fDrawFlags::Std,
			StdTetra = fDrawFlags::StdTetra
		};

		public ref class SoftBodyHelpers sealed
		{
		private:
			SoftBodyHelpers() {};

		public:
			static float CalculateUV(int resx, int resy, int ix, int iy, int id);
			static SoftBody^ CreateEllipsoid(SoftBodyWorldInfo^ worldInfo, Vector3 center,
				Vector3 radius, int res);
			static SoftBody^ CreateFromConvexHull(SoftBodyWorldInfo^ worldInfo, array<Vector3>^ vertices,
				bool randomizeConstraints);
			static SoftBody^ CreateFromConvexHull(SoftBodyWorldInfo^ worldInfo, array<Vector3>^ vertices);
			static SoftBody^ CreateFromTetGenData(SoftBodyWorldInfo^ worldInfo, String^ ele,
				String^ face, String^ node, bool faceLinks, bool tetraLinks, bool facesFromTetras);
			static SoftBody^ CreateFromTetGenFile(SoftBodyWorldInfo^ worldInfo,
				String^ elementFilename, String^ faceFilename, String^ nodeFilename,
				bool faceLinks, bool tetraLinks, bool facesFromTetras);
			static SoftBody^ CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo, array<btScalar>^ vertices,
				array<int>^ triangles, bool randomizeConstraints);
			static SoftBody^ CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo, array<btScalar>^ vertices,
				array<int>^ triangles);
			static SoftBody^ CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
				array<Vector3>^ vertices, array<int>^ triangles, bool randomizeConstraints);
			static SoftBody^ CreateFromTriMesh(SoftBodyWorldInfo^ worldInfo,
				array<Vector3>^ vertices, array<int>^ triangles);
			static SoftBody^ CreatePatch(SoftBodyWorldInfo^ worldInfo, Vector3 corner00,
				Vector3 corner10, Vector3 corner01, Vector3 corner11, int resx, int resy,
				int fixeds, bool gendiags);
			static SoftBody^ CreatePatchUV(SoftBodyWorldInfo^ worldInfo, Vector3 corner00,
				Vector3 corner10, Vector3 corner01, Vector3 corner11, int resx, int resy,
				int fixeds, bool gendiags, array<float>^ texCoords);
			static SoftBody^ CreatePatchUV(SoftBodyWorldInfo^ worldInfo, Vector3 corner00,
				Vector3 corner10, Vector3 corner01, Vector3 corner11, int resx, int resy,
				int fixeds, bool gendiags);
			static SoftBody^ CreateRope(SoftBodyWorldInfo^ worldInfo, Vector3 from, Vector3 to,
				int res, int fixeds);
#ifndef DISABLE_DEBUGDRAW
			static void Draw(SoftBody^ psb, IDebugDraw^ iDraw, DrawFlags drawFlags);
			static void Draw(SoftBody^ psb, IDebugDraw^ iDraw);
			static void DrawClusterTree(SoftBody^ psb, IDebugDraw^ iDraw, int minDepth,
				int maxDepth);
			static void DrawClusterTree(SoftBody^ psb, IDebugDraw^ iDraw, int minDepth);
			static void DrawClusterTree(SoftBody^ psb, IDebugDraw^ iDraw);
			static void DrawFaceTree(SoftBody^ psb, IDebugDraw^ iDraw, int minDepth, int maxDepth);
			static void DrawFaceTree(SoftBody^ psb, IDebugDraw^ iDraw, int minDepth);
			static void DrawFaceTree(SoftBody^ psb, IDebugDraw^ iDraw);
			static void DrawFrame(SoftBody^ psb, IDebugDraw^ iDraw);
			static void DrawInfos(SoftBody^ psb, IDebugDraw^ iDraw, bool masses, bool areas,
				bool stress);
			static void DrawNodeTree(SoftBody^ psb, IDebugDraw^ iDraw, int minDepth, int maxDepth);
			static void DrawNodeTree(SoftBody^ psb, IDebugDraw^ iDraw, int minDepth);
			static void DrawNodeTree(SoftBody^ psb, IDebugDraw^ iDraw);
#endif
			static void ReoptimizeLinkOrder(SoftBody^ psb);
		};
	};
};
