#include "Game.h"

namespace lab9
{
	// 생성자: 게임 객체를 초기화합니다.
	// 난수 시드를 설정하고, 객체 풀을 초기화하며, 활성 객체 목록의 크기를 예약합니다.
	Game::Game(unsigned int seed, unsigned int poolSize) :
		mPoolSize(poolSize),  // 객체 풀의 최대 크기를 설정
		mReturnGameObjects(poolSize)  // 객체 풀을 초기화
	{
		srand(seed);  // 난수 생성기 시드 설정
		mActiveGameObjects.reserve(poolSize);  // 활성 객체 목록의 크기를 미리 할당
	}

	// Spawn 함수: 새로운 IceCube 객체를 풀에서 가져와 활성화하고 목록에 추가합니다.
	void Game::Spawn()
	{
		IceCube* iceCube = mReturnGameObjects.Get();  // 객체 풀에서 IceCube 객체 가져오기
		iceCube->Initialize(rand() % MAX_FRAME_COUNT_TO_LIVE + 1);  // 무작위 수명으로 초기화
		mActiveGameObjects.push_back(iceCube);  // 활성 객체 목록에 추가
	}

	// 소멸자: 게임이 종료될 때 모든 활성화된 IceCube 객체를 삭제하고 목록을 비웁니다.
	Game::~Game()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it)
		{
			delete (*it);  // IceCube 객체를 삭제
		}

		mActiveGameObjects.clear();  // 활성 객체 목록을 비움
	}

	// Update 함수: 활성화된 모든 IceCube 객체를 업데이트하고, 비활성화된 객체를 풀로 반환합니다.
	void Game::Update()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end();)
		{
			IceCube* iceCube = *it;
			iceCube->Animate();  // IceCube 객체의 애니메이션 상태 업데이트

			if (!iceCube->IsActive())  // IceCube 객체가 비활성화된 경우
			{
				it = mActiveGameObjects.erase(it);  // 활성 객체 목록에서 제거
				mReturnGameObjects.Return(iceCube);  // 객체 풀에 반환
				continue;  // 다음 객체로 이동
			}

			++it;  // 다음 객체로 이동
		}
	}

	// GetActiveGameObjects 함수: 현재 활성화된 IceCube 객체 목록을 반환합니다.
	const std::vector<IceCube*>& Game::GetActiveGameObjects() const
	{
		return mActiveGameObjects;
	}

	// GetObjectPool 함수: IceCube 객체 풀에 대한 참조를 반환합니다.
	ObjectPool<IceCube>& Game::GetObjectPool()
	{
		return mReturnGameObjects;
	}
}