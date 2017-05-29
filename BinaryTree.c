#pragma 
#include <iostream>
using namespace std;
#include <stack>
#include <queue>

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};


template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(T* array, size_t sz, T invalid)
	{
		size_t idx = 0;
		_root = _CreateBinaryTree(array, sz, invalid, idx);
	}
	~BinaryTree()
	{
		_Destroy(_root);
	}
	void PrevOrder()//递归前序遍历
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void PrevOrderNoR() //非递归遍历
	{
		stack<Node*> s;
		Node* cur = _root;
		while (!s.empty() || cur)
		{
			while (cur)
			{
				cout << cur->_data << "  ";
				s.push(cur);
				cur = cur->_left;
			}
			cur = s.top()->_right;
			s.pop();
		}
		cout << endl;
	}
	void InOrder()   //中序递归遍历
	{
		_InOrder(_root);
		cout << endl;
	}
	void InOrderNoR() //中序非递归遍历
	{
		stack<Node*> s;
		Node* cur = _root;
		while (cur ||  !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			cout << top->_data << "  ";
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void PostOrder() //后续递归
	{
		_PostOrder(_root);
		cout << endl;
	}
	void PostOrderNoR() //后续非递归
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << "  ";
				prev = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}
	size_t Depth() //只有一个节点深度为1
	{
		return _depth(_root);
	}
	size_t LeaveSize()   //叶子节点个数
	{
		return _LeaveSize(_root);
	}
	size_t GetLeaveSize(size_t k)    //k层叶子节点个数
	{
		return _GetLeaveSize(_root, k);
	}
protected:
	size_t _LeaveSize(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		return _LeaveSize(root->_left) + _LeaveSize(root->_right)+1;
	}
	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}

	size_t _GetLeaveSize(Node* root, size_t  k) //获取K层叶子节点的个数
	{
		if (root == NULL)
		{
			return 0;
		}
		if (k == 1)
		{
			return 1;
		}
		return _GetLeaveSize(root->_left,k-1) + _GetLeaveSize(root->_right,k-1);
	}


	size_t _GetKLevelSize(Node* root, size_t k)
	{
		if (root == NULL)
			return 0;

		if (k == 1)
			return 1;

		return _GetKLevelSize(root->_left, k - 1)
			+ _GetKLevelSize(root->_left, k - 1);
	}

	size_t _depth(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->_left == NULL && root->_right == NULL)
		{
			return 1;
		}
		size_t leftdepth = _depth(root->_left);
		size_t rightdepth = _depth(root->_right);
		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
	}
	void _PostOrder(Node* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_data << "  ";
		}
	}
	void _InOrder(Node* root)
	{
		if (root != NULL)
		{
			_InOrder(root->_left);
			cout << root->_data << "  ";
			_InOrder(root->_right);
		}
	}
	void _PrevOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_data << "  ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
	}
	// { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	Node* _CreateBinaryTree(T* array,size_t  sz,T invalid, size_t& idx)  
	{
		Node* root = NULL;
		if (idx < sz && array[idx] != invalid)//两条件创建下一节点
		{
			root = new Node(array[idx]);
			root->_left = _CreateBinaryTree(array, sz, invalid, ++idx);
			root->_right = _CreateBinaryTree(array, sz, invalid, ++idx);
		}
		return root;
	}

private: 
	Node* _root;
};


void FunTest()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> a(array, sizeof(array) / sizeof(array[0]), '#');
	a.PrevOrder();
	a.PrevOrderNoR();
	a.InOrder();
	a.InOrderNoR();
	a.PostOrder();
	a.PostOrderNoR();
	cout<<a.Depth()<<endl;
	cout << a.GetLeaveSize(3) << endl;
}