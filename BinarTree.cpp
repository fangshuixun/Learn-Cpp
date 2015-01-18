//C++实现二叉树
//主要练习了建立二叉树，二叉树的遍历
//关键点：类成员函数指针


#include<iostream>
#include<istream>
#include<exception>
using std::bad_alloc;
using std::istream;
using std::cin;
using std::cout;
using std::endl;

template<class T>
class TreeNode{
public:
	T leaf;
	TreeNode *leftChild;
	TreeNode *rightChild;
	TreeNode() :leaf(0), leftChild(nullptr), rightChild(nullptr){};
	explicit TreeNode(int value, TreeNode *l = nullptr, TreeNode *r = nullptr) :leaf(value), leftChild(l), rightChild(r){}
};

template<typename T>
class BinaryTree{
private:
	TreeNode<T> *root;
	int highth;
	int leafNumber;
	int TreeCount;
	void CreateTree(TreeNode<T>* &r);
	bool deleteLeaf(TreeNode<T>* &leaf);
	bool print(TreeNode<T>* &leaf);
	void preOrderTraverse(TreeNode<T> *node, bool(BinaryTree<T>::*visit)(TreeNode<T>* &element));
	void backOrderTraverse(TreeNode<T> *node, bool(BinaryTree<T>::*visit)(TreeNode<T>* &element));
public:
	BinaryTree() :root(nullptr), leafNumber(0), TreeCount(0){ cout << "construct" << endl; }
	BinaryTree(int i);
	void Traverse(bool(BinaryTree<T>::*visit)(TreeNode<T>* &element));
	void Print();
	~BinaryTree();
};

template<typename T>
void BinaryTree<T>::CreateTree(TreeNode<T>* &r)  //指针的引用，不然是值传递
{
	T leaf;
	cin.get(leaf);
	if (leaf == ' ')
		r = nullptr;
	else
	{
		r = new TreeNode<T>(leaf);
		CreateTree(r->leftChild);
		CreateTree(r->rightChild);
	}
}


template<typename T>
BinaryTree<T>::BinaryTree(int i)
{
	CreateTree(root);
	cout << "constructed" << endl;
}


template<typename T>
void BinaryTree<T>::preOrderTraverse(TreeNode<T> *node, bool(BinaryTree<T>::*visit)(TreeNode<T>* &element))  //类成员函数的运用
{
	if (!node)
		return;
	else
	{
		(this->*visit)(node);
		preOrderTraverse(node->leftChild, visit);
		preOrderTraverse(node->rightChild, visit);
	}
}

template<typename T>
void BinaryTree<T>::backOrderTraverse(TreeNode<T> *node, bool(BinaryTree<T>::*visit)(TreeNode<T>* &element))
{
	if (!node)
		return;
	else
	{
		backOrderTraverse(node->leftChild, visit);
		backOrderTraverse(node->rightChild, visit);
		(this->*visit)(node);
	}
}


template<typename T>
bool BinaryTree<T>::print(TreeNode<T>* &node)
{
	cout << node->leaf << " ";
	return true;
}

template <typename T>
bool BinaryTree<T>::deleteLeaf(TreeNode<T>* &node)
{
	try
	{
		delete node;
	}
	catch (bad_alloc err)
	{
		return false;
	}
	return true;
}

template<typename T>
void BinaryTree<T>::Traverse(bool(BinaryTree<T>::*visit)(TreeNode<T>* &element))
{
	backOrderTraverse(root,visit);
}

template<typename T>
void BinaryTree<T>::Print()
{
	Traverse(&BinaryTree<T>::print);
}

template<typename T>
BinaryTree<T>::~BinaryTree()  //析构后序遍历
{
	if (root)
		Traverse(&BinaryTree<T>::deleteLeaf);
	cout << "deconstruct" << endl;
}

int main()
{
	//BinaryTree<char> tree1;
	BinaryTree<char> tree2(1);
	tree2.Print();
	system("pause");
	return 0;
}