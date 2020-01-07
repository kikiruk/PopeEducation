#include <string>
#include <iostream>
#include "MyString.h"

using namespace std;
using namespace assignment1;

void test();
void print(const MyString& Ms)
{
	cout << "���ڿ� : " << Ms.GetCString() << endl;
	cout << "mLength : " << Ms.GetLength() << endl;
}

int main()
{
	//MyString Ms1("Hello World");
	//MyString Ms2(Ms1);
	//print(Ms2);
	//Ms1.LastIndexOf("");
	//print(Ms1);

	test();
	return 0;
}


void test()
{
	assignment1::MyString test("");
	while (true)
	{
		int input;
		char input_2[100];
		char forChad;
		cin >> input;

		switch (input)
		{
		case 0:
			cout <<
				"01 : unsigned int GetLength() const" << endl <<
				"02 : const char* GetCString() const" << endl <<
				"03 : void Append(const char* s)" << endl <<
				"04 : MyString operator+(const MyString & other) const" << endl <<
				"05 : int IndexOf(const char* s)" << endl <<
				"06 : int LastIndexOf(const char* s)" << endl <<
				"07 : void Interleave(const char* s)" << endl <<
				"08 : bool RemoveAt(unsigned int i)" << endl <<
				"09 : void PadLeft(unsigned int totalLength)" << endl <<
				"10 : void PadLeft(unsigned int totalLength, const char c)" << endl <<
				"11 : void PadRight(unsigned int totalLength)" << endl <<
				"12 : void PadRight(unsigned int totalLength, const char c)" << endl <<
				"13 : void Reverse()" << endl <<
				"14 : bool operator==(const MyString & rhs) const" << endl <<
				"15 : MyString& operator=(const MyString & rhs)" << endl <<
				"16 : void ToLower()" << endl <<
				"17 : void ToUpper()" << endl <<
				"18 : void print(test)" << endl;
			break;
		case 1:
			cout << test.GetLength() << endl;
			break;
		case 2:
			cout << test.GetCString() << endl;
			break;
		case 3:
			cout << "�ڿ� �߰��� ���ڿ� : ";
			cin >> input_2;
			test.Append(input_2);
			print(test);
			break;
		case 4:
			cout << "�ڿ� �߰��� ���ڿ� : ";
			cin >> input_2;
			test.operator+(assignment1::MyString(input_2));
			print(test);
			break;
		case 5:
			cout << "�տ������� �˻� �� ���ڿ� : ";
			cin >> input_2;
			cout << test.IndexOf(input_2) << endl;
			break;
		case 6:
			cout << "�ڿ������� �˻� �� ���ڿ� : ";
			cin >> input_2;
			cout << test.LastIndexOf(input_2) << endl;
			break;
		case 7:
			cout << "���� ���ڿ� �Է� : ";
			cin >> input_2;
			test.Interleave(input_2);
			print(test);
			break;
		case 8:
			cout << "���� index �Է� : ";
			cin >> input;
			test.RemoveAt(input);
			print(test);
			break;
		case 9:
			cout << "pad�� Ƚ�� : ";
			cin >> input;
			test.PadLeft(input);
			print(test);
			break;
		case 10:
			cout << "pad�� Ƚ�� : ";
			cin >> input;
			cout << "pad�� �����ϳ� : ";
			cin >> forChad;
			test.PadLeft(input, forChad);
			print(test);
			break;
		case 11:
			cout << "pad�� Ƚ�� : ";
			cin >> input;
			test.PadRight(input);
			print(test);
			break;
		case 12:
			cout << "pad�� Ƚ�� : ";
			cin >> input;
			cout << "pad�� �����ϳ� : ";
			cin >> forChad;
			test.PadRight(input, forChad);
			print(test);
			break;
		case 13:
			cout << "Reverce ����" << endl;
			test.Reverse();
			print(test);
			break;
		case 14:
			cout << "���� ���� : " << endl;
			print(test);
			cout << "���� ���ڿ� : ";
			cin >> input_2;
			cout << test.operator==(assignment1::MyString(input_2)) << endl;
			break;
		case 15:
			cout << "������ ���ڿ� : ";
			cin >> input_2;
			test.operator=(assignment1::MyString(input_2));
			print(test);
			break;
		case 16:
			cout << "ToLower()" << endl;
			test.ToLower();
			print(test);

			break;
		case 17:
			cout << "ToUpper()" << endl;
			test.ToUpper();
			print(test);
			break;
		case 18:
			cout << "print(test)" << endl;
			print(test);
			break;

		case 19:
			return;

		default:
			break;
		}
	}

}
