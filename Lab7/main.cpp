//#include "Lab7.h"
//
//using namespace std;
//
//int main()
//{
//	std::vector<char> key;
//	
//	key.push_back('a');
//	key.push_back('b');
//	key.push_back('c');
//	
//	std::vector<int> value;
//	
//	value.push_back(1);
//	value.push_back(2);
//	value.push_back(3);
//	value.push_back(4);
//	
//	map<char, int> test = lab7::ConvertVectorsToMap<char, int>(key, value);
//	
//	
//	for (auto iter = test.begin(); iter != test.end(); iter++)
//	{
//		cout << (*iter).first << "," << (*iter).second << endl;
//	}
//
//
//	vector<int> v1;
//
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//
//	vector<int> v2;
//
//	v2.push_back(3);
//	v2.push_back(2);
//	v2.push_back(4);
//
//
//	vector<int> v3;
//
//	v3 = lab7::operator+(v1, v2);
//
//	for (auto iter = v3.begin(); iter != v3.end(); iter++)
//	{
//		cout << (*iter) << endl;
//	}
//
//
//	map<char, int> map1;
//
//	map1.insert(pair<char, int>('a', 1));
//	map1.insert(pair<char, int>('b', 2));
//	map1.insert(pair<char, int>('c', 3));
//
//	map<char, int> map2;
//
//	map2.insert(pair<char, int>('a', 4));
//	map2.insert(pair<char, int>('b', 5));
//	map2.insert(pair<char, int>('f', 6));
//
//	map<char, int> map3;
//
//	map3 = lab7::operator+(map1, map2);
//
//	for (auto iter = map3.begin(); iter != map3.end(); iter++)
//	{
//		cout << (*iter).first << "," << (*iter).second << endl;
//	}
//
//	lab7::operator<<(cout, v3) << endl;
//	lab7::operator<<(cout, map3);
//}

#include <cassert>

#include "Lab7.h"

using namespace lab7;

int main()
{
	std::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	std::vector<char> v2;
	v2.push_back('a');
	v2.push_back('b');
	v2.push_back('c');

	std::vector<int> v3;
	v3.push_back(4);
	v3.push_back(5);
	v3.push_back(6);

	std::map<char, int> m1;
	m1['a'] = 1;
	m1['b'] = 2;
	m1['c'] = 3;

	std::map<char, int> m2;
	m2['d'] = 4;
	m2['e'] = 5;
	m2['f'] = 6;

	std::map<int, char> m = lab7::ConvertVectorsToMap(v1, v2);
	{
		std::map<int, char>::const_iterator it = m.begin();

		assert(it->first == 1);
		assert(it->second == 'a');
		it++;
		assert(it->first == 2);
		assert(it->second == 'b');
		it++;
		assert(it->first == 3);
		assert(it->second == 'c');
	}

	std::vector<char> keys = lab7::GetKeys(m1);
	{
		std::vector<char>::const_iterator it = keys.begin();

		assert(*it == 'a');
		it++;
		assert(*it == 'b');
		it++;
		assert(*it == 'c');
	}

	std::vector<int> values = lab7::GetValues(m1);
	{
		std::vector<int>::const_iterator it = values.begin();

		assert(*it == 1);
		it++;
		assert(*it == 2);
		it++;
		assert(*it == 3);
	}

	std::vector<int> reversedV1 = lab7::Reverse(v1);
	{
		assert(reversedV1[0] == v1[2]);
		assert(reversedV1[1] == v1[1]);
		assert(reversedV1[2] == v1[0]);
	}

	std::vector<int> combinedVector = v1 + v3;
	{
		assert(combinedVector.size() == 6);
		assert(combinedVector[0] == 1);
		assert(combinedVector[1] == 2);
		assert(combinedVector[2] == 3);
		assert(combinedVector[3] == 4);
		assert(combinedVector[4] == 5);
		assert(combinedVector[5] == 6);
	}

	std::map<char, int> combinedMap = m1 + m2;
	{
		std::map<char, int>::const_iterator it = combinedMap.begin();

		assert(combinedMap.size() == 6);

		assert(it->first == 'a');
		assert(it->second == 1);
		it++;
		assert(it->first == 'b');
		assert(it->second == 2);
		it++;
		assert(it->first == 'c');
		assert(it->second == 3);
		it++;
		assert(it->first == 'd');
		assert(it->second == 4);
		it++;
		assert(it->first == 'e');
		assert(it->second == 5);
		it++;
		assert(it->first == 'f');
		assert(it->second == 6);
	}

	std::cout << v1 << std::endl;
	std::cout << m1 << std::endl;

	return 0;
}