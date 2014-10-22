#pragma once

namespace BulletSharp
{
	public ref class TypedObject : IDisposable
	{
	internal:
		btTypedObject* _native;

		TypedObject(btTypedObject* native);

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
