#pragma once

namespace BulletSharp
{
	public ref class TypedObject
	{
	internal:
		btTypedObject* _unmanaged;
		TypedObject(btTypedObject* typedObject);

	public:
		property ObjectType ObjectType
		{
			BulletSharp::ObjectType get();
			void set(BulletSharp::ObjectType value);
		}
	};
};
