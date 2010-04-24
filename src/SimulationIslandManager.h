#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class Dispatcher;

	public ref class SimulationIslandManager : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;
	private:
		btSimulationIslandManager* _manager;
	internal:
		SimulationIslandManager(btSimulationIslandManager* manager);

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

		//property UnionFind^ UnionFind
		//{
		//	BulletSharp::UnionFind^ get();
		//}

	internal:
		property btSimulationIslandManager* UnmanagedPointer
		{
			virtual btSimulationIslandManager* get();
			void set(btSimulationIslandManager* value);
		}
	};
};
