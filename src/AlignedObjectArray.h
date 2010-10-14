#pragma once

#include "IDisposable.h"

#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftBody.h"
#endif
#ifndef DISABLE_VEHICLE
#include "WheelInfo.h"
#endif

using namespace System::Collections;
using namespace System::Diagnostics;

namespace BulletSharp
{
	ref class BroadphasePair;
	ref class CollisionObject;
	ref class CollisionShape;
	ref class CompoundShapeChild;
	ref class PersistentManifold;

	public ref class AlignedObjectArray : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		void* _alignedObjectArray;

	internal:
		AlignedObjectArray(void* alignedObjectArray);

	public:
		!AlignedObjectArray();
	protected:
		~AlignedObjectArray();

	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property void* UnmanagedPointer
		{
			virtual void* get();
			void set(void* value);
		}
	};

	[DebuggerDisplay("Size = {Size}")]
	public ref class BroadphasePairArray : AlignedObjectArray
	{
	internal:
		BroadphasePairArray(btBroadphasePairArray* stkNnArray);

	public:
		BroadphasePairArray();

		void Clear();
		void PopBack();
		void PushBack(BroadphasePair^ pair);
		void Remove(BroadphasePair^ pair);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property BroadphasePair^ default [int]
		{
			BroadphasePair^ get (int index);
			void set(int index, BroadphasePair^ value);
		}

	internal:
		property btBroadphasePairArray* UnmanagedPointer
		{
			virtual btBroadphasePairArray* get() new;
		}
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Size = {Size}")]
		public ref class ClusterArray : AlignedObjectArray, IEnumerable
		{
		internal:
			ClusterArray(btSoftBody::tClusterArray* clusterArray);

		public:
			ClusterArray();

			virtual IEnumerator^ GetEnumerator();

			void Clear();
			void PopBack();
			void PushBack(Cluster^ cluster);
			void Remove(Cluster^ cluster);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property Cluster^ default [int]
			{
				Cluster^ get (int index);
				void set(int index, Cluster^ value);
			}

		internal:
			property btSoftBody::tClusterArray* UnmanagedPointer
			{
				virtual btSoftBody::tClusterArray* get() new;
			}
		};
	};

	public ref class ClusterEnumerator : IEnumerator
	{
	private:
		BulletSharp::SoftBody::ClusterArray^ _clusterArray;
		int i;

	public:
		ClusterEnumerator(BulletSharp::SoftBody::ClusterArray^ clusterArray);

		property Object^ Current
		{
			virtual Object^ get();
		}

		virtual bool MoveNext();
		virtual void Reset();
	};
#endif

	[DebuggerDisplay("Size = {Size}")]
	public ref class CollisionShapeArray : AlignedObjectArray
	{
	public:
		CollisionShapeArray();

		void Clear();
		void PopBack();
		void PushBack(CollisionShape^ collisionShape);
		void Remove(CollisionShape^ collisionShape);
		void Swap(int index0, int index1);

		property int Capacity
		{
			int get();
		}

		property int Size
		{
			int get();
		}

		property CollisionShape^ default [int]
		{
			CollisionShape^ get (int index);
			void set(int index, CollisionShape^ value);
		}

	internal:
		property btAlignedObjectArray<btCollisionShape*>* UnmanagedPointer
		{
			btAlignedObjectArray<btCollisionShape*>* get() new;
		}
	};

	[DebuggerDisplay("Size = {Size}")]
	public ref class CollisionObjectArray : AlignedObjectArray, IEnumerable
	{
	internal:
		CollisionObjectArray(btCollisionObjectArray* collisionObjectArray);

	public:
		CollisionObjectArray();

		virtual IEnumerator^ GetEnumerator();

		void Clear();
		void PopBack();
		void PushBack(CollisionObject^ collisionObject);
		void Remove(CollisionObject^ collisionObject);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property CollisionObject^ default [int]
		{
			CollisionObject^ get (int index);
			void set(int index, CollisionObject^ value);
		}

	internal:
		property btCollisionObjectArray* UnmanagedPointer
		{
			virtual btCollisionObjectArray* get() new;
		}
	};

	public ref class CollisionObjectEnumerator : IEnumerator
	{
	private:
		CollisionObjectArray^ _objArray;
		int i;

	public:
		CollisionObjectEnumerator(CollisionObjectArray^ objArray);

		property CollisionObject^ Current
		{
			virtual CollisionObject^ get();
		}

		property Object^ CurrentBase { 
			virtual Object^ get() sealed = IEnumerator::Current::get;
		};

		virtual bool MoveNext();
		virtual void Reset();
	};

	[DebuggerDisplay("Size = {Size}")]
	public ref class CompoundShapeChildArray : AlignedObjectArray
	{
	internal:
		CompoundShapeChildArray(btAlignedObjectArray<btCompoundShapeChild>* compundShapeChildArray);

	public:
		CompoundShapeChildArray();

		virtual IEnumerator^ GetEnumerator();

		void Clear();
		void PopBack();
		void PushBack(CompoundShapeChild^ compundShapeChild);
		void Remove(CompoundShapeChild^ compundShapeChild);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property CompoundShapeChild^ default [int]
		{
			CompoundShapeChild^ get (int index);
			void set(int index, CompoundShapeChild^ value);
		}

	internal:
		property btAlignedObjectArray<btCompoundShapeChild>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btCompoundShapeChild>* get() new;
		}
	};

	[DebuggerDisplay("Size = {Size}")]
	public ref class CompoundShapeChildEnumerator : IEnumerator
	{
	private:
		CompoundShapeChildArray^ _shapeArray;
		int i;

	public:
		CompoundShapeChildEnumerator(CompoundShapeChildArray^ shapeArray);

		property Object^ Current
		{
			virtual Object^ get();
		}

		virtual bool MoveNext();
		virtual void Reset();
	};

#ifndef DISABLE_DBVT
	[DebuggerDisplay("Size = {Size}")]
	public ref class DbvtNodeArray : AlignedObjectArray
	{
	internal:
		DbvtNodeArray(btAlignedObjectArray<const btDbvtNode*>* nodeArray);

	public:
		DbvtNodeArray();

		void Clear();
		void PopBack();
		void PushBack(DbvtNode^ stkNps);
		void Remove(DbvtNode^ stkNps);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property DbvtNode^ default [int]
		{
			DbvtNode^ get (int index);
			void set(int index, DbvtNode^ value);
		}

	internal:
		property btAlignedObjectArray<const btDbvtNode*>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<const btDbvtNode*>* get() new;
		}
	};

	[DebuggerDisplay("Size = {Size}")]
	public ref class StkNnArray : AlignedObjectArray
	{
	internal:
		StkNnArray(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray);

	public:
		StkNnArray();

		void Clear();
		void PopBack();
		void PushBack(Dbvt::StkNn^ stkNps);
		void Remove(Dbvt::StkNn^ stkNps);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property Dbvt::StkNn^ default [int]
		{
			Dbvt::StkNn^ get (int index);
			void set(int index, Dbvt::StkNn^ value);
		}

	internal:
		property btAlignedObjectArray<btDbvt::sStkNN>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btDbvt::sStkNN>* get() new;
		}
	};

	[DebuggerDisplay("Size = {Size}")]
	public ref class StkNpsArray : AlignedObjectArray
	{
	internal:
		StkNpsArray(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray);

	public:
		StkNpsArray();

		void Clear();
		void PopBack();
		void PushBack(Dbvt::StkNps^ stkNps);
		void Remove(Dbvt::StkNps^ stkNps);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property Dbvt::StkNps^ default [int]
		{
			Dbvt::StkNps^ get (int index);
			void set(int index, Dbvt::StkNps^ value);
		}

	internal:
		property btAlignedObjectArray<btDbvt::sStkNPS>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btDbvt::sStkNPS>* get() new;
		}
	};
#endif

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Size = {Size}")]
		public ref class FaceArray : AlignedObjectArray
		{
		internal:
			FaceArray(btAlignedObjectArray<btSoftBody::Face>* faceArray);

		public:
			FaceArray();

			void Clear();
			void PopBack();
			void PushBack(Face^ face);
			void Remove(Face^ face);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property Face^ default [int]
			{
				Face^ get (int index);
				void set(int index, Face^ value);
			}

		internal:
			property btAlignedObjectArray<btSoftBody::Face>* UnmanagedPointer
			{
				virtual btAlignedObjectArray<btSoftBody::Face>* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Size = {Size}")]
	public ref class IntArray : AlignedObjectArray
	{
	internal:
		IntArray(btAlignedObjectArray<int>* intArray);

	public:
		IntArray();

		void Clear();
		void PopBack();
		void PushBack(int intValue);
		void Remove(int intValue);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property int default [int]
		{
			int get (int index);
			void set(int index, int value);
		}

	internal:
		property btAlignedObjectArray<int>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<int>* get() new;
		}
	};

	[DebuggerDisplay("Size = {Size}")]
	public ref class ManifoldArray : AlignedObjectArray
	{
	internal:
		ManifoldArray(btManifoldArray* manifoldArray);

	public:
		ManifoldArray();

		void Clear();
		void PopBack();
		void PushBack(PersistentManifold^ manifold);
		void Remove(PersistentManifold^ manifold);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property PersistentManifold^ default [int]
		{
			PersistentManifold^ get (int index);
			void set(int index, PersistentManifold^ value);
		}

	internal:
		property btManifoldArray* UnmanagedPointer
		{
			virtual btManifoldArray* get() new;
		}
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Size = {Size}")]
		public ref class LinkArray : AlignedObjectArray, IEnumerable
		{
		internal:
			LinkArray(btSoftBody::tLinkArray* linkArray);

		public:
			LinkArray();

			virtual IEnumerator^ GetEnumerator();

			void Clear();
			void PopBack();
			void PushBack(Link^ link);
			void Remove(Link^ link);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property Link^ default [int]
			{
				Link^ get (int index);
				void set(int index, Link^ value);
			}

		internal:
			property btSoftBody::tLinkArray* UnmanagedPointer
			{
				virtual btSoftBody::tLinkArray* get() new;
			}
		};

		public ref class LinkEnumerator : IEnumerator
		{
		private:
			LinkArray^ _linkArray;
			int i;

		public:
			LinkEnumerator(LinkArray^ linkArray);

			property Object^ Current
			{
				virtual Object^ get();
			}

			virtual bool MoveNext();
			virtual void Reset();
		};

		[DebuggerDisplay("Size = {Size}")]
		public ref class MaterialArray : AlignedObjectArray
		{
		internal:
			MaterialArray(btSoftBody::tMaterialArray* materialArray);

		public:
			MaterialArray();

			void Clear();
			void PopBack();
			void PushBack(Material^ material);
			void Remove(Material^ material);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property Material^ default [int]
			{
				Material^ get (int index);
				void set(int index, Material^ value);
			}

		internal:
			property btSoftBody::tMaterialArray* UnmanagedPointer
			{
				virtual btSoftBody::tMaterialArray* get() new;
			}
		};

		[DebuggerDisplay("Size = {Size}")]
		public ref class NodeArray : AlignedObjectArray
		{
		internal:
			NodeArray(btSoftBody::tNodeArray* nodeArray);

		public:
			NodeArray();

			void Clear();
			void PopBack();
			void PushBack(Node^ node);
			void Remove(Node^ node);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property Node^ default [int]
			{
				Node^ get (int index);
				void set(int index, Node^ value);
			}

		internal:
			property btSoftBody::tNodeArray* UnmanagedPointer
			{
				virtual btSoftBody::tNodeArray* get() new;
			}
		};

		[DebuggerDisplay("Size = {Size}")]
		public ref class NodePtrArray : AlignedObjectArray
		{
		internal:
			NodePtrArray(btAlignedObjectArray<btSoftBody::Node*>* nodeArray);

		public:
			NodePtrArray();

			void Clear();
			void PopBack();
			void PushBack(Node^ node);
			void Remove(Node^ node);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property Node^ default [int]
			{
				Node^ get (int index);
				void set(int index, Node^ value);
			}

		internal:
			property btAlignedObjectArray<btSoftBody::Node*>* UnmanagedPointer
			{
				virtual btAlignedObjectArray<btSoftBody::Node*>* get() new;
			}
		};

		[DebuggerDisplay("Size = {Size}")]
		public ref class NoteArray : AlignedObjectArray
		{
		internal:
			NoteArray(btSoftBody::tNoteArray* noteArray);

		public:
			NoteArray();

			void Clear();
			void PopBack();
			void PushBack(Note^ note);
			void Remove(Note^ note);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property Note^ default [int]
			{
				Note^ get (int index);
				void set(int index, Note^ value);
			}

		internal:
			property btSoftBody::tNoteArray* UnmanagedPointer
			{
				virtual btSoftBody::tNoteArray* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Size = {Size}")]
	public ref class ScalarArray : AlignedObjectArray
	{
	internal:
		ScalarArray(btAlignedObjectArray<btScalar>* btScalarArray);

	public:
		ScalarArray();

		void Clear();
		void PopBack();
		void PushBack(btScalar intValue);
		void Remove(btScalar intValue);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property btScalar default [int]
		{
			btScalar get (int index);
			void set(int index, btScalar value);
		}

	internal:
		property btAlignedObjectArray<btScalar>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btScalar>* get() new;
		}
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Size = {Size}")]
		public ref class SoftBodyArray : AlignedObjectArray
		{
		internal:
			SoftBodyArray(btSoftBody::tSoftBodyArray* softBodyArray);

		public:
			SoftBodyArray();

			void Clear();
			void PopBack();
			void PushBack(SoftBody^ node);
			void Remove(SoftBody^ node);
			void Swap(int index0, int index1);

			property int Size
			{
				int get();
			}

			property int Capacity
			{
				int get();
			}

			property SoftBody^ default [int]
			{
				SoftBody^ get (int index);
				void set(int index, SoftBody^ value);
			}

		internal:
			property btSoftBody::tSoftBodyArray* UnmanagedPointer
			{
				virtual btSoftBody::tSoftBodyArray* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Size = {Size}")]
	public ref class Vector3Array : AlignedObjectArray
	{
	internal:
		Vector3Array(btAlignedObjectArray<btVector3>* vector3Array);

	public:
		Vector3Array();

		void Clear();
		void PopBack();
		void PushBack(Vector3 vector3Value);
		void Remove(Vector3 vector3Value);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property Vector3 default [int]
		{
			Vector3 get (int index);
			void set(int index, Vector3 value);
		}

	internal:
		property btAlignedObjectArray<btVector3>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btVector3>* get() new;
		}
	};

#ifndef DISABLE_VEHICLE
	[DebuggerDisplay("Size = {Size}")]
	public ref class WheelInfoArray : AlignedObjectArray
	{
	internal:
		WheelInfoArray(btAlignedObjectArray<btWheelInfo>* wheelInfoArray);

	public:
		WheelInfoArray();

		void Clear();
		void PopBack();
		void PushBack(WheelInfo^ wheelInfo);
		void Remove(WheelInfo^ wheelInfo);
		void Swap(int index0, int index1);

		property int Size
		{
			int get();
		}

		property int Capacity
		{
			int get();
		}

		property WheelInfo^ default [int]
		{
			WheelInfo^ get (int index);
			void set(int index, WheelInfo^ value);
		}

	internal:
		property btAlignedObjectArray<btWheelInfo>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btWheelInfo>* get() new;
		}
	};
#endif
};
