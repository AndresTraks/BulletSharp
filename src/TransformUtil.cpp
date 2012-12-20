#include "StdAfx.h"

#include "TransformUtil.h"

void TransformUtil::CalculateDiffAxisAngle(Matrix transform0, Matrix transform1,
	[Out] Vector3% axis, [Out] btScalar% angle)
{
	btTransform* transform0Temp = Math::MatrixToBtTransform(transform0);
	btTransform* transform1Temp = Math::MatrixToBtTransform(transform1);
	btVector3* axisTemp = new btVector3;
	btScalar angleTemp;

	btTransformUtil::calculateDiffAxisAngle(*transform0Temp, *transform1Temp, *axisTemp, angleTemp);

	ALIGNED_DEL(transform0Temp);
	ALIGNED_DEL(transform1Temp);

	Math::BtVector3ToVector3(axisTemp, axis);
	delete axisTemp;

	angle = angleTemp;
}

void TransformUtil::CalculateDiffAxisAngleQuaternion(Quaternion orn0, Quaternion orn1a,
	[Out] Vector3% axis, [Out] btScalar% angle)
{
	btQuaternion* orn0Temp = Math::QuaternionToBtQuat(orn0);
	btQuaternion* orn1aTemp = Math::QuaternionToBtQuat(orn1a);
	btVector3* axisTemp = new btVector3;
	btScalar angleTemp;

	btTransformUtil::calculateDiffAxisAngleQuaternion(*orn0Temp, *orn1aTemp, *axisTemp, angleTemp);

	delete orn0Temp;
	delete orn1aTemp;

	Math::BtVector3ToVector3(axisTemp, axis);
	delete axisTemp;

	angle = angleTemp;
}

void TransformUtil::CalculateVelocity(Matrix transform0, Matrix transform1,
	btScalar timeStep, [Out] Vector3% linVel, [Out] Vector3% angVel)
{
	btTransform* transform0Temp = Math::MatrixToBtTransform(transform0);
	btTransform* transform1Temp = Math::MatrixToBtTransform(transform1);
	btVector3* linVelTemp = new btVector3;
	btVector3* angVelTemp = new btVector3;

	btTransformUtil::calculateVelocity(*transform0Temp, *transform1Temp, timeStep, *linVelTemp, *angVelTemp);

	ALIGNED_DEL(transform0Temp);
	ALIGNED_DEL(transform1Temp);

	Math::BtVector3ToVector3(linVelTemp, linVel);
	Math::BtVector3ToVector3(angVelTemp, angVel);

	delete linVelTemp;
	delete angVelTemp;
}

void TransformUtil::CalculateVelocityQuaternion (Vector3 pos0, Vector3 pos1, Quaternion orn0, Quaternion orn1,
	btScalar timeStep, [Out] Vector3% linVel, [Out] Vector3% angVel)
{
	VECTOR3_DEF(pos0);
	VECTOR3_DEF(pos1);
	btQuaternion* orn0Temp = Math::QuaternionToBtQuat(orn0);
	btQuaternion* orn1Temp = Math::QuaternionToBtQuat(orn1);
	btVector3* linVelTemp = new btVector3;
	btVector3* angVelTemp = new btVector3;

	btTransformUtil::calculateVelocityQuaternion(VECTOR3_USE(pos0), VECTOR3_USE(pos1),
		*orn0Temp, *orn1Temp, timeStep, *linVelTemp, *angVelTemp);

	VECTOR3_DEL(pos0);
	VECTOR3_DEL(pos1);
	delete orn0Temp;
	delete orn1Temp;

	Math::BtVector3ToVector3(linVelTemp, linVel);
	Math::BtVector3ToVector3(angVelTemp, angVel);

	delete linVelTemp;
	delete angVelTemp;
}

void TransformUtil::IntegrateTransform(Matrix curTrans, Vector3 linvel, Vector3 angvel,
	btScalar timeStep, [Out] Matrix% predictedTransform)
{
	btTransform* curTransTemp = Math::MatrixToBtTransform(curTrans);
	VECTOR3_DEF(linvel);
	VECTOR3_DEF(angvel);
	btTransform* predictedTransformTemp = ALIGNED_ALLOC(btTransform);

	btTransformUtil::integrateTransform(*curTransTemp, VECTOR3_USE(linvel), VECTOR3_USE(angvel), timeStep, *predictedTransformTemp);

	ALIGNED_DEL(curTransTemp);
	VECTOR3_DEL(linvel);
	VECTOR3_DEL(angvel);

	Math::BtTransformToMatrix(predictedTransformTemp, predictedTransform);
	ALIGNED_DEL(predictedTransformTemp);
}

ConvexSeparatingDistanceUtil::ConvexSeparatingDistanceUtil(btScalar boundingRadiusA, btScalar boundingRadiusB)
{
	_util = new btConvexSeparatingDistanceUtil(boundingRadiusA, boundingRadiusB);
}

void ConvexSeparatingDistanceUtil::InitSeparatingDistance(Vector3 separatingVector, btScalar separatingDistance, Matrix transA, Matrix transB)
{
	VECTOR3_DEF(separatingVector);
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	_util->initSeparatingDistance(VECTOR3_USE(separatingVector), separatingDistance, *transATemp, *transBTemp);

	VECTOR3_DEL(separatingVector);
	ALIGNED_DEL(transATemp);
	ALIGNED_DEL(transBTemp);
}

void ConvexSeparatingDistanceUtil::UpdateSeparatingDistance(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	_util->updateSeparatingDistance(*transATemp, *transBTemp);

	ALIGNED_DEL(transATemp);
	ALIGNED_DEL(transBTemp);
}

btScalar ConvexSeparatingDistanceUtil::ConservativeSeparatingDistance::get()
{
	return _util->getConservativeSeparatingDistance();
}
