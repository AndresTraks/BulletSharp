using BulletSharp;
using System.Windows.Forms;

namespace DemoFramework
{
    public sealed class BodyPicker
    {
        private Demo _demo;

        private RigidBody _pickedBody;
        private TypedConstraint _rigidBodyPickConstraint;
        private MultiBodyPoint2Point _multiBodyPickConstraint;
        private bool _prevCanSleep;
        private float _oldPickingDist;

        public BodyPicker(Demo demo)
        {
            _demo = demo;
        }

        public void Update()
        {
            var input = _demo.Input;

            if ((input.MousePressed & MouseButtons.Right) != 0)
            {
                PickBody();
            }
            else if (input.MouseReleased == MouseButtons.Right)
            {
                RemovePickingConstraint();
            }

            if (input.MouseDown == MouseButtons.Right)
            {
                MovePickedBody();
            }
        }

        public void RemovePickingConstraint()
        {
            if (_rigidBodyPickConstraint != null)
            {
                _demo.World.RemoveConstraint(_rigidBodyPickConstraint);
                _rigidBodyPickConstraint.Dispose();
                _rigidBodyPickConstraint = null;
                _pickedBody.ForceActivationState(ActivationState.ActiveTag);
                _pickedBody.DeactivationTime = 0;
                _pickedBody = null;
            }

            if (_multiBodyPickConstraint != null)
            {
                _multiBodyPickConstraint.MultiBodyA.CanSleep = _prevCanSleep;
                (_demo.World as MultiBodyDynamicsWorld).RemoveMultiBodyConstraint(_multiBodyPickConstraint);
                _multiBodyPickConstraint.Dispose();
                _multiBodyPickConstraint = null;
            }
        }

        private void PickBody()
        {
            Vector3 rayFrom = _demo.Freelook.Eye;
            Vector3 rayTo = _demo.GetCameraRayTo();

            DynamicsWorld world = _demo.World;

            using (var rayCallback = new ClosestRayResultCallback(ref rayFrom, ref rayTo))
            {
                world.RayTestRef(ref rayFrom, ref rayTo, rayCallback);
                if (rayCallback.HasHit)
                {
                    Vector3 pickPosition = rayCallback.HitPointWorld;
                    var body = rayCallback.CollisionObject as RigidBody;
                    if (body != null)
                    {
                        PickRigidBody(body, ref pickPosition);
                    }
                    else
                    {
                        var collider = rayCallback.CollisionObject as MultiBodyLinkCollider;
                        if (collider != null)
                        {
                            PickMultiBody(collider, ref pickPosition);
                        }
                    }
                    _oldPickingDist = (pickPosition - rayFrom).Length;
                }
            }
        }

        private void PickRigidBody(RigidBody body, ref Vector3 pickPosition)
        {
            if (body.IsStaticObject || body.IsKinematicObject)
            {
                return;
            }

            _pickedBody = body;
            _pickedBody.ActivationState = ActivationState.DisableDeactivation;

            DynamicsWorld world = _demo.World;

            Vector3 localPivot = Vector3.TransformCoordinate(pickPosition, Matrix.Invert(body.CenterOfMassTransform));

            if (_demo.Input.KeysDown.Contains(Keys.ShiftKey))
            {
                var dof6 = new Generic6DofConstraint(body, Matrix.Translation(localPivot), false)
                {
                    LinearLowerLimit = Vector3.Zero,
                    LinearUpperLimit = Vector3.Zero,
                    AngularLowerLimit = Vector3.Zero,
                    AngularUpperLimit = Vector3.Zero
                };

                world.AddConstraint(dof6);
                _rigidBodyPickConstraint = dof6;

                dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 0);
                dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 1);
                dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 2);
                dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 3);
                dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 4);
                dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 5);

                dof6.SetParam(ConstraintParam.StopErp, 0.1f, 0);
                dof6.SetParam(ConstraintParam.StopErp, 0.1f, 1);
                dof6.SetParam(ConstraintParam.StopErp, 0.1f, 2);
                dof6.SetParam(ConstraintParam.StopErp, 0.1f, 3);
                dof6.SetParam(ConstraintParam.StopErp, 0.1f, 4);
                dof6.SetParam(ConstraintParam.StopErp, 0.1f, 5);
            }
            else
            {
                var p2p = new Point2PointConstraint(body, localPivot);
                world.AddConstraint(p2p);
                _rigidBodyPickConstraint = p2p;
                p2p.Setting.ImpulseClamp = 30;
                //very weak constraint for picking
                p2p.Setting.Tau = 0.001f;
                /*
                p2p.SetParam(ConstraintParams.Cfm, 0.8f, 0);
                p2p.SetParam(ConstraintParams.Cfm, 0.8f, 1);
                p2p.SetParam(ConstraintParams.Cfm, 0.8f, 2);
                p2p.SetParam(ConstraintParams.Erp, 0.1f, 0);
                p2p.SetParam(ConstraintParams.Erp, 0.1f, 1);
                p2p.SetParam(ConstraintParams.Erp, 0.1f, 2);
                */
            }
        }

        private void PickMultiBody(MultiBodyLinkCollider collider, ref Vector3 pickPosition)
        {
            MultiBody multiBody = collider.MultiBody;
            if (multiBody == null)
            {
                return;
            }

            _prevCanSleep = multiBody.CanSleep;
            multiBody.CanSleep = false;
            Vector3 pivotInA = multiBody.WorldPosToLocal(collider.Link, pickPosition);

            var p2p = new MultiBodyPoint2Point(multiBody, collider.Link, null, pivotInA, pickPosition)
            {
                MaxAppliedImpulse = 2
            };

            var world = _demo.World as MultiBodyDynamicsWorld;
            world.AddMultiBodyConstraint(p2p);
            _multiBodyPickConstraint = p2p;
        }

        private void MovePickedBody()
        {
            if (_rigidBodyPickConstraint != null)
            {
                Vector3 rayFrom = _demo.Freelook.Eye;
                Vector3 newRayTo = _demo.GetCameraRayTo();

                //keep it at the same picking distance
                Vector3 direction = newRayTo - rayFrom;
                direction.Normalize();
                direction *= _oldPickingDist;

                if (_rigidBodyPickConstraint.ConstraintType == TypedConstraintType.D6)
                {
                    var dof6 = _rigidBodyPickConstraint as Generic6DofConstraint;

                    //keep it at the same picking distance
                    Matrix tempFrameOffsetA = dof6.FrameOffsetA;
                    tempFrameOffsetA.Origin = rayFrom + direction;
                    dof6.SetFrames(tempFrameOffsetA, dof6.FrameOffsetB);
                }
                else
                {
                    var p2p = _rigidBodyPickConstraint as Point2PointConstraint;

                    //keep it at the same picking distance
                    p2p.PivotInB = rayFrom + direction;
                }
            }
            else if (_multiBodyPickConstraint != null)
            {
                Vector3 rayFrom = _demo.Freelook.Eye;
                Vector3 newRayTo = _demo.GetCameraRayTo();

                Vector3 dir = (newRayTo - rayFrom);
                dir.Normalize();
                dir *= _oldPickingDist;
                _multiBodyPickConstraint.PivotInB = rayFrom + dir;
            }
        }
    }
}
