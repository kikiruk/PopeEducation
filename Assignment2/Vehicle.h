#pragma once

#include "Person.h"
#include "Trailer.h"

namespace assignment2
{
	class DeusExMachina;
	class Sedan;

	class Vehicle
	{
		friend DeusExMachina;
		friend Sedan;

	public:
		Vehicle(unsigned int maxPassengersCount);
		Vehicle(const Vehicle& other);
		virtual ~Vehicle();

		virtual unsigned int GetMaxSpeed() const = 0;
		virtual void Travel() = 0;

		virtual const Vehicle& operator=(const Vehicle& other);

		bool AddPassenger(const Person* person);
		bool RemovePassenger(unsigned int i);
		const Person* GetPassenger(unsigned int i) const;
		unsigned int GetPassengersCount() const;
		unsigned int GetMaxPassengersCount() const;

	protected:
		unsigned int mMaxPassengerCount;
		unsigned int mCount;
		const Person** mPassengers;
		unsigned int mPassengerWeight;
		unsigned int mTravelCount;
		unsigned int mDistance;
		const Trailer* mTrailer;
	};
}