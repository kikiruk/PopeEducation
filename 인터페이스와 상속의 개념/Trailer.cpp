#include "Trailer.h"

namespace assignment2
{
	Trailer::Trailer(unsigned int weight) : 
		mWeight(weight)
	{
	}

	Trailer::Trailer(const Trailer& other) :
		mWeight(other.mWeight)
	{
	}

	unsigned int Trailer::GetWeight() const
	{
		return mWeight;
	}
}