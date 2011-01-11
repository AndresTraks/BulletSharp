using SlimDX;

namespace BspDemo
{
    public class BspConverter
    {
        public void ConvertBsp(BspLoader bspLoader, float scaling)
        {
            Vector3 playerStart = new Vector3(0, 0, 100);
            if (bspLoader.FindVectorByName("info_player_start", ref playerStart) == false)
            {
                bspLoader.FindVectorByName("info_player_deathmatch", ref playerStart);
            }
            playerStart[2] += 20.0f * scaling; //start a bit higher

            foreach (BspLeaf leaf in bspLoader.Leaves)
            {
                bool isValidBrush = false;

                for (int b = 0; b < leaf.NumLeafBrushes; b++)
                {
                    int brushID = bspLoader.LeafBrushes[leaf.FirstLeafBrush + b];
                    BspBrush brush = bspLoader.Brushes[brushID];

                    if (brush.ShaderNum != -1)
                    {
                        if ((bspLoader.Shaders[brush.ShaderNum].ContentFlags & ContentFlags.Solid) == ContentFlags.Solid)
                        {
                        }
                    }
                }
            }

            foreach (BspEntity entity in bspLoader.Entities)
            {
                if (entity.ClassName == "trigger_push")
                {
                }
            }
        }
    }
}
