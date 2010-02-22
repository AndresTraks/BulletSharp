#pragma once

namespace BulletSharp
{
	public ref class TypedConstraint abstract
	{
		private:
			btTypedConstraint* _typedConstraint;

		protected:
			TypedConstraint(btTypedConstraint* typedConstraint);

		internal:
			property btTypedConstraint* UnmanagedPointer
			{
				virtual btTypedConstraint* get();
				void set(btTypedConstraint* value);
			}
	};
};
