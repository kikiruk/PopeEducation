#include <cassert>
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
		return GetDriveSpeed();
	}

	unsigned int Sedan::GetDriveSpeed() const
	{
		if (mPassengerWeight <= 80)
			return 480;
		else if (mPassengerWeight > 80)
			return 458;
		else if (mPassengerWeight > 160)
			return 400;
		else if (mPassengerWeight > 260)
			return 380;
		else if (mPassengerWeight > 350)
			return 300;
		else
			assert(false);
	}

	void Sedan::Travel()
	{
		if (mTrailer != nullptr)
		{
			if (mTravelCount != 5)
				mDistance += GetMaxSpeed();

			mTravelCount = (mTravelCount + 1) % 6;
		}
		else
		{
			if (mTravelCount != 5 && mTravelCount != 6)
				mDistance += GetMaxSpeed();

			mTravelCount = (mTravelCount + 1) % 7;
		}
	}
}