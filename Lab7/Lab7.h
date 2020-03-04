#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

namespace lab7
{
	template <typename K, class V>
	std::map<K, V> ConvertVectorsToMap(const std::vector<K>& keys, const std::vector<V>& values)
	{
		std::map<K, V> m;

		size_t roop = std::min(keys.size(),values.size());

		for (size_t i = 0; i < roop; i++)
			m.insert(std::pair<K, V>(keys[i], values[i]));

		return m;
	}

	template <typename K, class V>
	std::vector<K> GetKeys(const std::map<K, V>& m)
	{
		std::vector<K> v;
		v.reserve(m.size());

		for (auto i = m.begin(); i != m.end(); i++)
			v.push_back(i->first);

		return v;
	}

	template <typename K, class V>
	std::vector<V> GetValues(const std::map<K, V>& m)
	{
		std::vector<V> v;
		v.reserve(m.size());

		for (auto i = m.begin(); i != m.end(); i++)
			v.push_back(i->second);

		return v;
	}

	template <typename T>
	std::vector<T> Reverse(const std::vector<T>& v)
	{
		std::vector<T> rv;
		rv.reserve(v.capacity());

		for (size_t i = v.size() - 1; true; i--)
		{
			rv.push_back(v[i]);

			if (i == 0) break;
		}

		return rv;
	}

	template <typename T>
	std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
	{
		std::vector<T> combined;
		std::set<T> duplicateCheck;
		combined.reserve(v1.capacity() + v2.capacity());

		const std::vector<T>* vectors[2] = { &v1,&v2 };
		size_t roop = 0;
		for (size_t i = 0; i < 2; i++)
		{
			roop = vectors[i]->size();
			for (size_t j = 0; j < roop; j++)
			{
				if (duplicateCheck.insert((*vectors[i])[j]).second)
				{
					combined.push_back((*vectors[i])[j]);
				}
			}
		}

		return combined;
	}

	template <typename K, class V>
	std::map<K, V> operator+(const std::map<K, V>& m1, const std::map<K, V>& m2)
	{
		std::map<K, V> combined(m1);

		for (auto i = m2.begin(); i != m2.end(); i++)
			combined.insert(*i);

		return combined;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
	{
		typename std::vector<T>::const_iterator i = v.begin();
		os << *(i++);

		for (; i != v.end(); i++)
			os << ", " << *i;

		return os;
	}

	template <typename K, class V>
	std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
	{
		for (auto i = m.begin(); i != m.end(); i++)
			os << "{ " << i->first << ", " << i->second << " }" << std::endl;

		return os;
	}
}