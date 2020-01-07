#pragma once
namespace assignment1
{
	class MyString
	{

	public:
		MyString(const char* s);
		MyString(const MyString& other);
		~MyString();

		inline unsigned int GetLength() const;
		inline const char* GetCString() const;
		void Append(const char* s);
		MyString operator+(const MyString& other) const;
		int IndexOf(const char* s) const;
		int LastIndexOf(const char* s) const;
		void Interleave(const char* s);
		bool RemoveAt(unsigned int i);
		void PadLeft(unsigned int totalLength);
		void PadLeft(unsigned int totalLength, const char c);
		void PadRight(unsigned int totalLength);
		void PadRight(unsigned int totalLength, const char c);
		void Reverse();
		bool operator==(const MyString& rhs) const;
		MyString& operator=(const MyString& rhs);
		void ToLower();
		void ToUpper();

	private:
		char* mS;
		unsigned int mLength;

		inline unsigned int calculateLength(const char*) const;
		inline char* strCopyFactory(const char* c, const unsigned int length) const;
	};
}