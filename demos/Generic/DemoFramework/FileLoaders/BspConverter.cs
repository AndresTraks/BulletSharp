using BulletSharp;
using System.Collections.Generic;

namespace DemoFramework.FileLoaders
{
    public abstract class BspConverter
    {
        public void ConvertBsp(BspLoader bspLoader, float scaling)
        {
            Vector3 playerStart = GetPlayerPosition(bspLoader);
            playerStart.Z += 20.0f; //start a bit higher
            playerStart *= scaling;

            foreach (BspLeaf leaf in bspLoader.Leaves)
            {
                for (int b = 0; b < leaf.NumLeafBrushes; b++)
                {
                    int brushID = bspLoader.LeafBrushes[leaf.FirstLeafBrush + b];
                    BspBrush brush = bspLoader.Brushes[brushID];

                    if (brush.ShaderNum == -1) continue;

                    ContentFlags flags = bspLoader.IsVbsp
                        ? (ContentFlags)brush.ShaderNum
                        : bspLoader.Shaders[brush.ShaderNum].ContentFlags;

                    if ((flags & ContentFlags.Solid) == 0) continue;

                    var planeEquations = new List<Vector4>();
                    brush.ShaderNum = -1;

                    for (int p = 0; p < brush.NumSides; p++)
                    {
                        int sideId = brush.FirstSide + p;

                        BspBrushSide brushSide = bspLoader.BrushSides[sideId];
                        BspPlane plane = bspLoader.Planes[brushSide.PlaneNum];
                        Vector4 planeEquation = new Vector4(plane.Normal, scaling * -plane.Distance);
                        planeEquations.Add(planeEquation);
                    }

                    bool isValidBrush = planeEquations.Count > 0;
                    if (isValidBrush)
                    {
                        List<Vector3> vertices = GeometryUtil.GetVerticesFromPlaneEquations(planeEquations);
                        const bool isEntity = false;
                        Vector3 entityTarget = Vector3.Zero;
                        AddConvexVerticesCollider(vertices, isEntity, entityTarget);
                    }
                }
            }
            /*
            foreach (BspEntity entity in bspLoader.Entities)
            {
                if (entity.ClassName == "trigger_push")
                {
                }
            }
            */
        }

        private Vector3 GetPlayerPosition(BspLoader bspLoader)
        {
            BspEntity player;
            if (bspLoader.Entities.TryGetValue("info_player_start", out player))
            {
                return player.Origin;
            }
            else if (bspLoader.Entities.TryGetValue("info_player_deathmatch", out player))
            {
                return player.Origin;
            }
            return new Vector3(0, 0, 100);
        }

        public abstract void AddConvexVerticesCollider(List<Vector3> vertices, bool isEntity, Vector3 entityTargetLocation);
    }
}
