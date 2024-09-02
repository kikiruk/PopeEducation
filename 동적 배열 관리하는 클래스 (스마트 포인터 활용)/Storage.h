#pragma once

#include <memory> // 스마트 포인터 사용을 위해 포함

namespace lab11
{
	// Storage 클래스 템플릿: 동적 배열을 관리하는 클래스
	// T 타입의 데이터를 저장하며, 동적 메모리 관리를 자동으로 처리
	template<typename T>
	class Storage
	{
	public:
		Storage(unsigned int length); // 지정된 길이로 배열을 초기화
		Storage(unsigned int length, const T& initialValue); // 지정된 길이와 초기값으로 배열을 초기화
		Storage(const Storage& other); // 복사 생성자
		Storage(Storage&& other) noexcept; // 이동 생성자
		~Storage() = default; // 소멸자: 기본 소멸자 사용

		const Storage& operator=(const Storage& other); // 복사 대입 연산자
		const Storage& operator=(Storage&& other); // 이동 대입 연산자

		bool Update(unsigned int index, const T& data); // 배열의 특정 인덱스에 데이터를 업데이트
		const std::unique_ptr<T[]>& GetData() const; // 배열 데이터에 대한 const 참조를 반환
		unsigned int GetSize() const; // 배열의 크기를 반환

	private:
		unsigned int mSize; // 배열의 크기
		std::unique_ptr<T[]> mArray; // 동적 배열을 관리하는 스마트 포인터
	};

	// 생성자: 지정된 길이로 배열을 초기화하고, 모든 값을 0으로 설정
	template<typename T>
	Storage<T>::Storage(unsigned int length)
		: mSize(length) // 배열 크기 설정
		, mArray(new T[length]) // 동적 배열 할당
	{
		std::memset(mArray.get(), 0, sizeof(T) * length); // 배열을 0으로 초기화
	}

	// 생성자: 지정된 길이로 배열을 초기화하고, 모든 값을 초기값으로 설정
	template<typename T>
	Storage<T>::Storage(unsigned int length, const T& initialValue)
		: mSize(length) // 배열 크기 설정
		, mArray(new T[length]) // 동적 배열 할당
	{
		for (unsigned int i = 0; i < length; i++)
			mArray[i] = initialValue; // 각 요소를 초기값으로 설정
	}

	// 복사 생성자: 다른 Storage 객체로부터 데이터를 복사
	template<typename T>
	inline Storage<T>::Storage(const Storage& other)
		: mSize(other.mSize) // 배열 크기 복사
		, mArray(new T[other.mSize]) // 새로운 동적 배열 할당
	{
		std::memcpy(mArray.get(), other.mArray.get(), sizeof(T) * other.mSize); // 배열 내용 복사
	}

	// 이동 생성자: 다른 Storage 객체로부터 데이터를 이동
	template<typename T>
	inline Storage<T>::Storage(Storage&& other) noexcept
		: mSize(other.mSize) // 배열 크기 이동
		, mArray(std::move(other.mArray)) // 배열 포인터 이동
	{
		other.mSize = 0; // 이동된 객체의 크기를 0으로 설정
	}

	// 복사 대입 연산자: 다른 Storage 객체로부터 데이터를 복사
	template<typename T>
	inline const Storage<T>& Storage<T>::operator=(const Storage& other)
	{
		if (this != &other) // 자기 자신과의 대입을 방지
		{
			mSize = other.mSize; // 배열 크기 복사
			mArray = std::make_unique<T[]>(other.mSize); // 새로운 동적 배열 할당

			std::memcpy(mArray.get(), other.mArray.get(), sizeof(T) * other.mSize); // 배열 내용 복사
		}

		return *this; // 현재 객체를 반환
	}

	// 이동 대입 연산자: 다른 Storage 객체로부터 데이터를 이동
	template<typename T>
	inline const Storage<T>& Storage<T>::operator=(Storage&& other)
	{
		if (this != &other) // 자기 자신과의 대입을 방지
		{
			mSize = other.mSize; // 배열 크기 이동
			mArray = std::move(other.mArray); // 배열 포인터 이동
			other.mSize = 0; // 이동된 객체의 크기를 0으로 설정
		}

		return *this; // 현재 객체를 반환
	}

	// Update 함수: 배열의 특정 인덱스에 데이터를 업데이트
	template<typename T>
	bool Storage<T>::Update(unsigned int index, const T& data)
	{
		if (index >= mSize) // 인덱스가 배열 크기보다 큰 경우
			return false; // 실패 반환

		mArray[index] = data; // 데이터 업데이트
		return true; // 성공 반환
	}

	// GetData 함수: 배열 데이터에 대한 const 참조를 반환
	template<typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return mArray; // 배열 포인터 반환
	}

	// GetSize 함수: 배열의 크기를 반환
	template<typename T>
	unsigned int Storage<T>::GetSize() const
	{
		return mSize; // 배열 크기 반환
	}
}