#pragma once

namespace BulletSharp
{
	class MotionStateWrapper;

	public ref class MotionState
	{
	private:
		btMotionState* _motionState;

	internal:
		MotionState(btMotionState* motionState);

	protected:
		MotionState();
		~MotionState();

	public:
		property Matrix WorldTransform
		{
			virtual Matrix get();
			virtual void set(Matrix value);
		}

	internal:
		property btMotionState* UnmanagedPointer
		{
			virtual btMotionState* get();
			void set(btMotionState* value);
		}
	};

	class MotionStateWrapper : public btMotionState
	{
	public:
		auto_gcroot<MotionState^> _motionState;

		virtual void getWorldTransform(btTransform& worldTrans) const
		{
			Math::MatrixToBtTransform(_motionState->WorldTransform, &worldTrans);
		}

		virtual void setWorldTransform(const btTransform& worldTrans)
		{
			_motionState->WorldTransform = Math::BtTransformToMatrix(&worldTrans);
		}
	};
};
