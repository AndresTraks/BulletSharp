#pragma once

namespace BulletSharp
{
	public interface class IDebugDraw
	{
		virtual void Draw3dText(Vector3% location, String^ textString);
		virtual void DrawAabb(Vector3% from, Vector3% to, BtColor color);
		virtual void DrawArc(Vector3% center, Vector3% normal, Vector3% axis, btScalar radiusA,
			btScalar radiusB, btScalar minAngle, btScalar maxAngle, BtColor color,
			bool drawSect, btScalar stepDegrees);
		virtual void DrawArc(Vector3% center, Vector3% normal, Vector3% axis, btScalar radiusA,
			btScalar radiusB, btScalar minAngle, btScalar maxAngle, BtColor color,
			bool drawSect);
		virtual void DrawBox(Vector3% bbMin, Vector3% bbMax, BtColor color);
		virtual void DrawBox(Vector3% bbMin, Vector3% bbMax, Matrix% trans, BtColor color);
		virtual void DrawCapsule(btScalar radius, btScalar halfHeight, int upAxis, Matrix% transform,
			BtColor color);
		virtual void DrawCone(btScalar radius, btScalar height, int upAxis, Matrix% transform,
			BtColor color);
		virtual void DrawContactPoint(Vector3% pointOnB, Vector3% normalOnB, btScalar distance,
			int lifeTime, BtColor color);
		virtual void DrawCylinder(btScalar radius, btScalar halfHeight, int upAxis, Matrix% transform,
			BtColor color);
		virtual void DrawLine(Vector3% from, Vector3% to, BtColor fromColor, BtColor toColor);
		virtual void DrawLine(Vector3% from, Vector3% to, BtColor color);
		virtual void DrawPlane(Vector3% planeNormal, btScalar planeConst, Matrix% transform,
			BtColor color);
		virtual void DrawSphere(Vector3% p, btScalar radius, BtColor color);
		virtual void DrawSphere(btScalar radius, Matrix% transform, BtColor color);
		virtual void DrawSpherePatch(Vector3% center, Vector3% up, Vector3% axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, BtColor color,
			btScalar stepDegrees, bool drawCenter);
		virtual void DrawSpherePatch(Vector3% center, Vector3% up, Vector3% axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, BtColor color,
			btScalar stepDegrees);
		virtual void DrawSpherePatch(Vector3% center, Vector3% up, Vector3% axis, btScalar radius,
			btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, BtColor color);
		virtual void DrawTransform(Matrix% transform, btScalar orthoLen);
		virtual void DrawTriangle(Vector3% v0, Vector3% v1, Vector3% v2, Vector3% __unnamed3,
			Vector3% __unnamed4, Vector3% __unnamed5, BtColor color, btScalar alpha);
		virtual void DrawTriangle(Vector3% v0, Vector3% v1, Vector3% v2, BtColor color, btScalar alpha);
		virtual void FlushLines();
		virtual void ReportErrorWarning(String^ warningString);

		property DebugDrawModes DebugMode
		{
			virtual DebugDrawModes get();
			virtual void set(DebugDrawModes value);
		}
	};
};
