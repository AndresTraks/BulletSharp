#pragma once

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class Dispatcher;
	ref class UnionFind;

	public ref class SimulationIslandManager
	{
	public:
		/*ref class IslandCallback abstract
		{
		internal:
			btSimulationIslandManager::IslandCallback* _native;

			IslandCallback(btSimulationIslandManager::IslandCallback* native);

			~IslandCallback();
			!IslandCallback();

		public:
			void ProcessIsland(array<CollisionObject^>^ bodies, array<PersistentManifold>^ manifolds,
				int islandId);

			property bool IsDisposed
			{
				virtual bool get();
			}
		};
		*/


	internal:
		btSimulationIslandManager* _native;

	private:
		bool _preventDelete;

	internal:
		SimulationIslandManager(btSimulationIslandManager* native, bool preventDelete);

		~SimulationIslandManager();
		!SimulationIslandManager();

	public:
		SimulationIslandManager();

		//void BuildAndProcessIslands(Dispatcher^ dispatcher, CollisionWorld^ collisionWorld,
		//	IslandCallback^ callback);
		void BuildIslands(Dispatcher^ dispatcher, CollisionWorld^ colWorld);
		void FindUnions(Dispatcher^ dispatcher, CollisionWorld^ colWorld);
		void InitUnionFind(int n);
		void StoreIslandActivationState(CollisionWorld^ world);
		void UpdateActivationState(CollisionWorld^ colWorld, Dispatcher^ dispatcher);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool SplitIslands
		{
			bool get();
			void set(bool doSplitIslands);
		}

		property UnionFind^ UnionFind
		{
			BulletSharp::UnionFind^ get();
		}
	};
};
