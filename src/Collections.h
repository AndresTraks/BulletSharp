#pragma once

using namespace System::Collections;
using namespace System::Diagnostics;

namespace BulletSharp
{
	ref class Vector3List;
	ref class Vector3ListDebugView
	{
	private:
		Vector3List^ _list;

	public:
		Vector3ListDebugView(Vector3List^ collection);

		[DebuggerBrowsable(DebuggerBrowsableState::RootHidden)]
		property array<Vector3>^ Items
		{
			array<Vector3>^ get();
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(Vector3ListDebugView::typeid)]
	public ref class Vector3List : public Generic::IList<Vector3>
	{
	private:
		btVector3* _vector3Array;
		int _length;
		bool isReadOnly;

	internal:
		Vector3List(btVector3* vector3Array, int length);
		Vector3List(const btVector3* vector3Array, int length);

	public:
		virtual void Add(Vector3 item);
		virtual void Clear();
		virtual bool Contains(Vector3 item);
		virtual void CopyTo(array<Vector3>^ array, int arrayIndex);
		virtual IEnumerator^ GetEnumerator() = System::Collections::IEnumerable::GetEnumerator;
		virtual Generic::IEnumerator<Vector3>^ GetSpecializedEnumerator() = Generic::IEnumerable<Vector3>::GetEnumerator;
		virtual int IndexOf(Vector3 item);
		virtual void Insert(int index, Vector3 item);
		virtual bool Remove(Vector3 item);
		virtual void RemoveAt(int index);

		property int Count
		{
			virtual int get()
			{
				return _length;
			}
		}

		property Vector3 default[int]
		{
			virtual Vector3 get(int i);
			virtual void set(int index, Vector3 value);
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
		Vector3List^ _vector3List;
		int i;

	public:
		Vector3Enumerator(Vector3List^ vector3List);
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
