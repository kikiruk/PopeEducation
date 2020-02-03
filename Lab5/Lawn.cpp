#include "Lawn.h"
#include "eGrassType.h"


namespace lab5
{
	unsigned int Lawn::GetGrassPrice(eGrassType grassType) const
	{
		double price = 0;

		switch (grassType)
		{
		case eGrassType::BERMUDA :
			price = 8;
			break;

		case eGrassType::BAHIA :
			price = 5;
			break;

		case eGrassType::BENTGRASS :
			price = 3;
			break;

		case eGrassType::PERENNIAL_RYEGRASS :
			price = 2.5;
			break;

		case eGrassType::ST_AUGUSTINE:
			price = 4.5;
			break;

		default:
			break;
		}

		price *= GetArea();

		return price + 0.5;
	}

	unsigned int Lawn::GetMinimumSodRollsCount() const
	{
		return GetArea() / 0.3 + 0.5;
	}
}