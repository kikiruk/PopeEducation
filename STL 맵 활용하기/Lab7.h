#pragma once

#include <iostream> // 표준 입출력을 위해 포함
#include <vector>   // 벡터 자료구조 사용을 위해 포함
#include <map>      // 맵 자료구조 사용을 위해 포함
#include <set>      // 집합 자료구조 사용을 위해 포함
#include <algorithm> // 알고리즘 함수들을 사용하기 위해 포함

namespace lab7
{
    // 두 벡터를 맵으로 변환하는 템플릿 함수
    // 첫 번째 벡터를 키로, 두 번째 벡터를 값으로 매핑
    template <typename K, class V>
    std::map<K, V> ConvertVectorsToMap(const std::vector<K>& keys, const std::vector<V>& values)
    {
        std::map<K, V> m;

        // 두 벡터의 크기 중 작은 것을 기준으로 반복
        size_t roop = std::min(keys.size(), values.size());

        // 각 키와 값을 맵에 삽입
        for (size_t i = 0; i < roop; i++)
            m.insert(std::pair<K, V>(keys[i], values[i]));

        return m; // 완성된 맵 반환
    }

    // 맵의 키를 벡터로 추출하는 템플릿 함수
    template <typename K, class V>
    std::vector<K> GetKeys(const std::map<K, V>& m)
    {
        std::vector<K> v;
        v.reserve(m.size()); // 벡터의 크기를 미리 예약

        // 맵의 각 항목에서 키만 추출하여 벡터에 저장
        for (auto i = m.begin(); i != m.end(); i++)
            v.push_back(i->first);

        return v; // 키들로 구성된 벡터 반환
    }

    // 맵의 값을 벡터로 추출하는 템플릿 함수
    template <typename K, class V>
    std::vector<V> GetValues(const std::map<K, V>& m)
    {
        std::vector<V> v;
        v.reserve(m.size()); // 벡터의 크기를 미리 예약

        // 맵의 각 항목에서 값만 추출하여 벡터에 저장
        for (auto i = m.begin(); i != m.end(); i++)
            v.push_back(i->second);

        return v; // 값들로 구성된 벡터 반환
    }

    // 벡터를 반대로 뒤집는 템플릿 함수
    template <typename T>
    std::vector<T> Reverse(const std::vector<T>& v)
    {
        std::vector<T> rv;
        rv.reserve(v.capacity()); // 반환할 벡터의 크기를 미리 예약

        // 벡터의 마지막 요소부터 첫 번째 요소까지 역순으로 삽입
        for (size_t i = v.size() - 1; true; i--)
        {
            rv.push_back(v[i]);

            if (i == 0)
                break; // 첫 번째 요소까지 삽입 후 종료
        }

        return rv; // 뒤집어진 벡터 반환
    }

    // 두 벡터를 합쳐서 중복을 제거한 새로운 벡터를 반환하는 연산자 오버로딩
    template <typename T>
    std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
    {
        std::vector<T> combined;
        std::set<T> duplicateCheck; // 중복 확인을 위한 집합
        combined.reserve(v1.capacity() + v2.capacity()); // 합쳐진 벡터의 크기를 미리 예약

        const std::vector<T>* vectors[2] = { &v1, &v2 };
        size_t roop = 0;
        // 두 벡터를 순차적으로 순회하면서 중복을 체크하며 요소를 삽입
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

        return combined; // 합쳐진 벡터 반환
    }

    // 두 맵을 합쳐서 새로운 맵을 반환하는 연산자 오버로딩
    template <typename K, class V>
    std::map<K, V> operator+(const std::map<K, V>& m1, const std::map<K, V>& m2)
    {
        std::map<K, V> combined(m1); // 첫 번째 맵으로 초기화

        // 두 번째 맵의 모든 항목을 삽입
        for (auto i = m2.begin(); i != m2.end(); i++)
            combined.insert(*i);

        return combined; // 합쳐진 맵 반환
    }

    // 벡터의 요소를 출력하는 연산자 오버로딩
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
    {
        typename std::vector<T>::const_iterator i = v.begin();
        os << *(i++); // 첫 번째 요소 출력

        // 나머지 요소들을 쉼표로 구분하여 출력
        for (; i != v.end(); i++)
            os << ", " << *i;

        return os;
    }

    // 맵의 요소를 출력하는 연산자 오버로딩
    template <typename K, class V>
    std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
    {
        // 각 맵의 항목을 {키, 값} 형태로 출력
        for (auto i = m.begin(); i != m.end(); i++)
            os << "{ " << i->first << ", " << i->second << " }" << std::endl;

        return os;
    }
}