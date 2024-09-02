#include "Lab2.h"
#include <iomanip> // 입출력 조작을 위한 헤더

namespace lab2
{
	// PrintIntegers: 입력 스트림에서 정수를 읽고, 8진수, 10진수, 16진수 형식으로 출력
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		// 출력 헤더 설정
		out << std::setw(12) << "oct" << ' ' // 12자리 폭으로 8진수 출력
			<< std::setw(10) << "dec" << ' ' // 10자리 폭으로 10진수 출력
			<< std::setw(8) << "hex" << std::endl; // 8자리 폭으로 16진수 출력

		// 구분선 출력
		out << "------------" << ' '
			<< "----------" << ' '
			<< "--------" << std::endl;

		int number = 0;

		// 입력 스트림에서 정수를 반복적으로 읽어 처리
		while (true)
		{
			in >> number; // 입력 스트림에서 정수를 읽음

			// 입력에 실패했을 경우 처리
			if (in.fail())
			{
				if (in.eof()) // 파일의 끝에 도달하면 반복문 종료
					break;

				in.clear(); // 입력 스트림 상태를 초기화
				in.ignore(); // 잘못된 입력 무시
			}
			else
			{
				// 읽은 정수를 8진수, 10진수, 16진수로 출력
				out << std::uppercase // 16진수에서 대문자 사용
					<< std::setw(12) << std::oct << number << ' ' // 8진수 출력
					<< std::setw(10) << std::dec << number << ' ' // 10진수 출력
					<< std::setw(8) << std::hex << number << std::endl; // 16진수 출력
			}
		}

		in.clear(); // 입력 스트림 상태를 초기화
	}

	// PrintMaxFloat: 입력 스트림에서 실수를 읽고, 가장 큰 값을 찾아 출력
	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		float number = 0;
		float maxNum = -FLT_MAX; // 초기 최대값을 가장 작은 값으로 설정

		// 고정 소수점 형식과 소수점 이하 3자리 설정
		out.setf(std::ios::fixed);
		out.precision(3);

		// 입력 스트림에서 실수를 반복적으로 읽어 처리
		while (true)
		{
			in >> number; // 입력 스트림에서 실수를 읽음

			// 읽은 실수가 현재 최대값보다 크면 최대값 갱신
			if (number > maxNum)
				maxNum = number;

			// 입력에 실패했을 경우 처리
			if (in.fail())
			{
				if (in.eof()) // 파일의 끝에 도달하면 반복문 종료
					break;

				in.clear(); // 입력 스트림 상태를 초기화
				in.ignore(); // 잘못된 입력 무시
			}
			else
			{
				// 실수를 고정 소수점 형식으로 출력
				out << "     " << std::setw(15)
					<< std::internal << std::showpos << number << std::endl;
			}
		}

		// 최대값을 출력
		out << "max: " << std::setw(15)
			<< std::internal << std::showpos << maxNum << std::endl;

		in.clear(); // 입력 스트림 상태를 초기화
	}
}