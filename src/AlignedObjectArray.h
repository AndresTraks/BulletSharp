#pragma once

#include "CollisionObject.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionShape;
	ref class TriangleIndexVertexArray;

	generic <class T>
	where T: CollisionShape
	public ref class AlignedObjectArray : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btAlignedObjectArray<btCollisionShape*>* _alignedObjectArray;

	public:
		AlignedObjectArray<T>();
		!AlignedObjectArray();
	protected:
		~AlignedObjectArray();

	public:
		property bool IsDisposed
		{
			virtual bool get()
			{
				return (_alignedObjectArray == NULL);
			}
		}

		void Clear()
		{
			_alignedObjectArray->clear();
		}

		void PopBack()
		{
			_alignedObjectArray->pop_back();
		}

		void PushBack(CollisionShape^ collisionShape);

		property int Size
		{
			int get()
			{
				return _alignedObjectArray->size();
			}
		}

		property int Capacity
		{
			int get()
			{
				return _alignedObjectArray->capacity();
			}
		}

		property CollisionShape^ default [int]
		{
			CollisionShape^ get (int index);
			void set(int index, CollisionShape^);
		}

	internal:
		property btAlignedObjectArray<btCollisionShape*>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btCollisionShape*>* get()
			{
				return _alignedObjectArray;
			}
			void set( btAlignedObjectArray<btCollisionShape*>* value )
			{
				_alignedObjectArray = value;
			}
		}
	};


	public ref class CollisionObjectArray : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btAlignedObjectArray<btCollisionObject*>* _alignedObjectArray;

	internal:
		CollisionObjectArray(btCollisionObjectArray* collisionObjectArray)
		{
			_alignedObjectArray = collisionObjectArray;
		}


	public:
		CollisionObjectArray()
		{
			_alignedObjectArray = new btAlignedObjectArray<btCollisionObject*>();
		}
		
		!CollisionObjectArray()
		{
			if( this->IsDisposed == true )
				return;

			OnDisposing( this, nullptr );

			_alignedObjectArray = NULL;

			OnDisposed( this, nullptr );
		}

	protected:
		~CollisionObjectArray()
		{
			this->!CollisionObjectArray();
		}

	public:
		property bool IsDisposed
		{
			virtual bool get()
			{
				return (_alignedObjectArray == NULL);
			}
		}

		void Clear()
		{
			_alignedObjectArray->clear();
		}

		void PopBack()
		{
			_alignedObjectArray->pop_back();
		}

		void PushBack(CollisionObject^ collisionObject);

		property int Size
		{
			int get()
			{
				return _alignedObjectArray->size();
			}
		}

		property int Capacity
		{
			int get()
			{
				return _alignedObjectArray->capacity();
			}
		}

		property CollisionObject^ default [int]
		{
			CollisionObject^ get (int index)
			{
				btCollisionObject* obj = (*_alignedObjectArray)[index];
				if (obj != nullptr)
					return gcnew CollisionObject(obj);
				else
					return nullptr;
			}
		}

	internal:
		property btAlignedObjectArray<btCollisionObject*>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btCollisionObject*>* get()
			{
				return _alignedObjectArray;
			}
			void set( btAlignedObjectArray<btCollisionObject*>* value )
			{
				_alignedObjectArray = value;
			}
		}
	};
};
