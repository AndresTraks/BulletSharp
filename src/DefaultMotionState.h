#pragma once

#include "MotionState.h"

namespace BulletSharp
{
	public ref class DefaultMotionState : MotionState
	{
	private:
		Object^ _userObject;

	public:
		DefaultMotionState(Matrix startTrans, Matrix centerOfMassOffset);
		DefaultMotionState(Matrix startTrans);
		DefaultMotionState();

		property Matrix CenterOfMassOffset
		{
			Matrix get();
			void set(Matrix value);
		}

		property Matrix GraphicsWorldTrans
		{
			Matrix get();
			void set(Matrix value);
		}

		property Matrix StartWorldTrans
		{
			Matrix get();
			void set(Matrix value);
		}

		property Object^ UserObject
		{
			Object^ get();
			void set(Object^ value);
		}

		virtual property Matrix WorldTransform
		{
			Matrix get() override;
			void set(Matrix value) override;
		}

		void GetWorldTransform([Out] Matrix% transform);
	};
};
