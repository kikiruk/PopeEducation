#include<climits> // INT_MAX�� INT_MIN�� ����ϱ� ���� ����
#include "Lab6.h" // �ش� ������Ʈ�� ��� ���� ����

namespace lab6
{
    // ���� �� ��� ������ ���� ����ϴ� �Լ�
    int Sum(const std::vector<int>& v)
    {
        // ���Ͱ� ����ִ� ���, 0�� ��ȯ
        if (v.empty())
            return 0;

        int answer = 0; // ���� ������ ���� �ʱ�ȭ

        // ������ ��� ��Ҹ� ��ȸ�ϸ� �ջ�
        for (unsigned int i = 0; i < v.size(); i++)
            answer += v[i];

        return answer; // ���� ���� ��ȯ
    }

    // ���� �� ���� ���� ���� ��ȯ�ϴ� �Լ�
    int Min(const std::vector<int>& v)
    {
        int minNum = INT_MAX; // �ּҰ��� ������ ���� �ʱ�ȭ (ó���� ���� ū ������ ����)

        // ������ ��� ��Ҹ� ��ȸ�ϸ� �ּҰ� ã��
        for (unsigned int i = 0; i < v.size(); i++)
        {
            if (minNum > v[i])
                minNum = v[i];
        }

        return minNum; // ���� �ּҰ� ��ȯ
    }

    // ���� �� ���� ū ���� ��ȯ�ϴ� �Լ�
    int Max(const std::vector<int>& v)
    {
        int maxNum = INT_MIN; // �ִ밪�� ������ ���� �ʱ�ȭ (ó���� ���� ���� ������ ����)

        // ������ ��� ��Ҹ� ��ȸ�ϸ� �ִ밪 ã��
        for (unsigned int i = 0; i < v.size(); i++)
        {
            if (maxNum < v[i])
                maxNum = v[i];
        }

        return maxNum; // ���� �ִ밪 ��ȯ
    }

    // ������ ��հ��� ����Ͽ� ��ȯ�ϴ� �Լ�
    float Average(const std::vector<int>& v)
    {
        // ���Ͱ� ����ִ� ���, 0.0f�� ��ȯ
        if (v.empty())
            return 0.0f;

        // ���� ����ϰ�, ��� ������ ������ ����� ����
        return static_cast<float>(Sum(v)) / v.size();
    }

    // ���� ������ ���� ���� �����ϴ� ���� ��ȯ�ϴ� �Լ�
    int NumberWithMaxOccurrence(const std::vector<int>& v)
    {
        int answer = 0; // ���� ���� �����ϴ� ���� ������ ����
        int numberNow = 0; // ���� �� ���� ��
        int numberCount = 0; // ���� ���� ���� Ƚ��
        int maxCount = 0; // ���� ���� ������ ���� Ƚ��

        // ������ �� ��Ҹ� ��ȸ
        for (auto i = v.begin(); i != v.end(); i++)
        {
            numberNow = *i; // ���� ��� ����
            numberCount = 0; // ���� Ƚ�� �ʱ�ȭ

            // ���� ��ҿ� ������ ��ҵ��� ���Ͽ� ���� Ƚ�� ���
            for (auto j = i + 1; j != v.end(); j++)
            {
                if (numberNow == *j)
                    numberCount++;
            }

            // �ִ� ���� Ƚ���� ������ ���, answer�� ���� ������ ����
            if (maxCount < numberCount)
            {
                maxCount = numberCount;
                answer = numberNow;
            }
        }

        return answer; // ���� ���� �����ϴ� �� ��ȯ
    }

    // ���͸� ������������ �����ϴ� �Լ�
    void SortDescending(std::vector<int>& v)
    {
        quickSort(0, v.size() - 1, v); // �� ������ �̿��Ͽ� ���� ����
    }

    // �� ������ ������ �Լ�
    void quickSort(int left, int right, std::vector<int>& v)
    {
        int pivot = left; // �ǹ��� ���� ������ ����
        int j = pivot; // �ǹ��� ��ġ�� ��Ÿ�� �ε���
        int i = left + 1; // ���� �� �������� ����
        int tmp; // ��ȯ�� ���� �ӽ� ����

        // ���� �ε����� ������ �ε������� ���� ���� ���� ����
        if (left < right)
        {
            // �ǹ����� ū ���� ã�Ƽ� ����
            for (; i <= right; i++)
            {
                if (v[i] > v[pivot])
                {
                    j++;
                    tmp = v[j];
                    v[j] = v[i];
                    v[i] = tmp;
                }
            }
            // �ǹ��� �߰����� �̵�
            tmp = v[left];
            v[left] = v[j];
            v[j] = tmp;
            pivot = j;

            // �ǹ� �������� �¿�� ���� ��������� ���� ����
            quickSort(left, pivot - 1, v);
            quickSort(pivot + 1, right, v);
        }
    }
}