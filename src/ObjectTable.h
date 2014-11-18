#pragma once

namespace BulletSharp
{
	ref class ObjectTable sealed
	{
	private:
		static Dictionary<intptr_t, Object^>^ objectTable;

		static ObjectTable();

	public:
		static void Add(Object^ obj, void* unmanagedPointer);
		static bool Contains(intptr_t unmanagedPointer);
		static bool Contains(Object^ managedObject);
		static void Remove(void* unmanagedPointer);

		generic<class T>
		static T GetObject(intptr_t unmanagedPointer);
		static intptr_t GetUnmanagedObject(Object^ unmanagedPointer);
	};
};
