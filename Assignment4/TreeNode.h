#pragma once

#include <memory>

namespace assignment4
{
	template<typename T>
	class TreeNode final
	{
	public:
		TreeNode(std::unique_ptr<T> data);
		TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data);
		~TreeNode() = default;
		TreeNode(const TreeNode& copy);
		TreeNode(const TreeNode&& copy) = delete;
		TreeNode& operator=(const TreeNode&) = delete;

		std::unique_ptr<T> Data;
		std::shared_ptr<TreeNode<T>> Left;
		std::shared_ptr<TreeNode<T>> Right;
		std::weak_ptr<TreeNode<T>> Parent;

	private:
		TreeNode(const TreeNode& copy, std::weak_ptr<TreeNode<T>>& parent);
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
	inline TreeNode<T>::TreeNode(const TreeNode& copy, std::weak_ptr<TreeNode<T>>& parent)
		: Data(std::make_unique<T>(*(copy.Data))
		, Left(make_shared<TreeNode<T>>((copy.Left == nullptr) ? nullptr : *copy.Left))
		, Right(make_shared<TreeNode<T>>((copy.Right == nullptr) ? nullptr : *copy.Right))
		, Parent(parent.lock())
	{
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(const TreeNode& copy)
		: Data(std::make_unique<T>(*(copy.Data))
		, Left(make_shared<TreeNode<T>>(*(copy.Left))
		, Right(make_shared<TreeNode<T>>(*(copy.Right))
	{
		Left->parent = Left;
		Right->parent = Right;
	}
}