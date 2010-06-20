#include "StdAfx.h"

#include "TransformUtil.h"

void TransformUtil::CalculateDiffAxisAngle(Matrix transform0, Matrix transform1,
	[Out] Vector3% axis, [Out] btScalar% angle)
{
	btTransform* transform0Temp = Math::MatrixToBtTransform(transform0);
	btTransform* transform1Temp = Math::MatrixToBtTransform(transform1);
	btVector3* axisTemp = new btVector3();
	btScalar angleTemp;

	btTransformUtil::calculateDiffAxisAngle(*transform0Temp, *transform1Temp, *axisTemp, angleTemp);

	delete transform0Temp;
	delete transform1Temp;

	axis = Math::BtVector3ToVector3(axisTemp);
	delete axisTemp;

	angle = angleTemp;
}

void TransformUtil::CalculateDiffAxisAngleQuaternion(Quaternion orn0, Quaternion orn1a,
	[Out] Vector3% axis, [Out] btScalar% angle)
{
	btQuaternion* orn0Temp = Math::QuaternionToBtQuat(orn0);
	btQuaternion* orn1aTemp = Math::QuaternionToBtQuat(orn1a);
	btVector3* axisTemp = new btVector3();
	btScalar angleTemp;

	btTransformUtil::calculateDiffAxisAngleQuaternion(*orn0Temp, *orn1aTemp, *axisTemp, angleTemp);

	delete orn0Temp;
	delete orn1aTemp;

	axis = Math::BtVector3ToVector3(axisTemp);
	delete axisTemp;

	angle = angleTemp;
}

void TransformUtil::CalculateVelocity(Matrix transform0, Matrix transform1,
	btScalar timeStep, [Out] Vector3% linVel, [Out] Vector3% angVel)
{
	btTransform* transform0Temp = Math::MatrixToBtTransform(transform0);
	btTransform* transform1Temp = Math::MatrixToBtTransform(transform1);
	btVector3* linVelTemp = new btVector3();
	btVector3* angVelTemp = new btVector3();

	btTransformUtil::calculateVelocity(*transform0Temp, *transform1Temp, timeStep, *linVelTemp, *angVelTemp);

	delete transform0Temp;
	delete transform1Temp;

	linVel = Math::BtVector3ToVector3(linVelTemp);
	angVel = Math::BtVector3ToVector3(angVelTemp);

	delete linVelTemp;
	delete angVelTemp;
}

void TransformUtil::CalculateVelocityQuaternion (Vector3 pos0, Vector3 pos1, Quaternion orn0, Quaternion orn1,
	btScalar timeStep, [Out] Vector3% linVel, [Out] Vector3% angVel)
{
	btVector3* pos0Temp = Math::Vector3ToBtVector3(pos0);
	btVector3* pos1Temp = Math::Vector3ToBtVector3(pos1);
	btQuaternion* orn0Temp = Math::QuaternionToBtQuat(orn0);
	btQuaternion* orn1Temp = Math::QuaternionToBtQuat(orn1);
	btVector3* linVelTemp = new btVector3();
	btVector3* angVelTemp = new btVector3();

	btTransformUtil::calculateVelocityQuaternion(*pos0Temp, *pos1Temp,
		*orn0Temp, *orn1Temp, timeStep, *linVelTemp, *angVelTemp);

	delete pos0Temp;
	delete pos1Temp;
	delete orn0Temp;
	delete orn1Temp;

	linVel = Math::BtVector3ToVector3(linVelTemp);
	angVel = Math::BtVector3ToVector3(angVelTemp);

	delete linVelTemp;
	delete angVelTemp;
}

void TransformUtil::IntegrateTransform(Matrix curTrans, Vector3 linvel, Vector3 angvel,
	btScalar timeStep, [Out] Matrix% predictedTransform)
{
	btTransform* curTransTemp = Math::MatrixToBtTransform(curTrans);
	btVector3* linvelTemp = Math::Vector3ToBtVector3(linvel);
	btVector3* angvelTemp = Math::Vector3ToBtVector3(angvel);
	btTransform* predictedTransformTemp = new btTransform();

	btTransformUtil::integrateTransform(*curTransTemp, *linvelTemp, *angvelTemp, timeStep, *predictedTransformTemp);

	delete curTransTemp;
	delete linvelTemp;
	delete angvelTemp;

	predictedTransform = Math::BtTransformToMatrix(predictedTransformTemp);
	delete predictedTransformTemp;
}

ConvexSeparatingDistanceUtil::ConvexSeparatingDistanceUtil(btScalar boundingRadiusA, btScalar boundingRadiusB)
{
	_util = new btConvexSeparatingDistanceUtil(boundingRadiusA, boundingRadiusB);
}

void ConvexSeparatingDistanceUtil::InitSeparatingDistance(Vector3 separatingVector, btScalar separatingDistance, Matrix transA, Matrix transB)
{
	btVector3* separatingVectorTemp = Math::Vector3ToBtVector3(separatingVector);
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	_util->initSeparatingDistance(*separatingVectorTemp, separatingDistance, *transATemp, *transBTemp);

	delete separatingVectorTemp;
	delete transATemp;
	delete transBTemp;
}

void ConvexSeparatingDistanceUtil::UpdateSeparatingDistance(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	_util->updateSeparatingDistance(*transATemp, *transBTemp);

	delete transATemp;
	delete transBTemp;
}

btScalar ConvexSeparatingDistanceUtil::ConservativeSeparatingDistance::get()
{
	return _util->getConservativeSeparatingDistance();
}
