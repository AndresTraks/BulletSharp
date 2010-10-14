#include "StdAfx.h"
#include "Collections.h"

Vector3ListDebugView::Vector3ListDebugView(Vector3List^ list)
{
	_list = list;
}

array<Vector3>^ Vector3ListDebugView::Items::get()
{
	array<Vector3>^ arr = gcnew array<Vector3>(_list->Count);
	_list->CopyTo(arr, 0);
	return arr;
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
	int i;
	for (i=0; i<_length; i++)
	{
		if (item.X == _vector3Array[i].m_floats[0] &&
			item.Y == _vector3Array[i].m_floats[1] &&
			item.Z == _vector3Array[i].m_floats[2])
		{
			return true;
		}
	}
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
	return gcnew Vector3Enumerator(this);
}

Generic::IEnumerator<Vector3>^ Vector3List::GetSpecializedEnumerator()
{
	return gcnew Vector3Enumerator(this);
}

int Vector3List::IndexOf(Vector3 item)
{
	int i;
	for (i=0; i<_length; i++)
	{
		if (item.X == _vector3Array[i].m_floats[0] &&
			item.Y == _vector3Array[i].m_floats[1] &&
			item.Z == _vector3Array[i].m_floats[2])
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


Vector3Enumerator::Vector3Enumerator(Vector3List^ vector3List)
{
	_vector3List = vector3List;
}

Vector3 Vector3Enumerator::GenericCurrent::get()
{
	return _vector3List[i];
}

Object^ Vector3Enumerator::Current::get()
{
	return GenericCurrent::get();
}

bool Vector3Enumerator::MoveNext()
{
	i++;
	return (i < _vector3List->Count);
}

void Vector3Enumerator::Reset()
{
	i=-1;
}
