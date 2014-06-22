#pragma once

namespace BulletSharp
{
	public ref class Element : IDisposable
	{
	internal:
		btElement* _native;
		Element(btElement* native, bool preventDelete);

	private:
		bool _preventDelete;

	public:
		!Element();
	protected:
		~Element();

	public:
		Element();

		property int Id
		{
			int get();
			void set(int value);
		}

		property int Sz
		{
			int get();
			void set(int value);
		}
	};

	public ref class UnionFind : IDisposable
	{
	internal:
		btUnionFind* _native;
		UnionFind(btUnionFind* native);

	public:
		!UnionFind();
	protected:
		~UnionFind();

	public:
		UnionFind();

		void Allocate(int N);
		int Find(int p, int q);
		int Find(int x);
		void Free();
		Element^ GetElement(int index);
		bool IsRoot(int x);
		void Reset(int N);
		void SortIslands();
		void Unite(int p, int q);

		property int NumElements
		{
			int get();
		}
	};
};
