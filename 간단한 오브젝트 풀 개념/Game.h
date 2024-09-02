#pragma once
#include <vector>
#include "IceCube.h"
#include "ObjectPool.h"

namespace lab9
{
	// Game Ŭ����: ���� ������ IceCube ��ü�� �����ϴ� Ŭ����
	// ��ü Ǯ�� ����Ͽ� IceCube ��ü�� ȿ�������� �����ϰ� ����
	class Game final
	{
	public:
		// ������: ���� �õ�� ��ü Ǯ�� ũ�⸦ �����Ͽ� ������ �ʱ�ȭ
		Game(unsigned int seed, unsigned int poolSize);
		Game(const Game& other) = delete;  // ���� ������ ����
		~Game();  // �Ҹ���: ���ҽ��� ����

		Game& operator=(const Game&) = delete;  // ���� ���� ������ ����
		void Spawn();  // ���ο� IceCube ��ü�� �����Ͽ� Ȱ��ȭ
		void Update();  // Ȱ��ȭ�� ��� IceCube ��ü�� ������Ʈ (�ִϸ��̼� ó��)
		const std::vector<IceCube*>& GetActiveGameObjects() const;  // ���� Ȱ��ȭ�� IceCube ��ü ����� ��ȯ
		ObjectPool<IceCube>& GetObjectPool();  // IceCube ��ü Ǯ�� ���� ������ ��ȯ

	private:
		const unsigned int mPoolSize;  // ��ü Ǯ�� �ִ� ũ��
		static constexpr unsigned int MAX_FRAME_COUNT_TO_LIVE = 100;  // IceCube ��ü�� �ִ� ���� (������ ��)
		std::vector<IceCube*> mActiveGameObjects;  // ���� Ȱ��ȭ�� IceCube ��ü ���
		ObjectPool<IceCube> mReturnGameObjects;  // IceCube ��ü�� �����ϴ� ��ü Ǯ
	};
}