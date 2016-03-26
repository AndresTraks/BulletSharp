#pragma once

namespace BulletSharp
{
	class MotionStateWrapper;

	public ref class MotionState abstract
	{
	internal:
		btMotionState* _native;

		MotionState(btMotionState* native);

		~MotionState();
		!MotionState();

	protected:
		MotionState();

	public:
		virtual property Matrix WorldTransform
		{
			Matrix get() abstract;
			void set(Matrix worldTrans) abstract;
		}
	};

	class MotionStateWrapper : public btMotionState
	{
	public:
		gcroot<MotionState^> _motionState;

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
