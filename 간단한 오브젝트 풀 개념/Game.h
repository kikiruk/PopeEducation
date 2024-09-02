#pragma once
#include <vector>
#include "IceCube.h"
#include "ObjectPool.h"

namespace lab9
{
	// Game 클래스: 게임 내에서 IceCube 객체를 관리하는 클래스
	// 객체 풀을 사용하여 IceCube 객체를 효율적으로 생성하고 관리
	class Game final
	{
	public:
		// 생성자: 난수 시드와 객체 풀의 크기를 설정하여 게임을 초기화
		Game(unsigned int seed, unsigned int poolSize);
		Game(const Game& other) = delete;  // 복사 생성자 금지
		~Game();  // 소멸자: 리소스를 정리

		Game& operator=(const Game&) = delete;  // 복사 대입 연산자 금지
		void Spawn();  // 새로운 IceCube 객체를 생성하여 활성화
		void Update();  // 활성화된 모든 IceCube 객체를 업데이트 (애니메이션 처리)
		const std::vector<IceCube*>& GetActiveGameObjects() const;  // 현재 활성화된 IceCube 객체 목록을 반환
		ObjectPool<IceCube>& GetObjectPool();  // IceCube 객체 풀에 대한 참조를 반환

	private:
		const unsigned int mPoolSize;  // 객체 풀의 최대 크기
		static constexpr unsigned int MAX_FRAME_COUNT_TO_LIVE = 100;  // IceCube 객체의 최대 수명 (프레임 수)
		std::vector<IceCube*> mActiveGameObjects;  // 현재 활성화된 IceCube 객체 목록
		ObjectPool<IceCube> mReturnGameObjects;  // IceCube 객체를 관리하는 객체 풀
	};
}