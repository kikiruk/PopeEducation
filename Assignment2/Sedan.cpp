#include <cassert>
#include "Sedan.h"

namespace assignment2
{
	Sedan::Sedan() :
		Vehicle(4),
		mTrailer(nullptr)
	{
	}

	Sedan::Sedan(const Sedan& copy) :
		Vehicle(copy),
		mTrailer(nullptr)
	{
		if (copy.mTrailer != nullptr)
			mTrailer = new Trailer(*copy.mTrailer);
	}

	Sedan::~Sedan()
	{
		if (mTrailer != nullptr)
			delete mTrailer;
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		if (trailer == NULL)
			return false;
			
		if (mTrailer != nullptr)
			return false;

		mTrailer = trailer;

		return true;
	}

	bool Sedan::RemoveTrailer()
	{
		if (mTrailer == nullptr)
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
		unsigned int weight = mPassengerWeight;

		if(mTrailer != nullptr)
			weight += mTrailer->GetWeight();

		if (weight > 350)
			return 300;
		else if (weight > 260)
			return 380;
		else if (weight > 160)
			return 400;
		else if (weight > 80)
			return 458;
		else
			return 480;
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