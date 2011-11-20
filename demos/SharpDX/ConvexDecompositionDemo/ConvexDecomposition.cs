using SharpDX;

namespace ConvexDecompositionDemo
{
    class ConvexResult
    {
        ConvexResult(float[] hvertices, int[] hindices)
        {
            mHullVertices = (float[])hvertices.Clone();
            mHullIndices = (int[])hindices.Clone();
        }

        ConvexResult(ConvexResult r)
        {
            mHullVertices = (float[])r.mHullVertices.Clone();
            mHullIndices = (int[])r.mHullIndices.Clone();
        }

        // the convex hull.
        float[] mHullVertices;
        int[] mHullIndices;

        float mHullVolume;		    // the volume of the convex hull.

        Vector3 mOBBSides;			  // the width, height and breadth of the best fit OBB
        Vector3 mOBBCenter;      // the center of the OBB
        Quaternion mOBBOrientation; // the quaternion rotation of the OBB.
        Matrix mOBBTransform;  // the 4x4 transform of the OBB.
        float mOBBVolume;         // the volume of the OBB

        float mSphereRadius;      // radius and center of best fit sphere
        Vector3 mSphereCenter;
        float mSphereVolume;      // volume of the best fit sphere
    };

    interface IConvexDecomposition
    {
        void ConvexDebugTri(float[] p1, float[] p2, float[] p3, uint color);
        void ConvexDebugPoint(float[] p, float dist, uint color);
        void ConvexDebugBound(float[] bmin, float[] bmax, uint color);
        void ConvexDebugOBB(float[] sides, float[] matrix, uint color);

        //void ConvexDecompResult(ConvexResult &result) = 0;
    };

    // just to avoid passing a zillion parameters to the method the
    // options are packed into this descriptor.
    class DecompDesc
    {
        public DecompDesc()
        {
            mDepth = 5;
            mCpercent = 5;
            mPpercent = 5;
            mMaxVertices = 32;
        }

        // describes the input triangle.
        public Vector3[] mVertices;
        public int mTcount;   // the number of triangles in the source mesh.
        public int[] mIndices;  // the indexed triangle list array (zero index based)

        // options
        public int mDepth;    // depth to split, a maximum of 10, generally not over 7.
        public float mCpercent; // the concavity threshold percentage.  0=20 is reasonable.
        public float mPpercent; // the percentage volume conservation threshold to collapse hulls. 0-30 is reasonable.

        // hull output limits.
        public int mMaxVertices; // maximum number of vertices in the output hull. Recommended 32 or less.
        public float mSkinWidth;   // a skin width to apply to the output hulls.

        public IConvexDecomposition mCallback; // the interface to receive back the results.
    };

    class ConvexDecomposition
    {

    }
}
