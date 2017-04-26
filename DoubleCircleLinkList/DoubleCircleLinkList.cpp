// DoubleCircleLinkList.cpp : 定义控制台应用程序的入口点。
#include<iostream>
#include<assert.h>
using namespace std;
template<class T>struct LinkNode
{
	LinkNode<T>*_next;
	LinkNode<T>*_prev;
	T _data;
	LinkNode(const T&x) :_data(x), _next(NULL), _prev(NULL)
	{}
};
template<class T, class Ref, class Ptr>struct Iterator
{
	typedef LinkNode<T>Node;
	Node*_node;
	typedef Iterator<T, Ref, Ptr>Sef;
	Iterator()
	{
		//默认构造函数
	}
	Iterator(Node*node) :_node(node)
	{
	}
	bool operator==(const Sef&s)const
	{
		return _node == s._node;
	}
	bool operator!=(const Sef&s)const
	{
		return _node != s._node;
	}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return _node;
	}
	Sef&operator++()
	{
		//前置++
		_node = _node->_next;
		return *this;
	}
	Sef operator++(int)
	{
		//后置++
		Sef tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	Sef&operator--()
	{
		//前置--
		_node = _node->_prev;
		return *this;
	}
	Sef operator--(int)
	{
		//后置--
		Sef tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
};
template<class T>class LinkList
{
	typedef LinkNode<T>Node;
protected:
	Node*_head;
public:
	typedef Iterator<T, T&, T*>LinkIterator;
	LinkList()
	{
		_head = CreateNode(T());//传默认参数
		_head->_next = _head;//设置哨兵
		_head->_prev = _head;
	}
	LinkList(const LinkList<T>&l)
	{
		_head = CreateNode(T());
		_head->_next = _head;
		_head->_prev = _head;
		Node*cur = l._head->_next;
		while (cur != l._head)
		{
			Insert(End(), cur->_data);
			cur = cur->_next;
		}
	}
	LinkList<T>&operator=(LinkList<T>l)
	{
		std::swap(_head, l._head);
		return *this;
	}
	~LinkList()
	{
		Node*cur = _head->_next;
		while (cur != _head)
		{
			Node*del = cur;
			cur = cur->_next;
			delete del;
			del = NULL;
		}
		delete _head;
	}
	void PushBack(const T&x)
	{
		Insert(End(), x);
	}
	void PushFront(const T&x)
	{
		Insert(Begin(), x);
	}
	void PopBack()
	{
		Erase(--End());
	}
	void PopFront()
	{
		Erase(Begin());
	}
	void Insert(LinkIterator pos, const T&x)
	{
		//在指定位置前插
		Node*cur = pos._node;
		Node*prev = cur->_prev;
		Node*NewNode = CreateNode(x);
		NewNode->_next = cur;
		cur->_prev = NewNode;
		prev->_next = NewNode;
		NewNode->_prev = prev;
	}
	void Erase(LinkIterator pos)
	{
		assert(pos != End());
		Node*del = pos._node;
		del->_prev->_next = del->_next;
		del->_next->_prev = del->_prev;
		delete del;
		del = NULL;
	}
	LinkIterator Begin()
	{
		return LinkIterator(_head->_next);
	}
	LinkIterator End()
	{
		return LinkIterator(_head);
	}
protected:
	Node*CreateNode(const T&x)
	{
		Node *NewNode = new  Node(x);
		return NewNode;
	}
};
void testIterator()
{
	LinkList<int>l;
	for (int i = 0; i < 10; i++)
	{
		l.PushBack(i + 1);
	}
	LinkList<int>::LinkIterator it = l.Begin();
	while (it != l.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		l.PopBack();
	}
	LinkList<int>::LinkIterator it1 = l.Begin();
	while (it1 != l.End())
	{
		cout << *it1 << " ";
		++it1;
	}
	cout << endl;
}
void test1()
{
	LinkList<int>l1;
	for (int i = 0; i < 10; i++)
	{
		l1.PushFront(i + 1);
	}
	LinkList<int>::LinkIterator it = l1.Begin();
	while (it != l1.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		l1.PopFront();
	}
	LinkList<int>::LinkIterator it1 = l1.Begin();
	while (it1 != l1.End())
	{
		cout << *it1 << " ";
		++it1;
	}
	cout << endl;
}
void test2()
{
	LinkList<int>l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	LinkList<int>::LinkIterator it = l1.Begin();
	while (it != l1.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	LinkList<int>l2(l1);
	l2.PushBack(5);
	LinkList<int>::LinkIterator it1 = l2.Begin();
	while (it1 != l2.End())
	{
		cout << *it1 << " ";
		++it1;
	}
	cout << endl;
	l1 = l2;
	LinkList<int>::LinkIterator it2 = l1.Begin();
	while (it2 != l1.End())
	{
		cout << *it2 << " ";
		++it2;
	}
	cout << endl;
}
int main()
{
	test1();
	test2();
	system("pause");
	return 0;
}