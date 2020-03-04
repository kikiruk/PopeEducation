#include "Lab7.h"

using namespace std;

int main()
{
	std::vector<char> key;
	
	key.push_back('a');
	key.push_back('b');
	key.push_back('c');
	
	std::vector<int> value;
	
	value.push_back(1);
	value.push_back(2);
	value.push_back(3);
	value.push_back(4);
	
	map<char, int> test = lab7::ConvertVectorsToMap<char, int>(key, value);
	
	
	for (auto iter = test.begin(); iter != test.end(); iter++)
	{
		cout << (*iter).first << "," << (*iter).second << endl;
	}


	vector<int> v1;

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;

	v2.push_back(3);
	v2.push_back(2);
	v2.push_back(4);


	vector<int> v3;

	v3 = lab7::operator+(v1, v2);

	for (auto iter = v3.begin(); iter != v3.end(); iter++)
	{
		cout << (*iter) << endl;
	}


	map<char, int> map1;

	map1.insert(pair<char, int>('a', 1));
	map1.insert(pair<char, int>('b', 2));
	map1.insert(pair<char, int>('c', 3));

	map<char, int> map2;

	map2.insert(pair<char, int>('a', 4));
	map2.insert(pair<char, int>('b', 5));
	map2.insert(pair<char, int>('f', 6));

	map<char, int> map3;

	map3 = lab7::operator+(map1, map2);

	for (auto iter = map3.begin(); iter != map3.end(); iter++)
	{
		cout << (*iter).first << "," << (*iter).second << endl;
	}

	lab7::operator<<(cout, v3) << endl;
	lab7::operator<<(cout, map3);
}