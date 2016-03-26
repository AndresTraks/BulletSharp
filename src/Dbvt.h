#pragma once

namespace BulletSharp
{
	ref class DbvtNode;
	ref class DbvtNodePtrArray;
	ref class AlignedDbvtNodeArray;
	ref class AlignedIntArray;
	ref class AlignedStkNNArray;
	ref class AlignedStkNpsArray;

	public ref class DbvtAabbMm
	{
	internal:
		btDbvtAabbMm* _native;

		DbvtAabbMm(btDbvtAabbMm* native);

	public:
		//DbvtAabbMm();

		int Classify(Vector3 n, btScalar o, int s);
		bool Contain(DbvtAabbMm^ a);
		void Expand(Vector3 e);
		static DbvtAabbMm^ FromCE(Vector3 c, Vector3 e);
		static DbvtAabbMm^ FromCR(Vector3 c, btScalar r);
		static DbvtAabbMm^ FromMM(Vector3 mi, Vector3 mx);
		static DbvtAabbMm^ FromPoints(array<Vector3>^ pts);
		btScalar ProjectMinimum(Vector3 v, unsigned int signs);
		void SignedExpand(Vector3 e);

		property Vector3 Center
		{
			Vector3 get();
		}

		property Vector3 Extents
		{
			Vector3 get();
		}

		property Vector3 Lengths
		{
			Vector3 get();
		}

		property Vector3 Maxs
		{
			Vector3 get();
		}

		property Vector3 Mins
		{
			Vector3 get();
		}

		property Vector3 TMaxs
		{
			Vector3 get();
		}

		property Vector3 TMins
		{
			Vector3 get();
		}
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

	private:
		DbvtNode^ _parent;

	internal:
		DbvtNode(btDbvtNode* native);

	public:
		//DbvtNode();

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
		}
	};

	public ref class Dbvt : ITrackingDisposable
	{
	public:
		ref class IClone
		{
		internal:
			btDbvt::IClone* _native;

			IClone(btDbvt::IClone* native);

			~IClone();
			!IClone();

		public:
			//IClone();

			void CloneLeaf(DbvtNode^ n);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		ref class ICollide
		{
		internal:
			btDbvt::ICollide* _native;

			ICollide(btDbvt::ICollide* native);

			~ICollide();
			!ICollide();

		public:
			bool AllLeaves(DbvtNode^ n);
			bool Descent(DbvtNode^ n);
			void Process(DbvtNode^ na, DbvtNode^ nb);
			void Process(DbvtNode^ n);
			void Process(DbvtNode^ n, btScalar s);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		ref class IWriter abstract
		{
		internal:
			btDbvt::IWriter* _native;

			IWriter(btDbvt::IWriter* native);

			~IWriter();
			!IWriter();

		public:
			void Prepare(DbvtNode^ root, int numnodes);
			void WriteLeaf(DbvtNode^ n, int index, int parent);
			void WriteNode(DbvtNode^ n, int index, int parent, int child0,
				int child1);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		ref class StkCln
		{
		internal:
			btDbvt::sStkCLN* _native;

			StkCln(btDbvt::sStkCLN* native);

		public:
			StkCln(DbvtNode^ n, DbvtNode^ p);

			property DbvtNode^ Node
			{
				DbvtNode^ get();
			}

			property DbvtNode^ Parent
			{
				DbvtNode^ get();
				void set(DbvtNode^ value);
			}
		};

		ref class StkNN
		{
		internal:
			btDbvt::sStkNN* _native;

			StkNN(btDbvt::sStkNN* native);

		public:
			StkNN();
			StkNN(DbvtNode^ na, DbvtNode^ nb);

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

		ref class StkNP
		{
		internal:
			btDbvt::sStkNP* _native;

			StkNP(btDbvt::sStkNP* native);

		public:
			StkNP(DbvtNode^ n, unsigned int m);

			property int Mask
			{
				int get();
				void set(int value);
			}

			property DbvtNode^ Node
			{
				DbvtNode^ get();
			}
		};

		ref class StkNps
		{
		internal:
			btDbvt::sStkNPS* _native;

			StkNps(btDbvt::sStkNPS* native);

		public:
			StkNps();
			StkNps(DbvtNode^ n, unsigned int m, btScalar v);

			property int Mask
			{
				int get();
				void set(int value);
			}

			property DbvtNode^ Node
			{
				DbvtNode^ get();
			}

			property btScalar Value
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btDbvt* _native;

	private:
		bool _preventDelete;

	internal:
		Dbvt(btDbvt* native, bool preventDelete);

		~Dbvt();
		!Dbvt();

	public:
		Dbvt();

		static int Allocate(AlignedIntArray^ ifree, AlignedStkNpsArray^ stock,
			StkNps^ value);
		static void Benchmark();
		void Clear();
		void Clone(Dbvt^ dest, IClone^ iclone);
		void Clone(Dbvt^ dest);
		static void CollideKdop(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets,
			ICollide^ policy);
		static void CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets, Vector3 sortaxis,
			int count, ICollide^ policy, bool fullsort);
		static void CollideOcl(DbvtNode^ root, array<Vector3>^ normals, array<btScalar>^ offsets, Vector3 sortaxis,
			int count, ICollide^ policy);
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
		void OptimizeTopDown(int buTreshold);
		void OptimizeTopDown();
		static void RayTest(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo, ICollide^ policy);
#ifndef DISABLE_INTERNAL
		void RayTestInternal(DbvtNode^ root, Vector3 rayFrom, Vector3 rayTo, Vector3 rayDirectionInverse,
			array<unsigned int>^ signs, btScalar lambdaMax, Vector3 aabbMin, Vector3 aabbMax,
			ICollide^ policy);
#endif
		void Remove(DbvtNode^ leaf);
		void Update(DbvtNode^ leaf, DbvtVolume^ volume);
		void Update(DbvtNode^ leaf, int lookahead);
		void Update(DbvtNode^ leaf);
		bool Update(DbvtNode^ leaf, DbvtVolume^ volume, btScalar margin);
		bool Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity);
		bool Update(DbvtNode^ leaf, DbvtVolume^ volume, Vector3 velocity, btScalar margin);
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

		property unsigned int Opath
		{
			unsigned int get();
			void set(unsigned int value);
		}

		property AlignedDbvtNodeArray^ RayTestStack
		{
			AlignedDbvtNodeArray^ get();
		}

		property DbvtNode^ Root
		{
			DbvtNode^ get();
			void set(DbvtNode^ value);
		}

		property AlignedStkNNArray^ StkStack
		{
			AlignedStkNNArray^ get();
		}
	};
};
