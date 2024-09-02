#include "Game.h"

namespace lab9
{
	// ������: ���� ��ü�� �ʱ�ȭ�մϴ�.
	// ���� �õ带 �����ϰ�, ��ü Ǯ�� �ʱ�ȭ�ϸ�, Ȱ�� ��ü ����� ũ�⸦ �����մϴ�.
	Game::Game(unsigned int seed, unsigned int poolSize) :
		mPoolSize(poolSize),  // ��ü Ǯ�� �ִ� ũ�⸦ ����
		mReturnGameObjects(poolSize)  // ��ü Ǯ�� �ʱ�ȭ
	{
		srand(seed);  // ���� ������ �õ� ����
		mActiveGameObjects.reserve(poolSize);  // Ȱ�� ��ü ����� ũ�⸦ �̸� �Ҵ�
	}

	// Spawn �Լ�: ���ο� IceCube ��ü�� Ǯ���� ������ Ȱ��ȭ�ϰ� ��Ͽ� �߰��մϴ�.
	void Game::Spawn()
	{
		IceCube* iceCube = mReturnGameObjects.Get();  // ��ü Ǯ���� IceCube ��ü ��������
		iceCube->Initialize(rand() % MAX_FRAME_COUNT_TO_LIVE + 1);  // ������ �������� �ʱ�ȭ
		mActiveGameObjects.push_back(iceCube);  // Ȱ�� ��ü ��Ͽ� �߰�
	}

	// �Ҹ���: ������ ����� �� ��� Ȱ��ȭ�� IceCube ��ü�� �����ϰ� ����� ���ϴ�.
	Game::~Game()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it)
		{
			delete (*it);  // IceCube ��ü�� ����
		}

		mActiveGameObjects.clear();  // Ȱ�� ��ü ����� ���
	}

	// Update �Լ�: Ȱ��ȭ�� ��� IceCube ��ü�� ������Ʈ�ϰ�, ��Ȱ��ȭ�� ��ü�� Ǯ�� ��ȯ�մϴ�.
	void Game::Update()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end();)
		{
			IceCube* iceCube = *it;
			iceCube->Animate();  // IceCube ��ü�� �ִϸ��̼� ���� ������Ʈ

			if (!iceCube->IsActive())  // IceCube ��ü�� ��Ȱ��ȭ�� ���
			{
				it = mActiveGameObjects.erase(it);  // Ȱ�� ��ü ��Ͽ��� ����
				mReturnGameObjects.Return(iceCube);  // ��ü Ǯ�� ��ȯ
				continue;  // ���� ��ü�� �̵�
			}

			++it;  // ���� ��ü�� �̵�
		}
	}

	// GetActiveGameObjects �Լ�: ���� Ȱ��ȭ�� IceCube ��ü ����� ��ȯ�մϴ�.
	const std::vector<IceCube*>& Game::GetActiveGameObjects() const
	{
		return mActiveGameObjects;
	}

	// GetObjectPool �Լ�: IceCube ��ü Ǯ�� ���� ������ ��ȯ�մϴ�.
	ObjectPool<IceCube>& Game::GetObjectPool()
	{
		return mReturnGameObjects;
	}
}