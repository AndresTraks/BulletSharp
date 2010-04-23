#pragma once

#include "Enums.h"

#include <msclr/auto_gcroot.h>

UsingFrameworkNamespace
UsingGraphicsNamespace
using namespace msclr;
using namespace System::Drawing;

namespace BulletSharp
{
	class DebugWrapper;

	public ref class DebugDraw
	{
	private:
		DebugWrapper* _debugDraw;
	internal:
		DebugDraw(DebugWrapper* debugDraw);
	public:
		DebugDraw();

		virtual void DrawLine(Vector3 from, Vector3 to, BtColor color) {};
		virtual void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, BtColor color) {};
		virtual void DrawTriangle(Vector3 v0, Vector3 v1, BtColor color) {};

		void SetDebugMode(DebugDrawModes debugMode);

	internal:
		property DebugWrapper* UnmanagedPointer
		{
			DebugWrapper* get();
			void set(DebugWrapper* value);
		}
	};

	// Each DebugDraw instance has an unmanaged DebugWrapper instance
	// that receives the drawing commands from Bullet and passes them on
	// to DebugDraw itself.

	class DebugWrapper : public btIDebugDraw
	{
	private:
		int m_debugMode;

	public:
		auto_gcroot<DebugDraw^> _debugDraw;

		virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
		{
			_debugDraw->DrawLine(
				Math::BtVector3ToVector3(&from), Math::BtVector3ToVector3(&to), BtVectorToBtColor(color));
		}

		virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color)
		{
			_debugDraw->DrawBox(
				Math::BtVector3ToVector3(&bbMin), Math::BtVector3ToVector3(&bbMax),	Math::BtTransformToMatrix(&trans), BtVectorToBtColor(color));
		}

		virtual void reportErrorWarning(const char* warningString)
		{
		}

		virtual void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
		{
		}

		virtual void setDebugMode(int debugMode)
		{
			m_debugMode = debugMode;
		}
		virtual int	getDebugMode() const
		{
			return m_debugMode;
		}

		virtual void draw3dText(const btVector3& location,const char* textString)
		{
		}
	};
};
