#pragma once

#include <memory>

namespace assignment4
{
	// TreeNode 클래스의 정의: 이진 탐색 트리의 노드를 나타내며, 고유 및 공유 포인터를 사용하여 메모리 관리
	template<typename T>
	class BinarySearchTree;

	template<typename T>
	class TreeNode final
	{
		// BinarySearchTree 클래스가 TreeNode의 private 멤버에 접근할 수 있도록 설정
		friend BinarySearchTree;

		// 복사 생성자를 private로 만들기 위해 std::_Ref_count_obj와 친구 관계 설정
		friend std::_Ref_count_obj;

	public:
		// 생성자: 데이터 포인터를 받아 노드를 초기화
		TreeNode(std::unique_ptr<T> data);

		// 부모 노드와 데이터 포인터를 받아 노드를 초기화
		TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data);

		~TreeNode() = default; // 기본 소멸자

		TreeNode(TreeNode&& copy) = delete; // 이동 생성자 삭제 (이동 불가)

		std::unique_ptr<T> Data; // 노드가 저장하는 데이터
		std::shared_ptr<TreeNode<T>> Left; // 왼쪽 자식 노드
		std::shared_ptr<TreeNode<T>> Right; // 오른쪽 자식 노드
		std::weak_ptr<TreeNode<T>> Parent; // 부모 노드 (약한 참조)

	private:
		// 복사 대입 연산자: 복사할 노드의 데이터와 자식 노드를 복사
		const TreeNode& operator=(const TreeNode&);

		// 복사 생성자: 복사할 노드의 데이터를 기반으로 새로운 노드를 생성
		TreeNode(const TreeNode& copy);
	};

	// 기본 생성자: 데이터 포인터를 받아 노드를 초기화
	template<typename T>
	TreeNode<T>::TreeNode(std::unique_ptr<T> data)
		: Data(std::move(data))
		, Left(nullptr)
		, Right(nullptr)
	{
	}

	// 부모 노드를 받아 노드를 초기화하는 생성자
	template<typename T>
	TreeNode<T>::TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data)
		: Data(std::move(data))
		, Left(nullptr)
		, Right(nullptr)
		, Parent(parent)
	{
	}

	// 복사 대입 연산자: 다른 노드의 데이터를 복사하고, 자식 노드도 복사하여 부모 관계를 설정
	template<typename T>
	inline const TreeNode<T>& TreeNode<T>::operator=(const TreeNode& copy)
	{
		if (this != &copy) // 자기 자신과의 대입을 방지
		{
			// 데이터 복사
			Data = std::make_unique<T>(*copy.Data);

			// 왼쪽 자식 노드 복사
			if (copy.Left != nullptr)
			{
				Left = std::make_shared<TreeNode<T>>(*copy.Left);

				// 복사된 자식 노드의 부모 노드를 설정
				if (Left->Left != nullptr)
				{
					Left->Left->Parent = Left;
				}

				if (Left->Right != nullptr)
				{
					Left->Right->Parent = Left;
				}
			}

			// 오른쪽 자식 노드 복사
			if (copy.Right != nullptr)
			{
				Right = std::make_shared<TreeNode<T>>(*copy.Right);

				// 복사된 자식 노드의 부모 노드를 설정
				if (Right->Left != nullptr)
				{
					Right->Left->Parent = Right;
				}

				if (Right->Right != nullptr)
				{
					Right->Right->Parent = Right;
				}
			}
		}

		return *this; // 현재 객체 반환
	}


	// 복사 생성자: 다른 노드의 데이터를 복사하고, 자식 노드도 복사하여 부모 관계를 설정
	template<typename T>
	inline TreeNode<T>::TreeNode(const TreeNode& copy)
		: Data(std::make_unique<T>(*copy.Data))
	{
		// 왼쪽 자식 노드 복사
		if (copy.Left != nullptr)
		{
			Left = std::make_shared<TreeNode<T>>(*copy.Left);

			// 복사된 자식 노드의 부모 노드를 설정
			if (Left->Left != nullptr)
			{
				Left->Left->Parent = Left;
			}

			if (Left->Right != nullptr)
			{
				Left->Right->Parent = Left;
			}
		}

		// 오른쪽 자식 노드 복사
		if (copy.Right != nullptr)
		{
			Right = std::make_shared<TreeNode<T>>(*copy.Right);

			// 복사된 자식 노드의 부모 노드를 설정
			if (Right->Left != nullptr)
			{
				Right->Left->Parent = Right;
			}

			if (Right->Right != nullptr)
			{
				Right->Right->Parent = Right;
			}
		}
	}

}