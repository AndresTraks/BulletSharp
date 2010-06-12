#pragma once

namespace BulletSharp
{
	public enum class ActivationState
	{
		ActiveTag = ACTIVE_TAG,
		IslandSleeping = ISLAND_SLEEPING,
		WantsDeactivation = WANTS_DEACTIVATION,
		DisableDeactivation = DISABLE_DEACTIVATION,
		DisableSimulation = DISABLE_SIMULATION
	};

	public enum class BroadphaseNativeType
	{
		BoxShape = BOX_SHAPE_PROXYTYPE,
		TriangleShape = TRIANGLE_SHAPE_PROXYTYPE,
		TetrahedralShape = TETRAHEDRAL_SHAPE_PROXYTYPE,
		ConvexTriangleMeshShape = CONVEX_TRIANGLEMESH_SHAPE_PROXYTYPE,
		ConvexHullShape = CONVEX_HULL_SHAPE_PROXYTYPE,
		ConvexPointCloudShape = CONVEX_POINT_CLOUD_SHAPE_PROXYTYPE,
		CustomPolyhedralShape = CUSTOM_POLYHEDRAL_SHAPE_TYPE,
		ImplicitConvexShapesStartHere = IMPLICIT_CONVEX_SHAPES_START_HERE,
		SphereShape = SPHERE_SHAPE_PROXYTYPE,
		MultiSphereShape = MULTI_SPHERE_SHAPE_PROXYTYPE,
		CapsuleShape = CAPSULE_SHAPE_PROXYTYPE,
		ConeShape = CONE_SHAPE_PROXYTYPE,
		ConvexShape = CONVEX_SHAPE_PROXYTYPE,
		CylinderShape = CYLINDER_SHAPE_PROXYTYPE,
		UniformScalingShape = UNIFORM_SCALING_SHAPE_PROXYTYPE,
		MinkowskiSumShape = MINKOWSKI_SUM_SHAPE_PROXYTYPE,
		MinkowskiDifferenceShape = MINKOWSKI_DIFFERENCE_SHAPE_PROXYTYPE,
		Box2dShape = BOX_2D_SHAPE_PROXYTYPE,
		Convex2dShape = CONVEX_2D_SHAPE_PROXYTYPE,
		CustomConvexShape = CUSTOM_CONVEX_SHAPE_TYPE,
		ConcaveShapesStartHere = CONCAVE_SHAPES_START_HERE,
		TriangleMeshShape = TRIANGLE_MESH_SHAPE_PROXYTYPE,
		ScaledTriangleMeshShape = SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE,
		FastConcaveMesh = FAST_CONCAVE_MESH_PROXYTYPE,
		TerrainShape = TERRAIN_SHAPE_PROXYTYPE,
		GImpactShape = GIMPACT_SHAPE_PROXYTYPE, 
		MultiMaterialTriangleMesh = MULTIMATERIAL_TRIANGLE_MESH_PROXYTYPE,
		EmptyShape = EMPTY_SHAPE_PROXYTYPE,
		StaticPlane = STATIC_PLANE_PROXYTYPE,
		CustomConcaveShape = CUSTOM_CONCAVE_SHAPE_TYPE,
		ConcaveShapesEndHere = CONCAVE_SHAPES_END_HERE,
		CompoundShape = COMPOUND_SHAPE_PROXYTYPE,
		SoftBodyShape = SOFTBODY_SHAPE_PROXYTYPE,
		HfFluidShape = HFFLUID_SHAPE_PROXYTYPE,
		HfFluidBuoyantConvexShape = HFFLUID_BUOYANT_CONVEX_SHAPE_PROXYTYPE,
		InvalidShape = INVALID_SHAPE_PROXYTYPE,
		MaxBroadphaseCollisionType = MAX_BROADPHASE_COLLISION_TYPES
	};

	[Flags]
	public enum class CollisionFlags
	{
		None = 0,
		StaticObject = btCollisionObject::CF_STATIC_OBJECT,
		KinematicObject = btCollisionObject::CF_KINEMATIC_OBJECT,
		NoContactResponse = btCollisionObject::CF_NO_CONTACT_RESPONSE,
		CustomMaterialCallback = btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK,
		CharacterObject = btCollisionObject::CF_CHARACTER_OBJECT,
		DisableVisualizeObject = btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
	};

	public enum CollisionObjectType
	{
		CollisionObjectType = btCollisionObject::CO_COLLISION_OBJECT,
		RigidBodyType = btCollisionObject::CO_RIGID_BODY,
		GhostObjectType = btCollisionObject::CO_GHOST_OBJECT,
		SoftBodyType = btCollisionObject::CO_SOFT_BODY,
		HfFluidType = btCollisionObject::CO_HF_FLUID
	};

	[Flags]
	public enum class CollisionFilterGroups
	{
		None = 0,
		DefaultFilter = btBroadphaseProxy::DefaultFilter,
		StaticFilter = btBroadphaseProxy::StaticFilter,
		KinematicFilter = btBroadphaseProxy::KinematicFilter,
		DebrisFilter = btBroadphaseProxy::DebrisFilter,
		SensorTrigger = btBroadphaseProxy::SensorTrigger,
		CharacterFilter = btBroadphaseProxy::CharacterFilter,
		AllFilter = btBroadphaseProxy::AllFilter
	};

	public enum class ConstraintParam
	{
		Erp = BT_CONSTRAINT_ERP,
		StopErp = BT_CONSTRAINT_STOP_ERP,
		Cfm = BT_CONSTRAINT_CFM,
		StopCfm = BT_CONSTRAINT_STOP_CFM
	};

	public enum class ContactManifoldType
	{
		PersistentManifold = BT_PERSISTENT_MANIFOLD_TYPE,
		MaxContactManifold = MAX_CONTACT_MANIFOLD_TYPE
	};

#ifndef DISABLE_DEBUGDRAW
	[Flags]
	public enum class DebugDrawModes
	{
		None = 0,
		NoDebug = btIDebugDraw::DBG_NoDebug,
		DrawWireframe = btIDebugDraw::DBG_DrawWireframe,
		DrawAabb = btIDebugDraw::DBG_DrawAabb,
		DrawFeaturesText = btIDebugDraw::DBG_DrawFeaturesText,
		DrawContactPoints = btIDebugDraw::DBG_DrawContactPoints,
		NoDeactivation = btIDebugDraw::DBG_NoDeactivation,
		NoHelpText = btIDebugDraw::DBG_NoHelpText,
		DrawText = btIDebugDraw::DBG_DrawText,
		ProfileTimings = btIDebugDraw::DBG_ProfileTimings,
		EnableSatComparison = btIDebugDraw::DBG_EnableSatComparison,
		DisableBulletLCP = btIDebugDraw::DBG_DisableBulletLCP,
		EnableCCD = btIDebugDraw::DBG_EnableCCD,
		DrawConstraints = btIDebugDraw::DBG_DrawConstraints,
		DrawConstraintLimits = btIDebugDraw::DBG_DrawConstraintLimits,
		FastWireframe = btIDebugDraw::DBG_FastWireframe,
		MaxDebugDrawMode = btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE
	};
#endif

#pragma warning(push)
#pragma warning(disable : 4482)
	[Flags]
	public enum class DispatcherFlags
	{
		StaticStaticReported = btCollisionDispatcher::DispatcherFlags::CD_STATIC_STATIC_REPORTED,
		UseRelativeContactBreakingThreshold = btCollisionDispatcher::DispatcherFlags::CD_USE_RELATIVE_CONTACT_BREAKING_THRESHOLD
	};
#pragma warning(pop)

	public enum class DynamicsWorldType
	{
		Simple = BT_SIMPLE_DYNAMICS_WORLD,
		Discrete = BT_DISCRETE_DYNAMICS_WORLD,
		Continuous = BT_CONTINUOUS_DYNAMICS_WORLD
	};

	// Mix of ContactManifoldType and TypedConstraintType
	public enum class ObjectType
	{
		PersistentManifold = BT_PERSISTENT_MANIFOLD_TYPE,
		MaxContactManifold = MAX_CONTACT_MANIFOLD_TYPE,
		Point2Point = POINT2POINT_CONSTRAINT_TYPE,
		Hinge = HINGE_CONSTRAINT_TYPE,
		ConeTwist = CONETWIST_CONSTRAINT_TYPE,
		D6 = D6_CONSTRAINT_TYPE,
		Slider = SLIDER_CONSTRAINT_TYPE,
		Contact = CONTACT_CONSTRAINT_TYPE
	};

	public enum class PhyScalarType
	{
		PhyFloat = PHY_FLOAT,
		PhyDouble = PHY_DOUBLE,
		PhyInteger = PHY_INTEGER,
		PhyShort = PHY_SHORT,
		PhyFixedPoint88 = PHY_FIXEDPOINT88,
		PhyUChar = PHY_UCHAR
	};

	[Flags]
	public enum class RigidBodyFlags
	{
		DisableWorldGravity = BT_DISABLE_WORLD_GRAVITY
	};

	[Flags]
	public enum class SolverModes
	{
		None = 0,
		RandomizeOrder = SOLVER_RANDMIZE_ORDER,
		FrictionSeparate = SOLVER_FRICTION_SEPARATE,
		UseWarmStarting = SOLVER_USE_WARMSTARTING,
		UseFrictionWarmStarting = SOLVER_USE_FRICTION_WARMSTARTING,
		Use2FrictionDirections = SOLVER_USE_2_FRICTION_DIRECTIONS,
		EnableFrictionDirectionCaching = SOLVER_ENABLE_FRICTION_DIRECTION_CACHING,
		DisableVelocityDependentFrictionDirection = SOLVER_DISABLE_VELOCITY_DEPENDENT_FRICTION_DIRECTION,
		CacheFriendly = SOLVER_CACHE_FRIENDLY,
		Simd = SOLVER_SIMD,
		Cuda = SOLVER_CUDA
	};

	public enum class TraversalMode
	{
		Recursive = btQuantizedBvh::TRAVERSAL_RECURSIVE,
		Stackless = ::btQuantizedBvh::TRAVERSAL_STACKLESS,
		StacklessCacheFriendly = btQuantizedBvh::TRAVERSAL_STACKLESS_CACHE_FRIENDLY
	};

#ifndef DISABLE_CONSTRAINTS
	public enum class TypedConstraintType
	{
		Point2Point = POINT2POINT_CONSTRAINT_TYPE,
		Hinge = HINGE_CONSTRAINT_TYPE,
		ConeTwist = CONETWIST_CONSTRAINT_TYPE,
		D6 = D6_CONSTRAINT_TYPE,
		Slider = SLIDER_CONSTRAINT_TYPE,
		Contact = CONTACT_CONSTRAINT_TYPE
	};
#endif

};
