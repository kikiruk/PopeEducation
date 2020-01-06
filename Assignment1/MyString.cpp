#include "MyString.h"

namespace assignment1
{
	MyString::MyString(const char* s)
	{
		mLength = calculateLength(s);
		mS = new char[mLength + 1];
		strCopy(mS, s);
	}

	MyString::MyString(const MyString& other)
	{
		mLength = other.GetLength();
		mS = new char[other.GetLength() + 1];
		strCopy(mS, other.GetCString());
	}

	MyString::~MyString()
	{
		delete[] mS;
	}

	unsigned int MyString::GetLength() const
	{
		return mLength;
	}

	const char* MyString::GetCString() const
	{
		return mS;
	}

	void MyString::Append(const char* s)
	{
		char* tmp = mS;
		unsigned int newLength = mLength + calculateLength(s);
		mS = new char[newLength + 1];

		for (unsigned int i = 0; i < mLength; i++)
		{
			mS[i] = tmp[i];
		}

		for (unsigned int i = mLength; i < newLength + 1; i++)
		{
			mS[i] = s[i - mLength];
		}

		mLength = newLength;
		delete[] tmp;
	}

	MyString MyString::operator+(const MyString& other) const
	{
		MyString tmp(*this);
		tmp.Append(other.GetCString());

		return tmp;
	}

	int MyString::IndexOf(const char* s)
	{
		unsigned int lengthOfs = calculateLength(s);
		 
		if (mLength < lengthOfs) return -1;

		for (int i = 0; i + lengthOfs - 1 < mLength + 1; i++)
		{
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j])
					continue;
			}

			return i;
		}

		return -1;
	}

	int MyString::LastIndexOf(const char* s)
	{
		unsigned int lengthOfs = calculateLength(s);
		
		if (mLength < lengthOfs) return -1;

		for (unsigned int i = mLength - lengthOfs; i >= 0; i--)
		{
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j])
					continue;
			}

			return i;
		}

		return -1;
	}

	void MyString::Interleave(const char* s)
	{
		unsigned int sLength = calculateLength(s);
		unsigned int currentMLength = mLength;
		const char* currentMS = mS;
		mLength = mLength + sLength;
		mS = new char[mLength + 1];

		for (unsigned int i = 0, j = 0; true; i++)
		{
			if (j >= mLength)
			{
				mS[mLength] = '\0';
				return;
			}

			if (i < currentMLength)
			{
				mS[j] = currentMS[i];
				j++;
			}

			if (i < sLength)
			{
				mS[j] = s[i];
				j++;
			}
		}

		delete[] currentMS;
	}

	bool MyString::RemoveAt(unsigned int index)
	{
		if (index < mLength)
		{
			for (unsigned int i = index + 1; i < mLength + 1; i++)
			{
				mS[i - 1] = mS[i];
			}
			mLength -= 1;

			return true;
		}
		else
		{
			return false;
		}
	}

	void MyString::PadLeft(unsigned int totalLength)
	{
		PadLeft(totalLength, ' ');
	}

	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		char* tmp = new char[mLength + 1];
		strCopy(tmp, mS);
		
		mS = new char[totalLength + mLength + 1];
		mLength += totalLength;

		for (unsigned int i = 0; i < totalLength; i++)
			mS[i] = c;

		for (unsigned int i = totalLength; i < mLength + 1; i++)
			mS[i] = tmp[i - totalLength];

		delete[] tmp;
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		PadRight(totalLength, ' ');
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		char* tmp = new char[mLength + 1];
		strCopy(tmp, mS);

		mS = new char[totalLength + mLength + 1];

		for (unsigned int i = 0; i < mLength; i++)
			mS[i] = tmp[i];

		for (unsigned int i = mLength; i < mLength + totalLength; i++)
			mS[i] = c;

		mS[totalLength + mLength] = '\0';

		mLength += totalLength;

		delete[] tmp;
	}

	void MyString::Reverse()
	{
		int tmp = 0;
		for (unsigned int i = 0; i < mLength / 2; i++)
		{
			tmp = mS[i];
			mS[i] = mS[mLength - 1 - i];
			mS[mLength - 1 - i] = tmp;
		}
	}

	bool MyString::operator==(const MyString& rhs) const
	{
		if (&rhs == this)
		{
			return true;
		}

		if (rhs.mLength == mLength)
		{
			for (unsigned int i = 0; i < mLength + 1; i++)
			{
				if (mS[i] != rhs.GetCString()[i])
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	MyString& MyString::operator=(const MyString& rhs)
	{
		if (this != &rhs) //자기자신 대입 방지
		{
			delete mS;
			mLength = rhs.GetLength();
			mS = new char[mLength + 1];
			strCopy(mS, rhs.GetCString());
		}

		return *this;
	}

	void MyString::ToLower()
	{
		for (unsigned int i = 0; i < mLength; i++)
		{
			if (mS[i] >= 65 && mS[i] <= 90)
				mS[i] += 32;
		}
	}

	void MyString::ToUpper()
	{
		for (unsigned int i = 0; i < mLength; i++)
		{
			if (mS[i] >= 97 && mS[i] <= 122)
				mS[i] -= 32;
		}
	}

	inline unsigned int MyString::calculateLength(const char* c) const
	{
		unsigned int length = 0;

		for (const char* i = c; *i != '\0'; i++)
			length++;

		return length;
	}

	inline void MyString::strCopy(char* s, const char* c)
	{
		unsigned int length = calculateLength(c);

		for (unsigned int i = 0; i < length + 1; i++)
			s[i] = c[i];
	}
}