#pragma once
#include <iostream>

template <typename T>
struct Node
{
	T value;
	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};

template <typename T>
class BinaryTree
{
	int size;
	Node<T>* root;
public:
	BinaryTree();

	Node<T>* Root();
	int Size();

	Node<T>* CreateNode(Node<T>* parent, T value);

	Node<T>* Find(T value);

	void AddNodeLoop(T value);
	void AddNodeReq(T value, Node<T>* node = nullptr);

	void DeleteNode(Node<T>* node);
	void DeleteBranch(Node<T>* node);

	Node<T>* Min(Node<T>* node = nullptr);
	Node<T>* Max(Node<T>* node = nullptr);

	void PrintBranch(Node<T>* node);
	void Print();

	~BinaryTree();
};




template<typename T>
inline BinaryTree<T>::BinaryTree() : size{}, root{ nullptr } {}

template<typename T>
inline Node<T>* BinaryTree<T>::Root(){ return root; }

template<typename T>
inline int BinaryTree<T>::Size(){ return size; }

template<typename T>
inline Node<T>* BinaryTree<T>::CreateNode(Node<T>* parent, T value)
{
	Node<T>* nodeNew = new Node<T>;
	nodeNew->parent = parent;
	nodeNew->value = value;
	return nodeNew;
}

template<typename T>
inline Node<T>* BinaryTree<T>::Find(T value)
{
	Node<T>* nodeCurrent{ root };

	while (nodeCurrent)
	{
		if (nodeCurrent->value == value)
			break;
		else
		{
			if (value <= nodeCurrent->value)
				nodeCurrent = nodeCurrent->left;
			else
				nodeCurrent = nodeCurrent->right;
		}
	}
	return nodeCurrent;
}

template<typename T>
inline void BinaryTree<T>::AddNodeLoop(T value)
{
	if (!root)
	{
		root = CreateNode(nullptr, value);
		size = 1;
		return;
	}

	Node<T>* nodeCurrent = root;
	Node<T>* nodeParent = nullptr;

	while (nodeCurrent)
	{
		nodeParent = nodeCurrent;
		if (value <= nodeCurrent->value)
			nodeCurrent = nodeCurrent->left;
		else
			nodeCurrent = nodeCurrent->right;
	}

	nodeCurrent = CreateNode(nodeParent, value);
	if (value <= nodeParent->value)
		nodeParent->left = nodeCurrent;
	else
		nodeParent->right = nodeCurrent;

	size++;
}

template<typename T>
inline void BinaryTree<T>::AddNodeReq(T value, Node<T>* node)
{
	if (!root)
	{
		root = CreateNode(nullptr, value);
		size = 1;
		return;
	}

	if (!node)
		node = root;

	if (value <= node->value)
	{
		if (node->left)
			AddNodeReq(value, node->left);
		else
			node->left = CreateNode(node, value);
	}
	else
	{
		if (node->right)
			AddNodeReq(value, node->right);
		else
			node->right = CreateNode(node, value);
	}

	size++;
}

template<typename T>
inline void BinaryTree<T>::DeleteNode(Node<T>* node)
{
	// delete leaf
	if (!node->left && !node->right)
	{
		if (node == root)
			root = nullptr;
		else
		{
			if (node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
		}
		delete node;
		size--;
		return;
	}

	// delete node with single child
	if ((bool)node->left ^ (bool)node->right)
	{
		Node<T>* nodeChild;
		if (node->left)
			nodeChild = node->left;
		else
			nodeChild = node->right;

		if (node == root)
			root = nodeChild;
		else
		{
			if (node->parent->left == node)
				node->parent->left = nodeChild;
			else
				node->parent->right = nodeChild;
		}

		delete node;
		size--;
		return;
	}

	// delete node with pair childs
	Node<T>* nodeMinRight = Min(node->right);
	node->value = nodeMinRight->value;
	DeleteNode(nodeMinRight);
}

template<typename T>
inline void BinaryTree<T>::DeleteBranch(Node<T>* node)
{
	if (node->left)
		DeleteBranch(node->left);
	if (node->right)
		DeleteBranch(node->right);
	
	if (node->parent->left == node)
		node->parent->left = nullptr;
	else
		node->parent->right = nullptr;

	delete node;
}

template<typename T>
inline Node<T>* BinaryTree<T>::Min(Node<T>* node)
{
	if (!node)
		node = root;

	while (node->left)
		node = node->left;
	return node;
}

template<typename T>
inline Node<T>* BinaryTree<T>::Max(Node<T>* node)
{
	if (!node)
		node = root;

	while (node->right)
		node = node->right;
	return node;
}

template<typename T>
inline void BinaryTree<T>::PrintBranch(Node<T>* node)
{
	if (node)
	{
		PrintBranch(node->left);
		std::cout << node->value << " ";
		PrintBranch(node->right);
	}
}

template<typename T>
inline void BinaryTree<T>::Print()
{
	PrintBranch(this->root);
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
	DeleteBranch(root);
}
