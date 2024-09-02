#include "Lab2.h"
#include <iomanip> // ����� ������ ���� ���

namespace lab2
{
	// PrintIntegers: �Է� ��Ʈ������ ������ �а�, 8����, 10����, 16���� �������� ���
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		// ��� ��� ����
		out << std::setw(12) << "oct" << ' ' // 12�ڸ� ������ 8���� ���
			<< std::setw(10) << "dec" << ' ' // 10�ڸ� ������ 10���� ���
			<< std::setw(8) << "hex" << std::endl; // 8�ڸ� ������ 16���� ���

		// ���м� ���
		out << "------------" << ' '
			<< "----------" << ' '
			<< "--------" << std::endl;

		int number = 0;

		// �Է� ��Ʈ������ ������ �ݺ������� �о� ó��
		while (true)
		{
			in >> number; // �Է� ��Ʈ������ ������ ����

			// �Է¿� �������� ��� ó��
			if (in.fail())
			{
				if (in.eof()) // ������ ���� �����ϸ� �ݺ��� ����
					break;

				in.clear(); // �Է� ��Ʈ�� ���¸� �ʱ�ȭ
				in.ignore(); // �߸��� �Է� ����
			}
			else
			{
				// ���� ������ 8����, 10����, 16������ ���
				out << std::uppercase // 16�������� �빮�� ���
					<< std::setw(12) << std::oct << number << ' ' // 8���� ���
					<< std::setw(10) << std::dec << number << ' ' // 10���� ���
					<< std::setw(8) << std::hex << number << std::endl; // 16���� ���
			}
		}

		in.clear(); // �Է� ��Ʈ�� ���¸� �ʱ�ȭ
	}

	// PrintMaxFloat: �Է� ��Ʈ������ �Ǽ��� �а�, ���� ū ���� ã�� ���
	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		float number = 0;
		float maxNum = -FLT_MAX; // �ʱ� �ִ밪�� ���� ���� ������ ����

		// ���� �Ҽ��� ���İ� �Ҽ��� ���� 3�ڸ� ����
		out.setf(std::ios::fixed);
		out.precision(3);

		// �Է� ��Ʈ������ �Ǽ��� �ݺ������� �о� ó��
		while (true)
		{
			in >> number; // �Է� ��Ʈ������ �Ǽ��� ����

			// ���� �Ǽ��� ���� �ִ밪���� ũ�� �ִ밪 ����
			if (number > maxNum)
				maxNum = number;

			// �Է¿� �������� ��� ó��
			if (in.fail())
			{
				if (in.eof()) // ������ ���� �����ϸ� �ݺ��� ����
					break;

				in.clear(); // �Է� ��Ʈ�� ���¸� �ʱ�ȭ
				in.ignore(); // �߸��� �Է� ����
			}
			else
			{
				// �Ǽ��� ���� �Ҽ��� �������� ���
				out << "     " << std::setw(15)
					<< std::internal << std::showpos << number << std::endl;
			}
		}

		// �ִ밪�� ���
		out << "max: " << std::setw(15)
			<< std::internal << std::showpos << maxNum << std::endl;

		in.clear(); // �Է� ��Ʈ�� ���¸� �ʱ�ȭ
	}
}