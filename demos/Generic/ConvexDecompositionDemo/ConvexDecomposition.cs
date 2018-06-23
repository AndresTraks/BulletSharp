using BulletSharp;
using System.Collections.Generic;
using System.Linq;

namespace ConvexDecompositionDemo
{
    internal sealed class ConvexDecomposition
    {
        private WavefrontWriter _wavefrontWriter;

        public ConvexDecomposition(WavefrontWriter wavefrontWriter = null)
        {
            _wavefrontWriter = wavefrontWriter;
        }

        public List<ConvexHullShape> ConvexShapes { get; } = new List<ConvexHullShape>();
        public List<Vector3> ConvexCentroids { get; } = new List<Vector3>();

        public Vector3 LocalScaling { get; set; } = new Vector3(1, 1, 1);

        public void Result(Vector3[] hullVertices, int[] hullIndices)
        {
            _wavefrontWriter.OutputObject(hullVertices, hullIndices);

            // Calculate centroid, to shift vertices around center of mass
            Vector3 centroid = CalculateCentroid(hullVertices);
            ConvexCentroids.Add(centroid);

            List<Vector3> outVertices = hullVertices.Select(v => v * LocalScaling - centroid).ToList();

            // This is a tools issue:
            // due to collision margin, convex objects overlap, compensate for it here.
#if false
            outVertices = ShrinkObjectInwards(hullVertices);
#endif

            var convexShape = new ConvexHullShape(outVertices);
            convexShape.Margin = 0.01f;
            ConvexShapes.Add(convexShape);
        }

        private Vector3 CalculateCentroid(ICollection<Vector3> vertices)
        {
            Vector3 centroid = Vector3.Zero;
            foreach (Vector3 v in vertices)
            {
                centroid += v;
            }
            return (centroid * LocalScaling) / vertices.Count;
        }
#if false
        private List<Vector3> ShrinkObjectInwards(AlignedVector3Array vertices)
        {
            const float collisionMargin = 0.01f;

            AlignedVector3Array planeEquations = new AlignedVector3Array();
            GeometryUtil.GetPlaneEquationsFromVertices(vertices, planeEquations);
            List<Vector4> shiftedPlaneEquations =
                planeEquations.Select(p => new Vector4(p.X, p.Y, p.Z, p.W + collisionMargin)).ToList();
            planeEquations.Dispose();
            return GeometryUtil.GetVerticesFromPlaneEquations(shiftedPlaneEquations);
        }
#endif
    }
}
