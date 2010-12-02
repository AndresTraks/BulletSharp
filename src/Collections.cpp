#include "StdAfx.h"
#include "Collections.h"
#include "CompoundShape.h"

#ifndef DISABLE_DBVT
#include "Dbvt.h"
#include "DbvtBroadphase.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftBody.h"
#endif

ListDebugView::ListDebugView(IEnumerable^ list)
{
	_list = list;
}

ArrayList^ ListDebugView::Items::get()
{
	ArrayList^ list = gcnew ArrayList();
	for each(Object^ o in _list)
		list->Add(o);
	return list;
}


Vector3ListDebugView::Vector3ListDebugView(Generic::IList<Vector3>^ list)
{
	_list = list;
}

array<Vector3>^ Vector3ListDebugView::Items::get()
{
	array<Vector3>^ arr = gcnew array<Vector3>(_list->Count);
	_list->CopyTo(arr, 0);
	return arr;
}


generic<class T>
ListEnumerator<T>::ListEnumerator(Generic::IList<T>^ list)
{
	_list = list;
	i=-1;
	_count = _list->Count;
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
	return (i < _count);
}

generic<class T>
void ListEnumerator<T>::Reset()
{
	i=-1;
}


generic<class T>
GenericList<T>::GenericList(void* array, int length)
{
	_array = array;
	_length = length;
	isReadOnly = false;
}

generic<class T>
GenericList<T>::GenericList(const void* array, int length)
{
	_array = (void*)array;
	_length = length;
	isReadOnly = true;
}

generic<class T>
void GenericList<T>::Add(T item)
{
	throw gcnew System::NotSupportedException("Cannot resize array.");
}

generic<class T>
void GenericList<T>::Clear()
{
	throw gcnew System::NotSupportedException("Cannot resize array.");
}

generic<class T>
IEnumerator^ GenericList<T>::GetEnumerator()
{
	return gcnew ListEnumerator<T>(this);
}

generic<class T>
Generic::IEnumerator<T>^ GenericList<T>::GetSpecializedEnumerator()
{
	return gcnew ListEnumerator<T>(this);
}

generic<class T>
bool GenericList<T>::Contains(T item)
{
	return IndexOf(item) != -1;
}

generic<class T>
int GenericList<T>::IndexOf(T item)
{
	/*
	If we're here, it means that the underlying struct type doesn't have
	an equality operator(==). So we use its C# counterpart,
	which does a member-wise comparison.
	*/
	int i;
	for (i=0; i<Count; i++)
	{
		if (this[i]->Equals(item))
			return i;
	}
	return -1;
}

generic<class T>
void GenericList<T>::Insert(int index, T item)
{
	throw gcnew System::NotSupportedException("Cannot resize array.");
}

generic<class T>
bool GenericList<T>::Remove(T item)
{
	throw gcnew System::NotSupportedException("Cannot resize array.");
}

generic<class T>
void GenericList<T>::RemoveAt(int index)
{
	throw gcnew System::NotSupportedException("Cannot resize array.");
}

generic<class T>
int GenericList<T>::Count::get()
{
	return _length;
}

generic<class T>
bool GenericList<T>::IsReadOnly::get()
{
	return isReadOnly;
}

generic<class T>
void* GenericList<T>::UnmanagedPointer::get()
{
	return _array;
}
generic<class T>
void GenericList<T>::UnmanagedPointer::set(void* value)
{
	_array = value;
}


BoolArray::BoolArray(bool* boolArray, int length)
: GenericList<bool>(boolArray, length)
{
}

BoolArray::BoolArray(const bool* boolArray, int length)
: GenericList<bool>(boolArray, length)
{
}

bool BoolArray::Contains(bool item)
{
	int i;
	int length = Count;
	for (i=Count; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return true;
		}
	}
	return false;
}

void BoolArray::CopyTo(array<bool>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	if (arrayIndex + Count > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = UnmanagedPointer[i];
	}
}

int BoolArray::IndexOf(bool item)
{
	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return i;
		}
	}
	return -1;
}

bool BoolArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return UnmanagedPointer[index];
}
void BoolArray::default::set(int index, bool value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = value;
}

bool* BoolArray::UnmanagedPointer::get()
{
	return (bool*) GenericList::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
SoftBody::BodyArray::BodyArray(btSoftBody::Body* bodyArray, int length)
: GenericList<Body^>(bodyArray, length)
{
}

SoftBody::BodyArray::BodyArray(const btSoftBody::Body* bodyArray, int length)
: GenericList<Body^>(bodyArray, length)
{
}

void SoftBody::BodyArray::CopyTo(array<Body^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int length = Count;
	if (arrayIndex + length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = gcnew Body(&UnmanagedPointer[i]);
	}
}

SoftBody::Body^ SoftBody::BodyArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Body(&UnmanagedPointer[index]);
}

void SoftBody::BodyArray::default::set(int index, Body^ value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = *value->UnmanagedPointer;
}

btSoftBody::Body* SoftBody::BodyArray::UnmanagedPointer::get()
{
	return (btSoftBody::Body*) GenericList::UnmanagedPointer;
}
#endif


CompoundShapeChildArray::CompoundShapeChildArray(btCompoundShapeChild* shapeArray, int length)
: GenericList<CompoundShapeChild^>(shapeArray, length)
{
}

CompoundShapeChildArray::CompoundShapeChildArray(const btCompoundShapeChild* shapeArray, int length)
: GenericList<CompoundShapeChild^>(shapeArray, length)
{
}

void CompoundShapeChildArray::CopyTo(array<CompoundShapeChild^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int length = Count;
	if (arrayIndex + length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = gcnew CompoundShapeChild(&UnmanagedPointer[i]);
	}
}

CompoundShapeChild^ CompoundShapeChildArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew CompoundShapeChild(&UnmanagedPointer[index]);
}

void CompoundShapeChildArray_SetDefault(btCompoundShapeChild* shapeArray,
	int index, btCompoundShapeChild* shape)
{
	shapeArray[index] = *shape;
}
void CompoundShapeChildArray::default::set(int index, CompoundShapeChild^ value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	CompoundShapeChildArray_SetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btCompoundShapeChild* CompoundShapeChildArray::UnmanagedPointer::get()
{
	return (btCompoundShapeChild*) GenericList::UnmanagedPointer;
}


#ifndef DISABLE_DBVT
DbvtArray::DbvtArray(btDbvt* dbvtArray, int length)
: GenericList<Dbvt^>(dbvtArray, length)
{
}

DbvtArray::DbvtArray(const btDbvt* dbvtArray, int length)
: GenericList<Dbvt^>(dbvtArray, length)
{
}

void DbvtArray::CopyTo(array<Dbvt^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int length = Count;
	if (arrayIndex + length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt(&UnmanagedPointer[i]);
	}
}

Dbvt^ DbvtArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	return gcnew Dbvt(&UnmanagedPointer[index]);
}
void DbvtArray::default::set(int index, Dbvt^ value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = *value->UnmanagedPointer;

}

btDbvt* DbvtArray::UnmanagedPointer::get()
{
	return (btDbvt*) GenericList::UnmanagedPointer;
}


DbvtNodePtrArray::DbvtNodePtrArray(btDbvtNode** nodePtrArray, int length)
: GenericList<DbvtNode^>(nodePtrArray, length)
{
}

DbvtNodePtrArray::DbvtNodePtrArray(const btDbvtNode** nodePtrArray, int length)
: GenericList<DbvtNode^>(nodePtrArray, length)
{
}

void DbvtNodePtrArray::CopyTo(array<DbvtNode^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int length = Count;
	if (arrayIndex + length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = gcnew DbvtNode(UnmanagedPointer[i]);
	}
}

DbvtNode^ DbvtNodePtrArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	btDbvtNode* nodePtr = UnmanagedPointer[index];
	if (nodePtr == 0)
		return nullptr;

	return gcnew DbvtNode(nodePtr);
}
void DbvtNodePtrArray::default::set(int index, DbvtNode^ value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	UnmanagedPointer[index] = GetUnmanagedNullable(value);
}

btDbvtNode** DbvtNodePtrArray::UnmanagedPointer::get()
{
	return (btDbvtNode**) GenericList::UnmanagedPointer;
}


DbvtProxyPtrArray::DbvtProxyPtrArray(btDbvtProxy** proxyPtrArray, int length)
: GenericList<DbvtProxy^>(proxyPtrArray, length)
{
}

DbvtProxyPtrArray::DbvtProxyPtrArray(const btDbvtProxy** proxyPtrArray, int length)
: GenericList<DbvtProxy^>(proxyPtrArray, length)
{
}

void DbvtProxyPtrArray::CopyTo(array<DbvtProxy^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int length = Count;
	if (arrayIndex + length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = gcnew DbvtProxy(UnmanagedPointer[i]);
	}
}

DbvtProxy^ DbvtProxyPtrArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	btDbvtProxy* proxyPtr = UnmanagedPointer[index];
	if (proxyPtr == 0)
		return nullptr;

	return gcnew DbvtProxy(proxyPtr);
}
void DbvtProxyPtrArray::default::set(int index, DbvtProxy^ value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	UnmanagedPointer[index] = GetUnmanagedNullable(value);
}

btDbvtProxy** DbvtProxyPtrArray::UnmanagedPointer::get()
{
	return (btDbvtProxy**) GenericList::UnmanagedPointer;
}
#endif


FloatArray::FloatArray(float* floatArray, int length)
: GenericList<float>(floatArray, length)
{
}

FloatArray::FloatArray(const float* floatArray, int length)
: GenericList<float>(floatArray, length)
{
}

FloatArray::FloatArray(int length)
: GenericList<float>(new float[length], length)
{
}

bool FloatArray::Contains(float item)
{
	int i;
	int length = Count;
	for (i=Count; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return true;
		}
	}
	return false;
}

void FloatArray::CopyTo(array<float>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	if (arrayIndex + Count > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = UnmanagedPointer[i];
	}
}

int FloatArray::IndexOf(float item)
{
	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return i;
		}
	}
	return -1;
}

float FloatArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return UnmanagedPointer[index];
}
void FloatArray::default::set(int index, float value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = value;
}

float* FloatArray::UnmanagedPointer::get()
{
	return (float*) GenericList::UnmanagedPointer;
}


IntArray::IntArray(int* intArray, int length)
: GenericList<int>(intArray, length)
{
}

IntArray::IntArray(const int* intArray, int length)
: GenericList<int>(intArray, length)
{
}

IntArray::IntArray(int length)
: GenericList<int>(new int[length], length)
{
}

bool IntArray::Contains(int item)
{
	int i;
	int length = Count;
	for (i=Count; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return true;
		}
	}
	return false;
}

void IntArray::CopyTo(array<int>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	if (arrayIndex + Count > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = UnmanagedPointer[i];
	}
}

int IntArray::IndexOf(int item)
{
	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return i;
		}
	}
	return -1;
}

int IntArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return UnmanagedPointer[index];
}
void IntArray::default::set(int index, int value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = value;
}

int* IntArray::UnmanagedPointer::get()
{
	return (int*) GenericList::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
SoftBody::NodePtrArray::NodePtrArray(btSoftBody::Node** nodePtrArray, int length)
: GenericList<Node^>(nodePtrArray, length)
{
}

SoftBody::NodePtrArray::NodePtrArray(const btSoftBody::Node** nodePtrArray, int length)
: GenericList<Node^>(nodePtrArray, length)
{
}

void SoftBody::NodePtrArray::CopyTo(array<Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int length = Count;
	if (arrayIndex + length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = gcnew Node(UnmanagedPointer[i]);
	}
}

SoftBody::Node^ SoftBody::NodePtrArray::default::get(int index)
{
	btSoftBody::Node* nodePtr = UnmanagedPointer[index];
	if (nodePtr == 0)
		return nullptr;
	return gcnew Node(nodePtr);
}
void SoftBody::NodePtrArray::default::set(int index, Node^ value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = GetUnmanagedNullable(value);
}

btSoftBody::Node** SoftBody::NodePtrArray::UnmanagedPointer::get()
{
	return (btSoftBody::Node**) GenericList::UnmanagedPointer;
}
#endif


ScalarArray::ScalarArray(btScalar* scalarArray, int length)
: GenericList<btScalar>(scalarArray, length)
{
}

ScalarArray::ScalarArray(const btScalar* scalarArray, int length)
: GenericList<btScalar>(scalarArray, length)
{
}

ScalarArray::ScalarArray(int length)
: GenericList<btScalar>(new btScalar[length], length)
{
}

bool ScalarArray::Contains(btScalar item)
{
	int i;
	int length = Count;
	for (i=Count; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return true;
		}
	}
	return false;
}

void ScalarArray::CopyTo(array<btScalar>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	if (arrayIndex + Count > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = UnmanagedPointer[i];
	}
}

int ScalarArray::IndexOf(btScalar item)
{
	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return i;
		}
	}
	return -1;
}

btScalar ScalarArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return UnmanagedPointer[index];
}
void ScalarArray::default::set(int index, btScalar value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = value;
}

btScalar* ScalarArray::UnmanagedPointer::get()
{
	return (btScalar*) GenericList::UnmanagedPointer;
}


UIntArray::UIntArray(unsigned int* uintArray, int length)
: GenericList<unsigned int>(uintArray, length)
{
}

UIntArray::UIntArray(const unsigned int* uintArray, int length)
: GenericList<unsigned int>(uintArray, length)
{
}

bool UIntArray::Contains(unsigned int item)
{
	int i;
	int length = Count;
	for (i=Count; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return true;
		}
	}
	return false;
}

void UIntArray::CopyTo(array<unsigned int>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	if (arrayIndex + Count > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = UnmanagedPointer[i];
	}
}

int UIntArray::IndexOf(unsigned int item)
{
	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return i;
		}
	}
	return -1;
}

unsigned int UIntArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return UnmanagedPointer[index];
}
void UIntArray::default::set(int index, unsigned int value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = value;
}

unsigned int* UIntArray::UnmanagedPointer::get()
{
	return (unsigned int*) GenericList::UnmanagedPointer;
}


UShortArray::UShortArray(unsigned short* uShortArray, int length)
: GenericList<unsigned short>(uShortArray, length)
{
}

UShortArray::UShortArray(const unsigned short* uShortArray, int length)
: GenericList<unsigned short>(uShortArray, length)
{
}

bool UShortArray::Contains(unsigned short item)
{
	int i;
	int length = Count;
	for (i=Count; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return true;
		}
	}
	return false;
}

void UShortArray::CopyTo(array<unsigned short>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	if (arrayIndex + Count > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = UnmanagedPointer[i];
	}
}

int UShortArray::IndexOf(unsigned short item)
{
	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (item == UnmanagedPointer[i])
		{
			return i;
		}
	}
	return -1;
}

unsigned short UShortArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return UnmanagedPointer[index];
}
void UShortArray::default::set(int index, unsigned short value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	UnmanagedPointer[index] = value;
}

unsigned short* UShortArray::UnmanagedPointer::get()
{
	return (unsigned short*) GenericList::UnmanagedPointer;
}


Vector3Array::Vector3Array(btVector3* vector3Array, int length)
: GenericList<Vector3>(vector3Array, length)
{
}

Vector3Array::Vector3Array(const btVector3* vector3Array, int length)
: GenericList<Vector3>(vector3Array, length)
{
}

Vector3Array::Vector3Array(int length)
: GenericList<Vector3>(new btVector3[length], length)
{
}

bool Vector3Array::Contains(Vector3 item)
{
	btVector3* itemTemp = Math::Vector3ToBtVector3(item);

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (itemTemp->m_floats[0] == UnmanagedPointer[i].m_floats[0] &&
			itemTemp->m_floats[1] == UnmanagedPointer[i].m_floats[1] &&
			itemTemp->m_floats[2] == UnmanagedPointer[i].m_floats[2])
		{
			delete itemTemp;
			return true;
		}
	}
	delete itemTemp;
	return false;
}

void Vector3Array::CopyTo(array<Vector3>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int length = Count;
	if (arrayIndex + length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<length; i++)
	{
		array[arrayIndex+i] = Math::BtVector3ToVector3(&UnmanagedPointer[i]);
	}
}

int Vector3Array::IndexOf(Vector3 item)
{
	btVector3* itemTemp = Math::Vector3ToBtVector3(item);

	int i;
	int length = Count;
	for (i=0; i<length; i++)
	{
		if (itemTemp->m_floats[0] == UnmanagedPointer[i].m_floats[0] &&
			itemTemp->m_floats[1] == UnmanagedPointer[i].m_floats[1] &&
			itemTemp->m_floats[2] == UnmanagedPointer[i].m_floats[2])
		{
			delete itemTemp;
			return i;
		}
	}
	delete itemTemp;
	return -1;
}

Vector3 Vector3Array::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return Math::BtVector3ToVector3(&UnmanagedPointer[index]);
}
void Vector3Array::default::set(int index, Vector3 value)
{
	if (IsReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	Math::Vector3ToBtVector3(value, &UnmanagedPointer[index]);
}

btVector3* Vector3Array::UnmanagedPointer::get()
{
	return (btVector3*) GenericList::UnmanagedPointer;
}
