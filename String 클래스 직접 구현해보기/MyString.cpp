#include "MyString.h"
#include <assert.h>

namespace assignment1
{
	// 생성자: 문자열을 받아와서 MyString 객체를 초기화합니다.
	MyString::MyString(const char* s)
	{
		mLength = calculateLength(s); // 문자열의 길이를 계산합니다.
		mS = strCopyFactory(s, mLength + 1); // 문자열을 동적으로 복사합니다.
	}

	// 복사 생성자: 다른 MyString 객체를 복사하여 새로운 객체를 만듭니다.
	MyString::MyString(const MyString& other)
	{
		mLength = calculateLength(other.GetCString()); // 다른 객체의 문자열 길이를 계산합니다.
		mS = strCopyFactory(other.GetCString(), mLength + 1); // 다른 객체의 문자열을 복사합니다.
	}

	// 소멸자: 동적으로 할당된 메모리를 해제합니다.
	MyString::~MyString()
	{
		delete[] mS;
	}

	// 문자열의 길이를 반환하는 메서드입니다.
	unsigned int MyString::GetLength() const
	{
		return mLength;
	}

	// 저장된 C 문자열을 반환하는 메서드입니다.
	const char* MyString::GetCString() const
	{
		return mS;
	}

	// 주어진 문자열을 현재 문자열에 추가합니다.
	void MyString::Append(const char* s)
	{
		if (calculateLength(s) == 0) // 추가할 문자열이 빈 문자열일 경우 아무 것도 하지 않습니다.
		{
			return;
		}

		char* tmp = mS; // 현재 문자열을 임시로 저장합니다.
		unsigned int newLength = mLength + calculateLength(s); // 새로운 문자열 길이를 계산합니다.
		mS = new char[newLength + 1]; // 새로운 길이에 맞게 메모리를 할당합니다.

		// 기존 문자열을 새로운 메모리로 복사합니다.
		for (unsigned int i = 0; i < mLength; i++)
		{
			mS[i] = tmp[i];
		}

		// 추가할 문자열을 뒤에 복사합니다.
		for (unsigned int i = mLength; i < newLength + 1; i++)
		{
			mS[i] = s[i - mLength];
		}

		mLength = newLength; // 문자열 길이를 갱신합니다.
		delete[] tmp; // 임시 메모리를 해제합니다.
	}

	// 더하기 연산자 오버로드: 두 문자열을 합쳐서 새로운 MyString 객체를 반환합니다.
	MyString MyString::operator+(const MyString& other) const
	{
		MyString tmp(*this); // 현재 객체를 복사합니다.
		tmp.Append(other.GetCString()); // 복사한 객체에 다른 객체의 문자열을 추가합니다.

		return tmp; // 새로운 MyString 객체를 반환합니다.
	}

	// 문자열 내에서 특정 문자열의 첫 번째 위치를 찾습니다.
	int MyString::IndexOf(const char* s) const
	{
		unsigned int lengthOfs = calculateLength(s); // 찾을 문자열의 길이를 계산합니다.

		if (lengthOfs == 0) // 찾을 문자열이 빈 문자열일 경우 0을 반환합니다.
		{
			return 0;
		}

		if (mLength < lengthOfs) // 찾을 문자열이 현재 문자열보다 길 경우 -1을 반환합니다.
		{
			return -1;
		}

		// 현재 문자열에서 찾을 문자열을 검색합니다.
		for (unsigned int i = 0; i <= mLength - lengthOfs; i++)
		{
			bool bCheck = true;
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j]) // 문자가 일치하지 않으면 검색 중지
				{
					bCheck = false;
					break;
				}
			}

			if (bCheck) // 문자열을 찾았을 경우 해당 위치를 반환합니다.
			{
				return i;
			}
		}

		return -1; // 문자열을 찾지 못했을 경우 -1을 반환합니다.
	}

	// 문자열 내에서 특정 문자열의 마지막 위치를 찾습니다.
	int MyString::LastIndexOf(const char* s) const
	{
		unsigned int lengthOfs = calculateLength(s); // 찾을 문자열의 길이를 계산합니다.

		if (mLength < lengthOfs) // 찾을 문자열이 현재 문자열보다 길 경우 -1을 반환합니다.
		{
			return -1;
		}

		if (lengthOfs == 0) // 찾을 문자열이 빈 문자열일 경우 문자열의 길이를 반환합니다.
		{
			return mLength;
		}

		// 문자열을 역방향으로 검색합니다.
		for (long i = static_cast<int>(mLength - lengthOfs); i >= 0; i--)
		{
			bool bCheck = true;
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j]) // 문자가 일치하지 않으면 검색 중지
				{
					bCheck = false;
					break;
				}
			}

			if (bCheck) // 문자열을 찾았을 경우 해당 위치를 반환합니다.
			{
				return i;
			}
		}

		return -1; // 문자열을 찾지 못했을 경우 -1을 반환합니다.
	}

	// 현재 문자열과 주어진 문자열을 교차하여 새로운 문자열을 만듭니다.
	void MyString::Interleave(const char* s)
	{
		unsigned int sLength = calculateLength(s); // 주어진 문자열의 길이를 계산합니다.

		if (sLength == 0) // 주어진 문자열이 빈 문자열일 경우 아무것도 하지 않습니다.
		{
			return;
		}

		unsigned int currentMLength = mLength; // 현재 문자열의 길이를 저장합니다.
		char* currentMS = mS; // 현재 문자열을 임시로 저장합니다.
		mLength += sLength; // 새로운 길이를 설정합니다.
		mS = new char[mLength + 1]; // 새로운 길이에 맞게 메모리를 할당합니다.

		// 두 문자열을 교차하여 복사합니다.
		for (unsigned int i = 0, j = 0; true; i++)
		{
			if (j >= mLength) // 문자열을 모두 교차하여 복사했을 경우 종료합니다.
			{
				mS[mLength] = '\0';
				delete[] currentMS; // 임시 메모리를 해제합니다.
				return;
			}

			if (i < currentMLength) // 현재 문자열에서 문자를 복사합니다.
			{
				assert(mLength >= j);
				mS[j] = currentMS[i];
				j++;
			}

			if (i < sLength) // 주어진 문자열에서 문자를 복사합니다.
			{
				assert(mLength >= j);
				mS[j] = s[i];
				j++;
			}
		}
	}

	// 주어진 인덱스의 문자를 제거합니다.
	bool MyString::RemoveAt(unsigned int index)
	{
		if (index < mLength) // 인덱스가 유효할 경우
		{
			for (unsigned int i = index + 1; i < mLength + 1; i++)
			{
				mS[i - 1] = mS[i]; // 문자를 제거하고, 그 뒤의 문자를 앞으로 이동합니다.
			}
			mLength -= 1; // 문자열 길이를 감소시킵니다.

			return true;
		}
		else // 인덱스가 유효하지 않을 경우
		{
			return false;
		}
	}

	// 왼쪽에 공백을 추가하여 문자열의 총 길이를 늘립니다.
	void MyString::PadLeft(unsigned int totalLength)
	{
		PadLeft(totalLength, ' '); // 기본 공백 문자 ' '를 사용합니다.
	}

	// 왼쪽에 주어진 문자를 추가하여 문자열의 총 길이를 늘립니다.
	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		if (totalLength <= mLength) // 총 길이가 현재 길이보다 짧거나 같으면 아무것도 하지 않습니다.
		{
			return;
		}

		char* tmp = mS; // 현재 문자열을 임시로 저장합니다.
		mS = new char[totalLength + 1]; // 새로운 길이에 맞게 메모리를 할당합니다.
		unsigned int endIndex = totalLength - mLength;

		// 왼쪽에 문자를 추가합니다.
		for (unsigned int i = 0; i < endIndex; i++)
			mS[i] = c;

		// 기존 문자열을 뒤에 복사합니다.
		for (unsigned int i = endIndex; i <= totalLength; i++)
			mS[i] = tmp[i - endIndex];

		mLength = totalLength; // 문자열 길이를 갱신합니다.

		delete[] tmp; // 임시 메모리를 해제합니다.
	}

	// 오른쪽에 공백을 추가하여 문자열의 총 길이를 늘립니다.
	void MyString::PadRight(unsigned int totalLength)
	{
		PadRight(totalLength, ' '); // 기본 공백 문자 ' '를 사용합니다.
	}

	// 오른쪽에 주어진 문자를 추가하여 문자열의 총 길이를 늘립니다.
	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		if (totalLength <= mLength) // 총 길이가 현재 길이보다 짧거나 같으면 아무것도 하지 않습니다.
		{
			return;
		}

		char* tmp = mS; // 현재 문자열을 임시로 저장합니다.

		mS = new char[totalLength + 1]; // 새로운 길이에 맞게 메모리를 할당합니다.

		// 기존 문자열을 앞쪽에 복사합니다.
		for (unsigned int i = 0; i < mLength; i++)
			mS[i] = tmp[i];

		// 오른쪽에 문자를 추가합니다.
		for (unsigned int i = mLength; i < totalLength; i++)
			mS[i] = c;

		mS[totalLength] = '\0'; // 문자열 끝에 null 문자를 추가합니다.
		mLength = totalLength; // 문자열 길이를 갱신합니다.

		delete[] tmp; // 임시 메모리를 해제합니다.
	}

	// 문자열을 뒤집습니다.
	void MyString::Reverse()
	{
		int tmp = 0;
		for (unsigned int i = 0; i < mLength / 2; i++)
		{
			tmp = mS[i]; // 임시로 문자를 저장합니다.
			mS[i] = mS[mLength - 1 - i]; // 앞과 뒤의 문자를 교환합니다.
			mS[mLength - 1 - i] = tmp; // 교환한 문자를 설정합니다.
		}
	}

	// 동일성 비교 연산자 오버로드: 두 문자열이 같은지 비교합니다.
	bool MyString::operator==(const MyString& rhs) const
	{
		if (&rhs == this) // 동일 객체 비교
		{
			return true;
		}

		if (rhs.mLength == mLength) // 길이가 같을 경우
		{
			for (unsigned int i = 0; i < mLength + 1; i++)
			{
				if (mS[i] != rhs.GetCString()[i]) // 문자가 하나라도 다르면 false 반환
				{
					return false;
				}
			}

			return true; // 모든 문자가 같을 경우 true 반환
		}

		return false; // 길이가 다를 경우 false 반환
	}

	// 대입 연산자 오버로드: 다른 MyString 객체를 현재 객체에 복사합니다.
	MyString& MyString::operator=(const MyString& rhs)
	{
		if (this != &rhs) // 자기 자신과의 대입을 방지합니다.
		{
			delete[] mS; // 기존 메모리를 해제합니다.
			mLength = calculateLength(rhs.GetCString()); // 복사할 문자열의 길이를 계산합니다.
			mS = strCopyFactory(rhs.GetCString(), mLength + 1); // 문자열을 복사합니다.
		}

		return *this;
	}

	// 문자열을 소문자로 변환합니다.
	void MyString::ToLower()
	{
		for (unsigned int i = 0; i < mLength; i++)
		{
			if (mS[i] >= 65 && mS[i] <= 90) // 대문자일 경우
				mS[i] += 32; // 소문자로 변환합니다.
		}
	}

	// 문자열을 대문자로 변환합니다.
	void MyString::ToUpper()
	{
		for (unsigned int i = 0; i < mLength; i++)
		{
			if (mS[i] >= 97 && mS[i] <= 122) // 소문자일 경우
				mS[i] -= 32; // 대문자로 변환합니다.
		}
	}

	// 문자열의 길이를 계산하는 내부 메서드입니다.
	inline unsigned int MyString::calculateLength(const char* c) const
	{
		unsigned int length = 0;

		for (const char* i = c; *i != '\0'; i++) // null 문자를 만날 때까지 반복합니다.
			length++;

		return length; // 문자열의 길이를 반환합니다.
	}

	// 문자열을 복사하는 내부 메서드입니다.
	inline char* MyString::strCopyFactory(const char* c, const unsigned int length) const
	{
		char* result = new char[length]; // 지정된 길이만큼 메모리를 할당합니다.

		for (unsigned int i = 0; i < length; i++) // 문자열을 복사합니다.
			result[i] = c[i];

		return result; // 복사된 문자열을 반환합니다.
	}
}

