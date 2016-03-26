#pragma once

namespace BulletSharp
{
	public ref class TransformUtil sealed
	{
		TransformUtil() {}

	public:
		static void CalculateDiffAxisAngle(Matrix transform0, Matrix transform1,
			[Out] Vector3% axis, [Out] btScalar% angle);
		static void CalculateDiffAxisAngleQuaternion(Quaternion orn0, Quaternion orn1a,
			[Out] Vector3% axis, [Out] btScalar% angle);
		static void CalculateVelocity(Matrix transform0, Matrix transform1, btScalar timeStep,
			[Out] Vector3% linVel, [Out] Vector3% angVel);
		static void CalculateVelocityQuaternion(Vector3 pos0, Vector3 pos1, Quaternion orn0,
			Quaternion orn1, btScalar timeStep, [Out] Vector3% linVel, [Out] Vector3% angVel);
		static void IntegrateTransform(Matrix curTrans, Vector3 linvel, Vector3 angvel,
			btScalar timeStep, [Out] Matrix% predictedTransform);
	};

	public ref class ConvexSeparatingDistanceUtil
	{
	internal:
		btConvexSeparatingDistanceUtil* _native;

		~ConvexSeparatingDistanceUtil();
		!ConvexSeparatingDistanceUtil();

	public:
		ConvexSeparatingDistanceUtil(btScalar boundingRadiusA, btScalar boundingRadiusB);

		void InitSeparatingDistance(Vector3 separatingVector, btScalar separatingDistance,
			Matrix transA, Matrix transB);
		void UpdateSeparatingDistance(Matrix transA, Matrix transB);

		property btScalar ConservativeSeparatingDistance
		{
			btScalar get();
		}
	};
};
