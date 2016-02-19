#include "StdAfx.h"

#include "Collections.h"
#include "CompoundShape.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif

CompoundShapeChild::CompoundShapeChild(btCompoundShapeChild* native, CollisionShape^ shape)
{
	_native = native;
	_childShape = shape;
}

btScalar CompoundShapeChild::ChildMargin::get()
{
	return _native->m_childMargin;
}
void CompoundShapeChild::ChildMargin::set(btScalar value)
{
	_native->m_childMargin = value;
}

CollisionShape^ CompoundShapeChild::ChildShape::get()
{
	return _childShape;
}
void CompoundShapeChild::ChildShape::set(CollisionShape^ value)
{
	_native->m_childShape = value->_native;
	_childShape = value;
}

BroadphaseNativeType CompoundShapeChild::ChildShapeType::get()
{
	return (BroadphaseNativeType)_native->m_childShapeType;
}
void CompoundShapeChild::ChildShapeType::set(BroadphaseNativeType value)
{
	_native->m_childShapeType = (int)value;
}

#ifndef DISABLE_DBVT
DbvtNode^ CompoundShapeChild::Node::get()
{
	if (_native->m_node == 0)
		return nullptr;
	return gcnew DbvtNode(_native->m_node);
}
void CompoundShapeChild::Node::set(DbvtNode^ value)
{
	_native->m_node = GetUnmanagedNullable(value);
}
#endif

Matrix CompoundShapeChild::Transform::get()
{
	return Math::BtTransformToMatrix(&_native->m_transform);
}
void CompoundShapeChild::Transform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_transform);
}


#define Native static_cast<btCompoundShape*>(_native)

CompoundShape::CompoundShape(btCompoundShape* native)
	: CollisionShape(native)
{
	_childList = gcnew CompoundShapeChildArray(Native);
}

CompoundShape::CompoundShape(bool enableDynamicAabbTree, int initialChildCapacity)
	: CollisionShape(new btCompoundShape(enableDynamicAabbTree, initialChildCapacity))
{
	_childList = gcnew CompoundShapeChildArray(Native);
}

CompoundShape::CompoundShape(bool enableDynamicAabbTree)
	: CollisionShape(new btCompoundShape(enableDynamicAabbTree))
{
	_childList = gcnew CompoundShapeChildArray(Native);
}

CompoundShape::CompoundShape()
	: CollisionShape(new btCompoundShape())
{
	_childList = gcnew CompoundShapeChildArray(Native);
}

void CompoundShape::AddChildShapeRef(Matrix% localTransform, CollisionShape^ shape)
{
	_childList->AddChildShape(localTransform, shape);
}

void CompoundShape::AddChildShape(Matrix localTransform, CollisionShape^ shape)
{
	_childList->AddChildShape(localTransform, shape);
}

void CompoundShape::CalculatePrincipalAxisTransform(array<btScalar>^ masses, Matrix% principal,
	[Out] Vector3% inertia)
{
	pin_ptr<btScalar> massesPtr = &masses[0];
	btTransform* principalTemp = Math::MatrixToBtTransform(principal);
	btVector3* inertiaTemp = ALIGNED_NEW(btVector3);
	
	Native->calculatePrincipalAxisTransform(massesPtr, *principalTemp, *inertiaTemp);
	Math::BtTransformToMatrix(principalTemp, principal);
	Math::BtVector3ToVector3(inertiaTemp, inertia);
	
	ALIGNED_FREE(principalTemp);
	ALIGNED_FREE(inertiaTemp);
}

void CompoundShape::CreateAabbTreeFromChildren()
{
	Native->createAabbTreeFromChildren();
}

CollisionShape^ CompoundShape::GetChildShape(int index)
{
	return CollisionShape::GetManaged(Native->getChildShape(index));
}

Matrix CompoundShape::GetChildTransform(int index)
{
	return Math::BtTransformToMatrix(&Native->getChildTransform(index));
}

void CompoundShape::RecalculateLocalAabb()
{
	Native->recalculateLocalAabb();
}

void CompoundShape::RemoveChildShape(CollisionShape^ shape)
{
	_childList->RemoveChildShape(shape);
}

void CompoundShape::RemoveChildShapeByIndex(int childShapeIndex)
{
	_childList->RemoveChildShapeByIndex(childShapeIndex);
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform,
	bool shouldRecalculateLocalAabb)
{
	TRANSFORM_CONV(newChildTransform);
	Native->updateChildTransform(childIndex, TRANSFORM_USE(newChildTransform), shouldRecalculateLocalAabb);
	TRANSFORM_DEL(newChildTransform);
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform)
{
	TRANSFORM_CONV(newChildTransform);
	Native->updateChildTransform(childIndex, TRANSFORM_USE(newChildTransform));
	TRANSFORM_DEL(newChildTransform);
}

CollisionShape^ CompoundShape::GetChildShapeByPtr(btCollisionShape* shapePtr, int index)
{
	int numChildren = _childList->Count;
	btCompoundShapeChild* childListPtr = Native->getChildList();

	// index may refer to a child shape or to a child shape inside another child compound shape
	if (index < numChildren && childListPtr[index].m_childShape == shapePtr)
	{
		return _childList[index]->ChildShape;
	}

	for (int i = 0; i < numChildren; i++)
	{
		btCompoundShapeChild* compoundShapeChildPtr = &childListPtr[i];
		if (compoundShapeChildPtr->m_childShape == shapePtr) return _childList[i]->ChildShape;

		if (compoundShapeChildPtr->m_childShapeType == BroadphaseNativeTypes::COMPOUND_SHAPE_PROXYTYPE)
		{
			BulletSharp::CollisionShape^ childShape =
				static_cast<CompoundShape^>(_childList[i]->ChildShape)->GetChildShapeByPtr(shapePtr, index);
			if (childShape) return childShape;
		}
	}

	return nullptr;
}

CompoundShapeChildArray^ CompoundShape::ChildList::get()
{
	return _childList;
}

#ifndef DISABLE_DBVT
Dbvt^ CompoundShape::DynamicAabbTree::get()
{
	return gcnew Dbvt(Native->getDynamicAabbTree(), true);
}
#endif

int CompoundShape::NumChildShapes::get()
{
	return Native->getNumChildShapes();
}

int CompoundShape::UpdateRevision::get()
{
	return Native->getUpdateRevision();
}
