#pragma once

// Fully implemented as of 19 Jun 2010

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btConvexCast.h>
#pragma managed(pop)

#include "IDisposable.h"

#include <msclr/auto_gcroot.h>

using namespace msclr;

namespace BulletSharp
{
	ref class DebugDraw;

	public ref class ConvexCast : BulletSharp::IDisposable
	{
	public:
		ref class CastResult : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btConvexCast::CastResult* _castResult;

		internal:
			CastResult(btConvexCast::CastResult* castResult);

		public:
			!CastResult();
		protected:
			~CastResult();

		public:
			CastResult();

#ifndef DISABLE_DEBUGDRAW
			void DebugDraw (btScalar fraction);
#endif
			void DrawCoordSystem (Matrix trans);

			property btScalar AllowedPenetration
			{
				btScalar get();
				void set(btScalar value);
			}

#ifndef DISABLE_DEBUGDRAW
			property BulletSharp::DebugDraw^ DebugDrawer
			{
				BulletSharp::DebugDraw^ get();
				void set(BulletSharp::DebugDraw^ value);
			}
#endif

			property btScalar Fraction
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 HitPoint
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Matrix HitTransformA
			{
				Matrix get();
				void set(Matrix value);
			}

			property Matrix HitTransformB
			{
				Matrix get();
				void set(Matrix value);
			}

			property Vector3 Normal
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property bool IsDisposed
			{
				virtual bool get();
			}

		internal:
			property btConvexCast::CastResult* UnmanagedPointer
			{
				virtual btConvexCast::CastResult* get();
				void set(btConvexCast::CastResult* value);
			}
		};

		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btConvexCast* _convexCast;

	internal:
		ConvexCast(btConvexCast* convexCast);

	public:
		!ConvexCast();
	protected:
		~ConvexCast();

	public:
		bool CalcTimeOfImpact(Matrix fromA, Matrix toA, Matrix fromB, Matrix toB, CastResult^ result);

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btConvexCast* UnmanagedPointer
		{
			virtual btConvexCast* get();
			void set(btConvexCast* value);
		}
	};
};
