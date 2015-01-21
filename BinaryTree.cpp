#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using std::stack;
using std::distance;
using std::cout;
using std::vector;


struct TreeNode{
	int value;
	TreeNode *leftChild, *rightChild;
	TreeNode(int val) :value(val),leftChild(nullptr),rightChild(nullptr){}
};


class BinaryTree{
public:
	TreeNode* CreateTree(vector<int> order, vector<int>inorder)
	{
	//	return PreorderCreate(order.begin(), order.end(), inorder.begin(), inorder.end());  //�����������������
		return PostOrderCreate(order.begin(), order.end(), inorder.begin(), inorder.end()); //�����������������
	}
	vector<int> Traversal(TreeNode *root,int i)     //1:���� 2������  3������
	{
		if (i == 1)                
			return PreTraversal(root);
		else if (i == 2)
			return InTraversal(root);
		else if (i == 3)
			return PostTraversal(root);
		else
			cout << "The number is wrong" << std::endl;
	}
	vector<vector<int>> levelOrderTraversal(TreeNode *root);
private:
	TreeNode* PreorderCreate(vector<int>::iterator, vector<int>::iterator, vector<int>::iterator, vector<int>::iterator);  //�����������������
	TreeNode* PostOrderCreate(vector<int>::iterator, vector<int>::iterator, vector<int>::iterator, vector<int>::iterator); //�����������������
	vector<int> PreTraversal(TreeNode *root); //����ջʵ�ַ���
	vector<int> InTraversal(TreeNode *root); //����ջʵ�ַ���
	vector<int> PostTraversal(TreeNode *root); //����ջʵ�ַ���
	void LevelTraversal(TreeNode *root, int level, vector<vector<int>> &result);
};

TreeNode* BinaryTree::PreorderCreate(vector<int>::iterator preBeg, vector<int>::iterator preEnd, vector<int>::iterator inBeg, vector<int>::iterator inEnd)
{
	if (preBeg == preEnd)
		return nullptr;
	if (inBeg == inEnd)
		return nullptr;
	TreeNode *root=new TreeNode(*preBeg);
	auto inCut = find(inBeg, inEnd, *preBeg);
	auto left = distance(inBeg, inCut);  //�ҵ�ƫ���������ݸ��ڵ�ȷ����������
	root->leftChild = PreorderCreate(next(preBeg), next(preBeg,left+1),inBeg,inCut);  //�ݹ齨����������
	root->rightChild = PreorderCreate(next(preBeg,left+1) , preEnd, next(inCut), inEnd);
	return root;
}

TreeNode* BinaryTree::PostOrderCreate(vector<int>::iterator postBeg, vector<int>::iterator postEnd, vector<int>::iterator inBeg, vector<int>::iterator inEnd)
{
	if (postBeg == postEnd)
		return nullptr;
	if (inBeg == inEnd)
		return nullptr;
	TreeNode *root = new TreeNode(*prev(postEnd));
	auto inCut = find(inBeg, inEnd, *prev(postEnd));
	auto left = distance(inBeg, inCut);  //�ҵ�ƫ���������ݸ��ڵ�ȷ����������
	root->leftChild = PostOrderCreate(postBeg,next(postBeg,left),inBeg,inCut);  //�ݹ齨����������
	root->rightChild = PostOrderCreate(next(postBeg, left), prev(postEnd), next(inCut), inEnd);
	return root;
}


vector<int>  BinaryTree::PreTraversal(TreeNode *root)//�������ջʵ��
{
	stack<TreeNode*> s;
	vector<int> result;
	TreeNode *p = root;
	while (p||!s.empty())
	{	
		if (p)
		{
			result.push_back(p->value);
			s.push(p);
			p = p->leftChild;
		}
		else
		{
			p = s.top();
			s.pop();
			p = p->rightChild;
		}
	}
	return result;
}


vector<int>  BinaryTree::InTraversal(TreeNode *root)//�������ջʵ��
{
	stack<TreeNode*> s;
	vector<int> result;
	TreeNode *p = root,*q;
	while (p || !s.empty())
	{
		if (p)
		{
			s.push(p);
			p = p->leftChild;
		}
		else
		{
			p = s.top();
			s.pop();
			result.push_back(p->value);
			p = p->rightChild;
		}
	}
	return result;
}

vector<int>  BinaryTree::PostTraversal(TreeNode *root)//�������ջʵ��
{
	stack<TreeNode*> s;
	vector<int> result;
	TreeNode *p = root,*q=nullptr;
	do
	{
		while (p)
		{
			s.push(p);
			p = p->leftChild;
		}
		q = nullptr;
		while (!s.empty())
		{
			p = s.top();
			s.pop();
			if (p->rightChild == q)
			{
				result.push_back(p->value);
				q = p;
			}
			else
			{
				s.push(p);
				p = p->rightChild;
				break;
			}
		}

	} while (!s.empty());
	return result;
}

vector<vector<int>> BinaryTree::levelOrderTraversal(TreeNode *root)
{
	vector<vector<int>> result;
	LevelTraversal(root,1,result);
	return result;
}

void BinaryTree::LevelTraversal(TreeNode *root, int level, vector<vector<int>> &result)  //������i��
{
	if (!root)
		return;
	if (level > result.size())
		result.resize(result.size()+1);
	result[level - 1].push_back(root->value);
	LevelTraversal(root->leftChild, level + 1, result);
	LevelTraversal(root->rightChild, level + 1, result);

}



int main()
{
	vector<int> pre({ 1, 2, 4, 5, 8, 3, 6, 7, 9 });
	vector<int> in({ 4, 2, 5, 8, 1, 6, 3, 9, 7 });
	vector<int> post({ 4, 8, 5, 2, 6, 9, 7, 3, 1 });
	BinaryTree solution;
//	TreeNode* root = solution.CreateTree(pre, in);//����������������
	TreeNode* root = solution.CreateTree(post, in);
	vector<int> result = solution.Traversal(root, 1);//�������
	for (auto c : result)
		cout << c << " ";
	cout << std::endl;
	result = solution.Traversal(root, 2);//�������
	for (auto c : result)
		cout << c << " ";
	cout << std::endl;
	result = solution.Traversal(root, 3);//�������
	for (auto c : result)
		cout << c << " ";
	cout << std::endl;

	vector<vector<int>> result2 = solution.levelOrderTraversal(root);//��ȱ���
	for (auto c : result2)
	{
		for (auto a : c)
			cout << a << " ";
		cout << std::endl;
	}


	system("pause");
	return 0;
}