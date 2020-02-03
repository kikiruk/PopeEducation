#pragma once
#include "Lawn.h"

namespace lab5
{
	class CircleLawn : public Lawn
	{
	public:
		CircleLawn(unsigned int radius);

		// Lawn��(��) ���� ��ӵ�
		virtual unsigned int GetArea() const override;

	private:
		const unsigned int mRadius;
	};
}

