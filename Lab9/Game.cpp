#include "Game.h"

namespace lab9
{
	Game::Game(unsigned int seed, unsigned int poolSize) :
		mPoolSize(poolSize),
		mReturnGameObjects(poolSize)
	{
		srand(seed);
		mActiveGameObjects.reserve(poolSize);
	}

	void Game::Spawn()
	{
		IceCube* iceCube = mReturnGameObjects.Get();
		iceCube->Initialize(rand() % MAX_FRAME_COUNT_TO_LIVE + 1);
		mActiveGameObjects.push_back(iceCube);
	}

	Game::~Game()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it)
		{
			delete (*it);
		}

		mActiveGameObjects.clear();
	}

	void Game::Update()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end();)
		{
			IceCube* iceCube = *it;
			iceCube->Animate();

			if (!iceCube->IsActive())
			{
				it = mActiveGameObjects.erase(it);
				mReturnGameObjects.Return(iceCube);
				continue;
			}

			++it;
		}
	}

	const std::vector<IceCube*>& Game::GetActiveGameObjects() const
	{
		return mActiveGameObjects;
	}

	ObjectPool<IceCube>& Game::GetObjectPool()
	{
		return mReturnGameObjects;
	}
}