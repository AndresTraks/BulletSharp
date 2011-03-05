#include "StdAfx.h"

#include "Collections.h"
#include "CompoundShape.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif

CompoundShapeChild::CompoundShapeChild(btCompoundShapeChild* compoundShapeChild)
{
	_child = compoundShapeChild;
}

CompoundShapeChild::CompoundShapeChild()
{
	_child = new btCompoundShapeChild;
}

btScalar CompoundShapeChild::ChildMargin::get()
{
	return _child->m_childMargin;
}
void CompoundShapeChild::ChildMargin::set(btScalar value)
{
	_child->m_childMargin = value;
}

CollisionShape^ CompoundShapeChild::ChildShape::get()
{
	return CollisionShape::Upcast(_child->m_childShape);
}
void CompoundShapeChild::ChildShape::set(CollisionShape^ value)
{
	_child->m_childShape = value->UnmanagedPointer;
}

BroadphaseNativeType CompoundShapeChild::ChildShapeType::get()
{
	return (BroadphaseNativeType)_child->m_childShapeType;
}
void CompoundShapeChild::ChildShapeType::set(BroadphaseNativeType value)
{
	_child->m_childShapeType = (int)value;
}

#ifndef DISABLE_DBVT
DbvtNode^ CompoundShapeChild::Node::get()
{
	if (_child->m_node == 0)
		return nullptr;
	return gcnew DbvtNode(_child->m_node);
}
void CompoundShapeChild::Node::set(DbvtNode^ value)
{
	_child->m_node = GetUnmanagedNullable(value);
}
#endif

Matrix CompoundShapeChild::Transform::get()
{
	return Math::BtTransformToMatrix(&_child->m_transform);
}
void CompoundShapeChild::Transform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_child->m_transform);
}

btCompoundShapeChild* CompoundShapeChild::UnmanagedPointer::get()
{
	return _child;
}
void CompoundShapeChild::UnmanagedPointer::set(btCompoundShapeChild* value)
{
	_child = value;
}


CompoundShape::CompoundShape(btCompoundShape* compoundShape)
: CollisionShape(compoundShape)
{
}

CompoundShape::CompoundShape()
: CollisionShape(new btCompoundShape())
{
}

CompoundShape::CompoundShape(bool enableDynamicAabbTree)
: CollisionShape(new btCompoundShape(enableDynamicAabbTree))
{
}

void CompoundShape::AddChildShape(Matrix localTransform, CollisionShape^ shape)
{
	btTransform* localTransformTemp = Math::MatrixToBtTransform(localTransform);
	UnmanagedPointer->addChildShape(*localTransformTemp, shape->UnmanagedPointer);
	delete localTransformTemp;
}

void CompoundShape::CalculatePrincipalAxisTransform(array<btScalar>^ masses, Matrix principal, Vector3 inertia)
{
	pin_ptr<btScalar> massesPtr = &masses[0];
	btTransform* principalTemp = Math::MatrixToBtTransform(principal);
	btVector3* inertiaTemp = Math::Vector3ToBtVector3(inertia);
	
	UnmanagedPointer->calculatePrincipalAxisTransform(massesPtr, *principalTemp, *inertiaTemp);
	
	delete principalTemp;
	delete inertiaTemp;
}

void CompoundShape::CreateAabbTreeFromChildren()
{
	UnmanagedPointer->createAabbTreeFromChildren();
}

CollisionShape^ CompoundShape::GetChildShape(int index)
{
	return CollisionShape::Upcast(UnmanagedPointer->getChildShape(index));
}

Matrix CompoundShape::GetChildTransform(int index)
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getChildTransform(index));
}

void CompoundShape::RecalculateLocalAabb()
{
	UnmanagedPointer->recalculateLocalAabb();
}

void CompoundShape::RemoveChildShape(CollisionShape^ shape)
{
	UnmanagedPointer->removeChildShape(shape->UnmanagedPointer);
}

void CompoundShape::RemoveChildShapeByIndex(int childShapeindex)
{
	UnmanagedPointer->removeChildShapeByIndex(childShapeindex);
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform, bool shouldRecalculateLocalAabb)
{
	btTransform* newChildTransformTemp = Math::MatrixToBtTransform(newChildTransform);
	UnmanagedPointer->updateChildTransform(childIndex, *newChildTransformTemp, shouldRecalculateLocalAabb);
	delete newChildTransformTemp;
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform)
{
	btTransform* newChildTransformTemp = Math::MatrixToBtTransform(newChildTransform);
	UnmanagedPointer->updateChildTransform(childIndex, *newChildTransformTemp);
	delete newChildTransformTemp;
}

CompoundShapeChildArray^ CompoundShape::ChildList::get()
{
	btCompoundShapeChild* childList = UnmanagedPointer->getChildList();
	if (childList == 0)
		return nullptr;
	return gcnew CompoundShapeChildArray(childList, UnmanagedPointer->getNumChildShapes());
}

#ifndef DISABLE_DBVT
Dbvt^ CompoundShape::DynamicAabbTree::get()
{
	return gcnew Dbvt(UnmanagedPointer->getDynamicAabbTree());
}
#endif

int CompoundShape::NumChildShapes::get()
{
	return UnmanagedPointer->getNumChildShapes();
}

int CompoundShape::UpdateRevision::get()
{
	return UnmanagedPointer->getUpdateRevision();
}

btCompoundShape* CompoundShape::UnmanagedPointer::get()
{
	return (btCompoundShape*)CollisionShape::UnmanagedPointer;
}
