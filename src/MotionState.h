#pragma once

namespace BulletSharp
{
	public ref class MotionState
	{
	private:
		btMotionState* _motionState;

	internal:
		MotionState(btMotionState* motionState);

	protected:
		~MotionState();

	public:
		property Matrix WorldTransform
		{
			virtual Matrix get();
			void set(Matrix value);
		}

	internal:
		property btMotionState* UnmanagedPointer
		{
			virtual btMotionState* get();
			void set( btMotionState* value );
		}
	};
};
