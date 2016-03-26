#pragma once

namespace BulletSharp
{
	public ref class Element
	{
	internal:
		btElement* _native;

		Element(btElement* native);

	public:
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

	public ref class UnionFind
	{
	internal:
		btUnionFind* _native;

		UnionFind(btUnionFind* native);

		~UnionFind();
		!UnionFind();

	public:
		UnionFind();

		void Allocate(int n);
		int Find(int p, int q);
		int Find(int x);
		void Free();
		Element^ GetElement(int index);
		bool IsRoot(int x);
		void Reset(int n);
		void SortIslands();
		void Unite(int p, int q);

		property int NumElements
		{
			int get();
		}
	};
};
