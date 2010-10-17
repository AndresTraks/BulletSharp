#include "StdAfx.h"
#include "Version.h"

using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Security::Permissions;

[assembly:AssemblyTitleAttribute("BulletSharp")];
[assembly:AssemblyProductAttribute("BulletSharp")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) Andres Traks 2009-2010")];

[assembly:AssemblyVersionAttribute(BULLETSHARP_VERSION_STRING)];

[assembly:ComVisible(false)];
[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];
