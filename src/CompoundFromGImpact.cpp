#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include <BulletCollision/Gimpact/btCompoundFromGimpact.h>
#include "CompoundFromGImpact.h"
#include "CompoundShape.h"
#include "GImpactShape.h"

CompoundShape^ CompoundFromGImpact::Create(GImpactMeshShape^ gImpactMesh, btScalar depth)
{
	return gcnew CompoundShape(btCreateCompoundFromGimpactShape((btGImpactMeshShape*)gImpactMesh->_native, depth));
}

#endif
