#pragma once

namespace BulletSharp
{
	public ref class TypedObject
	{
	internal:
		bool _preventDelete;
		btTypedObject* _native;

		TypedObject(btTypedObject* native, bool preventDelete);

	public:
		!TypedObject();
	protected:
		~TypedObject();

	public:
		property ObjectType ObjectType
		{
			BulletSharp::ObjectType get();
			void set(BulletSharp::ObjectType value);
		}
	};
};
