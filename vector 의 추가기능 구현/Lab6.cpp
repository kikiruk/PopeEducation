#include<climits> // INT_MAX와 INT_MIN을 사용하기 위해 포함
#include "Lab6.h" // 해당 프로젝트의 헤더 파일 포함

namespace lab6
{
    // 벡터 내 모든 정수의 합을 계산하는 함수
    int Sum(const std::vector<int>& v)
    {
        // 벡터가 비어있는 경우, 0을 반환
        if (v.empty())
            return 0;

        int answer = 0; // 합을 저장할 변수 초기화

        // 벡터의 모든 요소를 순회하며 합산
        for (unsigned int i = 0; i < v.size(); i++)
            answer += v[i];

        return answer; // 최종 합을 반환
    }

    // 벡터 내 가장 작은 값을 반환하는 함수
    int Min(const std::vector<int>& v)
    {
        int minNum = INT_MAX; // 최소값을 저장할 변수 초기화 (처음엔 가장 큰 값으로 설정)

        // 벡터의 모든 요소를 순회하며 최소값 찾기
        for (unsigned int i = 0; i < v.size(); i++)
        {
            if (minNum > v[i])
                minNum = v[i];
        }

        return minNum; // 최종 최소값 반환
    }

    // 벡터 내 가장 큰 값을 반환하는 함수
    int Max(const std::vector<int>& v)
    {
        int maxNum = INT_MIN; // 최대값을 저장할 변수 초기화 (처음엔 가장 작은 값으로 설정)

        // 벡터의 모든 요소를 순회하며 최대값 찾기
        for (unsigned int i = 0; i < v.size(); i++)
        {
            if (maxNum < v[i])
                maxNum = v[i];
        }

        return maxNum; // 최종 최대값 반환
    }

    // 벡터의 평균값을 계산하여 반환하는 함수
    float Average(const std::vector<int>& v)
    {
        // 벡터가 비어있는 경우, 0.0f를 반환
        if (v.empty())
            return 0.0f;

        // 합을 계산하고, 요소 개수로 나누어 평균을 구함
        return static_cast<float>(Sum(v)) / v.size();
    }

    // 벡터 내에서 가장 많이 등장하는 값을 반환하는 함수
    int NumberWithMaxOccurrence(const std::vector<int>& v)
    {
        int answer = 0; // 가장 많이 등장하는 값을 저장할 변수
        int numberNow = 0; // 현재 비교 중인 값
        int numberCount = 0; // 현재 값의 등장 횟수
        int maxCount = 0; // 가장 많이 등장한 값의 횟수

        // 벡터의 각 요소를 순회
        for (auto i = v.begin(); i != v.end(); i++)
        {
            numberNow = *i; // 현재 요소 저장
            numberCount = 0; // 등장 횟수 초기화

            // 현재 요소와 나머지 요소들을 비교하여 등장 횟수 계산
            for (auto j = i + 1; j != v.end(); j++)
            {
                if (numberNow == *j)
                    numberCount++;
            }

            // 최대 등장 횟수를 갱신할 경우, answer를 현재 값으로 변경
            if (maxCount < numberCount)
            {
                maxCount = numberCount;
                answer = numberNow;
            }
        }

        return answer; // 가장 많이 등장하는 값 반환
    }

    // 벡터를 내림차순으로 정렬하는 함수
    void SortDescending(std::vector<int>& v)
    {
        quickSort(0, v.size() - 1, v); // 퀵 정렬을 이용하여 정렬 수행
    }

    // 퀵 정렬을 구현한 함수
    void quickSort(int left, int right, std::vector<int>& v)
    {
        int pivot = left; // 피벗을 왼쪽 끝으로 설정
        int j = pivot; // 피벗의 위치를 나타낼 인덱스
        int i = left + 1; // 왼쪽 끝 다음부터 시작
        int tmp; // 교환을 위한 임시 변수

        // 왼쪽 인덱스가 오른쪽 인덱스보다 작은 동안 정렬 진행
        if (left < right)
        {
            // 피벗보다 큰 값을 찾아서 정렬
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
            // 피벗을 중간으로 이동
            tmp = v[left];
            v[left] = v[j];
            v[j] = tmp;
            pivot = j;

            // 피벗 기준으로 좌우로 나눠 재귀적으로 정렬 수행
            quickSort(left, pivot - 1, v);
            quickSort(pivot + 1, right, v);
        }
    }
}