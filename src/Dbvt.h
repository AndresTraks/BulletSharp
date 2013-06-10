#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class DbvtNode;
	ref class DbvtNodePtrArray;
	ref class AlignedDbvtNodeArray;
	ref class AlignedIntArray;
	ref class AlignedStkNnArray;
	ref class AlignedStkNpsArray;

	public ref class DbvtAabbMm
	{
	internal:
		btDbvtAabbMm* _native;

	internal:
		DbvtAabbMm(btDbvtAabbMm* aabbMm);

	public:
		Vector3 Center();
		Vector3 Lengths();
		Vector3 Extents();
		Vector3 Mins();
		Vector3 Maxs();
		static DbvtAabbMm^ FromCE(Vector3 c, Vector3 e);
		static DbvtAabbMm^ FromCR(Vector3 c, btScalar r);
		static DbvtAabbMm^ FromMM(Vector3 mi, Vector3 mx);
		static DbvtAabbMm^ FromPoints(array<Vector3>^ pts);
		void Expand(Vector3 e);
		void SignedExpand(Vector3 e);
		bool Contain(DbvtAabbMm^ a);
		int Classify(Vector3 n, btScalar o, int s);
		btScalar ProjectMinimum(Vector3 v, unsigned signs);
	};

	public ref class DbvtVolume : DbvtAabbMm
	{
	internal:
		DbvtVolume(btDbvtVolume* aabbMm);
	};

	public ref class DbvtNode
	{
	internal:
		btDbvtNode* _native;

		DbvtNode(btDbvtNode* node);

	public:
		property DbvtNodePtrArray^ Childs
		{
			DbvtNodePtrArray^ get();
		}

		property IntPtr Data
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property int DataAsInt
		{
			int get();
			void set(int value);
		}

		property bool IsInternal
		{
			bool get();
		}

		property bool IsLeaf
		{
			bool get();
		}

		property DbvtNode^ Parent
		{
			DbvtNode^ get();
			void set(DbvtNode^ value);
		}

		property DbvtVolume^ Volume
		{
			DbvtVolume^ get();
			void set(DbvtVolume^ value);
		}
	};

	public ref class Dbvt : BulletSharp::IDisposable
	{
	public:
		ref class StkNn
		{
		internal:
			btDbvt::sStkNN* _native;

			StkNn(btDbvt::sStkNN* stkNn);

		public:
			StkNn();
			StkNn(DbvtNode^ na, DbvtNode^ nb);

			property DbvtNode^ A
			{
				DbvtNode^ get();
				void set(DbvtNode^ value);
			}

			property DbvtNode^ B
			{
				DbvtNode^ get();
				void set(DbvtNode^ value);
			}
		};

		ref class StkNp
		{
		internal:
			btDbvt::sStkNP* _native;

			StkNp(btDbvt::sStkNP* stkNp);

		public:
			StkNp(DbvtNode^ n, unsigned m);
		};

		ref class StkNps
		{
		internal:
			btDbvt::sStkNPS* _native;

			StkNps(btDbvt::sStkNPS* stkNps);

		public:
			StkNps();
			StkNps(DbvtNode^ n, unsigned m, btScalar v);
		};

		ref class StkCln
		{
		internal:
			btDbvt::sStkCLN* _native;

			StkCln(btDbvt::sStkCLN* stkCln);

		public:
			StkCln(DbvtNode^ na, DbvtNode^ nb);
		};

		ref class ICollide : BulletSharp::IDisposable
		{
		internal:
			btDbvt::ICollide* _native;

		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		internal:
			ICollide(btDbvt::ICollide* iCollide);

		public:
			!ICollide();
		protected:
			~ICollide();

		public:
			bool AllLeaves(DbvtNode^ n);
			bool Descent(DbvtNode^ n);
			void Process(DbvtNode^ n, btScalar s);
			void Process(DbvtNode^ n);
			void Process(DbvtNode^ na, DbvtNode^ nb);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		ref class IWriter : BulletSharp::IDisposable
		{
		internal:
			btDbvt::IWriter* _native;

		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		internal:
			IWriter(btDbvt::IWriter* iWriter);

		public:
			!IWriter();
		protected:
			~IWriter();

		public:
			void Prepare(DbvtNode^ root, int numnodes);
			void WriteLeaf(DbvtNode^ n, int index, int parent);
			void WriteNode(DbvtNode^ n, int index, int parent, int child0, int child1);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		ref class IClone : BulletSharp::IDisposable
		{
		internal:
			btDbvt::IClone* _native;

		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		internal:
			IClone(btDbvt::IClone* iCollide);

		public:
			!IClone();
		protected:
			~IClone();

		public:
			void CloneLeaf(DbvtNode^ n);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};


		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btDbvt* _native;

		Dbvt(btDbvt* dbvt);

	public:
		!Dbvt();
	protected:
		~Dbvt();

	public:
		Dbvt();

		static int Allocate(AlignedIntArray^ ifree, AlignedStkNpsArray^ stock, StkNps^ value);
		static void Benchmark();
		void Clear();
		void Clone(Dbvt^ dest, IClone^ iclone);
		void Clone(Dbvt^ dest);
		static void CollideKdop(DbvtNode^ root, array<Vector3>^ normals,
			array<btScalar>^ offsets, int count, ICollide^ policy);
		static void CollideOcl(DbvtNode^ root, array<Vector3>^ normals,
			array<btScalar>^ offsets, Vector3 sortaxis, int count,
			ICollide^ policy, bool fullsort);
		static void CollideOcl(DbvtNode^ root, array<Vector3>^ normals,
			array<btScalar>^ offsets, Vector3 sortaxis, int count,
			ICollide^ policy);
		void CollideTT(DbvtNode^ root0, DbvtNode^ root1, ICollide^ policy);
		void CollideTTPersistentStack(DbvtNode^ root0, DbvtNode^ root1, ICollide^ policy);
		static void CollideTU(DbvtNode^ root, ICollide^ policy);
		void CollideTV(DbvtNode^ root, DbvtVolume^ volume, ICollide^ policy);
		static int CountLeaves(DbvtNode^ node);
		bool Empty();
		static void EnumLeaves(DbvtNode^ root, ICollide^ policy);
		static void EnumNodes(DbvtNode^ root, ICollide^ policy);
		static void ExtractLeaves(DbvtNode^ node, AlignedDbvtNodeArray^ leaves);
		DbvtNode^ Insert(DbvtVolume^ box, IntPtr data);
		static int MaxDepth(DbvtNode^ node);
		static int Nearest(array<int>^ i, StkNps^ a, btScalar v, int l, int h);
		void OptimizeBottomUp();
		void OptimizeIncremental(int passes);
		void OptimizeTopDown(int bu_treshold);
		void OptimizeTopDown();
		static void RayTest(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo,	ICollide^ policy);

#ifndef DISABLE_INTERNAL
		void RayTestInternal(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo,
			Vector3 rayDirectionInverse, array<unsigned int>^ signs,
			btScalar lambda_max, Vector3 aabbMin, Vector3 aabbMax, ICollide^ policy);
#endif

		void Remove(DbvtNode^ leaf);
		bool Update(DbvtNode^ leaf, DbvtVolume^ volume, btScalar margin);
		bool Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity);
		bool Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity, btScalar margin);
		void Update(DbvtNode^ leaf, DbvtVolume^ volume);
		void Update(DbvtNode^ leaf, int lookahead);
		void Update(DbvtNode^ leaf);
		void Write(IWriter^ iwriter);

		property DbvtNode^ Free
		{
			DbvtNode^ get();
			void set(DbvtNode^ value);
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property int Leaves
		{
			int get();
			void set(int value);
		}

		property int Lkhd
		{
			int get();
			void set(int value);
		}

		property unsigned Opath
		{
			unsigned get();
			void set(unsigned value);
		}

		property DbvtNode^ Root
		{
			DbvtNode^ get();
			void set(DbvtNode^ value);
		}

		property AlignedStkNnArray^ Stack
		{
			AlignedStkNnArray^ get();
			void set(AlignedStkNnArray^ value);
		}
	};
};
