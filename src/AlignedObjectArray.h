#pragma once

#include "AlignedObjectArray.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "IDisposable.h"
#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
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
			AlignedObjectArray<T>()
			{
				_alignedObjectArray = new btAlignedObjectArray<btCollisionShape*>();
			}
			
			!AlignedObjectArray()
			{
				if( this->IsDisposed == true )
					return;
	
				OnDisposing( this, nullptr );

				_alignedObjectArray = NULL;
	
				OnDisposed( this, nullptr );
			}

		protected:
			~AlignedObjectArray()
			{
				this->!AlignedObjectArray();
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

			void PushBack(CollisionShape^ collisionShape)
			{
				_alignedObjectArray->push_back(collisionShape->UnmanagedPointer);
			}

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
				CollisionShape^ get (int index)
				{
					return gcnew CollisionShape((*_alignedObjectArray)[index]);
				}
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

			void PushBack(CollisionObject^ collisionObject)
			{
				_alignedObjectArray->push_back(collisionObject->UnmanagedPointer);
			}

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
