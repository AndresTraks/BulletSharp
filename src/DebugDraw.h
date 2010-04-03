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

#if GRAPHICS_XNA31
		virtual void DrawLine(Vector3 from, Vector3 to, Microsoft::Xna::Framework::Graphics::Color color) {};
		virtual void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Microsoft::Xna::Framework::Graphics::Color color) {};
		virtual void DrawTriangle(Vector3 v0, Vector3 v1, Microsoft::Xna::Framework::Graphics::Color color) {};
#elif GRAPHICS_SLIMDX
		virtual void DrawLine(Vector3 from, Vector3 to, Color4 color) {};
		virtual void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Color4 color) {};
		virtual void DrawTriangle(Vector3 v0, Vector3 v1, Color4 color) {};
#elif GRAPHICS_MOGRE
		virtual void DrawLine(Vector3 from, Vector3 to, Mogre::ColourValue color) {};
		virtual void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Mogre::ColourValue color) {};
		virtual void DrawTriangle(Vector3 v0, Vector3 v1, Mogre::ColourValue color) {};
#elif GRAPHICS_NONE
		virtual void DrawLine(Vector3 from, Vector3 to, Color color) {};
		virtual void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Color color) {};
		virtual void DrawTriangle(Vector3 v0, Vector3 v1, Color color) {};
#endif

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
				Math::BtVector3ToVector3(&from), Math::BtVector3ToVector3(&to),
#if GRAPHICS_XNA31
				Microsoft::Xna::Framework::Graphics::Color(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_SLIMDX
				Color4(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_MOGRE
				Mogre::ColourValue(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_NONE
				Color::FromArgb(255, (int)(color.getX()*255), (int)(color.getY()*255), (int)(color.getY()*255))
#endif
			);
		}

		virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color)
		{
			_debugDraw->DrawBox(
				Math::BtVector3ToVector3(&bbMin), Math::BtVector3ToVector3(&bbMax),	Math::BtTransformToMatrix(&trans),
#if GRAPHICS_XNA31
				Microsoft::Xna::Framework::Graphics::Color(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_SLIMDX
				Color4(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_MOGRE
				Mogre::ColourValue(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_NONE
				Color::FromArgb(255, (int)(color.getX()*255), (int)(color.getY()*255), (int)(color.getY()*255))
#endif
			);
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
