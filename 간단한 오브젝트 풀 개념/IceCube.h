#pragma once

namespace lab9
{
	// IceCube Ŭ����: �ִϸ��̼ǰ� ������ �����ϴ� ������ ��ü�� ��Ÿ��
	// final Ű����� �� Ŭ������ ��ӵ� �� ������ �ǹ�
	class IceCube final
	{
	public:
		IceCube();  // ������: ��ü�� �ʱ�ȭ
		~IceCube();  // �Ҹ���: ��ü�� �Ҹ�� �� ȣ��

		void Initialize(unsigned int frameCountToLive);  // ��ü�� ������ �����ϰ� �ʱ�ȭ
		void Reset();  // ��ü�� �缳���Ͽ� ��Ȱ��ȭ ���·� ����
		void Animate();  // ��ü�� �ִϸ��̼��� ������Ʈ (���� ����)
		bool IsActive() const;  // ��ü�� Ȱ�� �������� Ȯ��

	private:
		unsigned int mFrameCountToLive;  // ��ü�� ���� ���� (������ ��)
	};
}