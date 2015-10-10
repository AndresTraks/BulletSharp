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

	[Flags]
	public enum class AnisotropicFrictionFlags
	{
		//None = btCollisionObject::CF_ANISOTROPIC_FRICTION_DISABLED,
		AnisotropicFrictionDisabled = btCollisionObject::CF_ANISOTROPIC_FRICTION_DISABLED,
		AnisotropicFriction = btCollisionObject::CF_ANISOTROPIC_FRICTION,
		AnisotropicRollingFriction = btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION,
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
		Box2DShape = BOX_2D_SHAPE_PROXYTYPE,
		Convex2DShape = CONVEX_2D_SHAPE_PROXYTYPE,
		CustomConvexShape = CUSTOM_CONVEX_SHAPE_TYPE,
		ConcaveShapesStartHere = CONCAVE_SHAPES_START_HERE,
		TriangleMeshShape = TRIANGLE_MESH_SHAPE_PROXYTYPE,
		ScaledTriangleMeshShape = SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE,
		FastConcaveMesh = FAST_CONCAVE_MESH_PROXYTYPE,
		TerrainShape = TERRAIN_SHAPE_PROXYTYPE,
		GImpactShape = GIMPACT_SHAPE_PROXYTYPE, 
		MultiMaterialTriangleMesh = MULTIMATERIAL_TRIANGLE_MESH_PROXYTYPE,
		EmptyShape = EMPTY_SHAPE_PROXYTYPE,
		StaticPlaneShape = STATIC_PLANE_PROXYTYPE,
		CustomConcaveShape = CUSTOM_CONCAVE_SHAPE_TYPE,
		ConcaveShapesEndHere = CONCAVE_SHAPES_END_HERE,
		CompoundShape = COMPOUND_SHAPE_PROXYTYPE,
		SoftBodyShape = SOFTBODY_SHAPE_PROXYTYPE,
		HfFluidShape = HFFLUID_SHAPE_PROXYTYPE,
		HfFluidBuoyantConvexShape = HFFLUID_BUOYANT_CONVEX_SHAPE_PROXYTYPE,
		InvalidShape = INVALID_SHAPE_PROXYTYPE,
		MaxBroadphaseCollisionType = MAX_BROADPHASE_COLLISION_TYPES
	};

#ifndef DISABLE_SOFTBODY
	public enum class BufferType
	{
		Cpu = btVertexBufferDescriptor::CPU_BUFFER,
		DX11 = btVertexBufferDescriptor::DX11_BUFFER,
		OpenGL = btVertexBufferDescriptor::OPENGL_BUFFER
	};
#endif

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

	[Flags]
	public enum class CollisionObjectTypes
	{
		None = 0,
		CollisionObjectType = btCollisionObject::CO_COLLISION_OBJECT,
		RigidBodyType = btCollisionObject::CO_RIGID_BODY,
		GhostObjectType = btCollisionObject::CO_GHOST_OBJECT,
		SoftBodyType = btCollisionObject::CO_SOFT_BODY,
		HfFluidType = btCollisionObject::CO_HF_FLUID,
		UserType = btCollisionObject::CO_USER_TYPE,
		FeatherStoneLinkType = btCollisionObject::CO_FEATHERSTONE_LINK
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

	[Flags]
	public enum class ConstraintSolverType
	{
		SequentialImpulseSolver = BT_SEQUENTIAL_IMPULSE_SOLVER,
		MlcpSolver = BT_MLCP_SOLVER,
		NncgSolver = BT_NNCG_SOLVER
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
		DrawNormals = btIDebugDraw::DBG_DrawNormals,
		DrawFrames = btIDebugDraw::DBG_DrawFrames,
		MaxDebugDrawMode = btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE
	};
#endif

#pragma warning(push)
#pragma warning(disable : 4482)
	[Flags]
	public enum class DispatcherFlags
	{
		None = 0,
		StaticStaticReported = btCollisionDispatcher::DispatcherFlags::CD_STATIC_STATIC_REPORTED,
		UseRelativeContactBreakingThreshold = btCollisionDispatcher::DispatcherFlags::CD_USE_RELATIVE_CONTACT_BREAKING_THRESHOLD,
		DisableContactPoolDynamicAllocation = btCollisionDispatcher::DispatcherFlags::CD_DISABLE_CONTACTPOOL_DYNAMIC_ALLOCATION
	};
#pragma warning(pop)

	public enum class DynamicsWorldType
	{
		Simple = BT_SIMPLE_DYNAMICS_WORLD,
		Discrete = BT_DISCRETE_DYNAMICS_WORLD,
		Continuous = BT_CONTINUOUS_DYNAMICS_WORLD,
		SoftRigid = BT_SOFT_RIGID_DYNAMICS_WORLD,
		Gpu = BT_GPU_DYNAMICS_WORLD
	};

	public enum class PhyScalarType
	{
		Single = PHY_FLOAT,
		Double = PHY_DOUBLE,
		Int32 = PHY_INTEGER,
		Int16 = PHY_SHORT,
		FixedPoint88 = PHY_FIXEDPOINT88,
		Byte = PHY_UCHAR
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		public enum class PSolver
		{
			Linear = btSoftBody::ePSolver::Linear,
			Anchors = btSoftBody::ePSolver::Anchors,
			RigidContacts = btSoftBody::ePSolver::RContacts,
			SoftContacts = btSoftBody::ePSolver::SContacts,
			End = btSoftBody::ePSolver::END
		};
	};
#endif

	[Flags]
	public enum class RigidBodyFlags
	{
		None = 0,
		DisableWorldGravity = BT_DISABLE_WORLD_GRAVITY,
		EnableGyroscopicForceExplicit = BT_ENABLE_GYROSCOPIC_FORCE_EXPLICIT,
		EnableGyroscopicForceImplicitWorld = BT_ENABLE_GYROSCOPIC_FORCE_IMPLICIT_WORLD,
		EnableGyroscopicForceImplicitBody = BT_ENABLE_GYROSCOPIC_FORCE_IMPLICIT_BODY,
		EnableGyroscopicForce = BT_ENABLE_GYROPSCOPIC_FORCE
	};

#ifndef DISABLE_CONSTRAINTS
	public enum class RotateOrder
	{
		XYZ = RO_XYZ,
		XZY = RO_XZY,
		YXZ = RO_YXZ,
		YZX = RO_YZX,
		ZXY = RO_ZXY,
		ZYX = RO_ZYX
	};
#endif

	[Flags]
	public enum class SolverModes
	{
		None = 0,
		RandomizeOrder = SOLVER_RANDMIZE_ORDER,
		FrictionSeparate = SOLVER_FRICTION_SEPARATE,
		UseWarmStarting = SOLVER_USE_WARMSTARTING,
		Use2FrictionDirections = SOLVER_USE_2_FRICTION_DIRECTIONS,
		EnableFrictionDirectionCaching = SOLVER_ENABLE_FRICTION_DIRECTION_CACHING,
		DisableVelocityDependentFrictionDirection = SOLVER_DISABLE_VELOCITY_DEPENDENT_FRICTION_DIRECTION,
		CacheFriendly = SOLVER_CACHE_FRIENDLY,
		Simd = SOLVER_SIMD,
		InterleaveContactAndFrictionConstraints = SOLVER_INTERLEAVE_CONTACT_AND_FRICTION_CONSTRAINTS,
		AllowZeroLengthFrictionDirections = SOLVER_ALLOW_ZERO_LENGTH_FRICTION_DIRECTIONS
	};

#ifndef DISABLE_SOFTBODY
	public enum class SolverType
	{
		Default = btSoftBodySolver::DEFAULT_SOLVER,
		Cpu = btSoftBodySolver::CPU_SOLVER,
		CL = btSoftBodySolver::CL_SOLVER,
		CLSimd = btSoftBodySolver::CL_SIMD_SOLVER,
		DX = btSoftBodySolver::DX_SOLVER,
		DXSimd = btSoftBodySolver::DX_SIMD_SOLVER
	};
#endif

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
		Contact = CONTACT_CONSTRAINT_TYPE,
		D6Spring = D6_SPRING_CONSTRAINT_TYPE,
		Gear = GEAR_CONSTRAINT_TYPE,
		Fixed = FIXED_CONSTRAINT_TYPE,
		D6Spring2 = D6_SPRING_2_CONSTRAINT_TYPE,
		MaxConstraint = MAX_CONSTRAINT_TYPE
	};
#endif

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[Flags]
		public enum class VSolver
		{
			Linear = btSoftBody::eVSolver::Linear,
			End = btSoftBody::eVSolver::END
		};
	};
#endif
};
