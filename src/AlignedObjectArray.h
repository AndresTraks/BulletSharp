#pragma once

#include "Collections.h"
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

	generic<class T>
	public ref class AlignedObjectArray abstract : Generic::IList<T>, BulletSharp::IDisposable
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
		virtual void Add(T item) = 0;
		virtual void Clear() = 0;
		virtual bool Contains(T item);
		virtual void CopyTo(array<T>^ array, int arrayIndex) = 0;
		virtual IEnumerator^ GetEnumerator() = IEnumerable::GetEnumerator;
		virtual Generic::IEnumerator<T>^ GetSpecializedEnumerator() = Generic::IEnumerable<T>::GetEnumerator;
		virtual int IndexOf(T item);
		virtual void Insert(int index, T item);
		virtual void PopBack() = 0;
		virtual bool Remove(T item);
		virtual void RemoveAt(int index);
		virtual void Swap(int index0, int index1) = 0;

		property int Count
		{
			virtual int get() = 0;
		}

		property T default [int]
		{
			virtual T get (int index) = 0;
			virtual void set(int index, T value) = 0;
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool IsReadOnly
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

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class BroadphasePairArray : AlignedObjectArray<BroadphasePair^>
	{
	internal:
		BroadphasePairArray(btBroadphasePairArray* pairArray);

	public:
		BroadphasePairArray();

		virtual void Add(BroadphasePair^ pair) override;
		virtual void Clear() override;
		virtual bool Contains(BroadphasePair^ pair) override;
		virtual void CopyTo(array<BroadphasePair^>^ array, int arrayIndex) override;
		virtual int IndexOf(BroadphasePair^ pair) override;
		virtual void PopBack() override;
		virtual bool Remove(BroadphasePair^ pair) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property BroadphasePair^ default [int]
		{
			virtual BroadphasePair^ get (int index) override;
			virtual void set(int index, BroadphasePair^ value) override;
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
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class ClusterArray : AlignedObjectArray<Cluster^>
		{
		internal:
			ClusterArray(btSoftBody::tClusterArray* clusterArray);

		public:
			ClusterArray();

			virtual void Add(Cluster^ cluster) override;
			virtual void Clear() override;
			virtual bool Contains(Cluster^ item) override;
			virtual void CopyTo(array<Cluster^>^ array, int arrayIndex) override;
			virtual int IndexOf(Cluster^ item) override;
			virtual void PopBack() override;
			virtual bool Remove(Cluster^ cluster) override;
			virtual void Swap(int index0, int index1) override;

			property int Count
			{
				virtual int get() override;
			}

			property int Capacity
			{
				int get();
			}

			property Cluster^ default [int]
			{
				virtual Cluster^ get (int index) override;
				virtual void set(int index, Cluster^ value) override;
			}

		internal:
			property btSoftBody::tClusterArray* UnmanagedPointer
			{
				virtual btSoftBody::tClusterArray* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class CollisionShapeArray : AlignedObjectArray<CollisionShape^>
	{
	public:
		CollisionShapeArray();

		virtual void Add(CollisionShape^ shape) override;
		virtual void Clear() override;
		virtual bool Contains(CollisionShape^ shape) override;
		virtual void CopyTo(array<CollisionShape^>^ array, int arrayIndex) override;
		virtual int IndexOf(CollisionShape^ shape) override;
		virtual void PopBack() override;
		virtual bool Remove(CollisionShape^ shape) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property CollisionShape^ default [int]
		{
			virtual CollisionShape^ get (int index) override;
			virtual void set(int index, CollisionShape^ value) override;
		}

	internal:
		property btAlignedObjectArray<btCollisionShape*>* UnmanagedPointer
		{
			btAlignedObjectArray<btCollisionShape*>* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class CollisionObjectArray : AlignedObjectArray<CollisionObject^>, IEnumerable
	{
	internal:
		CollisionObjectArray(btCollisionObjectArray* collisionObjectArray);

	public:
		CollisionObjectArray();

		virtual void Add(CollisionObject^ obj) override;
		virtual void Clear() override;
		virtual bool Contains(CollisionObject^ obj) override;
		virtual void CopyTo(array<CollisionObject^>^ array, int arrayIndex) override;
		virtual int IndexOf(CollisionObject^ obj) override;
		virtual void PopBack() override;
		virtual bool Remove(CollisionObject^ obj) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property CollisionObject^ default [int]
		{
			virtual CollisionObject^ get (int index) override;
			virtual void set(int index, CollisionObject^ value) override;
		}

	internal:
		property btCollisionObjectArray* UnmanagedPointer
		{
			virtual btCollisionObjectArray* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class CompoundShapeChildArray : AlignedObjectArray<CompoundShapeChild^>
	{
	internal:
		CompoundShapeChildArray(btAlignedObjectArray<btCompoundShapeChild>* compundShapeChildArray);

	public:
		CompoundShapeChildArray();

		virtual void Add(CompoundShapeChild^ child) override;
		virtual void Clear() override;
		virtual bool Contains(CompoundShapeChild^ child) override;
		virtual void CopyTo(array<CompoundShapeChild^>^ array, int arrayIndex) override;
		virtual int IndexOf(CompoundShapeChild^ child) override;
		virtual void PopBack() override;
		virtual bool Remove(CompoundShapeChild^ child) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property CompoundShapeChild^ default [int]
		{
			virtual CompoundShapeChild^ get (int index) override;
			virtual void set(int index, CompoundShapeChild^ value) override;
		}

	internal:
		property btAlignedObjectArray<btCompoundShapeChild>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btCompoundShapeChild>* get() new;
		}
	};

#ifndef DISABLE_DBVT
	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class DbvtNodeArray : AlignedObjectArray<DbvtNode^>
	{
	internal:
		DbvtNodeArray(btAlignedObjectArray<const btDbvtNode*>* nodeArray);

	public:
		DbvtNodeArray();

		virtual void Add(DbvtNode^ stkNps) override;
		virtual void Clear() override;
		virtual bool Contains(DbvtNode^ stkNps) override;
		virtual void CopyTo(array<DbvtNode^>^ array, int arrayIndex) override;
		virtual int IndexOf(DbvtNode^ stkNps) override;
		virtual void PopBack() override;
		virtual bool Remove(DbvtNode^ stkNps) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property DbvtNode^ default [int]
		{
			virtual DbvtNode^ get (int index) override;
			virtual void set(int index, DbvtNode^ value) override;
		}

	internal:
		property btAlignedObjectArray<const btDbvtNode*>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<const btDbvtNode*>* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class StkNnArray : AlignedObjectArray<Dbvt::StkNn^>
	{
	internal:
		StkNnArray(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray);

	public:
		StkNnArray();

		virtual void Add(Dbvt::StkNn^ stkNn) override;
		virtual void Clear() override;
		virtual void CopyTo(array<Dbvt::StkNn^>^ array, int arrayIndex) override;
		virtual void PopBack() override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property Dbvt::StkNn^ default [int]
		{
			virtual Dbvt::StkNn^ get (int index) override;
			virtual void set(int index, Dbvt::StkNn^ value) override;
		}

	internal:
		property btAlignedObjectArray<btDbvt::sStkNN>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btDbvt::sStkNN>* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class StkNpsArray : AlignedObjectArray<Dbvt::StkNps^>
	{
	internal:
		StkNpsArray(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray);

	public:
		StkNpsArray();

		virtual void Add(Dbvt::StkNps^ stkNps) override;
		virtual void Clear() override;
		virtual void CopyTo(array<Dbvt::StkNps^>^ array, int arrayIndex) override;
		virtual void PopBack() override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property Dbvt::StkNps^ default [int]
		{
			virtual Dbvt::StkNps^ get (int index) override;
			virtual void set(int index, Dbvt::StkNps^ value) override;
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
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class FaceArray : AlignedObjectArray<Face^>, Generic::IList<Face^>
		{
		internal:
			FaceArray(btAlignedObjectArray<btSoftBody::Face>* faceArray);

		public:
			FaceArray();

			virtual void Add(Face^ face) override;
			virtual void Clear() override;
			virtual void CopyTo(array<Face^>^ array, int arrayIndex) override;
			virtual void PopBack() override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property Face^ default [int]
			{
				virtual Face^ get (int index) override;
				virtual void set(int index, Face^ value) override;
			}

		internal:
			property btAlignedObjectArray<btSoftBody::Face>* UnmanagedPointer
			{
				virtual btAlignedObjectArray<btSoftBody::Face>* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class IntArray : AlignedObjectArray<int>
	{
	internal:
		IntArray(btAlignedObjectArray<int>* intArray);

	public:
		IntArray();

		virtual void Add(int integer) override;
		virtual void Clear() override;
		virtual bool Contains(int integer) override;
		virtual void CopyTo(array<int>^ array, int arrayIndex) override;
		virtual int IndexOf(int integer) override;
		virtual void PopBack() override;
		virtual bool Remove(int integer) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property int default [int]
		{
			virtual int get (int index) override;
			virtual void set(int index, int value) override;
		}

	internal:
		property btAlignedObjectArray<int>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<int>* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class ManifoldArray : AlignedObjectArray<PersistentManifold^>
	{
	internal:
		ManifoldArray(btManifoldArray* manifoldArray);

	public:
		ManifoldArray();

		virtual void Add(PersistentManifold^ manifold) override;
		virtual void Clear() override;
		virtual bool Contains(PersistentManifold^ manifold) override;
		virtual void CopyTo(array<PersistentManifold^>^ array, int arrayIndex) override;
		virtual int IndexOf(PersistentManifold^ manifold) override;
		virtual void PopBack() override;
		virtual bool Remove(PersistentManifold^ manifold) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property PersistentManifold^ default [int]
		{
			virtual PersistentManifold^ get (int index) override;
			virtual void set(int index, PersistentManifold^ value) override;
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
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class LinkArray : AlignedObjectArray<Link^>, IEnumerable
		{
		internal:
			LinkArray(btSoftBody::tLinkArray* linkArray);

		public:
			LinkArray();

			virtual void Add(Link^ link) override;
			virtual void Clear() override;
			virtual void CopyTo(array<Link^>^ array, int arrayIndex) override;
			virtual void PopBack() override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property Link^ default [int]
			{
				virtual Link^ get (int index) override;
				virtual void set(int index, Link^ value) override;
			}

		internal:
			property btSoftBody::tLinkArray* UnmanagedPointer
			{
				virtual btSoftBody::tLinkArray* get() new;
			}
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class MaterialArray : AlignedObjectArray<Material^>
		{
		internal:
			MaterialArray(btSoftBody::tMaterialArray* materialArray);

		public:
			MaterialArray();

			virtual void Add(Material^ material) override;
			virtual void Clear() override;
			virtual bool Contains(Material^ material) override;
			virtual void CopyTo(array<Material^>^ array, int arrayIndex) override;
			virtual int IndexOf(Material^ material) override;
			virtual void PopBack() override;
			virtual bool Remove(Material^ material) override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property Material^ default [int]
			{
				virtual Material^ get (int index) override;
				virtual void set(int index, Material^ value) override;
			}

		internal:
			property btSoftBody::tMaterialArray* UnmanagedPointer
			{
				virtual btSoftBody::tMaterialArray* get() new;
			}
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class NodeArray : AlignedObjectArray<Node^>
		{
		internal:
			NodeArray(btSoftBody::tNodeArray* nodeArray);

		public:
			NodeArray();

			virtual void Add(Node^ node) override;
			virtual void Clear() override;
			virtual void CopyTo(array<Node^>^ array, int arrayIndex) override;
			virtual void PopBack() override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property Node^ default [int]
			{
				virtual Node^ get (int index) override;
				virtual void set(int index, Node^ value) override;
			}

		internal:
			property btSoftBody::tNodeArray* UnmanagedPointer
			{
				virtual btSoftBody::tNodeArray* get() new;
			}
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class NodePtrArray : AlignedObjectArray<Node^>
		{
		internal:
			NodePtrArray(btAlignedObjectArray<btSoftBody::Node*>* nodeArray);

		public:
			NodePtrArray();

			virtual void Add(Node^ node) override;
			virtual void Clear() override;
			virtual bool Contains(Node^ node) override;
			virtual void CopyTo(array<Node^>^ array, int arrayIndex) override;
			virtual int IndexOf(Node^ node) override;
			virtual void PopBack() override;
			virtual bool Remove(Node^ node) override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property Node^ default [int]
			{
				virtual Node^ get (int index) override;
				virtual void set(int index, Node^ value) override;
			}

		internal:
			property btAlignedObjectArray<btSoftBody::Node*>* UnmanagedPointer
			{
				virtual btAlignedObjectArray<btSoftBody::Node*>* get() new;
			}
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class NoteArray : AlignedObjectArray<Note^>
		{
		internal:
			NoteArray(btSoftBody::tNoteArray* noteArray);

		public:
			NoteArray();

			virtual void Add(Note^ note) override;
			virtual void Clear() override;
			virtual void CopyTo(array<Note^>^ array, int arrayIndex) override;
			virtual void PopBack() override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property Note^ default [int]
			{
				virtual Note^ get (int index) override;
				virtual void set(int index, Note^ value) override;
			}

		internal:
			property btSoftBody::tNoteArray* UnmanagedPointer
			{
				virtual btSoftBody::tNoteArray* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class ScalarArray : AlignedObjectArray<btScalar>
	{
	internal:
		ScalarArray(btAlignedObjectArray<btScalar>* btScalarArray);

	public:
		ScalarArray();

		virtual void Add(btScalar scalar) override;
		virtual void Clear() override;
		virtual bool Contains(btScalar scalar) override;
		virtual void CopyTo(array<btScalar>^ array, int arrayIndex) override;
		virtual int IndexOf(btScalar scalar) override;
		virtual void PopBack() override;
		virtual bool Remove(btScalar scalar) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property btScalar default [int]
		{
			virtual btScalar get (int index) override;
			virtual void set(int index, btScalar value) override;
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
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class SoftBodyArray : AlignedObjectArray<SoftBody^>
		{
		internal:
			SoftBodyArray(btSoftBody::tSoftBodyArray* softBodyArray);

		public:
			SoftBodyArray();

			virtual void Add(SoftBody^ softBody) override;
			virtual void Clear() override;
			virtual bool Contains(SoftBody^ softBody) override;
			virtual void CopyTo(array<SoftBody^>^ array, int arrayIndex) override;
			virtual int IndexOf(SoftBody^ softBody) override;
			virtual void PopBack() override;
			virtual bool Remove(SoftBody^ softBody) override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property SoftBody^ default [int]
			{
				virtual SoftBody^ get (int index) override;
				virtual void set(int index, SoftBody^ value) override;
			}

		internal:
			property btSoftBody::tSoftBodyArray* UnmanagedPointer
			{
				virtual btSoftBody::tSoftBodyArray* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(Vector3ListDebugView::typeid)]
	public ref class Vector3Array : AlignedObjectArray<Vector3>
	{
	internal:
		Vector3Array(btAlignedObjectArray<btVector3>* vector3Array);

	public:
		Vector3Array();

		virtual void Add(Vector3 vector) override;
		virtual void Clear() override;
		virtual bool Contains(Vector3 vector) override;
		virtual void CopyTo(array<Vector3>^ array, int arrayIndex) override;
		virtual int IndexOf(Vector3 vector) override;
		virtual void PopBack() override;
		virtual bool Remove(Vector3 vector) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property Vector3 default [int]
		{
			virtual Vector3 get (int index) override;
			virtual void set(int index, Vector3 value) override;
		}

	internal:
		property btAlignedObjectArray<btVector3>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btVector3>* get() new;
		}
	};

#ifndef DISABLE_VEHICLE
	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class WheelInfoArray : AlignedObjectArray<WheelInfo^>
	{
	internal:
		WheelInfoArray(btAlignedObjectArray<btWheelInfo>* wheelInfoArray);

	public:
		WheelInfoArray();

		virtual void Add(WheelInfo^ wheelInfo) override;
		virtual void Clear() override;
		virtual void CopyTo(array<WheelInfo^>^ array, int arrayIndex) override;
		virtual void PopBack() override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property WheelInfo^ default [int]
		{
			virtual WheelInfo^ get (int index) override;
			virtual void set(int index, WheelInfo^ value) override;
		}

	internal:
		property btAlignedObjectArray<btWheelInfo>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btWheelInfo>* get() new;
		}
	};
#endif
};
