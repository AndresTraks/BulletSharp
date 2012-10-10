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
	private:
		btDbvtAabbMm* _aabbMm;

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

	internal:
		property btDbvtAabbMm* UnmanagedPointer
		{
			virtual btDbvtAabbMm* get();
			void set(btDbvtAabbMm* value);
		}
	};

	public ref class DbvtVolume : DbvtAabbMm
	{
	internal:
		DbvtVolume(btDbvtVolume* aabbMm);

		property btDbvtVolume* UnmanagedPointer
		{
			btDbvtVolume* get() new;
		}
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
		private:
			btDbvt::sStkNN* _stkNn;

		internal:
			StkNn(btDbvt::sStkNN* stkNn);

		public:
			StkNn();
			StkNn(DbvtNode^ na, DbvtNode^ nb);

		internal:
			property btDbvt::sStkNN* UnmanagedPointer
			{
				btDbvt::sStkNN* get();
				void set(btDbvt::sStkNN* value);
			}
		};

		ref class StkNp
		{
		private:
			btDbvt::sStkNP* _stkNp;

		internal:
			StkNp(btDbvt::sStkNP* stkNp);

		public:
			StkNp(DbvtNode^ n, unsigned m);

		internal:
			property btDbvt::sStkNP* UnmanagedPointer
			{
				btDbvt::sStkNP* get();
				void set(btDbvt::sStkNP* value);
			}
		};

		ref class StkNps
		{
		private:
			btDbvt::sStkNPS* _stkNps;

		internal:
			StkNps(btDbvt::sStkNPS* stkNps);

		public:
			StkNps();
			StkNps(DbvtNode^ n, unsigned m, btScalar v);

		internal:
			property btDbvt::sStkNPS* UnmanagedPointer
			{
				btDbvt::sStkNPS* get();
				void set(btDbvt::sStkNPS* value);
			}
		};

		ref class StkCln
		{
		private:
			btDbvt::sStkCLN* _stkCln;

		internal:
			StkCln(btDbvt::sStkCLN* stkCln);

		public:
			StkCln(DbvtNode^ na, DbvtNode^ nb);

		internal:
			property btDbvt::sStkCLN* UnmanagedPointer
			{
				btDbvt::sStkCLN* get();
				void set(btDbvt::sStkCLN* value);
			}
		};

		ref class ICollide : BulletSharp::IDisposable
		{
		private:
			btDbvt::ICollide* _iCollide;

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

		internal:
			property btDbvt::ICollide* UnmanagedPointer
			{
				virtual btDbvt::ICollide* get();
				void set(btDbvt::ICollide* value);
			}
		};

		ref class IWriter : BulletSharp::IDisposable
		{
		private:
			btDbvt::IWriter* _iWriter;

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

		internal:
			property btDbvt::IWriter* UnmanagedPointer
			{
				virtual btDbvt::IWriter* get();
				void set(btDbvt::IWriter* value);
			}
		};

		ref class IClone : BulletSharp::IDisposable
		{
		private:
			btDbvt::IClone* _iClone;

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

		internal:
			property btDbvt::IClone* UnmanagedPointer
			{
				virtual btDbvt::IClone* get();
				void set(btDbvt::IClone* value);
			}
		};


		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btDbvt* _dbvt;

	internal:
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

	internal:
		property btDbvt* UnmanagedPointer
		{
			virtual btDbvt* get();
			void set(btDbvt* value);
		}
	};
};
