#include "StdAfx.h"

#include "ObjectTable.h"

using namespace System::Collections::Generic;

static BulletSharp::ObjectTable::ObjectTable()
{
	objectTable = gcnew Dictionary<intptr_t, Object^>();
}

void BulletSharp::ObjectTable::Add(Object^ obj, void* unmanagedPointer)
{
	objectTable->Add((intptr_t)unmanagedPointer, obj);
}

bool BulletSharp::ObjectTable::Contains(intptr_t unmanagedPointer)
{
	return objectTable->ContainsKey(unmanagedPointer);
}

generic<class T>
T BulletSharp::ObjectTable::GetObject(intptr_t unmanagedPointer)
{
	return (T)objectTable[unmanagedPointer];
}
