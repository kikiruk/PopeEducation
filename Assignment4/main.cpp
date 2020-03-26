#include <cassert>
#include <ctime>
#include <iostream>
#include "TreeNode.h"
#include "BinarySearchTree.h"

using namespace assignment4;
using namespace std;

int main()
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

	cout << tree.Delete(10) << endl;

	vector<int> test = tree.TraverseInOrder(tree.GetRootNode().lock());

	for (int i = 0; i < 8; i++)
		cout << test[i] << " ,";

	cout << endl;

	cout << tree.Delete(20) << endl;

	test = tree.TraverseInOrder(tree.GetRootNode().lock());

	for (int i = 0; i < 7; i++)
		cout << test[i] << " ,";

	cout << endl;

	cout << tree.Delete(15) << endl;

	test = tree.TraverseInOrder(tree.GetRootNode().lock());

	for (int i = 0; i < 6; i++)
		cout << test[i] << " ,";

	cout << endl;

	return 0;
}

