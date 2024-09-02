#include "IceCube.h"

namespace lab9
{
	// 생성자: IceCube 객체를 초기화합니다. 
	// 초기 수명을 0으로 설정하여 비활성 상태로 만듭니다.
	IceCube::IceCube()
		: mFrameCountToLive(0)  // 초기화 리스트를 사용하여 mFrameCountToLive를 0으로 설정
	{
	}

	// 소멸자: 특별히 할 일이 없으므로 빈 상태로 유지
	IceCube::~IceCube()
	{
	}

	// Initialize 함수: 객체의 수명을 설정하여 활성화합니다.
	// 이 수명은 객체가 살아 있는 프레임 수를 나타냅니다.
	void IceCube::Initialize(unsigned int frameCountToLive)
	{
		mFrameCountToLive = frameCountToLive;  // 지정된 수명으로 초기화
	}

	// Reset 함수: 객체를 초기화하여 비활성 상태로 만듭니다.
	// 수명을 0으로 설정하여 비활성화합니다.
	void IceCube::Reset()
	{
		mFrameCountToLive = 0;  // 수명을 0으로 설정하여 객체를 비활성화
	}

	// Animate 함수: 객체의 애니메이션 상태를 업데이트합니다.
	// 객체의 수명을 1 감소시키며, 수명이 0이 되면 더 이상 업데이트하지 않습니다.
	void IceCube::Animate()
	{
		if (mFrameCountToLive == 0)  // 객체가 이미 비활성화된 경우
		{
			return;  // 아무 작업도 하지 않고 반환
		}

		mFrameCountToLive--;  // 수명을 1 감소시킴
	}

	// IsActive 함수: 객체가 활성 상태인지 확인합니다.
	// 수명이 0보다 크면 활성 상태로 간주합니다.
	bool IceCube::IsActive() const
	{
		return mFrameCountToLive > 0;  // 수명이 0보다 크면 true, 그렇지 않으면 false 반환
	}
}