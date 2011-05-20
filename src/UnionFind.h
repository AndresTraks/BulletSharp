#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class Element
	{
	private:
		btElement* _element;

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

	internal:
		Element(btElement* element);
	};

	public ref class UnionFind : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btUnionFind* _unionFind;

	public:
		!UnionFind();
	protected:
		~UnionFind();

	internal:
		UnionFind(btUnionFind* unionFind);

	public:
		UnionFind();

		void Allocate(int N);
		int Find(int x);
		int Find(int p, int q);
		void Free();
		Element^ GetElement(int index);
		bool IsRoot(int x);
		void Reset(int N);
		void SortIslands();
		void Unite(int p, int q);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property int NumElements
		{
			int get();
		}
	};
};
