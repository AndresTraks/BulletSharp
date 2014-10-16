#include "StdAfx.h"

#include "TransformUtil.h"

void TransformUtil::CalculateDiffAxisAngle(Matrix transform0, Matrix transform1, [Out] Vector3% axis,
	[Out] btScalar% angle)
{
	TRANSFORM_CONV(transform0);
	TRANSFORM_CONV(transform1);
	btVector3* axisTemp = ALIGNED_NEW(btVector3);
	btScalar angleTemp;
	btTransformUtil::calculateDiffAxisAngle(TRANSFORM_USE(transform0), TRANSFORM_USE(transform1),
		*axisTemp, angleTemp);
	TRANSFORM_DEL(transform0);
	TRANSFORM_DEL(transform1);
	Math::BtVector3ToVector3(axisTemp, axis);
	ALIGNED_FREE(axisTemp);
	angle = angleTemp;
}

void TransformUtil::CalculateDiffAxisAngleQuaternion(Quaternion orn0, Quaternion orn1a,
	[Out] Vector3% axis, [Out] btScalar% angle)
{
	QUATERNION_CONV(orn0);
	QUATERNION_CONV(orn1a);
	btVector3* axisTemp = ALIGNED_NEW(btVector3);
	btScalar angleTemp;
	btTransformUtil::calculateDiffAxisAngleQuaternion(QUATERNION_USE(orn0), QUATERNION_USE(orn1a),
		*axisTemp, angleTemp);
	QUATERNION_DEL(orn0);
	QUATERNION_DEL(orn1a);
	ALIGNED_FREE(axisTemp);
}

void TransformUtil::CalculateVelocity(Matrix transform0, Matrix transform1, btScalar timeStep,
	[Out] Vector3% linVel, [Out] Vector3% angVel)
{
	TRANSFORM_CONV(transform0);
	TRANSFORM_CONV(transform1);
	btVector3* linVelTemp = ALIGNED_NEW(btVector3);
	btVector3* angVelTemp = ALIGNED_NEW(btVector3);
	btTransformUtil::calculateVelocity(TRANSFORM_USE(transform0), TRANSFORM_USE(transform1),
		timeStep, *linVelTemp, *angVelTemp);
	TRANSFORM_DEL(transform0);
	TRANSFORM_DEL(transform1);
	Math::BtVector3ToVector3(linVelTemp, linVel);
	Math::BtVector3ToVector3(angVelTemp, angVel);
	ALIGNED_FREE(linVelTemp);
	ALIGNED_FREE(angVelTemp);
}

void TransformUtil::CalculateVelocityQuaternion(Vector3 pos0, Vector3 pos1, Quaternion orn0,
	Quaternion orn1, btScalar timeStep, [Out] Vector3% linVel, [Out] Vector3% angVel)
{
	VECTOR3_CONV(pos0);
	VECTOR3_CONV(pos1);
	QUATERNION_CONV(orn0);
	QUATERNION_CONV(orn1);
	btVector3* linVelTemp = ALIGNED_NEW(btVector3);
	btVector3* angVelTemp = ALIGNED_NEW(btVector3);
	btTransformUtil::calculateVelocityQuaternion(VECTOR3_USE(pos0), VECTOR3_USE(pos1),
		QUATERNION_USE(orn0), QUATERNION_USE(orn1), timeStep, *linVelTemp,
		*angVelTemp);
	VECTOR3_DEL(pos0);
	VECTOR3_DEL(pos1);
	QUATERNION_DEL(orn0);
	QUATERNION_DEL(orn1);
	Math::BtVector3ToVector3(linVelTemp, linVel);
	Math::BtVector3ToVector3(angVelTemp, angVel);
	ALIGNED_FREE(linVelTemp);
	ALIGNED_FREE(angVelTemp);
}

void TransformUtil::IntegrateTransform(Matrix curTrans, Vector3 linvel, Vector3 angvel,
	btScalar timeStep, [Out] Matrix% predictedTransform)
{
	TRANSFORM_CONV(curTrans);
	VECTOR3_CONV(linvel);
	VECTOR3_CONV(angvel);
	btTransform* predictedTransformTemp = ALIGNED_NEW(btTransform);
	btTransformUtil::integrateTransform(TRANSFORM_USE(curTrans), VECTOR3_USE(linvel),
		VECTOR3_USE(angvel), timeStep, *predictedTransformTemp);
	TRANSFORM_DEL(curTrans);
	VECTOR3_DEL(linvel);
	VECTOR3_DEL(angvel);
	Math::BtTransformToMatrix(predictedTransformTemp, predictedTransform);
	ALIGNED_FREE(predictedTransformTemp);
}


ConvexSeparatingDistanceUtil::~ConvexSeparatingDistanceUtil()
{
	this->!ConvexSeparatingDistanceUtil();
}

ConvexSeparatingDistanceUtil::!ConvexSeparatingDistanceUtil()
{
	delete _native;
	_native = NULL;
}

ConvexSeparatingDistanceUtil::ConvexSeparatingDistanceUtil(btScalar boundingRadiusA,
	btScalar boundingRadiusB)
{
	_native = new btConvexSeparatingDistanceUtil(boundingRadiusA, boundingRadiusB);
}

void ConvexSeparatingDistanceUtil::InitSeparatingDistance(Vector3 separatingVector,
	btScalar separatingDistance, Matrix transA, Matrix transB)
{
	VECTOR3_CONV(separatingVector);
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	_native->initSeparatingDistance(VECTOR3_USE(separatingVector), separatingDistance,
		TRANSFORM_USE(transA), TRANSFORM_USE(transB));
	VECTOR3_DEL(separatingVector);
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
}

void ConvexSeparatingDistanceUtil::UpdateSeparatingDistance(Matrix transA, Matrix transB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	_native->updateSeparatingDistance(TRANSFORM_USE(transA), TRANSFORM_USE(transB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
}

btScalar ConvexSeparatingDistanceUtil::ConservativeSeparatingDistance::get()
{
	return _native->getConservativeSeparatingDistance();
}
