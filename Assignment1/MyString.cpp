#include "MyString.h"
#include <assert.h>

namespace assignment1
{
	MyString::MyString(const char* s)
	{
		mLength = calculateLength(s);
		mS = strCopyFactory(s, mLength + 1);
	}

	MyString::MyString(const MyString& other)
	{
		mS = const_cast<char*>(other.GetCString());
		mLength = other.GetLength();
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
		if (calculateLength(s) == 0)
		{
			return;
		}

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

	int MyString::IndexOf(const char* s) const
	{
		unsigned int lengthOfs = calculateLength(s);
		 
		if (lengthOfs == 0)
		{
			return 0;
		}

		if (mLength < lengthOfs)
		{
			return -1;
		}

		bool bCheck = true;
		for (unsigned int i = 0; i <= mLength - lengthOfs; i++)
		{
			bCheck = true;
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j])
				{
					bCheck = false;
					break;
				}
			}

			if (bCheck)
			{
				return i;
			}
		}

		return -1;
	}

	int MyString::LastIndexOf(const char* s) const
	{
		unsigned int lengthOfs = calculateLength(s);
		
		if (mLength < lengthOfs)
		{
			return -1;
		}

		if (lengthOfs == 0)
		{
			return mLength;
		}

		bool bCheck = true;
		for (long i = static_cast<int>(mLength - lengthOfs); i >= 0; i--)
		{
			bCheck = true;
			for (unsigned int j = 0; j < lengthOfs; j++)
			{
				if (mS[i + j] != s[j])
				{
					bCheck = false;
					break;
				}
			}

			if (bCheck)
			{
				return i;
			}
		}

		return -1;
	}

	void MyString::Interleave(const char* s)
	{
		unsigned int sLength = calculateLength(s);

		if (sLength == 0)
		{
			return;
		}

		unsigned int currentMLength = mLength;
		char* currentMS = mS;
		mLength += sLength;
		mS = new char[mLength + 1];

		for (unsigned int i = 0, j = 0; true; i++)
		{
			if (j >= mLength)
			{
				mS[mLength] = '\0';
				delete[] currentMS;
				return;
			}

			if (i < currentMLength)
			{
				assert(mLength >= j);
				mS[j] = currentMS[i];
				j++;
			}

			if (i < sLength)
			{
				assert(mLength >= j);
				mS[j] = s[i];
				j++;
			}
		}

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
		if (totalLength <= mLength)
		{
			return;
		}

		char* tmp = mS;
		mS = new char[totalLength + 1];
		unsigned int endIndex = totalLength - mLength;

		for (unsigned int i = 0; i < endIndex; i++)
			mS[i] = c;

		for (unsigned int i = endIndex; i <= totalLength; i++)
			mS[i] = tmp[i - endIndex];

		mLength = totalLength;

		delete[] tmp;
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		PadRight(totalLength, ' ');
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		if (totalLength <= mLength)
		{
			return;
		}

		char* tmp = mS;

		mS = new char[totalLength + 1];

		for (unsigned int i = 0; i < mLength; i++)
			mS[i] = tmp[i];

		for (unsigned int i = mLength; i < totalLength; i++)
			mS[i] = c;

		mS[totalLength] = '\0';
		mLength = totalLength;

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
			mLength = calculateLength(rhs.GetCString());
			mS = strCopyFactory(rhs.GetCString(), mLength + 1);
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

	inline char* MyString::strCopyFactory(const char* c, const unsigned int length) const
	{
		char* result = new char[length];

		for (unsigned int i = 0; i < length; i++)
			result[i] = c[i];

		return result;
	}
}