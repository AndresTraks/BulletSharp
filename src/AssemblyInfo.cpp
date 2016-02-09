#include "StdAfx.h"
#include "Version.h"

using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Security::Permissions;

[assembly:AssemblyTitleAttribute("BulletSharp")];
[assembly:AssemblyProductAttribute("BulletSharp")];
[assembly:AssemblyCopyrightAttribute(BULLETSHARP_COPYRIGHT)];

[assembly:AssemblyVersionAttribute(BULLETSHARP_VERSION_STRING)];

#if GRAPHICS_MOGRE
[assembly:AssemblyDescriptionAttribute("BulletSharp for Mogre")];
#elif GRAPHICS_MONOGAME
[assembly:AssemblyDescriptionAttribute("BulletSharp for MonoGame")];
#elif GRAPHICS_NUMERICS
[assembly:AssemblyDescriptionAttribute("BulletSharp for System.Numerics")];
#elif GRAPHICS_OPENTK
[assembly:AssemblyDescriptionAttribute("BulletSharp for OpenTK")];
#elif GRAPHICS_SLIMDX
[assembly:AssemblyDescriptionAttribute("BulletSharp for SlimDX")];
#elif GRAPHICS_SHARPDX
[assembly:AssemblyDescriptionAttribute("BulletSharp for SharpDX")];
#elif GRAPHICS_GENERIC
[assembly:AssemblyDescriptionAttribute("BulletSharp Generic")];
#endif

[assembly:ComVisible(false)];
[assembly:CLSCompliantAttribute(true)];
