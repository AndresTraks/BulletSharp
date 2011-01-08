using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using SlimDX;

namespace BspDemo
{
    [DebuggerDisplay("ClassName: {ClassName}")]
    public class BspEntity
    {
        public string ClassName { get; set; }
        public Vector3 Origin { get; set; }

        public Dictionary<string, string> KeyValues { get; set; }

        public BspEntity()
        {
            KeyValues = new Dictionary<string, string>();
        }
    }

    public struct BspLeaf
    {
        public int Cluster;
        public int Area;
        public Vector3 Min;
        public Vector3 Max;
        public int FirstLeafFace;
        public int NumLeafFaces;
        public int FirstLeafBrush;
        public int NumLeafBrushes;
    }

    [DebuggerDisplay("Offset: {Offset}, Length: {Length}")]
    public struct BspLump
    {
        public int Offset;
        public int Length;
    }

    public enum BspLumpType
    {
        Entities = 0,
        Textures,
        Planes,
        Nodes,
        Leaves,
        LeafFaces,
        LeafBrushes,
        Models,
        Brushes,
        BrushSides,
        Vertices,
        MeshIndices,
        Shaders,
        Faces,
        Lightmaps,
        LightVols,
        VisData
    }

    public class BspLoader
    {
        public List<BspEntity> Entities { get; set; }
        public BspLeaf[] Leaves { get; set; }
        public int[] LeafBrushes { get; set; }

        public bool LoadBspFile(string filename)
        {
            return LoadBspFile(new FileStream(filename, FileMode.Open, FileAccess.Read));
        }

        public bool LoadBspFile(Stream buffer)
        {
            BinaryReader reader = new BinaryReader(buffer);

            BspLump[] lumps = new BspLump[17];
            Entities = new List<BspEntity>();


            // read header
            string id = Encoding.ASCII.GetString(reader.ReadBytes(4), 0, 4);
            int version = reader.ReadInt32();

            if (id != "IBSP" || version != 0x2E)
                return false;

            for (int i = 0; i < lumps.Length; i++)
            {
                lumps[i].Offset = reader.ReadInt32();
                lumps[i].Length = reader.ReadInt32();
            }


            // read entities
            buffer.Position = lumps[(int)BspLumpType.Entities].Offset;
            int length = lumps[(int)BspLumpType.Entities].Length;
            
            byte[] entityBytes = new byte[length];
            reader.Read(entityBytes, 0, length);

            string entityString = Encoding.ASCII.GetString(entityBytes);
            string[] entityStrings = entityString.Split('\n');

            BspEntity bspEntity = null;
            foreach (string entity in entityStrings)
            {
                switch (entity)
                {
                    case "\0":
                        continue;

                    case "{":
                        bspEntity = new BspEntity();
                        break;

                    case "}":
                        Entities.Add(bspEntity);
                        break;

                    default:
                        string[] keyValue = entity.Trim('\"').Split(new string[] { "\" \"" }, 2, 0);
                        if (keyValue[0] == "classname")
                        {
                            bspEntity.ClassName = keyValue[1];
                        }
                        else if (keyValue[0] == "origin")
                        {
                            string[] originStrings = keyValue[1].Split(' ');
                            bspEntity.Origin = new Vector3(
                                float.Parse(originStrings[0], CultureInfo.InvariantCulture),
                                float.Parse(originStrings[1], CultureInfo.InvariantCulture),
                                float.Parse(originStrings[2], CultureInfo.InvariantCulture));
                        }
                        else
                        {
                            bspEntity.KeyValues.Add(keyValue[0], keyValue[1]);
                        }
                        break;
                }
            }
            
            // read leaves
            buffer.Position = lumps[(int)BspLumpType.Leaves].Offset;
            length = lumps[(int)BspLumpType.Leaves].Length / Marshal.SizeOf(typeof(BspLeaf));
            Leaves = new BspLeaf[length];

            for (int i = 0; i < length; i++ )
            {
                Leaves[i].Cluster = reader.ReadInt32();
                Leaves[i].Area = reader.ReadInt32();

                //Swap Y and Z; invert Z
                Leaves[i].Min.X = reader.ReadInt32();
                Leaves[i].Min.Z = -reader.ReadInt32();
                Leaves[i].Min.Y = reader.ReadInt32();

                //Swap Y and Z; invert Z
                Leaves[i].Max.X = reader.ReadInt32();
                Leaves[i].Max.Z = -reader.ReadInt32();
                Leaves[i].Max.Y = reader.ReadInt32();

                Leaves[i].FirstLeafFace = reader.ReadInt32();
                Leaves[i].NumLeafFaces = reader.ReadInt32();
                Leaves[i].FirstLeafBrush = reader.ReadInt32();
                Leaves[i].NumLeafBrushes = reader.ReadInt32();
            }

            // read leaf brushes
            buffer.Position = lumps[(int)BspLumpType.LeafBrushes].Offset;
            length = lumps[(int)BspLumpType.LeafBrushes].Length / sizeof(int);
            LeafBrushes = new int[length];

            for (int i = 0; i < length; i++)
            {
                LeafBrushes[i] = reader.ReadInt32();
            }

            return true;
        }

        public bool FindVectorByName(string name, ref Vector3 outVector)
        {
            foreach (BspEntity entity in Entities)
            {
                if (entity.ClassName == name &&
                    (entity.ClassName == "info_player_start" ||
                    entity.ClassName == "info_player_deathmatch"))
                {
                    outVector = entity.Origin;
                    return true;
                }
            }

            return false;
        }
    }
}
