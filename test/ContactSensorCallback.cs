using BulletSharp;

namespace BulletSharpTest
{
    class ContactSensorCallback : ContactResultCallback
    {
        //! Constructor, pass whatever context you want to have available when processing contacts
        /*! You may also want to set CollisionFilterGroups and CollisionFilterMask
         *  (supplied by the superclass) for NeedsCollision() */
        public ContactSensorCallback(RigidBody tgtBody, object context /*, ... */)
        {
            body = tgtBody;
            ctxt = context;
        }

        private RigidBody body; //!< The body the sensor is monitoring
        private object ctxt; //!< External information for contact processing

        //! If you don't want to consider collisions where the bodies are joined by a constraint, override NeedsCollision:
        /*! However, if you use a CollisionObject for #body instead of a RigidBody,
         *  then this is unnecessary—CheckCollideWithOverride isn't available */
        public override bool NeedsCollision(BroadphaseProxy proxy)
        {
            // superclass will check CollisionFilterGroup and CollisionFilterMask
            if (!base.NeedsCollision(proxy))
                return false;

            // if passed filters, may also want to avoid contacts between constraints
            return body.CheckCollideWithOverride(proxy.ClientObject as CollisionObject);
        }

        //! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
#if BT_USE_DOUBLE_PRECISION
        public override double AddSingleResult(ManifoldPoint cp,
#else
        public override float AddSingleResult(ManifoldPoint cp,
#endif
            CollisionObjectWrapper colObj0, int partId0, int index0,
            CollisionObjectWrapper colObj1, int partId1, int index1)
        {
            Vector3 pt; // will be set to point of collision relative to body
            if (colObj0.CollisionObject == body)
            {
                pt = cp.LocalPointA;
                //Console.WriteLine("ContactSensorCallback");
            }
            else
            {
                System.Diagnostics.Debug.Assert(colObj1.CollisionObject == body);
                pt = cp.LocalPointB;
            }

            // do stuff with the collision point
            return 0; // not actually sure if return value is used for anything...?
        }
    }
}
