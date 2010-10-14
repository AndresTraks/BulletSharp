#pragma once

using namespace System::Collections;
using namespace System::Diagnostics;

namespace BulletSharp
{
	[DebuggerDisplay("Count = {Count}")]
	public ref class Vector3Collection : public Generic::ICollection<Vector3>
	{
	private:
		btVector3* _vector3Array;
		int _length;

	public:
		Vector3Collection(btVector3* vector3Array, int length);

		virtual void Add(Vector3 item);
		virtual void Clear();
		virtual bool Contains(Vector3 item);
		virtual void CopyTo(array<Vector3>^ array, int arrayIndex);
		virtual IEnumerator^ GetEnumerator() = System::Collections::IEnumerable::GetEnumerator;
		virtual Generic::IEnumerator<Vector3>^ GetSpecializedEnumerator() = Generic::IEnumerable<Vector3>::GetEnumerator;
		virtual bool Remove(Vector3 item);

		property int Count
		{
			virtual int get()
			{
				return _length;
			}
		}

		property Vector3 default[int]
		{
			Vector3 get(int i);
			void set(int index, Vector3 value);
		}

		property bool IsReadOnly
		{
			virtual bool get();
		}

	internal:
		property btVector3* UnmanagedPointer
		{
			btVector3* get()
			{
				return _vector3Array;
			}
		}
	};

	public ref class Vector3Enumerator : IEnumerator, Generic::IEnumerator<Vector3>
	{
	private:
		Vector3Collection^ _vector3Collection;
		int i;

	public:
		Vector3Enumerator(Vector3Collection^ vector3Collection);
		~Vector3Enumerator(){}

		property Vector3 GenericCurrent
		{
			virtual Vector3 get() = Generic::IEnumerator<Vector3>::Current::get;
		}

		property Object^ Current
		{
			virtual Object^ get() = IEnumerator::Current::get;;
		}

		virtual bool MoveNext();
		virtual void Reset();
	};
};
