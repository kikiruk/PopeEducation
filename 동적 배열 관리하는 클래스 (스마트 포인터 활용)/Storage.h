#pragma once

#include <memory> // ����Ʈ ������ ����� ���� ����

namespace lab11
{
	// Storage Ŭ���� ���ø�: ���� �迭�� �����ϴ� Ŭ����
	// T Ÿ���� �����͸� �����ϸ�, ���� �޸� ������ �ڵ����� ó��
	template<typename T>
	class Storage
	{
	public:
		Storage(unsigned int length); // ������ ���̷� �迭�� �ʱ�ȭ
		Storage(unsigned int length, const T& initialValue); // ������ ���̿� �ʱⰪ���� �迭�� �ʱ�ȭ
		Storage(const Storage& other); // ���� ������
		Storage(Storage&& other) noexcept; // �̵� ������
		~Storage() = default; // �Ҹ���: �⺻ �Ҹ��� ���

		const Storage& operator=(const Storage& other); // ���� ���� ������
		const Storage& operator=(Storage&& other); // �̵� ���� ������

		bool Update(unsigned int index, const T& data); // �迭�� Ư�� �ε����� �����͸� ������Ʈ
		const std::unique_ptr<T[]>& GetData() const; // �迭 �����Ϳ� ���� const ������ ��ȯ
		unsigned int GetSize() const; // �迭�� ũ�⸦ ��ȯ

	private:
		unsigned int mSize; // �迭�� ũ��
		std::unique_ptr<T[]> mArray; // ���� �迭�� �����ϴ� ����Ʈ ������
	};

	// ������: ������ ���̷� �迭�� �ʱ�ȭ�ϰ�, ��� ���� 0���� ����
	template<typename T>
	Storage<T>::Storage(unsigned int length)
		: mSize(length) // �迭 ũ�� ����
		, mArray(new T[length]) // ���� �迭 �Ҵ�
	{
		std::memset(mArray.get(), 0, sizeof(T) * length); // �迭�� 0���� �ʱ�ȭ
	}

	// ������: ������ ���̷� �迭�� �ʱ�ȭ�ϰ�, ��� ���� �ʱⰪ���� ����
	template<typename T>
	Storage<T>::Storage(unsigned int length, const T& initialValue)
		: mSize(length) // �迭 ũ�� ����
		, mArray(new T[length]) // ���� �迭 �Ҵ�
	{
		for (unsigned int i = 0; i < length; i++)
			mArray[i] = initialValue; // �� ��Ҹ� �ʱⰪ���� ����
	}

	// ���� ������: �ٸ� Storage ��ü�κ��� �����͸� ����
	template<typename T>
	inline Storage<T>::Storage(const Storage& other)
		: mSize(other.mSize) // �迭 ũ�� ����
		, mArray(new T[other.mSize]) // ���ο� ���� �迭 �Ҵ�
	{
		std::memcpy(mArray.get(), other.mArray.get(), sizeof(T) * other.mSize); // �迭 ���� ����
	}

	// �̵� ������: �ٸ� Storage ��ü�κ��� �����͸� �̵�
	template<typename T>
	inline Storage<T>::Storage(Storage&& other) noexcept
		: mSize(other.mSize) // �迭 ũ�� �̵�
		, mArray(std::move(other.mArray)) // �迭 ������ �̵�
	{
		other.mSize = 0; // �̵��� ��ü�� ũ�⸦ 0���� ����
	}

	// ���� ���� ������: �ٸ� Storage ��ü�κ��� �����͸� ����
	template<typename T>
	inline const Storage<T>& Storage<T>::operator=(const Storage& other)
	{
		if (this != &other) // �ڱ� �ڽŰ��� ������ ����
		{
			mSize = other.mSize; // �迭 ũ�� ����
			mArray = std::make_unique<T[]>(other.mSize); // ���ο� ���� �迭 �Ҵ�

			std::memcpy(mArray.get(), other.mArray.get(), sizeof(T) * other.mSize); // �迭 ���� ����
		}

		return *this; // ���� ��ü�� ��ȯ
	}

	// �̵� ���� ������: �ٸ� Storage ��ü�κ��� �����͸� �̵�
	template<typename T>
	inline const Storage<T>& Storage<T>::operator=(Storage&& other)
	{
		if (this != &other) // �ڱ� �ڽŰ��� ������ ����
		{
			mSize = other.mSize; // �迭 ũ�� �̵�
			mArray = std::move(other.mArray); // �迭 ������ �̵�
			other.mSize = 0; // �̵��� ��ü�� ũ�⸦ 0���� ����
		}

		return *this; // ���� ��ü�� ��ȯ
	}

	// Update �Լ�: �迭�� Ư�� �ε����� �����͸� ������Ʈ
	template<typename T>
	bool Storage<T>::Update(unsigned int index, const T& data)
	{
		if (index >= mSize) // �ε����� �迭 ũ�⺸�� ū ���
			return false; // ���� ��ȯ

		mArray[index] = data; // ������ ������Ʈ
		return true; // ���� ��ȯ
	}

	// GetData �Լ�: �迭 �����Ϳ� ���� const ������ ��ȯ
	template<typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return mArray; // �迭 ������ ��ȯ
	}

	// GetSize �Լ�: �迭�� ũ�⸦ ��ȯ
	template<typename T>
	unsigned int Storage<T>::GetSize() const
	{
		return mSize; // �迭 ũ�� ��ȯ
	}
}