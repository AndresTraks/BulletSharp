#pragma once

#include "IDebugDraw.h"

namespace BulletSharp
{
	class DebugDrawWrapper;

	public ref class DebugDraw abstract : public IDebugDraw, ITrackingDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		DebugDrawWrapper* _native;

	internal:
		DebugDraw(DebugDrawWrapper* debugDraw);

	public:
		!DebugDraw();
	protected:
		~DebugDraw();

	public:
		DebugDraw();

		virtual void Draw3dText(Vector3% location, String^ textString) = 0;
		virtual void DrawAabb(Vector3% from, Vector3% to, BtColor color);
		virtual void DrawArc(Vector3% center, Vector3% normal, Vector3% axis, btScalar radiusA, btScalar radiusB,
			btScalar minAngle, btScalar maxAngle, BtColor color, bool drawSect, btScalar stepDegrees);
		virtual void DrawArc(Vector3% center, Vector3% normal, Vector3% axis, btScalar radiusA, btScalar radiusB,
			btScalar minAngle, btScalar maxAngle, BtColor color, bool drawSect);
		virtual void DrawBox(Vector3% bbMin, Vector3% bbMax, Matrix% trans, BtColor color);
		virtual void DrawBox(Vector3% bbMin, Vector3% bbMax, BtColor color);
		virtual void DrawCapsule(btScalar radius, btScalar halfHeight, int upAxis, Matrix% transform, BtColor color);
		virtual void DrawCone(btScalar radius, btScalar height, int upAxis, Matrix% transform, BtColor color);
		virtual void DrawContactPoint(Vector3% pointOnB, Vector3% normalOnB, btScalar distance, int lifeTime, BtColor color) = 0;
		virtual void DrawCylinder(btScalar radius, btScalar halfHeight, int upAxis, Matrix% transform, BtColor color);
		virtual void DrawLine(Vector3% from, Vector3% to, BtColor color) = 0;
		virtual void DrawLine(Vector3% from, Vector3% to, BtColor fromColor, BtColor toColor);
		virtual void DrawPlane(Vector3% planeNormal, btScalar planeConst, Matrix% transform, BtColor color);
		virtual void DrawSphere(Vector3% p, btScalar radius, BtColor color);
		virtual void DrawSphere(btScalar radius, Matrix% transform, BtColor color);
		virtual void DrawSpherePatch(Vector3% center, Vector3% up, Vector3% axis, btScalar radius, btScalar minTh, btScalar maxTh,
			btScalar minPs, btScalar maxPs, BtColor color, btScalar stepDegrees, bool drawCenter);
		virtual void DrawSpherePatch(Vector3% center, Vector3% up, Vector3% axis, btScalar radius, btScalar minTh, btScalar maxTh,
			btScalar minPs, btScalar maxPs, BtColor color, btScalar stepDegrees);
		virtual void DrawSpherePatch(Vector3% center, Vector3% up, Vector3% axis, btScalar radius, btScalar minTh, btScalar maxTh,
			btScalar minPs, btScalar maxPs, BtColor color);
		virtual void DrawTransform(Matrix% transform, btScalar orthoLen);
		virtual void DrawTriangle(Vector3% v0, Vector3% v1, Vector3% v2, BtColor color, btScalar);
		virtual void DrawTriangle(Vector3% v0, Vector3% v1, Vector3% v2, Vector3%, Vector3%, Vector3%, BtColor color, btScalar alpha);

		virtual void FlushLines();
		virtual void ReportErrorWarning(String^ warningString) = 0;

		property bool IsDisposed
		{
			virtual bool get();
		}

		property DebugDrawModes DebugMode
		{
			virtual DebugDrawModes get() = 0;
			virtual void set(DebugDrawModes value) = 0;
		}
	};

	// Each DebugDraw instance has an unmanaged DebugDrawWrapper instance
	// that receives the drawing commands from Bullet and passes them on
	// to DebugDraw itself.

	class DebugDrawWrapper : public btIDebugDraw
	{
	public:
		GCHandle _debugDraw;

		DebugDrawWrapper(IDebugDraw^ debugDraw, bool weakReference);
		virtual ~DebugDrawWrapper();

		virtual void draw3dText(const btVector3& location, const char* textString);
		virtual void drawAabb(const btVector3& from, const btVector3& to, const btVector3& color);
		virtual void drawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
			btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
			const btVector3& color, bool drawSect, btScalar stepDegrees);
		virtual void drawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
			btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
			const btVector3& color, bool drawSect);
		virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color);
		virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color);
		virtual void drawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color);
		virtual void drawCone(btScalar radius, btScalar height, int upAxis, const btTransform& transform, const btVector3& color);
		virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
		virtual void drawCylinder(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color);
		virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
		virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
		virtual void drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& transform, const btVector3& color);
		virtual void drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
		virtual void drawSphere(btScalar radius, const btTransform& transform, const btVector3& color);
		virtual void drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees, bool drawCenter);
		virtual void drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees);
		virtual void drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color);
		virtual void drawTransform(const btTransform& transform, btScalar orthoLen);
		virtual void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar);
		virtual void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2,
			const btVector3&, const btVector3&, const btVector3&, const btVector3& color, btScalar alpha);

		virtual void baseDrawAabb(const btVector3& from, const btVector3& to, const btVector3& color);
		virtual void baseDrawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
			btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
			const btVector3& color, bool drawSect, btScalar stepDegrees);
		virtual void baseDrawArc(const btVector3& center, const btVector3& normal, const btVector3& axis,
			btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle,
			const btVector3& color, bool drawSect);
		virtual void baseDrawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color);
		virtual void baseDrawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color);
		virtual void baseDrawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color);
		virtual void baseDrawCone(btScalar radius, btScalar height, int upAxis, const btTransform& transform, const btVector3& color);
		virtual void baseDrawCylinder(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color);
		virtual void baseDrawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
		virtual void baseDrawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& transform, const btVector3& color);
		virtual void baseDrawSphere(const btVector3& p, btScalar radius, const btVector3& color);
		virtual void baseDrawSphere(btScalar radius, const btTransform& transform, const btVector3& color);
		virtual void baseDrawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees, bool drawCenter);
		virtual void baseDrawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees);
		virtual void baseDrawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color);
		virtual void baseDrawTransform(const btTransform& transform, btScalar orthoLen);
		virtual void baseDrawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar);
		virtual void baseDrawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2,
			const btVector3&, const btVector3&, const btVector3&, const btVector3& color, btScalar alpha);

		virtual void flushLines();
		virtual void reportErrorWarning(const char* warningString);

		virtual void setDebugMode(int debugMode);
		virtual int	getDebugMode() const;
	};
};
