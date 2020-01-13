#include "Lab2.h"
#include <iomanip>

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		out << std::setw(12) << "oct" << ' '
			<< std::setw(12) << "dec" << ' '
			<< std::setw(8) << "hex" << std::endl;

		out << "------------" << ' '
			<< "------------" << ' '
			<< "--------" << ' ' << std::endl;

		int number = 0;
		while (true)
		{
			in >> number;

			if (in.eof())
				break;

			if (in.fail())
			{
				in.clear();
				in.ignore();
			}
			else
			{
				out << std::uppercase
					<< std::setw(12) << std::oct << number << ' '
					<< std::setw(12) << std::dec << number << ' '
					<< std::setw(8) << std::hex << number << std::endl;
			}
		}

		in.clear();
	}

	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		float number = 0;
		float maxNum = 0;

		out.setf(std::ios::fixed);
		out.precision(3);

		while (true)
		{
			in >> number;

			if (in.eof())
				break;

			if (in.fail())
			{
				in.clear();
				in.ignore();
			}
			else
			{
				if (number > maxNum)
					maxNum = number;

				out << "     " << std::setw(15)
					<< std::internal << std::showpos << number << std::endl;
			}
		}

		out << "max: " << std::setw(15)
			<< std::internal << std::showpos << maxNum << std::endl;

		in.clear();
	}
}
