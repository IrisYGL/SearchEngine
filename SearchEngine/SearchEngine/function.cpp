#include "data structure.h"
#include "function.h"
#include "AVLTree.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>
using namespace std;
#define HASH_TABLE_LEN 100000
#define CHINESE_MIN 0x4e00
#define CHINESE_MAX 0x9fbb

//读取html文件
void ReadHtml(CharString filename, CharString & s)
{
	fstream fin(filename.c_str(), fstream::in);
	if (!fin.is_open())
	{
		cout << "Open file failed" << endl;
		return;
	}

	char s0[10000];
	while(fin.getline(s0, 10000))
	{
		int l = strlen(s0);
		s0[l] = '\n';
		s0[l + 1] = '\0';
		s += s0;
	}
}


//网页解析
CharString AnalyseHtml(CharString & fs, CharString & rootPath, CharString & filename)
{
	CharString str;
	Stack<CharString> S;
	CharStringLink content;
	CharString label;
	int p1, p2, flag;
	p1 = p2 = flag = 0;
	int begin = 0;
	int len = 0;
	wchar_t buf[20] = L"客官，这篇文章有意思吗";
	int size = WideCharToMultiByte(CP_UTF8, 0, buf, -1, nullptr, 0, 0, 0);
	char * tempBuf = new char[size];
	WideCharToMultiByte(CP_UTF8, 0, buf, -1, tempBuf, size, 0, 0);
	while (1)
	{
		p1 = fs.indexOf("<", p2);
		if (p1 < 0)
			break;
		if (fs.getenum(p1 + 2) == '/')
		{
			S.Pop();
			if (S.size() == len - 1)
			{
				CharString temp = fs.substring(begin, p1 - begin);
				
				if(flag == 1)
				{
					if (temp.indexOf(tempBuf) >= 0)
						;
					else
					{
						str += temp;
						content.add(temp);
					}
					flag = 0;
				}
				else
					content.add(temp);
				len = 0;
			}
		}
		else
		{
			S.Push("<");
		}
		p2 = fs.indexOf(">", p1);
		if (p2 < 0)
			break;
		label = fs.substring(p1, p2 - p1 + 1);
		if (label.indexOf("<!doctype html") >= 0 ||
			label.indexOf("<meta") >= 0 ||
			label.indexOf("<base") >= 0 ||
			label.indexOf("<img") >= 0 ||
			label.indexOf("<link") >= 0 ||
			label.indexOf("<br") >= 0 ||
			label.indexOf("<hr") >= 0)
		{
			S.Pop();
		}
		else if (label.indexOf("\"author\"") >= 0||
			label.indexOf("\"question-title\"") >= 0||
			label.indexOf("\"headline-title\"") >= 0||
			label.indexOf("class=\"content\"") >= 0)
		{
			if (label.indexOf("class=\"content\"") >= 0 && flag)
			{

			}
			else
			{
				if (!flag)
				{
					flag = 1;
				}
				else
					flag = 0;
				begin = p2 + 1;
				len = S.size();
			}
		}
	}

	//cout << S.size() << endl;

	fstream fout((rootPath + filename).c_str(), fstream::out);
	//cout << (rootPath + filename).c_str() << endl;
	if (!fout.is_open())
	{
		cout << "Open file failed" << endl;
	}

	//content.removeAt(content.length());
	content.moveToBegin();
	for (CharStringLink::Node * p = content.next(); p; p = content.next())
	{
		CharString data;
		p2 = p1 = -1;
		while (1)
		{
			p1 = p->m.indexOf("<", p2);
			if (p1 < 0)
			{
				data += p->m.substring(p2 + 1, p->m.len() - p2 - 1);
				break;
			}
			data += p->m.substring(p2 + 1, p1 - 1 - p2);
			p2 = p->m.indexOf(">", p1);
			if (p2 < 0)
				break;
		}
		fout << data << endl;
	}
	delete[] tempBuf;
	return str;
}


//用哈希函数生成字符串对应的哈希表中的位置
unsigned int hash_func(CharString s)
{
	const char *a = s.c_str();
	unsigned int h;
	char *p;
	for(h = 0, p = (char*)a; *p; p++)
	{
		h = 31 * h + *p;
	}
	return h % HASH_TABLE_LEN;
}


//词库的读入
CharStringLink * ReadDic(CharString & filename, int * maxWordLength)
{
	ifstream fin(filename.c_str(), fstream::in);
	if (!fin.is_open())
	{
		cout << "Open file failed" << endl;
		return nullptr;
	}
	char s0[100];
	CharStringLink *a = new CharStringLink[HASH_TABLE_LEN];
	while(fin.getline(s0, 100))
	{
		int sub = 0;
		unsigned char ch = (unsigned char)s0[0];
		if (ch >= 0xFC)
			sub = 6;
		else if (ch >= 0xF8)
			sub = 5;
		else if (ch >= 0xF0)
			sub = 4;
		else if (ch >= 0xE0)
			sub = 3;
		else if (ch >= 0xC0)
			sub = 2;
		else
			sub = 1;
		unsigned int hash = hash_func(s0);
		a[hash].add(CharString(s0));
		int l = strlen(s0);
		s0[sub + 1] = '\0';
		int size = MultiByteToWideChar(CP_UTF8, 0, s0, -1, nullptr, 0);
		wchar_t * buf = new wchar_t[size];
		MultiByteToWideChar(CP_UTF8, 0, s0, -1, buf, size);
		if (buf[0] >= CHINESE_MIN && buf[0] <= CHINESE_MAX)
		{
			if (maxWordLength[buf[0] - CHINESE_MIN] < l)
				maxWordLength[buf[0] - CHINESE_MIN] = l;
		}
		delete[] buf;
	}
	fin.close();
	return a;
}

//测试案例的读入
CharStringLink ReadQuery(CharString & filename)
{
	CharStringLink a;
	ifstream fin(filename.c_str(), fstream::in);
	if (!fin.is_open())
	{
		cout << "Open file failed" << endl;
		return a;
	}
	char s0[50];
	while(fin.getline(s0, 50))
	{
		a.add(CharString(s0));
	}
	fin.close();
	return a;
}

//在词库中查找单词是否存在
bool hash_find(CharString & s, CharStringLink* dic)
{
	if(dic[hash_func(s)].search(s))
		return true;
	return false;
}


