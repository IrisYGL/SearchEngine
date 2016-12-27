#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

//数据结构部分
#include <iostream>

//栈的实现(用模板类)
template <typename T>
class Stack
{
private:
	T * base;
	int volume;
	int length;

public:
	Stack();
	~Stack();
	void Push(T e);				 //压栈
	void Pop();					 //退栈
	T Top();					 //获取栈顶元素
	bool Empty();				 //判断栈是否为空
	int size() const;			//获得栈的大小，外部调用时private的length不可访问
};

//栈的实现（模板类需要接在这下面写，而不能写在data structure.cpp里）
template <typename T> Stack<T>::Stack()
{
	length = 0;
	volume = 50;
	base = new T [volume];
}

template <typename T> Stack<T>::~Stack()
{
	delete[] base;
}

template <typename T> void Stack <T>::Pop()
{
	if(length <= 0)
		return;
	length--;
}

template <typename T> void Stack <T>::Push(T e)   
{
	if(length >= volume)
	{
		volume = volume * 2;
		T * b = new T[volume];
		for (int i = 0; i < length; i++)
		{
			b[i] = base[i];
		}
		delete[]base;					//动态扩容
		base = b;
	}
	base[length] = e;
	length++;
}

template <typename T> T Stack<T>::Top()
{
	if(length <= 0)
		return T();
	return base[length - 1];
}

template <typename T> bool Stack<T>::Empty()
{
	return length == 0;
}

template <typename T> int Stack<T>::size() const
{
	return length;
}


//字符串的实现
class CharString
{
private:
	int length;
	char *a;

public:
	CharString();
	~CharString();
	CharString(const char * s);
	CharString(const CharString & s);
	const char * c_str() const;                               //获得头指针
	char getenum(int i);									  //获取字符串下标为i的字符
	int len();												  //获取字符串长度
	int indexOf(const CharString& s, int pos = 0) const;	  //查找子串的位置
	void operator = (const CharString& st);					  //=的重载
	void operator = (char* st);								  //=的重载
	bool operator == (const CharString& st) const;			  //==的重载
	bool operator < (const CharString& st) const;			  //<的重载
	bool operator > (const CharString& st) const;			  //>的重载
	CharString substring(int index, int len);				  //截取字符串
	void concat(const CharString& b);						  //连接字符串
	CharString operator+(const CharString& S);  			  //+的重载，连接字符串
	void operator += (const CharString &S);					  //+=的重载，同样用于连接字符串
	char& operator[](int i);								  //[]的重载
	friend std::ostream & operator << (std::ostream & cout, const CharString & s);    //<<的重载，用于输出字符串
};


//字符串链表的实现
class CharStringLink
{
public:
	struct Node
	{
		CharString m;
		Node *next;
	};

private:
	int num;
	Node *head, *tail, *cur;

public:
	CharStringLink();
	CharStringLink(CharStringLink & s);
	~CharStringLink();
	void add(CharString & s);									//添加元素
	void remove(CharString s);								//删除元素
	void removeAt(int index);								//删除指定位置的元素
	int length() const;										//获得链表长度
	Node* search(CharString s);								//查找某元素位置
	Node* cur_func();										//返回cur指针
	void moveToBegin()										//将现在的指针移到头部
	{
		cur = head;
	}
	Node* next()											//将现在的指针后移一个位置
	{
		cur = cur->next;
		return cur;
	}
};

#endif