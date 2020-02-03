#pragma once
#include "Lawn.h"

namespace lab5
{
	class CircleLawn : public Lawn
	{
	public:
		CircleLawn(unsigned int radius);

		// Lawn을(를) 통해 상속됨
		virtual unsigned int GetArea() const override;

	private:
		const unsigned int mRadius;
	};
}

