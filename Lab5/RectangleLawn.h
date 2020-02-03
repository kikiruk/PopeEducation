#pragma once
#include "Lawn.h"
#include "IFenceable.h"

namespace lab5
{
	class RectangleLawn : public Lawn, IFenceable
	{
	public:
		RectangleLawn(unsigned int width, unsigned int height);

		// Lawn을(를) 통해 상속됨
		virtual unsigned int GetArea() const override;

		// IFenceable을(를) 통해 상속됨
		virtual unsigned int GetMinimumFencesCount() const override;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const override;

	protected:
		const unsigned int mWidth;
		const unsigned int mHeight;
	};
}
