using SlimDX.Direct3D9;

namespace DemoFramework.SlimDX
{
    public class DeviceSettings9
    {
        public int AdapterOrdinal
        {
            get;
            set;
        }

        public CreateFlags CreationFlags
        {
            get;
            set;
        }

        public MultisampleType MultisampleType
        {
            get;
            set;
        }

        public bool Windowed
        {
            get;
            set;
        }
    }
}
