#pragma once
#include "Lawn.h"
#include "IFenceable.h"

namespace lab5
{
	class SquareLawn : public Lawn, IFenceable
	{
	public:
		SquareLawn(unsigned int width);

		// Lawn��(��) ���� ��ӵ�
		virtual unsigned int GetArea() const override;

		// IFenceable��(��) ���� ��ӵ�
		virtual unsigned int GetMinimumFencesCount() const override;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const override;
	private:
		const unsigned int mWidth;
	};
}

