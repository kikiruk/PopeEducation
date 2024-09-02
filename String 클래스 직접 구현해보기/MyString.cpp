#include "MyString.h"
#include <assert.h>

namespace assignment1
{
	// ������: ���ڿ��� �޾ƿͼ� MyString ��ü�� �ʱ�ȭ�մϴ�.
	MyString::MyString(const char* s)
	{
		mLength = calculateLength(s); // ���ڿ��� ���̸� ����մϴ�.
		mS = strCopyFactory(s, mLength + 1); // ���ڿ��� �������� �����մϴ�.
	}

	// ���� ������: �ٸ� MyString ��ü�� �����Ͽ� ���ο� ��ü�� ����ϴ�.
	MyString::MyString(const MyString& other)
	{
		mLength = calculateLength(other.GetCString()); // �ٸ� ��ü�� ���ڿ� ���̸� ����մϴ�.
		mS = strCopyFactory(other.GetCString(), mLength + 1); // �ٸ� ��ü�� ���ڿ��� �����մϴ�.
	}

	// �Ҹ���: �������� �Ҵ�� �޸𸮸� �����մϴ�.
	MyString::~MyString()
	{
		delete[] mS;
	}

	// ���ڿ��� ���̸� ��ȯ�ϴ� �޼����Դϴ�.
	unsigned int MyString::GetLength() const
	{
		return mLength;
	}

	// ����� C ���ڿ��� ��ȯ�ϴ� �޼����Դϴ�.
	const char* MyString::GetCString() const
	{
		return mS;
	}

	// �־��� ���ڿ��� ���� ���ڿ��� �߰��մϴ�.
	void MyString::Append(const char* s)
	{
		if (calculateLength(s) == 0) // �߰��� ���ڿ��� �� ���ڿ��� ��� �ƹ� �͵� ���� �ʽ��ϴ�.
		{
			return;
		}

		char* tmp = mS; // ���� ���ڿ��� �ӽ÷� �����մϴ�.
		unsigned int newLength = mLength + calculateLength(s); // ���ο� ���ڿ� ���̸� ����մϴ�.
		mS = new char[newLength + 1]; // ���ο� ���̿� �°� �޸𸮸� �Ҵ��մϴ�.

		// ���� ���ڿ��� ���ο� �޸𸮷� �����մϴ�.
		for (unsigned int i = 0; i < mLength; i++)
		{
			mS[i] = tmp[i];
		}

		// �߰��� ���ڿ��� �ڿ� �����մϴ�.
		for (unsigned int i = mLength; i < newLength + 1; i++)
		{
			mS[i] = s[i - mLength];
		}

		mLength = newLength; // ���ڿ� ���̸� �����մϴ�.
		delete[] tmp; // �ӽ� �޸𸮸� �����մϴ�.
	}

	// ���ϱ� ������ �����ε�: �� ���ڿ��� ���ļ� ���ο� MyString ��ü�� ��ȯ�մϴ�.
	MyString MyString::operator+(const MyString& other) const
	{
		MyString tmp(*this); // ���� ��ü�� �����մϴ�.
		tmp.Append(other.GetCString()); // ������ ��ü�� �ٸ� ��ü�� ���ڿ��� �߰��մϴ�.

		return tmp; // ���ο� MyString ��ü�� ��ȯ�մϴ�.
	}

	// ���ڿ� ������ Ư�� ���ڿ��� ù ��° ��ġ�� ã���ϴ�.
	int MyString::IndexOf(const char* s) const
	{
		unsigned int lengthOfs = calculateLength(s); // ã�� ���ڿ��� ���̸� ����մϴ�.

		if (lengthOfs == 0) // ã�� ���ڿ��� �� ���ڿ��� ��� 0�� ��ȯ�մϴ�.
		{
			return 0;
		}

		if (mLength < lengthOfs) // ã�� ���ڿ��� ���� ���ڿ����� �� ��� -1�� ��ȯ�մϴ�.
		{
			return -1;
		}

		// ���� ���ڿ����� ã�� ���ڿ��� �˻��մϴ�.
		for (unsigned int i = 0; i <= mLength - lengthOfs; i++)
		{
			bool bCheck = true;
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j]) // ���ڰ� ��ġ���� ������ �˻� ����
				{
					bCheck = false;
					break;
				}
			}

			if (bCheck) // ���ڿ��� ã���� ��� �ش� ��ġ�� ��ȯ�մϴ�.
			{
				return i;
			}
		}

		return -1; // ���ڿ��� ã�� ������ ��� -1�� ��ȯ�մϴ�.
	}

	// ���ڿ� ������ Ư�� ���ڿ��� ������ ��ġ�� ã���ϴ�.
	int MyString::LastIndexOf(const char* s) const
	{
		unsigned int lengthOfs = calculateLength(s); // ã�� ���ڿ��� ���̸� ����մϴ�.

		if (mLength < lengthOfs) // ã�� ���ڿ��� ���� ���ڿ����� �� ��� -1�� ��ȯ�մϴ�.
		{
			return -1;
		}

		if (lengthOfs == 0) // ã�� ���ڿ��� �� ���ڿ��� ��� ���ڿ��� ���̸� ��ȯ�մϴ�.
		{
			return mLength;
		}

		// ���ڿ��� ���������� �˻��մϴ�.
		for (long i = static_cast<int>(mLength - lengthOfs); i >= 0; i--)
		{
			bool bCheck = true;
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j]) // ���ڰ� ��ġ���� ������ �˻� ����
				{
					bCheck = false;
					break;
				}
			}

			if (bCheck) // ���ڿ��� ã���� ��� �ش� ��ġ�� ��ȯ�մϴ�.
			{
				return i;
			}
		}

		return -1; // ���ڿ��� ã�� ������ ��� -1�� ��ȯ�մϴ�.
	}

	// ���� ���ڿ��� �־��� ���ڿ��� �����Ͽ� ���ο� ���ڿ��� ����ϴ�.
	void MyString::Interleave(const char* s)
	{
		unsigned int sLength = calculateLength(s); // �־��� ���ڿ��� ���̸� ����մϴ�.

		if (sLength == 0) // �־��� ���ڿ��� �� ���ڿ��� ��� �ƹ��͵� ���� �ʽ��ϴ�.
		{
			return;
		}

		unsigned int currentMLength = mLength; // ���� ���ڿ��� ���̸� �����մϴ�.
		char* currentMS = mS; // ���� ���ڿ��� �ӽ÷� �����մϴ�.
		mLength += sLength; // ���ο� ���̸� �����մϴ�.
		mS = new char[mLength + 1]; // ���ο� ���̿� �°� �޸𸮸� �Ҵ��մϴ�.

		// �� ���ڿ��� �����Ͽ� �����մϴ�.
		for (unsigned int i = 0, j = 0; true; i++)
		{
			if (j >= mLength) // ���ڿ��� ��� �����Ͽ� �������� ��� �����մϴ�.
			{
				mS[mLength] = '\0';
				delete[] currentMS; // �ӽ� �޸𸮸� �����մϴ�.
				return;
			}

			if (i < currentMLength) // ���� ���ڿ����� ���ڸ� �����մϴ�.
			{
				assert(mLength >= j);
				mS[j] = currentMS[i];
				j++;
			}

			if (i < sLength) // �־��� ���ڿ����� ���ڸ� �����մϴ�.
			{
				assert(mLength >= j);
				mS[j] = s[i];
				j++;
			}
		}
	}

	// �־��� �ε����� ���ڸ� �����մϴ�.
	bool MyString::RemoveAt(unsigned int index)
	{
		if (index < mLength) // �ε����� ��ȿ�� ���
		{
			for (unsigned int i = index + 1; i < mLength + 1; i++)
			{
				mS[i - 1] = mS[i]; // ���ڸ� �����ϰ�, �� ���� ���ڸ� ������ �̵��մϴ�.
			}
			mLength -= 1; // ���ڿ� ���̸� ���ҽ�ŵ�ϴ�.

			return true;
		}
		else // �ε����� ��ȿ���� ���� ���
		{
			return false;
		}
	}

	// ���ʿ� ������ �߰��Ͽ� ���ڿ��� �� ���̸� �ø��ϴ�.
	void MyString::PadLeft(unsigned int totalLength)
	{
		PadLeft(totalLength, ' '); // �⺻ ���� ���� ' '�� ����մϴ�.
	}

	// ���ʿ� �־��� ���ڸ� �߰��Ͽ� ���ڿ��� �� ���̸� �ø��ϴ�.
	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		if (totalLength <= mLength) // �� ���̰� ���� ���̺��� ª�ų� ������ �ƹ��͵� ���� �ʽ��ϴ�.
		{
			return;
		}

		char* tmp = mS; // ���� ���ڿ��� �ӽ÷� �����մϴ�.
		mS = new char[totalLength + 1]; // ���ο� ���̿� �°� �޸𸮸� �Ҵ��մϴ�.
		unsigned int endIndex = totalLength - mLength;

		// ���ʿ� ���ڸ� �߰��մϴ�.
		for (unsigned int i = 0; i < endIndex; i++)
			mS[i] = c;

		// ���� ���ڿ��� �ڿ� �����մϴ�.
		for (unsigned int i = endIndex; i <= totalLength; i++)
			mS[i] = tmp[i - endIndex];

		mLength = totalLength; // ���ڿ� ���̸� �����մϴ�.

		delete[] tmp; // �ӽ� �޸𸮸� �����մϴ�.
	}

	// �����ʿ� ������ �߰��Ͽ� ���ڿ��� �� ���̸� �ø��ϴ�.
	void MyString::PadRight(unsigned int totalLength)
	{
		PadRight(totalLength, ' '); // �⺻ ���� ���� ' '�� ����մϴ�.
	}

	// �����ʿ� �־��� ���ڸ� �߰��Ͽ� ���ڿ��� �� ���̸� �ø��ϴ�.
	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		if (totalLength <= mLength) // �� ���̰� ���� ���̺��� ª�ų� ������ �ƹ��͵� ���� �ʽ��ϴ�.
		{
			return;
		}

		char* tmp = mS; // ���� ���ڿ��� �ӽ÷� �����մϴ�.

		mS = new char[totalLength + 1]; // ���ο� ���̿� �°� �޸𸮸� �Ҵ��մϴ�.

		// ���� ���ڿ��� ���ʿ� �����մϴ�.
		for (unsigned int i = 0; i < mLength; i++)
			mS[i] = tmp[i];

		// �����ʿ� ���ڸ� �߰��մϴ�.
		for (unsigned int i = mLength; i < totalLength; i++)
			mS[i] = c;

		mS[totalLength] = '\0'; // ���ڿ� ���� null ���ڸ� �߰��մϴ�.
		mLength = totalLength; // ���ڿ� ���̸� �����մϴ�.

		delete[] tmp; // �ӽ� �޸𸮸� �����մϴ�.
	}

	// ���ڿ��� �������ϴ�.
	void MyString::Reverse()
	{
		int tmp = 0;
		for (unsigned int i = 0; i < mLength / 2; i++)
		{
			tmp = mS[i]; // �ӽ÷� ���ڸ� �����մϴ�.
			mS[i] = mS[mLength - 1 - i]; // �հ� ���� ���ڸ� ��ȯ�մϴ�.
			mS[mLength - 1 - i] = tmp; // ��ȯ�� ���ڸ� �����մϴ�.
		}
	}

	// ���ϼ� �� ������ �����ε�: �� ���ڿ��� ������ ���մϴ�.
	bool MyString::operator==(const MyString& rhs) const
	{
		if (&rhs == this) // ���� ��ü ��
		{
			return true;
		}

		if (rhs.mLength == mLength) // ���̰� ���� ���
		{
			for (unsigned int i = 0; i < mLength + 1; i++)
			{
				if (mS[i] != rhs.GetCString()[i]) // ���ڰ� �ϳ��� �ٸ��� false ��ȯ
				{
					return false;
				}
			}

			return true; // ��� ���ڰ� ���� ��� true ��ȯ
		}

		return false; // ���̰� �ٸ� ��� false ��ȯ
	}

	// ���� ������ �����ε�: �ٸ� MyString ��ü�� ���� ��ü�� �����մϴ�.
	MyString& MyString::operator=(const MyString& rhs)
	{
		if (this != &rhs) // �ڱ� �ڽŰ��� ������ �����մϴ�.
		{
			delete[] mS; // ���� �޸𸮸� �����մϴ�.
			mLength = calculateLength(rhs.GetCString()); // ������ ���ڿ��� ���̸� ����մϴ�.
			mS = strCopyFactory(rhs.GetCString(), mLength + 1); // ���ڿ��� �����մϴ�.
		}

		return *this;
	}

	// ���ڿ��� �ҹ��ڷ� ��ȯ�մϴ�.
	void MyString::ToLower()
	{
		for (unsigned int i = 0; i < mLength; i++)
		{
			if (mS[i] >= 65 && mS[i] <= 90) // �빮���� ���
				mS[i] += 32; // �ҹ��ڷ� ��ȯ�մϴ�.
		}
	}

	// ���ڿ��� �빮�ڷ� ��ȯ�մϴ�.
	void MyString::ToUpper()
	{
		for (unsigned int i = 0; i < mLength; i++)
		{
			if (mS[i] >= 97 && mS[i] <= 122) // �ҹ����� ���
				mS[i] -= 32; // �빮�ڷ� ��ȯ�մϴ�.
		}
	}

	// ���ڿ��� ���̸� ����ϴ� ���� �޼����Դϴ�.
	inline unsigned int MyString::calculateLength(const char* c) const
	{
		unsigned int length = 0;

		for (const char* i = c; *i != '\0'; i++) // null ���ڸ� ���� ������ �ݺ��մϴ�.
			length++;

		return length; // ���ڿ��� ���̸� ��ȯ�մϴ�.
	}

	// ���ڿ��� �����ϴ� ���� �޼����Դϴ�.
	inline char* MyString::strCopyFactory(const char* c, const unsigned int length) const
	{
		char* result = new char[length]; // ������ ���̸�ŭ �޸𸮸� �Ҵ��մϴ�.

		for (unsigned int i = 0; i < length; i++) // ���ڿ��� �����մϴ�.
			result[i] = c[i];

		return result; // ����� ���ڿ��� ��ȯ�մϴ�.
	}
}

