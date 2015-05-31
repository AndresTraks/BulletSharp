#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "UnionFind.h"

Element::Element(btElement* native)
{
	_native = native;
}

int Element::Id::get()
{
	return _native->m_id;
}
void Element::Id::set(int value)
{
	_native->m_id = value;
}

int Element::Sz::get()
{
	return _native->m_sz;
}
void Element::Sz::set(int value)
{
	_native->m_sz = value;
}


UnionFind::UnionFind(btUnionFind* native)
{
	_native = native;
}

UnionFind::~UnionFind()
{
	this->!UnionFind();
}

UnionFind::!UnionFind()
{
	delete _native;
	_native = NULL;
}

UnionFind::UnionFind()
{
	_native = new btUnionFind();
}

void UnionFind::Allocate(int n)
{
	_native->allocate(n);
}

int UnionFind::Find(int p, int q)
{
	return _native->find(p, q);
}

int UnionFind::Find(int x)
{
	return _native->find(x);
}

void UnionFind::Free()
{
	_native->Free();
}

Element^ UnionFind::GetElement(int index)
{
	return gcnew Element(&_native->getElement(index));
}

bool UnionFind::IsRoot(int x)
{
	return _native->isRoot(x);
}

void UnionFind::Reset(int n)
{
	_native->reset(n);
}

void UnionFind::SortIslands()
{
	_native->sortIslands();
}

void UnionFind::Unite(int p, int q)
{
	_native->unite(p, q);
}

int UnionFind::NumElements::get()
{
	return _native->getNumElements();
}

#endif
