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
		BinarySearchTree(const BinarySearchTree& Copy) = delete;
		BinarySearchTree(const BinarySearchTree&& Copy) = delete;
		BinarySearchTree& operator=(const BinarySearchTree&) = delete;


		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data) const;
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		std::shared_ptr<TreeNode<T>> find(const T& data) const;

		static void mediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v);

	private:
		std::shared_ptr<TreeNode<T>> mRoot;
	};

	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree()
		: mRoot(nullptr)
	{
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
		std::weak_ptr<TreeNode<T>> ptr = find(data);

		if (ptr.lock() == nullptr)
			return false;

		while (true)
		{
			if (ptr.lock()->Left != nullptr)
			{
				ptr.lock()->Data = std::move(ptr.lock()->Left->Data);
				ptr = ptr.lock()->Left;
			}
			else if (ptr.lock()->Right != nullptr)
			{
				ptr.lock()->Data = std::move(ptr.lock()->Right->Data);
				ptr = ptr.lock()->Right;
			}
			else
			{
				if (ptr.lock() == mRoot)
				{
					mRoot.reset();
					return true;
				}

				std::weak_ptr<TreeNode<T>> parent = ptr.lock()->Parent.lock();

				if (parent.lock()->Left == ptr.lock())
					parent.lock()->Left.reset();
				else
					parent.lock()->Right.reset();

				return true;
			}
		}

	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		mediumRecursive(startNode, v);

		return v;
	}

	template<typename T>
	inline std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::find(const T& data) const
	{
		std::weak_ptr<TreeNode<T>> ptr = mRoot;
		while (true)
		{
			if (ptr.lock() == nullptr)
				return nullptr;
			else if (*ptr.lock()->Data == data)
				return ptr.lock();

			if (*ptr.lock()->Data < data)
				ptr = ptr.lock()->Right;
			else
				ptr = ptr.lock()->Left;
		}
	}

	template<typename T>
	inline void BinarySearchTree<T>::mediumRecursive(std::weak_ptr<TreeNode<T>> location, std::vector<T>& v)
	{
		if (location.lock() == nullptr)
			return;

		mediumRecursive(location.lock()->Left, v);

		v.push_back(*(location.lock()->Data));

		mediumRecursive(location.lock()->Right, v);
	}
}