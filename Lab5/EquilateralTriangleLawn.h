#pragma once
#include "Lawn.h"
#include "IFenceable.h"

namespace lab5
{
	class EquilateralTriangleLawn : public Lawn, IFenceable
	{
	public:
		EquilateralTriangleLawn(unsigned int oneSide);

		// Lawn을(를) 통해 상속됨
		virtual unsigned int GetArea() const override;

		// IFenceable을(를) 통해 상속됨
		virtual unsigned int GetMinimumFencesCount() const override;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const override;

	private:
		const unsigned int mOneSide;
	};
}

