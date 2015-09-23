#include "StdAfx.h"
#include "Collections.h"
#include "CollisionShape.h"
#include "CompoundShape.h"

#ifndef DISABLE_DBVT
#include "Dbvt.h"
#include "DbvtBroadphase.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftBody.h"
#endif

ListDebugView::ListDebugView(System::Collections::IEnumerable^ list)
{
	_list = list;
}

System::Collections::ArrayList^ ListDebugView::Items::get()
{
	System::Collections::ArrayList^ list = gcnew System::Collections::ArrayList();
	for each(Object^ o in _list)
		list->Add(o);
	return list;
}


Vector3ListDebugView::Vector3ListDebugView(IList<Vector3>^ list)
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
ListEnumerator<T>::ListEnumerator(IList<T>^ list)
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
	_native = array;
	_length = length;
	_isReadOnly = false;
}

generic<class T>
GenericList<T>::GenericList(const void* array, int length)
{
	_native = (void*)array;
	_length = length;
	_isReadOnly = true;
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
System::Collections::IEnumerator^ GenericList<T>::GetObjectEnumerator()
{
	return gcnew ListEnumerator<T>(this);
}

generic<class T>
IEnumerator<T>^ GenericList<T>::GetEnumerator()
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
	for (i=0; i<_length; i++)
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
	return _isReadOnly;
}


#define Native static_cast<bool*>(_native)

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
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = Native[i];
	}
}

int BoolArray::IndexOf(bool item)
{
	int i;
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
		{
			return i;
		}
	}
	return -1;
}

bool BoolArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	return Native[index];
}
void BoolArray::default::set(int index, bool value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = value;
}


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native static_cast<btSoftBody::Body*>(_native)

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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = gcnew Body(&Native[i]);
	}
}

SoftBody::Body^ SoftBody::BodyArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Body(&Native[index]);
}

void SoftBody::BodyArray::default::set(int index, Body^ value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = *value->_native;
}
#endif


#undef Native
#define Native static_cast<btCompoundShape*>(_native)

CompoundShapeChildArray::CompoundShapeChildArray(btCompoundShape* compoundShape)
	: GenericList<CompoundShapeChild^>(compoundShape, compoundShape->getNumChildShapes())
{
	_backingList = gcnew List<CompoundShapeChild^>();
	BuildBackingList();
}

void CompoundShapeChildArray::BuildBackingList()
{
	// Assume that children have not been removed by Bullet internally (e.g. by the world importer).
	int count = Native->getNumChildShapes();
	if (count != 0)
	{
		btCompoundShapeChild* childList = Native->getChildList();
		for (int i = 0; i < count; i++)
		{
			if (i >= _backingList->Count)
			{
				CollisionShape^ shape = CollisionShape::GetManaged(childList[i].m_childShape);
				_backingList->Add(gcnew CompoundShapeChild(&childList[i], shape));
			}
		}
	}
	_updateRevision = Native->getUpdateRevision();
}

void CompoundShapeChildArray::AddChildShape(Matrix% localTransform, CollisionShape^ shape)
{
	if (Native->getUpdateRevision() != _updateRevision)
	{
		BuildBackingList();
	}

	// getChildList asserts and crashes if count = 0
	btCompoundShapeChild* childListOld = Native->getNumChildShapes() ? Native->getChildList() : 0;
	TRANSFORM_CONV(localTransform);
	Native->addChildShape(TRANSFORM_USE(localTransform), shape->_native);
	TRANSFORM_DEL(localTransform);
	btCompoundShapeChild* childList = Native->getChildList();
	
    // Adjust the native pointer of existing children if the array was reallocated.
	int count = _backingList->Count;
    if (childListOld != childList)
    {
        for (int i = 0; i < count; i++)
        {
            _backingList[i]->_native = &childList[i];
        }
    }

	_backingList->Add(gcnew CompoundShapeChild(&childList[count], shape));
	_updateRevision = Native->getUpdateRevision();
}

void CompoundShapeChildArray::CopyTo(array<CompoundShapeChild^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = this[i];
	}
}

void CompoundShapeChildArray::RemoveChildShape(CollisionShape^ shape)
{
	if (Native->getUpdateRevision() != _updateRevision)
	{
		BuildBackingList();
	}
	
    btCollisionShape* shapePtr = shape->_native;
	int count = Native->getNumChildShapes();
    for (int i = 0; i < count; i++)
    {
        if (_backingList[i]->ChildShape->_native == shapePtr)
        {
            RemoveChildShapeByIndex(i);
            break;
        }
    }
}

void CompoundShapeChildArray::RemoveChildShapeByIndex(int childShapeIndex)
{
	if (Native->getUpdateRevision() != _updateRevision)
	{
		BuildBackingList();
	}
	Native->removeChildShapeByIndex(childShapeIndex);

	// Swap the last item with the item to be removed like Bullet does.
	int count = Native->getNumChildShapes();
    if (childShapeIndex != count)
    {
        CompoundShapeChild^ lastItem = _backingList[count];
        lastItem->_native = _backingList[childShapeIndex]->_native;
        _backingList[childShapeIndex] = lastItem;
    }
	_backingList->RemoveAt(count);

	_updateRevision = Native->getUpdateRevision();
}

CompoundShapeChild^ CompoundShapeChildArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Count)
		throw gcnew ArgumentOutOfRangeException("index");
	if (Native->getUpdateRevision() != _updateRevision)
	{
		BuildBackingList();
	}
	return _backingList[index];
}

#pragma managed(push, off)
void CompoundShapeChildArray_SetDefault(btCompoundShapeChild* shapeArray,
	int index, btCompoundShapeChild* shape)
{
	shapeArray[index] = *shape;
}
#pragma managed(pop)
void CompoundShapeChildArray::default::set(int index, CompoundShapeChild^ value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btCompoundShapeChild* childList = Native->getChildList();
	CompoundShapeChildArray_SetDefault(childList, index, value->_native);
}

int CompoundShapeChildArray::Count::get()
{
	return Native->getNumChildShapes();
}


#ifndef DISABLE_DBVT

#undef Native
#define Native static_cast<btDbvt*>(_native)

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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt(&Native[i], true);
	}
}

Dbvt^ DbvtArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");

	return gcnew Dbvt(&Native[index], true);
}
void DbvtArray::default::set(int index, Dbvt^ value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = *value->_native;
}


#undef Native
#define Native static_cast<btDbvtNode**>(_native)

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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = gcnew DbvtNode(Native[i]);
	}
}

DbvtNode^ DbvtNodePtrArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");

	btDbvtNode* nodePtr = Native[index];
	if (nodePtr == 0)
		return nullptr;

	return gcnew DbvtNode(nodePtr);
}
void DbvtNodePtrArray::default::set(int index, DbvtNode^ value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");

	Native[index] = GetUnmanagedNullable(value);
}


#undef Native
#define Native static_cast<btDbvtProxy**>(_native)

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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = dynamic_cast<DbvtProxy^>(DbvtProxy::GetManaged(Native[i]));
	}
}

DbvtProxy^ DbvtProxyPtrArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");

	btDbvtProxy* proxyPtr = Native[index];
	if (proxyPtr == 0)
		return nullptr;

	return dynamic_cast<DbvtProxy^>(DbvtProxy::GetManaged(proxyPtr));
}
void DbvtProxyPtrArray::default::set(int index, DbvtProxy^ value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");

	Native[index] = (btDbvtProxy*)GetUnmanagedNullable(value);
}
#endif


#undef Native
#define Native static_cast<float*>(_native)

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
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = Native[i];
	}
}

int FloatArray::IndexOf(float item)
{
	int i;
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
		{
			return i;
		}
	}
	return -1;
}

float FloatArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	return Native[index];
}
void FloatArray::default::set(int index, float value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = value;
}


#undef Native
#define Native static_cast<int*>(_native)

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
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = Native[i];
	}
}

int IntArray::IndexOf(int item)
{
	int i;
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
		{
			return i;
		}
	}
	return -1;
}

int IntArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	return Native[index];
}
void IntArray::default::set(int index, int value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = value;
}


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native static_cast<btSoftBody::Node**>(_native)

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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = gcnew Node(Native[i]);
	}
}

SoftBody::Node^ SoftBody::NodePtrArray::default::get(int index)
{
	btSoftBody::Node* nodePtr = Native[index];
	if (nodePtr == 0)
		return nullptr;
	return gcnew Node(nodePtr);
}
void SoftBody::NodePtrArray::default::set(int index, Node^ value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = (btSoftBody::Node*)GetUnmanagedNullable(value);
}
#endif


#undef Native
#define Native static_cast<btScalar*>(_native)

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
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = Native[i];
	}
}

int ScalarArray::IndexOf(btScalar item)
{
	int i;
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
		{
			return i;
		}
	}
	return -1;
}

btScalar ScalarArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	return Native[index];
}
void ScalarArray::default::set(int index, btScalar value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = value;
}


#undef Native
#define Native static_cast<unsigned int*>(_native)

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
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = Native[i];
	}
}

int UIntArray::IndexOf(unsigned int item)
{
	int i;
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
		{
			return i;
		}
	}
	return -1;
}

unsigned int UIntArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	return Native[index];
}
void UIntArray::default::set(int index, unsigned int value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = value;
}


#undef Native
#define Native static_cast<unsigned short*>(_native)

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
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
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
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	for (i=0; i<_length; i++)
	{
		array[arrayIndex+i] = Native[i];
	}
}

int UShortArray::IndexOf(unsigned short item)
{
	int i;
	for (i=0; i<_length; i++)
	{
		if (item == Native[i])
		{
			return i;
		}
	}
	return -1;
}

unsigned short UShortArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	return Native[index];
}
void UShortArray::default::set(int index, unsigned short value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	Native[index] = value;
}


#undef Native
#define Native static_cast<btVector3*>(_native)

Vector3Array::Vector3Array(btVector3* vector3Array, int length)
: GenericList<Vector3>(vector3Array, length)
{
	_vectorStride = sizeof(btVector3);
}

Vector3Array::Vector3Array(const btVector3* vector3Array, int length)
: GenericList<Vector3>(vector3Array, length)
{
	_vectorStride = sizeof(btVector3);
}

Vector3Array::Vector3Array(int length)
: GenericList<Vector3>(new btVector3[length], length)
{
	_vectorStride = sizeof(btVector3);
}

void Vector3Array::CopyTo(array<Vector3>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	if (arrayIndex + _length > array->Length)
		throw gcnew ArgumentException("Array too small.");

	int i;
	char* p = (char*)&Native[0];
	for (i=0; i<_length; i++)
	{
		Math::BtVector3ToVector3((btVector3*)p, array[arrayIndex+i]);
		p += _vectorStride;
	}
}

int Vector3Array::IndexOf(Vector3 item)
{
	VECTOR3_CONV(item);

	int i;
	char* vector = (char*)&Native[0];
	for (i=0; i<_length; i++)
	{
		if (VECTOR3_PTR(item)->m_floats[0] == ((btVector3*)vector)->m_floats[0] &&
			VECTOR3_PTR(item)->m_floats[1] == ((btVector3*)vector)->m_floats[1] &&
			VECTOR3_PTR(item)->m_floats[2] == ((btVector3*)vector)->m_floats[2])
		{
			VECTOR3_DEL(item);
			return i;
		}
		vector += _vectorStride;
	}
	VECTOR3_DEL(item);
	return -1;
}

Vector3 Vector3Array::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	btVector3* p = (btVector3*)(((char*)&Native[0]) + index * _vectorStride);
	return Math::BtVector3ToVector3(p);
}
void Vector3Array::default::set(int index, Vector3 value)
{
	if (_isReadOnly)
		throw gcnew InvalidOperationException("List is read-only.");
	if ((unsigned int)index >= (unsigned int)_length)
		throw gcnew ArgumentOutOfRangeException("index");
	btVector3* p = (btVector3*)(((char*)&Native[0]) + index * _vectorStride);
	Math::Vector3ToBtVector3(value, p);
}

int Vector3Array::Stride::get()
{
	return _vectorStride;
}
void Vector3Array::Stride::set(int value)
{
	_vectorStride = value;
}
