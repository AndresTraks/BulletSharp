#pragma once

namespace BulletSharp
{
	ref class CollisionObject;
	ref class CollisionShape;
	ref class ConvexHullShape;
	ref class CompoundShape;
	ref class DynamicsWorld;
	ref class RigidBody;
	ref class MultiSphereShape;
	ref class StridingMeshInterface;
	ref class TriangleIndexVertexArray;
	ref class BvhTriangleMeshShape;
	ref class OptimizedBvh;
	ref class ScaledBvhTriangleMeshShape;
	ref class ConeTwistConstraint;
	ref class GearConstraint;
	ref class Generic6DofConstraint;
	ref class Generic6DofSpringConstraint;
	ref class Generic6DofSpring2Constraint;
	ref class HingeConstraint;
	ref class Point2PointConstraint;
	ref class SliderConstraint;
	ref class TypedConstraint;
	ref class GImpactMeshShape;
	ref class TriangleInfoMap;

	namespace Serialize
	{
		class BulletWorldImporterWrapper;

		public ref class BulletWorldImporter
		{
		private:
			BulletWorldImporterWrapper* _native;
			DynamicsWorld^ _world;
			Dictionary<Object^, String^>^ _objectNameMap;
			Dictionary<String^, RigidBody^>^ _nameBodyMap;

		internal:
			List<OptimizedBvh^>^ _allocatedBvhs;
			Dictionary<IntPtr, OptimizedBvh^>^ _allocatedBvhsMap;
			List<CollisionObject^>^ _allocatedRigidBodies;
			List<CollisionShape^>^ _allocatedCollisionShapes;
#ifndef DISABLE_CONSTRAINTS
			List<TypedConstraint^>^ _allocatedConstraints;
#endif
			List<TriangleIndexVertexArray^>^ _allocatedTriangleIndexArrays;
			Dictionary<IntPtr, TriangleIndexVertexArray^>^ _allocatedTriangleIndexArraysMap;
			List<TriangleInfoMap^>^ _allocatedTriangleInfoMaps;

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
			virtual CollisionShape^ CreateConeShapeX(btScalar radius, btScalar height);
			virtual CollisionShape^ CreateConeShapeY(btScalar radius, btScalar height);
			virtual CollisionShape^ CreateConeShapeZ(btScalar radius, btScalar height);
			//virtual TriangleIndexVertexArray^ CreateMeshInterface(StridingMeshInterfaceData^ meshData);
			virtual TriangleIndexVertexArray^ CreateTriangleMeshContainer();
			virtual BvhTriangleMeshShape^ CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh);
			virtual CollisionShape^ CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh);
#ifndef DISABLE_GIMPACT
			virtual GImpactMeshShape^ CreateGImpactShape(StridingMeshInterface^ trimesh);
#endif
			//virtual StridingMeshInterfaceData^ CreateStridingMeshInterfaceData(StridingMeshInterfaceData^ interfaceData);
			virtual ConvexHullShape^ CreateConvexHullShape();
			virtual CompoundShape^ CreateCompoundShape();
			virtual ScaledBvhTriangleMeshShape^ CreateScaledTrangleMeshShape(BvhTriangleMeshShape^ meshShape, Vector3 localScaling);
			virtual MultiSphereShape^ CreateMultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi);

			// acceleration and connectivity structures
			virtual OptimizedBvh^ CreateOptimizedBvh();
			virtual TriangleInfoMap^ CreateTriangleInfoMap();

#ifndef DISABLE_CONSTRAINTS
			// constraints
			virtual Point2PointConstraint^ CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA, Vector3 pivotInB);
			virtual Point2PointConstraint^ CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA);
			virtual HingeConstraint^ CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame);
			virtual ConeTwistConstraint^ CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame);
			virtual ConeTwistConstraint^ CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame);
			virtual Generic6DofConstraint^ CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
			virtual Generic6DofConstraint^ CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB);
			virtual Generic6DofSpringConstraint^ CreateGeneric6DofSpringConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
			virtual Generic6DofSpring2Constraint^ CreateGeneric6DofSpring2Constraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, RotateOrder rotateOrder);
			virtual SliderConstraint^ CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
			virtual SliderConstraint^ CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA);
			virtual GearConstraint^ CreateGearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio);
#endif

			void DeleteAllData();
			bool LoadFile(String^ fileName, String^ preSwapFilenameOut);
			bool LoadFile(String^ fileName);
			bool LoadFileFromMemory(array<Byte>^ memoryBuffer);
			//bool LoadFileFromMemory(Parse::BulletFile^ file);
			//bool ConvertAllObjects(Parse::BulletFile^ file);

			// query for data
			CollisionShape^ GetCollisionShapeByIndex(int index);
			CollisionObject^ GetRigidBodyByIndex(int index);
#ifndef DISABLE_CONSTRAINTS
			TypedConstraint^ GetConstraintByIndex(int index);
#endif
			OptimizedBvh^ GetBvhByIndex(int index);
			TriangleInfoMap^ GetTriangleInfoMapByIndex(int index);

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

			property int BvhCount
			{
				int get();
			}

			property int CollisionShapeCount
			{
				int get();
			}

			property int ConstraintCount
			{
				int get();
			}

			property int RigidBodyCount
			{
				int get();
			}

			property int TriangleInfoMapCount
			{
				int get();
			}

			property int VerboseMode
			{
				int get();
				void set(int value);
			}
		};

		class BulletWorldImporterWrapper : public btBulletWorldImporter
		{
		private:
			gcroot<BulletWorldImporter^> _importer;

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
			virtual btCollisionShape* createConeShapeX(btScalar radius, btScalar height);
			virtual btCollisionShape* createConeShapeY(btScalar radius, btScalar height);
			virtual btCollisionShape* createConeShapeZ(btScalar radius, btScalar height);
			virtual class btTriangleIndexVertexArray* createTriangleMeshContainer();
			virtual	btBvhTriangleMeshShape* createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh);
			virtual btCollisionShape* createConvexTriangleMeshShape(btStridingMeshInterface* trimesh);
#ifndef DISABLE_GIMPACT
			virtual btGImpactMeshShape* createGimpactShape(btStridingMeshInterface* trimesh);
#endif
			virtual class btConvexHullShape* createConvexHullShape();
			virtual class btCompoundShape* createCompoundShape();
			virtual class btScaledBvhTriangleMeshShape* createScaledTrangleMeshShape(btBvhTriangleMeshShape* meshShape, const btVector3& localScalingbtBvhTriangleMeshShape);
			virtual class btMultiSphereShape* createMultiSphereShape(const btVector3* positions, const btScalar* radi, int numSpheres);
			//virtual btTriangleIndexVertexArray* createMeshInterface(btStridingMeshInterfaceData& meshData);

			// acceleration and connectivity structures
			virtual btOptimizedBvh* createOptimizedBvh();
			virtual btTriangleInfoMap* createTriangleInfoMap();

#ifndef DISABLE_CONSTRAINTS
			// constraints
			virtual btPoint2PointConstraint* createPoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btVector3& pivotInA, const btVector3& pivotInB);
			virtual btPoint2PointConstraint* createPoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
				const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
				const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA);
			virtual btHingeConstraint* createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame);
			virtual btConeTwistConstraint* createConeTwistConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
				const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame);
			virtual btConeTwistConstraint* createConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame);
			virtual btGeneric6DofConstraint* createGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btGeneric6DofConstraint* createGeneric6DofConstraint(btRigidBody& rigidBodyB,
				const btTransform& frameInB, bool useLinearReferenceFrameB);
			virtual btGeneric6DofSpringConstraint* createGeneric6DofSpringConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btGeneric6DofSpring2Constraint* createGeneric6DofSpring2Constraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btTransform& frameInA, const btTransform& frameInB, int rotateOrder);
			virtual btSliderConstraint* createSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btSliderConstraint* createSliderConstraint(btRigidBody& rigidBodyB,
				const btTransform& frameInB, bool useLinearReferenceFrameA);
			virtual btGearConstraint* createGearConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btVector3& axisInA, const btVector3& axisInB, btScalar ratio);
#endif


			// bodies
			virtual btCollisionObject* baseCreateCollisionObject(const btTransform& startTransform,
				btCollisionShape* shape, const char* bodyName);
			virtual btRigidBody* baseCreateRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
				btCollisionShape* shape, const char* bodyName);
		};
	};
};
