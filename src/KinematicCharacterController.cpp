#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "BroadphaseProxy.h"
#include "ConvexShape.h"
#include "Dispatcher.h"
#include "GhostObject.h"
#include "KinematicCharacterController.h"
#include "OverlappingPairCache.h"

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject,
	ConvexShape^ convexShape, btScalar stepHeight, int upAxis)
{
	_addedMargin = btScalar(0.02);
	_convexShape = convexShape;
	_fallSpeed = 55.0; // Terminal velocity of a sky diver in m/s.
	_ghostObject = ghostObject;
	_gravity = btScalar(9.8 * 3); // 3G acceleration.
	_interpolateUp = true;
	_jumpSpeed = btScalar(10.0); // ?
	_stepHeight = stepHeight;
	_upAxis = upAxis;
	_useGhostObjectSweepTest = true;
	_useWalkDirection = true;	// use walk direction by default, legacy behavior
	
	MaxSlope = btRadians(45.0);
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject,
	ConvexShape^ convexShape, btScalar stepHeight)
{
	_addedMargin = btScalar(0.02);
	_convexShape = convexShape;
	_fallSpeed = btScalar(55.0); // Terminal velocity of a sky diver in m/s.
	_ghostObject = ghostObject;
	_gravity = btScalar(9.8 * 3); // 3G acceleration.
	_interpolateUp = true;
	_jumpSpeed = btScalar(10.0); // ?
	_stepHeight = stepHeight;
	_upAxis = 1;
	_useGhostObjectSweepTest = true;
	_useWalkDirection = true;	// use walk direction by default, legacy behavior
	
	MaxSlope = btRadians(45.0);
}

Vector3 KinematicCharacterController::ComputeReflectionDirection(Vector3% direction, Vector3% normal)
{
	return direction - normal * (Vector3_Dot(direction, normal) * 2);
}

Vector3 KinematicCharacterController::GetUpAxisDirection(int upAxis)
{
	if (upAxis == 0) {
		return Vector3(1,0,0);
	} else if (upAxis == 1) {
		return Vector3(0,1,0);
	} else {
		return Vector3(0,0,1);
	}
}

Vector3 KinematicCharacterController::ParallelComponent(Vector3% direction, Vector3% normal)
{
	return normal * Vector3_Dot(direction, normal);
}

Vector3 KinematicCharacterController::PerpindicularComponent(Vector3% direction, Vector3% normal)
{
	return direction - ParallelComponent(direction, normal);
}

#pragma managed(push, off)
bool btKinematicCharacterController_recoverFromPenetration(btCollisionWorld* collisionWorld, btConvexShape*	m_convexShape,
	btPairCachingGhostObject* m_ghostObject, btVector3* m_currentPosition, btVector3* m_touchingNormal)
{
	// Here we must refresh the overlapping paircache as the penetrating movement itself or the
	// previous recovery iteration might have used setWorldTransform and pushed us into an object
	// that is not in the previous cache contents from the last timestep, as will happen if we
	// are pushed into a new AABB overlap. Unhandled this means the next convex sweep gets stuck.
	//
	// Do this by calling the broadphase's setAabb with the moved AABB, this will update the broadphase
	// paircache and the ghostobject's internal paircache at the same time.    /BW

	btVector3 minAabb, maxAabb;
	m_convexShape->getAabb(m_ghostObject->getWorldTransform(), minAabb, maxAabb);
	collisionWorld->getBroadphase()->setAabb(m_ghostObject->getBroadphaseHandle(), 
						 minAabb, 
						 maxAabb, 
						 collisionWorld->getDispatcher());
						 
	bool penetration = false;

	collisionWorld->getDispatcher()->dispatchAllCollisionPairs(m_ghostObject->getOverlappingPairCache(), collisionWorld->getDispatchInfo(), collisionWorld->getDispatcher());

	*m_currentPosition = m_ghostObject->getWorldTransform().getOrigin();
	
	btManifoldArray m_manifoldArray;
	btScalar maxPen = btScalar(0.0);
	for (int i = 0; i < m_ghostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
	{
		m_manifoldArray.resize(0);

		btBroadphasePair* collisionPair = &m_ghostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

		btCollisionObject* obj0 = static_cast<btCollisionObject*>(collisionPair->m_pProxy0->m_clientObject);
                btCollisionObject* obj1 = static_cast<btCollisionObject*>(collisionPair->m_pProxy1->m_clientObject);

		if ((obj0 && !obj0->hasContactResponse()) || (obj1 && !obj1->hasContactResponse()))
			continue;
		
		if (collisionPair->m_algorithm)
			collisionPair->m_algorithm->getAllContactManifolds(m_manifoldArray);

		
		for (int j=0; j<m_manifoldArray.size(); j++)
		{
			btPersistentManifold* manifold = m_manifoldArray[j];
			btScalar directionSign = manifold->getBody0() == m_ghostObject ? btScalar(-1.0) : btScalar(1.0);
			for (int p=0;p<manifold->getNumContacts();p++)
			{
				const btManifoldPoint&pt = manifold->getContactPoint(p);

				btScalar dist = pt.getDistance();

				if (dist < 0.0)
				{
					if (dist < maxPen)
					{
						maxPen = dist;
						*m_touchingNormal = pt.m_normalWorldOnB * directionSign;//??

					}
					*m_currentPosition += pt.m_normalWorldOnB * directionSign * dist * btScalar(0.2);
					penetration = true;
				} else {
					//printf("touching %f\n", dist);
				}
			}
			
			//manifold->clearManifold();
		}
	}
	btTransform newTrans = m_ghostObject->getWorldTransform();
	newTrans.setOrigin(*m_currentPosition);
	m_ghostObject->setWorldTransform(newTrans);
//	printf("m_touchingNormal = %f,%f,%f\n",m_touchingNormal[0],m_touchingNormal[1],m_touchingNormal[2]);
	return penetration;
}
#pragma managed(pop)

bool KinematicCharacterController::RecoverFromPenetration(CollisionWorld^ collisionWorld)
{
	btVector3* currentPositionTemp = ALIGNED_NEW(btVector3);
	btVector3* touchingNormalTemp = ALIGNED_NEW(btVector3);
	bool ret = btKinematicCharacterController_recoverFromPenetration(collisionWorld->_native, (btConvexShape*)_convexShape->_native,
		(btPairCachingGhostObject*)_ghostObject->_native, currentPositionTemp, touchingNormalTemp);
	Math::BtVector3ToVector3(currentPositionTemp, _currentPosition);
	Math::BtVector3ToVector3(touchingNormalTemp, _touchingNormal);
	ALIGNED_FREE(currentPositionTemp);
	ALIGNED_FREE(touchingNormalTemp);
	return ret;
}

btScalar Vector3_DistanceSquared(Vector3% v1, Vector3% v2)
{
	btScalar dx = Vector_X(v1) - Vector_X(v2);
	btScalar dy = Vector_Y(v1) - Vector_Y(v2);
	btScalar dz = Vector_Z(v1) - Vector_Z(v2);
	return dx * dx + dy * dy + dz * dz;
}

void KinematicCharacterController::StepDown(CollisionWorld^ collisionWorld, btScalar dt)
{
	bool runonce = false;
	Vector3 orig_position = _targetPosition;
	
	btScalar downVelocity = (_verticalVelocity < 0 ? -_verticalVelocity : 0) * dt;

	if(downVelocity > 0.0 && downVelocity > _fallSpeed
		&& (_wasOnGround || !_wasJumping))
		downVelocity = _fallSpeed;

	Vector3 step_drop = GetUpAxisDirection(_upAxis) * (_currentStepOffset + downVelocity);
	_targetPosition -= step_drop;

	btTransform* startTemp = ALIGNED_NEW(btTransform);
	btTransform* endTemp = ALIGNED_NEW(btTransform);
	btTransform* endDoubleTemp = ALIGNED_NEW(btTransform);
	startTemp->setIdentity();
	endTemp->setIdentity();
	endDoubleTemp->setIdentity();

	BroadphaseProxy^ ghostProxy = GhostObject->BroadphaseHandle;
	KinematicClosestNotMeConvexResultCallback^ callback = gcnew KinematicClosestNotMeConvexResultCallback(_ghostObject, GetUpAxisDirection(_upAxis), _maxSlopeCosine);
	callback->CollisionFilterGroup = ghostProxy->CollisionFilterGroup;
	callback->CollisionFilterMask = ghostProxy->CollisionFilterMask;

	KinematicClosestNotMeConvexResultCallback^ callback2 = gcnew KinematicClosestNotMeConvexResultCallback(_ghostObject, GetUpAxisDirection(_upAxis), _maxSlopeCosine);
	callback2->CollisionFilterGroup = ghostProxy->CollisionFilterGroup;
	callback2->CollisionFilterMask = ghostProxy->CollisionFilterMask;

	while (true)
	{
		Math::Vector3ToBtVector3(_currentPosition, &startTemp->getOrigin());
		Math::Vector3ToBtVector3(_targetPosition, &endTemp->getOrigin());
		Math::Vector3ToBtVector3(_targetPosition - step_drop, &endDoubleTemp->getOrigin());
		Matrix start = Math::BtTransformToMatrix(startTemp);
		Matrix end = Math::BtTransformToMatrix(endTemp);
		Matrix endDouble = Math::BtTransformToMatrix(endTemp); //set double test for 2x the step drop, to check for a large drop vs small drop

		if (_useGhostObjectSweepTest)
		{
			_ghostObject->ConvexSweepTest(_convexShape, start, end, callback, collisionWorld->DispatchInfo->AllowedCcdPenetration);

			if (!callback->HasHit)
			{
				//test a double fall height, to see if the character should interpolate it's fall (full) or not (partial)
				_ghostObject->ConvexSweepTest(_convexShape, start, endDouble, callback2, collisionWorld->DispatchInfo->AllowedCcdPenetration);
			}
		}
		else
		{
			// this works....
			collisionWorld->ConvexSweepTest(_convexShape, start, end, callback, collisionWorld->DispatchInfo->AllowedCcdPenetration);

			if (!callback->HasHit)
			{
				//test a double fall height, to see if the character should interpolate it's fall (large) or not (small)
				_ghostObject->ConvexSweepTest(_convexShape, start, endDouble, callback2, collisionWorld->DispatchInfo->AllowedCcdPenetration);
			}
		}

		float downVelocity2 = (_verticalVelocity < 0.0f ? -_verticalVelocity : 0.0f) * dt;
		bool has_hit = false;
		if (_bounceFix)
			has_hit = callback->HasHit || callback2->HasHit;
		else
			has_hit = callback2->HasHit;

		if (downVelocity2 > 0.0f && downVelocity2 < _stepHeight && has_hit && runonce == false
		&& (_wasOnGround || !_wasJumping))
		{
			//redo the velocity calculation when falling a small amount, for fast stairs motion
			//for larger falls, use the smoother/slower interpolated movement by not touching the target position

			_targetPosition = orig_position;
			downVelocity = _stepHeight;

			Vector3 step_drop2 = GetUpAxisDirection(_upAxis) * (_currentStepOffset + downVelocity);
			_targetPosition -= step_drop2;
			runonce = true;
			continue; //re-run previous tests
		}
		break;
	}
	ALIGNED_FREE(startTemp);
	ALIGNED_FREE(endTemp);
	ALIGNED_FREE(endDoubleTemp);

	if (callback->HasHit || runonce)
	{
		// we dropped a fraction of the height -> hit floor
		btScalar fraction = (Vector_Y(_currentPosition) - Vector_Y(callback->HitPointWorld)) / 2;

		//printf("hitpoint: %g - pos %g\n", callback.m_hitPointWorld.getY(), m_currentPosition.getY());

		btScalar rt;
		if (_bounceFix && !_fullDrop)
		{
			//due to errors in the closestHitFraction variable when used with large polygons, calculate the hit fraction manually
			rt = fraction;
		}
		else
		{
			rt = callback->ClosestHitFraction;
		}

		// Lerp3
		btScalar s = 1 - rt;
		Vector_SetX(_currentPosition, s * Vector_X(_currentPosition) + rt * Vector_X(_targetPosition));
		Vector_SetY(_currentPosition, s * Vector_Y(_currentPosition) + rt * Vector_Y(_targetPosition));
		Vector_SetZ(_currentPosition, s * Vector_Z(_currentPosition) + rt * Vector_Z(_targetPosition));

		_fullDrop = false;

		_verticalVelocity = 0.0;
		_verticalOffset = 0.0;
		_wasJumping = false;
	} else {
		// we dropped the full height
		_fullDrop = true;

		if (_bounceFix)
		{
			downVelocity = (_verticalVelocity < 0? -_verticalVelocity : 0) * dt;
			if (downVelocity > _fallSpeed && (_wasOnGround || !_wasJumping))
			{
				_targetPosition += step_drop; //undo previous target change
				downVelocity = _fallSpeed;
				step_drop = GetUpAxisDirection(_upAxis) * (_currentStepOffset + downVelocity);
				_targetPosition -= step_drop;
			}
		}
		//printf("full drop - %g, %g\n", m_currentPosition.getY(), m_targetPosition.getY());

		_currentPosition = _targetPosition;
	}

	delete callback;
	delete callback2;
}

void KinematicCharacterController::StepForwardAndStrafe(CollisionWorld^ collisionWorld, Vector3% walkMove)
{
	_targetPosition = _currentPosition + walkMove;

	btScalar fraction = 1.0;
	btScalar distance2 = Vector3_DistanceSquared(_currentPosition, _targetPosition);
	int maxIter = 10;

	btTransform* startTemp = ALIGNED_NEW(btTransform);
	btTransform* endTemp = ALIGNED_NEW(btTransform);
	startTemp->setIdentity();
	endTemp->setIdentity();

	while (fraction > btScalar(0.01) && maxIter-- > 0)
	{
		Math::Vector3ToBtVector3(_currentPosition, &startTemp->getOrigin());
		Math::Vector3ToBtVector3(_targetPosition, &endTemp->getOrigin());
		Matrix start = Math::BtTransformToMatrix(startTemp);
		Matrix end = Math::BtTransformToMatrix(endTemp);

		KinematicClosestNotMeConvexResultCallback^ callback = gcnew KinematicClosestNotMeConvexResultCallback(_ghostObject, GetUpAxisDirection(_upAxis), 0);
		BroadphaseProxy^ ghostProxy = GhostObject->BroadphaseHandle;
		callback->CollisionFilterGroup = ghostProxy->CollisionFilterGroup;
		callback->CollisionFilterMask = ghostProxy->CollisionFilterMask;

		btScalar margin = _convexShape->Margin;
		_convexShape->Margin = margin + _addedMargin;

		if (_useGhostObjectSweepTest)
		{
			_ghostObject->ConvexSweepTest(_convexShape, start, end, callback, collisionWorld->DispatchInfo->AllowedCcdPenetration);
		}
		else
		{
			collisionWorld->ConvexSweepTest(_convexShape, start, end, callback);
		}

		_convexShape->Margin = margin;

		fraction -= callback->ClosestHitFraction;

		if (callback->HasHit)
		{
			UpdateTargetPositionBasedOnCollision(callback->HitNormalWorld);
			Vector3 currentDir = _targetPosition - _currentPosition;
			distance2 = Vector3_DistanceSquared(_targetPosition, _currentPosition);
			if (distance2 > SIMD_EPSILON)
			{
				Vector3_Normalize(currentDir);
				// See Quake2: "If velocity is against original velocity, stop ead to avoid tiny oscilations in sloping corners."
				if (Vector3_Dot(currentDir, _normalizedDirection) <= 0)
				{
					break;
				}
			} else {
				//printf("currentDir: don't normalize a zero vector\n");
				break;
			}
		} else {
			_currentPosition = _targetPosition;
		}

		delete callback;
	}

	ALIGNED_FREE(startTemp);
	ALIGNED_FREE(endTemp);
}

void KinematicCharacterController::StepUp(CollisionWorld^ world)
{
	_targetPosition = _currentPosition + GetUpAxisDirection(_upAxis) * (_stepHeight + (_verticalOffset > 0 ? _verticalOffset : 0));

	btTransform* startTemp = ALIGNED_NEW(btTransform);
	btTransform* endTemp = ALIGNED_NEW(btTransform);
	startTemp->setIdentity();
	endTemp->setIdentity();
	Math::Vector3ToBtVector3(_currentPosition + GetUpAxisDirection(_upAxis) * (_convexShape->Margin + _addedMargin), &startTemp->getOrigin());
	Math::Vector3ToBtVector3(_targetPosition, &endTemp->getOrigin());
	Matrix start = Math::BtTransformToMatrix(startTemp);
	Matrix end = Math::BtTransformToMatrix(endTemp);
	ALIGNED_FREE(startTemp);
	ALIGNED_FREE(endTemp);

	KinematicClosestNotMeConvexResultCallback^ callback = gcnew KinematicClosestNotMeConvexResultCallback(_ghostObject, -GetUpAxisDirection(_upAxis), btScalar(0.7071));
	BroadphaseProxy^ ghostProxy = GhostObject->BroadphaseHandle;
	callback->CollisionFilterGroup = ghostProxy->CollisionFilterGroup;
	callback->CollisionFilterMask = ghostProxy->CollisionFilterMask;

	if (_useGhostObjectSweepTest)
	{
		_ghostObject->ConvexSweepTest(_convexShape, start, end, callback, world->DispatchInfo->AllowedCcdPenetration);
	}
	else
	{
		world->ConvexSweepTest(_convexShape, start, end, callback);
	}

	if (callback->HasHit)
	{
		// Only modify the position if the hit was a slope and not a wall or ceiling.
		if (Vector3_Dot(callback->HitNormalWorld, GetUpAxisDirection(_upAxis)) > 0)
		{
			// we moved up only a fraction of the step height
			_currentStepOffset = _stepHeight * callback->ClosestHitFraction;
			if (_interpolateUp) {
				// Lerp3
				btScalar rt = callback->ClosestHitFraction;
				btScalar s = 1 - rt;
				Vector_SetX(_currentPosition, s * Vector_X(_currentPosition) + rt * Vector_X(_targetPosition));
				Vector_SetY(_currentPosition, s * Vector_Y(_currentPosition) + rt * Vector_Y(_targetPosition));
				Vector_SetZ(_currentPosition, s * Vector_Z(_currentPosition) + rt * Vector_Z(_targetPosition));
			} else {
				_currentPosition = _targetPosition;
			}
		}
		_verticalVelocity = 0;
		_verticalOffset = 0;
	} else {
		_currentStepOffset = _stepHeight;
		_currentPosition = _targetPosition;
	}

	delete callback;
}

void KinematicCharacterController::UpdateTargetPositionBasedOnCollision(Vector3 hitNormal)
{
	btScalar normalMag = 1;

	Vector3 movementDirection = _targetPosition - _currentPosition;
	btScalar movementLength = Vector3_Length(movementDirection);
	if (movementLength>SIMD_EPSILON)
	{
		Vector3_Normalize(movementDirection);

		Vector3 reflectDir = ComputeReflectionDirection(movementDirection, hitNormal);
		Vector3_Normalize(reflectDir);

		//Vector3 parallelDir = ParallelComponent(reflectDir, hitNormal);
		Vector3 perpindicularDir = PerpindicularComponent(reflectDir, hitNormal);

		_targetPosition = _currentPosition;
		if (0)//tangentMag != 0.0)
		{
			//Vector3 parComponent = Vector3_Scale(parallelDir, tangentMag * movementLength);
			//Console::WriteLine(parComponent);
			//_targetPosition += parComponent;
		}

		if (normalMag != 0.0)
		{
			Vector3 perpComponent = perpindicularDir * (normalMag * movementLength);
			//Console::WriteLine(perpComponent);
			_targetPosition += perpComponent;
		}
	}
}

#ifndef DISABLE_DEBUGDRAW
void KinematicCharacterController::DebugDraw(IDebugDraw^ debugDrawer)
{
}
#endif

void KinematicCharacterController::Jump()
{
	if (!CanJump)
		return;

	_verticalVelocity = _jumpSpeed;
	_wasJumping = true;
/*
	//currently no jumping.
	Matrix xform = _rigidBody->MotionState->WorldTransform;
	Vector3 up = xform->Basis[1];
	Vector3_Normalize(up);
	btScalar magnitude = (btScalar(1.0)/_rigidBody->InvMass) * btScalar(8.0);
	_rigidBody->ApplyCentralImpulse(up * magnitude);
*/
}

void KinematicCharacterController::PlayerStep(CollisionWorld^ collisionWorld, btScalar dt)
{
	if (!_useWalkDirection && (_velocityTimeInterval <= 0.0 || Vector3_IsFuzzyZero(_walkDirection))) {
		return;		// no motion
	}

	_wasOnGround = OnGround;

	// Update fall velocity.
	_verticalVelocity -= _gravity * dt;
	if(_verticalVelocity > 0.0 && _verticalVelocity > _jumpSpeed)
	{
		_verticalVelocity = _jumpSpeed;
	}
	if(_verticalVelocity < 0.0 && btFabs(_verticalVelocity) > btFabs(_fallSpeed))
	{
		_verticalVelocity = -btFabs(_fallSpeed);
	}
	_verticalOffset = _verticalVelocity * dt;

	btTransform* xformTemp = ALIGNED_NEW(btTransform);
	xformTemp = &_ghostObject->_native->getWorldTransform();

	StepUp(collisionWorld);
	if (_useWalkDirection) {
		StepForwardAndStrafe(collisionWorld, _walkDirection);
	} else {
		// still have some time left for moving!
		btScalar dtMoving = (dt < _velocityTimeInterval) ? dt : _velocityTimeInterval;
		_velocityTimeInterval -= dt;

		// how far will we move while we are moving?
		Vector3 move = _walkDirection * dtMoving;

		StepForwardAndStrafe(collisionWorld, move);
	}
	StepDown(collisionWorld, dt);

	xformTemp->getOrigin().setX(Vector_X(_currentPosition));
	xformTemp->getOrigin().setY(Vector_Y(_currentPosition));
	xformTemp->getOrigin().setZ(Vector_Z(_currentPosition));
    _ghostObject->_native->setWorldTransform(*xformTemp);
	ALIGNED_FREE(xformTemp);
}

void KinematicCharacterController::PreStep(CollisionWorld^ collisionWorld)
{
	int numPenetrationLoops = 0;
	_touchingContact = false;
	while (RecoverFromPenetration(collisionWorld))
	{
		numPenetrationLoops++;
		_touchingContact = true;
		if (numPenetrationLoops > 4)
		{
			//Console::WriteLine("character could not recover from penetration = {0}", numPenetrationLoops);
			break;
		}
	}

	_currentPosition = Matrix_Origin(_ghostObject->WorldTransform);
	_targetPosition = _currentPosition;
}

void KinematicCharacterController::Reset(CollisionWorld^ collisionWorld)
{
	_verticalVelocity = 0.0;
	_verticalOffset = 0.0;
	_wasOnGround = false;
	_wasJumping = false;
	_walkDirection = Vector3_Zero;
	_velocityTimeInterval = 0.0;

	//clear pair cache
	HashedOverlappingPairCache^ cache = _ghostObject->OverlappingPairCache;
	AlignedBroadphasePairArray^ pairArray = cache->OverlappingPairArray;
	while (pairArray->Count > 0)
	{
		cache->RemoveOverlappingPair(pairArray[0]->Proxy0, pairArray[0]->Proxy1, collisionWorld->Dispatcher);
	}
}

void KinematicCharacterController::SetFallSpeed(btScalar fallSpeed)
{
	_fallSpeed = fallSpeed;
}

void KinematicCharacterController::SetJumpSpeed(btScalar jumpSpeed)
{
	_jumpSpeed = jumpSpeed;
}

void KinematicCharacterController::SetMaxJumpHeight(btScalar maxJumpHeight)
{
	_maxJumpHeight = maxJumpHeight;
}

void KinematicCharacterController::SetUpAxis(int axis)
{
	if (axis < 0)
		axis = 0;
	if (axis > 2)
		axis = 2;
	_upAxis = axis;
}

void KinematicCharacterController::SetUpInterpolate(bool value)
{
	_interpolateUp = value;
}

void KinematicCharacterController::SetUseGhostSweepTest(bool useGhostObjectSweepTest)
{
	_useGhostObjectSweepTest = useGhostObjectSweepTest;
}

void KinematicCharacterController::SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval)
{
	_useWalkDirection = false;
	_walkDirection = velocity;
	_normalizedDirection = _walkDirection;
	Vector3_Normalize(_normalizedDirection);
	_velocityTimeInterval += timeInterval;
}

void KinematicCharacterController::SetWalkDirection(Vector3 walkDirection)
{
	_walkDirection = walkDirection;
}

void KinematicCharacterController::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTime)
{
	PreStep(collisionWorld);
	PlayerStep(collisionWorld, deltaTime);
}

#pragma managed(push, off)
void KinematicCharacterController_Warp(btGhostObject* ghostObject, btVector3* origin)
{
	btTransform xform;
	xform.setIdentity();
	xform.setOrigin(*origin);
	ghostObject->setWorldTransform(xform);
}
#pragma managed(pop)
void KinematicCharacterController::Warp(Vector3 origin)
{
	VECTOR3_CONV(origin);
	KinematicCharacterController_Warp((btGhostObject*)_ghostObject->_native, VECTOR3_PTR(origin));
	VECTOR3_DEL(origin);
}

bool KinematicCharacterController::CanJump::get()
{
	return true;
}

PairCachingGhostObject^ KinematicCharacterController::GhostObject::get()
{
	return _ghostObject;
}

btScalar KinematicCharacterController::Gravity::get()
{
	return _gravity;
}
void KinematicCharacterController::Gravity::set(btScalar gravity)
{
	_gravity = gravity;
}

btScalar KinematicCharacterController::MaxSlope::get()
{
	return _maxSlopeRadians;
}
void KinematicCharacterController::MaxSlope::set(btScalar slopeRadians)
{
	_maxSlopeRadians = slopeRadians;
	_maxSlopeCosine = btCos(slopeRadians);
}

bool KinematicCharacterController::OnGround::get()
{
	return _verticalVelocity == 0.0 && _verticalOffset == 0.0;
}


KinematicClosestNotMeConvexResultCallback::KinematicClosestNotMeConvexResultCallback(CollisionObject^ me, Vector3 up, btScalar minSlopeDot)
	: ClosestConvexResultCallback()
{
	_me = me;
	_up = up;
	_minSlopeDot = minSlopeDot;
}

#pragma managed(push, off)
void KinematicClosestNotMeConvexResultCallback_AddSingleResult_Transform(btTransform* worldTransform,
	btVector3* hitNormalLocal, btVector3* hitNormalWorld)
{
	*hitNormalWorld = worldTransform->getBasis() * *hitNormalLocal;
}
#pragma managed(pop)

btScalar KinematicClosestNotMeConvexResultCallback::AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace)
{
	if (convexResult->HitCollisionObject == _me)
	{
		return 1;
	}

	if (!convexResult->HitCollisionObject->HasContactResponse)
	{
		return 1;
	}

	Vector3 hitNormalWorld;
    if (normalInWorldSpace)
    {
        hitNormalWorld = convexResult->HitNormalLocal;
    }
    else
    {
        // need to transform normal into worldspace
		btTransform* worldTransformTemp = Math::MatrixToBtTransform(convexResult->HitCollisionObject->WorldTransform);
		btVector3* hitNormalLocalTemp = Math::Vector3ToBtVector3(convexResult->HitNormalLocal);
		btVector3* hitNormalWorldTemp = ALIGNED_NEW(btVector3);
		KinematicClosestNotMeConvexResultCallback_AddSingleResult_Transform(worldTransformTemp, hitNormalLocalTemp, hitNormalWorldTemp);
		Math::BtVector3ToVector3(hitNormalWorldTemp, hitNormalWorld);
		ALIGNED_FREE(worldTransformTemp);
		ALIGNED_FREE(hitNormalLocalTemp);
		ALIGNED_FREE(hitNormalWorldTemp);
    }

    float dotUp = Vector3_Dot(_up, hitNormalWorld);
    if (dotUp < _minSlopeDot)
    {
        return 1;
    }

    return ClosestConvexResultCallback::AddSingleResult(convexResult, normalInWorldSpace);
}

#endif
