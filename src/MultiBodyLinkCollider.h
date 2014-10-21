#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class MultiBody;

	public ref class MultiBodyLinkCollider : CollisionObject
	{
	internal:
		MultiBodyLinkCollider(btMultiBodyLinkCollider* native);

	private:
		MultiBody^ _multiBody;

	public:
		MultiBodyLinkCollider(MultiBody^ multiBody, int link);

		static MultiBodyLinkCollider^ Upcast(CollisionObject^ colObj);

		property int Link
		{
			int get();
			void set(int value);
		}

		property BulletSharp::MultiBody^ MultiBody
		{
			BulletSharp::MultiBody^ get();
			void set(BulletSharp::MultiBody^ value);
		}
	};
};
