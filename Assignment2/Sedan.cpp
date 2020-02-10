#include "Sedan.h"

namespace assignment2
{
	Sedan::Sedan() : 
		Vehicle(4),
		mTrailer(nullptr)
	{
	}

	Sedan::~Sedan()
	{
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		if(mTrailer != nullptr)
			return false;
		
		mTrailer = trailer;

		return true;
	}

	bool Sedan::RemoveTrailer()
	{
		if(mTrailer == nullptr)
			return false;

		delete mTrailer;
		mTrailer = nullptr;

		return true;
	}

	unsigned int Sedan::GetMaxSpeed() const
	{
		return 0;
	}

	unsigned int Sedan::GetDriveSpeed() const
	{
		return 0;
	}

	void Sedan::Travel()
	{
	}
}