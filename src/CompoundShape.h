#pragma once

#include "CollisionShape.h"

UsingFrameworkNamespace

namespace BulletSharp
{
	ref class Dbvt;
	ref class DbvtNode;

	public ref class CompoundShapeChild
	{
	private:
		btCompoundShapeChild* _child;
	
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

		property int ChildShapeType
		{
			int get();
			void set(int value);
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
	};

	public ref class CompoundShape : CollisionShape
	{
	public:
		CompoundShape();
		CompoundShape(bool enableDynamicAabbTree);

		void AddChildShape(Matrix localTransform, CollisionShape^ shape);
		void CalculatePrincipalAxisTransform(array<btScalar>^ masses, Matrix principal, Vector3 inertia);
		//CompoundShapeChild^ GetChildList();
		CollisionShape^ GetChildShape(int index);
		Matrix GetChildTransform(int index);
		void RecalculateLocalAabb();
		void RemoveChildShape(CollisionShape^ shape);
		void RemoveChildShapeByIndex(int childShapeindex);
		void UpdateChildTransform(int childIndex, Matrix newChildTransform);

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
