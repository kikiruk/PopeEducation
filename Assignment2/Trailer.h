#pragma once

namespace assignment2
{
	class Trailer 
	{
	public:
		Trailer(unsigned int weight);
		~Trailer() = default;

		unsigned int GetWeight() const;

	private:
		unsigned int mWeight;
	};
}