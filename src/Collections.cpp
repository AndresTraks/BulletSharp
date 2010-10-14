#include "StdAfx.h"
#include "Collections.h"

Vector3Collection::Vector3Collection(btVector3* vector3Array, int length)
{
	_vector3Array = vector3Array;
	_length = length;
}

void Vector3Collection::Add(Vector3 item)
{
	throw gcnew System::NotSupportedException("Cannot resize collection.");
}

void Vector3Collection::Clear()
{
	throw gcnew System::NotSupportedException("Cannot resize collection.");
}

bool Vector3Collection::Contains(Vector3 item)
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

void Vector3Collection::CopyTo(array<Vector3>^ array, int arrayIndex)
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

IEnumerator^ Vector3Collection::GetEnumerator()
{
	return gcnew Vector3Enumerator(this);
}

Generic::IEnumerator<Vector3>^ Vector3Collection::GetSpecializedEnumerator()
{
	return gcnew Vector3Enumerator(this);
}

bool Vector3Collection::Remove(Vector3 item)
{
	throw gcnew System::NotSupportedException("Cannot resize collection.");
}

Vector3 Vector3Collection::default::get(int index)
{
	return Math::BtVector3ToVector3(&_vector3Array[index]);
}
void Vector3Collection::default::set(int index, Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer[index]);
}

bool Vector3Collection::IsReadOnly::get()
{
	return false;
}


Vector3Enumerator::Vector3Enumerator(Vector3Collection^ vector3Collection)
{
	_vector3Collection = vector3Collection;
}

Vector3 Vector3Enumerator::GenericCurrent::get()
{
	return _vector3Collection[i];
}

Object^ Vector3Enumerator::Current::get()
{
	return GenericCurrent::get();
}

bool Vector3Enumerator::MoveNext()
{
	i++;
	return (i < _vector3Collection->Count);
}

void Vector3Enumerator::Reset()
{
	i=-1;
}
