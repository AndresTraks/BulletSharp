#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class MultiBody;

	public ref class MultiBodyLinkCollider : CollisionObject
	{
		MultiBody^ _multiBody;

	internal:
		MultiBodyLinkCollider(btMultiBodyLinkCollider* native);

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
