#include "data structure.h"
#include "function.h"
#include "invertedDoc.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>
#include"time.h"
#define CHINESE_MIN 0x4e00
#define CHINESE_MAX 0x9fbb
using namespace std;


int main(int argc, char * argv[])
{
	clock_t start = clock();
	char s[500];
    for (int i = strlen(argv[0]) - 1; i >= 0; --i)
	{
		if (argv[0][i] == '\\')
		{
			strncpy_s(s, 500, argv[0], i);
			s[i] = '\0';
			break;
		}
	}
	CharString command = CharString("dir ") + CharString(s) + CharString("\\input /B >file.txt");
	cout << command << endl;
	system(command.c_str());
	fstream fin((CharString(s) + CharString("\\file.txt")).c_str(), fstream::in);
	if (!fin.is_open())
	{
		cout << "open file failed" << endl;
		return 0;
	}
	char temp[500];
	CharStringLink files;
	while (fin.getline(temp, 500))
	{
		files.add(CharString(temp));
	}
	files.moveToBegin();
	AVLTree *tree = new AVLTree;

	int maxWordLength[CHINESE_MAX - CHINESE_MIN + 1] = { 0 };
	CharStringLink * dic = ReadDic(CharString(s) + "\\´Ê¿â\\´Ê¿â.dic", maxWordLength);
	int n = 0;
	for (CharStringLink::Node * p = files.next(); p; p = files.next())
	{
		cout << n++ << " ";
		CharString str = s;
		str += CharString("\\input\\") + p->m;
		CharString fs;
		ReadHtml(str.c_str(), fs);
		CharString t = p->m.substring(0, p->m.indexOf(".htm"));
		CharString content = AnalyseHtml(fs, CharString(s) + CharString("\\output\\"), t + CharString(".info"));
		tree = divide(tree, content, dic, CharString(s) + CharString("\\output\\"), t + CharString(".txt"), maxWordLength);
	}
	CharStringLink test = ReadQuery(CharString(s) + "\\query.txt");
	test.moveToBegin();
	for (CharStringLink::Node * p = test.next(); p; p = test.next())
	{
		AVLNode *search;
		CharString n = p->m;
		search = tree->SearchAVLNode(tree->root, n);
		if(search != nullptr)
		{
			if(search->a.docLink)
				search->a.LinkByTimes();
			fstream fout((CharString(s) + "\\result.txt").c_str(), fstream::out);
			while(search->a.docLink)
			{
				fout << "(" << search->a.docLink->docID <<"," <<search->a.docLink->times<<")" << " ";
				search->a.docLink = search->a.docLink->next; 
			}
			fout << endl;
		}
	}
	clock_t end = clock();
	cout << "\nTimes:" << (end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}

