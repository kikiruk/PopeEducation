#include "Person.h"

namespace assignment2
{
	Person::Person(const char* name, unsigned int weight) :
		mName(name),
		mWeight(weight)
	{
	}

	Person::Person(const Person& other) :
		mName(other.mName),
		mWeight(other.mWeight)
	{
	}

	Person::Person() :
		mName(std::string()),
		mWeight(0)
	{
	}

	const std::string& Person::GetName() const
	{
		return mName;
	}

	unsigned int Person::GetWeight() const
	{
		return mWeight;
	}
}
