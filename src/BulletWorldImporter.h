#pragma once

#include "BvhTriangleMeshShape.h"
#include "CollisionShape.h"
#include "ConvexHullShape.h"
#include "CompoundShape.h"
#include "DynamicsWorld.h"
#include "IDisposable.h"
#include "RigidBody.h"
#include "StridingMeshInterface.h"
#include "TriangleIndexVertexArray.h"
#ifndef DISABLE_GIMPACT
#include "GImpactShape.h"
#endif
#ifndef DISABLE_CONSTRAINTS
#include "ConeTwistConstraint.h"
#include "Generic6DofConstraint.h"
#include "HingeConstraint.h"
#include "Point2PointConstraint.h"
#include "SliderConstraint.h"
#endif

#include <msclr/auto_gcroot.h>

using namespace msclr;

namespace BulletSharp
{
	namespace Serialize
	{
		class BulletWorldImporterWrapper;

		public ref class BulletWorldImporter : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			BulletWorldImporterWrapper* _importer;

		public:
			!BulletWorldImporter();
		protected:
			~BulletWorldImporter();

		public:
			BulletWorldImporter(DynamicsWorld^ world);
			BulletWorldImporter();

			// bodies
			virtual CollisionObject^ CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName);
			virtual RigidBody^ CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName);

			// shapes
			virtual CollisionShape^ CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant);
			virtual CollisionShape^ CreateBoxShape(Vector3 halfExtents);
			virtual CollisionShape^ CreateSphereShape(btScalar radius);
			virtual CollisionShape^ CreateCapsuleShapeX(btScalar radius, btScalar height);
			virtual CollisionShape^ CreateCapsuleShapeY(btScalar radius, btScalar height);
			virtual CollisionShape^ CreateCapsuleShapeZ(btScalar radius, btScalar height);

			virtual CollisionShape^ CreateCylinderShapeX(btScalar radius, btScalar height);
			virtual CollisionShape^ CreateCylinderShapeY(btScalar radius, btScalar height);
			virtual CollisionShape^ CreateCylinderShapeZ(btScalar radius, btScalar height);
			virtual TriangleIndexVertexArray^ CreateTriangleMeshContainer();
#ifndef DISABLE_BVH
			virtual BvhTriangleMeshShape^ CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh);
#endif
			virtual CollisionShape^ CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh);
#ifndef DISABLE_GIMPACT
			virtual GImpactMeshShape^ CreateGimpactShape(StridingMeshInterface^ trimesh);
#endif
			virtual ConvexHullShape^ CreateConvexHullShape();
			virtual CompoundShape^ CreateCompoundShape();

			// acceleration and connectivity structures
#ifndef DISABLE_BVH
			virtual OptimizedBvh^ CreateOptimizedBvh();
#endif
			//virtual TriangleInfoMap^ CreateTriangleInfoMap();

#ifndef DISABLE_CONSTRAINTS
			// constraints
			virtual Point2PointConstraint^ CreatePoint2PointConstraint(RigidBody^ rbA, RigidBody^ rbB, Vector3 pivotInA, Vector3 pivotInB);
			virtual Point2PointConstraint^ CreatePoint2PointConstraint(RigidBody^ rbA, Vector3 pivotInA);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame, bool useReferenceFrameA);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rbA, Matrix rbAFrame, bool useReferenceFrameA);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rbA, Matrix rbAFrame);
			virtual ConeTwistConstraint^ CreateConeTwistConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame);
			virtual ConeTwistConstraint^ CreateConeTwistConstraint(RigidBody^ rbA, Matrix rbAFrame);
			virtual Generic6DofConstraint^ CreateGeneric6DofConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
			virtual Generic6DofConstraint^ CreateGeneric6DofConstraint(RigidBody^ rbB, Matrix frameInB, bool useLinearReferenceFrameB);
			virtual SliderConstraint^ CreateSliderConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
			virtual SliderConstraint^ CreateSliderConstraint(RigidBody^ rbB, Matrix frameInB, bool useLinearReferenceFrameA);
#endif

			void DeleteAllData();
			bool LoadFile(String^ fileName);
			//bool LoadFileFromMemory(MemoryStream^ memoryBuffer, int len);
			//bool LoadFileFromMemory(Parse::BulletFile^ file);
			//bool ConvertAllObjects(Parse::BulletFile^ file);

			// query for data
			CollisionShape^ GetCollisionShapeByIndex(int index);
			CollisionObject^ GetRigidBodyByIndex(int index);
#ifndef DISABLE_CONSTRAINTS
			TypedConstraint^ GetConstraintByIndex(int index);
#endif
#ifndef DISABLE_BVH
			OptimizedBvh^ GetBvhByIndex(int index);
#endif
			//TriangleInfoMap^ GetTriangleInfoMapByIndex(int index);

			// queries involving named objects
			CollisionShape^ GetCollisionShapeByName(String^ name);
			RigidBody^ GetRigidBodyByName(String^ name);
#ifndef DISABLE_CONSTRAINTS
			TypedConstraint^ GetConstraintByName(String^ name);
#endif
			String^	GetNameForObject(Object^ obj);

			property bool IsDisposed
			{
				virtual bool get();
			}

			property int NumBvhs
			{
				int get();
			}

			property int NumCollisionShapes
			{
				int get();
			}

			property int NumConstraints
			{
				int get();
			}

			property int NumRigidBodies
			{
				int get();
			}

			property int NumTriangleInfoMaps
			{
				int get();
			}

			property bool VerboseMode
			{
				bool get();
				void set(bool value);
			}
		};

		class BulletWorldImporterWrapper : public btBulletWorldImporter
		{
		private:
			auto_gcroot<BulletWorldImporter^> _importer;

		public:
			BulletWorldImporterWrapper(btDynamicsWorld* world, BulletWorldImporter^ importer);

			// bodies
			virtual btCollisionObject* createCollisionObject(const btTransform& startTransform,
				btCollisionShape* shape, const char* bodyName);
			virtual btRigidBody* createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
				btCollisionShape* shape, const char* bodyName);

			// shapes
			virtual btCollisionShape* createPlaneShape(const btVector3& planeNormal, btScalar planeConstant);
			virtual btCollisionShape* createBoxShape(const btVector3& halfExtents);
			virtual btCollisionShape* createSphereShape(btScalar radius);
			virtual btCollisionShape* createCapsuleShapeX(btScalar radius, btScalar height);
			virtual btCollisionShape* createCapsuleShapeY(btScalar radius, btScalar height);
			virtual btCollisionShape* createCapsuleShapeZ(btScalar radius, btScalar height);

			virtual btCollisionShape* createCylinderShapeX(btScalar radius, btScalar height);
			virtual btCollisionShape* createCylinderShapeY(btScalar radius, btScalar height);
			virtual btCollisionShape* createCylinderShapeZ(btScalar radius, btScalar height);
			virtual class btTriangleIndexVertexArray* createTriangleMeshContainer();
#ifndef DISABLE_BVH
			virtual	btBvhTriangleMeshShape* createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh);
#endif
			virtual btCollisionShape* createConvexTriangleMeshShape(btStridingMeshInterface* trimesh);
#ifndef DISABLE_GIMPACT
			virtual btGImpactMeshShape* createGimpactShape(btStridingMeshInterface* trimesh);
#endif
			virtual class btConvexHullShape* createConvexHullShape();
			virtual class btCompoundShape* createCompoundShape();

			// acceleration and connectivity structures
#ifndef DISABLE_BVH
			virtual btOptimizedBvh* createOptimizedBvh();
#endif
			virtual btTriangleInfoMap* createTriangleInfoMap();

#ifndef DISABLE_CONSTRAINTS
			// constraints
			virtual btPoint2PointConstraint* createPoint2PointConstraint(btRigidBody& rbA, btRigidBody& rbB,
				const btVector3& pivotInA, const btVector3& pivotInB);
			virtual btPoint2PointConstraint* createPoint2PointConstraint(btRigidBody& rbA, const btVector3& pivotInA);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
				const btTransform& rbAFrame, const btTransform& rbBFrame, bool useReferenceFrameA);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
				const btTransform& rbAFrame, const btTransform& rbBFrame);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame, bool useReferenceFrameA);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame);
			virtual btConeTwistConstraint* createConeTwistConstraint(btRigidBody& rbA,btRigidBody& rbB,
				const btTransform& rbAFrame, const btTransform& rbBFrame);
			virtual btConeTwistConstraint* createConeTwistConstraint(btRigidBody& rbA, const btTransform& rbAFrame);
			virtual btGeneric6DofConstraint* createGeneric6DofConstraint(btRigidBody& rbA, btRigidBody& rbB,
				const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btGeneric6DofConstraint* createGeneric6DofConstraint(btRigidBody& rbB,
				const btTransform& frameInB, bool useLinearReferenceFrameB);
			virtual btSliderConstraint* createSliderConstraint(btRigidBody& rbA, btRigidBody& rbB,
				const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btSliderConstraint* createSliderConstraint(btRigidBody& rbB,
				const btTransform& frameInB, bool useLinearReferenceFrameA);
#endif


			// bodies
			virtual btCollisionObject* baseCreateCollisionObject(const btTransform& startTransform,
				btCollisionShape* shape, const char* bodyName);
			virtual btRigidBody* baseCreateRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
				btCollisionShape* shape, const char* bodyName);

			// shapes
			virtual btCollisionShape* baseCreatePlaneShape(const btVector3& planeNormal, btScalar planeConstant);
			virtual btCollisionShape* baseCreateBoxShape(const btVector3& halfExtents);
			virtual btCollisionShape* baseCreateSphereShape(btScalar radius);
			virtual btCollisionShape* baseCreateCapsuleShapeX(btScalar radius, btScalar height);
			virtual btCollisionShape* baseCreateCapsuleShapeY(btScalar radius, btScalar height);
			virtual btCollisionShape* baseCreateCapsuleShapeZ(btScalar radius, btScalar height);

			virtual btCollisionShape* baseCreateCylinderShapeX(btScalar radius, btScalar height);
			virtual btCollisionShape* baseCreateCylinderShapeY(btScalar radius, btScalar height);
			virtual btCollisionShape* baseCreateCylinderShapeZ(btScalar radius, btScalar height);
			virtual class btTriangleIndexVertexArray* baseCreateTriangleMeshContainer();
#ifndef DISABLE_BVH
			virtual	btBvhTriangleMeshShape* baseCreateBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh);
#endif
			virtual btCollisionShape* baseCreateConvexTriangleMeshShape(btStridingMeshInterface* trimesh);
#ifndef DISABLE_GIMPACT
			virtual btGImpactMeshShape* baseCreateGimpactShape(btStridingMeshInterface* trimesh);
#endif
			virtual class btConvexHullShape* baseCreateConvexHullShape();
			virtual class btCompoundShape* baseCreateCompoundShape();

			// acceleration and connectivity structures
#ifndef DISABLE_BVH
			virtual btOptimizedBvh* baseCreateOptimizedBvh();
#endif
			virtual btTriangleInfoMap* baseCreateTriangleInfoMap();

#ifndef DISABLE_CONSTRAINTS
			// constraints
			virtual btPoint2PointConstraint* baseCreatePoint2PointConstraint(btRigidBody& rbA, btRigidBody& rbB,
				const btVector3& pivotInA, const btVector3& pivotInB);
			virtual btPoint2PointConstraint* baseCreatePoint2PointConstraint(btRigidBody& rbA, const btVector3& pivotInA);
			virtual btHingeConstraint* baseCreateHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
				const btTransform& rbAFrame, const btTransform& rbBFrame, bool useReferenceFrameA);
			virtual btHingeConstraint* baseCreateHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
				const btTransform& rbAFrame, const btTransform& rbBFrame);
			virtual btHingeConstraint* baseCreateHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame, bool useReferenceFrameA);
			virtual btHingeConstraint* baseCreateHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame);
			virtual btConeTwistConstraint* baseCreateConeTwistConstraint(btRigidBody& rbA, btRigidBody& rbB,
				const btTransform& rbAFrame, const btTransform& rbBFrame);
			virtual btConeTwistConstraint* baseCreateConeTwistConstraint(btRigidBody& rbA, const btTransform& rbAFrame);
			virtual btGeneric6DofConstraint* baseCreateGeneric6DofConstraint(btRigidBody& rbA, btRigidBody& rbB,
				const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btGeneric6DofConstraint* baseCreateGeneric6DofConstraint(btRigidBody& rbB,
				const btTransform& frameInB, bool useLinearReferenceFrameB);
			virtual btSliderConstraint* baseCreateSliderConstraint(btRigidBody& rbA, btRigidBody& rbB,
				const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btSliderConstraint* baseCreateSliderConstraint(btRigidBody& rbB,
				const btTransform& frameInB, bool useLinearReferenceFrameA);
#endif
		};
	};
};
