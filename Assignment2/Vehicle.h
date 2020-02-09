#pragma once

#include "Person.h"

namespace assignment2
{
	class Vehicle
	{
		friend Airplane;
	public:
		Vehicle(unsigned int maxPassengersCount);
		Vehicle(const Vehicle& other);
		~Vehicle();

		virtual unsigned int GetMaxSpeed() const = 0;

		bool AddPassenger(const Person* person);
		bool RemovePassenger(unsigned int i);
		const Person* GetPassenger(unsigned int i) const;
		unsigned int GetPassengersCount() const;
		unsigned int GetMaxPassengersCount() const;

	protected:
		const unsigned int mMaxPassengerCount = 10;
		unsigned int mCount;
		const Person** mPassengers;
	};
}