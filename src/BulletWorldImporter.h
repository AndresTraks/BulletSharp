#pragma once

#include "DynamicsWorld.h"
#include "IDisposable.h"

namespace BulletSharp
{
	namespace Serialize
	{
		public ref class BulletWorldImporter : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btBulletWorldImporter* _importer;

		public:
			!BulletWorldImporter();
		protected:
			~BulletWorldImporter();

		public:
			BulletWorldImporter(DynamicsWorld^ world);
			BulletWorldImporter();

			void DeleteAllData();
			bool LoadFile(String^ fileName);
			//bool LoadFileFromMemory(MemoryStream^ memoryBuffer, int len);
			
			property bool IsDisposed
			{
				virtual bool get();
			}

			property bool NumBvhs
			{
				bool get();
			}

			property bool NumCollisionShapes
			{
				bool get();
			}

			property bool NumConstraints
			{
				bool get();
			}

			property bool NumRigidBodies
			{
				bool get();
			}

			property bool NumTriangleInfoMaps
			{
				bool get();
			}

			property bool VerboseMode
			{
				bool get();
				void set(bool value);
			}
		};
	};
};
