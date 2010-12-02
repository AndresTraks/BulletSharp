#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "UnionFind.h"

Element::Element(btElement* element)
{
	_element = element;
}

Element::Element()
{
	_element = new btElement();
}

int Element::Id::get()
{
	return _element->m_id;
}
void Element::Id::set(int value)
{
	_element->m_id = value;
}

int Element::Sz::get()
{
	return _element->m_sz;
}
void Element::Sz::set(int value)
{
	_element->m_sz = value;
}


UnionFind::UnionFind(btUnionFind* unionFind)
{
	_unionFind = unionFind;
}

UnionFind::UnionFind()
{
	_unionFind = new btUnionFind();
}

UnionFind::~UnionFind()
{
	this->!UnionFind();
}

UnionFind::!UnionFind()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing( this, nullptr );
	
	_unionFind = NULL;
	
	OnDisposed( this, nullptr );
}

void UnionFind::Allocate(int N)
{
	_unionFind->allocate(N);
}

int UnionFind::Find(int x)
{
	return _unionFind->find(x);
}

int UnionFind::Find(int p, int q)
{
	return _unionFind->find(p, q);
}

void UnionFind::Free()
{
	_unionFind->Free();
}

Element^ UnionFind::GetElement(int index)
{
	return gcnew Element(&_unionFind->getElement(index));
}

bool UnionFind::IsRoot(int x)
{
	return _unionFind->isRoot(x);
}

void UnionFind::Reset(int N)
{
	return _unionFind->reset(N);
}

void UnionFind::SortIslands()
{
	_unionFind->sortIslands();
}

void UnionFind::Unite(int p, int q)
{
	return _unionFind->unite(p, q);
}

bool UnionFind::IsDisposed::get()
{
	return (_unionFind == NULL);
}

int UnionFind::NumElements::get()
{
	return _unionFind->getNumElements();
}

#endif
