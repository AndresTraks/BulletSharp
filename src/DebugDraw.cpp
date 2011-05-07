#include "StdAfx.h"

#ifndef DISABLE_DEBUGDRAW

#include "DebugDraw.h"
#include "StringConv.h"

DebugDraw::DebugDraw()
{
	_debugDraw = new DebugDrawWrapper(this);
	_debugDraw->setDebugMode(0);
}

DebugDraw::DebugDraw(DebugDrawWrapper* debugDraw)
{
	_debugDraw = debugDraw;
}

IDebugDraw^ DebugDraw::GetManaged(btIDebugDraw* debugDraw)
{
	// Compare to 0 before checking the table here since debugDraw is normally 0.
	if (debugDraw == 0)
		return nullptr;

	if (ObjectTable::Contains((intptr_t)debugDraw))
		return ObjectTable::GetObject<IDebugDraw^>((intptr_t)debugDraw);

	return ((DebugDrawWrapper*)debugDraw)->getDebugDraw();
}

DebugDrawWrapper* DebugDraw::GetUnmanaged(IDebugDraw^ debugDraw)
{
	if (debugDraw == nullptr)
		return 0;

	DebugDraw^ cast = dynamic_cast<DebugDraw^>(debugDraw);
	if (cast != nullptr)
		return cast->UnmanagedPointer;

	if (ObjectTable::Contains(debugDraw))
		return (BulletSharp::DebugDrawWrapper*)ObjectTable::GetUnmanagedObject(debugDraw);

	DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDraw);
	ObjectTable::Add(debugDraw, wrapper);

	return wrapper;
}

void DebugDraw::Draw3dText(Vector3 location, String^ textString)
{
/*
	btVector3* locationTemp = Math::Vector3ToBtVector3(location);
	const char* textStringTemp = StringConv::ManagedToUnmanaged(textString);
	
	_debugDraw->baseDraw3dText(*locationTemp, textStringTemp);
	
	delete locationTemp;
	StringConv::FreeUnmanagedString(textStringTemp);
*/
}

void DebugDraw::DrawAabb(Vector3 from, Vector3 to, BtColor color)
{
	btVector3* fromTemp = Math::Vector3ToBtVector3(from);
	btVector3* toTemp = Math::Vector3ToBtVector3(to);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawAabb(*fromTemp, *toTemp, *colorTemp);

	delete fromTemp;
	delete toTemp;
	delete colorTemp;
}

void DebugDraw::DrawArc(Vector3 center, Vector3 normal, Vector3 axis, btScalar radiusA, btScalar radiusB,
	btScalar minAngle, btScalar maxAngle, BtColor color, bool drawSect, btScalar stepDegrees)
{
	btVector3* centerTemp = Math::Vector3ToBtVector3(center);
	btVector3* normalTemp = Math::Vector3ToBtVector3(normal);
	btVector3* axisTemp = Math::Vector3ToBtVector3(axis);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawArc(*centerTemp, *normalTemp, *axisTemp, radiusA, radiusB, minAngle, maxAngle, *colorTemp, drawSect, stepDegrees);

	delete centerTemp;
	delete normalTemp;
	delete axisTemp;
	delete colorTemp;
}

void DebugDraw::DrawArc(Vector3 center, Vector3 normal, Vector3 axis, btScalar radiusA, btScalar radiusB,
	btScalar minAngle, btScalar maxAngle, BtColor color, bool drawSect)
{
	btVector3* centerTemp = Math::Vector3ToBtVector3(center);
	btVector3* normalTemp = Math::Vector3ToBtVector3(normal);
	btVector3* axisTemp = Math::Vector3ToBtVector3(axis);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawArc(*centerTemp, *normalTemp, *axisTemp, radiusA, radiusB, minAngle, maxAngle, *colorTemp, drawSect);

	delete centerTemp;
	delete normalTemp;
	delete axisTemp;
	delete colorTemp;
}

void DebugDraw::DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, BtColor color)
{
	btVector3* bbMinTemp = Math::Vector3ToBtVector3(bbMin);
	btVector3* bbMaxTemp = Math::Vector3ToBtVector3(bbMax);
	btTransform* transTemp = Math::MatrixToBtTransform(trans);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawBox(*bbMinTemp, *bbMaxTemp, *transTemp, *colorTemp);
	
	delete bbMinTemp;
	delete bbMaxTemp;
	delete transTemp;
	delete colorTemp;
};

void DebugDraw::DrawBox(Vector3 bbMin, Vector3 bbMax, BtColor color)
{
	btVector3* bbMinTemp = Math::Vector3ToBtVector3(bbMin);
	btVector3* bbMaxTemp = Math::Vector3ToBtVector3(bbMax);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawBox(*bbMinTemp, *bbMaxTemp, *colorTemp);

	delete bbMinTemp;
	delete bbMaxTemp;
	delete colorTemp;
};

void DebugDraw::DrawCapsule(btScalar radius, btScalar halfHeight, int upAxis, Matrix transform, BtColor color)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawCapsule(radius, halfHeight, upAxis, *transformTemp, *colorTemp);

	delete transformTemp;
	delete colorTemp;
}

void DebugDraw::DrawCone(btScalar radius, btScalar height, int upAxis, Matrix transform, BtColor color)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawCone(radius, height, upAxis, *transformTemp, *colorTemp);

	delete transformTemp;
	delete colorTemp;
}

void DebugDraw::DrawContactPoint(Vector3 pointOnB, Vector3 normalOnB, btScalar distance, int lifeTime, BtColor color)
{
/*
	btVector3* pointOnBTemp = Math::Vector3ToBtVector3(pointOnB);
	btVector3* normalOnBTemp = Math::Vector3ToBtVector3(normalOnB);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawContactPoint(*pointOnBTemp, *normalOnBTemp, distance, lifeTime, *colorTemp);

	delete pointOnBTemp;
	delete normalOnBTemp;
	delete colorTemp;
*/
}

void DebugDraw::DrawCylinder(btScalar radius, btScalar halfHeight, int upAxis, Matrix transform, BtColor color)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawCylinder(radius, halfHeight, upAxis, *transformTemp, *colorTemp);

	delete transformTemp;
	delete colorTemp;
}

void DebugDraw::DrawLine(Vector3 from, Vector3 to, BtColor fromColor, BtColor toColor)
{
	btVector3* fromTemp = Math::Vector3ToBtVector3(from);
	btVector3* toTemp = Math::Vector3ToBtVector3(to);
	btVector3* fromColorTemp = BtColorToBtVector(fromColor);
	btVector3* toColorTemp = BtColorToBtVector(toColor);

	_debugDraw->baseDrawLine(*fromTemp, *toTemp, *fromColorTemp, *toColorTemp);

	delete fromTemp;
	delete toTemp;
	delete fromColorTemp;
	delete toColorTemp;
};

void DebugDraw::DrawPlane(Vector3 planeNormal, btScalar planeConst, Matrix transform, BtColor color)
{
	btVector3* planeNormalTemp = Math::Vector3ToBtVector3(planeNormal);
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawPlane(*planeNormalTemp, planeConst, *transformTemp, *colorTemp);

	delete planeNormalTemp;
	delete transformTemp;
	delete colorTemp;
}

void DebugDraw::DrawSphere(Vector3 p, btScalar radius, BtColor color)
{
	btVector3* pTemp = Math::Vector3ToBtVector3(p);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawSphere(*pTemp, radius, *colorTemp);

	delete pTemp;
	delete colorTemp;
}

void DebugDraw::DrawSphere(btScalar radius, Matrix transform, BtColor color)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawSphere(radius, *transformTemp, *colorTemp);

	delete transformTemp;
	delete colorTemp;
}

void DebugDraw::DrawSpherePatch(Vector3 center, Vector3 up, Vector3 axis, btScalar radius, btScalar minTh, btScalar maxTh,
	btScalar minPs, btScalar maxPs, BtColor color, btScalar stepDegrees)
{
	btVector3* centerTemp = Math::Vector3ToBtVector3(center);
	btVector3* upTemp = Math::Vector3ToBtVector3(up);
	btVector3* axisTemp = Math::Vector3ToBtVector3(axis);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawSpherePatch(*centerTemp, *upTemp, *axisTemp, radius, minTh, maxTh, minPs, maxPs, *colorTemp, stepDegrees);

	delete centerTemp;
	delete upTemp;
	delete axisTemp;
	delete colorTemp;
}

void DebugDraw::DrawSpherePatch(Vector3 center, Vector3 up, Vector3 axis, btScalar radius, btScalar minTh, btScalar maxTh,
	btScalar minPs, btScalar maxPs, BtColor color)
{
	btVector3* centerTemp = Math::Vector3ToBtVector3(center);
	btVector3* upTemp = Math::Vector3ToBtVector3(up);
	btVector3* axisTemp = Math::Vector3ToBtVector3(axis);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawSpherePatch(*centerTemp, *upTemp, *axisTemp, radius, minTh, maxTh, minPs, maxPs, *colorTemp);

	delete centerTemp;
	delete upTemp;
	delete axisTemp;
	delete colorTemp;
}

void DebugDraw::DrawTransform(Matrix transform, btScalar orthoLen)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);

	_debugDraw->baseDrawTransform(*transformTemp, orthoLen);

	delete transformTemp;
}

void DebugDraw::DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, BtColor color, btScalar)
{
	btVector3* v0Temp = Math::Vector3ToBtVector3(v0);
	btVector3* v1Temp = Math::Vector3ToBtVector3(v1);
	btVector3* v2Temp = Math::Vector3ToBtVector3(v2);
	btVector3* colorTemp = BtColorToBtVector(color);

	_debugDraw->baseDrawTriangle(*v0Temp, *v1Temp, *v2Temp, *colorTemp, 0);

	delete v0Temp;
	delete v1Temp;
	delete v2Temp;
	delete colorTemp;
}

void DebugDraw::DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Vector3, Vector3, Vector3, BtColor color, btScalar alpha)
{
	btVector3* v0Temp = Math::Vector3ToBtVector3(v0);
	btVector3* v1Temp = Math::Vector3ToBtVector3(v1);
	btVector3* v2Temp = Math::Vector3ToBtVector3(v2);
	btVector3* colorTemp = BtColorToBtVector(color);
	btVector3* none = new btVector3();

	_debugDraw->baseDrawTriangle(*v0Temp, *v1Temp, *v2Temp, *none, *none, *none, *colorTemp, alpha);

	delete v0Temp;
	delete v1Temp;
	delete v2Temp;
	delete colorTemp;
	delete none;
}

void DebugDraw::ReportErrorWarning(String^ warningString)
{
/*
	const char* warningStringTemp = StringConv::ManagedToUnmanaged(warningString);

	_debugDraw->baseReportErrorWarning(warningStringTemp);

	StringConv::FreeUnmanagedString(warningStringTemp);
*/
}

DebugDrawModes DebugDraw::DebugMode::get()
{
	return m_debugMode;
}
void DebugDraw::DebugMode::set(DebugDrawModes value)
{
	m_debugMode = value;
}

DebugDrawWrapper* DebugDraw::UnmanagedPointer::get()
{
	return _debugDraw;
}
void DebugDraw::UnmanagedPointer::set(DebugDrawWrapper* value)
{
	_debugDraw = value;
}


DebugDrawWrapper::DebugDrawWrapper(IDebugDraw^ debugDraw)
{
	_debugDraw = debugDraw;
}

DebugDrawWrapper::~DebugDrawWrapper()
{
	ObjectTable::Remove(this);
}

IDebugDraw^ DebugDrawWrapper::getDebugDraw()
{
	return _debugDraw.get();
}

void DebugDrawWrapper::setDebugDraw(IDebugDraw^ value)
{
	_debugDraw.attach(value);
}

void DebugDrawWrapper::draw3dText(const btVector3& location, const char* textString)
{
	_debugDraw->Draw3dText(Math::BtVector3ToVector3(&location), StringConv::UnmanagedToManaged(textString));
}

void DebugDrawWrapper::drawAabb(const btVector3& from, const btVector3& to, const btVector3& color)
{
	_debugDraw->DrawAabb(
		Math::BtVector3ToVector3(&from), Math::BtVector3ToVector3(&to), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
	btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
	const btVector3& color, bool drawSect, btScalar stepDegrees)
{
	_debugDraw->DrawArc(Math::BtVector3ToVector3(&center), Math::BtVector3ToVector3(&normal), Math::BtVector3ToVector3(&axis),
		radiusA, radiusB, minAngle, maxAngle, BtVectorToBtColor(color), drawSect, stepDegrees);
}

void DebugDrawWrapper::drawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
	btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
	const btVector3& color, bool drawSect)
{
	_debugDraw->DrawArc(Math::BtVector3ToVector3(&center), Math::BtVector3ToVector3(&normal), Math::BtVector3ToVector3(&axis),
		radiusA, radiusB, minAngle, maxAngle, BtVectorToBtColor(color), drawSect);
}

void DebugDrawWrapper::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color)
{
	_debugDraw->DrawBox(
		Math::BtVector3ToVector3(&bbMin), Math::BtVector3ToVector3(&bbMax),	Math::BtTransformToMatrix(&trans), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color)
{
	_debugDraw->DrawBox(
		Math::BtVector3ToVector3(&bbMin), Math::BtVector3ToVector3(&bbMax),	BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color)
{
	_debugDraw->DrawCapsule(radius, halfHeight, upAxis, Math::BtTransformToMatrix(&transform), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawCone(btScalar radius, btScalar height, int upAxis, const btTransform& transform, const btVector3& color)
{
	_debugDraw->DrawCone(radius, height, upAxis, Math::BtTransformToMatrix(&transform), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	_debugDraw->DrawContactPoint(Math::BtVector3ToVector3(&PointOnB), Math::BtVector3ToVector3(&normalOnB),
		distance, lifeTime, BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawCylinder(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color)
{
	_debugDraw->DrawCylinder(radius, halfHeight, upAxis, Math::BtTransformToMatrix(&transform), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	_debugDraw->DrawLine(
		Math::BtVector3ToVector3(&from), Math::BtVector3ToVector3(&to), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	_debugDraw->DrawLine(
		Math::BtVector3ToVector3(&from), Math::BtVector3ToVector3(&to), BtVectorToBtColor(fromColor), BtVectorToBtColor(toColor));
}

void DebugDrawWrapper::drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& transform, const btVector3& color)
{
	_debugDraw->DrawPlane(Math::BtVector3ToVector3(&planeNormal), planeConst, Math::BtTransformToMatrix(&transform), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{
	_debugDraw->DrawSphere(Math::BtVector3ToVector3(&p), radius, BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawSphere(btScalar radius, const btTransform& transform, const btVector3& color)
{
	_debugDraw->DrawSphere(radius, Math::BtTransformToMatrix(&transform), BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
	btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees)
{
	_debugDraw->DrawSpherePatch(Math::BtVector3ToVector3(&center), Math::BtVector3ToVector3(&up), Math::BtVector3ToVector3(&axis),
		radius, minTh, maxTh, minPs, maxPs, BtVectorToBtColor(color), stepDegrees);
}

void DebugDrawWrapper::drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
	btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color)
{
	_debugDraw->DrawSpherePatch(Math::BtVector3ToVector3(&center), Math::BtVector3ToVector3(&up), Math::BtVector3ToVector3(&axis),
		radius, minTh, maxTh, minPs, maxPs, BtVectorToBtColor(color));
}

void DebugDrawWrapper::drawTransform(const btTransform& transform, btScalar orthoLen)
{
	_debugDraw->DrawTransform(Math::BtTransformToMatrix(&transform), orthoLen);
}

void DebugDrawWrapper::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar)
{
	_debugDraw->DrawTriangle(Math::BtVector3ToVector3(&v0), Math::BtVector3ToVector3(&v1), Math::BtVector3ToVector3(&v2),
		BtVectorToBtColor(color), 0);
}

void DebugDrawWrapper::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2,
	const btVector3& n0, const btVector3& n1, const btVector3& n2, const btVector3& color, btScalar alpha)
{
	_debugDraw->DrawTriangle(Math::BtVector3ToVector3(&v0), Math::BtVector3ToVector3(&v1), Math::BtVector3ToVector3(&v2),
		Math::BtVector3ToVector3(&n0), Math::BtVector3ToVector3(&n1), Math::BtVector3ToVector3(&n2), BtVectorToBtColor(color), alpha);
}

/*
void DebugDrawWrapper::baseDraw3dText(const btVector3& location,const char* textString)
{
	btIDebugDraw::draw3dText(location, textString);
}
*/

void DebugDrawWrapper::baseDrawAabb(const btVector3& from, const btVector3& to, const btVector3& color)
{
	btIDebugDraw::drawAabb(from, to, color);
}

void DebugDrawWrapper::baseDrawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
	btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
	const btVector3& color, bool drawSect, btScalar stepDegrees)
{
	btIDebugDraw::drawArc(center, normal, axis, radiusA, radiusB, minAngle, maxAngle, color, drawSect, stepDegrees);
}

void DebugDrawWrapper::baseDrawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
	btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
	const btVector3& color, bool drawSect)
{
	btIDebugDraw::drawArc(center, normal, axis, radiusA, radiusB, minAngle, maxAngle, color, drawSect);
}

void DebugDrawWrapper::baseDrawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color)
{
	btIDebugDraw::drawBox(bbMin, bbMax, trans, color);
}

void DebugDrawWrapper::baseDrawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color)
{
	btIDebugDraw::drawBox(bbMin, bbMax, color);
}

void DebugDrawWrapper::baseDrawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color)
{
	btIDebugDraw::drawCapsule(radius, halfHeight, upAxis, transform, color);
}

void DebugDrawWrapper::baseDrawCone(btScalar radius, btScalar height, int upAxis, const btTransform& transform, const btVector3& color)
{
	btIDebugDraw::drawCone(radius, height, upAxis, transform, color);
}

/*
void DebugDrawWrapper::baseDrawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	btIDebugDraw::drawContactPoint(PointOnB, normalOnB, distance, lifeTime, color);
}
*/

void DebugDrawWrapper::baseDrawCylinder(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color)
{
	btIDebugDraw::drawCylinder(radius, halfHeight, upAxis, transform, color);
}

void DebugDrawWrapper::baseDrawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	btIDebugDraw::drawLine(from, to, fromColor, toColor);
}

void DebugDrawWrapper::baseDrawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& transform, const btVector3& color)
{
	btIDebugDraw::drawPlane(planeNormal, planeConst, transform, color);
}

void DebugDrawWrapper::baseDrawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{
	btIDebugDraw::drawSphere(p, radius, color);
}

void DebugDrawWrapper::baseDrawSphere(btScalar radius, const btTransform& transform, const btVector3& color)
{
	btIDebugDraw::drawSphere(radius, transform, color);
}

void DebugDrawWrapper::baseDrawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
	btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees)
{
	btIDebugDraw::drawSpherePatch(center, up, axis, radius, minTh, maxTh, minPs, maxPs, color, stepDegrees);
}

void DebugDrawWrapper::baseDrawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
	btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color)
{
	btIDebugDraw::drawSpherePatch(center, up, axis, radius, minTh, maxTh, minPs, maxPs, color);
}

void DebugDrawWrapper::baseDrawTransform(const btTransform& transform, btScalar orthoLen)
{
	btIDebugDraw::drawTransform(transform, orthoLen);
}

void DebugDrawWrapper::baseDrawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar)
{
	btIDebugDraw::drawTriangle(v0, v1, v2, color, 0);
}

void DebugDrawWrapper::baseDrawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2,
	const btVector3& n0, const btVector3& n1, const btVector3& n2, const btVector3& color, btScalar alpha)
{
	btIDebugDraw::drawTriangle(v0, v1, v2, n0, n1, n2, color, alpha);
}

void DebugDrawWrapper::reportErrorWarning(const char* warningString)
{
	_debugDraw->ReportErrorWarning(StringConv::UnmanagedToManaged(warningString));
}

/*
void DebugDrawWrapper::baseReportErrorWarning(const char* warningString)
{
	btIDebugDraw::reportErrorWarning(warningString);
}
*/

void DebugDrawWrapper::setDebugMode(int debugMode)
{
	_debugDraw->DebugMode = (BulletSharp::DebugDrawModes)debugMode;
}
int	DebugDrawWrapper::getDebugMode() const
{
	return (int)_debugDraw->DebugMode;
}

#endif
