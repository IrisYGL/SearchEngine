#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

//���ݽṹ����
#include <iostream>

//ջ��ʵ��(��ģ����)
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
	void Push(T e);				 //ѹջ
	void Pop();					 //��ջ
	T Top();					 //��ȡջ��Ԫ��
	bool Empty();				 //�ж�ջ�Ƿ�Ϊ��
	int size() const;			//���ջ�Ĵ�С���ⲿ����ʱprivate��length���ɷ���
};

//ջ��ʵ�֣�ģ������Ҫ����������д��������д��data structure.cpp�
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
		delete[]base;					//��̬����
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


//�ַ�����ʵ��
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
	const char * c_str() const;                               //���ͷָ��
	char getenum(int i);									  //��ȡ�ַ����±�Ϊi���ַ�
	int len();												  //��ȡ�ַ�������
	int indexOf(const CharString& s, int pos = 0) const;	  //�����Ӵ���λ��
	void operator = (const CharString& st);					  //=������
	void operator = (char* st);								  //=������
	bool operator == (const CharString& st) const;			  //==������
	bool operator < (const CharString& st) const;			  //<������
	bool operator > (const CharString& st) const;			  //>������
	CharString substring(int index, int len);				  //��ȡ�ַ���
	void concat(const CharString& b);						  //�����ַ���
	CharString operator+(const CharString& S);  			  //+�����أ������ַ���
	void operator += (const CharString &S);					  //+=�����أ�ͬ�����������ַ���
	char& operator[](int i);								  //[]������
	friend std::ostream & operator << (std::ostream & cout, const CharString & s);    //<<�����أ���������ַ���
};


//�ַ��������ʵ��
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
	void add(CharString & s);									//���Ԫ��
	void remove(CharString s);								//ɾ��Ԫ��
	void removeAt(int index);								//ɾ��ָ��λ�õ�Ԫ��
	int length() const;										//���������
	Node* search(CharString s);								//����ĳԪ��λ��
	Node* cur_func();										//����curָ��
	void moveToBegin()										//�����ڵ�ָ���Ƶ�ͷ��
	{
		cur = head;
	}
	Node* next()											//�����ڵ�ָ�����һ��λ��
	{
		cur = cur->next;
		return cur;
	}
};

#endif