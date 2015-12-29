#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "MultiBody.h"
#include "MultiBodyLinkCollider.h"

#define Native static_cast<btMultiBodyLinkCollider*>(_native)

MultiBodyLinkCollider::MultiBodyLinkCollider(btMultiBodyLinkCollider* native)
	: CollisionObject(native)
{
}

MultiBodyLinkCollider::MultiBodyLinkCollider(BulletSharp::MultiBody^ multiBody, int link)
	: CollisionObject(new btMultiBodyLinkCollider(multiBody->_native, link))
{
	_multiBody = multiBody;
}

MultiBodyLinkCollider^ MultiBodyLinkCollider::Upcast(CollisionObject^ colObj)
{
	return static_cast<MultiBodyLinkCollider^>(CollisionObject::GetManaged(btMultiBodyLinkCollider::upcast(colObj->_native)));
}

int MultiBodyLinkCollider::Link::get()
{
	return Native->m_link;
}
void MultiBodyLinkCollider::Link::set(int value)
{
	Native->m_link = value;
}

MultiBody^ MultiBodyLinkCollider::MultiBody::get()
{
	return _multiBody;
}
void MultiBodyLinkCollider::MultiBody::set(BulletSharp::MultiBody^ value)
{
	Native->m_multiBody = value->_native;
	_multiBody = value;
}

#endif
