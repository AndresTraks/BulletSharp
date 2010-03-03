#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class DbvtNode;

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
	private:
		btDbvtNode* _node;
	internal:
		DbvtNode(btDbvtNode* node);

		property array<DbvtNode^>^ Childs
		{
			array<DbvtNode^>^ get();
			void set(array<DbvtNode^>^ value);
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

	internal:
		property btDbvtNode* UnmanagedPointer
		{
			virtual btDbvtNode* get();
			void set(btDbvtNode* value);
		}
	};

	public ref class Dbvt : BulletSharp::IDisposable
	{
	public:

		ref class StkNn
		{
		private:
			btDbvt::sStkNN* _stkNn;
//			StkNn();
//			StkNn(DbvtNode^ na, DbvtNode^ nb);

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
//			StkNp();
//			StkNp(DbvtNode^ na, DbvtNode^ nb);

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
//			StkNps();
//			StkNps(DbvtNode^ na, DbvtNode^ nb);

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
//			StkCln();
//			StkCln(DbvtNode^ na, DbvtNode^ nb);

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

	public:
		Dbvt();

	internal:
		Dbvt(btDbvt* dbvt);
	public:
		!Dbvt();
	protected:
		~Dbvt();
	public:
		static int Allocate(array<int>^ ifree, array<StkNps^>^ stock, StkNps^ value);
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

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btDbvt* UnmanagedPointer
		{
			virtual btDbvt* get();
			void set(btDbvt* value);
		}
	};
};
