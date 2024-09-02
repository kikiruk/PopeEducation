#pragma once

#include <iostream> // ǥ�� ������� ���� ����
#include <vector>   // ���� �ڷᱸ�� ����� ���� ����
#include <map>      // �� �ڷᱸ�� ����� ���� ����
#include <set>      // ���� �ڷᱸ�� ����� ���� ����
#include <algorithm> // �˰��� �Լ����� ����ϱ� ���� ����

namespace lab7
{
    // �� ���͸� ������ ��ȯ�ϴ� ���ø� �Լ�
    // ù ��° ���͸� Ű��, �� ��° ���͸� ������ ����
    template <typename K, class V>
    std::map<K, V> ConvertVectorsToMap(const std::vector<K>& keys, const std::vector<V>& values)
    {
        std::map<K, V> m;

        // �� ������ ũ�� �� ���� ���� �������� �ݺ�
        size_t roop = std::min(keys.size(), values.size());

        // �� Ű�� ���� �ʿ� ����
        for (size_t i = 0; i < roop; i++)
            m.insert(std::pair<K, V>(keys[i], values[i]));

        return m; // �ϼ��� �� ��ȯ
    }

    // ���� Ű�� ���ͷ� �����ϴ� ���ø� �Լ�
    template <typename K, class V>
    std::vector<K> GetKeys(const std::map<K, V>& m)
    {
        std::vector<K> v;
        v.reserve(m.size()); // ������ ũ�⸦ �̸� ����

        // ���� �� �׸񿡼� Ű�� �����Ͽ� ���Ϳ� ����
        for (auto i = m.begin(); i != m.end(); i++)
            v.push_back(i->first);

        return v; // Ű��� ������ ���� ��ȯ
    }

    // ���� ���� ���ͷ� �����ϴ� ���ø� �Լ�
    template <typename K, class V>
    std::vector<V> GetValues(const std::map<K, V>& m)
    {
        std::vector<V> v;
        v.reserve(m.size()); // ������ ũ�⸦ �̸� ����

        // ���� �� �׸񿡼� ���� �����Ͽ� ���Ϳ� ����
        for (auto i = m.begin(); i != m.end(); i++)
            v.push_back(i->second);

        return v; // ����� ������ ���� ��ȯ
    }

    // ���͸� �ݴ�� ������ ���ø� �Լ�
    template <typename T>
    std::vector<T> Reverse(const std::vector<T>& v)
    {
        std::vector<T> rv;
        rv.reserve(v.capacity()); // ��ȯ�� ������ ũ�⸦ �̸� ����

        // ������ ������ ��Һ��� ù ��° ��ұ��� �������� ����
        for (size_t i = v.size() - 1; true; i--)
        {
            rv.push_back(v[i]);

            if (i == 0)
                break; // ù ��° ��ұ��� ���� �� ����
        }

        return rv; // �������� ���� ��ȯ
    }

    // �� ���͸� ���ļ� �ߺ��� ������ ���ο� ���͸� ��ȯ�ϴ� ������ �����ε�
    template <typename T>
    std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
    {
        std::vector<T> combined;
        std::set<T> duplicateCheck; // �ߺ� Ȯ���� ���� ����
        combined.reserve(v1.capacity() + v2.capacity()); // ������ ������ ũ�⸦ �̸� ����

        const std::vector<T>* vectors[2] = { &v1, &v2 };
        size_t roop = 0;
        // �� ���͸� ���������� ��ȸ�ϸ鼭 �ߺ��� üũ�ϸ� ��Ҹ� ����
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

        return combined; // ������ ���� ��ȯ
    }

    // �� ���� ���ļ� ���ο� ���� ��ȯ�ϴ� ������ �����ε�
    template <typename K, class V>
    std::map<K, V> operator+(const std::map<K, V>& m1, const std::map<K, V>& m2)
    {
        std::map<K, V> combined(m1); // ù ��° ������ �ʱ�ȭ

        // �� ��° ���� ��� �׸��� ����
        for (auto i = m2.begin(); i != m2.end(); i++)
            combined.insert(*i);

        return combined; // ������ �� ��ȯ
    }

    // ������ ��Ҹ� ����ϴ� ������ �����ε�
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
    {
        typename std::vector<T>::const_iterator i = v.begin();
        os << *(i++); // ù ��° ��� ���

        // ������ ��ҵ��� ��ǥ�� �����Ͽ� ���
        for (; i != v.end(); i++)
            os << ", " << *i;

        return os;
    }

    // ���� ��Ҹ� ����ϴ� ������ �����ε�
    template <typename K, class V>
    std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
    {
        // �� ���� �׸��� {Ű, ��} ���·� ���
        for (auto i = m.begin(); i != m.end(); i++)
            os << "{ " << i->first << ", " << i->second << " }" << std::endl;

        return os;
    }
}