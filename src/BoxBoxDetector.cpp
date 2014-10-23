#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BoxBoxDetector.h"
#include "BoxShape.h"

#define Native static_cast<btBoxBoxDetector*>(_native)

BoxBoxDetector::BoxBoxDetector(BoxShape^ box1, BoxShape^ box2)
	: DiscreteCollisionDetectorInterface(ALIGNED_NEW(btBoxBoxDetector) ((btBoxShape*)box1->_native,
		(btBoxShape*)box2->_native))
{
	_box1 = box1;
	_box2 = box2;
}

BoxShape^ BoxBoxDetector::Box1::get()
{
	return _box1;
}
void BoxBoxDetector::Box1::set(BoxShape^ value)
{
	Native->m_box1 = (btBoxShape*)value->_native;
	_box1 = value;
}

BoxShape^ BoxBoxDetector::Box2::get()
{
	return _box2;
}
void BoxBoxDetector::Box2::set(BoxShape^ value)
{
	Native->m_box2 = (btBoxShape*)value->_native;
	_box2 = value;
}

#endif
