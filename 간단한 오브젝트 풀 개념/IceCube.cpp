#include "IceCube.h"

namespace lab9
{
	// ������: IceCube ��ü�� �ʱ�ȭ�մϴ�. 
	// �ʱ� ������ 0���� �����Ͽ� ��Ȱ�� ���·� ����ϴ�.
	IceCube::IceCube()
		: mFrameCountToLive(0)  // �ʱ�ȭ ����Ʈ�� ����Ͽ� mFrameCountToLive�� 0���� ����
	{
	}

	// �Ҹ���: Ư���� �� ���� �����Ƿ� �� ���·� ����
	IceCube::~IceCube()
	{
	}

	// Initialize �Լ�: ��ü�� ������ �����Ͽ� Ȱ��ȭ�մϴ�.
	// �� ������ ��ü�� ��� �ִ� ������ ���� ��Ÿ���ϴ�.
	void IceCube::Initialize(unsigned int frameCountToLive)
	{
		mFrameCountToLive = frameCountToLive;  // ������ �������� �ʱ�ȭ
	}

	// Reset �Լ�: ��ü�� �ʱ�ȭ�Ͽ� ��Ȱ�� ���·� ����ϴ�.
	// ������ 0���� �����Ͽ� ��Ȱ��ȭ�մϴ�.
	void IceCube::Reset()
	{
		mFrameCountToLive = 0;  // ������ 0���� �����Ͽ� ��ü�� ��Ȱ��ȭ
	}

	// Animate �Լ�: ��ü�� �ִϸ��̼� ���¸� ������Ʈ�մϴ�.
	// ��ü�� ������ 1 ���ҽ�Ű��, ������ 0�� �Ǹ� �� �̻� ������Ʈ���� �ʽ��ϴ�.
	void IceCube::Animate()
	{
		if (mFrameCountToLive == 0)  // ��ü�� �̹� ��Ȱ��ȭ�� ���
		{
			return;  // �ƹ� �۾��� ���� �ʰ� ��ȯ
		}

		mFrameCountToLive--;  // ������ 1 ���ҽ�Ŵ
	}

	// IsActive �Լ�: ��ü�� Ȱ�� �������� Ȯ���մϴ�.
	// ������ 0���� ũ�� Ȱ�� ���·� �����մϴ�.
	bool IceCube::IsActive() const
	{
		return mFrameCountToLive > 0;  // ������ 0���� ũ�� true, �׷��� ������ false ��ȯ
	}
}