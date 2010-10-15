#include "StdAfx.h"
#include "Collections.h"

ListDebugView::ListDebugView(IEnumerable^ list)
{
	_list = list;
}

array<Object^>^ ListDebugView::Items::get()
{
	ArrayList^ list = gcnew ArrayList();
	for each(Object^ o in _list)
	{
		list->Add(o);
	}
	array<Object^>^ arr = gcnew array<Object^>(list->Count);
	list->CopyTo(arr, 0);
	return arr;
}


generic<class T>
ListEnumerator<T>::ListEnumerator(Generic::IList<T>^ list)
{
	_list = list;
}

generic<class T>
T ListEnumerator<T>::GenericCurrent::get()
{
	return _list[i];
}

generic<class T>
Object^ ListEnumerator<T>::Current::get()
{
	return GenericCurrent::get();
}

generic<class T>
bool ListEnumerator<T>::MoveNext()
{
	i++;
	return (i < _list->Count);
}

generic<class T>
void ListEnumerator<T>::Reset()
{
	i=-1;
}


Vector3List::Vector3List(btVector3* vector3Array, int length)
{
	_vector3Array = vector3Array;
	_length = length;
	isReadOnly = false;
}

Vector3List::Vector3List(const btVector3* vector3Array, int length)
{
	_vector3Array = (btVector3*)vector3Array;
	_length = length;
	isReadOnly = true;
}

void Vector3List::Add(Vector3 item)
{
	throw gcnew System::NotSupportedException("Cannot resize list.");
}

void Vector3List::Clear()
{
	throw gcnew System::NotSupportedException("Cannot resize list.");
}

bool Vector3List::Contains(Vector3 item)
{
	btVector3* itemTemp = Math::Vector3ToBtVector3(item);

	int i;
	for (i=0; i<_length; i++)
	{
		if (itemTemp->m_floats[0] == _vector3Array[i].m_floats[0] &&
			itemTemp->m_floats[1] == _vector3Array[i].m_floats[1] &&
			itemTemp->m_floats[2] == _vector3Array[i].m_floats[2])
		{
			delete itemTemp;
			return true;
		}
	}
	delete itemTemp;
	return false;
}

void Vector3List::CopyTo(array<Vector3>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = Math::BtVector3ToVector3(&_vector3Array[i]);
	}
}

IEnumerator^ Vector3List::GetEnumerator()
{
	return gcnew ListEnumerator<Vector3>(this);
}

Generic::IEnumerator<Vector3>^ Vector3List::GetSpecializedEnumerator()
{
	return gcnew ListEnumerator<Vector3>(this);
}

int Vector3List::IndexOf(Vector3 item)
{
	btVector3* itemTemp = Math::Vector3ToBtVector3(item);

	int i;
	for (i=0; i<_length; i++)
	{
		if (itemTemp->m_floats[0] == _vector3Array[i].m_floats[0] &&
			itemTemp->m_floats[1] == _vector3Array[i].m_floats[1] &&
			itemTemp->m_floats[2] == _vector3Array[i].m_floats[2])
		{
			return i;
		}
	}
	return -1;
}

void Vector3List::Insert(int index, Vector3 item)
{
	throw gcnew System::NotSupportedException("Cannot resize collection.");
}

bool Vector3List::Remove(Vector3 item)
{
	throw gcnew System::NotSupportedException("Cannot resize list.");
}

void Vector3List::RemoveAt(int index)
{
	throw gcnew System::NotSupportedException("Cannot resize list.");
}

Vector3 Vector3List::default::get(int index)
{
	return Math::BtVector3ToVector3(&_vector3Array[index]);
}
void Vector3List::default::set(int index, Vector3 value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	Math::Vector3ToBtVector3(value, &UnmanagedPointer[index]);
}

bool Vector3List::IsReadOnly::get()
{
	return isReadOnly;
}


Vector3List::Vector3ListDebugView::Vector3ListDebugView(Vector3List^ list)
{
	_list = list;
}

array<Vector3>^ Vector3List::Vector3ListDebugView::Items::get()
{
	array<Vector3>^ arr = gcnew array<Vector3>(_list->Count);
	_list->CopyTo(arr, 0);
	return arr;
}
