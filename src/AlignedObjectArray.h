#pragma once

#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif
#include "PersistentManifold.h"

namespace BulletSharp
{
	ref struct BroadphasePair;
	ref class CollisionObject;
	ref class CollisionShape;
	ref class CompoundShapeChild;
	ref class IndexedMesh;
	ref class ListDebugView;
	ref class TriangleMesh;
	ref class Vector3ListDebugView;
	ref class WheelInfo;

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		ref class Anchor;
		ref class Cluster;
		ref class Face;
		ref class Joint;
		ref class Link;
		ref class Material;
		ref class Node;
		ref class Note;
		ref class RigidContact;
		ref class SoftBody;
		ref class SoftContact;
		ref class Tetra;
	};
#endif

	generic<class T>
	public ref class AlignedObjectArray abstract : IList<T>
	{
	internal:
		void* _native;

	private:
		bool _ownsObject;

	internal:
		AlignedObjectArray(void* alignedObjectArray, bool ownsObject);
		AlignedObjectArray(void* alignedObjectArray);

		!AlignedObjectArray();
		~AlignedObjectArray();

	public:
		virtual void Add(T item) = 0;
		virtual void Clear() = 0;
		virtual bool Contains(T item);
		virtual void CopyTo(array<T>^ array, int arrayIndex) = 0;
		virtual System::Collections::IEnumerator^ GetObjectEnumerator() = System::Collections::IEnumerable::GetEnumerator;
		virtual IEnumerator<T>^ GetEnumerator() = IEnumerable<T>::GetEnumerator;
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
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedAnchorArray : AlignedObjectArray<Anchor^>
		{
		internal:
			AlignedAnchorArray(btSoftBody::tAnchorArray* anchorArray);

		public:
			AlignedAnchorArray();

			virtual void Add(Anchor^ anchor) override;
			virtual void Clear() override;
			virtual void CopyTo(array<Anchor^>^ array, int arrayIndex) override;
			virtual void PopBack() override;
			virtual void Swap(int index0, int index1) override;

			property int Count
			{
				virtual int get() override;
			}

			property int Capacity
			{
				int get();
			}

			property Anchor^ default [int]
			{
				virtual Anchor^ get (int index) override;
				virtual void set(int index, Anchor^ value) override;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedBroadphasePairArray : AlignedObjectArray<BroadphasePair^>
	{
	internal:
		AlignedBroadphasePairArray(btBroadphasePairArray* pairArray);

	public:
		AlignedBroadphasePairArray();

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
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedClusterArray : AlignedObjectArray<Cluster^>
		{
		internal:
			AlignedClusterArray(btSoftBody::tClusterArray* clusterArray);

		public:
			AlignedClusterArray();

			virtual void Add(Cluster^ cluster) override;
			virtual void Clear() override;
			virtual bool Contains(Cluster^ cluster) override;
			virtual void CopyTo(array<Cluster^>^ array, int arrayIndex) override;
			virtual int IndexOf(Cluster^ cluster) override;
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
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedCollisionObjectArray : AlignedObjectArray<CollisionObject^>, System::Collections::IEnumerable
	{
	internal:
		AlignedCollisionObjectArray(btCollisionObjectArray* collisionObjectArray);
		AlignedCollisionObjectArray(btCollisionObjectArray* collisionObjectArray, btCollisionWorld* collisionWorld);

	private:
		btCollisionWorld* _collisionWorld;
		List<CollisionObject^>^ _backingList;

	public:
		virtual void Add(CollisionObject^ item) override;
		void Add(CollisionObject^ item, short collisionFilterGroup, short collisionFilterMask);
		virtual void Clear() override;
		virtual bool Contains(CollisionObject^ item) override;
		virtual void CopyTo(array<CollisionObject^>^ array, int arrayIndex) override;
		virtual System::Collections::IEnumerator^ GetObjectEnumerator() override;
		virtual IEnumerator<CollisionObject^>^ GetEnumerator() override;
		virtual int IndexOf(CollisionObject^ item) override;
		virtual void PopBack() override;
		virtual bool Remove(CollisionObject^ item) override;
		virtual void RemoveAt(int index) override;
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
	};

#ifndef DISABLE_DBVT
	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedDbvtNodeArray : AlignedObjectArray<DbvtNode^>
	{
	internal:
		AlignedDbvtNodeArray(btAlignedObjectArray<const btDbvtNode*>* AlignedNodeArray);

	public:
		AlignedDbvtNodeArray();

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
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedStkNNArray : AlignedObjectArray<Dbvt::StkNN^>
	{
	internal:
		AlignedStkNNArray(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray);

	public:
		AlignedStkNNArray();

		virtual void Add(Dbvt::StkNN^ stkNn) override;
		virtual void Clear() override;
		virtual void CopyTo(array<Dbvt::StkNN^>^ array, int arrayIndex) override;
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

		property Dbvt::StkNN^ default [int]
		{
			virtual Dbvt::StkNN^ get (int index) override;
			virtual void set(int index, Dbvt::StkNN^ value) override;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedStkNpsArray : AlignedObjectArray<Dbvt::StkNps^>
	{
	internal:
		AlignedStkNpsArray(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray);

	public:
		AlignedStkNpsArray();

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
	};
#endif

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedFaceArray : AlignedObjectArray<Face^>, IList<Face^>
		{
		internal:
			AlignedFaceArray(btAlignedObjectArray<btSoftBody::Face>* faceArray);

		public:
			AlignedFaceArray();

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
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedIndexedMeshArray : AlignedObjectArray<IndexedMesh^>
	{
	internal:
		AlignedIndexedMeshArray(btAlignedObjectArray<btIndexedMesh>* indexedMeshArray);

	public:
		AlignedIndexedMeshArray();

		virtual void Add(IndexedMesh^ indexedMesh) override;
		virtual void Clear() override;
		virtual void CopyTo(array<IndexedMesh^>^ array, int arrayIndex) override;
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

		property IndexedMesh^ default [int]
		{
			virtual IndexedMesh^ get (int index) override;
			virtual void set(int index, IndexedMesh^ value) override;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedIntArray : AlignedObjectArray<int>
	{
	internal:
		AlignedIntArray(btAlignedObjectArray<int>* intArray);

	public:
		AlignedIntArray();

		virtual void Add(int integer) override;
		virtual void Clear() override;
		virtual bool Contains(int integer) override;
		virtual void CopyTo(array<int>^ array, int arrayIndex) override;
		virtual int IndexOf(int integer) override;
		virtual void PopBack() override;
		virtual bool Remove(int integer) override;
		void Resize(int newSize);
		void Resize(int newSize, int fillData);
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
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedJointArray : AlignedObjectArray<Joint^>, System::Collections::IEnumerable
		{
		internal:
			AlignedJointArray(btSoftBody::tJointArray* jointArray);

		public:
			AlignedJointArray();

			virtual void Add(Joint^ joint) override;
			virtual void Clear() override;
			virtual bool Contains(Joint^ joint) override;
			virtual void CopyTo(array<Joint^>^ array, int arrayIndex) override;
			virtual int IndexOf(Joint^ joint) override;
			virtual void PopBack() override;
			virtual bool Remove(Joint^ joint) override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property Joint^ default [int]
			{
				virtual Joint^ get (int index) override;
				virtual void set(int index, Joint^ value) override;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedManifoldArray : AlignedObjectArray<PersistentManifold>
	{
	internal:
		AlignedManifoldArray(btManifoldArray* manifoldArray);

	public:
		AlignedManifoldArray();

		virtual void Add(PersistentManifold manifold) override;
		virtual void Clear() override;
		virtual bool Contains(PersistentManifold manifold) override;
		virtual void CopyTo(array<PersistentManifold>^ array, int arrayIndex) override;
		virtual int IndexOf(PersistentManifold manifold) override;
		virtual void PopBack() override;
		virtual bool Remove(PersistentManifold manifold) override;
		virtual void Swap(int index0, int index1) override;

		property int Capacity
		{
			int get();
		}

		property int Count
		{
			virtual int get() override;
		}

		property PersistentManifold default [int]
		{
			virtual PersistentManifold get (int index) override;
			virtual void set(int index, PersistentManifold value) override;
		}
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedLinkArray : AlignedObjectArray<Link^>, System::Collections::IEnumerable
		{
		internal:
			AlignedLinkArray(btSoftBody::tLinkArray* linkArray);

		public:
			AlignedLinkArray();

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
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedMaterialArray : AlignedObjectArray<Material^>
		{
		internal:
			AlignedMaterialArray(btSoftBody::tMaterialArray* materialArray);

		public:
			AlignedMaterialArray();

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
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedNodeArray : AlignedObjectArray<Node^>
		{
		internal:
			AlignedNodeArray(btSoftBody::tNodeArray* AlignedNodeArray);

		public:
			AlignedNodeArray();

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
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedNodePtrArray : AlignedObjectArray<Node^>
		{
		internal:
			AlignedNodePtrArray(btAlignedObjectArray<btSoftBody::Node*>* AlignedNodeArray);

		public:
			AlignedNodePtrArray();

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
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedNoteArray : AlignedObjectArray<Note^>
		{
		internal:
			AlignedNoteArray(btSoftBody::tNoteArray* noteArray);

		public:
			AlignedNoteArray();

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
		};
	};
#endif

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedPSolverArray : AlignedObjectArray<PSolver>
		{
		internal:
			AlignedPSolverArray(btSoftBody::tPSolverArray* pSolverArray);

		public:
			AlignedPSolverArray();

			virtual void Add(PSolver solver) override;
			virtual void Clear() override;
			virtual bool Contains(PSolver solver) override;
			virtual void CopyTo(array<PSolver>^ array, int arrayIndex) override;
			virtual int IndexOf(PSolver solver) override;
			virtual void PopBack() override;
			virtual bool Remove(PSolver solver) override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property PSolver default [int]
			{
				virtual PSolver get (int index) override;
				virtual void set(int index, PSolver value) override;
			}
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedRigidContactArray : AlignedObjectArray<RigidContact^>
		{
		internal:
			AlignedRigidContactArray(btSoftBody::tRContactArray* rigidContactArray);

		public:
			AlignedRigidContactArray();

			virtual void Add(RigidContact^ rigidContact) override;
			virtual void Clear() override;
			virtual void CopyTo(array<RigidContact^>^ array, int arrayIndex) override;
			virtual void PopBack() override;
			virtual void Swap(int index0, int index1) override;

			property int Count
			{
				virtual int get() override;
			}

			property int Capacity
			{
				int get();
			}

			property RigidContact^ default [int]
			{
				virtual RigidContact^ get (int index) override;
				virtual void set(int index, RigidContact^ value) override;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedScalarArray : AlignedObjectArray<btScalar>
	{
	internal:
		AlignedScalarArray(btAlignedObjectArray<btScalar>* btScalarArray);

	public:
		AlignedScalarArray();

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
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedSoftBodyArray : AlignedObjectArray<SoftBody^>
		{
		internal:
			AlignedSoftBodyArray(btSoftBody::tSoftBodyArray* softBodyArray);

		public:
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
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedSoftContactArray : AlignedObjectArray<SoftContact^>
		{
		internal:
			AlignedSoftContactArray(btSoftBody::tSContactArray* softContactArray);

		public:
			AlignedSoftContactArray();

			virtual void Add(SoftContact^ softContact) override;
			virtual void Clear() override;
			virtual void CopyTo(array<SoftContact^>^ array, int arrayIndex) override;
			virtual void PopBack() override;
			virtual void Swap(int index0, int index1) override;

			property int Count
			{
				virtual int get() override;
			}

			property int Capacity
			{
				int get();
			}

			property SoftContact^ default [int]
			{
				virtual SoftContact^ get (int index) override;
				virtual void set(int index, SoftContact^ value) override;
			}
		};

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedTetraArray : AlignedObjectArray<Tetra^>, IList<Tetra^>
		{
		internal:
			AlignedTetraArray(btAlignedObjectArray<btSoftBody::Tetra>* tetraArray);

		public:
			AlignedTetraArray();

			virtual void Add(Tetra^ tetra) override;
			virtual void Clear() override;
			virtual void CopyTo(array<Tetra^>^ array, int tetraIndex) override;
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

			property Tetra^ default [int]
			{
				virtual Tetra^ get (int index) override;
				virtual void set(int index, Tetra^ value) override;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class AlignedTriangleMeshArray : AlignedObjectArray<TriangleMesh^>
	{
	internal:
		AlignedTriangleMeshArray(btAlignedObjectArray<btTriangleMesh*>* triangleMeshArray);

	public:
		AlignedTriangleMeshArray();

		virtual void Add(TriangleMesh^ triangleMesh) override;
		virtual void Clear() override;
		virtual void CopyTo(array<TriangleMesh^>^ array, int arrayIndex) override;
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

		property TriangleMesh^ default [int]
		{
			virtual TriangleMesh^ get (int index) override;
			virtual void set(int index, TriangleMesh^ value) override;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(Vector3ListDebugView::typeid)]
	public ref class AlignedVector3Array : AlignedObjectArray<Vector3>
	{
	internal:
		AlignedVector3Array(btAlignedObjectArray<btVector3>* vector3Array);

	public:
		AlignedVector3Array();

		virtual void Add(Vector3 vector) override;
		void Add(Vector4 vector);
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
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class AlignedVSolverArray : AlignedObjectArray<VSolver>
		{
		internal:
			AlignedVSolverArray(btSoftBody::tVSolverArray* vSolverArray);

		public:
			AlignedVSolverArray();

			virtual void Add(VSolver solver) override;
			virtual void Clear() override;
			virtual bool Contains(VSolver solver) override;
			virtual void CopyTo(array<VSolver>^ array, int arrayIndex) override;
			virtual int IndexOf(VSolver solver) override;
			virtual void PopBack() override;
			virtual bool Remove(VSolver solver) override;
			virtual void Swap(int index0, int index1) override;

			property int Capacity
			{
				int get();
			}

			property int Count
			{
				virtual int get() override;
			}

			property VSolver default [int]
			{
				virtual VSolver get (int index) override;
				virtual void set(int index, VSolver value) override;
			}
		};
	};
#endif
};
