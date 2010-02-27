#pragma once

#include "Enums.h"

namespace BulletSharp
{
	public ref class TypedObject
	{
	private:
		btTypedObject* _typedObject;
	internal:
		TypedObject(btTypedObject* typedObject);

	public:
		property ObjectType ObjectType
		{
			BulletSharp::ObjectType get();
			void set(BulletSharp::ObjectType value);
		}

	internal:
		property btTypedObject* UnmanagedPointer
		{
			virtual btTypedObject* get();
			void set(btTypedObject* value);
		}
	};
};
