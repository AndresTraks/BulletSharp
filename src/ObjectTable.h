#pragma once

namespace BulletSharp
{
	ref class ObjectTable sealed
	{
	private:
		static System::Collections::Generic::Dictionary<intptr_t, Object^>^ objectTable;

		static ObjectTable();

	public:
		static void Add(Object^ obj, void* unmanagedPointer);
		static bool Contains(intptr_t unmanagedPointer);

		generic<class T>
		static T GetObject(intptr_t unmanagedPointer);
	};
};
