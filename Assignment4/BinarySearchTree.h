#pragma once

#include <memory>
#include <vector>

namespace assignment4
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		BinarySearchTree();
		~BinarySearchTree() = default;
		BinarySearchTree(const BinarySearchTree& copy);
		BinarySearchTree(BinarySearchTree&& copy);
		const BinarySearchTree& operator=(const BinarySearchTree&);


		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data) const;
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		const std::shared_ptr<TreeNode<T>>* find(const T data) const; //same
		std::shared_ptr<TreeNode<T>>* find(const T data);			  //same

		static void doMediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v);

	private:
		std::shared_ptr<TreeNode<T>> mRoot;
	};

	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree()
		: mRoot(nullptr)
	{
	}

	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& copy)
		: mRoot(std::make_shared<TreeNode<T>>(*copy.mRoot))
	{
		if (mRoot->Left != nullptr)
			mRoot->Left->Parent = mRoot;

		if (mRoot->Right != nullptr)
			mRoot->Right->Parent = mRoot;
	}

	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& copy)
	{
		mRoot = copy.mRoot;
		copy.mRoot.reset();
	}

	template<typename T>
	const BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& copy)
	{
		if (this != &copy)
		{
			mRoot = copy.mRoot;

			if (mRoot->Left != nullptr)
				mRoot->Left->Parent = mRoot;

			if (mRoot->Right != nullptr)
				mRoot->Right->Parent = mRoot;
		}

		return *this;
	}

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<TreeNode<T>>(std::move(data));
		}
		else
		{
			std::weak_ptr<TreeNode<T>> ptr = mRoot;
			while (true)
			{
				if (*(ptr.lock()->Data) < *data)
				{
					if (ptr.lock()->Right == nullptr)
					{
						ptr.lock()->Right = std::make_shared<TreeNode<T>>(ptr.lock(), std::move(data));
						return;
					}

					ptr = ptr.lock()->Right;
				}
				else
				{
					if (ptr.lock()->Left == nullptr)
					{
						ptr.lock()->Left = std::make_shared<TreeNode<T>>(ptr.lock(), std::move(data));
						return;
					}

					ptr = ptr.lock()->Left;
				}
			}
		}
	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRoot;
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data) const
	{
		return (find(data) == nullptr) ? false : true;
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		std::shared_ptr<TreeNode<T>>* ptrNow = find(data);

		if (ptrNow == nullptr)
			return false;

		std::weak_ptr<TreeNode<T>> rememberPtr = *ptrNow;

		std::weak_ptr<TreeNode<T>> rememberParent;
		while (true)
		{
			if ((*ptrNow)->Left != nullptr)
			{
				(*ptrNow)->Data = std::move((*ptrNow)->Left->Data);

				if ((*ptrNow)->Left->Right != nullptr)
				{
					rememberParent = *ptrNow;
					ptrNow = &((*ptrNow)->Right);

					while (true)
					{
						if (*ptrNow == nullptr)
						{
							*ptrNow = rememberPtr.lock()->Left->Right;
							rememberPtr.lock()->Left->Right.reset();  //���ʳ���� �����ʺκ��� �ٽú���.
							(*ptrNow)->Parent = rememberParent.lock();//�θ��� ����
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
				if ((*ptrNow)->Right != nullptr)
					(*ptrNow) = (*ptrNow)->Right;
				else
					(*ptrNow).reset();

				return true;
			}
		}
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		doMediumRecursive(startNode, v);

		return v;
	}

	template<typename T>
	inline const std::shared_ptr<TreeNode<T>>* BinarySearchTree<T>::find(const T data) const
	{
		const std::shared_ptr<TreeNode<T>>* ptr = &mRoot;
		while (true)
		{
			if (*ptr == nullptr)
				return nullptr;
			else if (*((*ptr)->Data) == data)
				return ptr;

			if (*((*ptr)->Data) < data)
				ptr = &((*ptr)->Right);
			else
				ptr = &((*ptr)->Left);
		}
	}

	template<typename T>
	inline std::shared_ptr<TreeNode<T>>* BinarySearchTree<T>::find(const T data)
	{
		std::shared_ptr<TreeNode<T>>* ptr = &mRoot;
		while (true)
		{
			if (*ptr == nullptr)
				return nullptr;
			else if (*((*ptr)->Data) == data)
				return ptr;

			if (*((*ptr)->Data) < data)
				ptr = &((*ptr)->Right);
			else
				ptr = &((*ptr)->Left);
		}
	}

	template<typename T>
	inline void BinarySearchTree<T>::doMediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v)
	{
		if (location.lock() == nullptr)
			return;

		doMediumRecursive(location.lock()->Left, v);

		v.push_back(*(location.lock()->Data));

		doMediumRecursive(location.lock()->Right, v);
	}
}