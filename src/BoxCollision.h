#pragma once

namespace BulletSharp
{
	public ref class Aabb
	{
	internal:
		btAABB* _native;

	private:
		bool _preventDelete;

	internal:
		Aabb(btAABB* native, bool preventDelete);

		~Aabb();
		!Aabb();

	public:
		Aabb();
		Aabb(Vector3 v1, Vector3 v2, Vector3 v3);
		Aabb(Vector3 v1, Vector3 v2, Vector3 v3, btScalar margin);
		Aabb(Aabb^ other);
		Aabb(Aabb^ other, btScalar margin);

		void AppyTransform(Matrix trans);
		//void AppyTransformTransCache(BT_BOX_BOX_TRANSFORM_CACHE^ trans);
		bool CollidePlane(Vector4 plane);
		bool CollideRay(Vector3 vorigin, Vector3 vdir);
		bool CollideTriangleExact(Vector3 p1, Vector3 p2, Vector3 p3, Vector4 trianglePlane);
		void CopyWithMargin(Aabb^ other, btScalar margin);
		void FindIntersection(Aabb^ other, Aabb^ intersection);
		void GetCenterExtend([Out] Vector3% center, [Out] Vector3% extend);
		bool HasCollision(Aabb^ other);
		void IncrementMargin(btScalar margin);
		void Invalidate();
		void Merge(Aabb^ box);
		//bool OverlappingTransCache(Aabb^ box, BT_BOX_BOX_TRANSFORM_CACHE^ transcache,
		//	bool fulltest);
		bool OverlappingTransConservative(Aabb^ box, Matrix trans1To0);
		//bool OverlappingTransConservative2(Aabb^ box, BT_BOX_BOX_TRANSFORM_CACHE^ trans1To0);
		//eBT_PLANE_INTERSECTION_TYPE PlaneClassify(Vector4 plane);
		void ProjectionInterval(Vector3 direction, [Out] btScalar% vmin, [Out] btScalar% vmax);

		property Vector3 Max
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 Min
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};
};
