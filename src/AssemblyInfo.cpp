#include "StdAfx.h"
#include "Version.h"

using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Security::Permissions;

[assembly:AssemblyTitleAttribute("BulletSharp")];
[assembly:AssemblyProductAttribute("BulletSharp")];
[assembly:AssemblyCopyrightAttribute(BULLETSHARP_COPYRIGHT)];

[assembly:AssemblyVersionAttribute(BULLETSHARP_VERSION_STRING)];

#if GRAPHICS_XNA31
[assembly:AssemblyDescriptionAttribute("BulletSharp for XNA 3.1")];
#elif GRAPHICS_XNA40
[assembly:AssemblyDescriptionAttribute("BulletSharp for XNA 4.0")];
#elif GRAPHICS_MONOGAME
[assembly:AssemblyDescriptionAttribute("BulletSharp for MonoGame")];
#elif GRAPHICS_SLIMDX
[assembly:AssemblyDescriptionAttribute("BulletSharp for SlimDX")];
#elif GRAPHICS_SHARPDX
[assembly:AssemblyDescriptionAttribute("BulletSharp for SharpDX")];
#elif GRAPHICS_MOGRE
[assembly:AssemblyDescriptionAttribute("BulletSharp for Mogre")];
#elif GRAPHICS_OPENTK
[assembly:AssemblyDescriptionAttribute("BulletSharp for OpenTK")];
#elif GRAPHICS_AXIOM
[assembly:AssemblyDescriptionAttribute("BulletSharp for Axiom 3D")];
#elif GRAPHICS_WAPICODEPACK
[assembly:AssemblyDescriptionAttribute("BulletSharp for Windows API Code Pack")];
#elif GRAPHICS_GENERIC
[assembly:AssemblyDescriptionAttribute("BulletSharp Generic")];
#endif

[assembly:ComVisible(false)];
[assembly:CLSCompliantAttribute(true)];
