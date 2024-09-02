#pragma once

#include <memory>
#include <vector>

namespace assignment4
{
	// TreeNode Ŭ������ ���� ����
	template<typename T>
	class TreeNode;

	// BinarySearchTree Ŭ����: ���� Ž�� Ʈ���� ����
	template<typename T>
	class BinarySearchTree final
	{
	public:
		BinarySearchTree(); // �⺻ ������
		~BinarySearchTree() = default; // �⺻ �Ҹ���
		BinarySearchTree(const BinarySearchTree& copy); // ���� ������
		BinarySearchTree(BinarySearchTree&& copy); // �̵� ������
		const BinarySearchTree& operator=(const BinarySearchTree&); // ���� ������ �����ε�

		// Ʈ�� ���� �޼����
		void Insert(std::unique_ptr<T> data); // Ʈ���� ������ ����
		bool Search(const T& data) const; // Ʈ������ ������ �˻�
		bool Delete(const T& data); // Ʈ������ ������ ����
		const std::weak_ptr<TreeNode<T>> GetRootNode() const; // ��Ʈ ��� ��ȯ

		// Ʈ���� ���� ��ȸ�Ͽ� �����͸� ��ȯ
		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		// ������ �˻��� ���� ����� ���� �޼���
		const std::shared_ptr<TreeNode<T>>* find(const T data) const; // ��� ����
		std::shared_ptr<TreeNode<T>>* find(const T data); // ���� ����

		// ���� ��ȸ�� �����ϴ� ��� ���� �޼���
		static void doMediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v);

	private:
		std::shared_ptr<TreeNode<T>> mRoot; // Ʈ���� ��Ʈ ��带 ����Ű�� ������
	};

	// �⺻ ������: ��Ʈ ��带 �ʱ�ȭ
	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree()
		: mRoot(nullptr)
	{
	}

	// ���� ������: �ٸ� Ʈ���� �����Ͽ� ���ο� Ʈ���� ����ϴ�.
	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& copy)
		: mRoot(std::make_shared<TreeNode<T>>(*copy.mRoot))
	{
		// �θ� ��� ����
		if (mRoot->Left != nullptr)
			mRoot->Left->Parent = mRoot;

		if (mRoot->Right != nullptr)
			mRoot->Right->Parent = mRoot;
	}

	// �̵� ������: �ٸ� Ʈ���� �������� �̵���ŵ�ϴ�.
	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& copy)
	{
		mRoot = copy.mRoot; // ��Ʈ ��带 �̵�
		copy.mRoot.reset(); // ���� Ʈ���� ��Ʈ ��带 nullptr�� ����
	}

	// ���� ������ �����ε�: �ٸ� Ʈ���� ���� Ʈ���� ����
	template<typename T>
	const BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& copy)
	{
		if (this != &copy) // �ڱ� �ڽŰ��� ������ ����
		{
			mRoot = copy.mRoot; // ��Ʈ ��带 ����

			// �θ� ��� ����
			if (mRoot->Left != nullptr)
				mRoot->Left->Parent = mRoot;

			if (mRoot->Right != nullptr)
				mRoot->Right->Parent = mRoot;
		}

		return *this; // ���� ��ü�� ��ȯ
	}

	// Insert: Ʈ���� ���ο� �����͸� ����
	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		// Ʈ���� ������� ��� ��Ʈ ��带 ����
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<TreeNode<T>>(std::move(data));
		}
		else
		{
			std::weak_ptr<TreeNode<T>> ptr = mRoot;
			while (true)
			{
				// ������ �����Ͱ� ���� ��庸�� Ŭ ���
				if (*(ptr.lock()->Data) < *data)
				{
					// ������ �ڽ� ��尡 ������� ��� ���ο� ��带 ����
					if (ptr.lock()->Right == nullptr)
					{
						ptr.lock()->Right = std::make_shared<TreeNode<T>>(ptr.lock(), std::move(data));
						return;
					}

					ptr = ptr.lock()->Right; // ������ �ڽ� ���� �̵�
				}
				else
				{
					// ���� �ڽ� ��尡 ������� ��� ���ο� ��带 ����
					if (ptr.lock()->Left == nullptr)
					{
						ptr.lock()->Left = std::make_shared<TreeNode<T>>(ptr.lock(), std::move(data));
						return;
					}

					ptr = ptr.lock()->Left; // ���� �ڽ� ���� �̵�
				}
			}
		}
	}

	// GetRootNode: ��Ʈ ��带 ��ȯ
	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRoot;
	}

	// Search: Ʈ������ Ư�� �����͸� �˻�
	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data) const
	{
		return (find(data) == nullptr) ? false : true;
	}

	// Delete: Ʈ������ Ư�� �����͸� ����
	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		std::shared_ptr<TreeNode<T>>* ptrNow = find(data);

		// �����Ͱ� ������ false ��ȯ
		if (ptrNow == nullptr)
			return false;

		std::weak_ptr<TreeNode<T>> rememberPtr = *ptrNow;
		std::weak_ptr<TreeNode<T>> rememberParent;

		while (true)
		{
			// ���� �ڽ��� ���� ���, �ش� �ڽ� ����� �����͸� ���� ���� �̵�
			if ((*ptrNow)->Left != nullptr)
			{
				(*ptrNow)->Data = std::move((*ptrNow)->Left->Data);

				// ���� �ڽ� ����� ������ �ڽ� ��带 �θ�� �翬��
				if ((*ptrNow)->Left->Right != nullptr)
				{
					rememberParent = *ptrNow;
					ptrNow = &((*ptrNow)->Right);

					while (true)
					{
						if (*ptrNow == nullptr)
						{
							*ptrNow = rememberPtr.lock()->Left->Right;
							rememberPtr.lock()->Left->Right.reset(); // ���� �ڽ��� ������ �ڽ� ���� ����
							(*ptrNow)->Parent = rememberParent.lock(); // �θ� ��� ����
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
				// ���� �ڽ��� ���� ���, ������ �ڽ��� ���� ���� ����
				if ((*ptrNow)->Right != nullptr)
					(*ptrNow) = (*ptrNow)->Right;
				else
					(*ptrNow).reset(); // �ڽ��� ���� ��� ��带 ����

				return true;
			}
		}
	}

	// TraverseInOrder: Ʈ���� ���� ��ȸ�Ͽ� �����͸� ��ȯ
	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		doMediumRecursive(startNode, v); // ���� ��ȸ�� ����

		return v;
	}

	// find: Ʈ������ Ư�� �����͸� ã�� ���� ����� �޼��� (��� ����)
	template<typename T>
	inline const std::shared_ptr<TreeNode<T>>* BinarySearchTree<T>::find(const T data) const
	{
		const std::shared_ptr<TreeNode<T>>* ptr = &mRoot;
		while (true)
		{
			if (*ptr == nullptr)
				return nullptr; // �����Ͱ� ������ nullptr ��ȯ
			else if (*((*ptr)->Data) == data)
				return ptr; // �����͸� ã���� �ش� ��� ��ȯ

			// �����͸� ���Ͽ� ���� �Ǵ� ���������� �̵�
			if (*((*ptr)->Data) < data)
				ptr = &((*ptr)->Right);
			else
				ptr = &((*ptr)->Left);
		}
	}

	// find: Ʈ������ Ư�� �����͸� ã�� ���� ����� �޼��� (���� ����)
	template<typename T>
	inline std::shared_ptr<TreeNode<T>>* BinarySearchTree<T>::find(const T data)
	{
		std::shared_ptr<TreeNode<T>>* ptr = &mRoot;
		while (true)
		{
			if (*ptr == nullptr)
				return nullptr; // �����Ͱ� ������ nullptr ��ȯ
			else if (*((*ptr)->Data) == data)
				return ptr; // �����͸� ã���� �ش� ��� ��ȯ

			// �����͸� ���Ͽ� ���� �Ǵ� ���������� �̵�
			if (*((*ptr)->Data) < data)
				ptr = &((*ptr)->Right);
			else
				ptr = &((*ptr)->Left);
		}
	}

	// doMediumRecursive: ���� ��ȸ�� �����ϴ� ����� ��� �޼���
	template<typename T>
	inline void BinarySearchTree<T>::doMediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v)
	{
		if (location.lock() == nullptr)
			return; // ��尡 ������ ����

		doMediumRecursive(location.lock()->Left, v); // ���� ����Ʈ�� ��ȸ

		v.push_back(*(location.lock()->Data)); // ���� ����� ������ �߰�

		doMediumRecursive(location.lock()->Right, v); // ������ ����Ʈ�� ��ȸ
	}
}