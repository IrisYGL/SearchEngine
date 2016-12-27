#include "data structure.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>
using namespace std;



//字符串的实现
const char * CharString::c_str() const
{
	return a;
}

char CharString::getenum(int n)
{
	return a[n-1];
}

int CharString::len()
{
	return length;
}


CharString::CharString()
{
	length = 0;
	a = new char[length + 1];
	a[0] = '\0';
}

CharString::CharString(const CharString & s)
{
	length = s.length;
	a = new char[length + 1];
	strcpy_s(a, length + 1, s.a);
}

CharString::~CharString()
{
	delete[] a;
}

CharString::CharString(const char * s)
{
	length = strlen(s);
	a = new char[length + 1];
	strcpy_s(a, length + 1, s);
}

int CharString::indexOf(const CharString &s, int pos)const
{
	if(pos < 0)
		pos = 0;
	int *next = new int[s.length + 1];
	next[0] = -1;
	int j = -1, i = 0;
	while (i < s.length)
	{
		if (j == -1 || s.a[i] == s.a[j])
		{
			++i;
			++j;
			if (s.a[i] != s.a[j])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}
	i = pos;
	j = 0;
	while (i < length && j < s.length)
	{
		if (j == -1 || a[i] == s.a[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	delete[] next;
	if (j >= s.length)
		return i - s.length;
	else
		return -1;
}

void CharString::operator=(const CharString &st)
{
	delete[] a;
	length = st.length;
	a = new char[length + 1];
	strcpy_s(a, length + 1, st.a);
	a[length] = '\0';
}

char& CharString::operator[](int i)
{
	if (i < 0)
		i = 0;
	if (i >= length)
		i = length - 1;
	return a[i];
}

void CharString::operator=(char *st)
{
	delete a;
	length = strlen(st);
	a = new char[length + 1];
	strcpy_s(a, length + 1, st);
	a[length] = '\0';
}

bool CharString:: operator==(const CharString &st) const
{
	return !strcmp(a, st.a);
}

bool CharString:: operator < (const CharString &st) const
{
	if(strcmp(a, st.a) < 0) 
		return 1;
	else
		return 0;
}

bool CharString:: operator > (const CharString &st) const
{
	if(strcmp(a, st.a) > 0)
		return 1;
	else
		return 0;
}

CharString CharString::operator+(const CharString &S)
{
	CharString r;
	r.length = length + S.length;
	delete[] r.a;
	r.a = new char[r.length + 1];
	strcpy_s(r.a, r.length + 1, a);
	strcat_s(r.a, r.length + 1, S.a);
	return r;
}

void CharString::operator+=(const CharString&S)
{
	length += S.length;
	char * t = new char[length + 1];
	strcpy_s(t, length + 1, a);
	strcat_s(t, length + 1, S.a);
	delete[] a;
	a = t;
}

ostream & operator << (ostream & cout, const CharString & s)
{
	cout << s.a;
	return cout;
}


CharString CharString::substring(int index, int len)
{
	CharString m;
	int begin = index;
	int end = index + len;
	if (begin < 0 || begin >= length)
		begin = 0;
	if (end < 0 || end >= length)
		end = length;
	m.length = end - begin;
	delete[] m.a;
	m.a = new char[m.length + 1];
	strncpy_s(m.a, m.length + 1, a + begin, m.length);
	return m;
}

void CharString::concat(const CharString& b)
{
	*this += b;
}



//字符串链表的实现
CharStringLink::CharStringLink()
{
	num = 0;
	head = new Node;
	head->next = nullptr;
	tail = head;
}

CharStringLink::CharStringLink(CharStringLink & s)
{
	num = 0;
	head = new Node;
	head->next = nullptr;
	tail = head;
	s.cur = s.head->next;
	while (s.cur)
	{
		add(s.cur->m);
		s.cur = s.cur->next;
	}
}

CharStringLink::~CharStringLink()
{
	while (head)
	{
		tail = head;
		head = head->next;
		delete tail;
	}
}

void CharStringLink :: add(CharString & s)
{
	cur = new Node;
	cur->m = s;
	cur->next = nullptr;
	tail->next = cur;
	tail = cur;
	num++;
}

void CharStringLink :: remove(CharString s)
{
	cur = head;
	while (cur->next && !(cur->m == s))
	{
		cur = cur->next;
	}
	if (cur->next = nullptr)
		return;

	Node * p = cur->next;
	if (p == tail)
		tail = cur;
	cur->next = p->next;
	num--;
	delete p;
}

CharStringLink::Node* CharStringLink::search(CharString s)
{
	cur = head->next;
	while (cur)
	{
		if (cur->m == s)
		{
			return cur;
		}
		cur = cur->next;
	}
	return nullptr;
}

void CharStringLink::removeAt(int index)
{
	if (index <= 0 || index > num)
		return;
	cur = head;
	for (int i = 1; i < index; ++i)
	{
		cur = cur->next;
	}
	Node * p = cur->next;
	if (p == tail)
		tail = cur;
	cur->next = p->next;
	delete p;
	num--;
}

int CharStringLink::length() const
{
	return num;
}

CharStringLink :: Node *CharStringLink::cur_func()
{
	return cur;
}