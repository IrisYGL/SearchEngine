#include "invertedDoc.h"
#include "function.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#define LEN_MAX 15
#define CHINESE_MIN 0x4e00
#define CHINESE_MAX 0x9fbb
using namespace std;

int getDocID(CharString filename)
{
	filename = filename.substring(0, 4);
	return atoi(filename.c_str());
}

//中文分词并用所分的词构建平衡二叉树，同时建立倒排文档
AVLTree* divide(AVLTree* tree, CharString s, CharStringLink * dic, CharString rootPath, CharString filename, int * maxWordLength)
{
	int DocID = getDocID(filename);
	int taller;
	fstream fout((rootPath + filename).c_str(), fstream::out);
	if (!fout.is_open())
	{
		cout << "open file failed" << endl;
	}
	CharString m;
	for(int i = 0; i < s.len(); i++)
	{
		int len = LEN_MAX;
		unsigned char ch = (unsigned char)s.getenum(i + 1);
		int sub = 0;
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

		m = s.substring(i, sub);
		int size = MultiByteToWideChar(CP_UTF8, 0, m.c_str(), -1, nullptr, 0);
		wchar_t * buf = new wchar_t[size];
		MultiByteToWideChar(CP_UTF8, 0, m.c_str(), -1, buf, size);
		if (buf[0] >= CHINESE_MIN && buf[0] <= CHINESE_MAX)
		{
			len = maxWordLength[buf[0] - CHINESE_MIN];
			delete[] buf;
		}
		else
		{
			continue;
			delete[] buf;
		}

		do
		{
			m = s.substring(i, len);
			if(hash_find(m, dic))
			{
				AVLNode *present = tree->root;
				tree->InsertNode(tree->root, m, taller, present);
				present->a.addLinkInfo(DocID);
				present->a.occur++;
				fout << m << endl;
				i+=len - 1;
				break;
			}
			else
			{
				len--;
			}
		}
		while(len > sub);

		if (len == sub)
		{
			m = s.substring(i, sub);
			int size = MultiByteToWideChar(CP_UTF8, 0, m.c_str(), -1, nullptr, 0);
			wchar_t * buf = new wchar_t[size];
			MultiByteToWideChar(CP_UTF8, 0, m.c_str(), -1, buf, size);
			if (buf[0] >= 0x4e00 && buf[0] <= 0x9fbb)
			{
				AVLNode *present = tree->root;
				tree->InsertNode(tree->root, m, taller, present);
				present->a.addLinkInfo(DocID);
				present->a.occur++;
				fout << m << endl;
			}
			delete[] buf;
			i += sub - 1;
		}
	}
	return tree;
}