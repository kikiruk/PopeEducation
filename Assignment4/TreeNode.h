#pragma once

#include <memory>

namespace assignment4
{	
	template<typename T>
	class BinarySearchTree;

	template<typename T>
	class TreeNode final
	{
	friend BinarySearchTree; //복사생성자를 private 로만들기 위해서
	friend std::_Ref_count_obj;

	public:
		TreeNode(std::unique_ptr<T> data);
		TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data);
		~TreeNode() = default;
		TreeNode(const TreeNode&& copy) = delete;

		std::unique_ptr<T> Data;
		std::shared_ptr<TreeNode<T>> Left;
		std::shared_ptr<TreeNode<T>> Right;
		std::weak_ptr<TreeNode<T>> Parent;

	private:
		const TreeNode& operator=(const TreeNode&);
		TreeNode(const TreeNode& copy);
	};

	template<typename T>
	TreeNode<T>::TreeNode(std::unique_ptr<T> data)
		: Data(std::move(data))
		, Left(nullptr)
		, Right(nullptr)
	{
	}

	template<typename T>
	TreeNode<T>::TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data)
		: Data(std::move(data))
		, Left(nullptr)
		, Right(nullptr)
		, Parent(parent)
	{
	}

	template<typename T>
	inline const TreeNode<T>& TreeNode<T>::operator=(const TreeNode& copy)
	{
		if (this != &copy)
		{
			Data = std::make_unique<T>(*copy.Data);

			if (copy.Left != nullptr)
			{
				Left = std::make_shared<TreeNode<T>>(*copy.Left);

				if (Left->Left != nullptr)
				{
					Left->Left->Parent = Left;
				}

				if (Left->Right != nullptr)
				{
					Left->Right->Parent = Left;
				}
			}

			if (copy.Right != nullptr)
			{
				Right = std::make_shared<TreeNode<T>>(*copy.Right);

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


		return *this;
	}
	
	
	template<typename T>
	inline TreeNode<T>::TreeNode(const TreeNode& copy)
		: Data(std::make_unique<T>(*copy.Data))
	{
		if (copy.Left != nullptr)
		{
			Left = std::make_shared<TreeNode<T>>(*copy.Left);

			if (Left->Left != nullptr)
			{
				Left->Left->Parent = Left;
			}
			
			if (Left->Right != nullptr)
			{
				Left->Right->Parent = Left;
			}
		}
	
		if (copy.Right != nullptr)
		{
			Right = std::make_shared<TreeNode<T>>(*copy.Right);
			
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