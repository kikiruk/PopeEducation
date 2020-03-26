#include <cassert>
#include <ctime>
#include <iostream>
#include "TreeNode.h"
#include "BinarySearchTree.h"

using namespace assignment4;

void Test_Insert_GetRoot();
void Test_Search();
void Test_Delete();
void Test_Traverse();

int main()
{
	Test_Insert_GetRoot();
	Test_Search();
	Test_Delete();
	Test_Traverse();

	return 0;
}

void Test_Insert_GetRoot()
{
	BinarySearchTree<int> tree;

	int arr[10] = { 10, 15, 5, 4, 19, 20, 17, 12, 7, 0 };

	tree.Insert(std::make_unique<int>(arr[0]));
	tree.Insert(std::make_unique<int>(arr[1]));
	tree.Insert(std::make_unique<int>(arr[2]));
	tree.Insert(std::make_unique<int>(arr[3]));
	tree.Insert(std::make_unique<int>(arr[4]));
	tree.Insert(std::make_unique<int>(arr[5]));
	tree.Insert(std::make_unique<int>(arr[6]));
	tree.Insert(std::make_unique<int>(arr[7]));
	tree.Insert(std::make_unique<int>(arr[8]));

	std::shared_ptr<TreeNode<int>> test0 = tree.GetRootNode().lock();
	assert(*test0->Data.get() == 10);
	assert(test0->Parent.lock().get() == nullptr);
	std::shared_ptr<TreeNode<int>> test1 = test0->Left;
	assert(*test1->Data.get() == 5);
	assert(*test1->Parent.lock()->Data.get() == 10);
	std::shared_ptr<TreeNode<int>> test2 = test1->Left;
	assert(*test2->Data.get() == 4);
	assert(*test2->Parent.lock()->Data.get() == 5);
	std::shared_ptr<TreeNode<int>> test3 = test1->Right;
	assert(*test3->Data.get() == 7);
	assert(*test3->Parent.lock()->Data.get() == 5);
	std::shared_ptr<TreeNode<int>> test4 = test0->Right;
	assert(*test4->Data.get() == 15);
	assert(*test4->Parent.lock()->Data.get() == 10);
	std::shared_ptr<TreeNode<int>> test5 = test4->Left;
	assert(*test5->Data.get() == 12);
	assert(*test5->Parent.lock()->Data.get() == 15);
	std::shared_ptr<TreeNode<int>> test6 = test4->Right;
	assert(*test6->Data.get() == 19);
	assert(*test6->Parent.lock()->Data.get() == 15);
	std::shared_ptr<TreeNode<int>> test7 = test6->Left;
	assert(*test7->Data.get() == 17);
	assert(*test7->Parent.lock()->Data.get() == 19);
	std::shared_ptr<TreeNode<int>> test8 = test6->Right;
	assert(*test8->Data.get() == 20);
	assert(*test8->Parent.lock()->Data.get() == 19);

	return;
}

void Test_Search()
{
	BinarySearchTree<int> tree;

	int arr[10] = { 10, 15, 5, 4, 19, 20, 17, 12, 7, 0 };

	assert(!tree.Search(arr[0]));
	tree.Insert(std::make_unique<int>(arr[0]));
	assert(tree.Search(arr[0]));
	tree.Insert(std::make_unique<int>(arr[1]));
	assert(tree.Search(arr[1]));
	tree.Insert(std::make_unique<int>(arr[2]));
	assert(tree.Search(arr[2]));
	tree.Insert(std::make_unique<int>(arr[3]));
	assert(tree.Search(arr[3]));
	tree.Insert(std::make_unique<int>(arr[4]));
	assert(tree.Search(arr[4]));
	tree.Insert(std::make_unique<int>(arr[5]));
	assert(tree.Search(arr[5]));
	tree.Insert(std::make_unique<int>(arr[6]));
	assert(tree.Search(arr[6]));
	tree.Insert(std::make_unique<int>(arr[7]));
	assert(tree.Search(arr[7]));
	tree.Insert(std::make_unique<int>(arr[8]));
	assert(tree.Search(arr[8]));
	assert(!tree.Search(arr[9]));

	return;
}

void Test_Delete()
{
	BinarySearchTree<int> tree;

	int arr[9] = { 10, 15, 5, 4, 19, 20, 17, 12, 7 };

	for (size_t i = 0; i < 9; i++)
	{
		tree.Insert(std::make_unique<int>(arr[i]));
	}

	std::vector<int> tmp;
	//	End
	assert(!tree.Delete(9)); 	// 존재하지 않는 노드 삭제

	assert(tree.Delete(20));	// Right 노드 삭제	tmp = tree.TraverseInOrder((tree.GetRootNode().lock()));

	assert(!tree.Search(20));	// 삭제 확인
	assert(tree.Delete(12));	// Left 노드 삭제

	assert(!tree.Search(12));	// 삭제 확인
	assert(!tree.Delete(11));	// 존재하지 않는 노드 삭제

	//	Middle
	assert(tree.Delete(19));	// Left만 있는 노드 삭제

	assert(!tree.Search(19));	// 삭제 확인
	assert(tree.Search(17));
	assert(tree.Delete(15));	// Right만 있는 노드 삭제
	assert(!tree.Search(15));	// 삭제 확인
	assert(tree.Delete(5)); 	// Left, Right 모두 있는 노드 삭제
	assert(!tree.Search(5));	assert(!tree.Delete(5));	// 존재하지 않는 노드 삭제

	//	Head
	assert(tree.Delete(10)); 	// Left, Right 모두 있는 헤드 삭제
	assert(!tree.Search(10));	// 삭제 확인
	assert(tree.Delete(4));
	


	assert(tree.Delete(7));
	assert(tree.Delete(17));	// Left, Right 모두 없는 헤드 삭제
	assert(!tree.Search(17));	// 삭제 확인
	assert(!tree.Delete(17));	// 비어있는 상태에서 삭제


	for (size_t i = 0; i < 9; i++)
	{
		tree.Insert(std::make_unique<int>(arr[i]));

		tmp = tree.TraverseInOrder((tree.GetRootNode().lock()));

		for (auto i = tmp.begin(); i != tmp.end(); i++)
		{
			std::cout << *i << ", ";
		}
		std::cout << std::endl;
	}
	
	for (size_t i = 0; i < 9; i++)
	{
		tree.Delete(arr[i]);

		tmp = tree.TraverseInOrder((tree.GetRootNode().lock()));

		for (auto i = tmp.begin(); i != tmp.end(); i++)
		{
			std::cout << *i << ", ";
		}
		std::cout << std::endl;

	}

	return;
}

void Test_Traverse()
{
	BinarySearchTree<int> tree;

	int arr[9] = { 10, 15, 5, 4, 19, 20, 17, 12, 7 };
	int arr_chk[9] = { 4, 5, 7, 10, 12, 15, 17, 19, 20 };

	// 빈 트리
	std::vector<int> v1 = tree.TraverseInOrder(tree.GetRootNode().lock());
	assert(v1.size() == 0);
	assert(v1.empty());

	tree.Insert(std::make_unique<int>(arr[0]));
	// 헤드만 있는 트리
	std::vector<int> v2 = tree.TraverseInOrder(tree.GetRootNode().lock());
	assert(v2.size() == 1);
	assert(v2[0] == arr[0]);

	// empty 포인터
	std::vector<int> v3 = tree.TraverseInOrder(tree.GetRootNode().lock()->Left);
	assert(v3.size() == 0);
	assert(v3.empty());

	// 트리 입력
	for (size_t i = 1; i < 9; i++)
	{
		tree.Insert(std::make_unique<int>(arr[i]));
	}

	// 헤드 노드 입력
	std::vector<int> v4 = tree.TraverseInOrder(tree.GetRootNode().lock());
	assert(v4.size() == 9);
	assert(v4[0] == arr_chk[0]);
	assert(v4[1] == arr_chk[1]);
	assert(v4[2] == arr_chk[2]);
	assert(v4[3] == arr_chk[3]);
	assert(v4[4] == arr_chk[4]);
	assert(v4[5] == arr_chk[5]);
	assert(v4[6] == arr_chk[6]);
	assert(v4[7] == arr_chk[7]);
	assert(v4[8] == arr_chk[8]);

	// 중간 노드 입력
	std::vector<int> v5 = tree.TraverseInOrder(tree.GetRootNode().lock()->Right->Right);
	assert(v5.size() == 3);
	assert(v5[0] == arr_chk[6]);
	assert(v5[1] == arr_chk[7]);
	assert(v5[2] == arr_chk[8]);

	// 말단 노드 입력
	std::vector<int> v6 = tree.TraverseInOrder(tree.GetRootNode().lock()->Right->Left);
	assert(v6.size() == 1);
	assert(v6[0] == arr_chk[4]);

	// 노드 삭제
	for (size_t i = 0; i < 8; i++)
	{
		tree.Delete(arr[i]);
	}

	// 7만 남기고 모두 삭제된 트리
	std::vector<int> v7 = tree.TraverseInOrder(tree.GetRootNode().lock());
	assert(v7.size() == 1);
	assert(v7[0] == arr[8]);

	// 노드가 모두 삭제된 트리
	tree.Delete(arr[8]);
	std::vector<int> v8 = tree.TraverseInOrder(tree.GetRootNode().lock());
	assert(v8.size() == 0);
	assert(v8.empty());

	return;
}

void TestCaseFromSlackOnlyLeftRight()
{
	BinarySearchTree<int> tree1;
	tree1.Insert(std::make_unique<int>(8));
	tree1.Insert(std::make_unique<int>(5));
	tree1.Insert(std::make_unique<int>(30));
	tree1.Insert(std::make_unique<int>(20));
	tree1.Insert(std::make_unique<int>(45));
	tree1.Insert(std::make_unique<int>(11));
	tree1.Insert(std::make_unique<int>(25));
	tree1.Insert(std::make_unique<int>(26));
	tree1.Insert(std::make_unique<int>(40));
	tree1.Insert(std::make_unique<int>(48));
	tree1.Insert(std::make_unique<int>(24));
	tree1.Insert(std::make_unique<int>(41));
	bool bDeleted1 = tree1.Delete(30);
	assert(bDeleted1);

	BinarySearchTree<int> tree2;
	tree2.Insert(std::make_unique<int>(8));
	tree2.Insert(std::make_unique<int>(5));
	tree2.Insert(std::make_unique<int>(20));
	tree2.Insert(std::make_unique<int>(45));
	tree2.Insert(std::make_unique<int>(11));
	tree2.Insert(std::make_unique<int>(25));
	tree2.Insert(std::make_unique<int>(26));
	tree2.Insert(std::make_unique<int>(40));
	tree2.Insert(std::make_unique<int>(48));
	tree2.Insert(std::make_unique<int>(24));
	tree2.Insert(std::make_unique<int>(41));

	std::vector<int> v1 = tree1.TraverseInOrder(tree1.GetRootNode().lock());
	std::vector<int> v2 = tree2.TraverseInOrder(tree2.GetRootNode().lock());

	assert(v1.size() == 11);
	assert(v2.size() == 11);
	assert(v1[0] == v2[0]);
	assert(v1[1] == v2[1]);
	assert(v1[2] == v2[2]);
	assert(v1[3] == v2[3]);
	assert(v1[4] == v2[4]);
	assert(v1[5] == v2[5]);
	assert(v1[6] == v2[6]);
	assert(v1[7] == v2[7]);
	assert(v1[8] == v2[8]);
	assert(v1[9] == v2[9]);
	assert(v1[10] == v2[10]);

	// 트리 모양이 같은 형태인지 일일이 검토
	// 8
	assert(tree1.GetRootNode().lock() != nullptr);
	assert(tree2.GetRootNode().lock() != nullptr);
	assert(*tree1.GetRootNode().lock()->Data == *tree2.GetRootNode().lock()->Data);
	// 5
	assert(tree1.GetRootNode().lock()->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Left->Data == *tree2.GetRootNode().lock()->Left->Data);
	// 20
	assert(tree1.GetRootNode().lock()->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Data == *tree2.GetRootNode().lock()->Right->Data);
	// 11
	assert(tree1.GetRootNode().lock()->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Left->Data);
	// 45
	assert(tree1.GetRootNode().lock()->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Data);
	// 25
	assert(tree1.GetRootNode().lock()->Right->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Data);
	// 24
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Left->Data);
	// 26
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Data == 26);
	// 48
	assert(tree1.GetRootNode().lock()->Right->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Right->Data);
	// 40
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Right->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Data == 40);
	// 41
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Right->Right->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Right->Data == 41);
}

void TestCaseFromSlackOnlyRightLeft()
{
	BinarySearchTree<int> tree1;
	tree1.Insert(std::make_unique<int>(8));
	tree1.Insert(std::make_unique<int>(5));
	tree1.Insert(std::make_unique<int>(30));
	tree1.Insert(std::make_unique<int>(20));
	tree1.Insert(std::make_unique<int>(45));
	tree1.Insert(std::make_unique<int>(11));
	tree1.Insert(std::make_unique<int>(25));
	tree1.Insert(std::make_unique<int>(40));
	tree1.Insert(std::make_unique<int>(48));
	tree1.Insert(std::make_unique<int>(24));
	tree1.Insert(std::make_unique<int>(39));
	tree1.Insert(std::make_unique<int>(41));
	bool bDeleted1 = tree1.Delete(30);
	assert(bDeleted1);

	BinarySearchTree<int> tree2;
	tree2.Insert(std::make_unique<int>(8));
	tree2.Insert(std::make_unique<int>(5));
	tree2.Insert(std::make_unique<int>(20));
	tree2.Insert(std::make_unique<int>(45));
	tree2.Insert(std::make_unique<int>(11));
	tree2.Insert(std::make_unique<int>(25));
	tree2.Insert(std::make_unique<int>(40));
	tree2.Insert(std::make_unique<int>(48));
	tree2.Insert(std::make_unique<int>(24));
	tree2.Insert(std::make_unique<int>(39));
	tree2.Insert(std::make_unique<int>(41));

	std::vector<int> v1 = tree1.TraverseInOrder(tree1.GetRootNode().lock());
	std::vector<int> v2 = tree2.TraverseInOrder(tree2.GetRootNode().lock());

	assert(v1.size() == 11);
	assert(v2.size() == 11);
	assert(v1[0] == v2[0]);
	assert(v1[1] == v2[1]);
	assert(v1[2] == v2[2]);
	assert(v1[3] == v2[3]);
	assert(v1[4] == v2[4]);
	assert(v1[5] == v2[5]);
	assert(v1[6] == v2[6]);
	assert(v1[7] == v2[7]);
	assert(v1[8] == v2[8]);
	assert(v1[9] == v2[9]);
	assert(v1[10] == v2[10]);

	// 트리 모양이 같은 형태인지 일일이 검토
	// 8
	assert(tree1.GetRootNode().lock() != nullptr);
	assert(tree2.GetRootNode().lock() != nullptr);
	assert(*tree1.GetRootNode().lock()->Data == *tree2.GetRootNode().lock()->Data);
	// 5
	assert(tree1.GetRootNode().lock()->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Left->Data == *tree2.GetRootNode().lock()->Left->Data);
	// 20
	assert(tree1.GetRootNode().lock()->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Data == *tree2.GetRootNode().lock()->Right->Data);
	// 11
	assert(tree1.GetRootNode().lock()->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Left->Data);
	// 45
	assert(tree1.GetRootNode().lock()->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Data);
	// 25
	assert(tree1.GetRootNode().lock()->Right->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Data == 25);
	// 24
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Left->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Left->Data == 24);
	// 40
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Data);
	// 48
	assert(tree1.GetRootNode().lock()->Right->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Right->Data);
	// 41
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Right->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Data == 41);
	// 39
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Left->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Data == 39);
}

void TestCaseFromSlackLeftRightWithRightChild()
{
	BinarySearchTree<int> tree1;
	tree1.Insert(std::make_unique<int>(8));
	tree1.Insert(std::make_unique<int>(5));
	tree1.Insert(std::make_unique<int>(30));
	tree1.Insert(std::make_unique<int>(20));
	tree1.Insert(std::make_unique<int>(45));
	tree1.Insert(std::make_unique<int>(11));
	tree1.Insert(std::make_unique<int>(25));
	tree1.Insert(std::make_unique<int>(40));
	tree1.Insert(std::make_unique<int>(48));
	tree1.Insert(std::make_unique<int>(24));
	tree1.Insert(std::make_unique<int>(26));
	tree1.Insert(std::make_unique<int>(27));
	tree1.Insert(std::make_unique<int>(39));
	tree1.Insert(std::make_unique<int>(41));
	bool bDeleted1 = tree1.Delete(30);
	assert(bDeleted1);

	BinarySearchTree<int> tree2;
	tree2.Insert(std::make_unique<int>(8));
	tree2.Insert(std::make_unique<int>(5));
	tree2.Insert(std::make_unique<int>(20));
	tree2.Insert(std::make_unique<int>(45));
	tree2.Insert(std::make_unique<int>(11));
	tree2.Insert(std::make_unique<int>(25));
	tree2.Insert(std::make_unique<int>(40));
	tree2.Insert(std::make_unique<int>(48));
	tree2.Insert(std::make_unique<int>(24));
	tree2.Insert(std::make_unique<int>(26));
	tree2.Insert(std::make_unique<int>(27));
	tree2.Insert(std::make_unique<int>(39));
	tree2.Insert(std::make_unique<int>(41));

	std::vector<int> v1 = tree1.TraverseInOrder(tree1.GetRootNode().lock());
	std::vector<int> v2 = tree2.TraverseInOrder(tree2.GetRootNode().lock());

	assert(v1.size() == 13);
	assert(v2.size() == 13);
	assert(v1[0] == v2[0]);
	assert(v1[1] == v2[1]);
	assert(v1[2] == v2[2]);
	assert(v1[3] == v2[3]);
	assert(v1[4] == v2[4]);
	assert(v1[5] == v2[5]);
	assert(v1[6] == v2[6]);
	assert(v1[7] == v2[7]);
	assert(v1[8] == v2[8]);
	assert(v1[9] == v2[9]);
	assert(v1[10] == v2[10]);
	assert(v1[11] == v2[11]);
	assert(v1[12] == v2[12]);

	// 트리 모양이 같은 형태인지 일일이 검토
	// 8
	assert(tree1.GetRootNode().lock() != nullptr);
	assert(tree2.GetRootNode().lock() != nullptr);
	assert(*tree1.GetRootNode().lock()->Data == *tree2.GetRootNode().lock()->Data);
	// 5
	assert(tree1.GetRootNode().lock()->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Left->Data == *tree2.GetRootNode().lock()->Left->Data);
	// 20
	assert(tree1.GetRootNode().lock()->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Data == *tree2.GetRootNode().lock()->Right->Data);
	// 11
	assert(tree1.GetRootNode().lock()->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Left->Data);
	// 45
	assert(tree1.GetRootNode().lock()->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Data);
	// 25
	assert(tree1.GetRootNode().lock()->Right->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Data);
	// 24
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Left->Data);
	// 40
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Data);
	// 48
	assert(tree1.GetRootNode().lock()->Right->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Right->Data);
	// 26
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Left != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Left != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Left->Data);
	// 41
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Right->Data);
	// 27
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Left->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Data == 27);
	// 39
	assert(tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Right != nullptr);
	assert(tree2.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Right != nullptr);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Right->Data == *tree2.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Right->Data);
	assert(*tree1.GetRootNode().lock()->Right->Right->Left->Right->Left->Right->Right->Data == 39);
}


void TestCaseRandomNode()
{
	BinarySearchTree<int> randomTree1;
	BinarySearchTree<int> randomTree2;
	std::vector<int> randomTreeTraverse1;
	std::vector<int> randomTreeTraverse2;

	unsigned int randomValue = 0;

	for (unsigned int loopIndex = 0; loopIndex < 100; loopIndex++)
	{
		srand((unsigned int)time(NULL));

		for (unsigned int index = 0; index < 30; index++)
		{
			randomValue = rand() % 100;
			randomTree1.Insert(std::make_unique<int>(randomValue));
			randomTree2.Insert(std::make_unique<int>(randomValue));
		}

		srand((unsigned int)time(NULL));

		for (unsigned int index = 0; index < 20; index++)
		{
			randomValue = rand() % 100;
			assert(randomTree1.Search(randomValue) == randomTree2.Search(randomValue));
			assert(randomTree1.Delete(randomValue) == randomTree2.Delete(randomValue));
			assert(randomTree1.Search(randomValue) == randomTree2.Search(randomValue));
		}

		randomTreeTraverse1 = randomTree1.TraverseInOrder(randomTree1.GetRootNode().lock());
		randomTreeTraverse2 = randomTree2.TraverseInOrder(randomTree2.GetRootNode().lock());

		assert(randomTreeTraverse1.size() == randomTreeTraverse2.size());

		while (randomTreeTraverse1.size() != 0)
		{
			assert(randomTreeTraverse1.back() == randomTreeTraverse2.back());
			randomTreeTraverse1.pop_back();
			randomTreeTraverse2.pop_back();
		}
	}
}

void Test_Delete_0hoo()
{
	bool bDelete = false;
	bool bSearch = false;
	BinarySearchTree<int> tree;
	std::vector<int> traverseResult;

	bDelete = tree.Delete(15);
	bSearch = tree.Search(15);
	traverseResult = tree.TraverseInOrder(tree.GetRootNode().lock());
	assert(!bDelete);
	assert(!bSearch);
	assert(traverseResult.empty());

	tree.Insert(std::make_unique<int>(15));
	traverseResult = tree.TraverseInOrder(tree.GetRootNode().lock());
	bDelete = tree.Delete(15);
	assert(bDelete);
	assert(traverseResult.size() == 1);
	assert(traverseResult[0] == 15);
	assert(tree.GetRootNode().lock() == nullptr);

	BinarySearchTree<int> tree1;
	tree1.Insert(std::make_unique<int>(10));
	tree1.Insert(std::make_unique<int>(5));
	tree1.Insert(std::make_unique<int>(15));
	bDelete = tree1.Delete(10);
	assert(bDelete);
	traverseResult = tree1.TraverseInOrder(tree1.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 15);

	BinarySearchTree<int> tree2;
	tree2.Insert(std::make_unique<int>(10));
	tree2.Insert(std::make_unique<int>(5));
	tree2.Insert(std::make_unique<int>(15));
	tree2.Insert(std::make_unique<int>(13));
	tree2.Insert(std::make_unique<int>(20));
	bDelete = tree2.Delete(10);
	assert(bDelete);
	traverseResult = tree2.TraverseInOrder(tree2.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 13);
	assert(traverseResult[2] == 15);
	assert(traverseResult[3] == 20);

	BinarySearchTree<int> tree3;
	tree3.Insert(std::make_unique<int>(10));
	tree3.Insert(std::make_unique<int>(5));
	tree3.Insert(std::make_unique<int>(15));
	tree3.Insert(std::make_unique<int>(20));
	bDelete = tree3.Delete(10);
	assert(bDelete);
	traverseResult = tree3.TraverseInOrder(tree3.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 15);
	assert(traverseResult[2] == 20);

	BinarySearchTree<int> tree4;
	tree4.Insert(std::make_unique<int>(10));
	tree4.Insert(std::make_unique<int>(5));
	tree4.Insert(std::make_unique<int>(15));
	tree4.Insert(std::make_unique<int>(13));
	tree4.Insert(std::make_unique<int>(14));
	tree4.Insert(std::make_unique<int>(20));
	bDelete = tree4.Delete(10);
	assert(bDelete);
	traverseResult = tree4.TraverseInOrder(tree4.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 13);
	assert(traverseResult[2] == 14);
	assert(traverseResult[3] == 15);
	assert(traverseResult[4] == 20);

	BinarySearchTree<int> tree5;
	tree5.Insert(std::make_unique<int>(10));
	tree5.Insert(std::make_unique<int>(5));
	tree5.Insert(std::make_unique<int>(15));
	tree5.Insert(std::make_unique<int>(13));
	tree5.Insert(std::make_unique<int>(20));
	bDelete = tree5.Delete(15);
	assert(bDelete);
	traverseResult = tree5.TraverseInOrder(tree5.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 10);
	assert(traverseResult[2] == 13);
	assert(traverseResult[3] == 20);

	BinarySearchTree<int> tree6;
	tree6.Insert(std::make_unique<int>(10));
	tree6.Insert(std::make_unique<int>(5));
	tree6.Insert(std::make_unique<int>(15));
	tree6.Insert(std::make_unique<int>(1));
	tree6.Insert(std::make_unique<int>(2));
	bDelete = tree6.Delete(5);
	assert(bDelete);
	traverseResult = tree6.TraverseInOrder(tree6.GetRootNode().lock());
	assert(traverseResult[0] == 1);
	assert(traverseResult[1] == 2);
	assert(traverseResult[2] == 10);
	assert(traverseResult[3] == 15);


	BinarySearchTree<int> tree7;
	tree7.Insert(std::make_unique<int>(10));
	tree7.Insert(std::make_unique<int>(5));
	tree7.Insert(std::make_unique<int>(15));
	tree7.Insert(std::make_unique<int>(13));
	tree7.Insert(std::make_unique<int>(20));
	tree7.Insert(std::make_unique<int>(17));
	tree7.Insert(std::make_unique<int>(25));
	bDelete = tree7.Delete(15);
	assert(bDelete);
	traverseResult = tree7.TraverseInOrder(tree7.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 10);
	assert(traverseResult[2] == 13);
	assert(traverseResult[3] == 17);
	assert(traverseResult[4] == 20);
	assert(traverseResult[5] == 25);

	BinarySearchTree<int> tree8;
	tree8.Insert(std::make_unique<int>(15));
	tree8.Insert(std::make_unique<int>(10));
	tree8.Insert(std::make_unique<int>(20));
	tree8.Insert(std::make_unique<int>(5));
	tree8.Insert(std::make_unique<int>(13));
	tree8.Insert(std::make_unique<int>(12));
	tree8.Insert(std::make_unique<int>(14));
	bDelete = tree8.Delete(10);
	assert(bDelete);
	traverseResult = tree8.TraverseInOrder(tree8.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 12);
	assert(traverseResult[2] == 13);
	assert(traverseResult[3] == 14);
	assert(traverseResult[4] == 15);
	assert(traverseResult[5] == 20);

	BinarySearchTree<int> tree9;
	tree9.Insert(std::make_unique<int>(10));
	tree9.Insert(std::make_unique<int>(5));
	tree9.Insert(std::make_unique<int>(15));
	tree9.Insert(std::make_unique<int>(13));
	tree9.Insert(std::make_unique<int>(20));
	tree9.Insert(std::make_unique<int>(25));
	bDelete = tree9.Delete(15);
	assert(bDelete);
	traverseResult = tree9.TraverseInOrder(tree9.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 10);
	assert(traverseResult[2] == 13);
	assert(traverseResult[3] == 20);
	assert(traverseResult[4] == 25);

	BinarySearchTree<int> tree10;
	tree10.Insert(std::make_unique<int>(15));
	tree10.Insert(std::make_unique<int>(10));
	tree10.Insert(std::make_unique<int>(20));
	tree10.Insert(std::make_unique<int>(5));
	tree10.Insert(std::make_unique<int>(13));
	tree10.Insert(std::make_unique<int>(14));
	bDelete = tree10.Delete(10);
	assert(bDelete);
	traverseResult = tree10.TraverseInOrder(tree10.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 13);
	assert(traverseResult[2] == 14);
	assert(traverseResult[3] == 15);
	assert(traverseResult[4] == 20);

	BinarySearchTree<int> tree11;
	tree11.Insert(std::make_unique<int>(10));
	tree11.Insert(std::make_unique<int>(5));
	tree11.Insert(std::make_unique<int>(15));
	tree11.Insert(std::make_unique<int>(13));
	tree11.Insert(std::make_unique<int>(20));
	tree11.Insert(std::make_unique<int>(17));
	tree11.Insert(std::make_unique<int>(25));
	tree11.Insert(std::make_unique<int>(18));
	bDelete = tree11.Delete(15);
	assert(bDelete);
	traverseResult = tree11.TraverseInOrder(tree11.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 10);
	assert(traverseResult[2] == 13);
	assert(traverseResult[3] == 17);
	assert(traverseResult[4] == 18);
	assert(traverseResult[5] == 20);
	assert(traverseResult[6] == 25);

	bDelete = tree11.Delete(15);
	assert(!bDelete);

	bDelete = tree11.Delete(17);
	assert(bDelete);
	traverseResult = tree11.TraverseInOrder(tree11.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 10);
	assert(traverseResult[2] == 13);
	assert(traverseResult[3] == 18);
	assert(traverseResult[4] == 20);
	assert(traverseResult[5] == 25);

	bDelete = tree11.Delete(17);
	assert(!bDelete);

	bDelete = tree11.Delete(10);
	assert(bDelete);
	traverseResult = tree11.TraverseInOrder(tree11.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 13);
	assert(traverseResult[2] == 18);
	assert(traverseResult[3] == 20);
	assert(traverseResult[4] == 25);


	BinarySearchTree<int> tree12;
	tree12.Insert(std::make_unique<int>(15));
	tree12.Insert(std::make_unique<int>(7));
	tree12.Insert(std::make_unique<int>(20));
	tree12.Insert(std::make_unique<int>(5));
	tree12.Insert(std::make_unique<int>(11));
	tree12.Insert(std::make_unique<int>(9));
	tree12.Insert(std::make_unique<int>(14));
	tree12.Insert(std::make_unique<int>(10));
	bDelete = tree12.Delete(7);
	assert(bDelete);
	traverseResult = tree12.TraverseInOrder(tree12.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 9);
	assert(traverseResult[2] == 10);
	assert(traverseResult[3] == 11);
	assert(traverseResult[4] == 14);
	assert(traverseResult[5] == 15);
	assert(traverseResult[6] == 20);

	bDelete = tree12.Delete(7);
	assert(!bDelete);

	bDelete = tree12.Delete(9);
	assert(bDelete);
	traverseResult = tree12.TraverseInOrder(tree12.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 10);
	assert(traverseResult[2] == 11);
	assert(traverseResult[3] == 14);
	assert(traverseResult[4] == 15);
	assert(traverseResult[5] == 20);

	bDelete = tree12.Delete(9);
	assert(!bDelete);

	bDelete = tree12.Delete(10);
	assert(bDelete);

	traverseResult = tree12.TraverseInOrder(tree12.GetRootNode().lock());
	assert(traverseResult[0] == 5);
	assert(traverseResult[1] == 11);
	assert(traverseResult[2] == 14);
	assert(traverseResult[3] == 15);
	assert(traverseResult[4] == 20);

	return;
}
