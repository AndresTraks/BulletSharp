#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class Dispatcher;
	ref class UnionFind;

	public ref class SimulationIslandManager : BulletSharp::IDisposable
	{
	public:
		/*ref class IslandCallback : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		internal:
			btSimulationIslandManager::IslandCallback* _native;

		public:
			!IslandCallback();
		protected:
			~IslandCallback();

		public:
			IslandCallback();

			void ProcessIsland(array<CollisionObject^>^ bodies, array<PersistentManifold^>^ manifolds, int islandId);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};
		*/
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		bool _preventDelete;

	internal:
		btSimulationIslandManager* _native;

		SimulationIslandManager(btSimulationIslandManager* manager, bool preventDelete);

	public:
		!SimulationIslandManager();
	protected:
		~SimulationIslandManager();

	public:
		SimulationIslandManager();

		//void BuildAndProcessIslands(Dispatcher^ dispatcher, CollisionWorld^ collisionWorld, IslandCallback^ callback);
		void BuildIslands(Dispatcher^ dispatcher, CollisionWorld^ colWorld);
		void FindUnions(Dispatcher^ dispatcher, CollisionWorld^ colWorld);
		void InitUnionFind(int n);
		void UpdateActivationState(CollisionWorld^ colWorld, Dispatcher^ dispatcher);
		void StoreIslandActivationState(CollisionWorld^ world);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool SplitIslands
		{
			bool get();
			void set(bool value);
		}

		property UnionFind^ UnionFind
		{
			BulletSharp::UnionFind^ get();
		}
	};
};
