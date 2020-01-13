#include "Lab2.h"
#include <vector>
#include <iomanip>
#include <algorithm>

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		std::vector<int> outPut;
		outPut.reserve(10);

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
				outPut.push_back(number);
			}
		}

		out << std::setw(12) << "oct" << ' '
			<< std::setw(12) << "dec" << ' '
			<< std::setw(8) << "hex" << std::endl;

		out << "------------" << ' '
			<< "------------" << ' '
			<< "------------" << ' ' << std::endl;

		for (size_t i = 0; i < outPut.size(); i++)
		{
			out << std::uppercase
				<< std::setw(12) << std::oct << outPut[i] << ' '
				<< std::setw(12) << std::dec << outPut[i] << ' '
				<< std::setw(8) << std::hex << outPut[i] << std::endl;
		}

		in.clear();
	}

	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		std::vector<float> outPut;
		outPut.reserve(10);

		float number = 0;
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
				outPut.push_back(number);
			}
		}

		out.setf(std::ios::fixed);
		out.precision(3);

		for (size_t i = 0; i < outPut.size(); i++)
		{
			out << "     " << std::setw(15)
				<< std::internal << std::showpos << outPut[i] << std::endl;
		}

		std::sort(outPut.begin(), outPut.end());

		out << "max: " << std::setw(15)
			<< std::internal << std::showpos << outPut[outPut.size() - 1] << std::endl;

		in.clear();
	}
}
