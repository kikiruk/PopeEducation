#pragma once

namespace lab9
{
	// IceCube 클래스: 애니메이션과 수명을 관리하는 간단한 객체를 나타냄
	// final 키워드는 이 클래스가 상속될 수 없음을 의미
	class IceCube final
	{
	public:
		IceCube();  // 생성자: 객체를 초기화
		~IceCube();  // 소멸자: 객체가 소멸될 때 호출

		void Initialize(unsigned int frameCountToLive);  // 객체의 수명을 설정하고 초기화
		void Reset();  // 객체를 재설정하여 비활성화 상태로 만듦
		void Animate();  // 객체의 애니메이션을 업데이트 (수명 감소)
		bool IsActive() const;  // 객체가 활성 상태인지 확인

	private:
		unsigned int mFrameCountToLive;  // 객체의 남은 수명 (프레임 수)
	};
}