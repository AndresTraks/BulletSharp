#pragma once

#include "CollisionShape.h"

namespace BulletSharp
{
	ref class CompoundShapeChildArray;
	ref class Dbvt;
	ref class DbvtNode;

	public ref class CompoundShapeChild
	{
	private:
		btCompoundShapeChild* _child;

	internal:
		CompoundShapeChild(btCompoundShapeChild* compoundShapeChild);

	public:
		CompoundShapeChild();

		property btScalar ChildMargin
		{
			btScalar get();
			void set(btScalar value);
		}

		property CollisionShape^ ChildShape
		{
			CollisionShape^ get();
			void set(CollisionShape^ value);
		}

		property BroadphaseNativeType ChildShapeType
		{
			BroadphaseNativeType get();
			void set(BroadphaseNativeType value);
		}

#ifndef DISABLE_DBVT
		property DbvtNode^ Node
		{
			DbvtNode^ get();
			void set(DbvtNode^ value);
		}
#endif

		property Matrix Transform
		{
			Matrix get();
			void set(Matrix value);
		}

	internal:
		property btCompoundShapeChild* UnmanagedPointer
		{
			btCompoundShapeChild* get();
			void set(btCompoundShapeChild* value);
		}
	};

	public ref class CompoundShape : CollisionShape
	{
	internal:
		CompoundShape(btCompoundShape* compoundShape);

	public:
		CompoundShape();
		CompoundShape(bool enableDynamicAabbTree);

		void AddChildShape(Matrix localTransform, CollisionShape^ shape);
		void CalculatePrincipalAxisTransform(array<btScalar>^ masses, Matrix principal, Vector3 inertia);
		void CreateAabbTreeFromChildren();
		CollisionShape^ GetChildShape(int index);
		Matrix GetChildTransform(int index);
		void RecalculateLocalAabb();
		void RemoveChildShape(CollisionShape^ shape);
		void RemoveChildShapeByIndex(int childShapeindex);
		void UpdateChildTransform(int childIndex, Matrix newChildTransform, bool shouldRecalculateLocalAabb);
		void UpdateChildTransform(int childIndex, Matrix newChildTransform);

		property CompoundShapeChildArray^ ChildList
		{
			CompoundShapeChildArray^ get();
		}

#ifndef DISABLE_DBVT
		property Dbvt^ DynamicAabbTree
		{
			Dbvt^ get();
		}
#endif

		property int NumChildShapes
		{
			int get();
		}

		property int UpdateRevision
		{
			int get();
		}

	internal:
		property btCompoundShape* UnmanagedPointer
		{
			btCompoundShape* get();
		}
	};
};
