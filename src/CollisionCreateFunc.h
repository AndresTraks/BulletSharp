#pragma once

namespace BulletSharp
{
	ref class CollisionAlgorithm;
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObjectWrapper;

	public ref class CollisionAlgorithmCreateFunc
	{
	internal:
		btCollisionAlgorithmCreateFunc* _native;

	private:
		bool _preventDelete;

	internal:
		CollisionAlgorithmCreateFunc(btCollisionAlgorithmCreateFunc* native, bool preventDelete);

		~CollisionAlgorithmCreateFunc();
		!CollisionAlgorithmCreateFunc();

	public:
		CollisionAlgorithmCreateFunc();

		CollisionAlgorithm^ CreateCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ info,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool Swapped
		{
			bool get();
			void set(bool value);
		}
	};
};
