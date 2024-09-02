#pragma once

#include <memory>

namespace assignment4
{
	// TreeNode Ŭ������ ����: ���� Ž�� Ʈ���� ��带 ��Ÿ����, ���� �� ���� �����͸� ����Ͽ� �޸� ����
	template<typename T>
	class BinarySearchTree;

	template<typename T>
	class TreeNode final
	{
		// BinarySearchTree Ŭ������ TreeNode�� private ����� ������ �� �ֵ��� ����
		friend BinarySearchTree;

		// ���� �����ڸ� private�� ����� ���� std::_Ref_count_obj�� ģ�� ���� ����
		friend std::_Ref_count_obj;

	public:
		// ������: ������ �����͸� �޾� ��带 �ʱ�ȭ
		TreeNode(std::unique_ptr<T> data);

		// �θ� ���� ������ �����͸� �޾� ��带 �ʱ�ȭ
		TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data);

		~TreeNode() = default; // �⺻ �Ҹ���

		TreeNode(TreeNode&& copy) = delete; // �̵� ������ ���� (�̵� �Ұ�)

		std::unique_ptr<T> Data; // ��尡 �����ϴ� ������
		std::shared_ptr<TreeNode<T>> Left; // ���� �ڽ� ���
		std::shared_ptr<TreeNode<T>> Right; // ������ �ڽ� ���
		std::weak_ptr<TreeNode<T>> Parent; // �θ� ��� (���� ����)

	private:
		// ���� ���� ������: ������ ����� �����Ϳ� �ڽ� ��带 ����
		const TreeNode& operator=(const TreeNode&);

		// ���� ������: ������ ����� �����͸� ������� ���ο� ��带 ����
		TreeNode(const TreeNode& copy);
	};

	// �⺻ ������: ������ �����͸� �޾� ��带 �ʱ�ȭ
	template<typename T>
	TreeNode<T>::TreeNode(std::unique_ptr<T> data)
		: Data(std::move(data))
		, Left(nullptr)
		, Right(nullptr)
	{
	}

	// �θ� ��带 �޾� ��带 �ʱ�ȭ�ϴ� ������
	template<typename T>
	TreeNode<T>::TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data)
		: Data(std::move(data))
		, Left(nullptr)
		, Right(nullptr)
		, Parent(parent)
	{
	}

	// ���� ���� ������: �ٸ� ����� �����͸� �����ϰ�, �ڽ� ��嵵 �����Ͽ� �θ� ���踦 ����
	template<typename T>
	inline const TreeNode<T>& TreeNode<T>::operator=(const TreeNode& copy)
	{
		if (this != &copy) // �ڱ� �ڽŰ��� ������ ����
		{
			// ������ ����
			Data = std::make_unique<T>(*copy.Data);

			// ���� �ڽ� ��� ����
			if (copy.Left != nullptr)
			{
				Left = std::make_shared<TreeNode<T>>(*copy.Left);

				// ����� �ڽ� ����� �θ� ��带 ����
				if (Left->Left != nullptr)
				{
					Left->Left->Parent = Left;
				}

				if (Left->Right != nullptr)
				{
					Left->Right->Parent = Left;
				}
			}

			// ������ �ڽ� ��� ����
			if (copy.Right != nullptr)
			{
				Right = std::make_shared<TreeNode<T>>(*copy.Right);

				// ����� �ڽ� ����� �θ� ��带 ����
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

		return *this; // ���� ��ü ��ȯ
	}


	// ���� ������: �ٸ� ����� �����͸� �����ϰ�, �ڽ� ��嵵 �����Ͽ� �θ� ���踦 ����
	template<typename T>
	inline TreeNode<T>::TreeNode(const TreeNode& copy)
		: Data(std::make_unique<T>(*copy.Data))
	{
		// ���� �ڽ� ��� ����
		if (copy.Left != nullptr)
		{
			Left = std::make_shared<TreeNode<T>>(*copy.Left);

			// ����� �ڽ� ����� �θ� ��带 ����
			if (Left->Left != nullptr)
			{
				Left->Left->Parent = Left;
			}

			if (Left->Right != nullptr)
			{
				Left->Right->Parent = Left;
			}
		}

		// ������ �ڽ� ��� ����
		if (copy.Right != nullptr)
		{
			Right = std::make_shared<TreeNode<T>>(*copy.Right);

			// ����� �ڽ� ����� �θ� ��带 ����
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