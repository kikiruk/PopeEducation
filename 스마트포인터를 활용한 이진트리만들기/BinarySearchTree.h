#pragma once

#include <memory>
#include <vector>

namespace assignment4
{
	// TreeNode 클래스의 전방 선언
	template<typename T>
	class TreeNode;

	// BinarySearchTree 클래스: 이진 탐색 트리의 구현
	template<typename T>
	class BinarySearchTree final
	{
	public:
		BinarySearchTree(); // 기본 생성자
		~BinarySearchTree() = default; // 기본 소멸자
		BinarySearchTree(const BinarySearchTree& copy); // 복사 생성자
		BinarySearchTree(BinarySearchTree&& copy); // 이동 생성자
		const BinarySearchTree& operator=(const BinarySearchTree&); // 대입 연산자 오버로드

		// 트리 조작 메서드들
		void Insert(std::unique_ptr<T> data); // 트리에 데이터 삽입
		bool Search(const T& data) const; // 트리에서 데이터 검색
		bool Delete(const T& data); // 트리에서 데이터 삭제
		const std::weak_ptr<TreeNode<T>> GetRootNode() const; // 루트 노드 반환

		// 트리를 중위 순회하여 데이터를 반환
		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		// 데이터 검색을 위한 비공개 헬퍼 메서드
		const std::shared_ptr<TreeNode<T>>* find(const T data) const; // 상수 버전
		std::shared_ptr<TreeNode<T>>* find(const T data); // 비상수 버전

		// 중위 순회를 수행하는 재귀 헬퍼 메서드
		static void doMediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v);

	private:
		std::shared_ptr<TreeNode<T>> mRoot; // 트리의 루트 노드를 가리키는 포인터
	};

	// 기본 생성자: 루트 노드를 초기화
	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree()
		: mRoot(nullptr)
	{
	}

	// 복사 생성자: 다른 트리를 복사하여 새로운 트리를 만듭니다.
	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& copy)
		: mRoot(std::make_shared<TreeNode<T>>(*copy.mRoot))
	{
		// 부모 노드 설정
		if (mRoot->Left != nullptr)
			mRoot->Left->Parent = mRoot;

		if (mRoot->Right != nullptr)
			mRoot->Right->Parent = mRoot;
	}

	// 이동 생성자: 다른 트리의 소유권을 이동시킵니다.
	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& copy)
	{
		mRoot = copy.mRoot; // 루트 노드를 이동
		copy.mRoot.reset(); // 원본 트리의 루트 노드를 nullptr로 설정
	}

	// 대입 연산자 오버로드: 다른 트리를 현재 트리에 복사
	template<typename T>
	const BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& copy)
	{
		if (this != &copy) // 자기 자신과의 대입을 방지
		{
			mRoot = copy.mRoot; // 루트 노드를 복사

			// 부모 노드 설정
			if (mRoot->Left != nullptr)
				mRoot->Left->Parent = mRoot;

			if (mRoot->Right != nullptr)
				mRoot->Right->Parent = mRoot;
		}

		return *this; // 현재 객체를 반환
	}

	// Insert: 트리에 새로운 데이터를 삽입
	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		// 트리가 비어있을 경우 루트 노드를 생성
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<TreeNode<T>>(std::move(data));
		}
		else
		{
			std::weak_ptr<TreeNode<T>> ptr = mRoot;
			while (true)
			{
				// 삽입할 데이터가 현재 노드보다 클 경우
				if (*(ptr.lock()->Data) < *data)
				{
					// 오른쪽 자식 노드가 비어있을 경우 새로운 노드를 삽입
					if (ptr.lock()->Right == nullptr)
					{
						ptr.lock()->Right = std::make_shared<TreeNode<T>>(ptr.lock(), std::move(data));
						return;
					}

					ptr = ptr.lock()->Right; // 오른쪽 자식 노드로 이동
				}
				else
				{
					// 왼쪽 자식 노드가 비어있을 경우 새로운 노드를 삽입
					if (ptr.lock()->Left == nullptr)
					{
						ptr.lock()->Left = std::make_shared<TreeNode<T>>(ptr.lock(), std::move(data));
						return;
					}

					ptr = ptr.lock()->Left; // 왼쪽 자식 노드로 이동
				}
			}
		}
	}

	// GetRootNode: 루트 노드를 반환
	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRoot;
	}

	// Search: 트리에서 특정 데이터를 검색
	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data) const
	{
		return (find(data) == nullptr) ? false : true;
	}

	// Delete: 트리에서 특정 데이터를 삭제
	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		std::shared_ptr<TreeNode<T>>* ptrNow = find(data);

		// 데이터가 없으면 false 반환
		if (ptrNow == nullptr)
			return false;

		std::weak_ptr<TreeNode<T>> rememberPtr = *ptrNow;
		std::weak_ptr<TreeNode<T>> rememberParent;

		while (true)
		{
			// 왼쪽 자식이 있을 경우, 해당 자식 노드의 데이터를 현재 노드로 이동
			if ((*ptrNow)->Left != nullptr)
			{
				(*ptrNow)->Data = std::move((*ptrNow)->Left->Data);

				// 왼쪽 자식 노드의 오른쪽 자식 노드를 부모와 재연결
				if ((*ptrNow)->Left->Right != nullptr)
				{
					rememberParent = *ptrNow;
					ptrNow = &((*ptrNow)->Right);

					while (true)
					{
						if (*ptrNow == nullptr)
						{
							*ptrNow = rememberPtr.lock()->Left->Right;
							rememberPtr.lock()->Left->Right.reset(); // 왼쪽 자식의 오른쪽 자식 연결 해제
							(*ptrNow)->Parent = rememberParent.lock(); // 부모 노드 설정
							break;
						}

						rememberParent = *ptrNow;
						ptrNow = &((*ptrNow)->Left);
					}
				}

				ptrNow = &(rememberPtr.lock()->Left);
				rememberPtr = *ptrNow;
			}
			else
			{
				// 왼쪽 자식이 없을 경우, 오른쪽 자식을 현재 노드로 설정
				if ((*ptrNow)->Right != nullptr)
					(*ptrNow) = (*ptrNow)->Right;
				else
					(*ptrNow).reset(); // 자식이 없을 경우 노드를 삭제

				return true;
			}
		}
	}

	// TraverseInOrder: 트리를 중위 순회하여 데이터를 반환
	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		doMediumRecursive(startNode, v); // 중위 순회를 수행

		return v;
	}

	// find: 트리에서 특정 데이터를 찾기 위한 비공개 메서드 (상수 버전)
	template<typename T>
	inline const std::shared_ptr<TreeNode<T>>* BinarySearchTree<T>::find(const T data) const
	{
		const std::shared_ptr<TreeNode<T>>* ptr = &mRoot;
		while (true)
		{
			if (*ptr == nullptr)
				return nullptr; // 데이터가 없으면 nullptr 반환
			else if (*((*ptr)->Data) == data)
				return ptr; // 데이터를 찾으면 해당 노드 반환

			// 데이터를 비교하여 왼쪽 또는 오른쪽으로 이동
			if (*((*ptr)->Data) < data)
				ptr = &((*ptr)->Right);
			else
				ptr = &((*ptr)->Left);
		}
	}

	// find: 트리에서 특정 데이터를 찾기 위한 비공개 메서드 (비상수 버전)
	template<typename T>
	inline std::shared_ptr<TreeNode<T>>* BinarySearchTree<T>::find(const T data)
	{
		std::shared_ptr<TreeNode<T>>* ptr = &mRoot;
		while (true)
		{
			if (*ptr == nullptr)
				return nullptr; // 데이터가 없으면 nullptr 반환
			else if (*((*ptr)->Data) == data)
				return ptr; // 데이터를 찾으면 해당 노드 반환

			// 데이터를 비교하여 왼쪽 또는 오른쪽으로 이동
			if (*((*ptr)->Data) < data)
				ptr = &((*ptr)->Right);
			else
				ptr = &((*ptr)->Left);
		}
	}

	// doMediumRecursive: 중위 순회를 수행하는 비공개 재귀 메서드
	template<typename T>
	inline void BinarySearchTree<T>::doMediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v)
	{
		if (location.lock() == nullptr)
			return; // 노드가 없으면 종료

		doMediumRecursive(location.lock()->Left, v); // 왼쪽 서브트리 순회

		v.push_back(*(location.lock()->Data)); // 현재 노드의 데이터 추가

		doMediumRecursive(location.lock()->Right, v); // 오른쪽 서브트리 순회
	}
}